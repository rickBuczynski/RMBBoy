//
//  MMU.c
//  RMBBoy
//
//  Created by Rick Buczynski on 2014-10-05.
//  Copyright (c) 2014 Rick Buczynski. All rights reserved.
//

@import Foundation;

#include <stdlib.h>

#import "MMU.h"
#import "GPU.h"

int MMU_bios[] = {
    0x31, 0xFE, 0xFF, 0xAF, 0x21, 0xFF, 0x9F, 0x32, 0xCB, 0x7C, 0x20, 0xFB, 0x21, 0x26, 0xFF, 0x0E,
    0x11, 0x3E, 0x80, 0x32, 0xE2, 0x0C, 0x3E, 0xF3, 0xE2, 0x32, 0x3E, 0x77, 0x77, 0x3E, 0xFC, 0xE0,
    0x47, 0x11, 0x04, 0x01, 0x21, 0x10, 0x80, 0x1A, 0xCD, 0x95, 0x00, 0xCD, 0x96, 0x00, 0x13, 0x7B,
    0xFE, 0x34, 0x20, 0xF3, 0x11, 0xD8, 0x00, 0x06, 0x08, 0x1A, 0x13, 0x22, 0x23, 0x05, 0x20, 0xF9,
    0x3E, 0x19, 0xEA, 0x10, 0x99, 0x21, 0x2F, 0x99, 0x0E, 0x0C, 0x3D, 0x28, 0x08, 0x32, 0x0D, 0x20,
    0xF9, 0x2E, 0x0F, 0x18, 0xF3, 0x67, 0x3E, 0x64, 0x57, 0xE0, 0x42, 0x3E, 0x91, 0xE0, 0x40, 0x04,
    0x1E, 0x02, 0x0E, 0x0C, 0xF0, 0x44, 0xFE, 0x90, 0x20, 0xFA, 0x0D, 0x20, 0xF7, 0x1D, 0x20, 0xF2,
    0x0E, 0x13, 0x24, 0x7C, 0x1E, 0x83, 0xFE, 0x62, 0x28, 0x06, 0x1E, 0xC1, 0xFE, 0x64, 0x20, 0x06,
    0x7B, 0xE2, 0x0C, 0x3E, 0x87, 0xF2, 0xF0, 0x42, 0x90, 0xE0, 0x42, 0x15, 0x20, 0xD2, 0x05, 0x20,
    0x4F, 0x16, 0x20, 0x18, 0xCB, 0x4F, 0x06, 0x04, 0xC5, 0xCB, 0x11, 0x17, 0xC1, 0xCB, 0x11, 0x17,
    0x05, 0x20, 0xF5, 0x22, 0x23, 0x22, 0x23, 0xC9, 0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B,
    0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E,
    0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC,
    0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E, 0x3c, 0x42, 0xB9, 0xA5, 0xB9, 0xA5, 0x42, 0x4C,
    0x21, 0x04, 0x01, 0x11, 0xA8, 0x00, 0x1A, 0x13, 0xBE, 0x20, 0xFE, 0x23, 0x7D, 0xFE, 0x34, 0x20,
    0xF5, 0x06, 0x19, 0x78, 0x86, 0x23, 0x05, 0x20, 0xFB, 0x86, 0x20, 0xFE, 0x3E, 0x01, 0xE0, 0x50
};

void MMU_reset(MMU *mmu)
{
    mmu->inBios = 1;
    mmu->wram = calloc(8192, sizeof(int));
    mmu->eram = calloc(8192, sizeof(int));
    mmu->zram = calloc(127, sizeof(int));
    
    MMU_loadRom(mmu);
}

void MMU_free(MMU *mmu)
{
    free(mmu->wram);
    free(mmu->eram);
    free(mmu->zram);
    free(mmu->rom);
}

