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
    int* data;
} Screen;

void Screen_reset(Screen *screen);
void Screen_free(Screen *screen);
void Screen_display(Screen *screen);

typedef struct GPU {
    Screen *screen;
    
} GPU;

void GPU_reset(GPU *gpu);
void GPU_free(GPU *gpu);