//
//  Z80.c
//  RMBBoy
//
//  Created by Rick Buczynski on 2014-10-05.
//  Copyright (c) 2014 Rick Buczynski. All rights reserved.
//

@import Foundation;

#include "Z80.h"
#include "MMU.h"

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
    NSLog(@"z80->regs.a = %d\n",z80->regs.a);
    NSLog(@"z80->regs.b = %d\n",z80->regs.b);
    NSLog(@"z80->regs.c = %d\n",z80->regs.c);
    NSLog(@"z80->regs.d = %d\n",z80->regs.d);
    NSLog(@"z80->regs.e = %d\n",z80->regs.e);
    NSLog(@"z80->regs.h = %d\n",z80->regs.h);
    NSLog(@"z80->regs.l = %d\n",z80->regs.l);
    NSLog(@"z80->regs.f = %d\n",z80->regs.f);
    
    NSLog(@"z80->regs.pc = %d\n",z80->regs.pc);
    NSLog(@"z80->regs.sp = %d\n",z80->regs.sp);
    
    NSLog(@"z80->regs.m = %d\n",z80->regs.m);
    NSLog(@"z80->regs.t = %d\n",z80->regs.t);
    
    NSLog(@"z80->clock.m = %d\n",z80->clock.m);
    NSLog(@"z80->clock.t = %d\n",z80->clock.t);
}

#pragma mark - instructions

void Z80_foo(Z80 *z80) {
    NSLog(@"foo\n");
}

void Z80_baz(Z80 *z80) {
    NSLog(@"baz\n");
}

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

typedef void (*instr_ptr_t)(Z80 *);

instr_ptr_t instrMap[] =
{
    Z80_foo,
    Z80_baz,
    Z80_ADDr_e,
};

void Z80_run(Z80 *z80)
{
    MMU mmu;
    MMU_reset(&mmu);
    MMU_loadRom(&mmu);
    
    int i = 0;
    /*
    while(i++ < 4) {
        int op = MMU_rb(&mmu,z80->regs.pc,z80->regs.pc);                // Fetch instruction
        instrMap[op](z80);                                              // Dispatch
        z80->regs.pc &= 65535;                                          // Mask PC to 16 bits
        z80->clock.m += z80->regs.m;                                    // Add time to CPU clock
        z80->clock.t += z80->regs.t;
        
        z80->regs.pc++;
    }
     */
    
    /*
    int val = MMU_rb(&mmu,0x0100,0x0100);                // Fetch instruction
    while(i < 4) {
        val = MMU_rb(&mmu,i,0x0100);                // Fetch instruction
        NSLog(@"%c",val);
        i++;
    }
     */
    
    MMU_free(&mmu);
}

void Z80_doStuff()
{
    Z80 z80;
    
    //Z80_printRegisters(&z80);
    //Z80_reset(&z80);
    //Z80_printRegisters(&z80);
    //Z80_ADDr_e(&z80);
    //Z80_printRegisters(&z80);
    
    Z80_reset(&z80);
    Z80_run(&z80);
    
    
    
}