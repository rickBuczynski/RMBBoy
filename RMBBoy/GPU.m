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
    int size = screen->width*screen->height;
    
    NSMutableArray* pixels = [[NSMutableArray alloc]
                                   initWithCapacity:size];
    
    for (int i = 0; i < size; i++) {
        [pixels addObject: [NSNumber numberWithInt:screen->data[i]]];
    }
    
    [[NSNotificationCenter defaultCenter] postNotificationName:@"display gameboy screen"
                                                        object:nil
                                                      userInfo:@{@"pixels":pixels}];
}

#pragma mark - tileset

void TileSet_alloc(TileSet *tileSet)
{
    // 384 x 8 x 8
    tileSet->tiles = malloc(384*sizeof(int**));
    
    for (int i=0; i<384; i++) {
        tileSet->tiles[i] = malloc(8*sizeof(int*));
        for (int j=0; j<8; j++) {
            tileSet->tiles[i][j] = calloc(8, sizeof(int));
        }
    }
}

void TileSet_free(TileSet *tileSet)
{
    // 384 x 8 x 8
    for (int i=0; i<384; i++) {
        for (int j=0; j<8; j++) {
            free(tileSet->tiles[i][j]);
        }
        free(tileSet->tiles[i]);
    }
    free(tileSet->tiles);
}

void TileSet_update(TileSet *tileSet, int *vram, int addr, int val)
{
    // get "base address" for this tile row
    addr &= 0x1FFE;
    
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
    gpu->mode = 0;
    gpu->modeClock = 0;
    gpu->line = 0;
    
    gpu->screen = malloc(sizeof(Screen));
    Screen_reset(gpu->screen);
    
    gpu->tileSet = malloc(sizeof(TileSet));
    TileSet_alloc(gpu->tileSet);
    
    gpu->vram = calloc(8192, sizeof(int));
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
    
}
