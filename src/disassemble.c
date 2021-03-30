/*******************************  COPYRIGHT  ********************************/
/*
 *  Author? "Gregory N. Leonhardt"
 *  License? "CC BY-NC 2.0"
 *           "https://creativecommons.org/licenses/by-nc/2.0/"
 *
 ****************************************************************************/

/******************************** JAVADOC ***********************************/
/**
 *  What is the reason for this file to exist/
 *
 ****************************************************************************/

/****************************************************************************
 *  Compiler directives
 ****************************************************************************/


/****************************************************************************
 * System Function
 ****************************************************************************/

                                //*******************************************
#include <stdbool.h>            //  TRUE, FALSE, etc.
#include <stdint.h>             //  Alternative storage types
#include <stdlib.h>             //  ANSI standard library.
#include <unistd.h>             //  UNIX standard library.
#include <stdio.h>              //  Standard I/O definitions
                                //*******************************************
#include <string.h>
                                //*******************************************


/****************************************************************************
 * Application
 ****************************************************************************/

                                //*******************************************
#include "global.h"             //  Global definitions
#include "memory.h"             //  Memory management and access
#include "registers.h"          //  All things CPU registers.
                                //*******************************************

/****************************************************************************
 * Enumerations
 ****************************************************************************/

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

/****************************************************************************
 * Definitions
 ****************************************************************************/

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

/****************************************************************************
 * Private Structures
 ****************************************************************************/

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

/****************************************************************************
 * Storage Allocation
 ****************************************************************************/

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

/****************************************************************************
 *  Storage Allocation
 ****************************************************************************/

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

/****************************************************************************
 * Private Functions
 ****************************************************************************/


/****************************************************************************
 * MAIN
 ****************************************************************************/


