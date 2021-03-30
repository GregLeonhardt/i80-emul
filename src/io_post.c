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
#include "op_code.h"            //  OP-Code instruction maps
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
 *  IN      A, n
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      This test only verifies the instruction map table is worling.
 *
 ****************************************************************************/

static
int
tc_in_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x00,             //  0000    LD      A, x'00
        0xDB, 0x00,             //  0002    IN      x'00
        0x76      };            //  0004    HALT

    /************************************************************************
     *  Run the program
     ************************************************************************/

    //  Assume a successful test run.
    post_rc = true;

    //  Load the program
    memory_load( 0x0000, sizeof( program ), program );

    //  Run the program
    inst_fetch( );

    /************************************************************************
     *  Verify the results
     ************************************************************************/

    if ( CPU_REG_PC != 0x0005 )
    {
        //  NO:     Write an error message
        printf( "POST: tc_in_00 failed:         [in   A, n  ]\n" );
        printf( "POST: PC = 0x%04X\n", CPU_REG_PC );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  OUT     A, n
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      This test only verifies the instruction map table is worling.
 *
 ****************************************************************************/

static
int
tc_out_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x00,             //  0000    LD      A, x'00
        0xD3, 0x00,             //  0002    OUT     x'00
        0x76      };            //  0004    HALT

    /************************************************************************
     *  Run the program
     ************************************************************************/

    //  Assume a successful test run.
    post_rc = true;

    //  Load the program
    memory_load( 0x0000, sizeof( program ), program );

    //  Run the program
    inst_fetch( );

    /************************************************************************
     *  Verify the results
     ************************************************************************/

    if ( CPU_REG_PC != 0x0005 )
    {
        //  NO:     Write an error message
        printf( "POST: tc_out_00 failed:         [out  A, n  ]\n" );
        printf( "POST: PC = 0x%04X\n", CPU_REG_PC );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************
 * MAIN
 ****************************************************************************/


/****************************************************************************/
/**
 *  FooBar Power On Self Test
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *
 ****************************************************************************/

int
io_post(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                 */
    int                         post_rc;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Assume the test is going to pass
    post_rc = true;

    /************************************************************************
     *  POST Code
     ************************************************************************/

    //  @NOTE:      These tests are run in a very specific order.
    //              DO NOT change the order without understanding why
    //              the order is the way it is.

    //  @NOTE:  Some [definitely not all] instructions behave different
    //          between the 8080 and Z80.  Running both at a minimum will
    //          exercise both instruction maps.

    for( CPU = CPU_I80;
         CPU <= CPU_Z80;
         CPU += 1 )
    {
        if ( post_rc == true )      post_rc = tc_in_00( );          //  IN  A, n
        if ( post_rc == true )      post_rc = tc_out_00( );             //  IN  A, n

        //  Z80 ONLY instructions
        if( CPU == CPU_Z80 )
        {
        }

        //  Was the test suite successfully complete :
        if( post_rc == true )
        {
            //  YES:    Write a completion message
            printf( "POST: IO      complete %s mode.\n",
                    CPU == CPU_I80 ? "Intel 8080" : "Zilog Z80" );
        }
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( post_rc );
}
/****************************************************************************/