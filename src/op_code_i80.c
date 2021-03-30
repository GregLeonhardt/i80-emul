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

#define     DEBUG_MODE      ( 0 )

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


/****************************************************************************
 * Application
 ****************************************************************************/

                                //*******************************************
#include "global.h"             //  Global definitions
#include "memory.h"             //  Memory management and access
#include "registers.h"          //  All things CPU registers.
#include "op_code.h"            //  OP-Code instruction maps
#include "control.h"            //  Control (NOP, HLT, etc.) instrucions.
#include "load.h"               //  LD   *,*
#include "exchange.h"           //  EX   *,*
#include "math.h"               //  8 bit instrucions.
#include "logic.h"              //  Logic (AND, OR, XOR, CMP) instrucions.
#include "math_16.h"            //  16 bit Arithmatic instrucions.
#include "shift.h"              //  Shift and Rotate instructions
#include "jump.h"               //  Jump instructions
#include "call.h"               //  Call instructions
#include "io.h"                 //  Input & Output instructions
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

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************/
/**
 *  The program counter is pointing to an invalid op-code.
 *
 *  @param
 *
 *  @return                     0 is returned
 *
 *  @note
 *
 ****************************************************************************/

static
void
invalid_op_code(
    uint8_t                     op_code
    )
{

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Function code
     ************************************************************************/

    //  Tell the world there is a problem.
    printf( "DEBUG: Invalid i80 op_code [x%02X] @ [x%04X]\n",
            op_code, CPU_REG_PC );

#if DEBUG_MODE
        //  Memory dump (Page 0)
        printf( "Page-0\n" );
        memory_dump( 0x0000, 0x0100 );

        //  Memory dump (CCP)
        printf( "\nCCP:\n" );
        memory_dump( 0xDC00, 0x0800 );

        //  Memory dump (BDOS)
        printf( "\nBDOS:\n" );
        memory_dump( 0xE400, 0x0E00 );

        //  Memory dump (BIOS)
        printf( "\nBIOS:\n" );
        memory_dump( 0xF200, 0x0E00 );

        //  The last line feed and flush
        printf( "\n\n" );
        fflush( stdout );
#endif

    /************************************************************************
     *  Function Exit
     ************************************************************************/
    operation_rc.states = 0;

    //  DONE!
}

/****************************************************************************
 * MAIN
 ****************************************************************************/


/****************************************************************************/
/**
 *  Initialize the i8080 instruction map.
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *
 ****************************************************************************/

