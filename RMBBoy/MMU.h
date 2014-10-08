//
//  MMU.h
//  RMBBoy
//
//  Created by Rick Buczynski on 2014-10-05.
//  Copyright (c) 2014 Rick Buczynski. All rights reserved.
//

#import "GPU.h"

typedef struct GPURef {
    int *vram;
    int ***tileset;
} GPURef;

typedef struct MMU {
    int inBios;
    unsigned char *rom;
    int *wram;
    int *eram;
    int *zram;
    
    // GPU is memory mapped so MMU needs a reference to it
    GPU *gpu;
} MMU;

void MMU_reset(MMU *mmu);
void MMU_free(MMU *mmu);

int MMU_rb(MMU *mmu, int addr, int programCounter);
int MMU_rw(MMU *mmu, int addr, int programCounter);

void MMU_wb(MMU *mmu, int addr, int val);
void MMU_ww(MMU *mmu, int addr, int val);

void MMU_loadRom(MMU *mmu);

