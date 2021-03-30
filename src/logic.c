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
#include "logic.h"              //  Logic (AND, OR, XOR, CMP) instrucions.
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
 *  Add the contents of the first byte are logiclly AND'd with the value of
 *  the second byte.  The results are returned.
 *
 *  @param  byte_1                  The first byte
 *  @param  byte_2                  The second byte
 *
 *
 *  @return result
 *
 *  @note
 *      Condition Bits Affected
 *          S is set if result is negative; otherwise, it is reset.
 *          Z is set if result is 0; otherwise, it is reset.
 *          H is set.
 *          P/V is reset if overflow; otherwise, it is reset.
 *          N is reset.
 *          C is reset.
 *
 ****************************************************************************/

uint8_t
and_8(
    uint8_t                     byte_1,
    uint8_t                     byte_2
    )
{
    /**
     *  @param  result              The result of the add operation        */
    uint16_t                    result;

    //  result = byte_1 & byte_2
    result = byte_1 & byte_2;

    /************************************************************************
     *  SET FLAGS
     ************************************************************************/

    //  Carry
    CLEAR_FLAG_C( );

    //  SUBTRACT/ADD
    CLEAR_FLAG_N( );

    //  PARITY/OVERFLOW
    if ( parity_8( result & 0x00FF ) == 0 )
        CLEAR_FLAG_PV( );       //  Parity Even
    else
        SET_FLAG_PV( );         //  Parity Odd

    //  HALF CARRY
    CLEAR_FLAG_H( );

    //  ZERO
    if ( ( result & 0x00FF ) == 0x0000 )
        SET_FLAG_Z( );
    else
        CLEAR_FLAG_Z( );

    //  SIGN
    if ( ( result & 0x0080 ) == 0x0080 )
        SET_FLAG_S( );
    else
        CLEAR_FLAG_S( );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    return( (uint8_t)result );
}

/****************************************************************************/
/**
 *  Add the contents of the first byte are logiclly OR'd with the value of
 *  the second byte.  The results are returned.
 *
 *  @param  byte_1                  The first byte
 *  @param  byte_2                  The second byte
 *
 *
 *  @return result
 *
 *  @note
 *      Condition Bits Affected
 *          S is set if result is negative; otherwise, it is reset.
 *          Z is set if result is 0; otherwise, it is reset.
 *          H is set.
 *          P/V is reset if overflow; otherwise, it is reset.
 *          N is reset.
 *          C is reset.
 *
 ****************************************************************************/

uint8_t
or_8(
    uint8_t                     byte_1,
    uint8_t                     byte_2
    )
{
    /**
     *  @param  result              The result of the add operation        */
    uint16_t                    result;

    //  result = byte_1 & byte_2
    result = byte_1 | byte_2;

    /************************************************************************
     *  SET FLAGS
     ************************************************************************/

    //  Carry
    CLEAR_FLAG_C( );

    //  SUBTRACT/ADD
    CLEAR_FLAG_N( );

    //  PARITY/OVERFLOW
    if ( parity_8( result & 0x00FF ) == 0 )
        CLEAR_FLAG_PV( );       //  Parity Even
    else
        SET_FLAG_PV( );         //  Parity Odd

    //  HALF CARRY
    CLEAR_FLAG_H( );

    //  ZERO
    if ( ( result & 0x00FF ) == 0x0000 )
        SET_FLAG_Z( );
    else
        CLEAR_FLAG_Z( );

    //  SIGN
    if ( ( result & 0x0080 ) == 0x0080 )
        SET_FLAG_S( );
    else
        CLEAR_FLAG_S( );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    return( (uint8_t)result );
}

/****************************************************************************/
/**
 *  Add the contents of the first byte are logiclly XOR'd with the value of
 *  the second byte.  The results are returned.
 *
 *  @param  byte_1                  The first byte
 *  @param  byte_2                  The second byte
 *
 *
 *  @return result
 *
 *  @note
 *      Condition Bits Affected
 *          S is set if result is negative; otherwise, it is reset.
 *          Z is set if result is 0; otherwise, it is reset.
 *          H is set.
 *          P/V is reset if overflow; otherwise, it is reset.
 *          N is reset.
 *          C is reset.
 *
 ****************************************************************************/

