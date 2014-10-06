//
//  Instructions.h
//  RMBBoy
//
//  Created by Rick Buczynski on 2014-10-05.
//  Copyright (c) 2014 Rick Buczynski. All rights reserved.
//

void Z80_foo(Z80 *z80) {
    NSLog(@"foo");
}

void Z80_baz(Z80 *z80) {
    NSLog(@"baz");
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
    
    NSLog(@"did an add");
    
}

typedef void (*instr_ptr_t)(Z80 *);

instr_ptr_t instrMap[] =
{
    Z80_foo,
    Z80_baz,
    Z80_ADDr_e,
};
