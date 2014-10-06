//
//  Z80.c
//  RMBBoy
//
//  Created by Rick Buczynski on 2014-10-05.
//  Copyright (c) 2014 Rick Buczynski. All rights reserved.
//

@import Foundation;

#import "Z80.h"
#import "MMU.h"
#import "Z80_Instructions.h"

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
    
    z80->regs.ime = 0;
    
    z80->regs.m = 0;
    z80->regs.t = 0;
    
    z80->regSaves.a = 0;
    z80->regSaves.b = 0;
    z80->regSaves.c = 0;
    z80->regSaves.d = 0;
    z80->regSaves.e = 0;
    z80->regSaves.h = 0;
    z80->regSaves.l = 0;
    z80->regSaves.f = 0;
    
    z80->clock.m = 0;
    z80->clock.t = 0;
    
    z80->flags.stop = 0;
    z80->flags.halt = 0;
    
    z80->mmu = malloc(sizeof(MMU));
    MMU_reset(z80->mmu);
    
    z80->gpu = malloc(sizeof(GPU));
    GPU_reset(z80->gpu);
}

void Z80_free(Z80 *z80)
{
    MMU_free(z80->mmu);
    free(z80->mmu);
    
    GPU_free(z80->gpu);
    free(z80->gpu);
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



void Z80_run(Z80 *z80)
{

    int i = 0;
    
    while(i++ < 5) {
        int op = MMU_rb(z80->mmu,z80->regs.pc,z80->regs.pc);                // Fetch instruction
        instrMap[op](z80);                                              // Dispatch
        z80->regs.pc &= 65535;                                          // Mask PC to 16 bits
        z80->clock.m += z80->regs.m;                                    // Add time to CPU clock
        z80->clock.t += z80->regs.t;
        
        z80->regs.pc++;
    }
    
    Screen_display(z80->gpu->screen);
    
    /*
    int val = MMU_rb(&mmu,0x0100,0x0100);                // Fetch instruction
    while(i < 4) {
        val = MMU_rb(&mmu,i,0x0100);                // Fetch instruction
        NSLog(@"%c",val);
        i++;
    }
     */
    
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
    Z80_free(&z80);
    
    
}