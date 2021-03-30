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
 *  ADD     A, B
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      0x40 + 0x40 = 0x80
 *      Flags tested:    S   Z   H  PV   C
 *                       1   0   0   1   0
 *
 ****************************************************************************/

static
int
tc_add_r_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x40,             //  0000    LD   A, 0x40
        0x06, 0x40,             //  0003    LD   B, 0x40
        0x80,                   //  0006    ADD  A, B
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

    //  Intel 8080 and Zilog have different results.
    if( CPU == CPU_I80 )
    {
        if (    ( GET_A( )                   !=        0x80 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_add_r_00 failed:     [add  a, b]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0x80 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_add_r_00 failed:     [add  a, b]\n" );
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
 *  ADD     A, C
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      1 + -1 = 0
 *      Flags tested:    S   Z   H  PV   C
 *                       0   1   1   0   1
 *
 ****************************************************************************/

static
int
tc_add_r_01(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0xFF,             //  0000    LD   A, x'FE
        0x0E, 0x01,             //  0003    LD   C, x'01
        0x81,                   //  0006    ADD  A, C
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

    //  Intel 8080 and Zilog have different results.
    if( CPU == CPU_I80 )
    {
        if (    ( GET_A( )                   !=  (uint8_t)0 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=  CPU_FLAG_Z )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_add_r_01 failed:     [add  a, c]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=  (uint8_t)0 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=  CPU_FLAG_Z )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_add_r_01 failed:     [add  a, c]\n" );
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
 *  ADD     A, D
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      3 + -2 = 1
 *      Flags tested:    S   Z   H  PV   C
 *                       0   0   1   0   1
 *
 ****************************************************************************/

static
int
tc_add_r_02(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x78,             //  0000    LD   A, x'78
        0x16, 0x69,             //  0003    LD   D, x'69
        0x82,                   //  0006    ADD  A, D
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

    //  Intel 8080 and Zilog have different results.
    if( CPU == CPU_I80 )
    {
        if (    ( GET_A( )                   !=        0xE1 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_add_r_02 failed:     [add  a, d]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0xE1 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_add_r_02 failed:     [add  a, d]\n" );
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
 *  ADD     A, E
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      3 + -5 = -2
 *      Flags tested:    S   Z   H  PV   C
 *                       1   0   0   0   0
 *
 ****************************************************************************/

static
int
tc_add_r_03(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0xFB,             //  0000    LD   A, x'FB
        0x1E, 0x03,             //  0003    LD   E, x'03
        0x83,                   //  0006    ADD  A, E
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

    //  Intel 8080 and Zilog have different results.
    if( CPU == CPU_I80 )
    {
        if (    ( GET_A( )                   !=        0xFE )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_add_r_03 failed:     [add  a, e]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0xFE )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_add_r_03 failed:     [add  a, e]\n" );
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
 *  ADD     A, H
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      -3 + 5 = 2
 *      Flags tested:    S   Z   H  PV   C
 *                       0   0   1   0   1
 *
 ****************************************************************************/

static
int
tc_add_r_04(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x05,             //  0000    LD   A, x'05
        0x26, 0xFD,             //  0003    LD   H, x'FD
        0x84,                   //  0006    ADD  A, H
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

    //  Intel 8080 and Zilog have different results.
    if( CPU == CPU_I80 )
    {
        if (    ( GET_A( )                   !=        0x02 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_add_r_04 failed:     [add  a, h]\n" );
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
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_add_r_04 failed:     [add  a, h]\n" );
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
 *  ADD     A, L
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      10 + -10 = 0
 *      Flags tested:    S   Z   H  PV   C
 *                       0   1   1   0   1
 *
 ****************************************************************************/

static
int
tc_add_r_05(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0xEF,             //  0000    LD   A, x'EF
        0x2E, 0x11,             //  0003    LD   L, x'11
        0x85,                   //  0006    ADD  A, L
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

    //  Intel 8080 and Zilog have different results.
    if( CPU == CPU_I80 )
    {
        if (    ( GET_A( )                   !=        0x00 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=  CPU_FLAG_Z )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_add_r_05 failed:     [add  a, l]\n" );
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
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=  CPU_FLAG_Z )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_add_r_05 failed:     [add  a, l]\n" );
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
 *  ADD     A, A
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      49 + 49 = 98
 *      Flags tested:    S   Z   H  PV   C
 *                       0   0   0   0   0
 *
 ****************************************************************************/

static
int
tc_add_r_06(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x31,             //  0000    LD   A, x'31
        0x3E, 0x31,             //  0003    LD   A, x'31
        0x87,                   //  0006    ADD  A, A
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

    //  Intel 8080 and Zilog have different results.
    if( CPU == CPU_I80 )
    {
        if (    ( GET_A( )                   !=        0x62 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_add_r_06 failed:     [add  a, a]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0x62 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_add_r_06 failed:     [add  a, a]\n" );
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
 *  ADD     A, n
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      -34 + 34 = 00
 *      Flags tested:    S   Z   H  PV   C
 *                       0   1   1   0   1
 *
 ****************************************************************************/

static
int
tc_add_n_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x99,             //  0000    LD   A, x'99
        0xC6, 0x77,             //  0002    ADD  A, x'77
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

    //  Intel 8080 and Zilog have different results.
    if( CPU == CPU_I80 )
    {
        if (    ( GET_A( )                   !=        0x10 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_add_n_00 failed:     [add  a, n]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0x10 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_add_n_00 failed:     [add  a, n]\n" );
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
 *  ADD     A, (HL)
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      -100 + -43 = -57
 *      Flags tested:    S   Z   H  PV   C
 *                       1   0   1   0   0
 *
 ****************************************************************************/

static
int
tc_add_hl_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x21, 0x00, 0x20,       //  0000    LD  HL, 0x0020
        0x36, 0xA6,             //  0003    LD  (HL), x'A6
        0x3E, 0x12,             //  0005    LD   A,  x'12
        0x86,                   //  0006    ADD  A, (HL)
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

    //  Intel 8080 and Zilog have different results.
    if( CPU == CPU_I80 )
    {
        if (    ( GET_A( )                   !=        0xB8 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_add_hl_00 failed:     [add  a, (hl)]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0xB8 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_add_hl_00 failed:     [add  a, (hl)]\n" );
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
 *  ADC     A, B
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      0x80 + ( 0x80 + 0x80 ) = 0x81
 *      Flags tested:    S   Z   H  PV   C
 *                       1   0   0   0   0
 *
 ****************************************************************************/

static
int
tc_adc_r_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x80,             //  0000    LD   A, 0x80
        0x06, 0x80,             //  0003    LD   B, 0x80
        0x80,                   //  0006    ADD  A, B
        0x88,                   //  0007    ADC  A, B
        0x76      };            //  0008    HALT

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
        if (    ( GET_A( )                   !=        0x81 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_adc_r_00 failed:     [adc  a, b]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0x81 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_adc_r_00 failed:     [adc  a, b]\n" );
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
 *  ADC     A, C
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      0x20 + ( 0x20 + 0x20 ) = 0x60
 *      Flags tested:    S   Z   H  PV   C
 *                       0   0   0   0   0
 *
 ****************************************************************************/

static
int
tc_adc_r_01(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x20,             //  0000    LD   A, 0x20
        0x0E, 0x20,             //  0003    LD   C, 0x20
        0x81,                   //  0006    ADD  A, C
        0x89,                   //  0007    ADC  A, C
        0x76      };            //  0008    HALT

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
        if (    ( GET_A( )                   !=        0x60 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_adc_r_01 failed:     [adc  a, c]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0x60 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_adc_r_01 failed:     [adc  a, c]\n" );
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
 *  ADC     A, D
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      0x02 + ( 0xFC + 0x02 ) = 0x00
 *      Flags tested:    S   Z   H  PV   C
 *                       0   1   1   0   1
 *
 ****************************************************************************/

static
int
tc_adc_r_02(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0xFC,             //  0000    LD   A, 0xFC
        0x16, 0x02,             //  0003    LD   D, 0x02
        0x82,                   //  0006    ADD  A, D
        0x8A,                   //  0007    ADC  A, D
        0x76      };            //  0008    HALT

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
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=  CPU_FLAG_Z )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_adc_r_02 failed:     [adc  a, d]\n" );
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
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=  CPU_FLAG_Z )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_adc_r_02 failed:     [adc  a, d]\n" );
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
 *  ADC     A, E
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      0x7F + ( 0x7F + 0x0E ) = 0x0C
 *      Flags tested:    S   Z   H  PV   C
 *                       0   0   1   0   0
 *
 ****************************************************************************/

static
int
tc_adc_r_03(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x0E,             //  0000    LD   A, 0x0E
        0x1E, 0x7F,             //  0003    LD   E, 0x7F
        0x83,                   //  0006    ADD  A, E
        0x8B,                   //  0007    ADC  A, E
        0x76      };            //  0008    HALT

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
        if (    ( GET_A( )                   !=        0x0C )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_adc_r_03 failed:     [adc  a, e]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0x0C )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_adc_r_03 failed:     [adc  a, e]\n" );
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
 *  ADC     A, H
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      0x22 + ( 0x22 + 0x11 ) = 0x55
 *      Flags tested:    S   Z   H  PV   C
 *                       0   0   0   0   0
 *
 ****************************************************************************/

static
int
tc_adc_r_04(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x11,             //  0000    LD   A, 0x11
        0x26, 0x22,             //  0003    LD   H, 0x22
        0x84,                   //  0006    ADD  A, H
        0x8C,                   //  0007    ADC  A, H
        0x76      };            //  0008    HALT

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
        if (    ( GET_A( )                   !=        0x55 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_adc_r_04 failed:     [adc  a, h]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0x55 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_adc_r_04 failed:     [adc  a, h]\n" );
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
 *  ADC     A, L
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      0x22 + ( 0x22 + 0x11 ) = 0x55
 *      Flags tested:    S   Z   H  PV   C
 *                       0   0   0   0   0
 *
 ****************************************************************************/

static
int
tc_adc_r_05(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x11,             //  0000    LD   A, 0x11
        0x2E, 0x22,             //  0003    LD   L, 0x22
        0x85,                   //  0006    ADD  A, L
        0x8D,                   //  0007    ADC  A, L
        0x76      };            //  0008    HALT

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
        if (    ( GET_A( )                   !=        0x55 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_adc_r_05 failed:     [adc  a, l]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0x55 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_adc_r_05 failed:     [adc  a, l]\n" );
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
 *  ADC     A, A
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      ( 0x11 + 0x11 ) + ( 0x11 + 0x11 ) = 0x44
 *      Flags tested:    S   Z   H  PV   C
 *                       0   0   0   0   0
 *
 ****************************************************************************/

static
int
tc_adc_r_06(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x11,             //  0000    LD   A, 0x11
        0x87,                   //  0006    ADD  A, A
        0x8F,                   //  0007    ADC  A, A
        0x76      };            //  0008    HALT

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
        if (    ( GET_A( )                   !=        0x44 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_adc_r_06 failed:     [adc  a, a]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0x44 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_adc_r_06 failed:     [adc  a, a]\n" );
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
 *  ADC     A, n
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      ( -34 + 34 ) + -34  = -33
 *      Flags tested:    S   Z   H  PV   C
 *                       1   0   0   0   0
 *
 ****************************************************************************/

static
int
tc_adc_n_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x00,             //  0000    LD   A, x'00
        0xC6, 0x00,             //  0002    ADD  A, x'00
        0xCE, 0x00,             //  0004    ADC  A, x'00
        0x76      };            //  0006    HALT

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
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=  CPU_FLAG_Z )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_adc_n_00 failed:     [adc  a, n]\n" );
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
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=  CPU_FLAG_Z )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_adc_n_00 failed:     [adc  a, n]\n" );
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
 *  ADC     A, (HL)
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      -100 + ( -100 + 43 ) = 99
 *      Flags tested:    S   Z   H  PV   C
 *                       0   0   1   1   1
 *
 ****************************************************************************/

static
int
tc_adc_hl_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x21, 0x00, 0x20,       //  0000    LD  HL, 0x0003
        0x36, 0x12,             //  0003    LD  (HL), x'12
        0x3E, 0x80,             //  0005    LD   A,  x'80
        0x86,                   //  0006    ADD  A, (HL)
        0x8E,                   //  0007    ADC  A, (HL)
        0x76      };            //  0008    HALT

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
        if (    ( GET_A( )                   !=        0xA4 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_adc_hl_00 failed:     [adc  a, (hl)]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0xA4 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_adc_hl_00 failed:     [adc  a, (hl)]\n" );
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
 *  SUB     A, B
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      0x80 - 0x81 = 0x00
 *      Flags tested:    S   Z   H  PV   C
 *                       1   0   1   0   1
 *
 ****************************************************************************/

static
int
tc_sub_r_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x80,             //  0000    LD   A, 0x80
        0x06, 0x81,             //  0003    LD   B, 0x81
        0x90,                   //  0006    SUB  A, B
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

    //  Intel 8080 and Zilog have different results.
    if( CPU == CPU_I80 )
    {
        if (    ( GET_A( )                   !=       0xFF )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sub_r_00 failed:     [sub  a, b]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=       0xFF )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sub_r_00 failed:     [sub  a, b]\n" );
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
 *  SUB     A, C
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      0xFF - 0x01 = 0xFE
 *      Flags tested:    S   Z   H  PV   C
 *                       1   0   0   0   0
 *
 ****************************************************************************/

static
int
tc_sub_r_01(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0xFF,             //  0000    LD   A, x'FF
        0x0E, 0x01,             //  0003    LD   C, x'01
        0x91,                   //  0006    SUB  A, C
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

    //  Intel 8080 and Zilog have different results.
    if( CPU == CPU_I80 )
    {
        if (    ( GET_A( )                   !=        0xFE )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sub_r_01 failed:     [sub  a, c]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0xFE )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sub_r_01 failed:     [sub  a, c]\n" );
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
 *  SUB     A, D
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      0x03 - 0xFC = 0xF9
 *      Flags tested:    S   Z   H  PV   C
 *                       0   0   1   0   1
 *
 ****************************************************************************/

static
int
tc_sub_r_02(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x03,             //  0000    LD   A, x'03
        0x16, 0xFC,             //  0003    LD   D, x'FC
        0x92,                   //  0006    SUB  A, D
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

    //  Intel 8080 and Zilog have different results.
    if( CPU == CPU_I80 )
    {
        if (    ( GET_A( )                   !=        0x07 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sub_r_02 failed:     [sub  a, d]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0x07 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sub_r_02 failed:     [sub  a, d]\n" );
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
 *  SUB     A, E
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      0x03 - 0xD7 = 0x2C
 *      Flags tested:    S   Z   H  PV   C
 *                       0   0   1   0   1
 *
 ****************************************************************************/

static
int
tc_sub_r_03(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x03,             //  0000    LD   A, x'03
        0x1E, 0xD7,             //  0003    LD   E, x'D7
        0x93,                   //  0006    SUB  A, E
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

    //  Intel 8080 and Zilog have different results.
    if( CPU == CPU_I80 )
    {
        if (    ( GET_A( )                   !=        0x2C )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sub_r_03 failed:     [sub  a, e]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0x2C )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sub_r_03 failed:     [sub  a, e]\n" );
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
 *  SUB     A, H
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      0x05 - 0xFB - 0x00
 *      Flags tested:    S   Z   H  PV   C
 *                       0   0   1   0   1
 *
 ****************************************************************************/

static
int
tc_sub_r_04(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x05,             //  0000    LD   A, x'05
        0x26, 0xFB,             //  0003    LD   H, x'FB
        0x94,                   //  0006    SUB  A, H
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

    //  Intel 8080 and Zilog have different results.
    if( CPU == CPU_I80 )
    {
        if (    ( GET_A( )                   !=        0x0A )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sub_r_04 failed:     [sub  a, h]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0x0A )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sub_r_04 failed:     [sub  a, h]\n" );
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
 *  SUB     A, L
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      0x02 - 0x0F = 0xF3
 *      Flags tested:    S   Z   H  PV   C
 *                       1   0   1   0   1
 *
 ****************************************************************************/

static
int
tc_sub_r_05(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x02,             //  0000    LD   A, x'02
        0x2E, 0x0F,             //  0003    LD   L, x'0F
        0x95,                   //  0006    SUB  A, L
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

    //  Intel 8080 and Zilog have different results.
    if( CPU == CPU_I80 )
    {
        if (    ( GET_A( )                   !=        0xF3 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sub_r_05 failed:     [sub  a, l]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0xF3 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sub_r_05 failed:     [sub  a, l]\n" );
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
 *  SUB     A, A
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      0x49 - 0x49 = 0x00
 *      Flags tested:    S   Z   H  PV   C
 *                       0   1   0   0   0
 *
 ****************************************************************************/

static
int
tc_sub_r_06(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x49,             //  0000    LD   A, x'49
        0x97,                   //  0006    SUB  A, A
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

    //  Intel 8080 and Zilog have different results.
    if( CPU == CPU_I80 )
    {
        if (    ( GET_A( )                   !=        0x00 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=  CPU_FLAG_Z )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sub_r_06 failed:     [sub  a, a]\n" );
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
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=  CPU_FLAG_Z )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sub_r_06 failed:     [sub  a, a]\n" );
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
 *  SUB     A, n
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      0x71 - 0x13 = 0x00
 *      Flags tested:    S   Z   H  PV   C
 *                       0   0   1   0   0
 *
 ****************************************************************************/

static
int
tc_sub_n_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x71,             //  0000    LD   A, x'71
        0xD6, 0x13,             //  0002    SUB  A, x'13
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

    //  Intel 8080 and Zilog have different results.
    if( CPU == CPU_I80 )
    {
        if (    ( GET_A( )                   !=        0x5E )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sub_n_00 failed:     [sub  a, n]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0x5E )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sub_n_00 failed:     [sub  a, n]\n" );
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
 *  SUB     A, (HL)
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      0x43 - 0x6F = 0xD4
 *      Flags tested:    S   Z   H  PV   C
 *                       1   0   1   0   1
 *
 ****************************************************************************/

static
int
tc_sub_hl_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x43,             //  0005    LD   A,  x'43
        0x21, 0x00, 0x20,       //  0000    LD   HL, 0x0020
        0x36, 0x6F,             //  0003    LD   (HL), x'6F
        0x96,                   //  0006    SUB  A, (HL)
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

    //  Intel 8080 and Zilog have different results.
    if( CPU == CPU_I80 )
    {
        if (    ( GET_A( )                   !=        0xD4 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sub_hl_00 failed:     [sub  a, (hl)]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0xD4 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sub_hl_00 failed:     [sub  a, (hl)]\n" );
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
 *  SBC     A, B
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      ( 0x80 - 0x80 ) - 0x80
 *      (  (0)  0x00  ) - 0x80 = 0x80
 *      Flags tested:    S   Z   H  PV   C
 *                       1   0   0   1   0
 *
 ****************************************************************************/

static
int
tc_sbc_r_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x80,             //  0000    LD   A, 0x80
        0x06, 0x80,             //  0003    LD   B, 0x80
        0x90,                   //  0006    SUB  A, B
        0x98,                   //  0007    SBC  A, B
        0x76      };            //  0008    HALT

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
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sbc_r_00 failed:     [sbc  a, b]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0x80 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sbc_r_00 failed:     [sbc  a, b]\n" );
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
 *  SBC     A, C
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      ( 0x20 - 0x20 ) - 0x20
 *      (  (0)  0x00  ) - 0x20 = 0xE0
 *      Flags tested:    S   Z   H  PV   C
 *                       1   0   0   0   1
 *
 ****************************************************************************/

static
int
tc_sbc_r_01(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x20,             //  0000    LD   A, 0x20
        0x0E, 0x20,             //  0003    LD   C, 0x20
        0x91,                   //  0006    SUB  A, C
        0x99,                   //  0007    SBC  A, C
        0x76      };            //  0008    HALT

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
        if (    ( GET_A( )                   !=        0xE0 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sbc_r_01 failed:     [sbc  a, c]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0xE0 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sbc_r_01 failed:     [sbc  a, c]\n" );
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
 *  SBC     A, D
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      ( 0xFE - 0x01 ) - 0xFE
 *      (  (0)  0xFD  ) - 0x01 = 0xFC
 *      Flags tested:    S   Z   H  PV   C
 *                       1   0   0   0   0
 *
 ****************************************************************************/

static
int
tc_sbc_r_02(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0xFE,             //  0000    LD   A, x'FE
        0x16, 0x01,             //  0003    LD   D, x'01
        0x92,                   //  0006    SUB  A, D
        0x9A,                   //  0007    SBC  A, D
        0x76      };            //  0008    HALT

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
        if (    ( GET_A( )                   !=        0xFC )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sbc_r_02 failed:     [sbc  a, d]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0xFC )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sbc_r_02 failed:     [sbc  a, d]\n" );
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
 *  SBC     A, E
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      ( 0x0E - 0x7F ) - 0x7F
 *      (  (1)  0x8F  ) - 0x7F = 0x0F
 *      Flags tested:    S   Z   H  PV   C
 *                       1   0   0   1   0
 *
 ****************************************************************************/

static
int
tc_sbc_r_03(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x0E,             //  0000    LD   A, x'0E
        0x1E, 0x7F,             //  0003    LD   E, x'7F
        0x93,                   //  0006    SUB  A, E
        0x9B,                   //  0007    SBC  A, E
        0x76      };            //  0008    HALT

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
        if (    ( GET_A( )                   !=        0x0F )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sbc_r_03 failed:     [sbc  a, e]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0x0F )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sbc_r_03 failed:     [sbc  a, e]\n" );
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
 *  SBC     A, H
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      ( 0x11 - 0x22 ) - 0x22
 *      (  (1)  0xEF  ) - 0x22 = 0xCC
 *      Flags tested:    S   Z   H  PV   C
 *                       1   0   0   0   0
 *
 ****************************************************************************/

static
int
tc_sbc_r_04(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x11,             //  0000    LD   A, x'11
        0x26, 0x22,             //  0003    LD   H, x'22
        0x94,                   //  0006    SUB  A, H
        0x9C,                   //  0007    SBC  A, H
        0x76      };            //  0008    HALT

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
        if (    ( GET_A( )                   !=        0xCC )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sbc_r_04 failed:     [sbc  a, h]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0xCC )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sbc_r_04 failed:     [sbc  a, h]\n" );
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
 *  SBC     A, L
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      ( 0x22 - 0xF6 ) - 0xF6
 *      (  (1)  0x2C  ) - 0xF6 = 0xCA
 *      Flags tested:    S   Z   H  PV   C
 *                       1   0   0   1   0
 *
 ****************************************************************************/

static
int
tc_sbc_r_05(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x22,             //  0000    LD   A, x'22
        0x2E, 0xF6,             //  0003    LD   L, x'F6
        0x95,                   //  0006    SUB  A, L
        0x9D,                   //  0007    SBC  A, L
        0x76      };            //  0008    HALT

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
        if (    ( GET_A( )                   !=        0x35 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sbc_r_05 failed:     [sbc  a, l]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0x35 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sbc_r_05 failed:     [sbc  a, l]\n" );
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
 *  SBC     A, A
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      ( 0x11 - 0x11 ) - ( 0x11 - 0x11 )
 *      (  (0)  0x00  ) - (  (0)  0x00  ) = 0x00
 *      Flags tested:    S   Z   H  PV   C
 *                       0   1   0   0  0
 *
 ****************************************************************************/

static
int
tc_sbc_r_06(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x11,             //  0000    LD   A, 0x11
        0x97,                   //  0006    SUB  A, A
        0x9F,                   //  0007    SBC  A, A
        0x76      };            //  0008    HALT

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
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=  CPU_FLAG_Z )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sbc_r_06 failed:     [sbc  a, a]\n" );
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
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=  CPU_FLAG_Z )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sbc_r_06 failed:     [sbc  a, a]\n" );
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
 *  SBC     A, n
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      ( 0x34 - 0x11 ) - 0x04
 *      (  (0)  0x23  ) - 0x04 = 0x1F
 *      Flags tested:    S   Z   H  PV   C
 *                       0   0   1   0   0
 *
 ****************************************************************************/

static
int
tc_sbc_n_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x34,             //  0000    LD   A, x'34
        0xD6, 0x11,             //  0002    SUB  A, x'11
        0xDE, 0x04,             //  0004    SBC  A, x'04
        0x76      };            //  0006    HALT

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
        if (    ( GET_A( )                   !=        0x1F )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sbc_n_00 failed:     [sbc  a, n]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0x1F )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sbc_n_00 failed:     [sbc  a, n]\n" );
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
 *  SBC     A, (HL)
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      ( 0x81 - 0x7F ) - 0x7F
 *      (  (0)  0x02  ) - 0x7F = 0x83
 *      Flags tested:    S   Z   H  PV   C
 *                       1   0   1   0   1
 *
 ****************************************************************************/

static
int
tc_sbc_hl_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x81,             //  0005    LD   A, x'81
        0x21, 0x00, 0x20,       //  0000    LD  HL, 0x0003
        0x36, 0x7F,             //  0003    LD  (HL), x'7F
        0x96,                   //  0006    SUB  A, (HL)
        0x9E,                   //  0007    SBC  A, (HL)
        0x76      };            //  0008    HALT

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
        if (    ( GET_A( )                   !=        0x83 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sbc_hl_00 failed:     [sbc  a, (hl)]\n" );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_A( )                   !=        0x83 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
             || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
        {
            //  NO:     Write an error message
            printf( "POST: tc_sbc_hl_00 failed:     [sbc  a, (hl)]\n" );
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
 *  INC     r
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      0x40 + 0x40 = 0x80
 *      Flags tested:    S   Z   H  PV   C
 *                       1   0   0   1   0
 *
 ****************************************************************************/

static
int
tc_inc_r_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x06, 0x00,             //  0000    LD   B, 0x00
        0x0E, 0x0F,             //  0002    LD   C, 0x0F
        0x16, 0x7F,             //  0004    LD   D, 0x7F
        0x1E, 0x1F,             //  0006    LD   E, 0x1F
        0x26, 0x55,             //  0008    LD   H, 0x55
        0x2E, 0xAA,             //  000A    LD   L, 0xAA
        0x3E, 0xFF,             //  000C    LD   A, 0xFF
        0x04,                   //  000E    INC  B
        0x0C,                   //  000F    INC  C
        0x14,                   //  0010    INC  D
        0x1C,                   //  0011    INC  E
        0x24,                   //  0012    INC  H
        0x2C,                   //  0013    INC  L
        0x3C,                   //  0014    INC  A
        0x76      };            //  0015    HALT

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
        if (    ( GET_B( )                   !=        0x01 )
             || ( GET_C( )                   !=        0x10 )
             || ( GET_D( )                   !=        0x80 )
             || ( GET_E( )                   !=        0x20 )
             || ( GET_H( )                   !=        0x56 )
             || ( GET_L( )                   !=        0xAB )
             || ( GET_A( )                   !=        0x00 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=  CPU_FLAG_Z )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) != CPU_FLAG_PV )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
                                                              ) //  01 [Carry isn't effected.
        {
            //  NO:     Write an error message
            printf( "POST: tc_inc_r_00 failed:     [inc  r]\n" );
            printf( "POST: B  = 0x%02X\n", GET_B( ) );
            printf( "POST: C  = 0x%02X\n", GET_C( ) );
            printf( "POST: D  = 0x%02X\n", GET_D( ) );
            printf( "POST: E  = 0x%02X\n", GET_E( ) );
            printf( "POST: H  = 0x%02X\n", GET_H( ) );
            printf( "POST: L  = 0x%02X\n", GET_L( ) );
            printf( "POST: A  = 0x%02X\n", GET_A( ) );
            printf( "POST: F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( GET_B( )                   !=        0x01 )
             || ( GET_C( )                   !=        0x10 )
             || ( GET_D( )                   !=        0x80 )
             || ( GET_E( )                   !=        0x20 )
             || ( GET_H( )                   !=        0x56 )
             || ( GET_L( )                   !=        0xAB )
             || ( GET_A( )                   !=        0x00 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=           0 )   //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=  CPU_FLAG_Z )   //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
                                                              ) //  01 [Carry isn't effected.
        {
            //  NO:     Write an error message
            printf( "POST: tc_inc_r_00 failed:     [inc  r]\n" );
            printf( "POST: B  = 0x%02X\n", GET_B( ) );
            printf( "POST: C  = 0x%02X\n", GET_C( ) );
            printf( "POST: D  = 0x%02X\n", GET_D( ) );
            printf( "POST: E  = 0x%02X\n", GET_E( ) );
            printf( "POST: H  = 0x%02X\n", GET_H( ) );
            printf( "POST: L  = 0x%02X\n", GET_L( ) );
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
 *  INC     (HL)
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      0x40 + 0x40 = 0x80
 *      Flags tested:    S   Z   H  PV   C
 *                       1   0   0   1   0
 *
 ****************************************************************************/

static
int
tc_inc_hl_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x21, 0x20, 0x00,       //  0000    LD  HL, 0x0020
        0x36, 100,              //  0003    LD  (HL), 100
        0x34,                   //  0005    INC (HL)
        0x76      };            //  0015    HALT

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
        if (    ( memory_get_8( 0x0020 )     != (uint8_t)101 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=            0 )      //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=            0 )      //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=            0 )      //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=  CPU_FLAG_PV )      //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=            0 ) )    //  02
                //  [Carry isn't effected by this instruction.]         01
        {
            //  NO:     Write an error message
            printf( "POST: tc_inc_hl_00 failed:     [inc  (hl)]\n" );
            printf( "POST: (0x0020) = 0x%02X\n", memory_get_8( 0x0020 ) );
            printf( "POST:       F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }
    else
    {
        if (    ( memory_get_8( 0x0020 )     != (uint8_t)101 )
             || ( ( GET_F( ) & CPU_FLAG_S  ) !=            0 )      //  80
             || ( ( GET_F( ) & CPU_FLAG_Z  ) !=            0 )      //  40
             || ( ( GET_F( ) & CPU_FLAG_H  ) !=            0 )      //  10
             || ( ( GET_F( ) & CPU_FLAG_PV ) !=            0 )      //  04
             || ( ( GET_F( ) & CPU_FLAG_N  ) !=            0 ) )    //  02
                //  [Carry isn't effected by this instruction.]         01
        {
            //  NO:     Write an error message
            printf( "POST: tc_inc_hl_00 failed:     [inc  (hl)]\n" );
            printf( "POST: (0x0020) = 0x%02X\n", memory_get_8( 0x0020 ) );
            printf( "POST:       F  = 0x%02X\n", GET_F( ) );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  DEC     r
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      0x40 + 0x40 = 0x80
 *      Flags tested:    S   Z   H  PV   C
 *                       1   0   0   1   0
 *
 ****************************************************************************/

static
int
tc_dec_r_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x06, 0x00,             //  0000    LD   B, 0x00
        0x0E, 0x0F,             //  0002    LD   C, 0x0F
        0x16, 0x7F,             //  0004    LD   D, 0x7F
        0x1E, 0x1F,             //  0006    LD   E, 0x1F
        0x26, 0x55,             //  0008    LD   H, 0x55
        0x2E, 0xAA,             //  000A    LD   L, 0xAA
        0x3E, 0xFF,             //  000C    LD   A, 0xFF
        0x05,                   //  000E    INC  B
        0x0D,                   //  000F    INC  C
        0x15,                   //  0010    INC  D
        0x1D,                   //  0011    INC  E
        0x25,                   //  0012    INC  H
        0x2D,                   //  0013    INC  L
        0x3D,                   //  0014    INC  A
        0x76      };            //  0015    HALT

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

    if (    ( GET_B( )                   !=        0xFF )
         || ( GET_C( )                   !=        0x0E )
         || ( GET_D( )                   !=        0x7E )
         || ( GET_E( )                   !=        0x1E )
         || ( GET_H( )                   !=        0x54 )
         || ( GET_L( )                   !=        0xA9 )
         || ( GET_A( )                   !=        0xFE )
         || ( ( GET_F( ) & CPU_FLAG_S  ) !=  CPU_FLAG_S )   //  80
         || ( ( GET_F( ) & CPU_FLAG_Z  ) !=           0 )   //  40
         || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
         || ( ( GET_F( ) & CPU_FLAG_PV ) !=           0 )   //  04
         || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N )   //  02
                                                          ) //  01 [Carry isn't effected.
    {
        //  NO:     Write an error message
        printf( "POST: tc_dec_r_00 failed:     [dec  r]\n" );
        printf( "POST: B  = 0x%02X\n", GET_B( ) );
        printf( "POST: C  = 0x%02X\n", GET_C( ) );
        printf( "POST: D  = 0x%02X\n", GET_D( ) );
        printf( "POST: E  = 0x%02X\n", GET_E( ) );
        printf( "POST: H  = 0x%02X\n", GET_H( ) );
        printf( "POST: L  = 0x%02X\n", GET_L( ) );
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
 *  DEC     (HL)
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      0x40 + 0x40 = 0x80
 *      Flags tested:    S   Z   H  PV   C
 *                       1   0   0   1   0
 *
 ****************************************************************************/

static
int
tc_dec_hl_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x21, 0x20, 0x00,       //  0000    LD  HL, 0x0020
        0x36, 100,              //  0003    LD  (HL), 100
        0x35,                   //  0005    INC (HL)
        0x76      };            //  0015    HALT

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

    if (    ( memory_get_8( 0x0020 )     != (uint8_t)99  )
         || ( ( GET_F( ) & CPU_FLAG_S  ) !=            0 )      //  80
         || ( ( GET_F( ) & CPU_FLAG_Z  ) !=            0 )      //  40
         || ( ( GET_F( ) & CPU_FLAG_H  ) !=            0 )      //  10
         || ( ( GET_F( ) & CPU_FLAG_PV ) !=            0 )      //  04
         || ( ( GET_F( ) & CPU_FLAG_N  ) !=   CPU_FLAG_N ) )    //  02
            //  [Carry isn't effected by this instruction.]         01
    {
        //  NO:     Write an error message
        printf( "POST: tc_dec_hl_00 failed:     [dec  (hl)]\n" );
        printf( "POST: (0x0020) = 0x%02X\n", memory_get_8( 0x0020 ) );
        printf( "POST:       F  = 0x%02X\n", GET_F( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  DAA
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *          N  Carry(in)  Bits 7-4  Half-Carry   Bits 3-0     ADD     Carry(out)
 *      01  0    0           0-9        0          0-9         00        0
 *
 ****************************************************************************/

static
int
tc_daa_01_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x00,             //  0000    LD   A, 0x00
        0x06, 0x00,             //  0002    LD   B, 0x00
        0x80,                   //  0004    ADD  A, B
        0x27,                   //  0005    DAA
        0x76      };            //  0006    HALT

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

    if (    ( GET_A( )                   !=        0x00 )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_daa_01_00 failed:     [daa      ]\n" );
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
 *  DAA
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *          N  Carry(in)  Bits 7-4  Half-Carry   Bits 3-0     ADD     Carry(out)
 *      01  0    0           0-9        0          0-9         00        0
 *
 ****************************************************************************/

static
int
tc_daa_01_01(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x90,             //  0000    LD   A, 0x90
        0x06, 0x09,             //  0002    LD   B, 0x09
        0x80,                   //  0004    ADD  A, B
        0x27,                   //  0005    DAA
        0x76      };            //  0006    HALT

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

    if (    ( GET_A( )                   !=        0x99 )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_daa_01_01 failed:     [daa      ]\n" );
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
 *  DAA
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *          N  Carry(in)  Bits 7-4  Half-Carry   Bits 3-0     ADD     Carry(out)
 *      02  0    0           0-8        0          A-F         06        0
 *
 ****************************************************************************/

static
int
tc_daa_02_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x00,             //  0000    LD   A, 0x00
        0x06, 0x0A,             //  0002    LD   B, 0x0A
        0x80,                   //  0004    ADD  A, B
        0x27,                   //  0005    DAA
        0x76      };            //  0006    HALT

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

    if (    ( GET_A( )                   !=        0x10 )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_daa_02_00 failed:     [daa      ]\n" );
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
 *  DAA
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *          N  Carry(in)  Bits 7-4  Half-Carry   Bits 3-0     ADD     Carry(out)
 *      02  0    0           0-8        0          A-F         06        0
 *
 ****************************************************************************/

static
int
tc_daa_02_01(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x80,             //  0000    LD   A, 0x80
        0x06, 0x0F,             //  0002    LD   B, 0x0F
        0x80,                   //  0004    ADD  A, B
        0x27,                   //  0005    DAA
        0x76      };            //  0006    HALT

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

    if (    ( GET_A( )                   !=        0x95 )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_daa_02_01 failed:     [daa      ]\n" );
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
 *  DAA
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *          N  Carry(in)  Bits 7-4  Half-Carry   Bits 3-0     ADD     Carry(out)
 *      03  0    0           0-9        1          0-3         06        0
 *
 ****************************************************************************/

static
int
tc_daa_03_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x0F,             //  0000    LD   A, 0x0F
        0x06, 0x01,             //  0002    LD   B, 0x01
        0x80,                   //  0004    ADD  A, B
        0x27,                   //  0005    DAA
        0x76      };            //  0006    HALT

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

    if (    ( GET_A( )                   !=        0x16 )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_daa_03_00 failed:     [daa      ]\n" );
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
 *  DAA
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *          N  Carry(in)  Bits 7-4  Half-Carry   Bits 3-0     ADD     Carry(out)
 *      03  0    0           0-9        1          0-3         06        0
 *
 ****************************************************************************/

static
int
tc_daa_03_01(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x8F,             //  0000    LD   A, 0x8F
        0x06, 0x04,             //  0002    LD   B, 0x04
        0x80,                   //  0004    ADD  A, B
        0x27,                   //  0005    DAA
        0x76      };            //  0006    HALT

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

    if (    ( GET_A( )                   !=        0x99 )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_daa_03_01 failed:     [daa      ]\n" );
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
 *  DAA
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *          N  Carry(in)  Bits 7-4  Half-Carry   Bits 3-0     ADD     Carry(out)
 *      04  0    0           A-F        0          0-9         60        1
 *
 ****************************************************************************/

static
int
tc_daa_04_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0xA0,             //  0000    LD   A, 0xA0
        0x06, 0x00,             //  0002    LD   B, 0x00
        0x80,                   //  0004    ADD  A, B
        0x27,                   //  0005    DAA
        0x76      };            //  0006    HALT

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

    if (    ( GET_A( )                   !=        0x00 )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_daa_04_00 failed:     [daa      ]\n" );
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
 *  DAA
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *          N  Carry(in)  Bits 7-4  Half-Carry   Bits 3-0     ADD     Carry(out)
 *      04  0    0           A-F        0          0-9         60        1
 *
 ****************************************************************************/

static
int
tc_daa_04_01(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0xF0,             //  0000    LD   A, 0xF0
        0x06, 0x09,             //  0002    LD   B, 0x09
        0x80,                   //  0004    ADD  A, B
        0x27,                   //  0005    DAA
        0x76      };            //  0006    HALT

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

    if (    ( GET_A( )                   !=        0x59 )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_daa_04_01 failed:     [daa      ]\n" );
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
 *  DAA
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *          N  Carry(in)  Bits 7-4  Half-Carry   Bits 3-0     ADD     Carry(out)
 *      05  0    0           9-F        0          A-F         66        1
 *
 ****************************************************************************/

static
int
tc_daa_05_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x90,             //  0000    LD   A, 0x90
        0x06, 0x0A,             //  0002    LD   B, 0x0A
        0x80,                   //  0004    ADD  A, B
        0x27,                   //  0005    DAA
        0x76      };            //  0006    HALT

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

    if (    ( GET_A( )                   !=        0x00 )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_daa_05_00 failed:     [daa      ]\n" );
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
 *  DAA
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *          N  Carry(in)  Bits 7-4  Half-Carry   Bits 3-0     ADD     Carry(out)
 *      05  0    0           9-F        0          A-F         66        1
 *
 ****************************************************************************/

static
int
tc_daa_05_01(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0xF0,             //  0000    LD   A, 0xF0
        0x06, 0x0F,             //  0002    LD   B, 0x0F
        0x80,                   //  0004    ADD  A, B
        0x27,                   //  0005    DAA
        0x76      };            //  0006    HALT

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

    if (    ( GET_A( )                   !=        0x65 )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_daa_05_01 failed:     [daa      ]\n" );
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
 *  DAA
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *          N  Carry(in)  Bits 7-4  Half-Carry   Bits 3-0     ADD     Carry(out)
 *      06  0    0           A-F        1          0-3         66        1
 *
 ****************************************************************************/

static
int
tc_daa_06_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x9F,             //  0000    LD   A, 0x9F
        0x06, 0x01,             //  0002    LD   B, 0x01
        0x80,                   //  0004    ADD  A, B
        0x27,                   //  0005    DAA
        0x76      };            //  0006    HALT

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

    if (    ( GET_A( )                   !=        0x06 )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_daa_06_00 failed:     [daa      ]\n" );
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
 *  DAA
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *          N  Carry(in)  Bits 7-4  Half-Carry   Bits 3-0     ADD     Carry(out)
 *      06  0    0           A-F        1          0-3         66        1
 *
 ****************************************************************************/

static
int
tc_daa_06_01(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0xEF,             //  0000    LD   A, 0xEF
        0x06, 0x04,             //  0002    LD   B, 0x04
        0x80,                   //  0004    ADD  A, B
        0x27,                   //  0005    DAA
        0x76      };            //  0006    HALT

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

    if (    ( GET_A( )                   !=        0x59 )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_daa_06_01 failed:     [daa      ]\n" );
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
 *  DAA
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *          N  Carry(in)  Bits 7-4  Half-Carry   Bits 3-0     ADD     Carry(out)
 *      07  0    1           0-2        0          0-9         60        1
 *
 ****************************************************************************/

static
int
tc_daa_07_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x80,             //  0000    LD   A, 0x80
        0x06, 0x80,             //  0002    LD   B, 0x80
        0x80,                   //  0004    ADD  A, B
        0x27,                   //  0005    DAA
        0x76      };            //  0006    HALT

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

    if (    ( GET_A( )                   !=        0x60 )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_daa_07_00 failed:     [daa      ]\n" );
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
 *  DAA
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *          N  Carry(in)  Bits 7-4  Half-Carry   Bits 3-0     ADD     Carry(out)
 *      07  0    1           0-2        0          0-9         60        1
 *
 ****************************************************************************/

static
int
tc_daa_07_01(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x80,             //  0000    LD   A, 0x80
        0x06, 0xA9,             //  0002    LD   B, 0xA9
        0x80,                   //  0004    ADD  A, B
        0x27,                   //  0005    DAA
        0x76      };            //  0006    HALT

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

    if (    ( GET_A( )                   !=        0x89 )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_daa_07_01 failed:     [daa      ]\n" );
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
 *  DAA
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *          N  Carry(in)  Bits 7-4  Half-Carry   Bits 3-0     ADD     Carry(out)
 *      08  0    1           0-2        0          A-F         66        1
 *
 ****************************************************************************/

static
int
tc_daa_08_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x91,             //  0000    LD   A, 0x91
        0x06, 0x99,             //  0002    LD   B, 0x99
        0x80,                   //  0004    ADD  A, B
        0x27,                   //  0005    DAA
        0x76      };            //  0006    HALT

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

    if (    ( GET_A( )                   !=        0x90 )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_daa_08_00 failed:     [daa      ]\n" );
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
 *  DAA
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *          N  Carry(in)  Bits 7-4  Half-Carry   Bits 3-0     ADD     Carry(out)
 *      08  0    1           0-2        0          A-F         66        1
 *
 ****************************************************************************/

static
int
tc_daa_08_01(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0xB1,             //  0000    LD   A, 0xB1
        0x06, 0x7E,             //  0002    LD   B, 0x7E
        0x80,                   //  0004    ADD  A, B
        0x27,                   //  0005    DAA
        0x76      };            //  0006    HALT

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

    if (    ( GET_A( )                   !=        0x95 )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_daa_08_01 failed:     [daa      ]\n" );
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
 *  DAA
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *          N  Carry(in)  Bits 7-4  Half-Carry   Bits 3-0     ADD     Carry(out)
 *      09  0    1           0-3        1          0-3         66        1
 *
 ****************************************************************************/

static
int
tc_daa_09_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x0F,             //  0000    LD   A, 0x0F
        0x06, 0xF1,             //  0002    LD   B, 0xF1
        0x80,                   //  0004    ADD  A, B
        0x27,                   //  0005    DAA
        0x76      };            //  0006    HALT

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

    if (    ( GET_A( )                   !=        0x66 )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_daa_09_00 failed:     [daa      ]\n" );
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
 *  DAA
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *          N  Carry(in)  Bits 7-4  Half-Carry   Bits 3-0     ADD     Carry(out)
 *      09  0    1           0-3        1          0-3         66        1
 *
 ****************************************************************************/

static
int
tc_daa_09_01(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0xFF,             //  0000    LD   A, 0xFF
        0x06, 0x34,             //  0002    LD   B, 0x34
        0x80,                   //  0004    ADD  A, B
        0x27,                   //  0005    DAA
        0x76      };            //  0006    HALT

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

    if (    ( GET_A( )                   !=        0x99 )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_daa_09_01 failed:     [daa      ]\n" );
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
 *  DAA
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *          N  Carry(in)  Bits 7-4  Half-Carry   Bits 3-0     ADD     Carry(out)
 *      10  1    0           0-9        0          0-9         00        0
 *
 ****************************************************************************/

static
int
tc_daa_10_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x01,             //  0000    LD   A, 0x01
        0x06, 0x01,             //  0002    LD   B, 0x01
        0x90,                   //  0004    SUB  A, B
        0x27,                   //  0005    DAA
        0x76      };            //  0006    HALT

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

    if (    ( GET_A( )                   !=        0x00 )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_daa_10_00 failed:     [daa      ]\n" );
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
 *  DAA
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *          N  Carry(in)  Bits 7-4  Half-Carry   Bits 3-0     ADD     Carry(out)
 *      10  1    0           0-9        0          0-9         00        0
 *
 ****************************************************************************/

static
int
tc_daa_10_01(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0xAA,             //  0000    LD   A, 0xAA
        0x06, 0x11,             //  0002    LD   B, 0x11
        0x90,                   //  0004    SUB  A, B
        0x27,                   //  0005    DAA
        0x76      };            //  0006    HALT

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

    if (    ( GET_A( )                   !=        0x99 )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_daa_10_01 failed:     [daa      ]\n" );
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
 *  DAA
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *          N  Carry(in)  Bits 7-4  Half-Carry   Bits 3-0     ADD     Carry(out)
 *      11  1    0           0-8        1          6-F         FA        0
 *
 ****************************************************************************/

static
int
tc_daa_11_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x15,             //  0000    LD   A, 0x15
        0x06, 0x0F,             //  0002    LD   B, 0x0F
        0x90,                   //  0004    SUB  A, B
        0x27,                   //  0005    DAA
        0x76      };            //  0006    HALT

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

    if (    ( GET_A( )                   !=        0x00 )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_daa_11_00 failed:     [daa      ]\n" );
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
 *  DAA
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *          N  Carry(in)  Bits 7-4  Half-Carry   Bits 3-0     ADD     Carry(out)
 *      11  1    0           0-8        1          6-F         FA        0
 *
 ****************************************************************************/

static
int
tc_daa_11_01(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x90,             //  0000    LD   A, 0x90
        0x06, 0x01,             //  0002    LD   B, 0x01
        0x90,                   //  0004    SUB  A, B
        0x27,                   //  0005    DAA
        0x76      };            //  0006    HALT

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

    if (    ( GET_A( )                   !=        0x89 )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_daa_11_00 failed:     [daa      ]\n" );
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
 *  DAA
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *          N  Carry(in)  Bits 7-4  Half-Carry   Bits 3-0     ADD     Carry(out)
 *      12  1    1           7-F        0          0-9         A0        1
 *
 ****************************************************************************/

static
int
tc_daa_12_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x60,             //  0000    LD   A, 0x60
        0x06, 0xF0,             //  0002    LD   B, 0xF0
        0x90,                   //  0004    SUB  A, B
        0x27,                   //  0005    DAA
        0x76      };            //  0006    HALT

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

    if (    ( GET_A( )                   !=        0x10 )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_daa_12_00 failed:     [daa      ]\n" );
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
 *  DAA
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *          N  Carry(in)  Bits 7-4  Half-Carry   Bits 3-0     ADD     Carry(out)
 *      12  1    1           7-F        0          0-9         A0        1
 *
 ****************************************************************************/

static
int
tc_daa_12_01(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x09,             //  0000    LD   A, 0x09
        0x06, 0x10,             //  0002    LD   B, 0x10
        0x90,                   //  0004    SUB  A, B
        0x27,                   //  0005    DAA
        0x76      };            //  0006    HALT

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

    if (    ( GET_A( )                   !=        0x99 )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_daa_12_01 failed:     [daa      ]\n" );
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
 *  DAA
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *          N  Carry(in)  Bits 7-4  Half-Carry   Bits 3-0     ADD     Carry(out)
 *      13  1    1           6-F        1          6-F         9A        1
 *
 ****************************************************************************/

static
int
tc_daa_13_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x00,             //  0000    LD   A, 0x00
        0x06, 0x9A,             //  0002    LD   B, 0x9A
        0x90,                   //  0004    SUB  A, B
        0x27,                   //  0005    DAA
        0x76      };            //  0006    HALT

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

    if (    ( GET_A( )                   !=        0x00 )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_daa_13_00 failed:     [daa      ]\n" );
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
 *  DAA
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *          N  Carry(in)  Bits 7-4  Half-Carry   Bits 3-0     ADD     Carry(out)
 *      13  1    1           6-F        1          6-F         9A        1
 *
 ****************************************************************************/

static
int
tc_daa_13_01(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x11,             //  0000    LD   A, 0x11
        0x06, 0x12,             //  0002    LD   B, 0x12
        0x90,                   //  0004    SUB  A, B
        0x27,                   //  0005    DAA
        0x76      };            //  0006    HALT

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

    if (    ( GET_A( )                   !=        0x99 )
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_daa_13_00 failed:     [daa      ]\n" );
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
 *  CPL
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      0x5A = 0xA5
 *      Flags tested:    S   Z   H  PV   C
 *                       x   x   1   x   x
 *
 ****************************************************************************/

static
int
tc_cpl_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x5A,             //  0000    LD   A, x'5A
        0x2F,                   //  0006    CPL
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

    if (    ( GET_A( )                   !=        0xA5 )
         || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
         || ( ( GET_F( ) & CPU_FLAG_N  ) !=  CPU_FLAG_N ) ) //  02
    {
        //  NO:     Write an error message
        printf( "POST: tc_cpl_00 failed:     [cpl      ]\n" );
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
 *  CCF
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      0x00 + 0x00 = 0x00
 *      Flags tested:    S   Z   H  PV   C
 *                       x   x   0   x   1
 *
 ****************************************************************************/

static
int
tc_ccf_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x00,             //  0000    LD   A, x'00
        0x87,                   //  0006    ADD  A, A
        0x3F,                   //  0006    CCF
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

    if (    ( GET_A( )                   !=        0x00 )
         || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
         || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_ccf_00 failed:     [ccf      ]\n" );
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
 *  CCF
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      0x80 + 0x80 = 0x00
 *      Flags tested:    S   Z   H  PV   C
 *                       x   x   1   x   0
 *
 ****************************************************************************/

static
int
tc_ccf_01(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x80,             //  0000    LD   A, x'80
        0x87,                   //  0006    ADD  A, A
        0x3F,                   //  0006    CCF
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

    if (    ( GET_A( )                   !=        0x00 )
         || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
         || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_ccf_01 failed:     [ccf      ]\n" );
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
 *  SCF
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      0x00 + 0x00 = 0x00
 *      Flags tested:    S   Z   H  PV   C
 *                       x   x   0   x   1
 *
 ****************************************************************************/

static
int
tc_scf_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x00,             //  0000    LD   A, x'00
        0x87,                   //  0006    ADD  A, A
        0x37,                   //  0006    SCF
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

    if (    ( GET_A( )                   !=        0x00 )
         || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
         || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_scf_00 failed:     [scf      ]\n" );
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
 *  SCF
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      0x80 + 0x80 = 0x00
 *      Flags tested:    S   Z   H  PV   C
 *                       x   x   0   x   0
 *
 ****************************************************************************/

static
int
tc_scf_01(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x80,             //  0000    LD   A, x'80
        0x87,                   //  0006    ADD  A, A
        0x37,                   //  0006    SCF
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

    if (    ( GET_A( )                   !=        0x00 )
         || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
         || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_scf_00 failed:     [scf      ]\n" );
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
 *  NEG
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      0x80 + 0x80 = 0x00
 *      Flags tested:    S   Z   H  PV   C
 *                       x   x   0   x   0
 *
 ****************************************************************************/

static
int
tc_neg_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0xAA,             //  0000    LD   A, x'AA
        0xED, 0x44,             //  0002    NEG
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

    if ( GET_A( ) != 0x56 )
    {
        //  NO:     Write an error message
        printf( "POST: tc_neg_00 failed:     [neg      ]\n" );
        printf( "POST: A  = 0x%02X\n", GET_A( ) );

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
 *  ARITH Power On Self Test
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
math_post(
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

    /************************************************************************
     *  Power On Self Test
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
        if ( post_rc == true )      post_rc = tc_add_r_00( );       //  ADD  A, B
        if ( post_rc == true )      post_rc = tc_add_r_01( );       //  ADD  A, C
        if ( post_rc == true )      post_rc = tc_add_r_02( );       //  ADD  A, D
        if ( post_rc == true )      post_rc = tc_add_r_03( );       //  ADD  A, E
        if ( post_rc == true )      post_rc = tc_add_r_04( );       //  ADD  A, H
        if ( post_rc == true )      post_rc = tc_add_r_05( );       //  ADD  A, L
        if ( post_rc == true )      post_rc = tc_add_r_06( );       //  ADD  A, A
        if ( post_rc == true )      post_rc = tc_add_n_00( );       //  ADD  A, n
        if ( post_rc == true )      post_rc = tc_add_hl_00( );      //  ADD  A, (HL)

        if ( post_rc == true )      post_rc = tc_adc_r_00( );       //  ADC  A, B
        if ( post_rc == true )      post_rc = tc_adc_r_01( );       //  ADC  A, C
        if ( post_rc == true )      post_rc = tc_adc_r_02( );       //  ADC  A, D
        if ( post_rc == true )      post_rc = tc_adc_r_03( );       //  ADC  A, E
        if ( post_rc == true )      post_rc = tc_adc_r_04( );       //  ADC  A, H
        if ( post_rc == true )      post_rc = tc_adc_r_05( );       //  ADC  A, L
        if ( post_rc == true )      post_rc = tc_adc_r_06( );       //  ADC  A, A
        if ( post_rc == true )      post_rc = tc_adc_n_00( );       //  ADD  A, n
        if ( post_rc == true )      post_rc = tc_adc_hl_00( );      //  ADD  A, (HL)

        if ( post_rc == true )      post_rc = tc_sub_r_00( );       //  SUB  A, B
        if ( post_rc == true )      post_rc = tc_sub_r_01( );       //  SUB  A, C
        if ( post_rc == true )      post_rc = tc_sub_r_02( );       //  SUB  A, D
        if ( post_rc == true )      post_rc = tc_sub_r_03( );       //  SUB  A, E
        if ( post_rc == true )      post_rc = tc_sub_r_04( );       //  SUB  A, H
        if ( post_rc == true )      post_rc = tc_sub_r_05( );       //  SUB  A, L
        if ( post_rc == true )      post_rc = tc_sub_r_06( );       //  SUB  A, A
        if ( post_rc == true )      post_rc = tc_sub_n_00( );       //  SUB  A, n
        if ( post_rc == true )      post_rc = tc_sub_hl_00( );      //  SUB  A, (HL)

        if ( post_rc == true )      post_rc = tc_sbc_r_00( );       //  SBC  A, B
        if ( post_rc == true )      post_rc = tc_sbc_r_01( );       //  SBC  A, C
        if ( post_rc == true )      post_rc = tc_sbc_r_02( );       //  SBC  A, D
        if ( post_rc == true )      post_rc = tc_sbc_r_03( );       //  SBC  A, E
        if ( post_rc == true )      post_rc = tc_sbc_r_04( );       //  SBC  A, H
        if ( post_rc == true )      post_rc = tc_sbc_r_05( );       //  SBC  A, L
        if ( post_rc == true )      post_rc = tc_sbc_r_06( );       //  SBC  A, A
        if ( post_rc == true )      post_rc = tc_sbc_n_00( );       //  SBC  A, n
        if ( post_rc == true )      post_rc = tc_sbc_hl_00( );      //  SBC  A, (HL)

        if ( post_rc == true )      post_rc = tc_inc_r_00( );       //  INC  r
        if ( post_rc == true )      post_rc = tc_inc_hl_00( );      //  INC  (HL)

        if ( post_rc == true )      post_rc = tc_dec_r_00( );       //  DEC  r
        if ( post_rc == true )      post_rc = tc_dec_hl_00( );      //  DEC  (HL)

        //------------------------------------------------------------------------
        //      N  Carry(in)  Bits 7-4  Half-Carry   Bits 3-0     ADD     Carry(out)
        //  01  0    0           0-9        0          0-9         00        0
        //  02  0    0           0-8        0          A-F         06        0
        //  03  0    0           0-9        1          0-3         06        0
        //  04  0    0           A-F        0          0-9         60        1
        //  05  0    0           9-F        0          A-F         66        1
        //  06  0    0           A-F        1          0-3         66        1
        //  07  0    1           0-2        0          0-9         60        1
        //  08  0    1           0-2        0          A-F         66        1
        //  09  0    1           0-3        1          0-3         66        1
        //  10  1    0           0-9        0          0-9         00        0
        //  11  1    0           0-8        1          6-F         FA        0
        //  12  1    1           7-F        0          0-9         A0        1
        //  13  1    1           6-F        1          6-F         9A        1
        //------------------------------------------------------------------------

        if ( post_rc == true )      post_rc = tc_daa_01_00( );      //  DAA     [state  1]
        if ( post_rc == true )      post_rc = tc_daa_01_01( );      //  DAA     [state  1]
        if ( post_rc == true )      post_rc = tc_daa_02_00( );      //  DAA     [state  2]
        if ( post_rc == true )      post_rc = tc_daa_02_01( );      //  DAA     [state  2]
        if ( post_rc == true )      post_rc = tc_daa_03_00( );      //  DAA     [state  3]
        if ( post_rc == true )      post_rc = tc_daa_03_01( );      //  DAA     [state  3]
        if ( post_rc == true )      post_rc = tc_daa_04_00( );      //  DAA     [state  4]
        if ( post_rc == true )      post_rc = tc_daa_04_01( );      //  DAA     [state  4]
        if ( post_rc == true )      post_rc = tc_daa_05_00( );      //  DAA     [state  5]
        if ( post_rc == true )      post_rc = tc_daa_05_01( );      //  DAA     [state  5]
        if ( post_rc == true )      post_rc = tc_daa_06_00( );      //  DAA     [state  6]
        if ( post_rc == true )      post_rc = tc_daa_06_01( );      //  DAA     [state  6]
        if ( post_rc == true )      post_rc = tc_daa_10_00( );      //  DAA     [state 10]
        if ( post_rc == true )      post_rc = tc_daa_10_01( );      //  DAA     [state 10]

        if ( post_rc == true )      post_rc = tc_cpl_00( );         //  CPL

        if ( post_rc == true )      post_rc = tc_ccf_00( );         //  CCF
        if ( post_rc == true )      post_rc = tc_ccf_01( );         //  CCF

        if ( post_rc == true )      post_rc = tc_scf_00( );         //  SCF
        if ( post_rc == true )      post_rc = tc_scf_01( );         //  SCF

        //  Z80 ONLY instructions
        if( CPU == CPU_Z80 )
        {
            if ( post_rc == true )  post_rc = tc_daa_07_00( );      //  DAA     [state  7]
            if ( post_rc == true )  post_rc = tc_daa_07_01( );      //  DAA     [state  7]
            if ( post_rc == true )  post_rc = tc_daa_08_00( );      //  DAA     [state  8]
            if ( post_rc == true )  post_rc = tc_daa_08_01( );      //  DAA     [state  8]
            if ( post_rc == true )  post_rc = tc_daa_09_00( );      //  DAA     [state  9]
            if ( post_rc == true )  post_rc = tc_daa_09_01( );      //  DAA     [state  9]
            if ( post_rc == true )  post_rc = tc_daa_11_00( );      //  DAA     [state 11]
            if ( post_rc == true )  post_rc = tc_daa_11_01( );      //  DAA     [state 11]
            if ( post_rc == true )  post_rc = tc_daa_12_00( );      //  DAA     [state 12]
            if ( post_rc == true )  post_rc = tc_daa_12_01( );      //  DAA     [state 12]
            if ( post_rc == true )  post_rc = tc_daa_13_00( );      //  DAA     [state 13]
            if ( post_rc == true )  post_rc = tc_daa_13_01( );      //  DAA     [state 13]
            if ( post_rc == true )  post_rc = tc_neg_00( );         //  NEG
        }

        //  Was the test suite successfully complete :
        if( post_rc == true )
        {
            //  YES:    Write a completion message
            printf( "POST: MATH    complete %s mode.\n",
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