/****************************************************************************/
/**
 *  Disassemble the current Op-Code.
 *
 *  @parm   pc                      Program Counter
 *  @parm   op_code                 The operation code of the current instruction.
 *
 *  @return                         No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
disassemble(
    uint16_t                    pc,
    uint8_t                     op_code
    )
{
    /**
     *  @param  mnemonic           Instruction mnemonic                     */
    char                        mnemonic[ 32 ];
    /**
     *  @param  inst_len            Instruction length                      */
    int                         inst_len;

    //  Clean the mnemonic buffer
    memset( mnemonic, 0x00, sizeof( mnemonic ) );

    //  Base Intel 8080 or Z80 instruction set ?
    if( EIS == EIS_BASE )
    {
        //  YES:    Op-Code decode
        switch( op_code )
        {
        //========================================================================
            case    0x00:
                inst_len = 1; strcat( mnemonic, "NOP            " ); break;
            case    0x01:
                inst_len = 3; strcat( mnemonic, "LD     BC, nn  " ); break;
            case    0x02:
                inst_len = 1; strcat( mnemonic, "LD     (BC), A " ); break;
            case    0x03:
                inst_len = 1; strcat( mnemonic, "INC    BC      " ); break;
            case    0x04:
                inst_len = 1; strcat( mnemonic, "INC    B       " ); break;
            case    0x05:
                inst_len = 1; strcat( mnemonic, "DEC    B       " ); break;
            case    0x06:
                inst_len = 2; strcat( mnemonic, "LD     B, n    " ); break;
            case    0x07:
                inst_len = 1; strcat( mnemonic, "RLCA           " ); break;
            case    0x08:
                inst_len = 1; strcat( mnemonic, "EX     AF, AF' " ); break;
            case    0x09:
                inst_len = 1; strcat( mnemonic, "ADD    HL, BC  " ); break;
            case    0x0A:
                inst_len = 1; strcat( mnemonic, "LD     A, (BC) " ); break;
            case    0x0B:
                inst_len = 1; strcat( mnemonic, "DEC    BC      " ); break;
            case    0x0C:
                inst_len = 1; strcat( mnemonic, "INC    C       " ); break;
            case    0x0D:
                inst_len = 1; strcat( mnemonic, "DEC    C       " ); break;
            case    0x0E:
                inst_len = 2; strcat( mnemonic, "LD     C, n    " ); break;
            case    0x0F:
                inst_len = 1; strcat( mnemonic, "RRCA           " ); break;
        //========================================================================
            case    0x10:
                inst_len = 2; strcat( mnemonic, "DJNZ   e       " ); break;
            case    0x11:
                inst_len = 3; strcat( mnemonic, "LD     DE, nn  " ); break;
            case    0x12:
                inst_len = 1; strcat( mnemonic, "LD     (DE), A " ); break;
            case    0x13:
                inst_len = 1; strcat( mnemonic, "INC    DE      " ); break;
            case    0x14:
                inst_len = 1; strcat( mnemonic, "INC    D       " ); break;
            case    0x15:
                inst_len = 1; strcat( mnemonic, "DEC    D       " ); break;
            case    0x16:
                inst_len = 2; strcat( mnemonic, "LD     D, n    " ); break;
            case    0x17:
                inst_len = 1; strcat( mnemonic, "RLA            " ); break;
            case    0x18:
                inst_len = 2; strcat( mnemonic, "JR     e       " ); break;
            case    0x19:
                inst_len = 1; strcat( mnemonic, "ADD    HL, DE  " ); break;
            case    0x1A:
                inst_len = 1; strcat( mnemonic, "LD     A, (DE) " ); break;
            case    0x1B:
                inst_len = 1; strcat( mnemonic, "DEC    DE      " ); break;
            case    0x1C:
                inst_len = 1; strcat( mnemonic, "INC    E       " ); break;
            case    0x1D:
                inst_len = 1; strcat( mnemonic, "DEC    E       " ); break;
            case    0x1E:
                inst_len = 2; strcat( mnemonic, "LD     E, n    " ); break;
            case    0x1F:
                inst_len = 1; strcat( mnemonic, "RRA            " ); break;
        //========================================================================
            case    0x20:
                inst_len = 2; strcat( mnemonic, "JR     NZ, e   " ); break;
            case    0x21:
                inst_len = 3; strcat( mnemonic, "LD     HL, nn  " ); break;
            case    0x22:
                inst_len = 3; strcat( mnemonic, "LD     (nn), HL" ); break;
            case    0x23:
                inst_len = 1; strcat( mnemonic, "INC    HL      " ); break;
            case    0x24:
                inst_len = 1; strcat( mnemonic, "INC    H       " ); break;
            case    0x25:
                inst_len = 1; strcat( mnemonic, "DEC    H       " ); break;
            case    0x26:
                inst_len = 2; strcat( mnemonic, "LD     H, n    " ); break;
            case    0x27:
                inst_len = 1; strcat( mnemonic, "DAA            " ); break;
            case    0x28:
                inst_len = 2; strcat( mnemonic, "JR     Z, e    " ); break;
            case    0x29:
                inst_len = 1; strcat( mnemonic, "ADD    HL, HL  " ); break;
            case    0x2A:
                inst_len = 3; strcat( mnemonic, "LD     HL, (nn)" ); break;
            case    0x2B:
                inst_len = 1; strcat( mnemonic, "DEC    HL      " ); break;
            case    0x2C:
                inst_len = 1; strcat( mnemonic, "INC    L       " ); break;
            case    0x2D:
                inst_len = 1; strcat( mnemonic, "DEC    L       " ); break;
            case    0x2E:
                inst_len = 2; strcat( mnemonic, "LD     L, n    " ); break;
            case    0x2F:
                inst_len = 1; strcat( mnemonic, "CPL            " ); break;
        //========================================================================
            case    0x30:
                inst_len = 2; strcat( mnemonic, "JR     NC, e   " ); break;
            case    0x31:
                inst_len = 3; strcat( mnemonic, "LD     SP, nn  " ); break;
            case    0x32:
                inst_len = 3; strcat( mnemonic, "LD     (nn), A " ); break;
            case    0x33:
                inst_len = 1; strcat( mnemonic, "INC    SP      " ); break;
            case    0x34:
                inst_len = 1; strcat( mnemonic, "INC    (HL)    " ); break;
            case    0x35:
                inst_len = 1; strcat( mnemonic, "DEC    (HL)    " ); break;
            case    0x36:
                inst_len = 2; strcat( mnemonic, "LD     (HL), n " ); break;
            case    0x37:
                inst_len = 1; strcat( mnemonic, "SCF            " ); break;
            case    0x38:
                inst_len = 2; strcat( mnemonic, "JR     C, e    " ); break;
            case    0x39:
                inst_len = 1; strcat( mnemonic, "ADD    HL, SP  " ); break;
            case    0x3A:
                inst_len = 3; strcat( mnemonic, "LD     A, (nn) " ); break;
            case    0x3B:
                inst_len = 1; strcat( mnemonic, "DEC    SP      " ); break;
            case    0x3C:
                inst_len = 1; strcat( mnemonic, "INC    A       " ); break;
            case    0x3D:
                inst_len = 1; strcat( mnemonic, "DEC    A       " ); break;
            case    0x3E:
                inst_len = 2; strcat( mnemonic, "LD     A, n    " ); break;
            case    0x3F:
                inst_len = 1; strcat( mnemonic, "CFF            " ); break;
        //========================================================================
            case    0x40:
                inst_len = 1; strcat( mnemonic, "LD     B, B    " ); break;
            case    0x41:
                inst_len = 1; strcat( mnemonic, "LD     B, C    " ); break;
            case    0x42:
                inst_len = 1; strcat( mnemonic, "LD     B, D    " ); break;
            case    0x43:
                inst_len = 1; strcat( mnemonic, "LD     B, E    " ); break;
            case    0x44:
                inst_len = 1; strcat( mnemonic, "LD     B, H    " ); break;
            case    0x45:
                inst_len = 1; strcat( mnemonic, "LD     B, L    " ); break;
            case    0x46:
                inst_len = 1; strcat( mnemonic, "LD     B, (HL) " ); break;
            case    0x47:
                inst_len = 1; strcat( mnemonic, "LD     B, A    " ); break;
            case    0x48:
                inst_len = 1; strcat( mnemonic, "LD     C, B    " ); break;
            case    0x49:
                inst_len = 1; strcat( mnemonic, "LD     C, C    " ); break;
            case    0x4A:
                inst_len = 1; strcat( mnemonic, "LD     C, D    " ); break;
            case    0x4B:
                inst_len = 1; strcat( mnemonic, "LD     C, E    " ); break;
            case    0x4C:
                inst_len = 1; strcat( mnemonic, "LD     C, H    " ); break;
            case    0x4D:
                inst_len = 1; strcat( mnemonic, "LD     C, L    " ); break;
            case    0x4E:
                inst_len = 1; strcat( mnemonic, "LD     C, (HL) " ); break;
            case    0x4F:
                inst_len = 1; strcat( mnemonic, "LD     C, A    " ); break;
        //========================================================================
            case    0x50:
                inst_len = 1; strcat( mnemonic, "LD     D, B    " ); break;
            case    0x51:
                inst_len = 1; strcat( mnemonic, "LD     D, C    " ); break;
            case    0x52:
                inst_len = 1; strcat( mnemonic, "LD     D, D    " ); break;
            case    0x53:
                inst_len = 1; strcat( mnemonic, "LD     D, E    " ); break;
            case    0x54:
                inst_len = 1; strcat( mnemonic, "LD     D, H    " ); break;
            case    0x55:
                inst_len = 1; strcat( mnemonic, "LD     D, L    " ); break;
            case    0x56:
                inst_len = 1; strcat( mnemonic, "LD     D, (HL) " ); break;
            case    0x57:
                inst_len = 1; strcat( mnemonic, "LD     D, A    " ); break;
            case    0x58:
                inst_len = 1; strcat( mnemonic, "LD     E, B    " ); break;
            case    0x59:
                inst_len = 1; strcat( mnemonic, "LD     E, C    " ); break;
            case    0x5A:
                inst_len = 1; strcat( mnemonic, "LD     E, D    " ); break;
            case    0x5B:
                inst_len = 1; strcat( mnemonic, "LD     E, E    " ); break;
            case    0x5C:
                inst_len = 1; strcat( mnemonic, "LD     E, H    " ); break;
            case    0x5D:
                inst_len = 1; strcat( mnemonic, "LD     E, L    " ); break;
            case    0x5E:
                inst_len = 1; strcat( mnemonic, "LD     E, (HL) " ); break;
            case    0x5F:
                inst_len = 1; strcat( mnemonic, "LD     E, A    " ); break;
        //========================================================================
            case    0x60:
                inst_len = 1; strcat( mnemonic, "LD     H, B    " ); break;
            case    0x61:
                inst_len = 1; strcat( mnemonic, "LD     H, C    " ); break;
            case    0x62:
                inst_len = 1; strcat( mnemonic, "LD     H, D    " ); break;
            case    0x63:
                inst_len = 1; strcat( mnemonic, "LD     H, E    " ); break;
            case    0x64:
                inst_len = 1; strcat( mnemonic, "LD     H, H    " ); break;
            case    0x65:
                inst_len = 1; strcat( mnemonic, "LD     H, L    " ); break;
            case    0x66:
                inst_len = 1; strcat( mnemonic, "LD     H, (HL) " ); break;
            case    0x67:
                inst_len = 1; strcat( mnemonic, "LD     H, A    " ); break;
            case    0x68:
                inst_len = 1; strcat( mnemonic, "LD     L, B    " ); break;
            case    0x69:
                inst_len = 1; strcat( mnemonic, "LD     L, C    " ); break;
            case    0x6A:
                inst_len = 1; strcat( mnemonic, "LD     L, D    " ); break;
            case    0x6B:
                inst_len = 1; strcat( mnemonic, "LD     L, E    " ); break;
            case    0x6C:
                inst_len = 1; strcat( mnemonic, "LD     L, H    " ); break;
            case    0x6D:
                inst_len = 1; strcat( mnemonic, "LD     L, L    " ); break;
            case    0x6E:
                inst_len = 1; strcat( mnemonic, "LD     L, (HL) " ); break;
            case    0x6F:
                inst_len = 1; strcat( mnemonic, "LD     L, A    " ); break;
        //========================================================================
            case    0x70:
                inst_len = 1; strcat( mnemonic, "LD     (HL), B " ); break;
            case    0x71:
                inst_len = 1; strcat( mnemonic, "LD     (HL), C " ); break;
            case    0x72:
                inst_len = 1; strcat( mnemonic, "LD     (HL), D " ); break;
            case    0x73:
                inst_len = 1; strcat( mnemonic, "LD     (HL), E " ); break;
            case    0x74:
                inst_len = 1; strcat( mnemonic, "LD     (HL), H " ); break;
            case    0x75:
                inst_len = 1; strcat( mnemonic, "LD     (HL), L " ); break;
            case    0x76:
                inst_len = 1; strcat( mnemonic, "HALT           " ); break;
            case    0x77:
                inst_len = 1; strcat( mnemonic, "LD     (HL), A " ); break;
            case    0x78:
                inst_len = 1; strcat( mnemonic, "LD     A, B    " ); break;
            case    0x79:
                inst_len = 1; strcat( mnemonic, "LD     A, C    " ); break;
            case    0x7A:
                inst_len = 1; strcat( mnemonic, "LD     A, D    " ); break;
            case    0x7B:
                inst_len = 1; strcat( mnemonic, "LD     A, E    " ); break;
            case    0x7C:
                inst_len = 1; strcat( mnemonic, "LD     A, H    " ); break;
            case    0x7D:
                inst_len = 1; strcat( mnemonic, "LD     A, L    " ); break;
            case    0x7E:
                inst_len = 1; strcat( mnemonic, "LD     A, (HL) " ); break;
            case    0x7F:
                inst_len = 1; strcat( mnemonic, "LD     A, A    " ); break;
        //========================================================================
            case    0x80:
                inst_len = 1; strcat( mnemonic, "ADD    A, B    " ); break;
            case    0x81:
                inst_len = 1; strcat( mnemonic, "ADD    A, C    " ); break;
            case    0x82:
                inst_len = 1; strcat( mnemonic, "ADD    A, D    " ); break;
            case    0x83:
                inst_len = 1; strcat( mnemonic, "ADD    A, E    " ); break;
            case    0x84:
                inst_len = 1; strcat( mnemonic, "ADD    A, H    " ); break;
            case    0x85:
                inst_len = 1; strcat( mnemonic, "ADD    A, L    " ); break;
            case    0x86:
                inst_len = 1; strcat( mnemonic, "ADD    A, (HL) " ); break;
            case    0x87:
                inst_len = 1; strcat( mnemonic, "ADD    A, A    " ); break;
            case    0x88:
                inst_len = 1; strcat( mnemonic, "ADC    A, B    " ); break;
            case    0x89:
                inst_len = 1; strcat( mnemonic, "ADC    A, C    " ); break;
            case    0x8A:
                inst_len = 1; strcat( mnemonic, "ADC    A, D    " ); break;
            case    0x8B:
                inst_len = 1; strcat( mnemonic, "ADC    A, E    " ); break;
            case    0x8C:
                inst_len = 1; strcat( mnemonic, "ADC    A, H    " ); break;
            case    0x8D:
                inst_len = 1; strcat( mnemonic, "ADC    A, L    " ); break;
            case    0x8E:
                inst_len = 1; strcat( mnemonic, "ADC    A, (HL) " ); break;
            case    0x8F:
                inst_len = 1; strcat( mnemonic, "ADC    A, A    " ); break;
        //========================================================================
            case    0x90:
                inst_len = 1; strcat( mnemonic, "SUB    A, B    " ); break;
            case    0x91:
                inst_len = 1; strcat( mnemonic, "SUB    A, C    " ); break;
            case    0x92:
                inst_len = 1; strcat( mnemonic, "SUB    A, D    " ); break;
            case    0x93:
                inst_len = 1; strcat( mnemonic, "SUB    A, E    " ); break;
            case    0x94:
                inst_len = 1; strcat( mnemonic, "SUB    A, H    " ); break;
            case    0x95:
                inst_len = 1; strcat( mnemonic, "SUB    A, L    " ); break;
            case    0x96:
                inst_len = 1; strcat( mnemonic, "SUB    A, (HL) " ); break;
            case    0x97:
                inst_len = 1; strcat( mnemonic, "SUB    A, A    " ); break;
            case    0x98:
                inst_len = 1; strcat( mnemonic, "SBC    A, B    " ); break;
            case    0x99:
                inst_len = 1; strcat( mnemonic, "SBC    A, C    " ); break;
            case    0x9A:
                inst_len = 1; strcat( mnemonic, "SBC    A, D    " ); break;
            case    0x9B:
                inst_len = 1; strcat( mnemonic, "SBC    A, E    " ); break;
            case    0x9C:
                inst_len = 1; strcat( mnemonic, "SBC    A, H    " ); break;
            case    0x9D:
                inst_len = 1; strcat( mnemonic, "SBC    A, L    " ); break;
            case    0x9E:
                inst_len = 1; strcat( mnemonic, "SBC    A, (HL) " ); break;
            case    0x9F:
                inst_len = 1; strcat( mnemonic, "SBC    A, A    " ); break;
        //========================================================================
            case    0xA0:
                inst_len = 1; strcat( mnemonic, "AND    B       " ); break;
            case    0xA1:
                inst_len = 1; strcat( mnemonic, "AND    C       " ); break;
            case    0xA2:
                inst_len = 1; strcat( mnemonic, "AND    D       " ); break;
            case    0xA3:
                inst_len = 1; strcat( mnemonic, "AND    E       " ); break;
            case    0xA4:
                inst_len = 1; strcat( mnemonic, "AND    H       " ); break;
            case    0xA5:
                inst_len = 1; strcat( mnemonic, "AND    L       " ); break;
            case    0xA6:
                inst_len = 1; strcat( mnemonic, "AND    (HL)    " ); break;
            case    0xA7:
                inst_len = 1; strcat( mnemonic, "AND    A       " ); break;
            case    0xA8:
                inst_len = 1; strcat( mnemonic, "XOR    B       " ); break;
            case    0xA9:
                inst_len = 1; strcat( mnemonic, "XOR    C       " ); break;
            case    0xAA:
                inst_len = 1; strcat( mnemonic, "XOR    D       " ); break;
            case    0xAB:
                inst_len = 1; strcat( mnemonic, "XOR    E       " ); break;
            case    0xAC:
                inst_len = 1; strcat( mnemonic, "XOR    H       " ); break;
            case    0xAD:
                inst_len = 1; strcat( mnemonic, "XOR    L       " ); break;
            case    0xAE:
                inst_len = 1; strcat( mnemonic, "XOR    (HL)    " ); break;
            case    0xAF:
                inst_len = 1; strcat( mnemonic, "XOR    A       " ); break;
        //========================================================================
            case    0xB0:
                inst_len = 1; strcat( mnemonic, "OR     B       " ); break;
            case    0xB1:
                inst_len = 1; strcat( mnemonic, "OR     C       " ); break;
            case    0xB2:
                inst_len = 1; strcat( mnemonic, "OR     D       " ); break;
            case    0xB3:
                inst_len = 1; strcat( mnemonic, "OR     E       " ); break;
            case    0xB4:
                inst_len = 1; strcat( mnemonic, "OR     H       " ); break;
            case    0xB5:
                inst_len = 1; strcat( mnemonic, "OR     L       " ); break;
            case    0xB6:
                inst_len = 1; strcat( mnemonic, "OR     (HL)    " ); break;
            case    0xB7:
                inst_len = 1; strcat( mnemonic, "OR     A       " ); break;
            case    0xB8:
                inst_len = 1; strcat( mnemonic, "CP     B       " ); break;
            case    0xB9:
                inst_len = 1; strcat( mnemonic, "CP     C       " ); break;
            case    0xBA:
                inst_len = 1; strcat( mnemonic, "CP     D       " ); break;
            case    0xBB:
                inst_len = 1; strcat( mnemonic, "CP     E       " ); break;
            case    0xBC:
                inst_len = 1; strcat( mnemonic, "CP     H       " ); break;
            case    0xBD:
                inst_len = 1; strcat( mnemonic, "CP     L       " ); break;
            case    0xBE:
                inst_len = 1; strcat( mnemonic, "CP     (HL)    " ); break;
            case    0xBF:
                inst_len = 1; strcat( mnemonic, "CP     A       " ); break;
        //========================================================================
            case    0xC0:
                inst_len = 1; strcat( mnemonic, "RET    NZ      " ); break;
            case    0xC1:
                inst_len = 1; strcat( mnemonic, "POP    BC      " ); break;
            case    0xC2:
                inst_len = 3; strcat( mnemonic, "JP     NZ, nn  " ); break;
            case    0xC3:
                inst_len = 3; strcat( mnemonic, "JP     nn      " ); break;
            case    0xC4:
                inst_len = 3; strcat( mnemonic, "CALL   NZ, nn  " ); break;
            case    0xC5:
                inst_len = 1; strcat( mnemonic, "PUSH   BC      " ); break;
            case    0xC6:
                inst_len = 2; strcat( mnemonic, "ADD    A, n    " ); break;
            case    0xC7:
                inst_len = 1; strcat( mnemonic, "RST    0       " ); break;
            case    0xC8:
                inst_len = 1; strcat( mnemonic, "RET    Z       " ); break;
            case    0xC9:
                inst_len = 1; strcat( mnemonic, "RET            " ); break;
            case    0xCA:
                inst_len = 3; strcat( mnemonic, "JP     Z, nn   " ); break;
            case    0xCB:
                inst_len = 1; strcat( mnemonic, "               " ); break;
            case    0xCC:
                inst_len = 3; strcat( mnemonic, "CALL   Z, nn   " ); break;
            case    0xCD:
                inst_len = 3; strcat( mnemonic, "CALL   nn      " ); break;
            case    0xCE:
                inst_len = 2; strcat( mnemonic, "ADD    A, n    " ); break;
            case    0xCF:
                inst_len = 1; strcat( mnemonic, "RST    1       " ); break;
        //========================================================================
            case    0xD0:
                inst_len = 1; strcat( mnemonic, "RET    NC      " ); break;
            case    0xD1:
                inst_len = 1; strcat( mnemonic, "POP    DE      " ); break;
            case    0xD2:
                inst_len = 3; strcat( mnemonic, "JP     NC, nn  " ); break;
            case    0xD3:
                inst_len = 2; strcat( mnemonic, "OUT    (n), A  " ); break;
            case    0xD4:
                inst_len = 3; strcat( mnemonic, "CALL   NC, nn  " ); break;
            case    0xD5:
                inst_len = 1; strcat( mnemonic, "PUSH   DE      " ); break;
            case    0xD6:
                inst_len = 2; strcat( mnemonic, "SUB    n       " ); break;
            case    0xD7:
                inst_len = 1; strcat( mnemonic, "RST    2       " ); break;
            case    0xD8:
                inst_len = 1; strcat( mnemonic, "RET    C       " ); break;
            case    0xD9:
                inst_len = 1; strcat( mnemonic, "EXX            " ); break;
            case    0xDA:
                inst_len = 3; strcat( mnemonic, "JP     C, nn   " ); break;
            case    0xDB:
                inst_len = 2; strcat( mnemonic, "IN     A, (n)  " ); break;
            case    0xDC:
                inst_len = 3; strcat( mnemonic, "CALL   C, nn   " ); break;
            case    0xDD:
                inst_len = 1; strcat( mnemonic, "               " ); break;
            case    0xDE:
                inst_len = 2; strcat( mnemonic, "SBC    n       " ); break;
            case    0xDF:
                inst_len = 1; strcat( mnemonic, "RST    3       " ); break;
        //========================================================================
            case    0xE0:
                inst_len = 1; strcat( mnemonic, "RET    PO      " ); break;
            case    0xE1:
                inst_len = 1; strcat( mnemonic, "POP    HL      " ); break;
            case    0xE2:
                inst_len = 3; strcat( mnemonic, "JP     PO, nn  " ); break;
            case    0xE3:
                inst_len = 1; strcat( mnemonic, "EX     (SP), HL" ); break;
            case    0xE4:
                inst_len = 3; strcat( mnemonic, "CALL   PO, nn  " ); break;
            case    0xE5:
                inst_len = 1; strcat( mnemonic, "PUSH   HL      " ); break;
            case    0xE6:
                inst_len = 2; strcat( mnemonic, "AND    n       " ); break;
            case    0xE7:
                inst_len = 1; strcat( mnemonic, "RST    4       " ); break;
            case    0xE8:
                inst_len = 1; strcat( mnemonic, "RET    PE      " ); break;
            case    0xE9:
                inst_len = 1; strcat( mnemonic, "JP     (HL)    " ); break;
            case    0xEA:
                inst_len = 3; strcat( mnemonic, "JP     PE, nn  " ); break;
            case    0xEB:
                inst_len = 1; strcat( mnemonic, "EX     DE, HL  " ); break;
            case    0xEC:
                inst_len = 3; strcat( mnemonic, "CALL   PE, nn  " ); break;
            case    0xED:
                inst_len = 0; strcat( mnemonic, "               " ); break;
            case    0xEE:
                inst_len = 2; strcat( mnemonic, "CP     n       " ); break;
            case    0xEF:
                inst_len = 1; strcat( mnemonic, "RST    5       " ); break;
        //========================================================================
            case    0xF0:
                inst_len = 1; strcat( mnemonic, "RET    P       " ); break;
            case    0xF1:
                inst_len = 1; strcat( mnemonic, "POP    AF      " ); break;
            case    0xF2:
                inst_len = 3; strcat( mnemonic, "JP     P, nn   " ); break;
            case    0xF3:
                inst_len = 1; strcat( mnemonic, "DI             " ); break;
            case    0xF4:
                inst_len = 3; strcat( mnemonic, "CALL   P, nn   " ); break;
            case    0xF5:
                inst_len = 1; strcat( mnemonic, "PUSH   AF      " ); break;
            case    0xF6:
                inst_len = 2; strcat( mnemonic, "OR     n       " ); break;
            case    0xF7:
                inst_len = 1; strcat( mnemonic, "RST    6       " ); break;
            case    0xF8:
                inst_len = 1; strcat( mnemonic, "RET    M       " ); break;
            case    0xF9:
                inst_len = 1; strcat( mnemonic, "LD     SP, HL  " ); break;
            case    0xFA:
                inst_len = 3; strcat( mnemonic, "JP     M, nn   " ); break;
            case    0xFB:
                inst_len = 1; strcat( mnemonic, "EI             " ); break;
            case    0xFC:
                inst_len = 3; strcat( mnemonic, "CALL   M, nn   " ); break;
            case    0xFD:
                inst_len = 0; strcat( mnemonic, "               " ); break;
            case    0xFE:
                inst_len = 2; strcat( mnemonic, "CP     n       " ); break;
            case    0xFF:
                inst_len = 1; strcat( mnemonic, "RST    7       " ); break;
        //========================================================================
        }
    }

    //  Z80 Extended Instruction Set 'ED' ?
    else
    if( EIS == EIS_ED )
    {
        //  YES:    Op-Code decode
        switch( op_code )
        {
        //========================================================================
            case    0x00:
            case    0x01:
            case    0x02:
            case    0x03:
            case    0x04:
            case    0x05:
            case    0x06:
            case    0x07:
            case    0x08:
            case    0x09:
            case    0x0A:
            case    0x0B:
            case    0x0C:
            case    0x0D:
            case    0x0E:
            case    0x0F:
                inst_len = 0; strcat( mnemonic, "               " ); break;
        //========================================================================
            case    0x10:
            case    0x11:
            case    0x12:
            case    0x13:
            case    0x14:
            case    0x15:
            case    0x16:
            case    0x17:
            case    0x18:
            case    0x19:
            case    0x1A:
            case    0x1B:
            case    0x1C:
            case    0x1D:
            case    0x1E:
            case    0x1F:
                inst_len = 0; strcat( mnemonic, "               " ); break;
        //========================================================================
            case    0x20:
            case    0x21:
            case    0x22:
            case    0x23:
            case    0x24:
            case    0x25:
            case    0x26:
            case    0x27:
            case    0x28:
            case    0x29:
            case    0x2A:
            case    0x2B:
            case    0x2C:
            case    0x2D:
            case    0x2E:
            case    0x2F:
                inst_len = 0; strcat( mnemonic, "               " ); break;
        //========================================================================
            case    0x30:
            case    0x31:
            case    0x32:
            case    0x33:
            case    0x34:
            case    0x35:
            case    0x36:
            case    0x37:
            case    0x38:
            case    0x39:
            case    0x3A:
            case    0x3B:
            case    0x3C:
            case    0x3D:
            case    0x3E:
            case    0x3F:
                inst_len = 0; strcat( mnemonic, "               " ); break;
        //========================================================================
            case    0x40:
                inst_len = 0; strcat( mnemonic, "               " ); break;
            case    0x41:
                inst_len = 0; strcat( mnemonic, "               " ); break;
            case    0x42:
                inst_len = 2; strcat( mnemonic, "SBC    HL, BC  " ); break;
            case    0x43:
                inst_len = 4; strcat( mnemonic, "LD     (nn), BC" ); break;
            case    0x44:
                inst_len = 2; strcat( mnemonic, "NEG            " ); break;
            case    0x45:
                inst_len = 2; strcat( mnemonic, "RETN           " ); break;
            case    0x46:
                inst_len = 2; strcat( mnemonic, "IM     0       " ); break;
            case    0x47:
                inst_len = 2; strcat( mnemonic, "LD     I, A    " ); break;
            case    0x48:
                inst_len = 0; strcat( mnemonic, "               " ); break;
            case    0x49:
                inst_len = 0; strcat( mnemonic, "               " ); break;
            case    0x4A:
                inst_len = 2; strcat( mnemonic, "ADD    HL, BC  " ); break;
            case    0x4B:
                inst_len = 4; strcat( mnemonic, "LD     BC, (nn)" ); break;
            case    0x4C:
                inst_len = 0; strcat( mnemonic, "               " ); break;
            case    0x4D:
                inst_len = 2; strcat( mnemonic, "RETI           " ); break;
            case    0x4E:
                inst_len = 0; strcat( mnemonic, "               " ); break;
            case    0x4F:
                inst_len = 2; strcat( mnemonic, "LD     R, A    " ); break;
        //========================================================================
            case    0x50:
            case    0x51:
                inst_len = 0; strcat( mnemonic, "               " ); break;
            case    0x52:
                inst_len = 2; strcat( mnemonic, "SBC    HL, DE  " ); break;
            case    0x53:
                inst_len = 4; strcat( mnemonic, "LD     (nn), DE" ); break;
            case    0x54:
            case    0x55:
                inst_len = 0; strcat( mnemonic, "               " ); break;
            case    0x56:
                inst_len = 2; strcat( mnemonic, "IM     1       " ); break;
            case    0x57:
                inst_len = 2; strcat( mnemonic, "LD     A, I    " ); break;
            case    0x58:
            case    0x59:
                inst_len = 0; strcat( mnemonic, "               " ); break;
            case    0x5A:
                inst_len = 2; strcat( mnemonic, "ADD    HL, DE  " ); break;
            case    0x5B:
                inst_len = 4; strcat( mnemonic, "LD     DE, (nn)" ); break;
            case    0x5C:
            case    0x5D:
                inst_len = 0; strcat( mnemonic, "               " ); break;
            case    0x5E:
                inst_len = 2; strcat( mnemonic, "IM     2       " ); break;
            case    0x5F:
                inst_len = 2; strcat( mnemonic, "LD     A, R    " ); break;
        //========================================================================
            case    0x60:
            case    0x61:
                inst_len = 0; strcat( mnemonic, "               " ); break;
            case    0x62:
                inst_len = 2; strcat( mnemonic, "SBC    HL, HL  " ); break;
            case    0x63:
                inst_len = 4; strcat( mnemonic, "LD     (nn), HL" ); break;
            case    0x64:
            case    0x65:
            case    0x66:
                inst_len = 0; strcat( mnemonic, "               " ); break;
            case    0x67:
                inst_len = 2; strcat( mnemonic, "RRD            " ); break;
            case    0x68:
            case    0x69:
                inst_len = 0; strcat( mnemonic, "               " ); break;
            case    0x6A:
                inst_len = 2; strcat( mnemonic, "ADD    HL, HL  " ); break;
            case    0x6B:
                inst_len = 4; strcat( mnemonic, "LD     HL, (nn)" ); break;
            case    0x6C:
            case    0x6D:
            case    0x6E:
            case    0x6F:
                inst_len = 0; strcat( mnemonic, "               " ); break;
        //========================================================================
            case    0x70:
            case    0x71:
                inst_len = 0; strcat( mnemonic, "               " ); break;
            case    0x72:
                inst_len = 2; strcat( mnemonic, "SBC    HL, SP  " ); break;
            case    0x73:
                inst_len = 4; strcat( mnemonic, "LD     (nn), SP" ); break;
            case    0x74:
            case    0x75:
            case    0x76:
            case    0x77:
            case    0x78:
            case    0x79:
                inst_len = 0; strcat( mnemonic, "               " ); break;
            case    0x7A:
                inst_len = 2; strcat( mnemonic, "ADD    HL, SP  " ); break;
            case    0x7B:
                inst_len = 4; strcat( mnemonic, "LD     SP, (nn)" ); break;
            case    0x7C:
            case    0x7D:
            case    0x7E:
            case    0x7F:
                inst_len = 0; strcat( mnemonic, "               " ); break;
        //========================================================================
            case    0x80:
            case    0x81:
            case    0x82:
            case    0x83:
            case    0x84:
            case    0x85:
            case    0x86:
            case    0x87:
            case    0x88:
            case    0x89:
            case    0x8A:
            case    0x8B:
            case    0x8C:
            case    0x8D:
            case    0x8E:
            case    0x8F:
                inst_len = 0; strcat( mnemonic, "               " ); break;
        //========================================================================
            case    0x90:
            case    0x91:
            case    0x92:
            case    0x93:
            case    0x94:
            case    0x95:
            case    0x96:
            case    0x97:
            case    0x98:
            case    0x99:
            case    0x9A:
            case    0x9B:
            case    0x9C:
            case    0x9D:
            case    0x9E:
            case    0x9F:
                inst_len = 0; strcat( mnemonic, "               " ); break;
        //========================================================================
            case    0xA0:
                inst_len = 2; strcat( mnemonic, "LDI            " ); break;
            case    0xA1:
                inst_len = 2; strcat( mnemonic, "CPI            " ); break;
            case    0xA2:
            case    0xA3:
            case    0xA4:
            case    0xA5:
            case    0xA6:
            case    0xA7:
                inst_len = 0; strcat( mnemonic, "               " ); break;
            case    0xA8:
                inst_len = 2; strcat( mnemonic, "LDD            " ); break;
            case    0xA9:
                inst_len = 2; strcat( mnemonic, "CPD            " ); break;
            case    0xAA:
            case    0xAB:
            case    0xAC:
            case    0xAD:
            case    0xAE:
            case    0xAF:
                inst_len = 0; strcat( mnemonic, "               " ); break;
        //========================================================================
            case    0xB0:
                inst_len = 2; strcat( mnemonic, "LDIR           " ); break;
            case    0xB1:
                inst_len = 2; strcat( mnemonic, "CPIR           " ); break;
            case    0xB2:
            case    0xB3:
            case    0xB4:
            case    0xB5:
            case    0xB6:
            case    0xB7:
                inst_len = 0; strcat( mnemonic, "               " ); break;
            case    0xB8:
                inst_len = 2; strcat( mnemonic, "LDDR           " ); break;
            case    0xB9:
                inst_len = 2; strcat( mnemonic, "CPDR           " ); break;
            case    0xBA:
            case    0xBB:
            case    0xBC:
            case    0xBD:
            case    0xBE:
            case    0xBF:
                inst_len = 0; strcat( mnemonic, "               " ); break;
        //========================================================================
            case    0xC0:
            case    0xC1:
            case    0xC2:
            case    0xC3:
            case    0xC4:
            case    0xC5:
            case    0xC6:
            case    0xC7:
            case    0xC8:
            case    0xC9:
            case    0xCA:
            case    0xCB:
            case    0xCC:
            case    0xCD:
            case    0xCE:
            case    0xCF:
                inst_len = 0; strcat( mnemonic, "               " ); break;
        //========================================================================
            case    0xD0:
            case    0xD1:
            case    0xD2:
            case    0xD3:
            case    0xD4:
            case    0xD5:
            case    0xD6:
            case    0xD7:
            case    0xD8:
            case    0xD9:
            case    0xDA:
            case    0xDB:
            case    0xDC:
            case    0xDD:
            case    0xDE:
            case    0xDF:
                inst_len = 0; strcat( mnemonic, "               " ); break;
        //========================================================================
            case    0xE0:
            case    0xE1:
            case    0xE2:
            case    0xE3:
            case    0xE4:
            case    0xE5:
            case    0xE6:
            case    0xE7:
            case    0xE8:
            case    0xE9:
            case    0xEA:
            case    0xEB:
            case    0xEC:
            case    0xED:
            case    0xEE:
            case    0xEF:
                inst_len = 0; strcat( mnemonic, "               " ); break;
        //========================================================================
            case    0xF0:
            case    0xF1:
            case    0xF2:
            case    0xF3:
            case    0xF4:
            case    0xF5:
            case    0xF6:
            case    0xF7:
            case    0xF8:
            case    0xF9:
            case    0xFA:
            case    0xFB:
            case    0xFC:
            case    0xFD:
            case    0xFE:
            case    0xFF:
                inst_len = 0; strcat( mnemonic, "               " ); break;
        //========================================================================
        }
    }
    //  Write the instruction address.
    printf( "%04X - ", pc );

    if ( inst_len == 0 )
        printf( "            - " );
    else
    if ( inst_len == 1 )
        printf( "%02X          - ",
                memory_get_8( pc     )  );
    else
    if ( inst_len == 2 )
        printf( "%02X %02X       - ",
                memory_get_8( pc     ),
                memory_get_8( pc + 1 )  );
    else
    if ( inst_len == 3 )
        printf( "%02X %02X %02X    - ",
                memory_get_8( pc     ),
                memory_get_8( pc + 1 ),
                memory_get_8( pc + 2 )  );
    else
    if ( inst_len == 4 )
        printf( "%02X %02X %02X %02X - ",
                memory_get_8( pc     ),
                memory_get_8( pc + 1 ),
                memory_get_8( pc + 2 ),
                memory_get_8( pc + 3 )  );

    if( mnemonic[ 0 ] == ' ' && EIS == EIS_ED )
        printf( "%02X %02X %02X %02X - \n",
                memory_get_8( pc     ),
                memory_get_8( pc + 1 ),
                memory_get_8( pc + 2 ),
                memory_get_8( pc + 3 )  );

    printf( "%s - AF:%04X BC:%04X DE:%04X HL:%04X SP:%04X (%04X)\n",
            mnemonic, CPU_REG_AF, CPU_REG_BC, CPU_REG_DE, CPU_REG_HL,
            CPU_REG_SP, memory_get_16( CPU_REG_SP ) );

    //  Update the display for each and instruction decode.
    fflush( stdout );
}
/****************************************************************************/