// TODO: the whole case statment thing is really weird
// I want to redo this later with ranges
int MMU_rb(MMU *mmu, int addr, int programCounter)
{
    switch (addr & 0xF000) {
        // BIOS or ROM0
        case 0x0000:
            if (mmu->inBios) {
                if (addr < 0x0100) {
                    return MMU_bios[addr];
                } else if (programCounter == 0x0100) {
                    mmu->inBios = 0;
                }
            }
            return mmu->rom[addr];
            
        // ROM 0
        case 0x1000:
        case 0x2000:
        case 0x3000:
            return mmu->rom[addr];
            
        // ROM 1
        case 0x4000:
        case 0x5000:
        case 0x6000:
        case 0x7000:
            return mmu->rom[addr];
            
        // Graphics: VRAM (8k)
        case 0x8000:
        case 0x9000:
            return mmu->gpu->vram[addr & 0x1FFF];
         
        // External RAM (8k)
        case 0xA000:
        case 0xB000:
            return mmu->eram[addr & 0x1FFF];
            
        // Working RAM (8k)
        case 0xC000:
        case 0xD000:
            return mmu->wram[addr & 0x1FFF];
            
        // Working RAM shadow
        case 0xE000:
            return mmu->wram[addr & 0x1FFF];
            
        case 0xF000:
            switch (addr & 0x0F00) {
                // Working RAM shadow
                case 0x000: case 0x100: case 0x200: case 0x300:
                case 0x400: case 0x500: case 0x600: case 0x700:
                case 0x800: case 0x900: case 0xA00: case 0xB00:
                case 0xC00: case 0xD00:
                    return mmu->wram[addr & 0x1FFF];
                
                // Graphics: object attribute memory
                // OAM is 160 bytes, remaining bytes read as 0
                case 0xE00:
                    if (addr < 0xFEA0) {
                        return 0; // TODO: add gpu oam
                    } else {
                        return 0;
                    }
                    
                // zero-page
                case 0xF00:
                    if (addr >= 0xFF80) {
                        return mmu->zram[addr & 0x7f];
                    } else {
                        // io control handling
                        switch (addr & 0x00F0) {
                            case 0x40: case 0x50: case 0x60: case 0x70:
                                return GPU_rb(mmu->gpu, addr);
                        }
                        return 0;
                    }
            }
        default:
            return 0;
    }
}

int MMU_rw(MMU *mmu, int addr, int programCounter)
{
    return MMU_rb(mmu, addr, programCounter) + (MMU_rb(mmu, addr+1, programCounter) << 8);
}

void MMU_wb(MMU *mmu, int addr, int val)
{
    switch(addr&0xF000)
    {
        // ROM bank 0
        case 0x0000:
            if(mmu->inBios && addr<0x0100) return;
            // fall through
            
        case 0x1000:
        case 0x2000:
        case 0x3000:
            break;
            
        // ROM bank 1
        case 0x4000: case 0x5000: case 0x6000: case 0x7000:
            break;
            
        // VRAM
        case 0x8000: case 0x9000:
            mmu->gpu->vram[addr&0x1FFF] = val;
            TileSet_update(mmu->gpu->tileSet, mmu->gpu->vram, addr&0x1FFF, val);
            break;
            
        // External RAM
        case 0xA000: case 0xB000:
            mmu->eram[addr&0x1FFF] = val;
            break;
            
        // Work RAM and echo
        case 0xC000: case 0xD000: case 0xE000:
            mmu->wram[addr&0x1FFF] = val;
            break;
            
        // Everything else
        case 0xF000:
            switch(addr&0x0F00)
            {
                    // Echo RAM
                case 0x000: case 0x100: case 0x200: case 0x300:
                case 0x400: case 0x500: case 0x600: case 0x700:
                case 0x800: case 0x900: case 0xA00: case 0xB00:
                case 0xC00: case 0xD00:
                    mmu->wram[addr&0x1FFF] = val;
                    break;
                    
                // OAM
                case 0xE00:
                    //if((addr&0xFF)<0xA0) GPU._oam[addr&0xFF] = val; TODO
                    //GPU.updateoam(addr,val); TODO
                    break;
                    
                // Zeropage RAM, I/O
                case 0xF00:
                    if(addr >= 0xFF80) {
                        mmu->zram[addr&0x7F]=val;
                    }
                    else {
                        switch (addr & 0x00F0) {
                            case 0x40: case 0x50: case 0x60: case 0x70:
                                GPU_wb(mmu->gpu, addr, val);
                                break;
                        }
                    }
                    break;
            }
            break;
    }
}

void MMU_ww(MMU *mmu, int addr, int val)
{
    MMU_wb(mmu, addr, val&255);
    MMU_wb(mmu, addr+1, val>>8);
}

#include <sys/stat.h>

void MMU_loadRom(MMU *mmu)
{
    
    NSString *path = [[NSBundle mainBundle] pathForResource:@"rom" ofType:@"bin"];
    
    NSData *myData = [NSData dataWithContentsOfFile:path];
    NSLog(@"%@", myData);
    
    const char *cPath = [path cStringUsingEncoding:[NSString defaultCStringEncoding]];
    struct stat st;
    stat(cPath, &st);
    unsigned long size = (unsigned long)st.st_size;
    
    mmu->rom = malloc(size*sizeof(unsigned char));
    [myData getBytes:mmu->rom length:size];
}
