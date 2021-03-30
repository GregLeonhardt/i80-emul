/*******************************  COPYRIGHT  ********************************/
/*
 *  Author? "Gregory N. Leonhardt"
 *  License? "CC BY-NC 2.0"
 *           "https://creativecommons.org/licenses/by-nc/2.0/"
 *
 ****************************************************************************/

/******************************** JAVADOC ***********************************/
/**
 *  This file contains emulation code for all "LD" instructions.
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


/****************************************************************************
 * Application
 ****************************************************************************/

                                //*******************************************
#include "global.h"             //  Global definitions
#include "memory.h"             //  Memory management and access
#include "registers.h"          //  All things CPU registers.
#include "load.h"               //  LD *,*
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

/****************************************************************************
 * MAIN
 ****************************************************************************/

/****************************************************************************/
/**                     Page        Op-Code
 *  LD  r, r'             71        01dddsss
 *  MOV d1,r2            4-4
 *
 *  The contents of any register r' are loaded to any other register r. r, r'
 *  identifies any of the registers A, B, C, D, E, H, or L.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
ld_rr_i80(
    uint8_t                     op_code
    )
{
    //  LD rd, rs
    reg_put_dr( op_code, reg_get_sr( op_code ) );

    //  Set the number of states for this instruction
    operation_rc.states =   4;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  LD  r, n              72        00rrr110 nnnnnnnn
 *  MVI r, data          4-4
 *
 *  The 8-bit integer n is loaded to any register r, in which r identifies
 *  registers A, B, C, D, E, H, or L.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
ld_rn_i80(
    uint8_t                     op_code
    )
{
    //  Store 'n' in the defined register
    reg_put_dr( op_code, memory_get_8( CPU_REG_PC++ ) );

    //  Set the number of states for this instruction
    operation_rc.states = 7;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  LD  r, (HL)           74        01rrr110
 *  MVI r, M             4-4
 *
 *  The 8-bit contents of memory location (HL) are loaded to register r, in
 *  which r identifies registers A, B, C, D, E, H, or L.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
ld_rhl_i80(
    uint8_t                     op_code
    )
{
    //  LD r, (HL)
    reg_put_dr( op_code, memory_get_8( CPU_REG_HL ) );

    //  Set the number of states for this instruction
    operation_rc.states   =   7;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  LD  (HL), r           79        01110rrr
 *  MOV M, r             4-4
 *
 *
 *  The contents of register r are loaded to the memory location specified by
 *  the contents of the HL register pair. The r symbol identifies registers
 *  A, B, C, D, E, H, or L.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
ld_hlr_i80(
    uint8_t                     op_code
    )
{
    //  LD (HL), r
    memory_put_8( CPU_REG_HL, reg_get_sr( op_code ) );

    //  Set the number of states for this instruction
    operation_rc.states =  7;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  LD  (HL), n           85        00110110 nnnnnnnn
 *  MVI M, data          4-4
 *
 *  The n integer is loaded to the memory address specified by the contents of
 *  the HL register pair.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
ld_hln_i80(
    uint8_t                     op_code
    )
{
    //  LD (HL), n
    memory_put_8( CPU_REG_HL, memory_get_8( CPU_REG_PC++ ) );

    //  Set the number of states for this instruction
    operation_rc.states = 10;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  LD  A, (ss)           88        00ss0101
 *  LXDA rp              4-5
 *
 *  The content of the memory location, whose address is in the register pair
 *  ss, is moved to register A.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      Only register pairs BC or DE may be specified.
 *
 ****************************************************************************/

