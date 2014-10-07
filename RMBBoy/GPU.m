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

#pragma mark - gpu

void GPU_reset(GPU *gpu)
{
    gpu->screen = malloc(sizeof(Screen));
    Screen_reset(gpu->screen);
    
    gpu->mode = 0;
    gpu->modeClock = 0;
    gpu->line = 0;
}

void GPU_free(GPU *gpu)
{
    Screen_free(gpu->screen);
    free(gpu->screen);
}

void GPU_renderScan(GPU *gpu)
{
    
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