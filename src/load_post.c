/*******************************  COPYRIGHT  ********************************/
/*
 *  Author? "Gregory N. Leonhardt"
 *  License? "CC BY-NC 2.0"
 *           "https://creativecommons.org/licenses/by-nc/2.0/"
 *
 ****************************************************************************/

/******************************** JAVADOC ***********************************/
/**
 *  This file contains emulation code for all "LD" instructions.
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
#include "load.h"               //  LD *,*
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
 *  LD      r, n
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
tc_ld_rn_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x06, 0x11,         //  0000    LD  B,x'11
            0x0E, 0x22,         //  0002    LD  C,x'22
            0x16, 0x33,         //  0004    LD  D,x'33
            0x1E, 0x44,         //  0006    LD  E,x'44
            0x26, 0x55,         //  0008    LD  H,x'55
            0x2E, 0x66,         //  000A    LD  L,x'66
            0x3E, 0x77,         //  000C    LD  A,x'77
            0x76      };        //  000E    HALT

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

    if (    ( GET_B( ) != 0x11 )
         || ( GET_C( ) != 0x22 )
         || ( GET_D( ) != 0x33 )
         || ( GET_E( ) != 0x44 )
         || ( GET_H( ) != 0x55 )
         || ( GET_L( ) != 0x66 )
         || ( GET_A( ) != 0x77 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ld_rn_00 failed:     [LD  r, n]\n" );
        printf( "POST: BC = 0x%04X\n", CPU_REG_BC );
        printf( "POST: DE = 0x%04X\n", CPU_REG_DE );
        printf( "POST: HL = 0x%04X\n", CPU_REG_HL );
        printf( "POST: AF = 0x%04X\n", CPU_REG_AF );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  LD      ss, NN
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
tc_ld_ssNN_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x01, 0X23, 0X01,       //  0000    LD  BC, 0x0123
        0x11, 0X67, 0X45,       //  0003    LD  DE, 0x4567
        0x21, 0XAB, 0X89,       //  0006    LD  HL, 0x89AB
        0x31, 0XEF, 0XCD,       //  0009    LD  SP, 0xCDEF
        0x76      };            //  000C    HALT


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

    if (    ( CPU_REG_BC != 0x0123 )
         || ( CPU_REG_DE != 0x4567 )
         || ( CPU_REG_HL != 0x89AB )
         || ( CPU_REG_SP != 0xCDEF ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ld_ssNN_00 failed:     [LD  ss, NN]\n" );
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
 *  LD      r, r
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *
 *      Uses the data saved in registers from test_load_0000.
 *
 ****************************************************************************/

