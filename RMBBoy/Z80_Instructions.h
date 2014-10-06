//
//  Instructions.h
//  RMBBoy
//
//  Created by Rick Buczynski on 2014-10-05.
//  Copyright (c) 2014 Rick Buczynski. All rights reserved.
//

#import "MMU.h"

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

/*--- Helper functions ---*/
void rsv(Z80 *z80) {
    z80->regSaves.a = z80->regs.a; z80->regSaves.b = z80->regs.b;
    z80->regSaves.c = z80->regs.c; z80->regSaves.d = z80->regs.d;
    z80->regSaves.e = z80->regs.e; z80->regSaves.f = z80->regs.f;
    z80->regSaves.h = z80->regs.h; z80->regSaves.l = z80->regs.l;
}

void rrs(Z80 *z80) {
    z80->regs.a = z80->regSaves.a; z80->regs.b = z80->regSaves.b;
    z80->regs.c = z80->regSaves.c; z80->regs.d = z80->regSaves.d;
    z80->regs.e = z80->regSaves.e; z80->regs.f = z80->regSaves.f;
    z80->regs.h = z80->regSaves.h; z80->regs.l = z80->regSaves.l;
}

/*
void MAPcb(Z80 *z80) {
    int i=MMU_rb(z80->mmu,z80->regs.pc, z80->regs.pc); z80->regs.pc++;
    z80->regs.pc &= 65535;
    if(Z80._cbmap[i]) Z80._cbmap[i]();
    else console.log(i);
}
*/

void XX(Z80 *z80) {
    /*Undefined map entry*/
    int opc = z80->regs.pc-1;
    NSLog(@"Unimplemented instruction at %d stopping.", opc);
    z80->flags.stop=1;
}

/*--- Load/store ---*/
void LDrr_bb(Z80 *z80) { z80->regs.b=z80->regs.b; z80->regs.m=1; }
void LDrr_bc(Z80 *z80) { z80->regs.b=z80->regs.c; z80->regs.m=1; }
void LDrr_bd(Z80 *z80) { z80->regs.b=z80->regs.d; z80->regs.m=1; }
void LDrr_be(Z80 *z80) { z80->regs.b=z80->regs.e; z80->regs.m=1; }
void LDrr_bh(Z80 *z80) { z80->regs.b=z80->regs.h; z80->regs.m=1; }
void LDrr_bl(Z80 *z80) { z80->regs.b=z80->regs.l; z80->regs.m=1; }
void LDrr_ba(Z80 *z80) { z80->regs.b=z80->regs.a; z80->regs.m=1; }
void LDrr_cb(Z80 *z80) { z80->regs.c=z80->regs.b; z80->regs.m=1; }
void LDrr_cc(Z80 *z80) { z80->regs.c=z80->regs.c; z80->regs.m=1; }
void LDrr_cd(Z80 *z80) { z80->regs.c=z80->regs.d; z80->regs.m=1; }
void LDrr_ce(Z80 *z80) { z80->regs.c=z80->regs.e; z80->regs.m=1; }
void LDrr_ch(Z80 *z80) { z80->regs.c=z80->regs.h; z80->regs.m=1; }
void LDrr_cl(Z80 *z80) { z80->regs.c=z80->regs.l; z80->regs.m=1; }
void LDrr_ca(Z80 *z80) { z80->regs.c=z80->regs.a; z80->regs.m=1; }
void LDrr_db(Z80 *z80) { z80->regs.d=z80->regs.b; z80->regs.m=1; }
void LDrr_dc(Z80 *z80) { z80->regs.d=z80->regs.c; z80->regs.m=1; }
void LDrr_dd(Z80 *z80) { z80->regs.d=z80->regs.d; z80->regs.m=1; }
void LDrr_de(Z80 *z80) { z80->regs.d=z80->regs.e; z80->regs.m=1; }
void LDrr_dh(Z80 *z80) { z80->regs.d=z80->regs.h; z80->regs.m=1; }
void LDrr_dl(Z80 *z80) { z80->regs.d=z80->regs.l; z80->regs.m=1; }
void LDrr_da(Z80 *z80) { z80->regs.d=z80->regs.a; z80->regs.m=1; }
void LDrr_eb(Z80 *z80) { z80->regs.e=z80->regs.b; z80->regs.m=1; }
void LDrr_ec(Z80 *z80) { z80->regs.e=z80->regs.c; z80->regs.m=1; }
void LDrr_ed(Z80 *z80) { z80->regs.e=z80->regs.d; z80->regs.m=1; }
void LDrr_ee(Z80 *z80) { z80->regs.e=z80->regs.e; z80->regs.m=1; }
void LDrr_eh(Z80 *z80) { z80->regs.e=z80->regs.h; z80->regs.m=1; }
void LDrr_el(Z80 *z80) { z80->regs.e=z80->regs.l; z80->regs.m=1; }
void LDrr_ea(Z80 *z80) { z80->regs.e=z80->regs.a; z80->regs.m=1; }
void LDrr_hb(Z80 *z80) { z80->regs.h=z80->regs.b; z80->regs.m=1; }
void LDrr_hc(Z80 *z80) { z80->regs.h=z80->regs.c; z80->regs.m=1; }
void LDrr_hd(Z80 *z80) { z80->regs.h=z80->regs.d; z80->regs.m=1; }
void LDrr_he(Z80 *z80) { z80->regs.h=z80->regs.e; z80->regs.m=1; }
void LDrr_hh(Z80 *z80) { z80->regs.h=z80->regs.h; z80->regs.m=1; }
void LDrr_hl(Z80 *z80) { z80->regs.h=z80->regs.l; z80->regs.m=1; }
void LDrr_ha(Z80 *z80) { z80->regs.h=z80->regs.a; z80->regs.m=1; }
void LDrr_lb(Z80 *z80) { z80->regs.l=z80->regs.b; z80->regs.m=1; }
void LDrr_lc(Z80 *z80) { z80->regs.l=z80->regs.c; z80->regs.m=1; }
void LDrr_ld(Z80 *z80) { z80->regs.l=z80->regs.d; z80->regs.m=1; }
void LDrr_le(Z80 *z80) { z80->regs.l=z80->regs.e; z80->regs.m=1; }
void LDrr_lh(Z80 *z80) { z80->regs.l=z80->regs.h; z80->regs.m=1; }
void LDrr_ll(Z80 *z80) { z80->regs.l=z80->regs.l; z80->regs.m=1; }
void LDrr_la(Z80 *z80) { z80->regs.l=z80->regs.a; z80->regs.m=1; }
void LDrr_ab(Z80 *z80) { z80->regs.a=z80->regs.b; z80->regs.m=1; }
void LDrr_ac(Z80 *z80) { z80->regs.a=z80->regs.c; z80->regs.m=1; }
void LDrr_ad(Z80 *z80) { z80->regs.a=z80->regs.d; z80->regs.m=1; }
void LDrr_ae(Z80 *z80) { z80->regs.a=z80->regs.e; z80->regs.m=1; }
void LDrr_ah(Z80 *z80) { z80->regs.a=z80->regs.h; z80->regs.m=1; }
void LDrr_al(Z80 *z80) { z80->regs.a=z80->regs.l; z80->regs.m=1; }
void LDrr_aa(Z80 *z80) { z80->regs.a=z80->regs.a; z80->regs.m=1; }

void LDrHLm_b(Z80 *z80) { z80->regs.b=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); z80->regs.m=2; }
void LDrHLm_c(Z80 *z80) { z80->regs.c=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); z80->regs.m=2; }
void LDrHLm_d(Z80 *z80) { z80->regs.d=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); z80->regs.m=2; }
void LDrHLm_e(Z80 *z80) { z80->regs.e=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); z80->regs.m=2; }
void LDrHLm_h(Z80 *z80) { z80->regs.h=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); z80->regs.m=2; }
void LDrHLm_l(Z80 *z80) { z80->regs.l=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); z80->regs.m=2; }
void LDrHLm_a(Z80 *z80) { z80->regs.a=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); z80->regs.m=2; }

void LDHLmr_b(Z80 *z80) { MMU_wb(z80->mmu,(z80->regs.h<<8)+z80->regs.l,z80->regs.b); z80->regs.m=2; }
void LDHLmr_c(Z80 *z80) { MMU_wb(z80->mmu,(z80->regs.h<<8)+z80->regs.l,z80->regs.c); z80->regs.m=2; }
void LDHLmr_d(Z80 *z80) { MMU_wb(z80->mmu,(z80->regs.h<<8)+z80->regs.l,z80->regs.d); z80->regs.m=2; }
void LDHLmr_e(Z80 *z80) { MMU_wb(z80->mmu,(z80->regs.h<<8)+z80->regs.l,z80->regs.e); z80->regs.m=2; }
void LDHLmr_h(Z80 *z80) { MMU_wb(z80->mmu,(z80->regs.h<<8)+z80->regs.l,z80->regs.h); z80->regs.m=2; }
void LDHLmr_l(Z80 *z80) { MMU_wb(z80->mmu,(z80->regs.h<<8)+z80->regs.l,z80->regs.l); z80->regs.m=2; }
void LDHLmr_a(Z80 *z80) { MMU_wb(z80->mmu,(z80->regs.h<<8)+z80->regs.l,z80->regs.a); z80->regs.m=2; }

void LDrn_b(Z80 *z80) { z80->regs.b=MMU_rb(z80->mmu,z80->regs.pc, z80->regs.pc); z80->regs.pc++; z80->regs.m=2; }
void LDrn_c(Z80 *z80) { z80->regs.c=MMU_rb(z80->mmu,z80->regs.pc, z80->regs.pc); z80->regs.pc++; z80->regs.m=2; }
void LDrn_d(Z80 *z80) { z80->regs.d=MMU_rb(z80->mmu,z80->regs.pc, z80->regs.pc); z80->regs.pc++; z80->regs.m=2; }
void LDrn_e(Z80 *z80) { z80->regs.e=MMU_rb(z80->mmu,z80->regs.pc, z80->regs.pc); z80->regs.pc++; z80->regs.m=2; }
void LDrn_h(Z80 *z80) { z80->regs.h=MMU_rb(z80->mmu,z80->regs.pc, z80->regs.pc); z80->regs.pc++; z80->regs.m=2; }
void LDrn_l(Z80 *z80) { z80->regs.l=MMU_rb(z80->mmu,z80->regs.pc, z80->regs.pc); z80->regs.pc++; z80->regs.m=2; }
void LDrn_a(Z80 *z80) { z80->regs.a=MMU_rb(z80->mmu,z80->regs.pc, z80->regs.pc); z80->regs.pc++; z80->regs.m=2; }

void LDHLmn(Z80 *z80) { MMU_wb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, MMU_rb(z80->mmu,z80->regs.pc, z80->regs.pc)); z80->regs.pc++; z80->regs.m=3; }

void LDBCmA(Z80 *z80) { MMU_wb(z80->mmu,(z80->regs.b<<8)+z80->regs.c, z80->regs.a); z80->regs.m=2; }
void LDDEmA(Z80 *z80) { MMU_wb(z80->mmu,(z80->regs.d<<8)+z80->regs.e, z80->regs.a); z80->regs.m=2; }

