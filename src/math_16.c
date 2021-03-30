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
#include "math_16.h"            //  16 bit Arithmatic instrucions.
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
 *
 *  Add the contents of 'addend' to 'augend' plus the value of 'carry'.
 *
 *  @param  addend              Number to be added
 *  @param  augend              Number to be added
 *  @param  carry               '1' = Carry, '0' = No carry
 *
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      Condition Bits Affected
 *          S is not affected.
 *          Z is not affected.
 *          H is set if carry from bit 11; otherwise, it is reset.
 *          P/V is not affected.
 *          N is reset.
 *          C is set if carry from bit 15; otherwise, it is reset.
 *
 ****************************************************************************/

static
uint16_t
add_16(
    uint32_t                    addend,
    uint32_t                    augend,
    uint32_t                    carry
    )
{
    /**
     *  @param  sum                 The sum of the add operation            */
    uint32_t                    sum;
    /**
     *  @param  half                Half carry difference                   */
    uint16_t                    half;

    //  sum = addend + augend + carry
    sum = (uint32_t)addend + (uint32_t)augend + (uint32_t)carry;

    /************************************************************************
     *  SET FLAGS
     ************************************************************************/

    //  Carry
    if ( ( sum & 0x00010000 ) == 0x00010000 )
        SET_FLAG_C( );
    else
        CLEAR_FLAG_C( );

    //  SUBTRACT/ADD
    CLEAR_FLAG_N( );

    //  PARITY/OVERFLOW
    // P/V is not affected.

    //  HALF CARRY
    half = ( ( addend & 0x0FFF ) + ( augend & 0x0FFF ) + carry );
    if ( ( half & 0x0100 ) == 0x0100 )
        SET_FLAG_H( );
    else
        CLEAR_FLAG_H( );

    //  ZERO
    // Z is not affected.

    //  SIGN
    // S is not affected.

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    return( (uint16_t)sum );
}

/****************************************************************************/
/**
 *  Subtract the contents of 'subtrahend' from the 'minuend' minus the value
 *  of 'borrow'.
 *
 *  @param  minuend              Number to be added
 *  @param  subtrahend              Number to be added
 *  @param  borrow               '1' = Carry, '0' = No borrow
 *
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      Condition Bits Affected
 *          S is set if result is negative; otherwise, it is reset.
 *          Z is set if result is 0; otherwise, it is reset.
 *          H is set if borrow from bit 12; otherwise, it is reset.
 *          P/V is set if overflow; otherwise, it is reset.
 *          N is set.
 *          C is set if borrow; otherwise, it is reset.
 *
 ****************************************************************************/

static
uint16_t
sub_16(
    uint32_t                    minuend,
    uint32_t                    subtrahend,
    uint32_t                    borrow
    )
{
    /**
     *  @param  difference          The difference of the add operation     */
    uint32_t                    difference;
    /**
     *  @param  half                Half carry difference                   */
    uint16_t                    half;

    //  difference = minuend - subtrahend - borrow
    difference = (uint16_t)minuend - (uint16_t)subtrahend - (uint16_t)borrow;

    /************************************************************************
     *  SET FLAGS
     ************************************************************************/

    //  Carry
    if ( ( difference & 0x00010000 ) == 0x00010000 )
        SET_FLAG_C( );
    else
        CLEAR_FLAG_C( );

    //  SUBTRACT/ADD
    SET_FLAG_N( );

    //  PARITY/OVERFLOW
    if (    ( ( minuend  & 0x8000 ) != ( subtrahend & 0x8000 ) )
         && ( difference & 0x8000 ) != ( minuend    & 0x8000 ) )
        SET_FLAG_PV( );
    else
        CLEAR_FLAG_PV( );

    //  HALF CARRY
    half = ( ( minuend & 0x00FF ) - ( subtrahend & 0x00FF ) - borrow );
    if ( ( half & 0x00010000 ) == 0x00010000 )
        SET_FLAG_H( );
    else
        CLEAR_FLAG_H( );

    //  ZERO
    if ( ( difference & 0xFFFF ) == 0x00 )
        SET_FLAG_Z( );
    else
        CLEAR_FLAG_Z( );

    //  SIGN
    if ( ( difference & 0x8000 ) == 0x8000 )
        SET_FLAG_S( );
    else
        CLEAR_FLAG_S( );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    return( (uint16_t)difference );
}

/****************************************************************************
 * MAIN
 ****************************************************************************/

/****************************************************************************/
/**                     Page        Op-Code
 *  ADD  HL, ss          188        00ss1001
 *  DAD  rp              4-8
 *
 *  The contents of register pair ss (any of register pairs BC, DE, HL, or SP)
 *  are added to the contents of register pair HL and the result is stored in HL.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
math_addhlss_i80(
    uint8_t                     op_code
    )
{
    //  ADD  HL, ss
    CPU_REG_HL = ( add_16( (uint32_t)CPU_REG_HL, (uint32_t)reg_get_ss( op_code ), 0 ) );

    //  Set the number of states for this instruction
    operation_rc.states =  11;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  INC  ss              198        00ss0011
 *  INX  rp              4-8
 *
 *  The contents of register pair ss (any of register pairs BC, DE, HL, or SP)
 *  are incremented.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
math_incss_i80(
    uint8_t                     op_code
    )
{
    //  INC  ss
    reg_put_ss( op_code, ( reg_get_ss( op_code ) + 1 ) );

    //  Set the number of states for this instruction
    operation_rc.states =   6;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  INC  ss              201        00ss1011
 *  DCX  rp              4-8
 *
 *  The contents of register pair ss (any of the register pairs BC, DE, HL, or
 *  SP) are decremented.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
math_decss_i80(
    uint8_t                     op_code
    )
{
    //  INC  ss
    reg_put_ss( op_code, ( reg_get_ss( op_code ) - 1 ) );

    //  Set the number of states for this instruction
    operation_rc.states =   6;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  ADC  HL, ss          190     ED 01ss1010
 *
 *  The contents of register pair ss (any of register pairs BC, DE, HL, or SP)
 *  are added with the Carry flag (C flag in the F Register) to the contents of
 *  register pair HL, and the result is stored in HL.
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
math_adchlss_ED(
    uint8_t                     op_code
    )
{
    //  ADC  HL, ss
    CPU_REG_HL = add_16( CPU_REG_HL, reg_get_ss( op_code ), GET_FLAG_C( ) );

    //  Set the number of states for this instruction
    operation_rc.states =  15;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  SBC  HL, ss          192     ED 01ss0010
 *
 *  The contents of the register pair ss (any of register pairs BC, DE, HL, or
 *  SP) and the Carry Flag (C flag in the F Register) are subtracted from the
 *  contents of register pair HL, and the result is stored in HL.
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
math_sbchlss_ED(
    uint8_t                     op_code
    )
{
    //  SBC  HL, ss
    CPU_REG_HL = sub_16( CPU_REG_HL, reg_get_ss( op_code ), GET_FLAG_C( ) );

    //  Set the number of states for this instruction
    operation_rc.states =  15;
}
/****************************************************************************/