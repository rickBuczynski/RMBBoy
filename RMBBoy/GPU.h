//
//  GPU.h
//  RMBBoy
//
//  Created by Rick Buczynski on 2014-10-06.
//  Copyright (c) 2014 Rick Buczynski. All rights reserved.
//

typedef struct Screen {
    int width;
    int height;
    int *data;
} Screen;

void Screen_reset(Screen *screen);
void Screen_free(Screen *screen);
void Screen_display(Screen *screen);

typedef struct TileSet {
    int ***tiles;
} TileSet;

void TileSet_update(TileSet *tileSet, int *vram, int addr, int val);

typedef struct GPU {
    int mode, modeClock, line;
    int switchbg, bgmap, bgtile, switchlcd;
    int scy, scx;
    
    Screen *screen;
    TileSet *tileSet;

    int *vram;
    int *palette;
} GPU;

void GPU_reset(GPU *gpu);
void GPU_free(GPU *gpu);
void GPU_renderScan(GPU *gpu);
void GPU_step(GPU *gpu, int cpuCycleCount);

int GPU_rb(GPU *gpu, int addr);
void GPU_wb(GPU *gpu, int addr, int val);
