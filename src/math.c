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
#include "math.h"               //  8 bit instrucions.
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
 *          S is set if result is negative; else, it is reset.
 *          Z is set if result is 0; else, it is reset.
 *          H is set if carry from bit 3; else, it is reset.
 *          P/V is set if overflow; else, it is reset.
 *          N is reset.
 *          C is set if carry from bit 7; else, it is reset.
 *
 ****************************************************************************/

uint8_t
add_8(
    uint16_t                    addend,
    uint16_t                    augend,
    uint16_t                    carry
    )
{
    /**
     *  @param  sum                 The sum of the add operation            */
    uint16_t                    sum;
    /**
     *  @param  half                Half carry difference                   */
    uint8_t                     half;

    //  sum = addend + augend + carry
    sum = (uint16_t)addend + (uint16_t)augend + (uint16_t)carry;

    /************************************************************************
     *  SET FLAGS
     ************************************************************************/

    //  Carry
    if ( ( sum & 0x0100 ) == 0x0100 ) SET_FLAG_C( ); else CLEAR_FLAG_C( );

    //  SUBTRACT/ADD
    CLEAR_FLAG_N( );

    //  Are we running Intel 8080 mode ?
    if ( CPU == CPU_I80 )
    {
        //  YES:    Set the 'PARITY' flag
        if ( parity_8( sum & 0x00FF ) == 0 )
            CLEAR_FLAG_PV( );       //  Parity Even
        else
            SET_FLAG_PV( );         //  Parity Odd
    }
    else
    {
        //  NO:     PARITY/OVERFLOW
        if (    ( ( addend & 0x80 ) == ( augend & 0x80 ) )
             && (      sum & 0x80 ) != ( addend & 0x80 ) )
            SET_FLAG_PV( );
        else
            CLEAR_FLAG_PV( );
    }

    //  HALF CARRY
    half = ( ( addend & 0x0F ) + ( augend & 0x0F ) + carry );
    if ( ( half & 0x10 ) == 0x10 )
        SET_FLAG_H( );
    else
        CLEAR_FLAG_H( );

    //  ZERO
    if ( ( sum & 0x00FF ) == 0x00 )
        SET_FLAG_Z( );
    else
        CLEAR_FLAG_Z( );

    //  SIGN
    if ( ( sum & 0x0080 ) == 0x80 )
        SET_FLAG_S( );
    else
        CLEAR_FLAG_S( );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    return( (uint8_t)sum );
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
 *          S is set if result is negative; else, it is reset.
 *          Z is set if result is 0; else, it is reset.
 *          H is set if borrow from bit 3; else, it is reset.
 *          P/V is set if overflow; else, it is reset.
 *          N is reset.
 *          C is set if borrow from bit 7; else, it is reset.
 *
 ****************************************************************************/

uint8_t
sub_8(
    uint16_t                    minuend,
    uint16_t                    subtrahend,
    uint16_t                    borrow
    )
{
    /**
     *  @param  difference          The difference of the add operation     */
    uint16_t                    difference;
    /**
     *  @param  half                Half carry difference                   */
    uint8_t                     half;

    //  difference = minuend - subtrahend - borrow
    difference = (uint16_t)minuend - (uint16_t)subtrahend - (uint16_t)borrow;

    /************************************************************************
     *  SET FLAGS
     ************************************************************************/

    //  Carry
    if ( ( difference & 0x0100 ) == 0x0100 )
        SET_FLAG_C( );
    else
        CLEAR_FLAG_C( );

    //  SUBTRACT/ADD
    SET_FLAG_N( );

    //  Are we running Intel 8080 mode ?
    if ( CPU == CPU_I80 )
    {
        //  YES:    Set the 'PARITY' flag
        if ( parity_8( difference & 0x00FF ) == 0 )
            CLEAR_FLAG_PV( );       //  Parity Even
        else
            SET_FLAG_PV( );         //  Parity Odd
    }
    else
    {
        //  NO:     PARITY/OVERFLOW
        if (    ( ( minuend  & 0x80 ) != ( subtrahend & 0x80 ) )
             && ( difference & 0x80 ) != ( minuend    & 0x80 ) )
            SET_FLAG_PV( );
        else
            CLEAR_FLAG_PV( );
    }

    //  HALF CARRY
    half = ( ( minuend & 0x0F ) - ( subtrahend & 0x0F ) - borrow );
    if ( ( half & 0x10 ) == 0x10 )
        SET_FLAG_H( );
    else
        CLEAR_FLAG_H( );

    //  ZERO
    if ( ( difference & 0x00FF ) == 0x00 )
        SET_FLAG_Z( );
    else
        CLEAR_FLAG_Z( );

    //  SIGN
    if ( ( difference & 0x0080 ) == 0x0080 )
        SET_FLAG_S( );
    else
        CLEAR_FLAG_S( );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    return( (uint8_t)difference );
}

/****************************************************************************/
/**
 *
 *  Increment the contents of 'number'.
 *
 *  @param  number              Number to be incremented
 *
 *
 *  @return sum                 = ( number + 1 )
 *
 *  @note
 *      Condition Bits Affected
 *          S is set if result is negative; else, it is reset.
 *          Z is set if result is 0; else, it is reset.
 *          H is set if carry from bit 3; else, it is reset.
 *          P/V is set if (number) was 7Fh before operation; else, it is reset.
 *          N is reset.
 *          C is not affected.
 *
 ****************************************************************************/

uint8_t
inc_8(
    uint16_t                    number
    )
{
    /**
     *  @param  sum                 The sum of the add operation            */
    uint16_t                    sum;

    //  Create 16 bit signed numbers
    if ( number > 127 ) number |= 0xFF00;

    //  sum = addend + augend + carry
    sum = (uint16_t)number + 1;

    /************************************************************************
     *  SET FLAGS
     ************************************************************************/

    //  Carry
    //          The carry flag is not effected by this instruction.

    //  SUBTRACT/ADD
    CLEAR_FLAG_N( );

    //  Are we running Intel 8080 mode ?
    if ( CPU == CPU_I80 )
    {
        //  YES:    Set the 'PARITY' flag
        if ( parity_8( sum & 0x00FF ) == 0 )
            CLEAR_FLAG_PV( );       //  Parity Even
        else
            SET_FLAG_PV( );         //  Parity Odd
    }
    else
    {
        //  NO:     PARITY/OVERFLOW
        if ( number == 0x7F )
            SET_FLAG_PV( );
        else
            CLEAR_FLAG_PV( );
    }

    //  HALF CARRY
    if ( number & 0x0F == 0x0F )
        SET_FLAG_H( );
    else
        CLEAR_FLAG_H( );

    //  ZERO
    if ( ( sum & 0x00FF ) == 0x0000 )
        SET_FLAG_Z( );
    else
        CLEAR_FLAG_Z( );

    //  SIGN
    if ( ( sum & 0x0080 ) == 0x0080 )
        SET_FLAG_S( );
    else
        CLEAR_FLAG_S( );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    return( (uint8_t)sum );
}

/****************************************************************************/
/**
 *
 *  Decrement the contents of 'number'.
 *
 *  @param  number              Number to be decremented
 *
 *
 *  @return sum                 = ( number - 1 )
 *
 *  @note
 *      Condition Bits Affected
 *          S is set if result is negative; else, it is reset.
 *          Z is set if result is 0; else, it is reset.
 *          H is set if borrow from bit 4, else, it is reset.
 *          P/V is set if (number) was 80h before operation; else, it is reset.
 *          N is set.
 *          C is not affected.
 *
 ****************************************************************************/

uint8_t
dec_8(
    uint16_t                    number
    )
{
    /**
     *  @param  sum                 The sum of the add operation            */
    uint16_t                    difference;

    //  Create 16 bit signed numbers
    if ( number > 127 ) number |= 0xFF00;

    //  sum = addend + augend + carry
    difference = (uint16_t)number - 1;

    /************************************************************************
     *  SET FLAGS
     ************************************************************************/

    //  Carry
    //          The carry flag is not effected by this instruction.

    //  SUBTRACT/ADD
    SET_FLAG_N( );

    //  PARITY/OVERFLOW
    if ( number == 0x80 )
        SET_FLAG_PV( );
    else
        CLEAR_FLAG_PV( );

    //  HALF CARRY
    if ( number & 0x1F == 0x1F )
        SET_FLAG_H( );
    else
        CLEAR_FLAG_H( );

    //  ZERO
    if ( ( difference & 0x00FF ) == 0x0000 )
        SET_FLAG_Z( );
    else
        CLEAR_FLAG_Z( );

    //  SIGN
    if ( ( difference & 0x0080 ) == 0x0080 )
        SET_FLAG_S( );
    else
        CLEAR_FLAG_S( );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    return( (uint8_t)difference );
}

/****************************************************************************
 * MAIN
 ****************************************************************************/

/****************************************************************************/
/**                     Page        Op-Code
 *  ADD  A, r            145        10000sss
 *  ADD  r               4-6
 *
 *  The contents of register r are added to the contents of the Accumulator,
 *  and the result is stored in the Accumulator. The r symbol identifies the
 *  registers A, B, C, D, E, H, or L.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      Condition Bits Affected
 *          S is set if result is negative; else, it is reset.
 *          Z is set if result is 0; else, it is reset.
 *          H is set if carry from bit 3; else, it is reset.
 *          P/V is set if overflow; else, it is reset.
 *          N is reset.
 *          C is set if carry from bit 7; else, it is reset.
 *
 ****************************************************************************/

void
math_addr_i80(
    uint8_t                     op_code
    )
{
    //  ADD  A, r
    PUT_A( add_8( reg_get_sr( op_code ), GET_A( ), 0 ) );

    //  Set the number of states for this instruction
    operation_rc.states =   4;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  ADD  A, n            147        11000110 nnnnnnnn
 *  ADI  n               4-6
 *
 *  The n integer is added to the contents of the Accumulator, and the results
 *  are stored in the Accumulator.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      Condition Bits Affected
 *          S is set if result is negative; else, it is reset.
 *          Z is set if result is 0; else, it is reset.
 *          H is set if carry from bit 3; else, it is reset.
 *          P/V is set if overflow; else, it is reset.
 *          N is reset.
 *          C is set if carry from bit 7; else, it is reset.
 *
 ****************************************************************************/

void
math_addn_i80(
    uint8_t                     op_code
    )
{
    //  ADD  A, n
    PUT_A( add_8( memory_get_8( CPU_REG_PC++ ), GET_A( ), 0 ) );

    //  Set the number of states for this instruction
    operation_rc.states =   7;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  ADD  A, (HL)         148       10000110
 *  ADD  r               4-6
 *
 *  The byte at the memory address specified by the contents of the HL register
 *  pair is added to the contents of the Accumulator, and the result is stored
 *  in the Accumulator.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      Condition Bits Affected
 *          S is set if result is negative; else, it is reset.
 *          Z is set if result is 0; else, it is reset.
 *          H is set if carry from bit 3; else, it is reset.
 *          P/V is set if overflow; else, it is reset.
 *          N is reset.
 *          C is set if carry from bit 7; else, it is reset.
 *
 ****************************************************************************/

void
math_addhl_i80(
    uint8_t                     op_code
    )
{
    //  ADD  A, HL
    PUT_A( add_8( memory_get_8( CPU_REG_HL ), GET_A( ), 0 ) );

    //  Set the number of states for this instruction
    operation_rc.states =   7;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  ADC  A, r            151        10001sss
 *  ADC  r               4-6
 *
 *  The contents of register r are added to the contents of the Accumulator,
 *  with the Carry Flag and the result is stored in the Accumulator. The r
 *  symbol identifies the registers A, B, C, D, E, H, or L.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      Condition Bits Affected
 *          S is set if result is negative; else, it is reset.
 *          Z is set if result is 0; else, it is reset.
 *          H is set if carry from bit 3; else, it is reset.
 *          P/V is set if overflow; else, it is reset.
 *          N is reset.
 *          C is set if carry from bit 7; else, it is reset.
 *
 ****************************************************************************/

void
math_adcr_i80(
    uint8_t                     op_code
    )
{
    //  ADD  A, r
    PUT_A( add_8( reg_get_sr( op_code ), GET_A( ), GET_FLAG_C( ) ) );

    //  Set the number of states for this instruction
    operation_rc.states =   4;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  ADC  A, n            147        11000110 nnnnnnnn
 *  ADI  n               4-6
 *
 *  The n integer is added to the contents of the Accumulator with the Carry
 *  Flag, and the results are stored in the Accumulator.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      Condition Bits Affected
 *          S is set if result is negative; else, it is reset.
 *          Z is set if result is 0; else, it is reset.
 *          H is set if carry from bit 3; else, it is reset.
 *          P/V is set if overflow; else, it is reset.
 *          N is reset.
 *          C is set if carry from bit 7; else, it is reset.
 *
 ****************************************************************************/

void
math_adcn_i80(
    uint8_t                     op_code
    )
{
    //  ADD  A, n
    PUT_A( add_8( memory_get_8( CPU_REG_PC++ ), GET_A( ), GET_FLAG_C( ) ) );

    //  Set the number of states for this instruction
    operation_rc.states =   7;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  ADC  A, (HL)         148       10000110
 *  SUB  M               4-6
 *
 *  The byte at the memory address specified by the contents of the HL register
 *  pair is added to the contents of the Accumulator with the Carry Flag, and
 *  the result is stored in the Accumulator.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      Condition Bits Affected
 *          S is set if result is negative; else, it is reset.
 *          Z is set if result is 0; else, it is reset.
 *          H is set if carry from bit 3; else, it is reset.
 *          P/V is set if overflow; else, it is reset.
 *          N is reset.
 *          C is set if carry from bit 7; else, it is reset.
 *
 ****************************************************************************/

void
math_adchl_i80(
    uint8_t                     op_code
    )
{
    //  ADD  A, HL
    PUT_A( add_8( memory_get_8( CPU_REG_HL ), GET_A( ), GET_FLAG_C( ) ) );

    //  Set the number of states for this instruction
    operation_rc.states =   7;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  SUB  A, r            153        10010sss
 *  SUB  r               4-6
 *
 *  The contents of register r are subtracted from the contents of the
 *  Accumulator, and the result is stored in the Accumulator. The r symbol
 *  identifies the registers A, B, C, D, E, H, or L.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
math_subr_i80(
    uint8_t                     op_code
    )
{
    //  SUB  A, r
    PUT_A( sub_8( GET_A( ), reg_get_sr( op_code ), 0 ) );

    //  Set the number of states for this instruction
    operation_rc.states =   4;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  SUB  A, n            153        11010110 nnnnnnnn
 *  SBI  n               4-7
 *
 *  The n integer is subtracted from the contents of the Accumulator, and the
 *  results are stored in the Accumulator.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
math_subn_i80(
    uint8_t                     op_code
    )
{
    //  SUB  A, n
    PUT_A( sub_8( GET_A( ), memory_get_8( CPU_REG_PC++ ), 0 ) );

    //  Set the number of states for this instruction
    operation_rc.states =   7;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  ADD  A, (HL)         153       10010110
 *  ADD  M               4-7
 *
 *  The byte at the memory address specified by the contents of the HL register
 *  pair is subtracted from the contents of the Accumulator, and the result
 *  is stored in the Accumulator.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
math_subhl_i80(
    uint8_t                     op_code
    )
{
    //  SUB  A, HL
    PUT_A( sub_8( GET_A( ), memory_get_8( CPU_REG_HL ), 0 ) );

    //  Set the number of states for this instruction
    operation_rc.states =   7;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  SBC  A, r            153        10011sss
 *  SBB  r               4-7
 *
 *  The contents of register r are subtracted from the contents of the
 *  Accumulator, with the Carry Flag and the result is stored in the
 *  Accumulator. The r symbol identifies the registers A, B, C, D, E, H, or L.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
math_sbcr_i80(
    uint8_t                     op_code
    )
{
    //  SBC  A, r
    PUT_A( sub_8( GET_A( ), reg_get_sr( op_code ), GET_FLAG_C( ) ) );

    //  Set the number of states for this instruction
    operation_rc.states =   4;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  SBC  A, n            147        11000110 nnnnnnnn
 *  SBI  n               4-6
 *
 *  The n integer is subtracted from the contents of the Accumulator with the
 *  Carry Flag, and the results are stored in the Accumulator.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
math_sbcn_i80(
    uint8_t                     op_code
    )
{
    //  SBC  A, n
    PUT_A( sub_8( GET_A( ), memory_get_8( CPU_REG_PC++ ), GET_FLAG_C( ) ) );

    //  Set the number of states for this instruction
    operation_rc.states =   7;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  ADC  A, (HL)         153        10010110
 *  SBB  M               4-6
 *
 *  The byte at the memory address specified by the contents of the HL register
 *  pair is subtracted from the contents of the Accumulator with the Carry Flag,
 *  and the result is stored in the Accumulator.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
math_sbchl_i80(
    uint8_t                     op_code
    )
{
    //  SBC  A, HL
    PUT_A( sub_8( GET_A( ), memory_get_8( CPU_REG_HL ), GET_FLAG_C( ) ) );

    //  Set the number of states for this instruction
    operation_rc.states =   7;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  INC  r               165        00ddd100
 *  INR  r               4-7
 *
 *  Register r is incremented and register r identifies any of the registers A,
 *  B, C, D, E, H, or L.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
math_incr_i80(
    uint8_t                     op_code
    )
{
    //  SBC  A, r
    reg_put_dr( op_code, inc_8( reg_get_dr( op_code ) ) );

    //  Set the number of states for this instruction
    operation_rc.states =   4;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  INC  (HL)            167        10110100
 *  INR  M               4-7
 *
 *  The byte contained in the address specified by the contents of the HL
 *  register pair is incremented.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
math_inchl_i80(
    uint8_t                     op_code
    )
{
    //  SBC  A, HL
    memory_put_8( CPU_REG_HL, ( inc_8( memory_get_8( CPU_REG_HL ) ) ) );

    //  Set the number of states for this instruction
    operation_rc.states =  11;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  DEC  r               170        00ddd101
 *  DCR  r               4-7
 *
 *  Register r is decremented and register r identifies any of the registers A,
 *  B, C, D, E, H, or L.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
math_decr_r80(
    uint8_t                     op_code
    )
{
    //  SBC  A, r
    reg_put_dr( op_code, dec_8( reg_get_dr( op_code ) ) );

    //  Set the number of states for this instruction
    operation_rc.states =   4;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  DEC  (HL)            170        10110101
 *  DCR  M               4-8
 *
 *  The byte contained in the address specified by the contents of the HL
 *  register pair is decremented.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
math_dechl_i80(
    uint8_t                     op_code
    )
{
    //  SBC  A, HL
    memory_put_8( CPU_REG_HL, ( dec_8( memory_get_8( CPU_REG_HL ) ) ) );

    //  Set the number of states for this instruction
    operation_rc.states =  11;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  DAA                  173        00100111
 *  DAA                  4-8
 *
 *  If the least significant four bits of the accumulator represents a number
 *  greater than 9, or if the Auxiliary Carry bit is equal to one, the
 *  accumulator is incremented by six. Otherwise, no incrementing occurs.
 *
 *  If the most significant four bits of the accumulator now represent a number
 *  greater than 9, or if the normal carry bit is equal to one, the most
 *  significant four bits of the accumulator are incremented by six.
 *  Otherwise, no incrementing occurs.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
math_daa_good(
    uint8_t                     op_code
    )
{
    unsigned int    daa_o, daa_oh, daa_ol;
    unsigned int    my_h, my_c;

    daa_o  = GET_A( );
    daa_ol = GET_A( ) & 0x0F;
    daa_oh = GET_A( ) & 0xF0;

    if( daa_ol  > 9 )
    {
        daa_ol += 6;
        my_h = 1;
    }
    else
    if( GET_FLAG_H( ) == 1 && daa_ol <= 3 )
    {
        daa_ol += 6;
    }

    //  Back to a four bit value
    daa_ol &= 0x0F;

    if( my_h == 1 )
        daa_oh += 0x10;

    if( daa_oh > 0x90 )
    {
        daa_oh += 0x60;
        my_c = 1;
    }
    else
    if( GET_FLAG_C( ) == 1 && daa_oh <= 0x30 )
    {
        daa_oh += 0x60;
        my_c = 1;
    }

    //  Set or clear the real flags
    if( my_h == 1 ) SET_FLAG_H( ); else CLEAR_FLAG_H( );
    if( my_c == 1 ) SET_FLAG_C( ); else CLEAR_FLAG_C( );
    CLEAR_FLAG_N( );

    //  Set the 'PARITY' flag
    if ( parity_8( GET_A( ) & 0x00FF ) == 0 )
        CLEAR_FLAG_PV( );       //  Parity Even
    else
        SET_FLAG_PV( );         //  Parity Odd

    //  ZERO
    if( GET_A( ) & 0x00FF ) SET_FLAG_Z( ); else CLEAR_FLAG_Z( );

    //  SIGN
    if ( GET_A( ) & 0x0080 ) SET_FLAG_S( ); else CLEAR_FLAG_S( );
}

/****************************************************************************/
/**                     Page        Op-Code
 *  DAA                  173        00100111
 *  DAA                  4-8
 *
 *  If the least significant four bits of the accumulator represents a number
 *  greater than 9, or if the Auxiliary Carry bit is equal to one, the
 *  accumulator is incremented by six. Otherwise, no incrementing occurs.
 *
 *  If the most significant four bits of the accumulator now represent a number
 *  greater than 9, or if the normal carry bit is equal to one, the most
 *  significant four bits of the accumulator are incremented by six.
 *  Otherwise, no incrementing occurs.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
math_daa_i80(
    uint8_t                     op_code
    )
{
    /**
     *  @param  tmp_a_l4        Low nibble of REG-A                         */
    uint16_t                    tmp_a_l4;
    /**
     *  @param  tmp_a_h4        Upper nibble of REG-A                       */
    uint16_t                    tmp_a_h4;
    /**
     *  @param  sum                 The sum of the add operation            */
    uint8_t                     sum;

    //  Copy Reg-A
    tmp_a_l4 = GET_A( ) & 0x0F;
    tmp_a_h4 = GET_A( ) & 0xF0;

    //  Is the lower nibble greater than 9
    //      or the half carry flag set
    if(    ( tmp_a_l4         > 9 )
        || ( GET_FLAG_H( )   != 0 ) )
    {
        //  YES:    Add six to the low nibble
        tmp_a_l4 += 6;

        //  Do we have to set the half carry flag ?
        if( tmp_a_l4 > 0x0F )
        {
            //  YES:    Set half carry and increment the upper nibble
            SET_FLAG_H( );
            tmp_a_h4 += 0x10;
        }
        else
        {
            //  NO:     Clear the half carry flag
            CLEAR_FLAG_H( );
        }
    }


    //  Is the upper nibble greater than 9
    //      or the      carry flag set
    if(    ( tmp_a_h4         > 0x90 )
        || ( GET_FLAG_C( )    !=   0 ) )
    {
        //  YES:    Add nine to the low nibble
        tmp_a_h4 += 0x60;

        //  Do we have to set the half carry flag ?
        if( tmp_a_h4 > 0xFF )
            SET_FLAG_C( );
        else
            CLEAR_FLAG_C( );
    }

    sum  = ( tmp_a_l4 & 0x0F );
    sum |=   tmp_a_h4;

    //  Save the result back in register A
    PUT_A( sum );

    uint16_t bar = GET_A( );

    //  SUBTRACT/ADD
    CLEAR_FLAG_N( );

    //  YES:    Set the 'PARITY' flag
    if ( parity_8( GET_A( ) & 0x00FF ) == 0 )
        CLEAR_FLAG_PV( );       //  Parity Even
    else
        SET_FLAG_PV( );         //  Parity Odd

    //  ZERO
    if ( ( GET_A( ) & 0x00FF ) == 0x00 )
        SET_FLAG_Z( );
    else
        CLEAR_FLAG_Z( );

    //  SIGN
    if ( ( GET_A( ) & 0x0080 ) == 0x80 )
        SET_FLAG_S( );
    else
        CLEAR_FLAG_S( );

    //  Set the number of states for this instruction
    operation_rc.states =  11;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  DAA                  173        00100111
 *  DAA                  4-8
 *
 *  This instruction conditionally adjusts the Accumulator for BCD addition
 *  and subtraction operations.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *          N  Carry(in)  Bits 7-4  Half-Carry   Bits 3-0     ADD     Carry(out)
 *      01  0    0           0-9        0          0-9         00        0
 *      02  0    0           0-8        0          A-F         06        0
 *      03  0    0           0-9        1          0-3         06        0
 *      04  0    0           A-F        0          0-9         60        1
 *      05  0    0           9-F        0          A-F         66        1
 *      06  0    0           A-F        1          0-3         66        1
 *      07  0    1           0-2        0          0-9         60        1
 *      08  0    1           0-2        0          A-F         66        1
 *      09  0    1           0-3        1          0-3         66        1
 *      10  1    0           0-9        0          0-9         00        0
 *      11  1    0           0-8        1          6-F         FA        0
 *      12  1    1           7-F        0          0-9         A0        1
 *      13  1    1           6-F        1          6-F         9A        1
 *
 ****************************************************************************/

void
math_daa_z80(
    uint8_t                     op_code
    )
{
    /**
     *  @param  reg_a               The current value of register A         */
    uint16_t                    reg_a;
    /**
     *  @param  reg_f               The current value of register F         */
    uint16_t                    reg_f;

    //  Get local copies of register A and F.
    reg_a = GET_A( );
    reg_f = GET_F( );

    //  Was the previous arithmetic instruction ADDITION ?
    if ( ( reg_f & CPU_FLAG_N ) == 0 )
    {
        //  YES:    ADDITION
        //  1       0   0-9     0   0-9     00      0
        if (    ( ( reg_f & CPU_FLAG_C ) ==    0 )      //  C = 0
             && ( ( reg_a &       0xF0 ) <= 0x90 )      //  7-4     0-9
             && ( ( reg_f & CPU_FLAG_H ) ==    0 )      //  H = 0
             && ( ( reg_a &       0x0F ) <= 0x09 ) )    //  3-0     0-9
        {
            //  Nothing to do here
            reg_a = reg_a;  //  For debug.
        }
        //  2       0   0-8     0   A-F     06      0
        else
        if (    ( ( reg_f & CPU_FLAG_C ) ==    0 )      //  C = 0
             && ( ( reg_a &       0xF0 ) <= 0x80 )      //  7-4     0-8
             && ( ( reg_f & CPU_FLAG_H ) ==    0 )      //  H = 0
             && ( ( reg_a &       0x0F ) >= 0x0A ) )    //  3-0     A-F
        {
            //  Adjust register A by adding 0x06
            reg_a += 0x06;
        }
        //  3       0   0-9     1   0-3     06      0
        else
        if (    ( ( reg_f & CPU_FLAG_C ) ==    0 )      //  C = 0
             && ( ( reg_a &       0xF0 ) <= 0x90 )      //  7-4     0-9
             && ( ( reg_f & CPU_FLAG_H ) !=    0 )      //  H = 1
             && ( ( reg_a &       0x0F ) <= 0x03 ) )    //  3-0     0-3
        {
            //  Adjust register A by adding 0x06
            reg_a += 0x06;
        }
        //  4       0   A-F     0   0-9     60      1
        else
        if (    ( ( reg_f & CPU_FLAG_C ) ==    0 )      //  C = 0
             && ( ( reg_a &       0xF0 ) >= 0xA0 )      //  7-4     A-F
             && ( ( reg_f & CPU_FLAG_H ) ==    0 )      //  H = 0
             && ( ( reg_a &       0x0F ) <= 0x09 ) )    //  3-0     0-9
        {
            //  Adjust register A by adding 0x60 and set the carry flag
            reg_a += 0x60;
            SET_FLAG_C( );
        }
        //  5       0   9-F     0   A-F     66      1
        else
        if (    ( ( reg_f & CPU_FLAG_C ) ==    0 )      //  C = 0
             && ( ( reg_a &       0xF0 ) >= 0x90 )      //  7-4     9-F
             && ( ( reg_f & CPU_FLAG_H ) ==    0 )      //  H = 0
             && ( ( reg_a &       0x0F ) >= 0x0A ) )    //  3-0     A-F
        {
            //  Adjust register A by adding 0x60 and set the carry flag
            reg_a += 0x66;
            SET_FLAG_C( );
        }
        //  6       0   A-F     1   0-3     66      1
        else
        if (    ( ( reg_f & CPU_FLAG_C ) ==    0 )      //  C = 0
             && ( ( reg_a &       0xF0 ) >= 0xA0 )      //  7-4     A-F
             && ( ( reg_f & CPU_FLAG_H ) !=    0 )      //  H = 1
             && ( ( reg_a &       0x0F ) <= 0x03 ) )    //  3-0     0-3
        {
            //  Adjust register A by adding 0x60 and set the carry flag
            reg_a += 0x66;
            SET_FLAG_C( );
        }
        //  7       1   0-2     0   0-9     60      1
        else
        if (    ( ( reg_f & CPU_FLAG_C ) !=    0 )      //  C = 1
             && ( ( reg_a &       0xF0 ) <= 0x20 )      //  7-4     0-2
             && ( ( reg_f & CPU_FLAG_H ) ==    0 )      //  H = 0
             && ( ( reg_a &       0x0F ) <= 0x09 ) )    //  3-0     0-9
        {
            //  Adjust register A by adding 0x60 and set the carry flag
            reg_a += 0x60;
            SET_FLAG_C( );
        }
        //  8       1   0-2     0   A-F     66      1
        else
        if (    ( ( reg_f & CPU_FLAG_C ) !=    0 )      //  C = 1
             && ( ( reg_a &       0xF0 ) <= 0x20 )      //  7-4     0-2
             && ( ( reg_f & CPU_FLAG_H ) ==    0 )      //  H = 0
             && ( ( reg_a &       0x0F ) >= 0x0A ) )    //  3-0     A-F
        {
            //  Adjust register A by adding 0x60 and set the carry flag
            reg_a += 0x66;
            SET_FLAG_C( );
        }
        //  9       1   0-3     1   0-3     66      1
        else
        if (    ( ( reg_f & CPU_FLAG_C ) !=    0 )      //  C = 1
             && ( ( reg_a &       0xF0 ) <= 0x30 )      //  7-4     0-3
             && ( ( reg_f & CPU_FLAG_H ) !=    0 )      //  H = 1
             && ( ( reg_a &       0x0F ) <= 0x03 ) )    //  3-0     0-3
        {
            //  Adjust register A by adding 0x60 and set the carry flag
            reg_a += 0x66;
            SET_FLAG_C( );
        }
    }
    else
    {
        //  NO:     SUBTRACTION
        //  10      0   0-9     0   0-0     00      0
        if (    ( ( reg_f & CPU_FLAG_C ) ==    0 )      //  C = 0
             && ( ( reg_a &       0xF0 ) <= 0x90 )      //  7-4     0-9
             && ( ( reg_f & CPU_FLAG_H ) ==    0 )      //  H = 0
             && ( ( reg_a &       0x0F ) <= 0x09 ) )    //  3-0     0-9
        {
            //  Nothing to do here
            reg_a = reg_a;  //  For debug.
        }
        //  11      0   0-8     1   6-F     FA      0
        else
        if (    ( ( reg_f & CPU_FLAG_C ) ==    0 )      //  C = 0
             && ( ( reg_a &       0xF0 ) <= 0x80 )      //  7-4     0-8
             && ( ( reg_f & CPU_FLAG_H ) !=    0 )      //  H = 1
             && ( ( reg_a &       0x0F ) >= 0x06 ) )    //  3-0     6-F
        {
            //  Adjust register A by adding 0x60 and set the carry flag
            reg_a += 0xFA;
        }
        //  12      1   7-F     0   0-9     A0      1
        else
        if (    ( ( reg_f & CPU_FLAG_C ) !=    0 )      //  C = 1
             && ( ( reg_a &       0xF0 ) >= 0x70 )      //  7-4     7-F
             && ( ( reg_f & CPU_FLAG_H ) ==    0 )      //  H = 0
             && ( ( reg_a &       0x0F ) <= 0x09 ) )    //  3-0     0-9
        {
            //  Adjust register A by adding 0x60 and set the carry flag
            reg_a += 0xA0;
            SET_FLAG_C( );
        }
        //  13      1   6-F     1   6-F     9A      1
        else
        if (    ( ( reg_f & CPU_FLAG_C ) !=    0 )      //  C = 1
             && ( ( reg_a &       0xF0 ) >= 0x60 )      //  7-4     6-F
             && ( ( reg_f & CPU_FLAG_H ) !=    0 )      //  H = 1
             && ( ( reg_a &       0x0F ) >= 0x06 ) )    //  3-0     6-F
        {
            //  Adjust register A by adding 0x60 and set the carry flag
            reg_a += 0x9A;
            SET_FLAG_C( );
        }
    }

    //  Save the result back in register A
    PUT_A( reg_a );

    //  Set the number of states for this instruction
    operation_rc.states =  11;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  CPL                  175        00101111
 *  CMA                 4-10
 *
 *  The contents of the Accumulator (Register A) are inverted (one’s complement).
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
math_cpl_i80(
    uint8_t                     op_code
    )
{
    //  CPL
    PUT_A( ( GET_A( ) ^ 0xFF ) );

    /************************************************************************
     *  SET FLAGS
     ************************************************************************/

    //  Carry                                                               C
    // C is not affected.

    //  SUBTRACT/ADD                                                        N
    SET_FLAG_N( );

    //  PARITY/OVERFLOW                                                     P/V
    // P/V is not affected.

    //  HALF CARRY                                                          H
    SET_FLAG_H( );

    //  ZERO                                                                Z
    // Z is not affected.

    //  SIGN                                                                S
    // S is not affected.

    //  Set the number of states for this instruction
    operation_rc.states =   4;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  CCF                  178        00111111
 *  CMC                 4-11
 *
 *  The Carry flag in the F Register is inverted.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
math_ccf_i80(
    uint8_t                     op_code
    )
{

    /************************************************************************
     *  SET FLAGS
     ************************************************************************/

    //  Carry         (CCF)                                                 C
    PUT_F( ( GET_F( ) ^ CPU_FLAG_C ) );

    //  SUBTRACT/ADD                                                        N
    CLEAR_FLAG_N( );

    //  PARITY/OVERFLOW                                                     P/V
    // P/V is not affected.

    //  HALF CARRY                                                          H
    if ( ( GET_F( ) & CPU_FLAG_C ) ) CLEAR_FLAG_H( ); else SET_FLAG_H( );

    //  ZERO                                                                Z
    // Z is not affected.

    //  SIGN                                                                S
    // S is not affected.

    //  Set the number of states for this instruction
    operation_rc.states =   4;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  SCF                 179        00110111
 *  STC                 4-11
 *
 *  The Carry flag in the F Register is inverted.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
math_scf_i80(
    uint8_t                     op_code
    )
{

    /************************************************************************
     *  SET FLAGS
     ************************************************************************/

    //  Carry         (CCF)                                                 C
    SET_FLAG_C( );

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
 *  NEG                 176     ED 01000100
 *
 *  The contents of the Accumulator are negated (two’s complement). This method
 *  is the same as subtracting the contents of the Accumulator from zero.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
math_neg_ED(
    uint8_t                     op_code
    )
{
    PUT_A( sub_8( 0, GET_A( ), 0 ) );

    //  Set the number of states for this instruction
    operation_rc.states =   8;
}
/****************************************************************************/