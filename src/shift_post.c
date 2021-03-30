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

/****************************************************************************/
/**
 *  RLCA
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
tc_rlca_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x3E, 0xAA,         //  0000    LD  A,x'AA
            0x07,               //  0002    RLCA
            0x76      };        //  0003    HALT

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

    if (    (   GET_A( )                 !=        0x55 )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_rlca_00 failed:     [rlca  ]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );
        printf( "POST: F  = 0x%02X\n", GET_F( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  RLCA
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
tc_rlca_01(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x3E, 0x55,         //  0000    LD  A,x'55
            0x07,               //  0002    RLCA
            0x76      };        //  0003    HALT

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

    if (    (   GET_A( )                 !=        0xAA )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_rlca_01 failed:     [rlca  ]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );
        printf( "POST: F  = 0x%02X\n", GET_F( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  RLA
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
tc_rla_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x3E, 0x00,         //  0000    LD   A,x'00
            0x87,               //  0002    ADD  A, A
            0x3E, 0x55,         //  0003    LD   A,x'55
            0x17,               //  0005    RLA
            0x76      };        //  0006    HALT

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

    if (    (   GET_A( )                 !=        0xAA )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_rla_00 failed:      [rla   ]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );
        printf( "POST: F  = 0x%02X\n", GET_F( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  RLA
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
tc_rla_01(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x3E, 0x80,         //  0000    LD   A,x'80
            0x87,               //  0002    ADD  A, A
            0x3E, 0x88,         //  0003    LD   A,x'88
            0x17,               //  0005    RLA
            0x76      };        //  0006    HALT

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

    if (    (   GET_A( )                 !=        0x11 )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_rla_00 failed:      [rla   ]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );
        printf( "POST: F  = 0x%02X\n", GET_F( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  RRCA
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
tc_rrca_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x3E, 0x01,         //  0000    LD  A,x'01
            0x0F,               //  0002    RRCA
            0x76      };        //  0003    HALT

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

    if (    (   GET_A( )                 !=        0x80 )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_rrca_00 failed:     [rrca  ]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );
        printf( "POST: F  = 0x%02X\n", GET_F( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  RRCA
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
tc_rrca_01(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x3E, 0x10,         //  0000    LD  A,x'10
            0x0F,               //  0002    RRCA
            0x76      };        //  0003    HALT

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

    if (    (   GET_A( )                 !=        0x08 )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_rrca_01 failed:     [rrca  ]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );
        printf( "POST: F  = 0x%02X\n", GET_F( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  RRA
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
tc_rra_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x3E, 0x00,         //  0000    LD   A,x'00
            0x87,               //  0002    ADD  A, A
            0x3E, 0x22,         //  0003    LD   A,x'22
            0x1F,               //  0005    RRA
            0x76      };        //  0006    HALT

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

    if (    (   GET_A( )                 !=        0x11 )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_rra_00 failed:      [rra   ]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );
        printf( "POST: F  = 0x%02X\n", GET_F( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  RRD
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
tc_rrd_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x20,             //  0000    LD   A,x'20
        0x21, 0X30, 0X00,       //  0002    LD  HL, 0030h
        0x77,                   //  0005    LD   (HL), A
        0x3E, 0x84,             //  0006    LD   A,x'84
        0xED, 0x67,             //  0008    RRD
        0x76      };            //  000A    HALT

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

    if (    ( GET_A( )               !=    0x80 )
         || ( CPU_REG_HL             !=  0x0030 )
         || ( memory_get_8( 0x0030 ) !=    0x42 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_rrd_00 failed:      [rrd   ]\n" );
        printf( "POST: A    =   0x%02X\n", GET_A( ) );
        printf( "POST: HL   = 0x%04X\n", CPU_REG_HL );
        printf( "POST: (HL) =   0x%02X\n", memory_get_8( CPU_REG_HL ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  RRA
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
tc_rra_01(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x3E, 0x80,         //  0000    LD   A,x'80
            0x87,               //  0002    ADD  A, A
            0x3E, 0x45,         //  0003    LD   A,x'45
            0x1F,               //  0005    RRA
            0x76      };        //  0006    HALT

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

    if (    (   GET_A( )                 !=        0xA2 )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_rra_01 failed:      [rra   ]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );
        printf( "POST: F  = 0x%02X\n", GET_F( ) );

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
 *  SHIFT / ROTATE Power On Self Test
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
shift_post(
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
     *  Power On Self Test
     ************************************************************************/

    //  @NOTE:  These tests are run in a very specific order.
    //          DO NOT change the order without understanding why
    //          the order is the way it is.

    //  @NOTE:  Some [definitely not all] instructions behave different
    //          between the 8080 and Z80.  Running both at a minimum will
    //          exercise both instruction maps.

    for( CPU = CPU_I80;
         CPU <= CPU_Z80;
         CPU += 1 )
    {
        if ( post_rc == true )      post_rc = tc_rlca_00( );        //  RLCA
        if ( post_rc == true )      post_rc = tc_rlca_01( );        //  RLCA

        if ( post_rc == true )      post_rc = tc_rla_00( );         //  RLA
        if ( post_rc == true )      post_rc = tc_rla_01( );         //  RLA

        if ( post_rc == true )      post_rc = tc_rrca_00( );        //  RRCA
        if ( post_rc == true )      post_rc = tc_rrca_01( );        //  RRCA

        if ( post_rc == true )      post_rc = tc_rra_00( );         //  RRA
        if ( post_rc == true )      post_rc = tc_rra_01( );         //  RRA

        //  Z80 ONLY instructions
        if( CPU == CPU_Z80 )
        {
            if ( post_rc == true )  post_rc = tc_rrd_00( );         //  RRD
        }

        //  Was the test suite successfully complete :
        if( post_rc == true )
        {
            //  YES:    Write a completion message
            printf( "POST: SHIFT   complete %s mode.\n",
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