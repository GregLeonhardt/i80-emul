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
#include "math_16.h"            //  16 bit Arithmatic instrucions.
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
 *  ADD     HL, BC
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      0x1234 + 0x5678 = 0x68AC
 *      Flags tested:    S   Z   H  PV   C
 *                       x   x   0   x   0
 *
 ****************************************************************************/

static
int
tc_add_hlbc_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x21, 0x34, 0x12,       //  0000    LD    HL, x'1234
        0x01, 0x78, 0x56,       //  0003    LD    BC, x'5678
        0x09,                   //  0006    ADD   HL, BC
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

    if (    ( CPU_REG_HL                 !=      0x68AC )
         || ( ( GET_F( ) & CPU_FLAG_H  ) !=           0 )   //  10
         || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=           0 ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_add_hlbc_00 failed:     [add  hl, bc]\n" );
        printf( "POST: HL = 0x%04X\n", CPU_REG_HL );
        printf( "POST: F  = 0x%02X\n", GET_F( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  ADD     HL, DE
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      0x8080 + 0x8080 = 0x0100
 *      Flags tested:    S   Z   H  PV   C
 *                       x   x   1   x   1
 *
 ****************************************************************************/

static
int
tc_add_hlde_01(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x21, 0x80, 0x80,       //  0000    HL, x'8080
        0x11, 0x80, 0x80,       //  0003    DE, x'8080
        0x19,                   //  0006    ADD  HL, DE
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

    if (    ( CPU_REG_HL                 !=      0x0100 )
         || ( ( GET_F( ) & CPU_FLAG_H  ) !=  CPU_FLAG_H )   //  10
         || ( ( GET_F( ) & CPU_FLAG_N  ) !=           0 )   //  02
         || ( ( GET_F( ) & CPU_FLAG_C  ) !=  CPU_FLAG_C ) ) //  01
    {
        //  NO:     Write an error message
        printf( "POST: tc_add_hlss_01 failed:     [add  hl, de]\n" );
        printf( "POST: HL = 0x%04X\n", CPU_REG_HL );
        printf( "POST: F  = 0x%02X\n", GET_F( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  INC     ss
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
tc_inc_ss_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x01, 0x00, 0x00,       //  0000    BC, x'0000
        0x11, 0xFF, 0x00,       //  0003    DE, x'00FF
        0x21, 0xFF, 0x0F,       //  0006    HL, x'0FFF
        0x31, 0xFF, 0xFF,       //  0009    SP, x'FFFF
        0x03,                   //  000C    INC BC
        0x13,                   //  000D    INC DE
        0x23,                   //  000E    INC HL
        0x33,                   //  000F    INC SP
        0x76      };            //  0010    HALT

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

    if (    ( CPU_REG_BC != 0x0001 )
         || ( CPU_REG_DE != 0x0100 )
         || ( CPU_REG_HL != 0x1000 )
         || ( CPU_REG_SP != 0x0000 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_inc_ss_00 failed:     [inc  ss    ]\n" );
        printf( "POST: BC = 0x%04X\n", CPU_REG_BC );
        printf( "POST: DE = 0x%04X\n", CPU_REG_DE );
        printf( "POST: HL = 0x%04X\n", CPU_REG_HL );
        printf( "POST: SP = 0x%04X\n", CPU_REG_SP );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  DEC     ss
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
tc_dec_ss_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x01, 0x00, 0x00,       //  0000    BC, x'0000
        0x11, 0x10, 0x00,       //  0003    DE, x'0010
        0x21, 0x00, 0x01,       //  0006    HL, x'0100
        0x31, 0x00, 0x10,       //  0009    SP, x'1000
        0x0B,                   //  000C    DEC BC
        0x1B,                   //  000D    DEC DE
        0x2B,                   //  000E    DEC HL
        0x3B,                   //  000F    DEC SP
        0x76      };            //  0010    HALT

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

    if (    ( CPU_REG_BC != 0xFFFF )
         || ( CPU_REG_DE != 0x000F )
         || ( CPU_REG_HL != 0x00FF )
         || ( CPU_REG_SP != 0x0FFF ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_dec_ss_00 failed:     [dec  ss    ]\n" );
        printf( "POST: BC = 0x%04X\n", CPU_REG_BC );
        printf( "POST: DE = 0x%04X\n", CPU_REG_DE );
        printf( "POST: HL = 0x%04X\n", CPU_REG_HL );
        printf( "POST: SP = 0x%04X\n", CPU_REG_SP );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  ADC  HL, ss
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
tc_adchlss_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x21, 0x00, 0x80,       //  0006    HL, x'8000
        0x01, 0x01, 0x00,       //  0000    BC, x'0001
        0x11, 0x10, 0x00,       //  0003    DE, x'0010
        0x31, 0x00, 0x01,       //  0009    SP, x'0100
        //                                                  ;HL = 8000h
        0xED, 0x4A,             //  000C    ADC  HL, BC     ;HL = 8001h
        0xED, 0x5A,             //  000C    ADC  HL, DE     ;HL = 8011h
        0xED, 0x6A,             //  000C    ADC  HL, HL     ;HL = 0022h
        0xED, 0x7A,             //  000C    ADC  HL, SP     ;HL = 0123h
        0x76      };            //  0010    HALT

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

    if ( CPU_REG_HL != 0x0123 )
    {
        //  NO:     Write an error message
        printf( "POST: tc_adchlss_00 failed:     [adc  hl, ss]\n" );
        printf( "POST: HL = 0x%04X\n", CPU_REG_HL );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  SBC  HL, ss
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
tc_sbchlss_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x21, 0x11, 0x81,       //  0006    HL, x'8111
        0x01, 0x01, 0x00,       //  0000    BC, x'0001
        0x11, 0x10, 0x00,       //  0003    DE, x'0010
        0x31, 0x00, 0x01,       //  0009    SP, x'0100
        //                                                  ;HL = 8111h
        0xED, 0x42,             //  000C    SBC  HL, BC     ;HL = 8110h
        0xED, 0x52,             //  000C    SBC  HL, DE     ;HL = 8100h
        0xED, 0x62,             //  000C    SBC  HL, HL     ;HL = 0000h
        0xED, 0x72,             //  000C    SBC  HL, SP     ;HL = FF00h
        0x76      };            //  0010    HALT

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

    if ( CPU_REG_HL != 0xFF00 )
    {
        //  NO:     Write an error message
        printf( "POST: tc_sbchlss_00 failed:     [sbc  hl, ss]\n" );
        printf( "POST: HL = 0x%04X\n", CPU_REG_HL );

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
math_16_post(
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
        if ( post_rc == true )      post_rc = tc_add_hlbc_00( );    //  ADD  HL, BC
        if ( post_rc == true )      post_rc = tc_add_hlde_01( );    //  ADD  HL, DE
        if ( post_rc == true )      post_rc = tc_inc_ss_00( );      //  INC  ss
        if ( post_rc == true )      post_rc = tc_dec_ss_00( );      //  DEC  ss

        //  Z80 ONLY instructions
        if( CPU == CPU_Z80 )
        {
            if ( post_rc == true )  post_rc = tc_adchlss_00( );     //  ADC  HL, SS
            if ( post_rc == true )  post_rc = tc_sbchlss_00( );     //  SBC  HL, SS
        }

        //  Was the test suite successfully complete :
        if( post_rc == true )
        {
            //  YES:    Write a completion message
            printf( "POST: MATH-16 complete %s mode.\n",
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