void LDmmA(Z80 *z80) { MMU_wb(z80->mmu,MMU_rw(z80->mmu,z80->regs.pc, z80->regs.pc), z80->regs.a); z80->regs.pc+=2; z80->regs.m=4; }

void LDABCm(Z80 *z80) { z80->regs.a=MMU_rb(z80->mmu,(z80->regs.b<<8)+z80->regs.c, z80->regs.pc); z80->regs.m=2; }
void LDADEm(Z80 *z80) { z80->regs.a=MMU_rb(z80->mmu,(z80->regs.d<<8)+z80->regs.e, z80->regs.pc); z80->regs.m=2; }

void LDAmm(Z80 *z80) { z80->regs.a=MMU_rb(z80->mmu,MMU_rw(z80->mmu,z80->regs.pc, z80->regs.pc), z80->regs.pc); z80->regs.pc+=2; z80->regs.m=4; }

void LDBCnn(Z80 *z80) { z80->regs.c=MMU_rb(z80->mmu,z80->regs.pc, z80->regs.pc); z80->regs.b=MMU_rb(z80->mmu,z80->regs.pc+1, z80->regs.pc); z80->regs.pc+=2; z80->regs.m=3; }
void LDDEnn(Z80 *z80) { z80->regs.e=MMU_rb(z80->mmu,z80->regs.pc, z80->regs.pc); z80->regs.d=MMU_rb(z80->mmu,z80->regs.pc+1, z80->regs.pc); z80->regs.pc+=2; z80->regs.m=3; }
void LDHLnn(Z80 *z80) { z80->regs.l=MMU_rb(z80->mmu,z80->regs.pc, z80->regs.pc); z80->regs.h=MMU_rb(z80->mmu,z80->regs.pc+1, z80->regs.pc); z80->regs.pc+=2; z80->regs.m=3; }
void LDSPnn(Z80 *z80) { z80->regs.sp=MMU_rw(z80->mmu,z80->regs.pc, z80->regs.pc); z80->regs.pc+=2; z80->regs.m=3; }

void LDHLmm(Z80 *z80) { int i=MMU_rw(z80->mmu,z80->regs.pc, z80->regs.pc); z80->regs.pc+=2; z80->regs.l=MMU_rb(z80->mmu,i, z80->regs.pc); z80->regs.h=MMU_rb(z80->mmu,i+1, z80->regs.pc); z80->regs.m=5; }
void LDmmHL(Z80 *z80) { int i=MMU_rw(z80->mmu,z80->regs.pc, z80->regs.pc); z80->regs.pc+=2; MMU_ww(z80->mmu,i,(z80->regs.h<<8)+z80->regs.l); z80->regs.m=5; }

void LDHLIA(Z80 *z80) { MMU_wb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.a); z80->regs.l=(z80->regs.l+1)&255; if(!z80->regs.l) z80->regs.h=(z80->regs.h+1)&255; z80->regs.m=2; }
void LDAHLI(Z80 *z80) { z80->regs.a=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); z80->regs.l=(z80->regs.l+1)&255; if(!z80->regs.l) z80->regs.h=(z80->regs.h+1)&255; z80->regs.m=2; }

void LDHLDA(Z80 *z80) { MMU_wb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.a); z80->regs.l=(z80->regs.l-1)&255; if(z80->regs.l==255) z80->regs.h=(z80->regs.h-1)&255; z80->regs.m=2; }
void LDAHLD(Z80 *z80) { z80->regs.a=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); z80->regs.l=(z80->regs.l-1)&255; if(z80->regs.l==255) z80->regs.h=(z80->regs.h-1)&255; z80->regs.m=2; }

void LDAIOn(Z80 *z80) { z80->regs.a=MMU_rb(z80->mmu,0xFF00+MMU_rb(z80->mmu,z80->regs.pc, z80->regs.pc), z80->regs.pc); z80->regs.pc++; z80->regs.m=3; }
void LDIOnA(Z80 *z80) { MMU_wb(z80->mmu,0xFF00+MMU_rb(z80->mmu,z80->regs.pc, z80->regs.pc),z80->regs.a); z80->regs.pc++; z80->regs.m=3; }
void LDAIOC(Z80 *z80) { z80->regs.a=MMU_rb(z80->mmu,0xFF00+z80->regs.c, z80->regs.pc); z80->regs.m=2; }
void LDIOCA(Z80 *z80) { MMU_wb(z80->mmu,0xFF00+z80->regs.c,z80->regs.a); z80->regs.m=2; }

void LDHLSPn(Z80 *z80) { int i=MMU_rb(z80->mmu,z80->regs.pc, z80->regs.pc); if(i>127) i=-((~i+1)&255); z80->regs.pc++; i+=z80->regs.sp; z80->regs.h=(i>>8)&255; z80->regs.l=i&255; z80->regs.m=3; }

void SWAPr_b(Z80 *z80) { int tr=z80->regs.b; z80->regs.b=((tr&0xF)<<4)|((tr&0xF0)>>4); z80->regs.f=z80->regs.b?0:0x80; z80->regs.m=1; }
void SWAPr_c(Z80 *z80) { int tr=z80->regs.c; z80->regs.c=((tr&0xF)<<4)|((tr&0xF0)>>4); z80->regs.f=z80->regs.c?0:0x80; z80->regs.m=1; }
void SWAPr_d(Z80 *z80) { int tr=z80->regs.d; z80->regs.d=((tr&0xF)<<4)|((tr&0xF0)>>4); z80->regs.f=z80->regs.d?0:0x80; z80->regs.m=1; }
void SWAPr_e(Z80 *z80) { int tr=z80->regs.e; z80->regs.e=((tr&0xF)<<4)|((tr&0xF0)>>4); z80->regs.f=z80->regs.e?0:0x80; z80->regs.m=1; }
void SWAPr_h(Z80 *z80) { int tr=z80->regs.h; z80->regs.h=((tr&0xF)<<4)|((tr&0xF0)>>4); z80->regs.f=z80->regs.h?0:0x80; z80->regs.m=1; }
void SWAPr_l(Z80 *z80) { int tr=z80->regs.l; z80->regs.l=((tr&0xF)<<4)|((tr&0xF0)>>4); z80->regs.f=z80->regs.l?0:0x80; z80->regs.m=1; }
void SWAPr_a(Z80 *z80) { int tr=z80->regs.a; z80->regs.a=((tr&0xF)<<4)|((tr&0xF0)>>4); z80->regs.f=z80->regs.a?0:0x80; z80->regs.m=1; }

/*--- Data processing ---*/
void ADDr_b(Z80 *z80) { int a=z80->regs.a; z80->regs.a+=z80->regs.b; z80->regs.f=(z80->regs.a>255)?0x10:0; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.b^a)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void ADDr_c(Z80 *z80) { int a=z80->regs.a; z80->regs.a+=z80->regs.c; z80->regs.f=(z80->regs.a>255)?0x10:0; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.c^a)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void ADDr_d(Z80 *z80) { int a=z80->regs.a; z80->regs.a+=z80->regs.d; z80->regs.f=(z80->regs.a>255)?0x10:0; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.d^a)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void ADDr_e(Z80 *z80) { int a=z80->regs.a; z80->regs.a+=z80->regs.e; z80->regs.f=(z80->regs.a>255)?0x10:0; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.e^a)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void ADDr_h(Z80 *z80) { int a=z80->regs.a; z80->regs.a+=z80->regs.h; z80->regs.f=(z80->regs.a>255)?0x10:0; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.h^a)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void ADDr_l(Z80 *z80) { int a=z80->regs.a; z80->regs.a+=z80->regs.l; z80->regs.f=(z80->regs.a>255)?0x10:0; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.l^a)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void ADDr_a(Z80 *z80) { int a=z80->regs.a; z80->regs.a+=z80->regs.a; z80->regs.f=(z80->regs.a>255)?0x10:0; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.a^a)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void ADDHL(Z80 *z80) { int a=z80->regs.a; int m=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); z80->regs.a+=m; z80->regs.f=(z80->regs.a>255)?0x10:0; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^a^m)&0x10) z80->regs.f|=0x20; z80->regs.m=2; }
void ADDn(Z80 *z80) { int a=z80->regs.a; int m=MMU_rb(z80->mmu,z80->regs.pc, z80->regs.pc); z80->regs.a+=m; z80->regs.pc++; z80->regs.f=(z80->regs.a>255)?0x10:0; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^a^m)&0x10) z80->regs.f|=0x20; z80->regs.m=2; }
void ADDHLBC(Z80 *z80) { int hl=(z80->regs.h<<8)+z80->regs.l; hl+=(z80->regs.b<<8)+z80->regs.c; if(hl>65535) z80->regs.f|=0x10; else z80->regs.f&=0xEF; z80->regs.h=(hl>>8)&255; z80->regs.l=hl&255; z80->regs.m=3; }
void ADDHLDE(Z80 *z80) { int hl=(z80->regs.h<<8)+z80->regs.l; hl+=(z80->regs.d<<8)+z80->regs.e; if(hl>65535) z80->regs.f|=0x10; else z80->regs.f&=0xEF; z80->regs.h=(hl>>8)&255; z80->regs.l=hl&255; z80->regs.m=3; }
void ADDHLHL(Z80 *z80) { int hl=(z80->regs.h<<8)+z80->regs.l; hl+=(z80->regs.h<<8)+z80->regs.l; if(hl>65535) z80->regs.f|=0x10; else z80->regs.f&=0xEF; z80->regs.h=(hl>>8)&255; z80->regs.l=hl&255; z80->regs.m=3; }
void ADDHLSP(Z80 *z80) { int hl=(z80->regs.h<<8)+z80->regs.l; hl+=z80->regs.sp; if(hl>65535) z80->regs.f|=0x10; else z80->regs.f&=0xEF; z80->regs.h=(hl>>8)&255; z80->regs.l=hl&255; z80->regs.m=3; }
void ADDSPn(Z80 *z80) { int i=MMU_rb(z80->mmu,z80->regs.pc, z80->regs.pc); if(i>127) i=-((~i+1)&255); z80->regs.pc++; z80->regs.sp+=i; z80->regs.m=4; }

