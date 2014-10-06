//
//  Z80.h
//  RMBBoy
//
//  Created by Rick Buczynski on 2014-10-05.
//  Copyright (c) 2014 Rick Buczynski. All rights reserved.
//

#import "MMU.h"
#import "GPU.h"

typedef struct Clock {
    int m;
    int t;
} Clock;

typedef struct Registers {
    int a,b,c,d,e,h,l,f;
    int pc,sp;
    int ime;
    int m,t;
} Registers;

typedef struct RegisterSaves {
    int a,b,c,d,e,h,l,f;
} RegisterSaves;

typedef struct Flags {
    int stop, halt;
} Flags;

typedef struct Z80 {
    Registers regs;
    RegisterSaves regSaves;
    Clock clock;
    Flags flags;
    
    MMU* mmu;
    GPU* gpu;
} Z80;

void Z80_doStuff();
