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
#include "jump.h"               //  Jump instructions
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
 *  JP      nn
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
tc_jp_nn_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0xC3, 0x08, 0x00,       //  0000    JP      x'0008
        0x76,                   //  0003    HALT
        0x76,                   //  0004    HALT
        0x76,                   //  0005    HALT
        0x76,                   //  0006    HALT
        0x76,                   //  0007    HALT
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

    if ( CPU_REG_PC != 0x0009 )
    {
        //  NO:     Write an error message
        printf( "POST: tc_jp_nn_00 failed:     [jp   nn    ]\n" );
        printf( "POST: PC = 0x%04X\n", CPU_REG_PC );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  JP      NZ, nn
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
tc_jp_nz_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x01,             //  0000    LD      A, x'01
        0x87,                   //  0002    ADD     A           ; Z = 0
        0xC2, 0x0A, 0x00,       //  0003    JP      NZ, x'000A
        0x76,                   //  0006    HALT
        0x76,                   //  0007    HALT
        0x76,                   //  0008    HALT
        0x76,                   //  0009    HALT
        0x97,                   //  000A    SUB     A           ; Z = 1
        0xC2, 0x09, 0x00,       //  000B    JP      NZ, x'0009
        0x76,                   //  000E    HALT
        0x76,                   //  000F    HALT
        0x76,                   //  0010    HALT
        0x76      };            //  0011    HALT

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

    if ( CPU_REG_PC != 0x000F )
    {
        //  NO:     Write an error message
        printf( "POST: tc_jp_nz_00 failed:   [jp   NZ, nn]\n" );
        printf( "POST: PC = 0x%04X\n", CPU_REG_PC );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  JP      Z, nn
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
tc_jp_z_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x01,             //  0000    LD      A, x'01
        0x97,                   //  0002    SUB     A           ; Z = 1
        0xCA, 0x0A, 0x00,       //  0003    JP      Z, x'000A
        0x76,                   //  0006    HALT
        0x76,                   //  0007    HALT
        0x76,                   //  0008    HALT
        0x76,                   //  0009    HALT
        0x3C,                   //  000A    INC     A           ; Z = 0
        0xCA, 0x09, 0x00,       //  000B    JP      Z, x'0009
        0x76,                   //  000E    HALT
        0x76,                   //  000F    HALT
        0x76,                   //  0010    HALT
        0x76      };            //  0011    HALT

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

    if ( CPU_REG_PC != 0x000F )
    {
        //  NO:     Write an error message
        printf( "POST: tc_jp_z_00 failed:   [jp    Z, nn]\n" );
        printf( "POST: PC = 0x%04X\n", CPU_REG_PC );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  JP      NC, nn
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
tc_jp_nc_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x40,             //  0000    LD      A, x'40
        0x87,                   //  0002    ADD     A           ; C = 0
        0xD2, 0x0A, 0x00,       //  0003    JP      NC, x'000A
        0x76,                   //  0006    HALT
        0x76,                   //  0007    HALT
        0x76,                   //  0008    HALT
        0x76,                   //  0009    HALT
        0x87,                   //  000A    ADD     A           ; C = 1
        0xD2, 0x09, 0x00,       //  000B    JP      NC, x'0009
        0x76,                   //  000E    HALT
        0x76,                   //  000F    HALT
        0x76,                   //  0010    HALT
        0x76      };            //  0011    HALT

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

    if ( CPU_REG_PC != 0x000F )
    {
        //  NO:     Write an error message
        printf( "POST: tc_jp_nc_00 failed:   [jp   NC, nn]\n" );
        printf( "POST: PC = 0x%04X\n", CPU_REG_PC );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  JP      C, nn
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
tc_jp_c_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x80,             //  0000    LD      A, x'80
        0x87,                   //  0002    ADD     A           ; C = 1
        0xDA, 0x0A, 0x00,       //  0003    JP      C, x'000A
        0x76,                   //  0006    HALT
        0x76,                   //  0007    HALT
        0x76,                   //  0008    HALT
        0x76,                   //  0009    HALT
        0x87,                   //  000A    ADD     A           ; C = 0
        0xDA, 0x09, 0x00,       //  000B    JP      C, x'0009
        0x76,                   //  000E    HALT
        0x76,                   //  000F    HALT
        0x76,                   //  0010    HALT
        0x76      };            //  0011    HALT

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

    if ( CPU_REG_PC != 0x000f )
    {
        //  NO:     Write an error message
        printf( "POST: tc_jp_c_00 failed:   [jp    C, nn]\n" );
        printf( "POST: PC = 0x%04X\n", CPU_REG_PC );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  JP      PO, nn
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
tc_jp_po_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x00,             //  0000    LD      A, 00h
        0xF6, 0x02,             //  0002    OR      02h         ; P = 1
        0xE2, 0x0A, 0x00,       //  0004    JP      PO, x'000A
        0x76,                   //  0007    HALT
        0x76,                   //  0008    HALT
        0x76,                   //  0009    HALT
        0xF6, 0x08,             //  000A    OR      80h         ; P = 0
        0xE2, 0x09, 0x00,       //  000C    JP      PO, x'0009
        0x76,                   //  000F    HALT
        0x76,                   //  0010    HALT
        0x76,                   //  0011    HALT
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

    if ( CPU_REG_PC != 0x0010 )
    {
        //  NO:     Write an error message
        printf( "POST: tc_jp_po_00 failed:   [jp   PO, nn]\n" );
        printf( "POST: PC = 0x%04X\n", CPU_REG_PC );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  JP     PE, nn
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
tc_jp_pe_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;
    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x00,             //  0000    LD      A, 00h
        0xF6, 0x03,             //  0002    OR      03h         ; P = 0
        0xEA, 0x0A, 0x00,       //  0004    JP      PE, x'000A
        0x76,                   //  0007    HALT
        0x76,                   //  0008    HALT
        0x76,                   //  0009    HALT
        0xF6, 0x08,             //  000A    OR      80h         ; P = 1
        0xEA, 0x09, 0x00,       //  000C    JP      PE, x'0009
        0x76,                   //  000F    HALT
        0x76,                   //  0010    HALT
        0x76,                   //  0011    HALT
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

    if ( CPU_REG_PC != 0x0010 )
    {
        //  NO:     Write an error message
        printf( "POST: tc_jp_pe_00 failed:   [jp    PE, nn]\n" );
        printf( "POST: PC = 0x%04X\n", CPU_REG_PC );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  JP      P, nn
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
tc_jp_p_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x20,             //  0000    LD      A, x'20
        0x87,                   //  0002    ADD     A           ; S = 0
        0xF2, 0x0A, 0x00,       //  0003    JP      P, x'000A
        0x76,                   //  0006    HALT
        0x76,                   //  0007    HALT
        0x76,                   //  0008    HALT
        0x76,                   //  0009    HALT
        0x87,                   //  000A    ADD     A           ; S = 1
        0xF2, 0x09, 0x00,       //  000B    JP      P, x'0009
        0x76,                   //  000E    HALT
        0x76,                   //  000F    HALT
        0x76,                   //  0010    HALT
        0x76      };            //  0011    HALT

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

    if ( CPU_REG_PC != 0x000F )
    {
        //  NO:     Write an error message
        printf( "POST: tc_jp_p_00 failed:   [jp    P, nn]\n" );
        printf( "POST: PC = 0x%04X\n", CPU_REG_PC );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  JP      M, nn
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
tc_jp_m_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x40,             //  0000    LD      A, x'40
        0x87,                   //  0002    ADD     A           ; S = 1
        0xFA, 0x0A, 0x00,       //  0003    JP      M, x'000A
        0x76,                   //  0006    HALT
        0x76,                   //  0007    HALT
        0x76,                   //  0008    HALT
        0x76,                   //  0009    HALT
        0x87,                   //  000A    ADD     A           ; S = 0
        0xFA, 0x09, 0x00,       //  000B    JP      M, x'0009
        0x76,                   //  000E    HALT
        0x76,                   //  000F    HALT
        0x76,                   //  0010    HALT
        0x76      };            //  0011    HALT

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

    if ( CPU_REG_PC != 0x000F )
    {
        //  NO:     Write an error message
        printf( "POST: tc_jp_m_00 failed:   [jp    M, nn]\n" );
        printf( "POST: PC = 0x%04X\n", CPU_REG_PC );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  JP      (HL)
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
tc_jp_hl_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x21, 0x09, 0x00,       //  0000    LD      HL, '0009
        0xE9,                   //  0003    JP      (HL)
        0x76,                   //  0004    HALT
        0x76,                   //  0005    HALT
        0x76,                   //  0006    HALT
        0x76,                   //  0007    HALT
        0x76,                   //  0008    HALT
        0x76      };            //  0009    HALT

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

    if ( CPU_REG_PC != 0x000A )
    {
        //  NO:     Write an error message
        printf( "POST: tc_jp_hl_00 failed:   [jp    (hl) ]\n" );
        printf( "POST: PC = 0x%04X\n", CPU_REG_PC );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  DJNZ    e
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
tc_djnz_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x06, 0x80,             //  0000    LD   B, 80h
        0x3E, 0x00,             //  0002    LD   A, 0
        0x3C,                   //  0004 L: INC  A
        0x10, 0x01,             //  0005    DJNZ C          ;Positive displacement
        0x76,                   //  0007    HALT
        0x10, 0xFA,             //  0008 C: DJNZ L          ;Negative displacement
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

    if (    ( CPU_REG_PC != 0x000B )
         || ( GET_A( )   !=   0x40 )
         || ( GET_B( )   !=   0x00 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_djnz_00 failed:   [djnz  e    ]\n" );
        printf( "POST: PC = 0x%04X\n", CPU_REG_PC );
        printf( "POST: A  = 0x%02X\n", GET_A( )   );
        printf( "POST: B  = 0x%02X\n", GET_B( )   );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  JR      e
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
tc_jr_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x18, 0x02,             //  0000    JR   B          ;Positive displacement
        0x76,                   //  0002    HALT
        0x76,                   //  0003 A: HALT
        0x18, 0xFD,             //  0004 B: JR   A          ;Negative displacement
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

    if ( CPU_REG_PC != 0x0004 )
    {
        //  NO:     Write an error message
        printf( "POST: tc_jr_00 failed:   [jr    e    ]\n" );
        printf( "POST: PC = 0x%04X\n", CPU_REG_PC );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  JR      Z, e
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
tc_jrz_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x97,                   //  0000    SUB  A          ;Z = true
        0x28, 0x06,             //  0001    JR   Z, W       ;Positive displacement
        0x76,                   //  0003    HALT

        0x3C,                   //  0004 Q: INC  A          ;Z = false
        0x28, 0x01,             //  0005    JR   Z, Y
        0x76,                   //  0007    HALT

        0x76,                   //  0008 Y: HALT

        0x28, 0xF9,             //  0009 W: JR   Z, Q       ;Negative displacement
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

    if ( CPU_REG_PC != 0x0008 )
    {
        //  NO:     Write an error message
        printf( "POST: tc_jrz_00 failed:   [jr    z, e ]\n" );
        printf( "POST: PC = 0x%04X\n", CPU_REG_PC );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  JR      NZ, e
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
tc_jrnz_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x97,                   //  0000    SUB  A          ;Z = true
        0x3C,                   //  0001    INC  A          ;Z = false
        0x20, 0x06,             //  0002    JR   NZ, W      ;Positive displacement
        0x76,                   //  0004    HALT

        0x97,                   //  0005 Q: SUB  A          ;Z = true
        0x20, 0x01,             //  0006    JR   NZ, Y
        0x76,                   //  0008    HALT

        0x76,                   //  0009 Y: HALT

        0x20, 0xF9,             //  000A W: JR   NZ, Q      ;Negative displacement
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

    if ( CPU_REG_PC != 0x0009 )
    {
        //  NO:     Write an error message
        printf( "POST: tc_jrnz_00 failed:   [jr    nz, e]\n" );
        printf( "POST: PC = 0x%04X\n", CPU_REG_PC );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  JR      C, e
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
tc_jrc_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x80,             //  0000    LD   A, 80h
        0x87,                   //  0002    ADD  A          ;C = true
        0x38, 0x06,             //  0003    JR   C, W       ;Positive displacement
        0x76,                   //  0005    HALT

        0x87,                   //  0006 Q: ADD  A          ;C = false
        0x38, 0x01,             //  0007    JR   C, Y
        0x76,                   //  0009    HALT

        0x76,                   //  000A Y: HALT

        0x38, 0xF9,             //  000B W: JR   C, Q       ;Negative displacement
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

    if ( CPU_REG_PC != 0x000A )
    {
        //  NO:     Write an error message
        printf( "POST: tc_jrc_00 failed:   [jr    c, e ]\n" );
        printf( "POST: PC = 0x%04X\n", CPU_REG_PC );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  JR      NC, e
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
tc_jrnc_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x3E, 0x40,             //  0000    LD   A, 40h
        0x87,                   //  0002    ADD  A          ;C = false
        0x30, 0x06,             //  0003    JR   NC, W      ;Positive displacement
        0x76,                   //  0005    HALT

        0x87,                   //  0006 Q: ADD  A          ;C = true
        0x30, 0x01,             //  0007    JR   NC, Y
        0x76,                   //  0009    HALT

        0x76,                   //  000A Y: HALT

        0x30, 0xF9,             //  000B W: JR   NC, Q      ;Negative displacement
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

    if ( CPU_REG_PC != 0x000A )
    {
        //  NO:     Write an error message
        printf( "POST: tc_jrnc_00 failed:   [jr    nc, e]\n" );
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
 *  JUMP   Power On Self Test
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
jump_post(
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
        if ( post_rc == true )      post_rc = tc_jp_nn_00( );       //  JP   nn

        if ( post_rc == true )      post_rc = tc_jp_nz_00( );       //  JP   NZ, nn
        if ( post_rc == true )      post_rc = tc_jp_z_00( );        //  JP   Z, nn
        if ( post_rc == true )      post_rc = tc_jp_nc_00( );       //  JP   NC, nn
        if ( post_rc == true )      post_rc = tc_jp_c_00( );        //  JP   C, nn
        if ( post_rc == true )      post_rc = tc_jp_po_00( );       //  JP   PO, nn
        if ( post_rc == true )      post_rc = tc_jp_pe_00( );       //  JP   PE, nn
        if ( post_rc == true )      post_rc = tc_jp_p_00( );        //  JP   P, nn
        if ( post_rc == true )      post_rc = tc_jp_m_00( );        //  JP   M, nn

        if ( post_rc == true )      post_rc = tc_jp_hl_00( );       //  JP   (HL)

        //  Z80 ONLY instructions
        if( CPU == CPU_Z80 )
        {
           if ( post_rc == true )  post_rc = tc_djnz_00( );         //  DJNZ e
           if ( post_rc == true )  post_rc = tc_jr_00( );           //  JR   e
           if ( post_rc == true )  post_rc = tc_jrz_00( );          //  JR   N, e
           if ( post_rc == true )  post_rc = tc_jrnz_00( );         //  JR   NZ, e
           if ( post_rc == true )  post_rc = tc_jrc_00( );          //  JR   C, e
           if ( post_rc == true )  post_rc = tc_jrnc_00( );         //  JR   NC, e
        }

        //  Was the test suite successfully complete :
        if( post_rc == true )
        {
            //  YES:    Write a completion message
            printf( "POST: JUMP    complete %s mode.\n",
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