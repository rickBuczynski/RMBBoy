//
//  MMU.h
//  RMBBoy
//
//  Created by Rick Buczynski on 2014-10-05.
//  Copyright (c) 2014 Rick Buczynski. All rights reserved.
//

typedef struct MMU {
    int inBios;
    const char *rom;
    int *wram;
    int *eram;
    int *zram;
} MMU;

void MMU_reset(MMU *mmu);
void MMU_free(MMU *mmu);

int MMU_rb(MMU *mmu, int addr, int programCounter);
int MMU_rw(MMU *mmu, int addr, int programCounter);

void MMU_wb(MMU *mmu, int addr, int val);
void MMU_ww(MMU *mmu, int addr, int val);

void MMU_loadRom(MMU *mmu);

