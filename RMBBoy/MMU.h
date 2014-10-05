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

int MMU_rb(int addr);
int MMU_rw(int addr);

void MMU_wb(int addr, int val);
void MMU_ww(int addr, int val);

#endif /* defined(__RMBBoy__MMU__) */
