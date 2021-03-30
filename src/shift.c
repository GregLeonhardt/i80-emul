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


/****************************************************************************
 * Application
 ****************************************************************************/

                                //*******************************************
#include "global.h"             //  Global definitions
#include "memory.h"             //  Memory management and access
#include "registers.h"          //  All things CPU registers.
#include "shift.h"              //  Shift and Rotate instructions
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
 *  RLCA                205        00000111
 *  RLC                 4-10
 *
 *  The contents of the Accumulator (Register A) are rotated left 1 bit
 *  position. The sign bit (bit 7) is copied to the Carry flag and also to
 *  bit 0. Bit 0 is the least-significant bit.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
shift_rlca_i80(
    uint8_t                     op_code
    )
{
    /**
     *  @param  data                Shift data                              */
    int                         data;

    //  Get data from the accumulator
    data = GET_A( );

    //  Left shift
    data = data << 1;

    //  Cary to bit 0
    if ( data & 0x0100 )
    {
        data |= 0x01;
        SET_FLAG_C( );
    }
    else
    {
        CLEAR_FLAG_C( );
    }

    PUT_A( (uint8_t)data );

    /************************************************************************
     *  SET FLAGS
     ************************************************************************/

    //  Carry         (CCF)                                                 C
    //  See above

    //  SUBTRACT/ADD                                                        N
    CLEAR_FLAG_N( );

    //  PARITY/OVERFLOW                                                     P/V
    // P/V is not affected.

    //  HALF CARRY                                                          H
    CLEAR_FLAG_H( );

    //  ZERO                                                                Z
    // Z is not affected.

    //  SIGN                                                                S
    // S is not affected.

    //  Set the number of states for this instruction
    operation_rc.states =   4;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  RLA                 207        00010111
 *  RLA                 4-10
 *
 *  The contents of the Accumulator (Register A) are rotated left 1 bit position
 *  through the Carry flag. The previous contents of the Carry flag are copied
 *  to bit 0. Bit 0 is the least significant bit.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
shift_rla_i80(
    uint8_t                     op_code
    )
{
    /**
     *  @param  data                Shift data                              */
    int                         data;

    //  Get data from the accumulator
    data = GET_A( );

    //  Left shift
    data = data << 1;

    //  Insert the cary flag into the LSB
    if ( ( GET_F( ) & CPU_FLAG_C ) != 0 )
        data |= 0x01;

    //  Cary to bit 0
    if ( data & 0x0100 )
    {
        SET_FLAG_C( );
    }
    else
    {
        CLEAR_FLAG_C( );
    }

    PUT_A( (uint8_t)data );

    /************************************************************************
     *  SET FLAGS
     ************************************************************************/

    //  Carry         (CCF)                                                 C
    //  See above

    //  SUBTRACT/ADD                                                        N
    CLEAR_FLAG_N( );

    //  PARITY/OVERFLOW                                                     P/V
    // P/V is not affected.

    //  HALF CARRY                                                          H
    CLEAR_FLAG_H( );

    //  ZERO                                                                Z
    // Z is not affected.

    //  SIGN                                                                S
    // S is not affected.

    //  Set the number of states for this instruction
    operation_rc.states =   4;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  RRCA                205        00001111
 *  RRC                 4-10
 *
 *  The contents of the Accumulator (Register A) are rotated right 1 bit
 *  position. Bit 0 is copied to the Carry flag and also to bit 7. Bit 0 is
 *  the least-significant bit.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
shift_rrca_i80(
    uint8_t                     op_code
    )
{
    /**
     *  @param  data                Shift data                              */
    int                         data;

    //  Get data from the accumulator
    data = GET_A( );

    //  Cary to bit 0
    if ( ( data & 0x0001 ) != 0 )
    {
        data |= 0x0100;
        SET_FLAG_C( );
    }
    else
    {
        CLEAR_FLAG_C( );
    }

    //  Left shift
    data = data >> 1;

    PUT_A( (uint8_t)data );

    /************************************************************************
     *  SET FLAGS
     ************************************************************************/

    //  Carry         (CCF)                                                 C
    //  See above

    //  SUBTRACT/ADD                                                        N
    CLEAR_FLAG_N( );

    //  PARITY/OVERFLOW                                                     P/V
    // P/V is not affected.

    //  HALF CARRY                                                          H
    CLEAR_FLAG_H( );

    //  ZERO                                                                Z
    // Z is not affected.

    //  SIGN                                                                S
    // S is not affected.

    //  Set the number of states for this instruction
    operation_rc.states =   4;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  RRA                 207        00011111
 *  RRA                 4-10
 *
 *  The contents of the Accumulator (Register A) are rotated left 1 bit position
 *  through the Carry flag. The previous contents of the Carry flag are copied
 *  to bit 0. Bit 0 is the least significant bit.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
shift_rra_i80(
    uint8_t                     op_code
    )
{
    /**
     *  @param  data                Shift data                              */
    int                         data;

    //  Get data from the accumulator
    data = GET_A( );

    //  Insert the cary flag into the LSB
    if ( ( GET_F( ) & CPU_FLAG_C ) != 0 )
        data |= 0x0100;

    //  Cary to bit 0
    if ( data & 0x0001 )
    {
        SET_FLAG_C( );
    }
    else
    {
        CLEAR_FLAG_C( );
    }

    //  Left shift
    data = data >> 1;

    PUT_A( (uint8_t)data );

    /************************************************************************
     *  SET FLAGS
     ************************************************************************/

    //  Carry         (CCF)                                                 C
    //  See above

    //  SUBTRACT/ADD                                                        N
    CLEAR_FLAG_N( );

    //  PARITY/OVERFLOW                                                     P/V
    // P/V is not affected.

    //  HALF CARRY                                                          H
    CLEAR_FLAG_H( );

    //  ZERO                                                                Z
    // Z is not affected.

    //  SIGN                                                                S
    // S is not affected.

    //  Set the number of states for this instruction
    operation_rc.states =   4;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  RRD                 240     ED 01100111
 *
 *  The contents of the low-order four bits (bits 3, 2, 1, and 0) of memory
 *  location (HL) are copied to the low-order four bits of the Accumulator
 *  (Register A). The previous contents of the low-order four bits of the
 *  Accumulator are copied to the high-order four bits (7, 6, 5, and 4) of
 *  location (HL); and the previous contents of the high-order four bits of
 *  (HL) are copied to the low-order four bits of (HL). The contents of the
 *  high-order bits of the Accumulator are unaffected.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      S is set if the Accumulator is negative after an operation; otherwise, it is reset.
 *      Z is set if the Accumulator is 0 after an operation; otherwise, it is reset.
 *      H is reset
 *      P/V is set if the parity of the Accumulator is even after an operation; otherwise, it is reset.
 *      N is reset.
 *      C is not affected.
 *
 ****************************************************************************/

void
shift_rrd_ED(
    uint8_t                     op_code
    )
{
    /**
     *  @param  tmp_a           Initial A                                   */
    uint8_t                     tmp_a;
    /**
     *  @param  tmp_hl          Initial (HL)                                */
    uint8_t                     tmp_hl;

    //  Get initial data values
    tmp_a = GET_A( );
    tmp_hl = memory_get_8( CPU_REG_HL );

    //  Move everything around
    PUT_A( ( ( tmp_a & 0xF0 ) | ( tmp_hl & 0x0F ) ) );

    uint8_t data_h, data_l;
    memory_put_8( CPU_REG_HL, (   ( ( tmp_hl & 0xF0 ) >> 4 )
                                | ( ( tmp_a & 0x0F )  << 4 ) ) );

    /************************************************************************
     *  SET FLAGS
     ************************************************************************/

    //  Carry
    // C is not affected.

    //  SUBTRACT/ADD
    CLEAR_FLAG_N( );

    //  PARITY/OVERFLOW
    if ( parity_8( GET_A( ) & 0x00FF ) == 0 )
        CLEAR_FLAG_PV( );       //  Parity Even
    else
        SET_FLAG_PV( );         //  Parity Odd

    //  HALF CARRY
    CLEAR_FLAG_H( );

    //  ZERO
    if( GET_A( ) == 0 )
        SET_FLAG_H( );
    else
        CLEAR_FLAG_H( );

    //  SIGN
    if ( ( GET_A( ) & 0x0080 ) == 0x80 )
        SET_FLAG_S( );
    else
        CLEAR_FLAG_S( );

    //  Set the number of states for this instruction
    operation_rc.states =  18;
}
/****************************************************************************/