void
ld_ass_i80(
    uint8_t                     op_code
    )
{
    //  LD A, (ss)
    PUT_A( memory_get_8( reg_get_ss( op_code ) ) );

    //  Set the number of states for this instruction
    operation_rc.states =  7;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  LD  A, (nn)           90        00111010 addr_l addr_h
 *  LDA addr             4-5
 *
 *  The contents of the memory location specified by the operands nn are loaded
 *  to the Accumulator. The first n operand after the op code is the low-order
 *  byte of a 2-byte memory address.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      Only register pairs BC or DE may be specified.
 *
 ****************************************************************************/

void
ld_ann_i80(
    uint8_t                     op_code
    )
{
    //  LD A, (nn)
    PUT_A( memory_get_8( memory_get_16_pc_p( ) ) );

    //  Set the number of states for this instruction
    operation_rc.states = 13;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  LD  (ss), A           91        00ss0010
 *  STAX rp              4-5
 *
 *  The content of the memory location, whose address is in the register pair
 *  ss, is moved to register A.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      Only register pairs BC or DE may be specified.
 *
 ****************************************************************************/

void
ld_ssa_i80(
    uint8_t                     op_code
    )
{
    //  LD (ss), A
    memory_put_8( reg_get_ss( op_code ), GET_A( ) );

    //  Set the number of states for this instruction
    operation_rc.states =  7;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  LD  (nn), A           93        00110010 addr_l addr_h
 *  STA ADDR             4-5
 *
 *  The contents of the Accumulator are loaded to the memory address specified
 *  by the operand nn. The first n operand after the op code is the low-order
 *  byte of nn.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      Only register pairs BC or DE may be specified.
 *
 ****************************************************************************/

void
ld_nna_i80(
    uint8_t                     op_code
    )
{
    //  LD (ss), A
    memory_put_8( memory_get_16_pc_p( ), GET_A( ) );

    //  Set the number of states for this instruction
    operation_rc.states = 13;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  LD  ss, nn            99        00ss0001 nnnnnnnn nnnnnnnn
 *  LXI rp, data         4-5
 *
 *  The 2-byte integer nn is loaded to the dd register pair, in which dd
 *  defines the BC, DE, HL, or SP register pairs.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
ld_ssNN_i80(
    uint8_t                     op_code
    )
{
    //  LD ss, nn
    reg_put_ss( op_code, memory_get_16_pc_p(  ) );

    //  Set the number of states for this instruction
    operation_rc.states = 10;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  LD HL, (nn)          102        00101010 addr_low addr_high
 *  LHLD addr            4-5
 *
 *  The contents of memory address (nn) are loaded to the low-order portion
 *  of register pair HL (Register L), and the contents of the next highest
 *  memory address (nn + 1) are loaded to the high-order portion of HL
 *  (Register H). The first n operand after the op code is the low-order
 *  byte of nn.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
ld_hlnn_i80(
    uint8_t                     op_code
    )
{
    //  LD HL, (nn)
    CPU_REG_HL = memory_get_16_p( memory_get_16_pc_p( ) );

    //  Set the number of states for this instruction
    operation_rc.states =  16;

    //  DONE!
}

/****************************************************************************/
/**                     Page        Op-Code
 *  LD (nn), HL          107        00100010 addr_low addr_high
 *  SHLD addr            4-5
 *
 *  The contents of the low-order portion of register pair HL (Register L) are
 *  loaded to memory address (nn), and the contents of the high-order portion
 *  of HL (Register H) are loaded to the next highest memory address (nn + 1).
 *  The first n operand after the op code is the low-order byte of nn.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
ld_nnhl_i80(
    uint8_t                     op_code
    )
{
    //  LD (nn), HL
    memory_put_16_p( memory_get_16_pc_p( ), CPU_REG_HL );

    //  Set the number of states for this instruction
    operation_rc.states =  16;

    //  DONE!
}

/****************************************************************************/
/**                     Page        Op-Code
 *  LD SP, HL            112        11111001
 *  SPHL                4-14
 *
 *  The contents of the register pair HL are loaded to the Stack Pointer (SP).
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
ld_sphl_i80(
    uint8_t                     op_code
    )
{
    //  LD SP, HL
    CPU_REG_SP = CPU_REG_HL;

    //  Set the number of states for this instruction
    operation_rc.states =   6;

    //  DONE!
}

/****************************************************************************/
/**                     Page        Op-Code
 *  PUSH qq              115        11qq0101
 *  PUSH PSW            4-13
 *  PUSH rp             4-13
 *
 *  The contents of the register pair qq are pushed to the external memory
 *  last-in, first-out (LIFO) stack. The Stack Pointer (SP) Register pair holds
 *  the 16-bit address of the current top of the Stack. This instruction first
 *  decrements SP and loads the high-order byte of register pair qq to the
 *  memory address specified by the SP. The SP is decremented again and loads
 *  the low-order byte of qq to the memory location corresponding to this new
 *  address in the SP. The operand qq identifies register pair BC, DE, HL, or
 *  AF.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
ld_pushqq_i80(
    uint8_t                     op_code
    )
{
    //  LD SP, HL
    push( reg_get_qq( op_code ) );

    //  Set the number of states for this instruction
    operation_rc.states =  11;

    //  DONE!
}

/****************************************************************************/
/**                     Page        Op-Code
 *  POP  qq              119        11qq0001
 *  POP  PSW            4-13
 *  POP  rp             4-13
 *
 *  The top two bytes of the external memory last-in, first-out (LIFO) stack
 *  are popped to register pair qq. The Stack Pointer (SP) Register pair holds
 *  the 16-bit address of the current top of the Stack. This instruction first
 *  loads to the low-order portion of qq, the byte at the memory location
 *  corresponding to the contents of SP; then SP is incremented and the contents
 *  of the corresponding adjacent memory location are loaded to the high-order
 *  portion of qq and the SP is now incremented again. The operand qq identifies
 *  register pair BC, DE, HL, or AF.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
ld_popqq_i80(
    uint8_t                     op_code
    )
{
    //  LD SP, HL
    reg_put_qq( op_code, pop( ) );

    //  Set the number of states for this instruction
    operation_rc.states =  11;

    //  DONE!
}

/****************************************************************************/
/**                     Page           Op-Code
 *  LD  (nn), ss         108        ED 01ss0011 addr_l  addr_h
 *
 *  The low-order byte of register pair ss is loaded to memory address (nn);
 *  the upper byte is loaded to memory address (nn + 1). Register pair ss
 *  defines either BC, DE, HL, or SP.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      Pair ss
 *           00     BC
 *           01     DE
 *           10     HL
 *           11     SP
 *
 ****************************************************************************/

void
ld_nnss_ED(
    uint8_t                     op_code
    )
{
    //  LD (nn), ss
    memory_put_16_p( memory_get_16_pc_p( ), reg_get_ss( op_code ) );

    //  Set the number of states for this instruction
    operation_rc.states = 16;
}

/****************************************************************************/
/**                     Page           Op-Code
 *  LD  ss, (nn)         103        ED 01ss1011 addr_l  addr_h
 *
 *  The contents of address (nn) are loaded to the low-order portion of
 *  register pair ss, and the contents of the next highest memory address
 *  (nn + 1) are loaded to the high-order portion of dd. Register pair ss
 *  defines BC, DE, HL, or SP.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      Pair ss
 *           00     BC
 *           01     DE
 *           10     HL
 *           11     SP
 *
 ****************************************************************************/

void
ld_ssnn_ED(
    uint8_t                     op_code
    )
{
    //  LD ss, (nn)
    reg_put_ss( op_code, memory_get_16_p( memory_get_16_pc_p( ) ) );

    //  Set the number of states for this instruction
    operation_rc.states = 20;
}

/****************************************************************************/
/**                     Page           Op-Code
 *  LD  i, a              96        ED 01000111
 *
 *  The contents of the Accumulator are loaded to the Interrupt Control Vector
 *  Register, I.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
ld_ia_ED(
    uint8_t                     op_code
    )
{
    //  LD   i, a
    CPU_REG_I = GET_A( );

    //  Set the number of states for this instruction
    operation_rc.states =  9;
}

/****************************************************************************/
/**                     Page           Op-Code
 *  LD  a, i              94        ED 01011110
 *
 *  The contents of the Interrupt Vector Register I are loaded to the
 *  Accumulator.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
ld_ai_ED(
    uint8_t                     op_code
    )
{
    //  LD   a, i
    PUT_A( CPU_REG_I );

    //  Set the number of states for this instruction
    operation_rc.states =  9;
}

/****************************************************************************/
/**                     Page           Op-Code
 *  LD  r, a              97        ED 01001111
 *
 *  The contents of the Accumulator are loaded to the Memory Refresh register R.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
ld_ra_ED(
    uint8_t                     op_code
    )
{
    //  LD   i, a
    CPU_REG_R = GET_A( );

    //  Set the number of states for this instruction
    operation_rc.states =  9;
}

/****************************************************************************/
/**                     Page           Op-Code
 *  LD  a, r              95        ED 01011111
 *
 *  The contents of Memory Refresh Register R are loaded to the Accumulator.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
ld_ar_ED(
    uint8_t                     op_code
    )
{
    //  LD   a, i
    PUT_A( CPU_REG_R );

    //  Set the number of states for this instruction
    operation_rc.states =  9;
}

/****************************************************************************/
/**                     Page           Op-Code
 *  LDD                  134        ED 01011000
 *
 *  The contents of Memory Refresh Register R are loaded to the Accumulator.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      S is not affected.
 *      Z is not affected.
 *      H is reset.
 *      P/V is set if BC – 1 ≠ 0; otherwise, it is reset.
 *      N is reset.
 *      C is not affected.
 *
 ****************************************************************************/

void
ld_ldd_ED(
    uint8_t                     op_code
    )
{
    //  LDD
    memory_put_8( CPU_REG_DE, memory_get_8( CPU_REG_HL ) );

    //  Decrement counters and pointers
    CPU_REG_HL -= 1;
    CPU_REG_DE -= 1;
    CPU_REG_BC -= 1;

    //  Is the counter equal to zero ?
    if( CPU_REG_BC != 0 )
    {
        //  NO:     Set the P/V flag
        SET_FLAG_PV( );
    }
    else
    {
        //  YES:    Clear the PV flag
        CLEAR_FLAG_PV( );
    }

    //  The remaining flags that are effected
    CLEAR_FLAG_H( );            //  H is reset.
    CLEAR_FLAG_N( );            //  N is reset.

    //  Set the number of states for this instruction
    operation_rc.states =16;
}

/****************************************************************************/
/**                     Page           Op-Code
 *  LDDR                 136        ED 10111000
 *
 *  This 2-byte instruction transfers a byte of data from the memory location
 *  addressed by the contents of the HL register pair to the memory location
 *  addressed by the contents of the DE register pair. Then both of these
 *  registers, and the BC (Byte Counter), are decremented. If decrementing
 *  causes BC to go to 0, the instruction is terminated. If BC is not 0,
 *  the program counter is decremented by two and the instruction is repeated.
 *  Interrupts are recognized and two refresh cycles execute after each data
 *  transfer.
 *  When the BC is set to 0, prior to instruction execution, the instruction
 *  loops through 64 KB.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      S is not affected.
 *      Z is not affected.
 *      H is reset.
 *      P/V is reset.
 *      N is reset.
 *      C is not affected.
 *
 ****************************************************************************/

void
ld_lddr_ED(
    uint8_t                     op_code
    )
{
    /**
     *  @param  count           Number of clock cycles                      */
    int                         count;

    //  Set the number of clock cycles this instruction will consume.
    if( CPU_REG_BC == 0 )
    {
        count = 0x0080000;
    }
    else
    {
        count = (int)CPU_REG_BC * 8;
    }

    //  LDDR
    do
    {
        memory_put_8( CPU_REG_DE, memory_get_8( CPU_REG_HL ) );

        //  Decrement counters and pointers
        CPU_REG_HL -= 1;
        CPU_REG_DE -= 1;
        CPU_REG_BC -= 1;

    }   while( CPU_REG_BC != 0 );


    //  Adjust the FLAGS as needed
    CLEAR_FLAG_H( );            //  H is reset.
    CLEAR_FLAG_PV( );           //  P/V is reset.
    CLEAR_FLAG_N( );            //  N is reset.

    //  Set the number of states for this instruction
    operation_rc.states = 16 + count;
}

/****************************************************************************/
/**                     Page           Op-Code
 *  LDI                  130        ED 10100000
 *
 *  A byte of data is transferred from the memory location addressed, by the
 *  contents of the HL register pair to the memory location addressed by the
 *  contents of the DE register pair. Then both these register pairs are
 *  incremented and the Byte Counter (BC) Register pair is decremented.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      S is not affected.
 *      Z is not affected.
 *      H is reset.
 *      P/V is set if BC – 1 ≠ 0; otherwise, it is reset.
 *      N is reset.
 *      C is not affected.
 *
 ****************************************************************************/

void
ld_ldi_ED(
    uint8_t                     op_code
    )
{
    //  LDD
    memory_put_8( CPU_REG_DE, memory_get_8( CPU_REG_HL ) );

    //  Decrement counters and pointers
    CPU_REG_HL += 1;
    CPU_REG_DE += 1;
    CPU_REG_BC -= 1;

    //  Is the counter equal to zero ?
    if( CPU_REG_BC != 0 )
    {
        //  NO:     Set the P/V flag
        SET_FLAG_PV( );
    }
    else
    {
        //  YES:    Clear the PV flag
        CLEAR_FLAG_PV( );
    }

    //  The remaining flags that are effected
    CLEAR_FLAG_H( );            //  H is reset.
    CLEAR_FLAG_N( );            //  N is reset.

    //  Set the number of states for this instruction
    operation_rc.states =16;
}

/****************************************************************************/
/**                     Page           Op-Code
 *  LDIR                 132        ED 10110000
 *
 *  This 2-byte instruction transfers a byte of data from the memory location
 *  addressed by the contents of the HL register pair to the memory location
 *  addressed by the DE register pair.  Both these register pairs are
 *  incremented and the Byte Counter (BC) Register pair is decremented. If
 *  decrementing allows the BC to go to 0, the instruction is terminated. If
 *  BC is not 0, the program counter is decremented by two and the instruction
 *  is repeated. Interrupts are recognized and two refresh cycles are executed
 *  after each data transfer. When the BC is set to 0 prior to instruction
 *  execution, the instruction loops through 64 KB.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
ld_ldir_ED(
    uint8_t                     op_code
    )
{
    /**
     *  @param  count           Number of clock cycles                      */
    int                         count;

    //  Set the number of clock cycles this instruction will consume.
    if( CPU_REG_BC == 0 )
    {
        count = 0x0080000;
    }
    else
    {
        count = (int)CPU_REG_BC * 8;
    }

    //  LDDR
    do
    {
        memory_put_8( CPU_REG_DE, memory_get_8( CPU_REG_HL ) );

        //  Decrement counters and pointers
        CPU_REG_HL += 1;
        CPU_REG_DE += 1;
        CPU_REG_BC -= 1;

    }   while( CPU_REG_BC != 0 );


    //  Adjust the FLAGS as needed
    CLEAR_FLAG_H( );            //  H is reset.
    CLEAR_FLAG_PV( );           //  P/V is reset.
    CLEAR_FLAG_N( );            //  N is reset.

    //  Set the number of states for this instruction
    operation_rc.states = 16 + count;
}
/****************************************************************************/