void ADCr_b(Z80 *z80) { int a=z80->regs.a; z80->regs.a+=z80->regs.b; z80->regs.a+=(z80->regs.f&0x10)?1:0; z80->regs.f=(z80->regs.a>255)?0x10:0; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.b^a)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void ADCr_c(Z80 *z80) { int a=z80->regs.a; z80->regs.a+=z80->regs.c; z80->regs.a+=(z80->regs.f&0x10)?1:0; z80->regs.f=(z80->regs.a>255)?0x10:0; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.c^a)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void ADCr_d(Z80 *z80) { int a=z80->regs.a; z80->regs.a+=z80->regs.d; z80->regs.a+=(z80->regs.f&0x10)?1:0; z80->regs.f=(z80->regs.a>255)?0x10:0; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.d^a)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void ADCr_e(Z80 *z80) { int a=z80->regs.a; z80->regs.a+=z80->regs.e; z80->regs.a+=(z80->regs.f&0x10)?1:0; z80->regs.f=(z80->regs.a>255)?0x10:0; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.e^a)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void ADCr_h(Z80 *z80) { int a=z80->regs.a; z80->regs.a+=z80->regs.h; z80->regs.a+=(z80->regs.f&0x10)?1:0; z80->regs.f=(z80->regs.a>255)?0x10:0; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.h^a)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void ADCr_l(Z80 *z80) { int a=z80->regs.a; z80->regs.a+=z80->regs.l; z80->regs.a+=(z80->regs.f&0x10)?1:0; z80->regs.f=(z80->regs.a>255)?0x10:0; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.l^a)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void ADCr_a(Z80 *z80) { int a=z80->regs.a; z80->regs.a+=z80->regs.a; z80->regs.a+=(z80->regs.f&0x10)?1:0; z80->regs.f=(z80->regs.a>255)?0x10:0; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.a^a)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void ADCHL(Z80 *z80) { int a=z80->regs.a; int m=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); z80->regs.a+=m; z80->regs.a+=(z80->regs.f&0x10)?1:0; z80->regs.f=(z80->regs.a>255)?0x10:0; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^m^a)&0x10) z80->regs.f|=0x20; z80->regs.m=2; }
void ADCn(Z80 *z80) { int a=z80->regs.a; int m=MMU_rb(z80->mmu,z80->regs.pc, z80->regs.pc); z80->regs.a+=m; z80->regs.pc++; z80->regs.a+=(z80->regs.f&0x10)?1:0; z80->regs.f=(z80->regs.a>255)?0x10:0; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^m^a)&0x10) z80->regs.f|=0x20; z80->regs.m=2; }

void SUBr_b(Z80 *z80) { int a=z80->regs.a; z80->regs.a-=z80->regs.b; z80->regs.f=(z80->regs.a<0)?0x50:0x40; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.b^a)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void SUBr_c(Z80 *z80) { int a=z80->regs.a; z80->regs.a-=z80->regs.c; z80->regs.f=(z80->regs.a<0)?0x50:0x40; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.c^a)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void SUBr_d(Z80 *z80) { int a=z80->regs.a; z80->regs.a-=z80->regs.d; z80->regs.f=(z80->regs.a<0)?0x50:0x40; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.d^a)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void SUBr_e(Z80 *z80) { int a=z80->regs.a; z80->regs.a-=z80->regs.e; z80->regs.f=(z80->regs.a<0)?0x50:0x40; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.e^a)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void SUBr_h(Z80 *z80) { int a=z80->regs.a; z80->regs.a-=z80->regs.h; z80->regs.f=(z80->regs.a<0)?0x50:0x40; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.h^a)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void SUBr_l(Z80 *z80) { int a=z80->regs.a; z80->regs.a-=z80->regs.l; z80->regs.f=(z80->regs.a<0)?0x50:0x40; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.l^a)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void SUBr_a(Z80 *z80) { int a=z80->regs.a; z80->regs.a-=z80->regs.a; z80->regs.f=(z80->regs.a<0)?0x50:0x40; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.a^a)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void SUBHL(Z80 *z80) { int a=z80->regs.a; int m=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); z80->regs.a-=m; z80->regs.f=(z80->regs.a<0)?0x50:0x40; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^m^a)&0x10) z80->regs.f|=0x20; z80->regs.m=2; }
void SUBn(Z80 *z80) { int a=z80->regs.a; int m=MMU_rb(z80->mmu,z80->regs.pc, z80->regs.pc); z80->regs.a-=m; z80->regs.pc++; z80->regs.f=(z80->regs.a<0)?0x50:0x40; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^m^a)&0x10) z80->regs.f|=0x20; z80->regs.m=2; }

void SBCr_b(Z80 *z80) { int a=z80->regs.a; z80->regs.a-=z80->regs.b; z80->regs.a-=(z80->regs.f&0x10)?1:0; z80->regs.f=(z80->regs.a<0)?0x50:0x40; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.b^a)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void SBCr_c(Z80 *z80) { int a=z80->regs.a; z80->regs.a-=z80->regs.c; z80->regs.a-=(z80->regs.f&0x10)?1:0; z80->regs.f=(z80->regs.a<0)?0x50:0x40; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.c^a)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void SBCr_d(Z80 *z80) { int a=z80->regs.a; z80->regs.a-=z80->regs.d; z80->regs.a-=(z80->regs.f&0x10)?1:0; z80->regs.f=(z80->regs.a<0)?0x50:0x40; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.d^a)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void SBCr_e(Z80 *z80) { int a=z80->regs.a; z80->regs.a-=z80->regs.e; z80->regs.a-=(z80->regs.f&0x10)?1:0; z80->regs.f=(z80->regs.a<0)?0x50:0x40; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.e^a)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void SBCr_h(Z80 *z80) { int a=z80->regs.a; z80->regs.a-=z80->regs.h; z80->regs.a-=(z80->regs.f&0x10)?1:0; z80->regs.f=(z80->regs.a<0)?0x50:0x40; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.h^a)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void SBCr_l(Z80 *z80) { int a=z80->regs.a; z80->regs.a-=z80->regs.l; z80->regs.a-=(z80->regs.f&0x10)?1:0; z80->regs.f=(z80->regs.a<0)?0x50:0x40; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.l^a)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void SBCr_a(Z80 *z80) { int a=z80->regs.a; z80->regs.a-=z80->regs.a; z80->regs.a-=(z80->regs.f&0x10)?1:0; z80->regs.f=(z80->regs.a<0)?0x50:0x40; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.a^a)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void SBCHL(Z80 *z80) { int a=z80->regs.a; int m=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); z80->regs.a-=m; z80->regs.a-=(z80->regs.f&0x10)?1:0; z80->regs.f=(z80->regs.a<0)?0x50:0x40; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^m^a)&0x10) z80->regs.f|=0x20; z80->regs.m=2; }
void SBCn(Z80 *z80) { int a=z80->regs.a; int m=MMU_rb(z80->mmu,z80->regs.pc, z80->regs.pc); z80->regs.a-=m; z80->regs.pc++; z80->regs.a-=(z80->regs.f&0x10)?1:0; z80->regs.f=(z80->regs.a<0)?0x50:0x40; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; if((z80->regs.a^m^a)&0x10) z80->regs.f|=0x20; z80->regs.m=2; }

void CPr_b(Z80 *z80) { int i=z80->regs.a; i-=z80->regs.b; z80->regs.f=(i<0)?0x50:0x40; i&=255; if(!i) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.b^i)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void CPr_c(Z80 *z80) { int i=z80->regs.a; i-=z80->regs.c; z80->regs.f=(i<0)?0x50:0x40; i&=255; if(!i) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.c^i)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void CPr_d(Z80 *z80) { int i=z80->regs.a; i-=z80->regs.d; z80->regs.f=(i<0)?0x50:0x40; i&=255; if(!i) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.d^i)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void CPr_e(Z80 *z80) { int i=z80->regs.a; i-=z80->regs.e; z80->regs.f=(i<0)?0x50:0x40; i&=255; if(!i) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.e^i)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void CPr_h(Z80 *z80) { int i=z80->regs.a; i-=z80->regs.h; z80->regs.f=(i<0)?0x50:0x40; i&=255; if(!i) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.h^i)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void CPr_l(Z80 *z80) { int i=z80->regs.a; i-=z80->regs.l; z80->regs.f=(i<0)?0x50:0x40; i&=255; if(!i) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.l^i)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void CPr_a(Z80 *z80) { int i=z80->regs.a; i-=z80->regs.a; z80->regs.f=(i<0)?0x50:0x40; i&=255; if(!i) z80->regs.f|=0x80; if((z80->regs.a^z80->regs.a^i)&0x10) z80->regs.f|=0x20; z80->regs.m=1; }
void CPHL(Z80 *z80) { int i=z80->regs.a; int m=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); i-=m; z80->regs.f=(i<0)?0x50:0x40; i&=255; if(!i) z80->regs.f|=0x80; if((z80->regs.a^i^m)&0x10) z80->regs.f|=0x20; z80->regs.m=2; }
void CPn(Z80 *z80) { int i=z80->regs.a; int m=MMU_rb(z80->mmu,z80->regs.pc, z80->regs.pc); i-=m; z80->regs.pc++; z80->regs.f=(i<0)?0x50:0x40; i&=255; if(!i) z80->regs.f|=0x80; if((z80->regs.a^i^m)&0x10) z80->regs.f|=0x20; z80->regs.m=2; }

void DAA(Z80 *z80) { int a=z80->regs.a; if((z80->regs.f&0x20)||((z80->regs.a&15)>9)) z80->regs.a+=6; z80->regs.f&=0xEF; if((z80->regs.f&0x20)||(a>0x99)) { z80->regs.a+=0x60; z80->regs.f|=0x10; } z80->regs.m=1; }

void ANDr_b(Z80 *z80) { z80->regs.a&=z80->regs.b; z80->regs.a&=255; z80->regs.f=z80->regs.a?0:0x80; z80->regs.m=1; }
void ANDr_c(Z80 *z80) { z80->regs.a&=z80->regs.c; z80->regs.a&=255; z80->regs.f=z80->regs.a?0:0x80; z80->regs.m=1; }
void ANDr_d(Z80 *z80) { z80->regs.a&=z80->regs.d; z80->regs.a&=255; z80->regs.f=z80->regs.a?0:0x80; z80->regs.m=1; }
void ANDr_e(Z80 *z80) { z80->regs.a&=z80->regs.e; z80->regs.a&=255; z80->regs.f=z80->regs.a?0:0x80; z80->regs.m=1; }
void ANDr_h(Z80 *z80) { z80->regs.a&=z80->regs.h; z80->regs.a&=255; z80->regs.f=z80->regs.a?0:0x80; z80->regs.m=1; }
void ANDr_l(Z80 *z80) { z80->regs.a&=z80->regs.l; z80->regs.a&=255; z80->regs.f=z80->regs.a?0:0x80; z80->regs.m=1; }
void ANDr_a(Z80 *z80) { z80->regs.a&=z80->regs.a; z80->regs.a&=255; z80->regs.f=z80->regs.a?0:0x80; z80->regs.m=1; }
void ANDHL(Z80 *z80) { z80->regs.a&=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); z80->regs.a&=255; z80->regs.f=z80->regs.a?0:0x80; z80->regs.m=2; }
void ANDn(Z80 *z80) { z80->regs.a&=MMU_rb(z80->mmu,z80->regs.pc, z80->regs.pc); z80->regs.pc++; z80->regs.a&=255; z80->regs.f=z80->regs.a?0:0x80; z80->regs.m=2; }

