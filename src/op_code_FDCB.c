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
    printf( "DEBUG: Invalid Z80 extended FDCB op_code [x%02X] @ [x%04X]\n",
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
op_code_FDCB_init(
    void
    )
{
    //========================================================================
    op_code_FDCB_table[ 0x00 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x01 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x02 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x03 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x04 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x05 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x06 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x07 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x08 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x09 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x0A ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x0B ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x0C ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x0D ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x0E ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x0F ] = invalid_op_code;           //
    //========================================================================
    op_code_FDCB_table[ 0x10 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x11 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x12 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x13 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x14 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x15 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x16 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x17 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x18 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x19 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x1A ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x1B ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x1C ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x1D ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x1E ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x1F ] = invalid_op_code;           //
    //========================================================================
    op_code_FDCB_table[ 0x20 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x21 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x22 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x23 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x24 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x25 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x26 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x27 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x28 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x29 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x2A ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x2B ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x2C ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x2D ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x2E ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x2F ] = invalid_op_code;           //
    //========================================================================
    op_code_FDCB_table[ 0x30 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x31 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x32 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x33 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x34 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x35 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x36 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x37 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x38 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x39 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x3A ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x3B ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x3C ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x3D ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x3E ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x3F ] = invalid_op_code;           //
    //========================================================================
    op_code_FDCB_table[ 0x40 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x41 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x42 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x43 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x44 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x45 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x46 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x47 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x48 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x49 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x4A ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x4B ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x4C ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x4D ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x4E ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x4F ] = invalid_op_code;           //
    //========================================================================
    op_code_FDCB_table[ 0x50 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x51 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x52 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x53 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x54 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x55 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x56 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x57 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x58 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x59 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x5A ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x5B ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x5C ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x5D ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x5E ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x5F ] = invalid_op_code;           //
    //========================================================================
    op_code_FDCB_table[ 0x60 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x61 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x62 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x63 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x64 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x65 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x66 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x67 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x68 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x69 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x6A ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x6B ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x6C ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x6D ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x6E ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x6F ] = invalid_op_code;           //
    //========================================================================
    op_code_FDCB_table[ 0x70 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x71 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x72 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x73 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x74 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x75 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x76 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x77 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x78 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x79 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x7A ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x7B ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x7C ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x7D ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x7E ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x7F ] = invalid_op_code;           //
    //========================================================================
    op_code_FDCB_table[ 0x80 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x81 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x82 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x83 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x84 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x85 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x86 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x87 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x88 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x89 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x8A ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x8B ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x8C ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x8D ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x8E ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x8F ] = invalid_op_code;           //
    //========================================================================
    op_code_FDCB_table[ 0x90 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x91 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x92 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x93 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x94 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x95 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x96 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x97 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x98 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x99 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x9A ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x9B ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x9C ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x9D ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x9E ] = invalid_op_code;           //
    op_code_FDCB_table[ 0x9F ] = invalid_op_code;           //
    //========================================================================
    op_code_FDCB_table[ 0xA0 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xA1 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xA2 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xA3 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xA4 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xA5 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xA6 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xA7 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xA8 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xA9 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xAA ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xAB ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xAC ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xAD ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xAE ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xAF ] = invalid_op_code;           //
    //========================================================================
    op_code_FDCB_table[ 0xB0 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xB1 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xB2 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xB3 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xB4 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xB5 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xB6 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xB7 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xB8 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xB9 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xBA ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xBB ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xBC ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xBD ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xBE ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xBF ] = invalid_op_code;           //
    //========================================================================
    op_code_FDCB_table[ 0xC0 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xC1 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xC2 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xC3 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xC4 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xC5 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xC6 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xC7 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xC8 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xC9 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xCA ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xCB ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xCC ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xCD ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xCE ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xCF ] = invalid_op_code;           //
    //========================================================================
    op_code_FDCB_table[ 0xD0 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xD1 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xD2 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xD3 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xD4 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xD5 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xD6 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xD7 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xD8 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xD9 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xDA ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xDB ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xDC ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xDD ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xDE ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xDF ] = invalid_op_code;           //
    //========================================================================
    op_code_FDCB_table[ 0xE0 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xE1 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xE2 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xE3 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xE4 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xE5 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xE6 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xE7 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xE8 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xE9 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xEA ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xEB ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xEC ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xED ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xEE ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xEF ] = invalid_op_code;           //
    //========================================================================
    op_code_FDCB_table[ 0xF0 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xF1 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xF2 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xF3 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xF4 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xF5 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xF6 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xF7 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xF8 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xF9 ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xFA ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xFB ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xFC ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xFD ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xFE ] = invalid_op_code;           //
    op_code_FDCB_table[ 0xFF ] = invalid_op_code;           //
    //========================================================================

}
/****************************************************************************/