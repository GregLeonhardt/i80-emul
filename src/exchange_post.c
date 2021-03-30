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
#include "exchange.h"           //  EX   *,*
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
 *  TEST_000:       EX   DE, HL
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *
 ****************************************************************************/

static
int
tc_ex_dehl_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x21, 0x23, 0x01,       //  0000    LD   HL, 0x0123
        0x11, 0x67, 0x45,       //  0003    LD   DE, 0x4567
        0xEB,                   //  0006    EX   DE, HL
        0x76      };            //  0007    HALT

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

    if (    ( CPU_REG_HL != 0x4567 )
         || ( CPU_REG_DE != 0x0123 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ex_dehl_00 failed:     [ex   de, hl]\n" );
        printf( "POST: HL = 0x%04X\n", CPU_REG_HL );
        printf( "POST: DE = 0x%04X\n", CPU_REG_DE );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  TEST_001:       EX   (SP), HL
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *
 ****************************************************************************/

static
int
tc_ex_sphl_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x21, 0x21, 0x43,       //  0000    LD   HL, 0x4321
        0x11, 0xE0, 0xD0,       //  0003    LD   DE, 0xD0E0
        0x31, 0x20, 0x00,       //  0006    LD   SP, 0x0020
        0xD5,                   //  0009    PUSH DE
        0xE3,                   //  000A    EX   (SP), HL
        0x76      };            //  000E    HALT

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

    if (    ( CPU_REG_HL                  != 0xD0E0 )
         || ( CPU_REG_SP                  != 0x001E )
         || ( memory_get_16( CPU_REG_SP ) != 0x2143 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ex_sphl_00 failed:     [ex   (sp), hl]\n" );
        printf( "POST: HL   = 0x%04X\n", CPU_REG_HL );
        printf( "POST: SP   = 0x%04X\n", CPU_REG_SP );
        printf( "POST: (SP) = 0x%04X\n", memory_get_16( CPU_REG_SP ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  EX   AF, AF'
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *
 ****************************************************************************/

static
int
tc_ex_afaf_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x00,             //  0000    LD   A, 00h
        0xF6, 0x02,             //  0002    OR   02h
        0x08,                   //  0003    EX   AF, AF'
        0x3E, 0x00,             //  0000    LD   A, 00h
        0xF6, 0x03,             //  0002    OR   03h
        0x08,                   //  0003    EX   AF, AF'
        0x76      };            //  000E    HALT

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

    if (    ( CPU_REG_AF                  != 0x0200 )
         || ( CPU_REG_AF_                 != 0x0304 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ex_afaf_00 failed:     [ex   af, af' ]\n" );
        printf( "POST: AF   = 0x%04X\n", CPU_REG_AF  );
        printf( "POST: AF'  = 0x%04X\n", CPU_REG_AF_ );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  EXX
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *
 ****************************************************************************/

static
int
tc_exx_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x01, 0x11, 0x22,       //  0000    LD   BC, 1122h
        0x11, 0x33, 0x44,       //  0003    LD   DE, 3344h
        0x21, 0x55, 0x66,       //  0006    LD   HL, 5566h
        0xD9,                   //  0009    EXX
        0x01, 0xAA, 0xBB,       //  000A    LD   BC, AABBh
        0x11, 0xCC, 0xDD,       //  000D    LD   DE, CCDDh
        0x21, 0xEE, 0xFF,       //  0010    LD   HL, EEFFh
        0xD9,                   //  0013    EXX
        0x76      };            //  0014    HALT

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

    if (    ( CPU_REG_BC                  != 0x2211 )
         || ( CPU_REG_BC_                 != 0xBBAA )
         || ( CPU_REG_DE                  != 0x4433 )
         || ( CPU_REG_DE_                 != 0xDDCC )
         || ( CPU_REG_HL                  != 0x6655 )
         || ( CPU_REG_HL_                 != 0xFFEE ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_exx_00 failed:     [exx          ]\n" );
        printf( "POST: BC   = 0x%04X\n", CPU_REG_BC  );
        printf( "POST: BC'  = 0x%04X\n", CPU_REG_BC_ );
        printf( "POST: DE   = 0x%04X\n", CPU_REG_DE  );
        printf( "POST: DE'  = 0x%04X\n", CPU_REG_DE_ );
        printf( "POST: HL   = 0x%04X\n", CPU_REG_HL  );
        printf( "POST: HL'  = 0x%04X\n", CPU_REG_HL_ );

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
 *  EXCHANGE Power On Self Test
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
ex_post(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                 */
    int                         post_rc;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Assume a successful test run.
    post_rc = true;

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
        if ( post_rc == true )      post_rc = tc_ex_dehl_00( );     //  EX   DE, HL
        if ( post_rc == true )      post_rc = tc_ex_sphl_00( );     //  EX   (SP), HL

        //  Z80 ONLY instructions
        if( CPU == CPU_Z80 )
        {
            if ( post_rc == true )  post_rc = tc_ex_afaf_00( );     //  EX   AF, AF'
            if ( post_rc == true )  post_rc = tc_exx_00( );         //  EXX
        }

        //  Was the test suite successfully complete :
        if( post_rc == true )
        {
            //  YES:    Write a completion message
            printf( "POST: EX      complete %s mode.\n",
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