void ORr_b(Z80 *z80) { z80->regs.a|=z80->regs.b; z80->regs.a&=255; z80->regs.f=z80->regs.a?0:0x80; z80->regs.m=1; }
void ORr_c(Z80 *z80) { z80->regs.a|=z80->regs.c; z80->regs.a&=255; z80->regs.f=z80->regs.a?0:0x80; z80->regs.m=1; }
void ORr_d(Z80 *z80) { z80->regs.a|=z80->regs.d; z80->regs.a&=255; z80->regs.f=z80->regs.a?0:0x80; z80->regs.m=1; }
void ORr_e(Z80 *z80) { z80->regs.a|=z80->regs.e; z80->regs.a&=255; z80->regs.f=z80->regs.a?0:0x80; z80->regs.m=1; }
void ORr_h(Z80 *z80) { z80->regs.a|=z80->regs.h; z80->regs.a&=255; z80->regs.f=z80->regs.a?0:0x80; z80->regs.m=1; }
void ORr_l(Z80 *z80) { z80->regs.a|=z80->regs.l; z80->regs.a&=255; z80->regs.f=z80->regs.a?0:0x80; z80->regs.m=1; }
void ORr_a(Z80 *z80) { z80->regs.a|=z80->regs.a; z80->regs.a&=255; z80->regs.f=z80->regs.a?0:0x80; z80->regs.m=1; }
void ORHL(Z80 *z80) { z80->regs.a|=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); z80->regs.a&=255; z80->regs.f=z80->regs.a?0:0x80; z80->regs.m=2; }
void ORn(Z80 *z80) { z80->regs.a|=MMU_rb(z80->mmu,z80->regs.pc, z80->regs.pc); z80->regs.pc++; z80->regs.a&=255; z80->regs.f=z80->regs.a?0:0x80; z80->regs.m=2; }

void XORr_b(Z80 *z80) { z80->regs.a^=z80->regs.b; z80->regs.a&=255; z80->regs.f=z80->regs.a?0:0x80; z80->regs.m=1; }
void XORr_c(Z80 *z80) { z80->regs.a^=z80->regs.c; z80->regs.a&=255; z80->regs.f=z80->regs.a?0:0x80; z80->regs.m=1; }
void XORr_d(Z80 *z80) { z80->regs.a^=z80->regs.d; z80->regs.a&=255; z80->regs.f=z80->regs.a?0:0x80; z80->regs.m=1; }
void XORr_e(Z80 *z80) { z80->regs.a^=z80->regs.e; z80->regs.a&=255; z80->regs.f=z80->regs.a?0:0x80; z80->regs.m=1; }
void XORr_h(Z80 *z80) { z80->regs.a^=z80->regs.h; z80->regs.a&=255; z80->regs.f=z80->regs.a?0:0x80; z80->regs.m=1; }
void XORr_l(Z80 *z80) { z80->regs.a^=z80->regs.l; z80->regs.a&=255; z80->regs.f=z80->regs.a?0:0x80; z80->regs.m=1; }
void XORr_a(Z80 *z80) { z80->regs.a^=z80->regs.a; z80->regs.a&=255; z80->regs.f=z80->regs.a?0:0x80; z80->regs.m=1; }
void XORHL(Z80 *z80) { z80->regs.a^=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); z80->regs.a&=255; z80->regs.f=z80->regs.a?0:0x80; z80->regs.m=2; }
void XORn(Z80 *z80) { z80->regs.a^=MMU_rb(z80->mmu,z80->regs.pc, z80->regs.pc); z80->regs.pc++; z80->regs.a&=255; z80->regs.f=z80->regs.a?0:0x80; z80->regs.m=2; }

void INCr_b(Z80 *z80) { z80->regs.b++; z80->regs.b&=255; z80->regs.f=z80->regs.b?0:0x80; z80->regs.m=1; }
void INCr_c(Z80 *z80) { z80->regs.c++; z80->regs.c&=255; z80->regs.f=z80->regs.c?0:0x80; z80->regs.m=1; }
void INCr_d(Z80 *z80) { z80->regs.d++; z80->regs.d&=255; z80->regs.f=z80->regs.d?0:0x80; z80->regs.m=1; }
void INCr_e(Z80 *z80) { z80->regs.e++; z80->regs.e&=255; z80->regs.f=z80->regs.e?0:0x80; z80->regs.m=1; }
void INCr_h(Z80 *z80) { z80->regs.h++; z80->regs.h&=255; z80->regs.f=z80->regs.h?0:0x80; z80->regs.m=1; }
void INCr_l(Z80 *z80) { z80->regs.l++; z80->regs.l&=255; z80->regs.f=z80->regs.l?0:0x80; z80->regs.m=1; }
void INCr_a(Z80 *z80) { z80->regs.a++; z80->regs.a&=255; z80->regs.f=z80->regs.a?0:0x80; z80->regs.m=1; }
void INCHLm(Z80 *z80) { int i=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc)+1; i&=255; MMU_wb(z80->mmu,(z80->regs.h<<8)+z80->regs.l,i); z80->regs.f=i?0:0x80; z80->regs.m=3; }

void DECr_b(Z80 *z80) { z80->regs.b--; z80->regs.b&=255; z80->regs.f=z80->regs.b?0:0x80; z80->regs.m=1; }
void DECr_c(Z80 *z80) { z80->regs.c--; z80->regs.c&=255; z80->regs.f=z80->regs.c?0:0x80; z80->regs.m=1; }
void DECr_d(Z80 *z80) { z80->regs.d--; z80->regs.d&=255; z80->regs.f=z80->regs.d?0:0x80; z80->regs.m=1; }
void DECr_e(Z80 *z80) { z80->regs.e--; z80->regs.e&=255; z80->regs.f=z80->regs.e?0:0x80; z80->regs.m=1; }
void DECr_h(Z80 *z80) { z80->regs.h--; z80->regs.h&=255; z80->regs.f=z80->regs.h?0:0x80; z80->regs.m=1; }
void DECr_l(Z80 *z80) { z80->regs.l--; z80->regs.l&=255; z80->regs.f=z80->regs.l?0:0x80; z80->regs.m=1; }
void DECr_a(Z80 *z80) { z80->regs.a--; z80->regs.a&=255; z80->regs.f=z80->regs.a?0:0x80; z80->regs.m=1; }
void DECHLm(Z80 *z80) { int i=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc)-1; i&=255; MMU_wb(z80->mmu,(z80->regs.h<<8)+z80->regs.l,i); z80->regs.f=i?0:0x80; z80->regs.m=3; }

void INCBC(Z80 *z80) { z80->regs.c=(z80->regs.c+1)&255; if(!z80->regs.c) z80->regs.b=(z80->regs.b+1)&255; z80->regs.m=1; }
void INCDE(Z80 *z80) { z80->regs.e=(z80->regs.e+1)&255; if(!z80->regs.e) z80->regs.d=(z80->regs.d+1)&255; z80->regs.m=1; }
void INCHL(Z80 *z80) { z80->regs.l=(z80->regs.l+1)&255; if(!z80->regs.l) z80->regs.h=(z80->regs.h+1)&255; z80->regs.m=1; }
void INCSP(Z80 *z80) { z80->regs.sp=(z80->regs.sp+1)&65535; z80->regs.m=1; }

void DECBC(Z80 *z80) { z80->regs.c=(z80->regs.c-1)&255; if(z80->regs.c==255) z80->regs.b=(z80->regs.b-1)&255; z80->regs.m=1; }
void DECDE(Z80 *z80) { z80->regs.e=(z80->regs.e-1)&255; if(z80->regs.e==255) z80->regs.d=(z80->regs.d-1)&255; z80->regs.m=1; }
void DECHL(Z80 *z80) { z80->regs.l=(z80->regs.l-1)&255; if(z80->regs.l==255) z80->regs.h=(z80->regs.h-1)&255; z80->regs.m=1; }
void DECSP(Z80 *z80) { z80->regs.sp=(z80->regs.sp-1)&65535; z80->regs.m=1; }

/*--- Bit manipulation ---*/
void BIT0b(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.b&0x01)?0:0x80; z80->regs.m=2; }
void BIT0c(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.c&0x01)?0:0x80; z80->regs.m=2; }
void BIT0d(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.d&0x01)?0:0x80; z80->regs.m=2; }
void BIT0e(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.e&0x01)?0:0x80; z80->regs.m=2; }
void BIT0h(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.h&0x01)?0:0x80; z80->regs.m=2; }
void BIT0l(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.l&0x01)?0:0x80; z80->regs.m=2; }
void BIT0a(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.a&0x01)?0:0x80; z80->regs.m=2; }
void BIT0m(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc)&0x01)?0:0x80; z80->regs.m=3; }

void RES0b(Z80 *z80) { z80->regs.b&=0xFE; z80->regs.m=2; }
void RES0c(Z80 *z80) { z80->regs.c&=0xFE; z80->regs.m=2; }
void RES0d(Z80 *z80) { z80->regs.d&=0xFE; z80->regs.m=2; }
void RES0e(Z80 *z80) { z80->regs.e&=0xFE; z80->regs.m=2; }
void RES0h(Z80 *z80) { z80->regs.h&=0xFE; z80->regs.m=2; }
void RES0l(Z80 *z80) { z80->regs.l&=0xFE; z80->regs.m=2; }
void RES0a(Z80 *z80) { z80->regs.a&=0xFE; z80->regs.m=2; }
void RES0m(Z80 *z80) { int i=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); i&=0xFE; MMU_wb(z80->mmu,(z80->regs.h<<8)+z80->regs.l,i); z80->regs.m=4; }

void SET0b(Z80 *z80) { z80->regs.b|=0x01; z80->regs.m=2; }
void SET0c(Z80 *z80) { z80->regs.b|=0x01; z80->regs.m=2; }
void SET0d(Z80 *z80) { z80->regs.b|=0x01; z80->regs.m=2; }
void SET0e(Z80 *z80) { z80->regs.b|=0x01; z80->regs.m=2; }
void SET0h(Z80 *z80) { z80->regs.b|=0x01; z80->regs.m=2; }
void SET0l(Z80 *z80) { z80->regs.b|=0x01; z80->regs.m=2; }
void SET0a(Z80 *z80) { z80->regs.b|=0x01; z80->regs.m=2; }
void SET0m(Z80 *z80) { int i=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); i|=0x01; MMU_wb(z80->mmu,(z80->regs.h<<8)+z80->regs.l,i); z80->regs.m=4; }

void BIT1b(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.b&0x02)?0:0x80; z80->regs.m=2; }
void BIT1c(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.c&0x02)?0:0x80; z80->regs.m=2; }
void BIT1d(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.d&0x02)?0:0x80; z80->regs.m=2; }
void BIT1e(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.e&0x02)?0:0x80; z80->regs.m=2; }
void BIT1h(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.h&0x02)?0:0x80; z80->regs.m=2; }
void BIT1l(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.l&0x02)?0:0x80; z80->regs.m=2; }
void BIT1a(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.a&0x02)?0:0x80; z80->regs.m=2; }
void BIT1m(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc)&0x02)?0:0x80; z80->regs.m=3; }

void RES1b(Z80 *z80) { z80->regs.b&=0xFD; z80->regs.m=2; }
void RES1c(Z80 *z80) { z80->regs.c&=0xFD; z80->regs.m=2; }
void RES1d(Z80 *z80) { z80->regs.d&=0xFD; z80->regs.m=2; }
void RES1e(Z80 *z80) { z80->regs.e&=0xFD; z80->regs.m=2; }
void RES1h(Z80 *z80) { z80->regs.h&=0xFD; z80->regs.m=2; }
void RES1l(Z80 *z80) { z80->regs.l&=0xFD; z80->regs.m=2; }
void RES1a(Z80 *z80) { z80->regs.a&=0xFD; z80->regs.m=2; }
void RES1m(Z80 *z80) { int i=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); i&=0xFD; MMU_wb(z80->mmu,(z80->regs.h<<8)+z80->regs.l,i); z80->regs.m=4; }

