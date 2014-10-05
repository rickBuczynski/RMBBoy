//
//  Z80.c
//  RMBBoy
//
//  Created by Rick Buczynski on 2014-10-05.
//  Copyright (c) 2014 Rick Buczynski. All rights reserved.
//

#include "Z80.h"

typedef struct Clock {
    // TODO: should these be ints or are they 8bit/16bit?
    int32_t m;
    int32_t t;
} Clock;

typedef struct Registers {
    int32_t a,b,c,d,e,h,l,f;
    int32_t pc,sp;
    int32_t m,t;
} Registers;

typedef struct Z80 {
    Registers regs;
    Clock clock;
} Z80;

void Z80_reset(Z80 *z80)
{
    z80->regs.a = 0;
    z80->regs.b = 0;
    z80->regs.c = 0;
    z80->regs.d = 0;
    z80->regs.e = 0;
    z80->regs.h = 0;
    z80->regs.l = 0;
    z80->regs.f = 0;
    
    z80->regs.pc = 0;
    z80->regs.sp = 0;
    
    z80->regs.m = 0;
    z80->regs.t = 0;
    
    z80->clock.m = 0;
    z80->clock.t = 0;
}

void Z80_printRegisters(Z80 *z80)
{
    printf("z80->regs.a = %d\n",z80->regs.a);
    printf("z80->regs.b = %d\n",z80->regs.b);
    printf("z80->regs.c = %d\n",z80->regs.c);
    printf("z80->regs.d = %d\n",z80->regs.d);
    printf("z80->regs.e = %d\n",z80->regs.e);
    printf("z80->regs.h = %d\n",z80->regs.h);
    printf("z80->regs.l = %d\n",z80->regs.l);
    printf("z80->regs.f = %d\n",z80->regs.f);
    
    printf("z80->regs.pc = %d\n",z80->regs.pc);
    printf("z80->regs.sp = %d\n",z80->regs.sp);
    
    printf("z80->regs.m = %d\n",z80->regs.m);
    printf("z80->regs.t = %d\n",z80->regs.t);
    
    printf("z80->clock.m = %d\n",z80->clock.m);
    printf("z80->clock.t = %d\n",z80->clock.t);
}

#pragma mark - instructions

void Z80_ADDr_e(Z80 *z80) {
    z80->regs.a += z80->regs.e;
    z80->regs.f = 0;
    if (!(z80->regs.a & 255)) {
        z80->regs.f |= 0x80;
    }
    if (z80->regs.a > 255) {
        z80->regs.f |= 0x10;
    }
    z80->regs.a &= 255;
    z80->regs.m = 1;
    z80->regs.t = 4;
    
}

void Z80_run()
{
    Z80 z80;
    
    Z80_printRegisters(&z80);
    Z80_reset(&z80);
    Z80_printRegisters(&z80);
    Z80_ADDr_e(&z80);
    Z80_printRegisters(&z80);
    
}