void
op_code_i80_init(
    void
    )
{
    //========================================================================
    op_code_i80_table[ 0x00 ] = control_nop_i80;            //  NOP
    op_code_i80_table[ 0x01 ] = ld_ssNN_i80;                //  LD      BC, nn
    op_code_i80_table[ 0x02 ] = ld_ssa_i80;                 //  LD      (BC), A
    op_code_i80_table[ 0x03 ] = math_incss_i80;             //  INC     BC
    op_code_i80_table[ 0x04 ] = math_incr_i80;              //  INC     B
    op_code_i80_table[ 0x05 ] = math_decr_r80;              //  DEC     B
    op_code_i80_table[ 0x06 ] = ld_rn_i80;                  //  LD      B, n
    op_code_i80_table[ 0x07 ] = shift_rlca_i80;             //  RLCA
    op_code_i80_table[ 0x08 ] = invalid_op_code;            //  EX      AF, AF' (Z80)
    op_code_i80_table[ 0x09 ] = math_addhlss_i80;           //  ADD     HL, BC
    op_code_i80_table[ 0x0A ] = ld_ass_i80;                 //  LD      A, (BC)
    op_code_i80_table[ 0x0B ] = math_decss_i80;             //  DEC     BC
    op_code_i80_table[ 0x0C ] = math_incr_i80;              //  INC     C
    op_code_i80_table[ 0x0D ] = math_decr_r80;              //  DEC     C
    op_code_i80_table[ 0x0E ] = ld_rn_i80;                  //  LD      C, n
    op_code_i80_table[ 0x0F ] = shift_rrca_i80;             //  RRCA
    //========================================================================
    op_code_i80_table[ 0x10 ] = invalid_op_code;            //  DJNZ    e       (Z80)
    op_code_i80_table[ 0x11 ] = ld_ssNN_i80;                //  LD      DE, nn
    op_code_i80_table[ 0x12 ] = ld_ssa_i80;                 //  LD      (DE), A
    op_code_i80_table[ 0x13 ] = math_incss_i80;             //  INC     DE
    op_code_i80_table[ 0x14 ] = math_incr_i80;              //  INC     D
    op_code_i80_table[ 0x15 ] = math_decr_r80;              //  DEC     D
    op_code_i80_table[ 0x16 ] = ld_rn_i80;                  //  LD      D, n
    op_code_i80_table[ 0x17 ] = shift_rla_i80;              //  RLA
    op_code_i80_table[ 0x18 ] = invalid_op_code;            //  JR      e       (Z80)
    op_code_i80_table[ 0x19 ] = math_addhlss_i80;           //  ADD     HL, DE
    op_code_i80_table[ 0x1A ] = ld_ass_i80;                 //  LD      A, (DE)
    op_code_i80_table[ 0x1B ] = math_decss_i80;             //  DEC     DE
    op_code_i80_table[ 0x1C ] = math_incr_i80;              //  INC     E
    op_code_i80_table[ 0x1D ] = math_decr_r80;              //  DEC     E
    op_code_i80_table[ 0x1E ] = ld_rn_i80;                  //  LD      E, n
    op_code_i80_table[ 0x1F ] = shift_rra_i80;              //  RRA
    //========================================================================
    op_code_i80_table[ 0x20 ] = invalid_op_code;            //  JR      NZ, e   (Z80)
    op_code_i80_table[ 0x21 ] = ld_ssNN_i80;                //  LD      HL, nn
    op_code_i80_table[ 0x22 ] = ld_nnhl_i80;                //  LD      (nn), HL
    op_code_i80_table[ 0x23 ] = math_incss_i80;             //  INC     HL
    op_code_i80_table[ 0x24 ] = math_incr_i80;              //  INC     H
    op_code_i80_table[ 0x25 ] = math_decr_r80;              //  DEC     H
    op_code_i80_table[ 0x26 ] = ld_rn_i80;                  //  LD      H, n
    op_code_i80_table[ 0x27 ] = math_daa_i80;               //  DAA
    op_code_i80_table[ 0x28 ] = invalid_op_code;            //  JR      Z, e    (Z80)
    op_code_i80_table[ 0x29 ] = math_addhlss_i80;           //  ADD     HL, HL
    op_code_i80_table[ 0x2A ] = ld_hlnn_i80;                //  LD      HL, (nn)
    op_code_i80_table[ 0x2B ] = math_decss_i80;             //  DEC     HL
    op_code_i80_table[ 0x2C ] = math_incr_i80;              //  INC     L
    op_code_i80_table[ 0x2D ] = math_decr_r80;              //  DEC     L
    op_code_i80_table[ 0x2E ] = ld_rn_i80;                  //  LD      L, n
    op_code_i80_table[ 0x2F ] = math_cpl_i80;               //  CPL
    //========================================================================
    op_code_i80_table[ 0x30 ] = invalid_op_code;            //  JR      NC, e   (Z80)
    op_code_i80_table[ 0x31 ] = ld_ssNN_i80;                //  LD      SP, nn
    op_code_i80_table[ 0x32 ] = ld_nna_i80;                 //  LD      (nn), A
    op_code_i80_table[ 0x33 ] = math_incss_i80;             //  INC     SP
    op_code_i80_table[ 0x34 ] = math_inchl_i80;             //  INC     (HL)
    op_code_i80_table[ 0x35 ] = math_dechl_i80;             //  DEC     (HL)
    op_code_i80_table[ 0x36 ] = ld_hln_i80;                 //  LD      (HL), n
    op_code_i80_table[ 0x37 ] = math_scf_i80;               //  SCF
    op_code_i80_table[ 0x38 ] = invalid_op_code;            //  JR      C, e    (Z80)
    op_code_i80_table[ 0x39 ] = math_addhlss_i80;           //  ADD     HL, SP
    op_code_i80_table[ 0x3A ] = ld_ann_i80;                 //  LD      A, (nn)
    op_code_i80_table[ 0x3B ] = math_decss_i80;             //  DEC     SP
    op_code_i80_table[ 0x3C ] = math_incr_i80;              //  INC     A
    op_code_i80_table[ 0x3D ] = math_decr_r80;              //  DEC     A
    op_code_i80_table[ 0x3E ] = ld_rn_i80;                  //  LD      A, n
    op_code_i80_table[ 0x3F ] = math_ccf_i80;               //  CFF
    //========================================================================
    op_code_i80_table[ 0x40 ] = ld_rr_i80;                  //  LD      B, B'
    op_code_i80_table[ 0x41 ] = ld_rr_i80;                  //  LD      B, C'
    op_code_i80_table[ 0x42 ] = ld_rr_i80;                  //  LD      B, D'
    op_code_i80_table[ 0x43 ] = ld_rr_i80;                  //  LD      B, E'
    op_code_i80_table[ 0x44 ] = ld_rr_i80;                  //  LD      B, H'
    op_code_i80_table[ 0x45 ] = ld_rr_i80;                  //  LD      B, L'
    op_code_i80_table[ 0x46 ] = ld_rhl_i80;                 //  LD      B, (HL)
    op_code_i80_table[ 0x47 ] = ld_rr_i80;                  //  LD      C, A'
    op_code_i80_table[ 0x48 ] = ld_rr_i80;                  //  LD      C, B'
    op_code_i80_table[ 0x49 ] = ld_rr_i80;                  //  LD      C, C'
    op_code_i80_table[ 0x4A ] = ld_rr_i80;                  //  LD      C, D'
    op_code_i80_table[ 0x4B ] = ld_rr_i80;                  //  LD      C, E'
    op_code_i80_table[ 0x4C ] = ld_rr_i80;                  //  LD      C, H'
    op_code_i80_table[ 0x4D ] = ld_rr_i80;                  //  LD      C, L'
    op_code_i80_table[ 0x4E ] = ld_rhl_i80;                 //  LD      C, (HL)
    op_code_i80_table[ 0x4F ] = ld_rr_i80;                  //  LD      C, A'
    //========================================================================
    op_code_i80_table[ 0x50 ] = ld_rr_i80;                  //  LD      D, B'
    op_code_i80_table[ 0x51 ] = ld_rr_i80;                  //  LD      D, C'
    op_code_i80_table[ 0x52 ] = ld_rr_i80;                  //  LD      D, D'
    op_code_i80_table[ 0x53 ] = ld_rr_i80;                  //  LD      D, E'
    op_code_i80_table[ 0x54 ] = ld_rr_i80;                  //  LD      D, H'
    op_code_i80_table[ 0x55 ] = ld_rr_i80;                  //  LD      D, L'
    op_code_i80_table[ 0x56 ] = ld_rhl_i80;                 //  LD      D, (HL)
    op_code_i80_table[ 0x57 ] = ld_rr_i80;                  //  LD      E, A'
    op_code_i80_table[ 0x58 ] = ld_rr_i80;                  //  LD      E, B'
    op_code_i80_table[ 0x59 ] = ld_rr_i80;                  //  LD      E, C'
    op_code_i80_table[ 0x5A ] = ld_rr_i80;                  //  LD      E, D'
    op_code_i80_table[ 0x5B ] = ld_rr_i80;                  //  LD      E, E'
    op_code_i80_table[ 0x5C ] = ld_rr_i80;                  //  LD      E, H'
    op_code_i80_table[ 0x5D ] = ld_rr_i80;                  //  LD      E, L'
    op_code_i80_table[ 0x5E ] = ld_rhl_i80;                 //  LD      E, (HL)
    op_code_i80_table[ 0x5F ] = ld_rr_i80;                  //  LD      E, A'
    //========================================================================
    op_code_i80_table[ 0x60 ] = ld_rr_i80;                  //  LD      H, B'
    op_code_i80_table[ 0x61 ] = ld_rr_i80;                  //  LD      H, C'
    op_code_i80_table[ 0x62 ] = ld_rr_i80;                  //  LD      H, D'
    op_code_i80_table[ 0x63 ] = ld_rr_i80;                  //  LD      H, E'
    op_code_i80_table[ 0x64 ] = ld_rr_i80;                  //  LD      H, H'
    op_code_i80_table[ 0x65 ] = ld_rr_i80;                  //  LD      H, L'
    op_code_i80_table[ 0x66 ] = ld_rhl_i80;                 //  LD      H, (HL)
    op_code_i80_table[ 0x67 ] = ld_rr_i80;                  //  LD      H, A'
    op_code_i80_table[ 0x68 ] = ld_rr_i80;                  //  LD      L, B'
    op_code_i80_table[ 0x69 ] = ld_rr_i80;                  //  LD      L, C'
    op_code_i80_table[ 0x6A ] = ld_rr_i80;                  //  LD      L, D'
    op_code_i80_table[ 0x6B ] = ld_rr_i80;                  //  LD      L, E'
    op_code_i80_table[ 0x6C ] = ld_rr_i80;                  //  LD      L, H'
    op_code_i80_table[ 0x6D ] = ld_rr_i80;                  //  LD      L, L'
    op_code_i80_table[ 0x6E ] = ld_rhl_i80;                 //  LD      L, (HL)
    op_code_i80_table[ 0X6F ] = ld_rr_i80;                  //  LD      L, A'
    //========================================================================
    op_code_i80_table[ 0x70 ] = ld_hlr_i80;                 //  LD      (HL), B
    op_code_i80_table[ 0x71 ] = ld_hlr_i80;                 //  LD      (HL), C
    op_code_i80_table[ 0x72 ] = ld_hlr_i80;                 //  LD      (HL), D
    op_code_i80_table[ 0x73 ] = ld_hlr_i80;                 //  LD      (HL), E
    op_code_i80_table[ 0x74 ] = ld_hlr_i80;                 //  LD      (HL), H
    op_code_i80_table[ 0x75 ] = ld_hlr_i80;                 //  LD      (HL), L
    op_code_i80_table[ 0x76 ] = control_hlt_i80;            //  HALT
    op_code_i80_table[ 0x77 ] = ld_hlr_i80;                 //  LD      (HL), B
    op_code_i80_table[ 0x78 ] = ld_rr_i80;                  //  LD      A, B'
    op_code_i80_table[ 0x79 ] = ld_rr_i80;                  //  LD      A, C'
    op_code_i80_table[ 0x7A ] = ld_rr_i80;                  //  LD      A, D'
    op_code_i80_table[ 0x7B ] = ld_rr_i80;                  //  LD      A, E'
    op_code_i80_table[ 0x7C ] = ld_rr_i80;                  //  LD      A, H'
    op_code_i80_table[ 0x7D ] = ld_rr_i80;                  //  LD      A, L'
    op_code_i80_table[ 0x7E ] = ld_rhl_i80;                 //  LD      A, (HL)
    op_code_i80_table[ 0X7F ] = ld_rr_i80;                  //  LD      A, B'
    //========================================================================
    op_code_i80_table[ 0x80 ] = math_addr_i80;              //  ADD     A, B
    op_code_i80_table[ 0x81 ] = math_addr_i80;              //  ADD     A, C
    op_code_i80_table[ 0x82 ] = math_addr_i80;              //  ADD     A, D
    op_code_i80_table[ 0x83 ] = math_addr_i80;              //  ADD     A, E
    op_code_i80_table[ 0x84 ] = math_addr_i80;              //  ADD     A, H
    op_code_i80_table[ 0x85 ] = math_addr_i80;              //  ADD     A, L
    op_code_i80_table[ 0x86 ] = math_addhl_i80;             //  ADD     A, (HL)
    op_code_i80_table[ 0x87 ] = math_addr_i80;              //  ADD     A, A
    op_code_i80_table[ 0x88 ] = math_adcr_i80;              //  ADC     A, B
    op_code_i80_table[ 0x89 ] = math_adcr_i80;              //  ADC     A, C
    op_code_i80_table[ 0x8A ] = math_adcr_i80;              //  ADC     A, D
    op_code_i80_table[ 0x8B ] = math_adcr_i80;              //  ADC     A, E
    op_code_i80_table[ 0x8C ] = math_adcr_i80;              //  ADC     A, H
    op_code_i80_table[ 0x8D ] = math_adcr_i80;              //  ADC     A, L
    op_code_i80_table[ 0x8E ] = math_adchl_i80;             //  ADC     A, (HL)
    op_code_i80_table[ 0x8F ] = math_adcr_i80;              //  ADC     A, A
    //========================================================================
    op_code_i80_table[ 0x90 ] = math_subr_i80;              //  SUB     A, B
    op_code_i80_table[ 0x91 ] = math_subr_i80;              //  SUB     A, C
    op_code_i80_table[ 0x92 ] = math_subr_i80;              //  SUB     A, D
    op_code_i80_table[ 0x93 ] = math_subr_i80;              //  SUB     A, E
    op_code_i80_table[ 0x94 ] = math_subr_i80;              //  SUB     A, H
    op_code_i80_table[ 0x95 ] = math_subr_i80;              //  SUB     A, L
    op_code_i80_table[ 0x96 ] = math_subhl_i80;             //  SUB     A, (HL)
    op_code_i80_table[ 0x97 ] = math_subr_i80;              //  SUB     A, A
    op_code_i80_table[ 0x98 ] = math_sbcr_i80;              //  SBC     A, B
    op_code_i80_table[ 0x99 ] = math_sbcr_i80;              //  SBC     A, D
    op_code_i80_table[ 0x9A ] = math_sbcr_i80;              //  SBC     A, E
    op_code_i80_table[ 0x9B ] = math_sbcr_i80;              //  SBC     A, F
    op_code_i80_table[ 0x9C ] = math_sbcr_i80;              //  SBC     A, H
    op_code_i80_table[ 0x9D ] = math_sbcr_i80;              //  SBC     A, L
    op_code_i80_table[ 0x9E ] = math_sbchl_i80;             //  SBC     A, (HL)
    op_code_i80_table[ 0x9F ] = math_sbcr_i80;              //  SBC     A, A
    //========================================================================
    op_code_i80_table[ 0xA0 ] = logic_andr_i80;             //  AND     B
    op_code_i80_table[ 0xA1 ] = logic_andr_i80;             //  AND     C
    op_code_i80_table[ 0xA2 ] = logic_andr_i80;             //  AND     D
    op_code_i80_table[ 0xA3 ] = logic_andr_i80;             //  AND     E
    op_code_i80_table[ 0xA4 ] = logic_andr_i80;             //  AND     H
    op_code_i80_table[ 0xA5 ] = logic_andr_i80;             //  AND     L
    op_code_i80_table[ 0xA6 ] = logic_andhl_i80;            //  AND     (HL)
    op_code_i80_table[ 0xA7 ] = logic_andr_i80;             //  AND     A
    op_code_i80_table[ 0xA8 ] = logic_xorr_i80;             //  XOR     B
    op_code_i80_table[ 0xA9 ] = logic_xorr_i80;             //  XOR     C
    op_code_i80_table[ 0xAA ] = logic_xorr_i80;             //  XOR     D
    op_code_i80_table[ 0xAB ] = logic_xorr_i80;             //  XOR     E
    op_code_i80_table[ 0xAC ] = logic_xorr_i80;             //  XOR     H
    op_code_i80_table[ 0xAD ] = logic_xorr_i80;             //  XOR     L
    op_code_i80_table[ 0xAE ] = logic_xorhl_i80;            //  XOR     (HL)
    op_code_i80_table[ 0xAF ] = logic_xorr_i80;             //  XOR     A
    //========================================================================
    op_code_i80_table[ 0xB0 ] = logic_orr_i80;              //  OR      B
    op_code_i80_table[ 0xB1 ] = logic_orr_i80;              //  OR      C
    op_code_i80_table[ 0xB2 ] = logic_orr_i80;              //  OR      D
    op_code_i80_table[ 0xB3 ] = logic_orr_i80;              //  OR      E
    op_code_i80_table[ 0xB4 ] = logic_orr_i80;              //  OR      H
    op_code_i80_table[ 0xB5 ] = logic_orr_i80;              //  OR      L
    op_code_i80_table[ 0xB6 ] = logic_orhl_i80;             //  OR      (HL)
    op_code_i80_table[ 0xB7 ] = logic_orr_i80;              //  OR      A
    op_code_i80_table[ 0xB8 ] = logic_cpr_i80;              //  CP      B
    op_code_i80_table[ 0xB9 ] = logic_cpr_i80;              //  CP      C
    op_code_i80_table[ 0xBA ] = logic_cpr_i80;              //  CP      D
    op_code_i80_table[ 0xBB ] = logic_cpr_i80;              //  CP      E
    op_code_i80_table[ 0xBC ] = logic_cpr_i80;              //  CP      H
    op_code_i80_table[ 0xBD ] = logic_cpr_i80;              //  CP      L
    op_code_i80_table[ 0xBE ] = logic_cphl_i80;             //  CP      (HL)
    op_code_i80_table[ 0xBF ] = logic_cpr_i80;              //  CP      A
    //========================================================================
    op_code_i80_table[ 0xC0 ] = ret_cc_i80;                 //  RET     NZ
    op_code_i80_table[ 0xC1 ] = ld_popqq_i80;               //  POP     BC
    op_code_i80_table[ 0xC2 ] = jump_jpccnn_i80;            //  JP      NZ, nn
    op_code_i80_table[ 0xC3 ] = jump_jpnn_i80;              //  JP      nn
    op_code_i80_table[ 0xC4 ] = call_ccnn_i80;              //  CALL    NZ, nn
    op_code_i80_table[ 0xC5 ] = ld_pushqq_i80;              //  PUSH    BC
    op_code_i80_table[ 0xC6 ] = math_addn_i80;              //  ADD     A, n
    op_code_i80_table[ 0xC7 ] = rst_t_i80;                  //  RST     0
    op_code_i80_table[ 0xC8 ] = ret_cc_i80;                 //  RET     Z
    op_code_i80_table[ 0xC9 ] = ret_i80;                    //  RET
    op_code_i80_table[ 0xCA ] = jump_jpccnn_i80;            //  JP      Z, nn
    op_code_i80_table[ 0xCB ] = invalid_op_code;            //  EIS     CB      (Z80)
    op_code_i80_table[ 0xCC ] = call_ccnn_i80;              //  CALL    Z, nn
    op_code_i80_table[ 0xCD ] = call_nn_i80;                //  CALL    nn
    op_code_i80_table[ 0xCE ] = math_adcn_i80;              //  ADC     A, n
    op_code_i80_table[ 0xCF ] = rst_t_i80;                  //  RST     1
    //========================================================================
    op_code_i80_table[ 0xD0 ] = ret_cc_i80;                 //  RET     NC
    op_code_i80_table[ 0xD1 ] = ld_popqq_i80;               //  POP     DE
    op_code_i80_table[ 0xD2 ] = jump_jpccnn_i80;            //  JP      NC, nn
    op_code_i80_table[ 0xD3 ] = out_n_i80;                  //  OUT     (n), A
    op_code_i80_table[ 0xD4 ] = call_ccnn_i80;              //  CALL    NC, nn
    op_code_i80_table[ 0xD5 ] = ld_pushqq_i80;              //  PUSH    DE
    op_code_i80_table[ 0xD6 ] = math_subn_i80;              //  SUB     n
    op_code_i80_table[ 0xD7 ] = rst_t_i80;                  //  RST     2
    op_code_i80_table[ 0xD8 ] = ret_cc_i80;                 //  RET     C
    op_code_i80_table[ 0xD9 ] = invalid_op_code;            //  EXX             (Z80)
    op_code_i80_table[ 0xDA ] = jump_jpccnn_i80;            //  JP      C, nn
    op_code_i80_table[ 0xDB ] = in_n_i80;                   //  IN      A, (n)
    op_code_i80_table[ 0xDC ] = call_ccnn_i80;              //  CALL    C, nn
    op_code_i80_table[ 0xDD ] = invalid_op_code;            //  EIS     DD      (Z80)
    op_code_i80_table[ 0xDE ] = math_sbcn_i80;              //  SBC     n
    op_code_i80_table[ 0xDF ] = rst_t_i80;                  //  RST     3
    //========================================================================
    op_code_i80_table[ 0xE0 ] = ret_cc_i80;                 //  RET     PO
    op_code_i80_table[ 0xE1 ] = ld_popqq_i80;               //  POP     HL
    op_code_i80_table[ 0xE2 ] = jump_jpccnn_i80;            //  JP      PO, nn
    op_code_i80_table[ 0xE3 ] = ex_sphl_i80;                //  EX      (SP), HL
    op_code_i80_table[ 0xE4 ] = call_ccnn_i80;              //  CALL    PO, nn
    op_code_i80_table[ 0xE5 ] = ld_pushqq_i80;              //  PUSH    HL
    op_code_i80_table[ 0xE6 ] = logic_andn_i80;             //  AND     n
    op_code_i80_table[ 0xE7 ] = rst_t_i80;                  //  RST     4
    op_code_i80_table[ 0xE8 ] = ret_cc_i80;                 //  RET     PE
    op_code_i80_table[ 0xE9 ] = jump_jphl_i80;              //  JP      (HL)
    op_code_i80_table[ 0xEA ] = jump_jpccnn_i80;            //  JP      PE, nn
    op_code_i80_table[ 0xEB ] = ex_dehl_i80;                //  EX      DE, HL
    op_code_i80_table[ 0xEC ] = call_ccnn_i80;              //  CALL    PE, nn
    op_code_i80_table[ 0xED ] = invalid_op_code;            //  EIS     ED      (Z80)
    op_code_i80_table[ 0xEE ] = logic_xorn_i80;             //  XOR     n
    op_code_i80_table[ 0xEF ] = rst_t_i80;                  //  RST     5
    //========================================================================
    op_code_i80_table[ 0xF0 ] = ret_cc_i80;                 //  RET     P
    op_code_i80_table[ 0xF1 ] = ld_popqq_i80;               //  POP     AF
    op_code_i80_table[ 0xF2 ] = jump_jpccnn_i80;            //  JP      P, nn
    op_code_i80_table[ 0xF3 ] = control_di_i80;             //  DI
    op_code_i80_table[ 0xF4 ] = call_ccnn_i80;              //  CALL    P, nn
    op_code_i80_table[ 0xF5 ] = ld_pushqq_i80;              //  PUSH    AF
    op_code_i80_table[ 0xF6 ] = logic_orn_i80;              //  OR      n
    op_code_i80_table[ 0xF7 ] = rst_t_i80;                  //  RST     6
    op_code_i80_table[ 0xF8 ] = ret_cc_i80;                 //  RET     M
    op_code_i80_table[ 0xF9 ] = ld_sphl_i80;                //  LD      SP, HL
    op_code_i80_table[ 0xFA ] = jump_jpccnn_i80;            //  JP,     M, nn
    op_code_i80_table[ 0xFB ] = control_di_i80;             //  EI
    op_code_i80_table[ 0xFC ] = call_ccnn_i80;              //  CALL    M, nn
    op_code_i80_table[ 0xFD ] = invalid_op_code;            //  EIS     FD      (Z80)
    op_code_i80_table[ 0xFE ] = logic_cpn_i80;              //  CP      n
    op_code_i80_table[ 0xFF ] = rst_t_i80;                  //  RST     7
    //========================================================================

}
/****************************************************************************/