void SET1b(Z80 *z80) { z80->regs.b|=0x02; z80->regs.m=2; }
void SET1c(Z80 *z80) { z80->regs.b|=0x02; z80->regs.m=2; }
void SET1d(Z80 *z80) { z80->regs.b|=0x02; z80->regs.m=2; }
void SET1e(Z80 *z80) { z80->regs.b|=0x02; z80->regs.m=2; }
void SET1h(Z80 *z80) { z80->regs.b|=0x02; z80->regs.m=2; }
void SET1l(Z80 *z80) { z80->regs.b|=0x02; z80->regs.m=2; }
void SET1a(Z80 *z80) { z80->regs.b|=0x02; z80->regs.m=2; }
void SET1m(Z80 *z80) { int i=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); i|=0x02; MMU_wb(z80->mmu,(z80->regs.h<<8)+z80->regs.l,i); z80->regs.m=4; }

void BIT2b(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.b&0x04)?0:0x80; z80->regs.m=2; }
void BIT2c(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.c&0x04)?0:0x80; z80->regs.m=2; }
void BIT2d(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.d&0x04)?0:0x80; z80->regs.m=2; }
void BIT2e(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.e&0x04)?0:0x80; z80->regs.m=2; }
void BIT2h(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.h&0x04)?0:0x80; z80->regs.m=2; }
void BIT2l(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.l&0x04)?0:0x80; z80->regs.m=2; }
void BIT2a(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.a&0x04)?0:0x80; z80->regs.m=2; }
void BIT2m(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc)&0x04)?0:0x80; z80->regs.m=3; }

void RES2b(Z80 *z80) { z80->regs.b&=0xFB; z80->regs.m=2; }
void RES2c(Z80 *z80) { z80->regs.c&=0xFB; z80->regs.m=2; }
void RES2d(Z80 *z80) { z80->regs.d&=0xFB; z80->regs.m=2; }
void RES2e(Z80 *z80) { z80->regs.e&=0xFB; z80->regs.m=2; }
void RES2h(Z80 *z80) { z80->regs.h&=0xFB; z80->regs.m=2; }
void RES2l(Z80 *z80) { z80->regs.l&=0xFB; z80->regs.m=2; }
void RES2a(Z80 *z80) { z80->regs.a&=0xFB; z80->regs.m=2; }
void RES2m(Z80 *z80) { int i=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); i&=0xFB; MMU_wb(z80->mmu,(z80->regs.h<<8)+z80->regs.l,i); z80->regs.m=4; }

void SET2b(Z80 *z80) { z80->regs.b|=0x04; z80->regs.m=2; }
void SET2c(Z80 *z80) { z80->regs.b|=0x04; z80->regs.m=2; }
void SET2d(Z80 *z80) { z80->regs.b|=0x04; z80->regs.m=2; }
void SET2e(Z80 *z80) { z80->regs.b|=0x04; z80->regs.m=2; }
void SET2h(Z80 *z80) { z80->regs.b|=0x04; z80->regs.m=2; }
void SET2l(Z80 *z80) { z80->regs.b|=0x04; z80->regs.m=2; }
void SET2a(Z80 *z80) { z80->regs.b|=0x04; z80->regs.m=2; }
void SET2m(Z80 *z80) { int i=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); i|=0x04; MMU_wb(z80->mmu,(z80->regs.h<<8)+z80->regs.l,i); z80->regs.m=4; }

void BIT3b(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.b&0x08)?0:0x80; z80->regs.m=2; }
void BIT3c(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.c&0x08)?0:0x80; z80->regs.m=2; }
void BIT3d(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.d&0x08)?0:0x80; z80->regs.m=2; }
void BIT3e(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.e&0x08)?0:0x80; z80->regs.m=2; }
void BIT3h(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.h&0x08)?0:0x80; z80->regs.m=2; }
void BIT3l(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.l&0x08)?0:0x80; z80->regs.m=2; }
void BIT3a(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.a&0x08)?0:0x80; z80->regs.m=2; }
void BIT3m(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc)&0x08)?0:0x80; z80->regs.m=3; }

void RES3b(Z80 *z80) { z80->regs.b&=0xF7; z80->regs.m=2; }
void RES3c(Z80 *z80) { z80->regs.c&=0xF7; z80->regs.m=2; }
void RES3d(Z80 *z80) { z80->regs.d&=0xF7; z80->regs.m=2; }
void RES3e(Z80 *z80) { z80->regs.e&=0xF7; z80->regs.m=2; }
void RES3h(Z80 *z80) { z80->regs.h&=0xF7; z80->regs.m=2; }
void RES3l(Z80 *z80) { z80->regs.l&=0xF7; z80->regs.m=2; }
void RES3a(Z80 *z80) { z80->regs.a&=0xF7; z80->regs.m=2; }
void RES3m(Z80 *z80) { int i=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); i&=0xF7; MMU_wb(z80->mmu,(z80->regs.h<<8)+z80->regs.l,i); z80->regs.m=4; }

void SET3b(Z80 *z80) { z80->regs.b|=0x08; z80->regs.m=2; }
void SET3c(Z80 *z80) { z80->regs.b|=0x08; z80->regs.m=2; }
void SET3d(Z80 *z80) { z80->regs.b|=0x08; z80->regs.m=2; }
void SET3e(Z80 *z80) { z80->regs.b|=0x08; z80->regs.m=2; }
void SET3h(Z80 *z80) { z80->regs.b|=0x08; z80->regs.m=2; }
void SET3l(Z80 *z80) { z80->regs.b|=0x08; z80->regs.m=2; }
void SET3a(Z80 *z80) { z80->regs.b|=0x08; z80->regs.m=2; }
void SET3m(Z80 *z80) { int i=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); i|=0x08; MMU_wb(z80->mmu,(z80->regs.h<<8)+z80->regs.l,i); z80->regs.m=4; }

void BIT4b(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.b&0x10)?0:0x80; z80->regs.m=2; }
void BIT4c(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.c&0x10)?0:0x80; z80->regs.m=2; }
void BIT4d(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.d&0x10)?0:0x80; z80->regs.m=2; }
void BIT4e(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.e&0x10)?0:0x80; z80->regs.m=2; }
void BIT4h(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.h&0x10)?0:0x80; z80->regs.m=2; }
void BIT4l(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.l&0x10)?0:0x80; z80->regs.m=2; }
void BIT4a(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.a&0x10)?0:0x80; z80->regs.m=2; }
void BIT4m(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc)&0x10)?0:0x80; z80->regs.m=3; }

void RES4b(Z80 *z80) { z80->regs.b&=0xEF; z80->regs.m=2; }
void RES4c(Z80 *z80) { z80->regs.c&=0xEF; z80->regs.m=2; }
void RES4d(Z80 *z80) { z80->regs.d&=0xEF; z80->regs.m=2; }
void RES4e(Z80 *z80) { z80->regs.e&=0xEF; z80->regs.m=2; }
void RES4h(Z80 *z80) { z80->regs.h&=0xEF; z80->regs.m=2; }
void RES4l(Z80 *z80) { z80->regs.l&=0xEF; z80->regs.m=2; }
void RES4a(Z80 *z80) { z80->regs.a&=0xEF; z80->regs.m=2; }
void RES4m(Z80 *z80) { int i=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); i&=0xEF; MMU_wb(z80->mmu,(z80->regs.h<<8)+z80->regs.l,i); z80->regs.m=4; }

void SET4b(Z80 *z80) { z80->regs.b|=0x10; z80->regs.m=2; }
void SET4c(Z80 *z80) { z80->regs.b|=0x10; z80->regs.m=2; }
void SET4d(Z80 *z80) { z80->regs.b|=0x10; z80->regs.m=2; }
void SET4e(Z80 *z80) { z80->regs.b|=0x10; z80->regs.m=2; }
void SET4h(Z80 *z80) { z80->regs.b|=0x10; z80->regs.m=2; }
void SET4l(Z80 *z80) { z80->regs.b|=0x10; z80->regs.m=2; }
void SET4a(Z80 *z80) { z80->regs.b|=0x10; z80->regs.m=2; }
void SET4m(Z80 *z80) { int i=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); i|=0x10; MMU_wb(z80->mmu,(z80->regs.h<<8)+z80->regs.l,i); z80->regs.m=4; }

void BIT5b(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.b&0x20)?0:0x80; z80->regs.m=2; }
void BIT5c(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.c&0x20)?0:0x80; z80->regs.m=2; }
void BIT5d(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.d&0x20)?0:0x80; z80->regs.m=2; }
void BIT5e(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.e&0x20)?0:0x80; z80->regs.m=2; }
void BIT5h(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.h&0x20)?0:0x80; z80->regs.m=2; }
void BIT5l(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.l&0x20)?0:0x80; z80->regs.m=2; }
void BIT5a(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.a&0x20)?0:0x80; z80->regs.m=2; }
void BIT5m(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc)&0x20)?0:0x80; z80->regs.m=3; }

void RES5b(Z80 *z80) { z80->regs.b&=0xDF; z80->regs.m=2; }
void RES5c(Z80 *z80) { z80->regs.c&=0xDF; z80->regs.m=2; }
void RES5d(Z80 *z80) { z80->regs.d&=0xDF; z80->regs.m=2; }
void RES5e(Z80 *z80) { z80->regs.e&=0xDF; z80->regs.m=2; }
void RES5h(Z80 *z80) { z80->regs.h&=0xDF; z80->regs.m=2; }
void RES5l(Z80 *z80) { z80->regs.l&=0xDF; z80->regs.m=2; }
void RES5a(Z80 *z80) { z80->regs.a&=0xDF; z80->regs.m=2; }
void RES5m(Z80 *z80) { int i=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); i&=0xDF; MMU_wb(z80->mmu,(z80->regs.h<<8)+z80->regs.l,i); z80->regs.m=4; }

void SET5b(Z80 *z80) { z80->regs.b|=0x20; z80->regs.m=2; }
void SET5c(Z80 *z80) { z80->regs.b|=0x20; z80->regs.m=2; }
void SET5d(Z80 *z80) { z80->regs.b|=0x20; z80->regs.m=2; }
void SET5e(Z80 *z80) { z80->regs.b|=0x20; z80->regs.m=2; }
void SET5h(Z80 *z80) { z80->regs.b|=0x20; z80->regs.m=2; }
void SET5l(Z80 *z80) { z80->regs.b|=0x20; z80->regs.m=2; }
void SET5a(Z80 *z80) { z80->regs.b|=0x20; z80->regs.m=2; }
void SET5m(Z80 *z80) { int i=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); i|=0x20; MMU_wb(z80->mmu,(z80->regs.h<<8)+z80->regs.l,i); z80->regs.m=4; }

void BIT6b(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.b&0x40)?0:0x80; z80->regs.m=2; }
void BIT6c(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.c&0x40)?0:0x80; z80->regs.m=2; }
void BIT6d(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.d&0x40)?0:0x80; z80->regs.m=2; }
void BIT6e(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.e&0x40)?0:0x80; z80->regs.m=2; }
void BIT6h(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.h&0x40)?0:0x80; z80->regs.m=2; }
void BIT6l(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.l&0x40)?0:0x80; z80->regs.m=2; }
void BIT6a(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.a&0x40)?0:0x80; z80->regs.m=2; }
void BIT6m(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc)&0x40)?0:0x80; z80->regs.m=3; }

