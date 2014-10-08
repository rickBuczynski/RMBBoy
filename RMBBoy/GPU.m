//
//  GPU.m
//  RMBBoy
//
//  Created by Rick Buczynski on 2014-10-06.
//  Copyright (c) 2014 Rick Buczynski. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GPU.h"

#pragma mark - screen

void Screen_reset(Screen *screen)
{
    screen->width = 160;
    screen->height = 144;
    screen->data = malloc(160*144*sizeof(int));
    
    for (int i=0; i<160*144; i++) {
        screen->data[i] = 255;
    }
}

void Screen_free(Screen *screen)
{
    free(screen->data);
}

void Screen_display(Screen *screen)
{
    /*
    int size = screen->width*screen->height;
    
    NSMutableArray* pixels = [[NSMutableArray alloc]
                                   initWithCapacity:size];
    
    for (int i = 0; i < size; i++) {
        [pixels addObject: [NSNumber numberWithInt:screen->data[i]]];
    }
    
    [[NSNotificationCenter defaultCenter] postNotificationName:@"display gameboy screen"
                                                        object:nil
                                                      userInfo:@{@"pixels":pixels}];
     */
}

#pragma mark - tileset

void TileSet_alloc(TileSet *tileSet)
{
    // 512 x 8 x 8
    tileSet->tiles = malloc(512*sizeof(int**));
    
    for (int i=0; i<512; i++) {
        tileSet->tiles[i] = malloc(8*sizeof(int*));
        for (int j=0; j<8; j++) {
            tileSet->tiles[i][j] = calloc(8, sizeof(int));
        }
    }
}

void TileSet_free(TileSet *tileSet)
{
    // 512 x 8 x 8
    for (int i=0; i<512; i++) {
        for (int j=0; j<8; j++) {
            free(tileSet->tiles[i][j]);
        }
        free(tileSet->tiles[i]);
    }
    free(tileSet->tiles);
}

void TileSet_update(TileSet *tileSet, int *vram, int addr, int val)
{
    int saddr = addr;
    if (addr&1) { saddr--; addr--; }
    
    // work out which tile and row was updated
    int tile = (addr >> 4) & 511;
    int y = (addr >> 1) & 7;
    
    int sx;
    for (int x=0; x<8; x++) {
        // find bit index for this pixel
        sx = 1 << (7-x);
        
        // update tile set
        tileSet->tiles[tile][y][x] = ((vram[addr] & sx) ? 1 : 0) + ((vram[addr+1] & sx) ? 1 : 0);
    }
    
}

#pragma mark - gpu

void GPU_reset(GPU *gpu)
{
    gpu->mode = 2;
    gpu->modeClock = 0;
    gpu->line = 0;
    
    gpu->switchbg=0; gpu->bgmap=0; gpu->bgtile=0; gpu->switchlcd=0;
    gpu->scy=0; gpu->scx=0;
    
    gpu->screen = malloc(sizeof(Screen));
    Screen_reset(gpu->screen);
    
    gpu->tileSet = malloc(sizeof(TileSet));
    TileSet_alloc(gpu->tileSet);
    
    gpu->vram = calloc(8192, sizeof(int));
    
    gpu->palette = calloc(4, sizeof(int));
}

void GPU_free(GPU *gpu)
{
    Screen_free(gpu->screen);
    free(gpu->screen);
    
    TileSet_free(gpu->tileSet);
    free(gpu->tileSet);
    
    free(gpu->vram);
}

