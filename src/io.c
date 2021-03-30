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
#include "io.h"                 //  Input & Output instructions
#include "bios.h"           //  CP/M BIOS
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
 *  IN   n               295        11011011 port
 *  IN   port           4-14
 *
 *  The operand n is placed on the bottom half (A0 through A7) of the address
 *  bus to select the I/O device at one of 256 possible ports. The contents of
 *  the Accumulator also appear on the top half (A8 through A15) of the address
 *  bus at this time. Then one byte from the selected port is placed on the
 *  data bus and written to the Accumulator (Register A) in the CPU.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      This is ONLY a placeholder instruction for the foreseeable future.
 *      We are running in a simulator and there isn't any hardware and
 *      thus no place to put the data.
 *
 ****************************************************************************/

void
in_n_i80(
    uint8_t                     op_code
    )
{
    /**
     *  @param  port                The output port number                  */
    uint8_t                     port;

    //  Read the port number to input from
    port = memory_get_8( CPU_REG_PC++ );

    //  Set the number of states for this instruction
    operation_rc.states   =  11;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  OUT  n               306        11010011 port
 *  OUT  port           4-14
 *
 *  The operand n is placed on the bottom half (A0 through A7) of the address
 *  bus to select the I/O device at one of 256 possible ports. The contents of
 *  the Accumulator (Register A) also appear on the top half (A8 through A15)
 *  of the address bus at this time. Then the byte contained in the Accumulator
 *  is placed on the data bus and written to the selected peripheral device.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      This is ONLY a placeholder instruction for the foreseeable future.
 *      We are running in a simulator and there isn't any hardware and
 *      thus no place to put the data.
 *
 *      This instruction is being used to change the simulator mode:
 *          port (n)        Register A          Mode:
 *            x'FF             x'FF             Intel   I80
 *            x'FF             x'FE             Zilog   Z80
 *
 ****************************************************************************/

void
out_n_i80(
    uint8_t                     op_code
    )
{
    /**
     *  @param  port                The output port number                  */
    uint8_t                     port;

    //  Read the port number to output to
    port = memory_get_8( CPU_REG_PC++ );

    /************************************************************************
     *  x'FE    CPU Type
     ************************************************************************/

    //  Are we changing the CPU type ?
    if( port == 0xFE )
    {
        //  Intel 8080 ?
        if( GET_A( ) == 0xFF )
        {
            //  YES:    Change it.
            CPU = CPU_I80;
            printf( "\n#CP:   Set Intel 8080 mode.\n\n" );
        }
        else
        //  Zilog Z80 ?
        if( GET_A( ) == 0xFE )
        {
            //  YES:    Change it.
            CPU = CPU_Z80;
            printf( "\n#CP:   Set Zilog Z80 mode.\n\n" );
        }
    }

    /************************************************************************
     *  x'FF    CP/M BIOS call
     ************************************************************************/

    //  Is this a BIOS call ?
    else
    if ( port == 0xFF )
    {
        //  YES:    Go perform the BIOS function
        cpm_bios( );
    }
    //  @ToDo   Add the Z80 mode when it is ready to go.

    //  Set the number of states for this instruction
    operation_rc.states   =  11;
}
/****************************************************************************/