void RES6b(Z80 *z80) { z80->regs.b&=0xBF; z80->regs.m=2; }
void RES6c(Z80 *z80) { z80->regs.c&=0xBF; z80->regs.m=2; }
void RES6d(Z80 *z80) { z80->regs.d&=0xBF; z80->regs.m=2; }
void RES6e(Z80 *z80) { z80->regs.e&=0xBF; z80->regs.m=2; }
void RES6h(Z80 *z80) { z80->regs.h&=0xBF; z80->regs.m=2; }
void RES6l(Z80 *z80) { z80->regs.l&=0xBF; z80->regs.m=2; }
void RES6a(Z80 *z80) { z80->regs.a&=0xBF; z80->regs.m=2; }
void RES6m(Z80 *z80) { int i=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); i&=0xBF; MMU_wb(z80->mmu,(z80->regs.h<<8)+z80->regs.l,i); z80->regs.m=4; }

void SET6b(Z80 *z80) { z80->regs.b|=0x40; z80->regs.m=2; }
void SET6c(Z80 *z80) { z80->regs.b|=0x40; z80->regs.m=2; }
void SET6d(Z80 *z80) { z80->regs.b|=0x40; z80->regs.m=2; }
void SET6e(Z80 *z80) { z80->regs.b|=0x40; z80->regs.m=2; }
void SET6h(Z80 *z80) { z80->regs.b|=0x40; z80->regs.m=2; }
void SET6l(Z80 *z80) { z80->regs.b|=0x40; z80->regs.m=2; }
void SET6a(Z80 *z80) { z80->regs.b|=0x40; z80->regs.m=2; }
void SET6m(Z80 *z80) { int i=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); i|=0x40; MMU_wb(z80->mmu,(z80->regs.h<<8)+z80->regs.l,i); z80->regs.m=4; }

void BIT7b(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.b&0x80)?0:0x80; z80->regs.m=2; }
void BIT7c(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.c&0x80)?0:0x80; z80->regs.m=2; }
void BIT7d(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.d&0x80)?0:0x80; z80->regs.m=2; }
void BIT7e(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.e&0x80)?0:0x80; z80->regs.m=2; }
void BIT7h(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.h&0x80)?0:0x80; z80->regs.m=2; }
void BIT7l(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.l&0x80)?0:0x80; z80->regs.m=2; }
void BIT7a(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(z80->regs.a&0x80)?0:0x80; z80->regs.m=2; }
void BIT7m(Z80 *z80) { z80->regs.f&=0x1F; z80->regs.f|=0x20; z80->regs.f=(MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc)&0x80)?0:0x80; z80->regs.m=3; }

void RES7b(Z80 *z80) { z80->regs.b&=0x7F; z80->regs.m=2; }
void RES7c(Z80 *z80) { z80->regs.c&=0x7F; z80->regs.m=2; }
void RES7d(Z80 *z80) { z80->regs.d&=0x7F; z80->regs.m=2; }
void RES7e(Z80 *z80) { z80->regs.e&=0x7F; z80->regs.m=2; }
void RES7h(Z80 *z80) { z80->regs.h&=0x7F; z80->regs.m=2; }
void RES7l(Z80 *z80) { z80->regs.l&=0x7F; z80->regs.m=2; }
void RES7a(Z80 *z80) { z80->regs.a&=0x7F; z80->regs.m=2; }
void RES7m(Z80 *z80) { int i=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); i&=0x7F; MMU_wb(z80->mmu,(z80->regs.h<<8)+z80->regs.l,i); z80->regs.m=4; }

void SET7b(Z80 *z80) { z80->regs.b|=0x80; z80->regs.m=2; }
void SET7c(Z80 *z80) { z80->regs.b|=0x80; z80->regs.m=2; }
void SET7d(Z80 *z80) { z80->regs.b|=0x80; z80->regs.m=2; }
void SET7e(Z80 *z80) { z80->regs.b|=0x80; z80->regs.m=2; }
void SET7h(Z80 *z80) { z80->regs.b|=0x80; z80->regs.m=2; }
void SET7l(Z80 *z80) { z80->regs.b|=0x80; z80->regs.m=2; }
void SET7a(Z80 *z80) { z80->regs.b|=0x80; z80->regs.m=2; }
void SET7m(Z80 *z80) { int i=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); i|=0x80; MMU_wb(z80->mmu,(z80->regs.h<<8)+z80->regs.l,i); z80->regs.m=4; }

void RLA(Z80 *z80) { int ci=z80->regs.f&0x10?1:0; int co=z80->regs.a&0x80?0x10:0; z80->regs.a=(z80->regs.a<<1)+ci; z80->regs.a&=255; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=1; }
void RLCA(Z80 *z80) { int ci=z80->regs.a&0x80?1:0; int co=z80->regs.a&0x80?0x10:0; z80->regs.a=(z80->regs.a<<1)+ci; z80->regs.a&=255; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=1; }
void RRA(Z80 *z80) { int ci=z80->regs.f&0x10?0x80:0; int co=z80->regs.a&1?0x10:0; z80->regs.a=(z80->regs.a>>1)+ci; z80->regs.a&=255; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=1; }
void RRCA(Z80 *z80) { int ci=z80->regs.a&1?0x80:0; int co=z80->regs.a&1?0x10:0; z80->regs.a=(z80->regs.a>>1)+ci; z80->regs.a&=255; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=1; }