void GPU_step(GPU *gpu, int cpuCycleCount)
{
    gpu->modeClock += cpuCycleCount;
    
    switch (gpu->mode) {
        // OAM read mode, scanline active
        case 2:
            if (gpu->modeClock >= 80) {
                // enter scanline mode 3
                gpu->modeClock = 0;
                gpu->mode = 3;
            }
            break;
            
        // VRAM read mode, scanline active
        // treat end of mode 3 as end of scanline
        case 3:
            if (gpu->modeClock >= 172) {
                // enter hblank
                gpu->modeClock = 0;
                gpu->mode = 0;
                
                // write a scanline to the framebuffer
                GPU_renderScan(gpu);
                
            }
            break;
            
        // Hblank
        // after the last hblank, display the screen data
        case 0:
            if (gpu->modeClock >= 204) {
                gpu->modeClock = 0;
                gpu->line++;
                
                if (gpu->line == 143) {
                    // enter vblank
                    gpu->mode = 1;
                    Screen_display(gpu->screen);
                } else {
                    gpu->mode = 2;
                }
            }
            break;
            
            // Vblank (10 lines)
        case 1:
            if (gpu->modeClock >= 456) {
                gpu->modeClock = 0;
                gpu->line++;
                
                if (gpu->line > 153) {
                    // restart scannin modes
                    gpu->mode = 2;
                    gpu->line = 0;
                }
            }
            
            break;
    }
}

void GPU_renderScan(GPU *gpu)
{
    // vram offset for the tile map
    int mapoffs = gpu->bgmap ? 0x1C00 : 0x1800;
    
    // which line of the tiles to use in the map
    mapoffs += ((gpu->line + gpu->scy) & 255) >> 3;
    
    // which tile to start with in the map line
    int lineoffs = gpu->scx >> 3;
    
    //which line of pixels to use in the tiles
    int y = (gpu->line + gpu->scy) & 7;
    
    // where in the tileline to start
    int x = gpu->scx & 7;
    
    // where to render on the canvas
    int canvasoffs = gpu->line * 160;
    
    // read tile index from the background map
    int tile = gpu->vram[mapoffs + lineoffs];
    
    // if the tile data set in use is #1, the indices are signed; calculate a real tile offset
    if (gpu->bgtile == 1 && tile < 128) {
        tile += 256;
    }
    
    for (int i=0; i<160; i++) {
        // remap the tile pixel through the palette
        int colour = gpu->palette[gpu->tileSet->tiles[tile][y][x]];
    
        gpu->screen->data[canvasoffs] = colour;
        canvasoffs++;
        
        // when this tile ends, read another
        x++;
        if(x==8) {
            x=0;
            lineoffs = (lineoffs +1) & 31;
            tile = gpu->vram[mapoffs + lineoffs];
            if (gpu->bgtile == 1 && tile < 128) {
                tile += 256;
            }
        }
        
    }
}

int GPU_rb(GPU *gpu, int addr)
{
    switch (addr) {
        // lcd control
        case 0xFF40:
            return ((gpu->switchbg ? 0x01 : 0x00) |
                    (gpu->bgmap ? 0x08 : 0x00) |
                    (gpu->bgtile ? 0x10 : 0x00) |
                    (gpu->switchlcd ? 0x80 : 0x00));
            
        // scroll y
        case 0xFF42:
            return gpu->scy;
            
        // scroll x
        case 0xFF43:
            return gpu->scx;
        
        // current scanline
        case 0xFF44:
            return gpu->line;
            
        default:
            return 0;
    }
}

void GPU_wb(GPU *gpu, int addr, int val)
{
    switch (addr) {
        // lcd control
        case 0xFF40:
            gpu->switchbg = (val & 0x01) ? 1 : 0;
            gpu->bgmap = (val & 0x08) ? 1 : 0;
            gpu->bgtile = (val & 0x10) ? 1 : 0;
            gpu->switchlcd = (val & 0x80) ? 1 : 0;
            
        // scroll y
        case 0xFF42:
            gpu->scy = val;
            break;
            
        // scroll x
        case 0xFF43:
            gpu->scx = val;
            break;
            
        // background palette
        case 0xFF47:
            for (int i=0; i<4; i++) {
                switch ((val >> (i*2)) & 3) {
                    case 0: gpu->palette[i] = 255; break;
                    case 1: gpu->palette[i] = 192; break;
                    case 2: gpu->palette[i] = 96; break;
                    case 3: gpu->palette[i] = 0; break;
                }
            }
            break;
    }
}