uint8_t
xor_8(
    uint8_t                     byte_1,
    uint8_t                     byte_2
    )
{
    /**
     *  @param  result              The result of the add operation        */
    uint16_t                    result;

    //  result = byte_1 & byte_2
    result = byte_1 ^ byte_2;

    /************************************************************************
     *  SET FLAGS
     ************************************************************************/

    //  Carry
    CLEAR_FLAG_C( );

    //  SUBTRACT/ADD
    CLEAR_FLAG_N( );

    //  PARITY/OVERFLOW
    if ( parity_8( result & 0x00FF ) == 0 )
        CLEAR_FLAG_PV( );       //  Parity Even
    else
        SET_FLAG_PV( );         //  Parity Odd

    //  HALF CARRY
    CLEAR_FLAG_H( );

    //  ZERO
    if ( ( result & 0x00FF ) == 0x0000 )
        SET_FLAG_Z( );
    else
        CLEAR_FLAG_Z( );

    //  SIGN
    if ( ( result & 0x0080 ) == 0x0080 )
        SET_FLAG_S( );
    else
        CLEAR_FLAG_S( );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    return( (uint8_t)result );
}

/****************************************************************************/
/**
 *  Compare: the contents of the first byte are subtracted from the value of the
 *  second byte.  ONLY FLAGS ARE CHANGED.
 *
 *  @param  byte_1                  The first byte
 *  @param  byte_2                  The second byte
 *
 *
 *  @return                         No information is returned from this function.
 *
 *  @note
 *      Condition Bits Affected
 *          S is set if result is negative; otherwise, it is reset.
 *          Z is set if result is 0; otherwise, it is reset.
 *          H is set if borrow from bit 4; otherwise, it is reset.
 *          P/V is set if overflow; otherwise, it is reset.
 *          N is set.
 *          C is set if borrow; otherwise, it is reset.
 *
 ****************************************************************************/

void
compare_8(
    uint16_t                    byte_1,
    uint16_t                    byte_2
    )
{
    /**
     *  @param  result              The result of the add operation        */
    uint16_t                    result;

    //  Create 16 bit signed numbers
    if ( byte_1 > 127 ) byte_1 |= 0xFF00;
    if ( byte_2 > 127 ) byte_2 |= 0xFF00;

    //  result = byte_1 & byte_2
    result = byte_1 - byte_2;

    /************************************************************************
     *  SET FLAGS
     ************************************************************************/

    //  Carry
    if ( byte_1 < byte_2  ) SET_FLAG_C( ); else CLEAR_FLAG_C( );

    //  SUBTRACT/ADD
    SET_FLAG_N( );

    //  Are we running Intel 8080 mode ?
    if ( CPU == CPU_I80 )
    {
        //  YES:    Set the 'PARITY' flag
        if ( parity_8( result & 0x00FF ) == 0 )
            CLEAR_FLAG_PV( );       //  Parity Even
        else
            SET_FLAG_PV( );         //  Parity Odd
    }
    else
    {
        //  PARITY/OVERFLOW
        if (    ( ( byte_1  & 0x80 ) != ( byte_2 & 0x80 ) )
             && ( result & 0x80 ) != ( byte_1    & 0x80 ) )
            SET_FLAG_PV( );
        else
            CLEAR_FLAG_PV( );
    }

    //  HALF CARRY
    if ( ( ( ( byte_1 & 0x0000F ) - ( byte_2 & 0x0000F ) ) & 0x0010 ) == 0x0010 )
        SET_FLAG_H( );
    else
        CLEAR_FLAG_H( );

    //  ZERO
    if ( byte_1 == byte_2 )
        SET_FLAG_Z( );
    else
        CLEAR_FLAG_Z( );

    //  SIGN
    if ( ( result & 0x0080 ) == 0x0080 )
        SET_FLAG_S( );
    else
        CLEAR_FLAG_S( );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

}

/****************************************************************************/
/**
 *  Compare: the contents of the first byte are subtracted from the value of the
 *  second byte.  ONLY FLAGS ARE CHANGED.
 *
 *  @param  byte_1                  The first byte
 *  @param  byte_2                  The second byte
 *
 *
 *  @return                         No information is returned from this function.
 *
 *  @note
 *      Condition Bits Affected
 *      S is set if result is negative; otherwise, it is reset.
 *      Z is set if A equals (HL); otherwise, it is reset.
 *      H is set if borrow from bit 4; otherwise, it is reset.
 *      P/V is set if BC – 1≠ 0; otherwise, it is reset.
 *      N is set.
 *      C is not affected.
 *
 ****************************************************************************/