void RLr_b(Z80 *z80) { int ci=z80->regs.f&0x10?1:0; int co=z80->regs.b&0x80?0x10:0; z80->regs.b=(z80->regs.b<<1)+ci; z80->regs.b&=255; z80->regs.f=(z80->regs.b)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void RLr_c(Z80 *z80) { int ci=z80->regs.f&0x10?1:0; int co=z80->regs.c&0x80?0x10:0; z80->regs.c=(z80->regs.c<<1)+ci; z80->regs.c&=255; z80->regs.f=(z80->regs.c)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void RLr_d(Z80 *z80) { int ci=z80->regs.f&0x10?1:0; int co=z80->regs.d&0x80?0x10:0; z80->regs.d=(z80->regs.d<<1)+ci; z80->regs.d&=255; z80->regs.f=(z80->regs.d)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void RLr_e(Z80 *z80) { int ci=z80->regs.f&0x10?1:0; int co=z80->regs.e&0x80?0x10:0; z80->regs.e=(z80->regs.e<<1)+ci; z80->regs.e&=255; z80->regs.f=(z80->regs.e)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void RLr_h(Z80 *z80) { int ci=z80->regs.f&0x10?1:0; int co=z80->regs.h&0x80?0x10:0; z80->regs.h=(z80->regs.h<<1)+ci; z80->regs.h&=255; z80->regs.f=(z80->regs.h)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void RLr_l(Z80 *z80) { int ci=z80->regs.f&0x10?1:0; int co=z80->regs.l&0x80?0x10:0; z80->regs.l=(z80->regs.l<<1)+ci; z80->regs.l&=255; z80->regs.f=(z80->regs.l)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void RLr_a(Z80 *z80) { int ci=z80->regs.f&0x10?1:0; int co=z80->regs.a&0x80?0x10:0; z80->regs.a=(z80->regs.a<<1)+ci; z80->regs.a&=255; z80->regs.f=(z80->regs.a)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void RLHL(Z80 *z80) { int i=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); int ci=z80->regs.f&0x10?1:0; int co=i&0x80?0x10:0; i=(i<<1)+ci; i&=255; z80->regs.f=(i)?0:0x80; MMU_wb(z80->mmu,(z80->regs.h<<8)+z80->regs.l,i); z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=4; }

void RLCr_b(Z80 *z80) { int ci=z80->regs.b&0x80?1:0; int co=z80->regs.b&0x80?0x10:0; z80->regs.b=(z80->regs.b<<1)+ci; z80->regs.b&=255; z80->regs.f=(z80->regs.b)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void RLCr_c(Z80 *z80) { int ci=z80->regs.c&0x80?1:0; int co=z80->regs.c&0x80?0x10:0; z80->regs.c=(z80->regs.c<<1)+ci; z80->regs.c&=255; z80->regs.f=(z80->regs.c)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void RLCr_d(Z80 *z80) { int ci=z80->regs.d&0x80?1:0; int co=z80->regs.d&0x80?0x10:0; z80->regs.d=(z80->regs.d<<1)+ci; z80->regs.d&=255; z80->regs.f=(z80->regs.d)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void RLCr_e(Z80 *z80) { int ci=z80->regs.e&0x80?1:0; int co=z80->regs.e&0x80?0x10:0; z80->regs.e=(z80->regs.e<<1)+ci; z80->regs.e&=255; z80->regs.f=(z80->regs.e)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void RLCr_h(Z80 *z80) { int ci=z80->regs.h&0x80?1:0; int co=z80->regs.h&0x80?0x10:0; z80->regs.h=(z80->regs.h<<1)+ci; z80->regs.h&=255; z80->regs.f=(z80->regs.h)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void RLCr_l(Z80 *z80) { int ci=z80->regs.l&0x80?1:0; int co=z80->regs.l&0x80?0x10:0; z80->regs.l=(z80->regs.l<<1)+ci; z80->regs.l&=255; z80->regs.f=(z80->regs.l)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void RLCr_a(Z80 *z80) { int ci=z80->regs.a&0x80?1:0; int co=z80->regs.a&0x80?0x10:0; z80->regs.a=(z80->regs.a<<1)+ci; z80->regs.a&=255; z80->regs.f=(z80->regs.a)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void RLCHL(Z80 *z80) { int i=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); int ci=i&0x80?1:0; int co=i&0x80?0x10:0; i=(i<<1)+ci; i&=255; z80->regs.f=(i)?0:0x80; MMU_wb(z80->mmu,(z80->regs.h<<8)+z80->regs.l,i); z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=4; }

void RRr_b(Z80 *z80) { int ci=z80->regs.f&0x10?0x80:0; int co=z80->regs.b&1?0x10:0; z80->regs.b=(z80->regs.b>>1)+ci; z80->regs.b&=255; z80->regs.f=(z80->regs.b)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void RRr_c(Z80 *z80) { int ci=z80->regs.f&0x10?0x80:0; int co=z80->regs.c&1?0x10:0; z80->regs.c=(z80->regs.c>>1)+ci; z80->regs.c&=255; z80->regs.f=(z80->regs.c)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void RRr_d(Z80 *z80) { int ci=z80->regs.f&0x10?0x80:0; int co=z80->regs.d&1?0x10:0; z80->regs.d=(z80->regs.d>>1)+ci; z80->regs.d&=255; z80->regs.f=(z80->regs.d)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void RRr_e(Z80 *z80) { int ci=z80->regs.f&0x10?0x80:0; int co=z80->regs.e&1?0x10:0; z80->regs.e=(z80->regs.e>>1)+ci; z80->regs.e&=255; z80->regs.f=(z80->regs.e)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void RRr_h(Z80 *z80) { int ci=z80->regs.f&0x10?0x80:0; int co=z80->regs.h&1?0x10:0; z80->regs.h=(z80->regs.h>>1)+ci; z80->regs.h&=255; z80->regs.f=(z80->regs.h)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void RRr_l(Z80 *z80) { int ci=z80->regs.f&0x10?0x80:0; int co=z80->regs.l&1?0x10:0; z80->regs.l=(z80->regs.l>>1)+ci; z80->regs.l&=255; z80->regs.f=(z80->regs.l)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void RRr_a(Z80 *z80) { int ci=z80->regs.f&0x10?0x80:0; int co=z80->regs.a&1?0x10:0; z80->regs.a=(z80->regs.a>>1)+ci; z80->regs.a&=255; z80->regs.f=(z80->regs.a)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void RRHL(Z80 *z80) { int i=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); int ci=z80->regs.f&0x10?0x80:0; int co=i&1?0x10:0; i=(i>>1)+ci; i&=255; MMU_wb(z80->mmu,(z80->regs.h<<8)+z80->regs.l,i); z80->regs.f=(i)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=4; }

void RRCr_b(Z80 *z80) { int ci=z80->regs.b&1?0x80:0; int co=z80->regs.b&1?0x10:0; z80->regs.b=(z80->regs.b>>1)+ci; z80->regs.b&=255; z80->regs.f=(z80->regs.b)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void RRCr_c(Z80 *z80) { int ci=z80->regs.c&1?0x80:0; int co=z80->regs.c&1?0x10:0; z80->regs.c=(z80->regs.c>>1)+ci; z80->regs.c&=255; z80->regs.f=(z80->regs.c)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void RRCr_d(Z80 *z80) { int ci=z80->regs.d&1?0x80:0; int co=z80->regs.d&1?0x10:0; z80->regs.d=(z80->regs.d>>1)+ci; z80->regs.d&=255; z80->regs.f=(z80->regs.d)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void RRCr_e(Z80 *z80) { int ci=z80->regs.e&1?0x80:0; int co=z80->regs.e&1?0x10:0; z80->regs.e=(z80->regs.e>>1)+ci; z80->regs.e&=255; z80->regs.f=(z80->regs.e)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void RRCr_h(Z80 *z80) { int ci=z80->regs.h&1?0x80:0; int co=z80->regs.h&1?0x10:0; z80->regs.h=(z80->regs.h>>1)+ci; z80->regs.h&=255; z80->regs.f=(z80->regs.h)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void RRCr_l(Z80 *z80) { int ci=z80->regs.l&1?0x80:0; int co=z80->regs.l&1?0x10:0; z80->regs.l=(z80->regs.l>>1)+ci; z80->regs.l&=255; z80->regs.f=(z80->regs.l)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void RRCr_a(Z80 *z80) { int ci=z80->regs.a&1?0x80:0; int co=z80->regs.a&1?0x10:0; z80->regs.a=(z80->regs.a>>1)+ci; z80->regs.a&=255; z80->regs.f=(z80->regs.a)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void RRCHL(Z80 *z80) { int i=MMU_rb(z80->mmu,(z80->regs.h<<8)+z80->regs.l, z80->regs.pc); int ci=i&1?0x80:0; int co=i&1?0x10:0; i=(i>>1)+ci; i&=255; MMU_wb(z80->mmu,(z80->regs.h<<8)+z80->regs.l,i); z80->regs.f=(i)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=4; }

void SLAr_b(Z80 *z80) { int co=z80->regs.b&0x80?0x10:0; z80->regs.b=(z80->regs.b<<1)&255; z80->regs.f=(z80->regs.b)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void SLAr_c(Z80 *z80) { int co=z80->regs.c&0x80?0x10:0; z80->regs.c=(z80->regs.c<<1)&255; z80->regs.f=(z80->regs.c)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void SLAr_d(Z80 *z80) { int co=z80->regs.d&0x80?0x10:0; z80->regs.d=(z80->regs.d<<1)&255; z80->regs.f=(z80->regs.d)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void SLAr_e(Z80 *z80) { int co=z80->regs.e&0x80?0x10:0; z80->regs.e=(z80->regs.e<<1)&255; z80->regs.f=(z80->regs.e)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void SLAr_h(Z80 *z80) { int co=z80->regs.h&0x80?0x10:0; z80->regs.h=(z80->regs.h<<1)&255; z80->regs.f=(z80->regs.h)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void SLAr_l(Z80 *z80) { int co=z80->regs.l&0x80?0x10:0; z80->regs.l=(z80->regs.l<<1)&255; z80->regs.f=(z80->regs.l)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void SLAr_a(Z80 *z80) { int co=z80->regs.a&0x80?0x10:0; z80->regs.a=(z80->regs.a<<1)&255; z80->regs.f=(z80->regs.a)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }

void SLLr_b(Z80 *z80) { int co=z80->regs.b&0x80?0x10:0; z80->regs.b=(z80->regs.b<<1)&255+1; z80->regs.f=(z80->regs.b)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void SLLr_c(Z80 *z80) { int co=z80->regs.c&0x80?0x10:0; z80->regs.c=(z80->regs.c<<1)&255+1; z80->regs.f=(z80->regs.c)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void SLLr_d(Z80 *z80) { int co=z80->regs.d&0x80?0x10:0; z80->regs.d=(z80->regs.d<<1)&255+1; z80->regs.f=(z80->regs.d)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void SLLr_e(Z80 *z80) { int co=z80->regs.e&0x80?0x10:0; z80->regs.e=(z80->regs.e<<1)&255+1; z80->regs.f=(z80->regs.e)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void SLLr_h(Z80 *z80) { int co=z80->regs.h&0x80?0x10:0; z80->regs.h=(z80->regs.h<<1)&255+1; z80->regs.f=(z80->regs.h)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void SLLr_l(Z80 *z80) { int co=z80->regs.l&0x80?0x10:0; z80->regs.l=(z80->regs.l<<1)&255+1; z80->regs.f=(z80->regs.l)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void SLLr_a(Z80 *z80) { int co=z80->regs.a&0x80?0x10:0; z80->regs.a=(z80->regs.a<<1)&255+1; z80->regs.f=(z80->regs.a)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }

void SRAr_b(Z80 *z80) { int ci=z80->regs.b&0x80; int co=z80->regs.b&1?0x10:0; z80->regs.b=((z80->regs.b>>1)+ci)&255; z80->regs.f=(z80->regs.b)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void SRAr_c(Z80 *z80) { int ci=z80->regs.c&0x80; int co=z80->regs.c&1?0x10:0; z80->regs.c=((z80->regs.c>>1)+ci)&255; z80->regs.f=(z80->regs.c)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void SRAr_d(Z80 *z80) { int ci=z80->regs.d&0x80; int co=z80->regs.d&1?0x10:0; z80->regs.d=((z80->regs.d>>1)+ci)&255; z80->regs.f=(z80->regs.d)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void SRAr_e(Z80 *z80) { int ci=z80->regs.e&0x80; int co=z80->regs.e&1?0x10:0; z80->regs.e=((z80->regs.e>>1)+ci)&255; z80->regs.f=(z80->regs.e)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void SRAr_h(Z80 *z80) { int ci=z80->regs.h&0x80; int co=z80->regs.h&1?0x10:0; z80->regs.h=((z80->regs.h>>1)+ci)&255; z80->regs.f=(z80->regs.h)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void SRAr_l(Z80 *z80) { int ci=z80->regs.l&0x80; int co=z80->regs.l&1?0x10:0; z80->regs.l=((z80->regs.l>>1)+ci)&255; z80->regs.f=(z80->regs.l)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void SRAr_a(Z80 *z80) { int ci=z80->regs.a&0x80; int co=z80->regs.a&1?0x10:0; z80->regs.a=((z80->regs.a>>1)+ci)&255; z80->regs.f=(z80->regs.a)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }

void SRLr_b(Z80 *z80) { int co=z80->regs.b&1?0x10:0; z80->regs.b=(z80->regs.b>>1)&255; z80->regs.f=(z80->regs.b)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void SRLr_c(Z80 *z80) { int co=z80->regs.c&1?0x10:0; z80->regs.c=(z80->regs.c>>1)&255; z80->regs.f=(z80->regs.c)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void SRLr_d(Z80 *z80) { int co=z80->regs.d&1?0x10:0; z80->regs.d=(z80->regs.d>>1)&255; z80->regs.f=(z80->regs.d)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void SRLr_e(Z80 *z80) { int co=z80->regs.e&1?0x10:0; z80->regs.e=(z80->regs.e>>1)&255; z80->regs.f=(z80->regs.e)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void SRLr_h(Z80 *z80) { int co=z80->regs.h&1?0x10:0; z80->regs.h=(z80->regs.h>>1)&255; z80->regs.f=(z80->regs.h)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void SRLr_l(Z80 *z80) { int co=z80->regs.l&1?0x10:0; z80->regs.l=(z80->regs.l>>1)&255; z80->regs.f=(z80->regs.l)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }
void SRLr_a(Z80 *z80) { int co=z80->regs.a&1?0x10:0; z80->regs.a=(z80->regs.a>>1)&255; z80->regs.f=(z80->regs.a)?0:0x80; z80->regs.f=(z80->regs.f&0xEF)+co; z80->regs.m=2; }

void CPL(Z80 *z80) { z80->regs.a ^= 255; z80->regs.f=z80->regs.a?0:0x80; z80->regs.m=1; }
void NEG(Z80 *z80) { z80->regs.a=0-z80->regs.a; z80->regs.f=(z80->regs.a<0)?0x10:0; z80->regs.a&=255; if(!z80->regs.a) z80->regs.f|=0x80; z80->regs.m=2; }

void CCF(Z80 *z80) { int ci=z80->regs.f&0x10?0:0x10; z80->regs.f=(z80->regs.f&0xEF)+ci; z80->regs.m=1; }
void SCF(Z80 *z80) { z80->regs.f|=0x10; z80->regs.m=1; }

/*--- Stack ---*/
void PUSHBC(Z80 *z80) { z80->regs.sp--; MMU_wb(z80->mmu,z80->regs.sp,z80->regs.b); z80->regs.sp--; MMU_wb(z80->mmu,z80->regs.sp,z80->regs.c); z80->regs.m=3; }
void PUSHDE(Z80 *z80) { z80->regs.sp--; MMU_wb(z80->mmu,z80->regs.sp,z80->regs.d); z80->regs.sp--; MMU_wb(z80->mmu,z80->regs.sp,z80->regs.e); z80->regs.m=3; }
void PUSHHL(Z80 *z80) { z80->regs.sp--; MMU_wb(z80->mmu,z80->regs.sp,z80->regs.h); z80->regs.sp--; MMU_wb(z80->mmu,z80->regs.sp,z80->regs.l); z80->regs.m=3; }
void PUSHAF(Z80 *z80) { z80->regs.sp--; MMU_wb(z80->mmu,z80->regs.sp,z80->regs.a); z80->regs.sp--; MMU_wb(z80->mmu,z80->regs.sp,z80->regs.f); z80->regs.m=3; }

void POPBC(Z80 *z80) { z80->regs.c=MMU_rb(z80->mmu,z80->regs.sp, z80->regs.pc); z80->regs.sp++; z80->regs.b=MMU_rb(z80->mmu,z80->regs.sp, z80->regs.pc); z80->regs.sp++; z80->regs.m=3; }
void POPDE(Z80 *z80) { z80->regs.e=MMU_rb(z80->mmu,z80->regs.sp, z80->regs.pc); z80->regs.sp++; z80->regs.d=MMU_rb(z80->mmu,z80->regs.sp, z80->regs.pc); z80->regs.sp++; z80->regs.m=3; }
void POPHL(Z80 *z80) { z80->regs.l=MMU_rb(z80->mmu,z80->regs.sp, z80->regs.pc); z80->regs.sp++; z80->regs.h=MMU_rb(z80->mmu,z80->regs.sp, z80->regs.pc); z80->regs.sp++; z80->regs.m=3; }
void POPAF(Z80 *z80) { z80->regs.f=MMU_rb(z80->mmu,z80->regs.sp, z80->regs.pc); z80->regs.sp++; z80->regs.a=MMU_rb(z80->mmu,z80->regs.sp, z80->regs.pc); z80->regs.sp++; z80->regs.m=3; }

/*--- Jump ---*/
void JPnn(Z80 *z80) { z80->regs.pc = MMU_rw(z80->mmu,z80->regs.pc, z80->regs.pc); z80->regs.m=3; }
void JPHL(Z80 *z80) { z80->regs.pc=(z80->regs.h<<8)+z80->regs.l; z80->regs.m=1; }
void JPNZnn(Z80 *z80) { z80->regs.m=3; if((z80->regs.f&0x80)==0x00) { z80->regs.pc=MMU_rw(z80->mmu,z80->regs.pc, z80->regs.pc); z80->regs.m++; } else z80->regs.pc+=2; }
void JPZnn(Z80 *z80)  { z80->regs.m=3; if((z80->regs.f&0x80)==0x80) { z80->regs.pc=MMU_rw(z80->mmu,z80->regs.pc, z80->regs.pc); z80->regs.m++; } else z80->regs.pc+=2; }
void JPNCnn(Z80 *z80) { z80->regs.m=3; if((z80->regs.f&0x10)==0x00) { z80->regs.pc=MMU_rw(z80->mmu,z80->regs.pc, z80->regs.pc); z80->regs.m++; } else z80->regs.pc+=2; }
void JPCnn(Z80 *z80)  { z80->regs.m=3; if((z80->regs.f&0x10)==0x10) { z80->regs.pc=MMU_rw(z80->mmu,z80->regs.pc, z80->regs.pc); z80->regs.m++; } else z80->regs.pc+=2; }

void JRn(Z80 *z80) { int i=MMU_rb(z80->mmu,z80->regs.pc, z80->regs.pc); if(i>127) i=-((~i+1)&255); z80->regs.pc++; z80->regs.m=2; z80->regs.pc+=i; z80->regs.m++; }
void JRNZn(Z80 *z80) { int i=MMU_rb(z80->mmu,z80->regs.pc, z80->regs.pc); if(i>127) i=-((~i+1)&255); z80->regs.pc++; z80->regs.m=2; if((z80->regs.f&0x80)==0x00) { z80->regs.pc+=i; z80->regs.m++; } }
void JRZn(Z80 *z80)  { int i=MMU_rb(z80->mmu,z80->regs.pc, z80->regs.pc); if(i>127) i=-((~i+1)&255); z80->regs.pc++; z80->regs.m=2; if((z80->regs.f&0x80)==0x80) { z80->regs.pc+=i; z80->regs.m++; } }
void JRNCn(Z80 *z80) { int i=MMU_rb(z80->mmu,z80->regs.pc, z80->regs.pc); if(i>127) i=-((~i+1)&255); z80->regs.pc++; z80->regs.m=2; if((z80->regs.f&0x10)==0x00) { z80->regs.pc+=i; z80->regs.m++; } }
void JRCn(Z80 *z80)  { int i=MMU_rb(z80->mmu,z80->regs.pc, z80->regs.pc); if(i>127) i=-((~i+1)&255); z80->regs.pc++; z80->regs.m=2; if((z80->regs.f&0x10)==0x10) { z80->regs.pc+=i; z80->regs.m++; } }

void DJNZn(Z80 *z80) { int i=MMU_rb(z80->mmu,z80->regs.pc, z80->regs.pc); if(i>127) i=-((~i+1)&255); z80->regs.pc++; z80->regs.m=2; z80->regs.b--; if(z80->regs.b) { z80->regs.pc+=i; z80->regs.m++; } }

void CALLnn(Z80 *z80) { z80->regs.sp-=2; MMU_ww(z80->mmu,z80->regs.sp,z80->regs.pc+2); z80->regs.pc=MMU_rw(z80->mmu,z80->regs.pc, z80->regs.pc); z80->regs.m=5; }
void CALLNZnn(Z80 *z80) { z80->regs.m=3; if((z80->regs.f&0x80)==0x00) { z80->regs.sp-=2; MMU_ww(z80->mmu,z80->regs.sp,z80->regs.pc+2); z80->regs.pc=MMU_rw(z80->mmu,z80->regs.pc, z80->regs.pc); z80->regs.m+=2; } else z80->regs.pc+=2; }
void CALLZnn(Z80 *z80) { z80->regs.m=3; if((z80->regs.f&0x80)==0x80) { z80->regs.sp-=2; MMU_ww(z80->mmu,z80->regs.sp,z80->regs.pc+2); z80->regs.pc=MMU_rw(z80->mmu,z80->regs.pc, z80->regs.pc); z80->regs.m+=2; } else z80->regs.pc+=2; }
void CALLNCnn(Z80 *z80) { z80->regs.m=3; if((z80->regs.f&0x10)==0x00) { z80->regs.sp-=2; MMU_ww(z80->mmu,z80->regs.sp,z80->regs.pc+2); z80->regs.pc=MMU_rw(z80->mmu,z80->regs.pc, z80->regs.pc); z80->regs.m+=2; } else z80->regs.pc+=2; }
void CALLCnn(Z80 *z80) { z80->regs.m=3; if((z80->regs.f&0x10)==0x10) { z80->regs.sp-=2; MMU_ww(z80->mmu,z80->regs.sp,z80->regs.pc+2); z80->regs.pc=MMU_rw(z80->mmu,z80->regs.pc, z80->regs.pc); z80->regs.m+=2; } else z80->regs.pc+=2; }

void RET(Z80 *z80) { z80->regs.pc=MMU_rw(z80->mmu,z80->regs.sp, z80->regs.pc); z80->regs.sp+=2; z80->regs.m=3; }
void RETI(Z80 *z80) { z80->regs.ime=1; rrs(z80); z80->regs.pc=MMU_rw(z80->mmu,z80->regs.sp, z80->regs.pc); z80->regs.sp+=2; z80->regs.m=3; }
void RETNZ(Z80 *z80) { z80->regs.m=1; if((z80->regs.f&0x80)==0x00) { z80->regs.pc=MMU_rw(z80->mmu,z80->regs.sp, z80->regs.pc); z80->regs.sp+=2; z80->regs.m+=2; } }
void RETZ(Z80 *z80) { z80->regs.m=1; if((z80->regs.f&0x80)==0x80) { z80->regs.pc=MMU_rw(z80->mmu,z80->regs.sp, z80->regs.pc); z80->regs.sp+=2; z80->regs.m+=2; } }
void RETNC(Z80 *z80) { z80->regs.m=1; if((z80->regs.f&0x10)==0x00) { z80->regs.pc=MMU_rw(z80->mmu,z80->regs.sp, z80->regs.pc); z80->regs.sp+=2; z80->regs.m+=2; } }
void RETC(Z80 *z80) { z80->regs.m=1; if((z80->regs.f&0x10)==0x10) { z80->regs.pc=MMU_rw(z80->mmu,z80->regs.sp, z80->regs.pc); z80->regs.sp+=2; z80->regs.m+=2; } }

void RST00(Z80 *z80) { rsv(z80); z80->regs.sp-=2; MMU_ww(z80->mmu,z80->regs.sp,z80->regs.pc); z80->regs.pc=0x00; z80->regs.m=3; }
void RST08(Z80 *z80) { rsv(z80); z80->regs.sp-=2; MMU_ww(z80->mmu,z80->regs.sp,z80->regs.pc); z80->regs.pc=0x08; z80->regs.m=3; }
void RST10(Z80 *z80) { rsv(z80); z80->regs.sp-=2; MMU_ww(z80->mmu,z80->regs.sp,z80->regs.pc); z80->regs.pc=0x10; z80->regs.m=3; }
void RST18(Z80 *z80) { rsv(z80); z80->regs.sp-=2; MMU_ww(z80->mmu,z80->regs.sp,z80->regs.pc); z80->regs.pc=0x18; z80->regs.m=3; }
void RST20(Z80 *z80) { rsv(z80); z80->regs.sp-=2; MMU_ww(z80->mmu,z80->regs.sp,z80->regs.pc); z80->regs.pc=0x20; z80->regs.m=3; }
void RST28(Z80 *z80) { rsv(z80); z80->regs.sp-=2; MMU_ww(z80->mmu,z80->regs.sp,z80->regs.pc); z80->regs.pc=0x28; z80->regs.m=3; }
void RST30(Z80 *z80) { rsv(z80); z80->regs.sp-=2; MMU_ww(z80->mmu,z80->regs.sp,z80->regs.pc); z80->regs.pc=0x30; z80->regs.m=3; }
void RST38(Z80 *z80) { rsv(z80); z80->regs.sp-=2; MMU_ww(z80->mmu,z80->regs.sp,z80->regs.pc); z80->regs.pc=0x38; z80->regs.m=3; }
void RST40(Z80 *z80) { rsv(z80); z80->regs.sp-=2; MMU_ww(z80->mmu,z80->regs.sp,z80->regs.pc); z80->regs.pc=0x40; z80->regs.m=3; }
void RST48(Z80 *z80) { rsv(z80); z80->regs.sp-=2; MMU_ww(z80->mmu,z80->regs.sp,z80->regs.pc); z80->regs.pc=0x48; z80->regs.m=3; }
void RST50(Z80 *z80) { rsv(z80); z80->regs.sp-=2; MMU_ww(z80->mmu,z80->regs.sp,z80->regs.pc); z80->regs.pc=0x50; z80->regs.m=3; }
void RST58(Z80 *z80) { rsv(z80); z80->regs.sp-=2; MMU_ww(z80->mmu,z80->regs.sp,z80->regs.pc); z80->regs.pc=0x58; z80->regs.m=3; }
void RST60(Z80 *z80) { rsv(z80); z80->regs.sp-=2; MMU_ww(z80->mmu,z80->regs.sp,z80->regs.pc); z80->regs.pc=0x60; z80->regs.m=3; }

void NOP(Z80 *z80) { z80->regs.m=1; }
void HALT(Z80 *z80) { z80->flags.halt=1; z80->regs.m=1; }

void DI(Z80 *z80) { z80->regs.ime=0; z80->regs.m=1; }
void EI(Z80 *z80) { z80->regs.ime=1; z80->regs.m=1; }



typedef void (*instr_ptr_t)(Z80 *);

instr_ptr_t instrMap[] =
{
    Z80_foo,
    Z80_baz,
    Z80_ADDr_e,
};
