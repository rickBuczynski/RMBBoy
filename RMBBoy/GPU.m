//
//  GPU.m
//  RMBBoy
//
//  Created by Rick Buczynski on 2014-10-06.
//  Copyright (c) 2014 Rick Buczynski. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GPU.h"


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

void GPU_reset(GPU *gpu)
{
    gpu->screen = malloc(sizeof(Screen));
    Screen_reset(gpu->screen);
}

void GPU_free(GPU *gpu)
{
    Screen_free(gpu->screen);
    free(gpu->screen);
}