void
compare_8_ED(
    uint16_t                    byte_1,
    uint16_t                    byte_2
    )
{
    /**
     *  @param  result              The result of the add operation        */
    uint16_t                    result;

    //  Create 16 bit signed numbers
    if ( byte_1 > 127 ) byte_1 |= 0xFF00;
    if ( byte_2 > 127 ) byte_2 |= 0xFF00;

    //  result = byte_1 & byte_2
    result = byte_1 - byte_2;

    /************************************************************************
     *  SET FLAGS
     ************************************************************************/

    //  Carry
    //  Not effected

    //  SUBTRACT/ADD
    SET_FLAG_N( );

    //  HALF CARRY
    if ( ( ( ( byte_1 & 0x0000F ) - ( byte_2 & 0x0000F ) ) & 0x0010 ) == 0x0010 )
        SET_FLAG_H( );
    else
        CLEAR_FLAG_H( );

    //  ZERO
    if ( byte_1 == byte_2 )
        SET_FLAG_Z( );
    else
        CLEAR_FLAG_Z( );

    //  SIGN
    if ( ( result & 0x0080 ) == 0x0080 )
        SET_FLAG_S( );
    else
        CLEAR_FLAG_S( );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

}

/****************************************************************************
 * MAIN
 ****************************************************************************/

/****************************************************************************/
/**                     Page        Op-Code
 *  AND  r               157        10100sss
 *  ANA  r               4-8
 *
 *  The contents of register r are logically AND'd with the contents of the
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
logic_andr_i80(
    uint8_t                     op_code
    )
{
    //  AND  A, r
    PUT_A( and_8( reg_get_sr( op_code ), GET_A( ) ) );

    //  Set the number of states for this instruction
    operation_rc.states =   4;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  AND  n               157        11100110
 *  ADI  n               4-9
 *
 *  The n integer are logically AND'd with the contents of the Accumulator, and
 *  the results are stored in the Accumulator.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
logic_andn_i80(
    uint8_t                     op_code
    )
{
    //  AND  A, n
    PUT_A( and_8( memory_get_8( CPU_REG_PC++ ), GET_A( ) ) );

    //  Set the number of states for this instruction
    operation_rc.states =   7;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  AND  (HL)            157       10100110
 *  ANA  M               4-8
 *
 *  The byte at the memory address specified by the contents of the HL register
 *  pair are logically AND'd with the contents of the Accumulator, and the
 *  result is stored in the Accumulator.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
logic_andhl_i80(
    uint8_t                     op_code
    )
{
    //  AND  A, HL
    PUT_A( and_8( memory_get_8( CPU_REG_HL ), GET_A( ) ) );

    //  Set the number of states for this instruction
    operation_rc.states =   7;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  OR   r               159        10110sss
 *  ORA  r               4-9
 *
 *  The contents of register r are logically OR'd with the contents of the
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
logic_orr_i80(
    uint8_t                     op_code
    )
{
    //  OR   r
    PUT_A( or_8( reg_get_sr( op_code ), GET_A( ) ) );

    //  Set the number of states for this instruction
    operation_rc.states =   4;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  OR   n               159        11110110
 *  ORI  n               4-9
 *
 *  The n integer are logically OR'd with the contents of the Accumulator, and
 *  the results are stored in the Accumulator.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
logic_orn_i80(
    uint8_t                     op_code
    )
{
    //  AND  A, n
    PUT_A( or_8( memory_get_8( CPU_REG_PC++ ), GET_A( ) ) );

    //  Set the number of states for this instruction
    operation_rc.states =   7;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  OR   (HL)            159       10110110
 *  ORA  M               4-9
 *
 *  The byte at the memory address specified by the contents of the HL register
 *  pair are logically OR'd with the contents of the Accumulator, and the result
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
logic_orhl_i80(
    uint8_t                     op_code
    )
{
    //  AND  A, HL
    PUT_A( or_8( memory_get_8( CPU_REG_HL ), GET_A( ) ) );

    //  Set the number of states for this instruction
    operation_rc.states =   7;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  XOR  r               161        10101sss
 *  XRA  r               4-9
 *
 *  The contents of register r are logically Exclusive OR'd with the contents
 *  of the Accumulator, and the result is stored in the Accumulator. The r
 *  symbol identifies the registers A, B, C, D, E, H, or L.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
logic_xorr_i80(
    uint8_t                     op_code
    )
{
    //  OR   r
    PUT_A( xor_8( reg_get_sr( op_code ), GET_A( ) ) );

    //  Set the number of states for this instruction
    operation_rc.states =   4;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  XOR  n               161        11101110
 *  XRI  n               4-9
 *
 *  The n integer are logically Exclusive OR'd with the contents of the
 *  Accumulator, and the results are stored in the Accumulator.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
logic_xorn_i80(
    uint8_t                     op_code
    )
{
    //  AND  A, n
    PUT_A( xor_8( memory_get_8( CPU_REG_PC++ ), GET_A( ) ) );

    //  Set the number of states for this instruction
    operation_rc.states =   7;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  XOR  A, (HL)         161       10101110
 *  XRA  M               4-9
 *
 *  The byte at the memory address specified by the contents of the HL register
 *  pair are logically Exclusive OR'd with the contents of the Accumulator, and
 *  the result is stored in the Accumulator.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
logic_xorhl_i80(
    uint8_t                     op_code
    )
{
    //  AND  A, HL
    PUT_A( xor_8( memory_get_8( CPU_REG_HL ), GET_A( ) ) );

    //  Set the number of states for this instruction
    operation_rc.states =   7;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  CP   r               164        10111sss
 *  CMP  r               4-9
 *
 *  The contents of register r is subtracted from the contents of the
 *  Accumulator. The Accumulator is unchanged. The r symbol identifies the
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
logic_cpr_i80(
    uint8_t                     op_code
    )
{
    //  OR   r
    compare_8( GET_A( ), reg_get_sr( op_code ) );

    //  Set the number of states for this instruction
    operation_rc.states =   4;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  CP   n               164        11111110
 *  CPI  n              4-10
 *
 *  The n integer is subtracted from the contents of the Accumulator. The
 *  Accumulator is unchanged.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
logic_cpn_i80(
    uint8_t                     op_code
    )
{
    //  AND  A, n
    compare_8( GET_A( ), memory_get_8( CPU_REG_PC++ ) );

    //  Set the number of states for this instruction
    operation_rc.states =   7;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  CP   (HL)            164       10111110
 *  CMP  M              4-10
 *
 *  The byte at the memory address specified by the contents of the HL register
 *  pair is subtracted from the contents of the Accumulator. The Accumulator
 *  is unchanged.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
logic_cphl_i80(
    uint8_t                     op_code
    )
{
    //  AND  A, HL
    compare_8( GET_A( ), memory_get_8( CPU_REG_HL ) );

    //  Set the number of states for this instruction
    operation_rc.states =   7;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  CPD                  141       10101001
 *
 *  The contents of the memory location addressed by the HL register pair is
 *  compared with the contents of the Accumulator. During a compare operation,
 *  a condition bit is set. The HL and Byte Counter (register pair BC) are
 *  decremented.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      S is set if result is negative; otherwise, it is reset.
 *      Z is set if A equals (HL); otherwise, it is reset.
 *      H is set if borrow from bit 4; otherwise, it is reset.
 *      P/V is set if BC – 1≠ 0; otherwise, it is reset.
 *      N is set.
 *      C is not affected.
 *
 ****************************************************************************/

