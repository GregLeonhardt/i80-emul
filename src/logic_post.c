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
 *  AND     B
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
tc_and_r_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x06, 0xFF,         //  0000    LD  B,x'FF
            0x3E, 0x77,         //  0002    LD  A,x'77
            0xA0,               //  0004    AND B
            0x76      };        //  0005    HALT

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

    if ( GET_A( ) != 0x77 )
    {
        //  NO:     Write an error message
        printf( "POST: tc_and_r_00 failed:     [and  B]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  AND     C
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
tc_and_r_01(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x0E, 0x00,         //  0000    LD  C,x'00
            0x3E, 0xFF,         //  0002    LD  A,x'FF
            0xA1,               //  0004    AND C
            0x76      };        //  0005    HALT

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

    if ( GET_A( ) != 0x00 )
    {
        //  NO:     Write an error message
        printf( "POST: tc_and_r_01 failed:     [and  C]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  TEST_002:       AND     D
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
tc_and_r_02(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x16, 0xFF,         //  0000    LD  D,x'00
            0x3E, 0x00,         //  0002    LD  A,x'FF
            0xA2,               //  0004    AND D
            0x76      };        //  0005    HALT

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

    if ( GET_A( ) != 0x00 )
    {
        //  NO:     Write an error message
        printf( "POST: tc_and_r_02 failed:     [and  D]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  AND     E
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
tc_and_r_03(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x1E, 0x00,         //  0000    LD  E,x'00
            0x3E, 0xFF,         //  0002    LD  A,x'FF
            0xA3,               //  0004    AND E
            0x76      };        //  0005    HALT

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

    if ( GET_A( ) != 0x00 )
    {
        //  NO:     Write an error message
        printf( "POST: tc_and_r_03 failed:     [and  E]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  AND     H
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
tc_and_r_04(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x26, 0xFF,         //  0000    LD  H,x'FF
            0x3E, 0x01,         //  0002    LD  A,x'01
            0xA4,               //  0004    AND H
            0x76      };        //  0005    HALT

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

    if ( GET_A( ) != 0x01 )
    {
        //  NO:     Write an error message
        printf( "POST: tc_and_r_04 failed:     [and  H]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  AND     L
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
tc_and_r_05(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x2E, 0xFF,         //  0000    LD  L,x'FF
            0x3E, 0xFF,         //  0002    LD  A,x'FF
            0xA5,               //  0004    AND L
            0x76      };        //  0005    HALT

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

    if ( GET_A( ) != 0xFF )
    {
        //  NO:     Write an error message
        printf( "POST: tc_and_r_05 failed:     [and  L]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  AND     A
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
tc_and_r_06(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x3E, 0xA5,         //  0000    LD  A,x'A5
            0xA7,               //  0002    AND A
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

    if ( GET_A( ) != 0xA5 )
    {
        //  NO:     Write an error message
        printf( "POST: tc_and_r_06 failed:     [and  A]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  AND     n
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
tc_and_n_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x3E, 0xA5,         //  0000    LD  A,x'A5
            0xEE, 0x03,         //  0002    AND A,x'03
            0x76      };        //  0004    HALT

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

    if ( GET_A( ) != 0xA6 )
    {
        //  NO:     Write an error message
        printf( "POST: tc_and_n_00 failed:     [and  n]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  AND     (HL)
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
tc_and_hl_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x21, 0x00, 0x20,   //  0000    LD, HL, x'0020
            0x36, 0x7C,         //  0003    LD  (HL), x'7C
            0x3E, 0xEF,         //  0005    LD  A,x'EF
            0xA6,               //  0002    AND (HL)
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

    if ( GET_A( ) != 0x6C )
    {
        //  NO:     Write an error message
        printf( "POST: tc_and_hl_00 failed:     [and  (hl)]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  OR      B
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
tc_or_r_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x06, 0x01,         //  0000    LD  B,x'01
            0x3E, 0x70,         //  0002    LD  A,x'70
            0xB0,               //  0004    OR  B
            0x76      };        //  0005    HALT

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

    if ( GET_A( ) != 0x71 )
    {
        //  NO:     Write an error message
        printf( "POST: tc_or_r_00 failed:     [or   B]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  OR      C
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
tc_or_r_01(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x0E, 0xFF,         //  0000    LD  C,x'FF
            0x3E, 0x00,         //  0002    LD  A,x'00
            0xB1,               //  0004    OR  C
            0x76      };        //  0005    HALT

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

    if ( GET_A( ) != 0xFF )
    {
        //  NO:     Write an error message
        printf( "POST: tc_or_r_01 failed:     [ord  C]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  OR      D
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
tc_or_r_02(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x16, 0x12,         //  0000    LD  D,x'12
            0x3E, 0xC0,         //  0002    LD  A,x'C0
            0xB2,               //  0004    OR  D
            0x76      };        //  0005    HALT

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

    if ( GET_A( ) != 0xD2 )
    {
        //  NO:     Write an error message
        printf( "POST: tc_or_r_02 failed:     [or   D]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  OR      E
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
tc_or_r_03(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x1E, 0x55,         //  0000    LD  E,x'55
            0x3E, 0xAA,         //  0002    LD  A,x'AA
            0xB3,               //  0004    OR  E
            0x76      };        //  0005    HALT

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

    if ( GET_A( ) != 0xFF )
    {
        //  NO:     Write an error message
        printf( "POST: tc_or_r_03 failed:     [or   E]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  OR      H
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
tc_or_r_04(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x26, 0x01,         //  0000    LD  H,x'01
            0x3E, 0x02,         //  0002    LD  A,x'02
            0xB4,               //  0004    OR  H
            0x76      };        //  0005    HALT

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

    if ( GET_A( ) != 0x03 )
    {
        //  NO:     Write an error message
        printf( "POST: tc_or_r_04 failed:     [or   H]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  OR      L
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
tc_or_r_05(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x2E, 0x7F,         //  0000    LD  L,x'7F
            0x3E, 0x80,         //  0002    LD  A,x'80
            0xB5,               //  0004    OR  L
            0x76      };        //  0005    HALT

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

    if ( GET_A( ) != 0xFF )
    {
        //  NO:     Write an error message
        printf( "POST: tc_or_r_05 failed:     [or  L]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  OR      A
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
tc_or_r_06(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x3E, 0x5A,         //  0000    LD  A,x'5A
            0xB7,               //  0002    OR  A
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

    if ( GET_A( ) != 0x5A )
    {
        //  NO:     Write an error message
        printf( "POST: tc_or_r_06 failed:     [or   A]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  OR      n
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
tc_or_n_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x3E, 0x90,         //  0000    LD  A,x'90
            0xF6, 0x0F,         //  0002    OR  A,x'0F
            0x76      };        //  0004    HALT

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

    if ( GET_A( ) != 0x9F )
    {
        //  NO:     Write an error message
        printf( "POST: tc_or_n_00 failed:     [or   n]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  OR      (HL)
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
tc_or_hl_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x21, 0x00, 0x20,   //  0000    LD, HL, x'0020
            0x36, 0x21,         //  0003    LD  (HL), x'21
            0x3E, 0x08,         //  0005    LD  A,x'08
            0xB6,               //  0002    OR  (HL)
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

    if ( GET_A( ) != 0x29 )
    {
        //  NO:     Write an error message
        printf( "POST: tc_or_hl_00 failed:     [or   (hl)]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  XOR     B
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
tc_xor_r_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x06, 0x98,         //  0000    LD  B,x'98
            0x3E, 0xFF,         //  0002    LD  A,x'FF
            0xA8,               //  0004    XOR B
            0x76      };        //  0005    HALT

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

    if ( GET_A( ) != 0x67 )
    {
        //  NO:     Write an error message
        printf( "POST: tc_xor_r_00 failed:     [xor   B]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  XOR     C
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
tc_xor_r_01(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x0E, 0x49,         //  0000    LD  C,x'49
            0x3E, 0xAA,         //  0002    LD  A,x'AA
            0xA9,               //  0004    XOR C
            0x76      };        //  0005    HALT

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

    if ( GET_A( ) != 0xE3 )
    {
        //  NO:     Write an error message
        printf( "POST: tc_xor_r_01 failed:     [xord  C]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  XOR     D
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
tc_xor_r_02(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x16, 0xE3,         //  0000    LD  D,x'E3
            0x3E, 0xAA,         //  0002    LD  A,x'AA
            0xAA,               //  0004    XOR D
            0x76      };        //  0005    HALT

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

    if ( GET_A( ) != 0x49 )
    {
        //  NO:     Write an error message
        printf( "POST: tc_xor_r_02 failed:     [xor   D]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  XOR     E
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
tc_xor_r_03(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x1E, 0x55,         //  0000    LD  E,x'55
            0x3E, 0xAA,         //  0002    LD  A,x'AA
            0xAB,               //  0004    XOR E
            0x76      };        //  0005    HALT

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

    if ( GET_A( ) != 0xFF )
    {
        //  NO:     Write an error message
        printf( "POST: tc_xor_r_03 failed:     [xor   E]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  XOR     H
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
tc_xor_r_04(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x26, 0xF1,         //  0000    LD  H,x'F1
            0x3E, 0xF2,         //  0002    LD  A,x'F2
            0xAC,               //  0004    XOR H
            0x76      };        //  0005    HALT

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

    if ( GET_A( ) != 0x03 )
    {
        //  NO:     Write an error message
        printf( "POST: tc_xor_r_04 failed:     [xor   H]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  XOR     L
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
tc_xor_r_05(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x2E, 0x7F,         //  0000    LD  L,x'7F
            0x3E, 0x8F,         //  0002    LD  A,x'8F
            0xAD,               //  0004    XOR L
            0x76      };        //  0005    HALT

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

    if ( GET_A( ) != 0xF0 )
    {
        //  NO:     Write an error message
        printf( "POST: tc_xor_r_05 failed:     [xor  L]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  XOR     A
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
tc_xor_r_06(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x3E, 0x5A,         //  0000    LD  A,x'5A
            0xAF,               //  0002    XOR A
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

    if ( GET_A( ) != 0x00 )
    {
        //  NO:     Write an error message
        printf( "POST: tc_xor_r_06 failed:     [xor   A]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  XOR     n
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
tc_xor_n_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x3E, 0x93,         //  0000    LD  A,x'93
            0xEE, 0x0F,         //  0002    XOR A,x'0F
            0x76      };        //  0004    HALT

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

    if ( GET_A( ) != 0x9C )
    {
        //  NO:     Write an error message
        printf( "POST: tc_xor_n_00 failed:     [xor   n]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  XOR     (HL)
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
tc_xor_hl_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x21, 0x00, 0x20,   //  0000    LD, HL, x'0020
            0x36, 0x21,         //  0003    LD  (HL), x'21
            0x3E, 0x08,         //  0005    LD  A,x'08
            0xAE,               //  0002    XOR (HL)
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

    if ( GET_A( ) != 0x29 )
    {
        //  NO:     Write an error message
        printf( "POST: tc_xor_hl_00 failed:     [xor   (hl)]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  CP      B
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
tc_cp_r_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x06, 0x01,         //  0000    LD  B,x'01
            0x3E, 0x70,         //  0002    LD  A,x'70
            0xB8,               //  0004    CP  B
            0x76      };        //  0005    HALT

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

    //  Intel 8080 and Zilog have different results.
    if( CPU == CPU_I80 )
    {
        if (    ( GET_A( )                   !=        0x70 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_cp_r_00 failed:     [cp   B]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0x70 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_cp_r_00 failed:     [cp   B]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  CP      C
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
tc_cp_r_01(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x0E, 0xFF,         //  0000    LD  C,x'FF
            0x3E, 0x00,         //  0002    LD  A,x'00
            0xB9,               //  0004    CP  C
            0x76      };        //  0005    HALT

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

    //  Intel 8080 and Zilog have different results.
    if( CPU == CPU_I80 )
    {
        if (    ( GET_A( )                   !=        0x00 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_cp_r_01 failed:     [ord  C]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0x00 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_cp_r_01 failed:     [ord  C]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  CP      D
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
tc_cp_r_02(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x16, 0xC0,         //  0000    LD  D,x'C0
            0x3E, 0xC0,         //  0002    LD  A,x'C0
            0xBA,               //  0004    CP  D
            0x76      };        //  0005    HALT

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

    //  Intel 8080 and Zilog have different results.
    if( CPU == CPU_I80 )
    {
        if (    ( GET_A( )                   !=        0xC0 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=  CPU_FLAG_Z )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_cp_r_00 failed:     [cp   D]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0xC0 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=  CPU_FLAG_Z )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_cp_r_00 failed:     [cp   D]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  CP      E
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
tc_cp_r_03(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x1E, 0xAA,         //  0000    LD  E,x'AA
            0x3E, 0xAA,         //  0002    LD  A,x'AA
            0xBB,               //  0004    CP  E
            0x76      };        //  0005    HALT

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

    //  Intel 8080 and Zilog have different results.
    if( CPU == CPU_I80 )
    {
        if (    ( GET_A( )                   !=        0xAA )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=  CPU_FLAG_Z )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_cp_r_03 failed:     [cp   E]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0xAA )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=  CPU_FLAG_Z )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_cp_r_03 failed:     [cp   E]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  CP      H
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
tc_cp_r_04(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x26, 0x01,         //  0000    LD  H,x'01
            0x3E, 0x02,         //  0002    LD  A,x'02
            0xBC,               //  0004    CP  H
            0x76      };        //  0005    HALT

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

    //  Intel 8080 and Zilog have different results.
    if( CPU == CPU_I80 )
    {
        if (    ( GET_A( )                   !=        0x02 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_cp_r_04 failed:     [cp   H]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0x02 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_cp_r_04 failed:     [cp   H]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  CP      L
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
tc_cp_r_05(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x2E, 0x7F,         //  0000    LD  L,x'7F
            0x3E, 0x80,         //  0002    LD  A,x'80
            0xBD,               //  0004    CP  L
            0x76      };        //  0005    HALT

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

    //  Intel 8080 and Zilog have different results.
    if( CPU == CPU_I80 )
    {
        if (    ( GET_A( )                   !=        0x80 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_cp_r_05 failed:     [cp  L]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0x80 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_cp_r_05 failed:     [cp  L]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  CP      A
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
tc_cp_r_06(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x3E, 0x5A,         //  0000    LD  A,x'5A
            0xBF,               //  0002    CP  A
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

    //  Intel 8080 and Zilog have different results.
    if( CPU == CPU_I80 )
    {
        if (    ( GET_A( )                   !=        0x5A )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=  CPU_FLAG_Z )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_cp_r_06 failed:     [cp   A]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0x5A )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=  CPU_FLAG_Z )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_cp_r_06 failed:     [cp   A]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  CP      n
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
tc_cp_n_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x3E, 0x90,         //  0000    LD  A,x'90
            0xFE, 0x0F,         //  0002    CP  A,x'0F
            0x76      };        //  0004    HALT

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

    //  Intel 8080 and Zilog have different results.
    if( CPU == CPU_I80 )
    {
        if (    ( GET_A( )                   !=        0x90 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_cp_n_00 failed:     [cp   n]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0x90 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_cp_n_00 failed:     [cp   n]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  CP      (HL)
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
tc_cp_hl_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x21, 0x00, 0x20,   //  0000    LD, HL, x'0020
            0x36, 0x21,         //  0003    LD  (HL), x'21
            0x3E, 0x08,         //  0005    LD  A,x'08
            0xBE,               //  0002    CP  (HL)
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

    //  Intel 8080 and Zilog have different results.
    if( CPU == CPU_I80 )
    {
        if (    ( GET_A( )                   !=        0x08 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_cp_hl_00 failed:     [cp   (hl)]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0x08 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_cp_hl_00 failed:     [cp   (hl)]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  CPD
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
tc_cpd_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        //  Initial register load   SOURCE
        0x21, 0x30, 0x00,       //  0000    LD   HL, 0030h  ;Initial pointer
        0x06, 0x20,             //  0003    LD   B, 020h    ;Byte Count
        0x3E, 0x00,             //  0005    LD   A, 000h    ;Fill data
        0x77,                   //  0007 R: LD   (HL), A    ;Start filling memory
        0x2C,                   //  0008    INC  L          ;Increment pointer
        0x10, 0xFC,             //  0009    DJNZ R          ;Loop till B == 0

        0x3E, 0x11,             //  000B    LD   A, 011h    ;Target byte
        0x32, 0x33, 0x00,       //  000D    LD   0033h, A   ;Store it

        //  Start the test
        0x21, 0x4F, 0x00,       //  0010    LD   HL, 004Fh  ;Search pointer
        0x01, 0x20, 0x00,       //  0013    LD   BC, 0020h  ;Byte Count
        0xED, 0xA9,             //  0016 W: CPD             ;Copy DE<-HL
        0xCA, 0x1F, 0x00,       //  0018    JP   Z, E       ;Break if zero
        0xEA, 0x16, 0x00,       //  001B    JP   PE, W      ;JP if BC != 0
        0x76,                   //  001E    HALT            ;ERROR END
        0x76      };            //  001F E: HALT            ;THE END

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

    if (    ( CPU_REG_PC != 0x0020 )
         || ( CPU_REG_HL != 0x0032 )
         || ( CPU_REG_BC != 0x0003 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_cpd_00 failed:     [cpd      ]\n" );
        printf( "POST: PC = 0x%04X\n", CPU_REG_PC );
        printf( "POST: HL = 0x%04X\n", CPU_REG_HL );
        printf( "POST: BC = 0x%04X\n", CPU_REG_BC );

        memory_dump( 0x0030, 32 );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  CPI
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
tc_cpi_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        //  Initial register load   SOURCE
        0x21, 0x30, 0x00,       //  0000    LD   HL, 0030h  ;Initial pointer
        0x06, 0x20,             //  0003    LD   B, 020h    ;Byte Count
        0x3E, 0x00,             //  0005    LD   A, 000h    ;Fill data
        0x77,                   //  0007 R: LD   (HL), A    ;Start filling memory
        0x2C,                   //  0008    INC  L          ;Increment pointer
        0x10, 0xFC,             //  0009    DJNZ R          ;Loop till B == 0

        0x3E, 0x33,             //  000B    LD   A, 033h    ;Target byte
        0x32, 0x43, 0x00,       //  000D    LD   0043h, A   ;Store it

        //  Start the test
        0x21, 0x30, 0x00,       //  0010    LD   HL, 0030h  ;Search pointer
        0x01, 0x20, 0x00,       //  0013    LD   BC, 0020h  ;Byte Count
        0xED, 0xA1,             //  0016 W: CPD             ;Copy DE<-HL
        0xCA, 0x1F, 0x00,       //  0018    JP   Z, E       ;Break if zero
        0xEA, 0x16, 0x00,       //  001B    JP   PE, W      ;JP if BC != 0
        0x76,                   //  001E    HALT            ;ERROR END
        0x76      };            //  001F E: HALT            ;THE END

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

    if (    ( CPU_REG_PC != 0x0020 )
         || ( CPU_REG_HL != 0x0044 )
         || ( CPU_REG_BC != 0x000C ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_cpi_00 failed:     [cpi      ]\n" );
        printf( "POST: PC = 0x%04X\n", CPU_REG_PC );
        printf( "POST: HL = 0x%04X\n", CPU_REG_HL );
        printf( "POST: BC = 0x%04X\n", CPU_REG_BC );

        memory_dump( 0x0030, 32 );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  CPDR
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
tc_cpdr_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        //  Initial register load   SOURCE
        0x21, 0x30, 0x00,       //  0000    LD   HL, 0030h  ;Initial pointer
        0x06, 0x20,             //  0003    LD   B, 020h    ;Byte Count
        0x3E, 0x00,             //  0005    LD   A, 000h    ;Fill data
        0x77,                   //  0007 R: LD   (HL), A    ;Start filling memory
        0x2C,                   //  0008    INC  L          ;Increment pointer
        0x10, 0xFC,             //  0009    DJNZ R          ;Loop till B == 0

        0x3E, 0x11,             //  000B    LD   A, 011h    ;Target byte
        0x32, 0x33, 0x00,       //  000D    LD   0033h, A   ;Store it

        //  Start the test
        0x21, 0x4F, 0x00,       //  0010    LD   HL, 004Fh  ;Search pointer
        0x01, 0x20, 0x00,       //  0013    LD   BC, 0020h  ;Byte Count
        0xED, 0xB9,             //  0016    CPDR            ;Copy DE<-HL
        0x76      };            //  0018    HALT            ;THE END

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

    if (    ( CPU_REG_PC != 0x0019 )
         || ( CPU_REG_HL != 0x0032 )
         || ( CPU_REG_BC != 0x0003 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_cpdr_00 failed:    [cpdr     ]\n" );
        printf( "POST: PC = 0x%04X\n", CPU_REG_PC );
        printf( "POST: HL = 0x%04X\n", CPU_REG_HL );
        printf( "POST: BC = 0x%04X\n", CPU_REG_BC );

        memory_dump( 0x0030, 32 );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  CPIR
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
tc_cpir_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        //  Initial register load   SOURCE
        0x21, 0x30, 0x00,       //  0000    LD   HL, 0030h  ;Initial pointer
        0x06, 0x20,             //  0003    LD   B, 020h    ;Byte Count
        0x3E, 0x00,             //  0005    LD   A, 000h    ;Fill data
        0x77,                   //  0007    LD   (HL), A    ;Start filling memory
        0x2C,                   //  0008    INC  L          ;Increment pointer
        0x10, 0xFC,             //  0009    DJNZ R          ;Loop till B == 0

        0x3E, 0x33,             //  000B    LD   A, 033h    ;Target byte
        0x32, 0x43, 0x00,       //  000D    LD   0043h, A   ;Store it

        //  Start the test
        0x21, 0x30, 0x00,       //  0010    LD   HL, 0030h  ;Search pointer
        0x01, 0x20, 0x00,       //  0013    LD   BC, 0020h  ;Byte Count
        0xED, 0xB1,             //  0016    CPD             ;Copy DE<-HL
        0x76      };            //  001F    HALT            ;THE END

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

    if (    ( CPU_REG_PC != 0x0019 )
         || ( CPU_REG_HL != 0x0044 )
         || ( CPU_REG_BC != 0x000C ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_cpir_00 failed:    [cpir     ]\n" );
        printf( "POST: PC = 0x%04X\n", CPU_REG_PC );
        printf( "POST: HL = 0x%04X\n", CPU_REG_HL );
        printf( "POST: BC = 0x%04X\n", CPU_REG_BC );

        memory_dump( 0x0030, 32 );

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
 *  LOAD Power On Self Test
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
logic_post(
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
        if ( post_rc == true )      post_rc = tc_and_r_00( );       //  AND  B
        if ( post_rc == true )      post_rc = tc_and_r_01( );       //  AND  C
        if ( post_rc == true )      post_rc = tc_and_r_02( );       //  AND  D
        if ( post_rc == true )      post_rc = tc_and_r_03( );       //  AND  E
        if ( post_rc == true )      post_rc = tc_and_r_04( );       //  AND  H
        if ( post_rc == true )      post_rc = tc_and_r_05( );       //  AND  L
        if ( post_rc == true )      post_rc = tc_and_r_06( );       //  AND  A
        if ( post_rc == true )      post_rc = tc_and_n_00( );       //  AND  n
        if ( post_rc == true )      post_rc = tc_and_hl_00( );      //  AND  (HL)

        if ( post_rc == true )      post_rc = tc_or_r_00( );        //  OR   B
        if ( post_rc == true )      post_rc = tc_or_r_01( );        //  OR   C
        if ( post_rc == true )      post_rc = tc_or_r_02( );        //  OR   D
        if ( post_rc == true )      post_rc = tc_or_r_03( );        //  OR   E
        if ( post_rc == true )      post_rc = tc_or_r_04( );        //  OR   H
        if ( post_rc == true )      post_rc = tc_or_r_05( );        //  OR   L
        if ( post_rc == true )      post_rc = tc_or_r_06( );        //  OR   A
        if ( post_rc == true )      post_rc = tc_or_n_00( );        //  OR   n
        if ( post_rc == true )      post_rc = tc_or_hl_00( );       //  OR   (HL)

        if ( post_rc == true )      post_rc = tc_xor_r_00( );       //  XOR   B
        if ( post_rc == true )      post_rc = tc_xor_r_01( );       //  XOR   C
        if ( post_rc == true )      post_rc = tc_xor_r_02( );       //  XOR   D
        if ( post_rc == true )      post_rc = tc_xor_r_03( );       //  XOR   E
        if ( post_rc == true )      post_rc = tc_xor_r_04( );       //  XOR   H
        if ( post_rc == true )      post_rc = tc_xor_r_05( );       //  XOR   L
        if ( post_rc == true )      post_rc = tc_xor_r_06( );       //  XOR   A
        if ( post_rc == true )      post_rc = tc_xor_n_00( );       //  XOR   n
        if ( post_rc == true )      post_rc = tc_xor_hl_00( );      //  XOR   (HL)

        if ( post_rc == true )      post_rc = tc_cp_r_00( );        //  CP   B
        if ( post_rc == true )      post_rc = tc_cp_r_01( );        //  CP   C
        if ( post_rc == true )      post_rc = tc_cp_r_02( );        //  CP   D
        if ( post_rc == true )      post_rc = tc_cp_r_03( );        //  CP   E
        if ( post_rc == true )      post_rc = tc_cp_r_04( );        //  CP   H
        if ( post_rc == true )      post_rc = tc_cp_r_05( );        //  CP   L
        if ( post_rc == true )      post_rc = tc_cp_r_06( );        //  CP   A
        if ( post_rc == true )      post_rc = tc_cp_n_00( );        //  CP   n
        if ( post_rc == true )      post_rc = tc_cp_hl_00( );       //  CP   (HL)

        //  Z80 ONLY instructions
        if( CPU == CPU_Z80 )
        {
            if ( post_rc == true )  post_rc = tc_cpd_00( );         //  CPD
            if ( post_rc == true )  post_rc = tc_cpi_00( );         //  CPI
            if ( post_rc == true )  post_rc = tc_cpdr_00( );        //  CPDR
            if ( post_rc == true )  post_rc = tc_cpir_00( );        //  CPIR
        }

        //  Was the test suite successfully complete :
        if( post_rc == true )
        {
            //  YES:    Write a completion message
            printf( "POST: LOGIC   complete %s mode.\n",
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