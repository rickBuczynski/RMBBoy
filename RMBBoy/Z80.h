//
//  Z80.h
//  RMBBoy
//
//  Created by Rick Buczynski on 2014-10-05.
//  Copyright (c) 2014 Rick Buczynski. All rights reserved.
//

typedef struct Clock {
    int m;
    int t;
} Clock;

typedef struct Registers {
    int a,b,c,d,e,h,l,f;
    int pc,sp;
    int m,t;
} Registers;

typedef struct Z80 {
    Registers regs;
    Clock clock;
    
} Z80;

void Z80_doStuff();