void
logic_cpd_ED(
    uint8_t                     op_code
    )
{
    //  CPD
    compare_8_ED( GET_A( ), memory_get_8( CPU_REG_HL ) );

    //  Decrement counter and pointer
    CPU_REG_HL -= 1;
    CPU_REG_BC -= 1;

    //  Has the count reached zero ?
    if( CPU_REG_BC == 0 )
        CLEAR_FLAG_PV( );       //  BC == 0
    else
        SET_FLAG_PV( );         //  BC != 0


    //  Set the number of states for this instruction
    operation_rc.states =  16;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  CPI                  138       10100001
 *
 *  The contents of the memory location addressed by the HL register is
 *  compared with the contents of the Accumulator. With a true compare, a
 *  condition bit is set. Then HL is incremented and the Byte Counter (register
 *  pair BC) is decremented.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      S is set if result is negative; otherwise, it is reset.
 *      Z is set if A is (HL); otherwise, it is reset.
 *      H is set if borrow from bit 4; otherwise, it is reset.
 *      P/V is set if BC – 1 is not 0; otherwise, it is reset.
 *      N is set.
 *      C is not affected.
 *
 ****************************************************************************/

void
logic_cpi_ED(
    uint8_t                     op_code
    )
{
    //  CPD
    compare_8_ED( GET_A( ), memory_get_8( CPU_REG_HL ) );

    //  Decrement counter and pointer
    CPU_REG_HL += 1;
    CPU_REG_BC -= 1;

    //  Has the count reached zero ?
    if( CPU_REG_BC == 0 )
        CLEAR_FLAG_PV( );       //  BC == 0
    else
        SET_FLAG_PV( );         //  BC != 0


    //  Set the number of states for this instruction
    operation_rc.states =  16;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  CPDR                 142       10111001
 *
 *  The contents of the memory location addressed by the HL register pair is
 *  compared with the contents of the Accumulator. During a compare operation,
 *  a condition bit is set. The HL and Byte Counter (BC) Register pairs are
 *  decremented. If decrementing allows the BC to go to 0 or if A = (HL), the
 *  instruction is terminated. If BC is not 0 and A = (HL), the program counter
 *  is decremented by two and the instruction is repeated. Interrupts are
 *  recognized and two refresh cycles execute after each data transfer. When
 *  the BC is set to 0, prior to instruction execution, the instruction loops
 *  through 64 KB if no match is found.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      S is set if result is negative; otherwise, it is reset.
 *      Z is set if A = (HL); otherwise, it is reset.
 *      H is set if borrow form bit 4; otherwise, it is reset.
 *      P/V is set if BC – 1 ≠ 0; otherwise, it is reset.
 *      N is set.
 *      C is not affected.
 *
 ****************************************************************************/

void
logic_cpdr_ED(
    uint8_t                     op_code
    )
{
    /**
     *  @param  count           Number of clock cycles                      */
    int                         count;

    //  Set the number of clock cycles this instruction will consume.
    if( CPU_REG_BC == 0 )
        count = 0x0080000;
    else
        count = (int)CPU_REG_BC * 8;

    do
    {
        //  CPD
        compare_8_ED( GET_A( ), memory_get_8( CPU_REG_HL ) );

        //  Adjust counter and pointer
        CPU_REG_HL -= 1;
        CPU_REG_BC -= 1;

        //  Has the count reached zero ?
        if( CPU_REG_BC == 0 )
            CLEAR_FLAG_PV( );       //  BC == 0
        else
            SET_FLAG_PV( );         //  BC != 0

        //  Was the search byte located ?
        if( GET_FLAG_Z( ) != 0 )
            break;

    }   while( CPU_REG_BC != 0 );

    //  Set the number of states for this instruction
    operation_rc.states =  16 + count;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  CPIR                 139       10110001
 *
 *  The contents of the memory location addressed by the HL register pair is
 *  compared with the contents of the Accumulator. During a compare operation,
 *  a condition bit is set. HL is incremented and the Byte Counter (register
 *  pair BC) is decremented. If decrementing causes BC to go to 0 or if A =
 *  (HL), the instruction is terminated. If BC is not 0 and A ≠ (HL), the
 *  program counter is decremented by two and the instruction is repeated.
 *  Interrupts are recognized and two refresh cycles are executed after each
 *  data transfer.
 *  If BC is set to 0 before instruction execution, the instruction loops
 *  through 64 KB if no match is found.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      S is set if result is negative; otherwise, it is reset.
 *      Z is set if A equals (HL); otherwise, it is reset.
 *      H is set if borrow from bit 4; otherwise, it is reset.
 *      P/V is set if BC – 1 does not equal 0; otherwise, it is reset.
 *      N is set.
 *      C is not affected.
 *
 ****************************************************************************/

void
logic_cpir_ED(
    uint8_t                     op_code
    )
{
    /**
     *  @param  count           Number of clock cycles                      */
    int                         count;

    //  Set the number of clock cycles this instruction will consume.
    if( CPU_REG_BC == 0 )
        count = 0x0080000;
    else
        count = (int)CPU_REG_BC * 8;

    do
    {
        //  CPI
        compare_8_ED( GET_A( ), memory_get_8( CPU_REG_HL ) );

        //  Adjust counter and pointer
        CPU_REG_HL += 1;
        CPU_REG_BC -= 1;

        //  Has the count reached zero ?
        if( CPU_REG_BC == 0 )
            CLEAR_FLAG_PV( );       //  BC == 0
        else
            SET_FLAG_PV( );         //  BC != 0

        //  Was the search byte located ?
        if( GET_FLAG_Z( ) != 0 )
            break;

    }   while( CPU_REG_BC != 0 );

    //  Set the number of states for this instruction
    operation_rc.states =  16 + count;
}
/****************************************************************************/