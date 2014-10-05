//
//  MMU.c
//  RMBBoy
//
//  Created by Rick Buczynski on 2014-10-05.
//  Copyright (c) 2014 Rick Buczynski. All rights reserved.
//

#include "MMU.h"

int MMU_rb(int addr)
{
    int memory [] = {0,0,1,2};
    return memory[addr];
}