static
int
tc_ld_rr_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
            0x06, 0x11,         //  0000    LD  B,x'11
            0x0E, 0x22,         //  0002    LD  C,x'22
            0x16, 0x33,         //  0004    LD  D,x'33
            0x1E, 0x44,         //  0006    LD  E,x'44
            0x26, 0x55,         //  0008    LD  H,x'55
            0x2E, 0x66,         //  000A    LD  L,x'66
            0x3E, 0x77,         //  000C    LD  A,x'77
            0x41,               //  000E    LD  B,C
            0x4A,               //  000F    LD  C,D
            0x53,               //  0010    LD  D,E
            0x5C,               //  0011    LD  E,H
            0x65,               //  0012    LD  H,L
            0x6F,               //  0013    LD  L,A
            0x78,               //  0014    LD  A,B
            0x76      };        //  0015    HALT

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

    if (    ( GET_B( ) != 0x22 )
         || ( GET_C( ) != 0x33 )
         || ( GET_D( ) != 0x44 )
         || ( GET_E( ) != 0x55 )
         || ( GET_H( ) != 0x66 )
         || ( GET_L( ) != 0x77 )
         || ( GET_A( ) != 0x22 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ld_rr_00 failed:     [LD  r,r]\n" );
        printf( "POST: BC = 0x%04X\n", CPU_REG_BC );
        printf( "POST: DE = 0x%04X\n", CPU_REG_DE );
        printf( "POST: HL = 0x%04X\n", CPU_REG_HL );
        printf( "POST: AF = 0x%04X\n", CPU_REG_AF );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  LD      (HL), r
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
tc_ld_hlr_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x21, 0x00, 0x01,       //  0000    LD  HL, 0x0100
        0x06, 0x11,             //  0003    LD  B,x'11
        0x70,                   //  0006    LD  (HL), B
        0x21, 0x01, 0x01,       //  0007    LD  HL, 0x0101
        0x0E, 0x22,             //  000A    LD  C,x'22
        0x71,                   //  000C    LD  (HL), C
        0x21, 0x02, 0x01,       //  000D    LD  HL, 0x0102
        0x16, 0x33,             //  0010    LD  D,x'33
        0x72,                   //  0012    LD  (HL), D
        0x21, 0x03, 0x01,       //  0013    LD  HL, 0x0103
        0x1E, 0x44,             //  0016    LD  E,x'44
        0x73,                   //  0018    LD  (HL), E
        0x21, 0x04, 0x01,       //  0019    LD  HL, 0x0104
        0x74,                   //  001C    LD  (HL), H
        0x21, 0x05, 0x01,       //  001D    LD  HL, 0x0105
        0x75,                   //  0020    LD  (HL), L
        0x21, 0x06, 0x01,       //  0021    LD  HL, 0x0106
        0x3E, 0x77,             //  0024    LD  A,x'77
        0x77,                   //  0026    LD  (HL), A
        0x76      };            //  001F    HALT

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

    if (    ( memory_get_8( 0x0100 ) != 0x11 )
         || ( memory_get_8( 0x0101 ) != 0x22 )
         || ( memory_get_8( 0x0102 ) != 0x33 )
         || ( memory_get_8( 0x0103 ) != 0x44 )
         || ( memory_get_8( 0x0104 ) != 0x01 )
         || ( memory_get_8( 0x0105 ) != 0x05 )
         || ( memory_get_8( 0x0106 ) != 0x77 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ld_hlr_00 failed:     [LD  (HL), r]\n" );
        printf( "POST: B (0x0100) = 0x%02X\n", memory_get_8( 0x0100 ) );
        printf( "POST: C (0x0101) = 0x%02X\n", memory_get_8( 0x0101 ) );
        printf( "POST: D (0x0102) = 0x%02X\n", memory_get_8( 0x0102 ) );
        printf( "POST: E (0x0103) = 0x%02X\n", memory_get_8( 0x0103 ) );
        printf( "POST: H (0x0104) = 0x%02X\n", memory_get_8( 0x0104 ) );
        printf( "POST: L (0x0105) = 0x%02X\n", memory_get_8( 0x0105 ) );
        printf( "POST: A (0x0106) = 0x%02X\n", memory_get_8( 0x0106 ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  LD      r, (HL)
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      Resisters H and L are not tested because the HL register pair is
 *      needed as the data source address.
 *
 ****************************************************************************/

static
int
tc_ld_rhl_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x21, 0x03, 0x00,       //  0000    LD  HL, 0x0003
        0x46,                   //  0003    LD  B,(HL)
        0x21, 0x07, 0x00,       //  0004    LD  HL, 0x0007
        0x4E,                   //  0007    LD  C,(HL)
        0x21, 0x0B, 0x00,       //  0008    LD  HL, 0x000B
        0x56,                   //  000B    LD  D,(HL)
        0x21, 0x0F, 0x00,       //  000C    LD  HL, 0x000F
        0x5E,                   //  000F    LD  E,(HL)
        0x21, 0x13, 0x00,       //  0010    LD  HL, 0x0013
        0x7E,                   //  0013    LD  A,(HL)
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

    if (    ( GET_B( ) != 0x46 )
         || ( GET_C( ) != 0x4E )
         || ( GET_D( ) != 0x56 )
         || ( GET_E( ) != 0x5E )
         || ( GET_A( ) != 0x7E ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ld_rhl_00 failed:     [LD  r, (HL)]\n" );
        printf( "POST: BC = 0x%04X\n", CPU_REG_BC );
        printf( "POST: DE = 0x%04X\n", CPU_REG_DE );
        printf( "POST: AF = 0x%04X\n", CPU_REG_AF );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  LD      (HL), n
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
tc_ld_hln_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x21, 0x00, 0x01,       //  0000    LD  HL, 0x0100
        0x36, 0x36,             //  0003    LD  (HL), x'36
        0x76      };            //  0005    HALT


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

    if (    ( memory_get_8( 0x0100 ) != 0x36 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ld_hln_00 failed:     [LD  (HL), n]\n" );
        printf( "POST: (0x0100) = 0x%02X\n", memory_get_8( 0x0100 ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  LD      HL, (nn)
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
tc_ld_hlnn_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x21, 0x00, 0x01,       //  0000    LD  HL, 0x0100
        0x36, 0xAA,             //  0003    LD  (HL), 0xAA
        0x21, 0x01, 0x01,       //  0005    LD  HL, 0x0101
        0x36, 0x55,             //  0008    LD  (HL), 0x55
        0x2A, 0x00, 0x01,       //  000A    LD  HL, (0x0100)
        0x76      };            //  000D    HALT


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

    if (    ( CPU_REG_HL != 0x55AA ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ld_hlnn_00 failed:     [LD  HL, (nn)]\n" );
        printf( "POST: HL = 0x%04X\n", CPU_REG_HL );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  LD      A, (ss)
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
tc_ld_ass_00(
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
        0x36, 0xCC,             //  0003    LD  (HL), 0xCC
        0x21, 0x00, 0x21,       //  0005    LD  HL, 0x0021
        0x36, 0xDD,             //  0008    LD  (HL), 0xDD
        0x01, 0x00, 0x20,       //  000A    LD  BC, 0x0020
        0x11, 0x00, 0x21,       //  000D    LD  DE, 0x0021
        0x0A,                   //  0010    LD  A, (BC)
        0x67,                   //  0011    LD  H, A
        0x1A,                   //  0012    LD  A, (DE)
        0x6F,                   //  0013    LD  L, A
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

    if (    ( CPU_REG_HL != 0xCCDD ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ld_ass_00 failed:     [LD  A, (ss)]\n" );
        printf( "POST: HL = 0x%04X\n", CPU_REG_HL );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  LD      A, (nn)
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
tc_ld_ann_00(
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
        0x36, 0x5A,             //  0003    LD  (HL), 0x5A
        0x3A, 0x20, 0x00,       //  0005    LD  A, (0x0020)
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

    if ( GET_A( ) != 0x5A )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ld_ann_00 failed:     [LD  A, (nn)]\n" );
        printf( "POST: A = 0x%02X\n", GET_A( ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  LD      (ss), A
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
tc_ld_ssa_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x01, 0x20, 0x00,       //  0000    LD  BC, 0x0020
        0x11, 0x21, 0x00,       //  0003    LD  DE, 0x0021
        0x21, 0x91, 0x19,       //  0006    LD  HL, 0x9119
        0x7C,                   //  0009    LD  A, H
        0x02,                   //  000A    LD  (BC), A
        0x7D,                   //  000B    LD  A, L
        0x12,                   //  000C    LD  (DE), A
        0x76      };            //  000D    HALT

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

    if ( memory_get_16( 0x0020 ) != 0x1991 )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ld_ssa_00 failed:     [LD  (ss), A]\n" );
        printf( "POST: (0x020) = 0x%04X\n", memory_get_16( 0x0020 ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  LD      (nn), A
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
tc_ld_nna_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x21, 0x91, 0x19,       //  0000    LD  HL, 0x1991
        0x7C,                   //  0003    LD  A, H
        0x32, 0x20, 0x00,       //  0004    LD  (0x0020), A
        0x7D,                   //  0007    LD  A, L
        0x32, 0x21, 0x00,       //  0008    LD  (0x0021), A
        0x76      };            //  000B    HALT

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

    if ( memory_get_16( 0x0020 ) != 0x1991 )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ld_nna_00 failed:     [LD  (nn), A]\n" );
        printf( "POST: (0x0020) = 0x%04X\n", memory_get_16( 0x0020 ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  LD      (nn), HL
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
tc_ld_nnhl_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x21, 0x5A, 0xA5,       //  0000    LD  HL, 0xA55A
        0x22, 0x20, 0x00,       //  0003    LD  (0x0020), HL
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

    if ( memory_get_16( 0x0020 ) != 0x5AA5 )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ld_nnhl_00 failed:     [LD  (nn), HL]\n" );
        printf( "POST: (0x0020) = 0x%04X\n", memory_get_16( 0x0020 ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  LD      SP, HL
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
tc_ld_sphl_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x21, 0x3C, 0xC3,       //  0000    LD  HL, 0xC33C
        0xF9,                   //  0003    LD  SP, HL
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

    if ( CPU_REG_SP != 0xC33C )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ld_sphl_00 failed:     [LD  SP, HL]\n" );
        printf( "POST: (0x0020) = 0x%04X\n", CPU_REG_SP );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  PUSH    qq
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      The data in the flags (F) register are indeterminate and are not
 *      verified in the results phase.
 *
 *      Data is pushed on the stack HH, LL and the stack pointer decrements
 *      for each byte.  Thus when looking at memory the data is seen in
 *      reverse order.
 *
 ****************************************************************************/

static
int
tc_push_qq_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x31, 0x20, 0x00,       //  0000    LD  SP, 0x0020
        0x01, 0xCC, 0xBB,       //  0003    LD  BC, 0xBBCC
        0x11, 0xEE, 0xDD,       //  0006    LD  DE, 0xDDEE
        0x21, 0x81, 0x80,       //  0009    LD  HL, 0x8081
        0x3E, 0x99,             //  000C    LD  A, 0x99
        0xC5,                   //  000E    PUSH BC
        0xD5,                   //  000F    PUSH DE
        0xE5,                   //  0010    PUSH HL
        0xF5,                   //  0011    PUSH AF
        0x76      };            //  0012    HALT

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

    if (    ( CPU_REG_SP              != 0x0018 )
         || ( memory_get_8 ( 0x0019 ) != 0x99 )
         || ( memory_get_16( 0x001A ) != 0x8180 )
         || ( memory_get_16( 0x001C ) != 0xEEDD )
         || ( memory_get_16( 0x001E ) != 0xCCBB ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_push_qq_00 failed:     [PUSH qq]\n" );
        printf( "POST: SP       = 0x%04X\n", CPU_REG_SP );
        printf( "POST: (0x0019) = 0x%02X\n", memory_get_8( 0x0019 ) );
        printf( "POST: (0x001A) = 0x%04X\n", memory_get_16( 0x001A ) );
        printf( "POST: (0x001C) = 0x%04X\n", memory_get_16( 0x001C ) );
        printf( "POST: (0x001E) = 0x%04X\n", memory_get_16( 0x001E ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  POP     qq
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      This test MUST immediately follow the "PUSH qq" test as it recovers
 *      the stack data loaded in that test.
 *
 ****************************************************************************/

static
int
tc_pop_qq_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0xF1,                   //  0003    POP  AF
        0xE1,                   //  0004    POP  HL
        0xD1,                   //  0005    POP  DE
        0xC1,                   //  0006    POP  BC
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

    if (    ( CPU_REG_SP != 0x0020 )
         || ( GET_A( )   != 0x99 )
         || ( CPU_REG_HL != 0x8081 )
         || ( CPU_REG_DE != 0xDDEE )
         || ( CPU_REG_BC != 0xBBCC ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_pop_qq_00 failed:     [POP  qq]\n" );
        printf( "POST: SP  = 0x%04X\n", CPU_REG_SP );
        printf( "POST: A   = 0x%02X\n", GET_A( )   );
        printf( "POST: HL  = 0x%04X\n", CPU_REG_HL );
        printf( "POST: DE  = 0x%04X\n", CPU_REG_DE );
        printf( "POST: BC  = 0x%04X\n", CPU_REG_BC );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  LD      (nn), ss
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
tc_ld_nnss_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x01, 0x22, 0x11,       //  0000    LD   BC, 1122h
        0x11, 0x44, 0x33,       //  0003    LD   DE, 3344h
        0x21, 0x66, 0x55,       //  0006    LD   HL, 5566h
        0x31, 0x88, 0x77,       //  0009    LD   SP, 7788h
        0xED, 0x43, 0x20, 0x00, //  000C    LD   (0020h), BC
        0xED, 0x53, 0x22, 0x00, //  0010    LD   (0022h), DE
        0xED, 0x63, 0x24, 0x00, //  0014    LD   (0024h), HL
        0xED, 0x73, 0x26, 0x00, //  0018    LD   (0026h), SP
        0x76      };            //  001C    HALT

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

    if (    ( memory_get_16( 0x0020 ) != 0x2211 )
         || ( memory_get_16( 0x0022 ) != 0x4433 )
         || ( memory_get_16( 0x0024 ) != 0x6655 )
         || ( memory_get_16( 0x0026 ) != 0x8877 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ld_nnss_00 failed:     [LD   (nn),ss]\n" );
        printf( "POST: (0x0020) = 0x%04X\n", memory_get_16( 0x0020 ) );
        printf( "POST: (0x0022) = 0x%04X\n", memory_get_16( 0x0022 ) );
        printf( "POST: (0x0024) = 0x%04X\n", memory_get_16( 0x0024 ) );
        printf( "POST: (0x0026) = 0x%04X\n", memory_get_16( 0x0026 ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  LD      ss, (nn)
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
tc_ld_ssnn_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        //  Initial register load
        0x01, 0x99, 0x88,       //  0000    LD   BC, 8899h
        0x11, 0xBB, 0xAA,       //  0003    LD   DE, AABBh
        0x21, 0xDD, 0xCC,       //  0006    LD   HL, CCDDh
        0x31, 0xFF, 0xEE,       //  0009    LD   SP, EEFFh
        //  Save registers
        0xED, 0x43, 0x40, 0x00, //  000C    LD   (0040h), BC
        0xED, 0x53, 0x42, 0x00, //  0010    LD   (0042h), DE
        0xED, 0x63, 0x44, 0x00, //  0014    LD   (0044h), HL
        0xED, 0x73, 0x46, 0x00, //  0018    LD   (0046h), SP
        //  Change the contents of the registers
        0x01, 0x00, 0x00,       //  001C    LD   BC, 0000h
        0x11, 0x00, 0x00,       //  001F    LD   DE, 0000h
        0x21, 0x00, 0x00,       //  0022    LD   HL, 0000h
        0x31, 0x00, 0x00,       //  0025    LD   SP, 0000H
        //  Load registers
        0xED, 0x4B, 0x40, 0x00, //  0028    LD   BC, (0040h)
        0xED, 0x5B, 0x42, 0x00, //  002C    LD   DE, (0042h)
        0xED, 0x6B, 0x44, 0x00, //  0030    LD   HL, (0044h)
        0xED, 0x7B, 0x46, 0x00, //  0034    LD   SP, (0046h)
        0x76      };            //  0038    HALT

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

    if (    ( CPU_REG_BC != 0x8899 )
         || ( CPU_REG_DE != 0xAABB )
         || ( CPU_REG_HL != 0xCCDD )
         || ( CPU_REG_SP != 0xEEFF ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ld_ssnn_00 failed:     [LD   ss,(nn)]\n" );
        printf( "POST: BC       = 0x%04X\n", CPU_REG_BC );
        printf( "POST: DE       = 0x%04X\n", CPU_REG_DE );
        printf( "POST: HL       = 0x%04X\n", CPU_REG_HL );
        printf( "POST: SP       = 0x%04X\n", CPU_REG_SP );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  LD      i, a
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
tc_ld_ia_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        //  Initial register load
        0x3E, 0xAA,             //  0000    LD   A,x'AA
        0xED, 0x47,             //  0002    LD   I, A
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

    if (    ( GET_A( )   != 0xAA )
         || ( CPU_REG_I  != 0xAA ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ld_ia_00 failed:     [LD   i, a]\n" );
        printf( "POST: A        = 0x%02X\n", GET_A( )   );
        printf( "POST: I        = 0x%02X\n", CPU_REG_I  );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  LD      a, i
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
tc_ld_ai_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        //  Initial register load
        0x3E, 0x55,             //  0000    LD   A, 55h
        0xED, 0x47,             //  0002    LD   I, A
        0x3E, 0x00,             //  0000    LD   A, 00h
        0xED, 0x57,             //  0002    LD   A, I
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

    if (    ( GET_A( )   != 0x55 )
         || ( CPU_REG_I  != 0x55 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ld_ai_00 failed:     [LD   a, i]\n" );
        printf( "POST: A        = 0x%02X\n", GET_A( )   );
        printf( "POST: I        = 0x%02X\n", CPU_REG_I  );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  LD      r, a
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      The refresh register increments from the fetching of instructions
 *      resulting the the difference between written and read values. If
 *      additional instructions are placed between the write and read
 *      a different value would result.
 *
 ****************************************************************************/

static
int
tc_ld_ra_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        //  Initial register load
        0x3E, 0xAA,             //  0000    LD   A,x'AA
        0xED, 0x4F,             //  0002    LD   R, A
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

    if (    ( GET_A( )   != 0xAA )
         || ( CPU_REG_R  != 0xAD ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ld_ra_00 failed:     [LD   r, a]\n" );
        printf( "POST: A        = 0x%02X\n", GET_A( )   );
        printf( "POST: R        = 0x%02X\n", CPU_REG_R  );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  LD      a, r
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
tc_ld_ar_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        //  Initial register load
        0x3E, 0xFF,             //  0000    LD   A, FFh
        0xED, 0x4F,             //  0002    LD   R, A
        0x3E, 0x00,             //  0000    LD   A, 00h
        0xED, 0x5F,             //  0002    LD   A, R
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

    if (    ( GET_A( )   != 0x83 )
         || ( CPU_REG_R  != 0x86 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ld_ar_00 failed:     [LD   a, r]\n" );
        printf( "POST: A        = 0x%02X\n", GET_A( )   );
        printf( "POST: R        = 0x%02X\n", CPU_REG_R  );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  LDD
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
tc_ld_ldd_00(
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
        0x06, 0x10,             //  0003    LD   B, 010h    ;Byte Count
        0x3E, 0xAA,             //  0005    LD   A, 0AAh    ;Fill data
        0x77,                   //  0007 R: LD   (HL), A    ;Start filling memory
        0x2C,                   //  0008    INC  L          ;Increment pointer
        0x10, 0xFC,             //  0009    DJNZ R          ;Loop till B == 0
        //  Initial register load   DESTINATION
        0x21, 0x40, 0x00,       //  000B    LD   HL, 0040h  ;Initial pointer
        0x06, 0x10,             //  000E    LD   B, 010h    ;Byte Count
        0x3E, 0x55,             //  0010    LD   A, 055h    ;Fill data
        0x77,                   //  0011 T: LD   (HL), A    ;Start filling memory
        0x2C,                   //  0012    INC  L          ;Increment pointer
        0x10, 0xFC,             //  0013    DJNZ T          ;Loop till B == 0
        //  Start the test
        0x21, 0x31, 0x00,       //  0015    LD   HL, 0031h  ;From
        0x11, 0x41, 0x00,       //  0018    LD   DE, 0041h  ;To
        0x01, 0x02, 0x00,       //  001B    LD   BC, 0002h  ;Byte Count
        0xED, 0xA8,             //  001E W: LDD             ;Copy DE<-HL
        0xE2, 0x1E, 0x00,       //  0020    JP   PO, W      ;JP if BC == 0
        0x76      };            //  0023    HALT            ;THE END

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

    if (    ( CPU_REG_BC             != 0x0001 )
         || ( CPU_REG_DE             != 0x0040 )
         || ( CPU_REG_HL             != 0x0030 )
         || ( memory_get_8( 0x0040 ) !=   0x55 )
         || ( memory_get_8( 0x0041 ) !=   0xAA )
         || ( memory_get_8( 0x0042 ) !=   0x55 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ld_ldd_00 failed:     [LDD      ]\n" );
        printf( "POST: BC       = 0x%04X\n", CPU_REG_BC );
        printf( "POST: DE       = 0x%04X\n", CPU_REG_DE );
        printf( "POST: HL       = 0x%04X\n", CPU_REG_HL );
        memory_dump( 0x0030, 33 );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  LDD
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
tc_ld_ldd_01(
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
        0x06, 0x10,             //  0003    LD   B, 010h    ;Byte Count
        0x3E, 0x11,             //  0005    LD   A, 011h    ;Fill data
        0x77,                   //  0007 R: LD   (HL), A    ;Start filling memory
        0x2C,                   //  0008    INC  L          ;Increment pointer
        0x10, 0xFC,             //  0009    DJNZ R          ;Loop till B == 0
        //  Initial register load   DESTINATION
        0x21, 0x40, 0x00,       //  000B    LD   HL, 0040h  ;Initial pointer
        0x06, 0x10,             //  000E    LD   B, 010h    ;Byte Count
        0x3E, 0xEE,             //  0010    LD   A, 0EEh    ;Fill data
        0x77,                   //  0012 T: LD   (HL), A    ;Start filling memory
        0x2C,                   //  0013    INC  L          ;Increment pointer
        0x10, 0xFC,             //  0014    DJNZ T          ;Loop till B == 0
        //  Start the test
        0x21, 0x3E, 0x00,       //  0016    LD   HL, 003Eh  ;From
        0x11, 0x4E, 0x00,       //  0019    LD   DE, 004Eh  ;To
        0x01, 0x0E, 0x00,       //  001C    LD   BC, 000Eh  ;Byte Count
        0xED, 0xA8,             //  001F W: LDD             ;Copy DE<-HL
        0xEA, 0x1F, 0x00,       //  0021    JP   PE, W      ;JP if BC != 0
        0x76      };            //  0024    HALT            ;THE END

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

    if (    ( CPU_REG_BC             != 0x0000 )
         || ( CPU_REG_DE             != 0x0040 )
         || ( CPU_REG_HL             != 0x0030 )
         || ( memory_get_8( 0x0040 ) !=   0xEE )
         || ( memory_get_8( 0x0041 ) !=   0x11 )
         || ( memory_get_8( 0x004E ) !=   0x11 )
         || ( memory_get_8( 0x004F ) !=   0xEE ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ld_ldd_01 failed:     [LDD      ]\n" );
        printf( "POST: BC       = 0x%04X\n", CPU_REG_BC );
        printf( "POST: DE       = 0x%04X\n", CPU_REG_DE );
        printf( "POST: HL       = 0x%04X\n", CPU_REG_HL );

        memory_dump( 0x0000, 49 );
        memory_dump( 0x0030, 33 );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  LDDR
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
tc_ld_lddr_00(
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
        0x06, 0x10,             //  0003    LD   B, 010h    ;Byte Count
        0x3E, 0x33,             //  0005    LD   A, 033h    ;Fill data
        0x77,                   //  0007 R: LD   (HL), A    ;Start filling memory
        0x2C,                   //  0008    INC  L          ;Increment pointer
        0x10, 0xFC,             //  0009    DJNZ R          ;Loop till B == 0
        //  Initial register load   DESTINATION
        0x21, 0x40, 0x00,       //  000B    LD   HL, 0040h  ;Initial pointer
        0x06, 0x10,             //  000E    LD   B, 010h    ;Byte Count
        0x3E, 0xCC,             //  0010    LD   A, 0CCh    ;Fill data
        0x77,                   //  0012 T: LD   (HL), A    ;Start filling memory
        0x2C,                   //  0013    INC  L          ;Increment pointer
        0x10, 0xFC,             //  0014    DJNZ T          ;Loop till B == 0
        //  Start the test
        0x21, 0x3E, 0x00,       //  0016    LD   HL, 003Eh  ;From
        0x11, 0x4E, 0x00,       //  0019    LD   DE, 004Eh  ;To
        0x01, 0x0E, 0x00,       //  001C    LD   BC, 000Eh  ;Byte Count
        0xED, 0xB8,             //  001F    LDDR            ;Copy DE<-HL till BC = 0
        0x76      };            //  0021    HALT            ;THE END

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

    if (    ( CPU_REG_BC             != 0x0000 )
         || ( CPU_REG_DE             != 0x0040 )
         || ( CPU_REG_HL             != 0x0030 )
         || ( memory_get_8( 0x0040 ) !=   0xCC )
         || ( memory_get_8( 0x0041 ) !=   0x33 )
         || ( memory_get_8( 0x004E ) !=   0x33 )
         || ( memory_get_8( 0x004F ) !=   0xCC ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ld_lddr_00 failed:     [LDDR     ]\n" );
        printf( "POST: BC       = 0x%04X\n", CPU_REG_BC );
        printf( "POST: DE       = 0x%04X\n", CPU_REG_DE );
        printf( "POST: HL       = 0x%04X\n", CPU_REG_HL );

        memory_dump( 0x0000, 49 );
        memory_dump( 0x0030, 33 );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  LDI
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
tc_ld_ldi_00(
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
        0x06, 0x10,             //  0003    LD   B, 010h    ;Byte Count
        0x3E, 0xAA,             //  0005    LD   A, 0AAh    ;Fill data
        0x77,                   //  0007 R: LD   (HL), A    ;Start filling memory
        0x2C,                   //  0008    INC  L          ;Increment pointer
        0x10, 0xFC,             //  0009    DJNZ R          ;Loop till B == 0
        //  Initial register load   DESTINATION
        0x21, 0x40, 0x00,       //  000B    LD   HL, 0040h  ;Initial pointer
        0x06, 0x10,             //  000E    LD   B, 010h    ;Byte Count
        0x3E, 0x55,             //  0010    LD   A, 055h    ;Fill data
        0x77,                   //  0011 T: LD   (HL), A    ;Start filling memory
        0x2C,                   //  0012    INC  L          ;Increment pointer
        0x10, 0xFC,             //  0013    DJNZ T          ;Loop till B == 0
        //  Start the test
        0x21, 0x31, 0x00,       //  0015    LD   HL, 0031h  ;From
        0x11, 0x41, 0x00,       //  0018    LD   DE, 0041h  ;To
        0x01, 0x02, 0x00,       //  001B    LD   BC, 0002h  ;Byte Count
        0xED, 0xA0,             //  001E W: LDI             ;Copy DE<-HL
        0xE2, 0x1E, 0x00,       //  0020    JP   PO, W      ;JP if BC == 0
        0x76      };            //  0023    HALT            ;THE END

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

    if (    ( CPU_REG_BC             != 0x0001 )
         || ( CPU_REG_DE             != 0x0042 )
         || ( CPU_REG_HL             != 0x0032 )
         || ( memory_get_8( 0x0040 ) !=   0x55 )
         || ( memory_get_8( 0x0041 ) !=   0xAA )
         || ( memory_get_8( 0x0042 ) !=   0x55 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ld_ldi_00 failed:     [LDI      ]\n" );
        printf( "POST: BC       = 0x%04X\n", CPU_REG_BC );
        printf( "POST: DE       = 0x%04X\n", CPU_REG_DE );
        printf( "POST: HL       = 0x%04X\n", CPU_REG_HL );
        memory_dump( 0x0030, 33 );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  LDI
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
tc_ld_ldi_01(
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
        0x06, 0x10,             //  0003    LD   B, 010h    ;Byte Count
        0x3E, 0x11,             //  0005    LD   A, 011h    ;Fill data
        0x77,                   //  0007 R: LD   (HL), A    ;Start filling memory
        0x2C,                   //  0008    INC  L          ;Increment pointer
        0x10, 0xFC,             //  0009    DJNZ R          ;Loop till B == 0
        //  Initial register load   DESTINATION
        0x21, 0x40, 0x00,       //  000B    LD   HL, 0040h  ;Initial pointer
        0x06, 0x10,             //  000E    LD   B, 010h    ;Byte Count
        0x3E, 0xEE,             //  0010    LD   A, 0EEh    ;Fill data
        0x77,                   //  0012 T: LD   (HL), A    ;Start filling memory
        0x2C,                   //  0013    INC  L          ;Increment pointer
        0x10, 0xFC,             //  0014    DJNZ T          ;Loop till B == 0
        //  Start the test
        0x21, 0x31, 0x00,       //  0016    LD   HL, 0031h  ;From
        0x11, 0x41, 0x00,       //  0019    LD   DE, 0041h  ;To
        0x01, 0x0E, 0x00,       //  001C    LD   BC, 000Eh  ;Byte Count
        0xED, 0xA0,             //  001F W: LDI             ;Copy DE<-HL
        0xEA, 0x1F, 0x00,       //  0021    JP   PE, W      ;JP if BC != 0
        0x76      };            //  0024    HALT            ;THE END

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

    if (    ( CPU_REG_BC             != 0x0000 )
         || ( CPU_REG_DE             != 0x004F )
         || ( CPU_REG_HL             != 0x003F )
         || ( memory_get_8( 0x0040 ) !=   0xEE )
         || ( memory_get_8( 0x0041 ) !=   0x11 )
         || ( memory_get_8( 0x004E ) !=   0x11 )
         || ( memory_get_8( 0x004F ) !=   0xEE ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ld_ldi_01 failed:     [LDI      ]\n" );
        printf( "POST: BC       = 0x%04X\n", CPU_REG_BC );
        printf( "POST: DE       = 0x%04X\n", CPU_REG_DE );
        printf( "POST: HL       = 0x%04X\n", CPU_REG_HL );

        memory_dump( 0x0030, 33 );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  LDIR
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
tc_ld_ldir_00(
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
        0x06, 0x10,             //  0003    LD   B, 010h    ;Byte Count
        0x3E, 0x33,             //  0005    LD   A, 033h    ;Fill data
        0x77,                   //  0007 R: LD   (HL), A    ;Start filling memory
        0x2C,                   //  0008    INC  L          ;Increment pointer
        0x10, 0xFC,             //  0009    DJNZ R          ;Loop till B == 0
        //  Initial register load   DESTINATION
        0x21, 0x40, 0x00,       //  000B    LD   HL, 0040h  ;Initial pointer
        0x06, 0x10,             //  000E    LD   B, 010h    ;Byte Count
        0x3E, 0xCC,             //  0010    LD   A, 0CCh    ;Fill data
        0x77,                   //  0012 T: LD   (HL), A    ;Start filling memory
        0x2C,                   //  0013    INC  L          ;Increment pointer
        0x10, 0xFC,             //  0014    DJNZ T          ;Loop till B == 0
        //  Start the test
        0x21, 0x31, 0x00,       //  0016    LD   HL, 0031h  ;From
        0x11, 0x41, 0x00,       //  0019    LD   DE, 0041h  ;To
        0x01, 0x0E, 0x00,       //  001C    LD   BC, 000Eh  ;Byte Count
        0xED, 0xB0,             //  001F    LDIR            ;Copy DE<-HL till BC = 0
        0x76      };            //  0021    HALT            ;THE END

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

    if (    ( CPU_REG_BC             != 0x0000 )
         || ( CPU_REG_DE             != 0x004F )
         || ( CPU_REG_HL             != 0x003F )
         || ( memory_get_8( 0x0040 ) !=   0xCC )
         || ( memory_get_8( 0x0041 ) !=   0x33 )
         || ( memory_get_8( 0x004E ) !=   0x33 )
         || ( memory_get_8( 0x004F ) !=   0xCC ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ld_ldir_00 failed:     [LDIR     ]\n" );
        printf( "POST: BC       = 0x%04X\n", CPU_REG_BC );
        printf( "POST: DE       = 0x%04X\n", CPU_REG_DE );
        printf( "POST: HL       = 0x%04X\n", CPU_REG_HL );

        memory_dump( 0x0000, 49 );
        memory_dump( 0x0030, 33 );

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
ld_post(
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
        if ( post_rc == true )      post_rc = tc_ld_rn_00( );       //  LD      r, n
        if ( post_rc == true )      post_rc = tc_ld_ssNN_00( );     //  LD   ss, nn
        if ( post_rc == true )      post_rc = tc_ld_rr_00( );       //  LD   r, r
        if ( post_rc == true )      post_rc = tc_ld_hlr_00( );      //  LD   (HL), r
        if ( post_rc == true )      post_rc = tc_ld_rhl_00( );      //  LD   r, (HL)
        if ( post_rc == true )      post_rc = tc_ld_hln_00( );      //  LD   (HL), n
        if ( post_rc == true )      post_rc = tc_ld_hlnn_00( );     //  LD   HL, (nn)
        if ( post_rc == true )      post_rc = tc_ld_ass_00( );      //  LD   A, (ss)
        if ( post_rc == true )      post_rc = tc_ld_ann_00( );      //  LD   A, (nn)
        if ( post_rc == true )      post_rc = tc_ld_ssa_00( );      //  LD   (ss), A
        if ( post_rc == true )      post_rc = tc_ld_nna_00( );      //  LD   (nn), A
        if ( post_rc == true )      post_rc = tc_ld_nnhl_00( );     //  LD   (nn), HL
        if ( post_rc == true )      post_rc = tc_ld_sphl_00( );     //  LD   SP, HL
        if ( post_rc == true )      post_rc = tc_push_qq_00( );     //  PUSH qq
        if ( post_rc == true )      post_rc = tc_pop_qq_00( );      //  POP  qq

        //  Z80 ONLY instructions
        if( CPU == CPU_Z80 )
        {
            if ( post_rc == true )  post_rc = tc_ld_nnss_00( );     //  LD   (nn), ss
            if ( post_rc == true )  post_rc = tc_ld_ssnn_00( );     //  LD   ss, (nn)
            if ( post_rc == true )  post_rc = tc_ld_ia_00( );       //  LD   i, a
            if ( post_rc == true )  post_rc = tc_ld_ai_00( );       //  LD   a, i
            if ( post_rc == true )  post_rc = tc_ld_ra_00( );       //  LD   r, a
            if ( post_rc == true )  post_rc = tc_ld_ar_00( );       //  LD   a, r
            if ( post_rc == true )  post_rc = tc_ld_ldd_00( );      //  LDD
            if ( post_rc == true )  post_rc = tc_ld_ldd_01( );      //  LDD
            if ( post_rc == true )  post_rc = tc_ld_lddr_00( );     //  LDDR
            if ( post_rc == true )  post_rc = tc_ld_ldi_00( );      //  LDI
            if ( post_rc == true )  post_rc = tc_ld_ldi_01( );      //  LDI
            if ( post_rc == true )  post_rc = tc_ld_ldir_00( );     //  LDIR
        }

        //  Was the test suite successfully complete :
        if( post_rc == true )
        {
            //  YES:    Write a completion message
            printf( "POST: LD      complete %s mode.\n",
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