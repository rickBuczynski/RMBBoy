//
//  MMU.h
//  RMBBoy
//
//  Created by Rick Buczynski on 2014-10-05.
//  Copyright (c) 2014 Rick Buczynski. All rights reserved.
//

#ifndef __RMBBoy__MMU__
#define __RMBBoy__MMU__

#include <stdio.h>

#include "Z80.h"

typedef struct MMU {
    int inBios;
    int *rom;
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

#endif /* defined(__RMBBoy__MMU__) */
