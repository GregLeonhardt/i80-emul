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
/**
 *  Get the contents of source register "r".
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

uint8_t
reg_get_sr(
    uint8_t                     op_code
    )
{
    /**
     *  @param  data            Register contents                           */
    uint8_t                     data;

    //  Mask for the source register
    switch( op_code & 0x07 )
    {
        case    R_B:            //  Source register B
            data = GET_B( );
            break;
        case    R_C:            //  Source register C
            data = GET_C( );
            break;
        case    R_D:            //  Source register D
            data = GET_D( );
            break;
        case    R_E:            //  Source register E
            data = GET_E( );
            break;
        case    R_H:            //  Source register H
            data = GET_H( );
            break;
        case    R_L:            //  Source register L
            data = GET_L( );
            break;
        case    R_A:            //  Source register A
            data = GET_A( );
            break;
    }
    return( data );
}

/****************************************************************************/
/**
 *  Get the contents of destination register "r".
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

uint8_t
reg_get_dr(
    uint8_t                     op_code
    )
{
    /**
     *  @param  data            Register contents                           */
    uint8_t                     data;

    //  Mask for the destination register
    switch( ( op_code & 0x38 ) >> 3 )
    {
        case    R_B:            //  Source register B
            data = GET_B( );
            break;
        case    R_C:            //  Source register C
            data = GET_C( );
            break;
        case    R_D:            //  Source register D
            data = GET_D( );
            break;
        case    R_E:            //  Source register E
            data = GET_E( );
            break;
        case    R_H:            //  Source register H
            data = GET_H( );
            break;
        case    R_L:            //  Source register L
            data = GET_L( );
            break;
        case    R_A:            //  Source register A
            data = GET_A( );
            break;
    }
    return( data );
}

/****************************************************************************/
/**
 *  Put data into destination register "r".
 *
 *  @parm   op_code             The operation code of the current instruction.
 *  @parm   data                An 8 bit byte that will be stored in a register
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
reg_put_dr(
    uint8_t                     op_code,
    uint8_t                     data
    )
{
    //  Mask for the destination register
    switch( ( op_code & 0x38 ) >> 3 )
    {
        case    R_B:            //  Destination register B
            PUT_B( data );
            break;
        case    R_C:            //  Destination register C
            PUT_C( data );
            break;
        case    R_D:            //  Destination register D
            PUT_D( data );
            break;
        case    R_E:            //  Destination register E
            PUT_E( data );
            break;
        case    R_H:            //  Destination register H
            PUT_H( data );
            break;
        case    R_L:            //  Destination register L
            PUT_L( data );
            break;
        case    R_A:            //  Destination register A
            PUT_A( data );
            break;
    }
}

/****************************************************************************/
/**
 *  Get the contents of register pair "ss".
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      Pair dd
 *           00     BC
 *           01     DE
 *           10     HL
 *           11     SP
 *
 ****************************************************************************/

uint16_t
reg_get_ss(
    uint8_t                     op_code
    )
{
    /**
     *  @param  data            Register contents                           */
    uint16_t                    data;

    //  Mask for the source register
    switch( ( op_code & 0x30 ) >> 4 )
    {
        case    SS_BC:          //  Source register pair BC
            data = CPU_REG_BC;
            break;
        case    SS_DE:          //  Source register pair DE
            data = CPU_REG_DE;
            break;
        case    SS_HL:          //  Source register pair HL
            data = CPU_REG_HL;
            break;
        case    SS_SP:          //  Source register pair SP
            data = CPU_REG_SP;
            break;
    }
    return( data );
}

/****************************************************************************/
/**
 *  Put 'data' into register set "ss".
 *
 *  @parm   op_code             The operation code of the current instruction.
 *  @parm   data                A 16 bit word that will be stored
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      Pair dd
 *           00     BC
 *           01     DE
 *           10     HL
 *           11     SP
 *
 ****************************************************************************/

void
reg_put_ss(
    uint8_t                     op_code,
    uint16_t                    data
    )
{
    //  Mask for the source register
    switch( ( op_code & 0x30 ) >> 4 )
    {
        case    SS_BC:          //  Source register pair BC
            CPU_REG_BC = data;
            break;
        case    SS_DE:          //  Source register pair DE
            CPU_REG_DE = data;
            break;
        case    SS_HL:          //  Source register pair HL
            CPU_REG_HL = data;
            break;
        case    SS_SP:          //  Source register pair SP
            CPU_REG_SP = data;
            break;
    }
}

/****************************************************************************/
/**
 *  Get the contents of register pair "qq".
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      Pair qq
 *           00     BC
 *           01     DE
 *           10     HL
 *           11     AF
 *
 ****************************************************************************/

uint16_t
reg_get_qq(
    uint8_t                     op_code
    )
{
    /**
     *  @param  data            Register contents                           */
    uint16_t                    data;

    //  Mask for the source register
    switch( ( op_code & 0x30 ) >> 4 )
    {
        case    QQ_BC:          //  Source register pair BC
            data = CPU_REG_BC;
            break;
        case    QQ_DE:          //  Source register pair DE
            data = CPU_REG_DE;
            break;
        case    QQ_HL:          //  Source register pair HL
            data = CPU_REG_HL;
            break;
        case    QQ_AF:          //  Source register pair AF
            data = CPU_REG_AF;
            break;
    }
    return( data );
}

/****************************************************************************/
/**
 *  Put 'data' into register set "qq".
 *
 *  @parm   op_code             The operation code of the current instruction.
 *  @parm   data                A 16 bit word that will be stored
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      Pair qq
 *           00     BC
 *           01     DE
 *           10     HL
 *           11     AF
 *
 ****************************************************************************/

void
reg_put_qq(
    uint8_t                     op_code,
    uint16_t                    data
    )
{
    //  Mask for the source register
    switch( ( op_code & 0x30 ) >> 4 )
    {
        case    QQ_BC:          //  Source register pair BC
            CPU_REG_BC = data;
            break;
        case    QQ_DE:          //  Source register pair DE
            CPU_REG_DE = data;
            break;
        case    QQ_HL:          //  Source register pair HL
            CPU_REG_HL = data;
            break;
        case    QQ_AF:          //  Source register pair AF
            CPU_REG_AF = data;
            break;
    }
}
/****************************************************************************/