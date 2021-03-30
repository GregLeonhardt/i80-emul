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
#include "call.h"               //  Call instructions
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
 *  TEST_000:       CALL    nn
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
tc_call_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x00,                   //  0000    NOP
        0x31, 0x20, 0x00,       //  0001    LD      SP, x'0020
        0xCD, 0x0B, 0x00,       //  0004    CALL    x'000B
        0x76,                   //  0007    HALT
        0x76,                   //  0008    HALT
        0x76,                   //  0009    HALT
        0x76,                   //  000A    HALT
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

    if (    (    CPU_REG_PC           != 0x000C )
         || (    CPU_REG_SP           != 0x001E )
         || ( memory_get_16( 0x001E ) != 0x0700 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_call_00 failed:     [call nn    ]\n" );
        printf( "POST: PC       = 0x%04X\n", CPU_REG_PC );
        printf( "POST: SP       = 0x%04X\n", CPU_REG_SP );
        printf( "POST: (0x001E) = 0x%04X\n", memory_get_16( 0x001E ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  TEST_000:       CALL    NZ, nn
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
tc_call_nz_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x00,                   //  0000    NOP
        0x31, 0x20, 0x00,       //  0001    LD      SP, x'0020
        0x3E, 0x01,             //  0004    LD      A, x'01
        0x87,                   //  0006    ADD     A           ; Z = 0
        0xC4, 0x0E, 0x00,       //  0007    CALL    NZ, x'000E
        0x76,                   //  000A    HALT
        0x76,                   //  000B    HALT
        0x76,                   //  000C    HALT
        0x76,                   //  000D    HALT
        0x97,                   //  000E    SUB     A           ; Z = 1
        0xC4, 0x0C, 0x00,       //  000F    CALL    NZ, x'000C
        0x76,                   //  0012    HALT
        0x76,                   //  0013    HALT
        0x76,                   //  0014    HALT
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

    if (    (    CPU_REG_PC           != 0x0013 )
         || (    CPU_REG_SP           != 0x001E )
         || ( memory_get_16( 0x001E ) != 0x0A00 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_call_nz_00 failed:   [call NZ, nn]\n" );
        printf( "POST: PC       = 0x%04X\n", CPU_REG_PC );
        printf( "POST: SP       = 0x%04X\n", CPU_REG_SP );
        printf( "POST: (0x001E) = 0x%04X\n", memory_get_16( 0x001E ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  TEST_001:       CALL    Z, nn
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
tc_call_z_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x00,                   //  0000    NOP
        0x31, 0x20, 0x00,       //  0001    LD      SP, x'0020
        0x3E, 0x01,             //  0004    LD      A, x'01
        0x97,                   //  0006    SUB     A           ; Z = 1
        0xCC, 0x0E, 0x00,       //  0007    CALL    Z, x'000E
        0x76,                   //  000A    HALT
        0x76,                   //  000B    HALT
        0x76,                   //  000C    HALT
        0x76,                   //  000D    HALT
        0x3C,                   //  000E    INC     A           ; Z = 0
        0xCC, 0x0C, 0x00,       //  000F    CALL    Z, x'000C
        0x76,                   //  0012    HALT
        0x76,                   //  0013    HALT
        0x76,                   //  0014    HALT
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

    if (    (    CPU_REG_PC           != 0x0013 )
         || (    CPU_REG_SP           != 0x001E )
         || ( memory_get_16( 0x001E ) != 0x0A00 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_call_z_00 failed:   [call  Z, nn]\n" );
        printf( "POST: PC       = 0x%04X\n", CPU_REG_PC );
        printf( "POST: SP       = 0x%04X\n", CPU_REG_SP );
        printf( "POST: (0x001E) = 0x%04X\n", memory_get_16( 0x001E ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  TEST_002:       CALL    NC, nn
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
tc_call_nc_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x00,                   //  0000    NOP
        0x31, 0x20, 0x00,       //  0001    LD      SP, x'0020
        0x3E, 0x40,             //  0004    LD      A, x'40
        0x87,                   //  0006    ADD     A           ; C = 0
        0xD4, 0x0E, 0x00,       //  0007    CALL    NC, x'000E
        0x76,                   //  000A    HALT
        0x76,                   //  000B    HALT
        0x76,                   //  000C    HALT
        0x76,                   //  000D    HALT
        0x87,                   //  000E    ADD     A           ; C = 1
        0xD4, 0x0C, 0x00,       //  000F    CALL    NC, x'000C
        0x76,                   //  0012    HALT
        0x76,                   //  0013    HALT
        0x76,                   //  0014    HALT
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

    if (    (    CPU_REG_PC           != 0x0013 )
         || (    CPU_REG_SP           != 0x001E )
         || ( memory_get_16( 0x001E ) != 0x0A00 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_call_nc_00 failed:   [call NC, nn]\n" );
        printf( "POST: PC       = 0x%04X\n", CPU_REG_PC );
        printf( "POST: SP       = 0x%04X\n", CPU_REG_SP );
        printf( "POST: (0x001E) = 0x%04X\n", memory_get_16( 0x001E ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  TEST_003:       CALL    C, nn
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
tc_call_c_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x00,                   //  0000    NOP
        0x31, 0x20, 0x00,       //  0001    LD      SP, x'0020
        0x3E, 0x80,             //  0004    LD      A, x'80
        0x87,                   //  0006    ADD     A           ; C = 1
        0xDC, 0x0E, 0x00,       //  0007    CALL    C, x'000E
        0x76,                   //  000A    HALT
        0x76,                   //  000B    HALT
        0x76,                   //  000C    HALT
        0x76,                   //  000D    HALT
        0x87,                   //  000E    ADD     A           ; C = 0
        0xDC, 0x0C, 0x00,       //  000F    CALL    C, x'000C
        0x76,                   //  0012    HALT
        0x76,                   //  0013    HALT
        0x76,                   //  0014    HALT
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

    if (    (    CPU_REG_PC           != 0x0013 )
         || (    CPU_REG_SP           != 0x001E )
         || ( memory_get_16( 0x001E ) != 0x0A00 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_call_c_00 failed:   [call  C, nn]\n" );
        printf( "POST: PC       = 0x%04X\n", CPU_REG_PC );
        printf( "POST: SP       = 0x%04X\n", CPU_REG_SP );
        printf( "POST: (0x001E) = 0x%04X\n", memory_get_16( 0x001E ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  TEST_004:       CALL    PO, nn
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
tc_call_po_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x00,                   //  0000    NOP
        0x31, 0x20, 0x00,       //  0001    LD      SP, x'0020
        0x3E, 0x00,             //  0004    LD      A, 00h
        0xF6, 0x02,             //  0006    OR      02h         ; P = 1
        0xE4, 0x0E, 0x00,       //  0008    CALL    PO, x'000E
        0x76,                   //  000B    HALT
        0x76,                   //  000C    HALT
        0x76,                   //  000D    HALT
        0xF6, 0x08,             //  000E    OR      80h         ; P = 0
        0xE4, 0x0C, 0x00,       //  0010    CALL    PO, x'000C
        0x76,                   //  0013    HALT
        0x76,                   //  0014    HALT
        0x76,                   //  0015    HALT
        0x76      };            //  0016    HALT

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

    if (    (    CPU_REG_PC           != 0x0014 )
         || (    CPU_REG_SP           != 0x001E )
         || ( memory_get_16( 0x001E ) != 0x0B00 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_call_po_00 failed:   [call PO, nn]\n" );
        printf( "POST: PC       = 0x%04X\n", CPU_REG_PC );
        printf( "POST: SP       = 0x%04X\n", CPU_REG_SP );
        printf( "POST: (0x001E) = 0x%04X\n", memory_get_16( 0x001E ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  TEST_005:       CALL   PE, nn
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
tc_call_pe_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x00,                   //  0000    NOP
        0x31, 0x20, 0x00,       //  0001    LD      SP, x'0020
        0x3E, 0x00,             //  0004    LD      A, 00h
        0xF6, 0x03,             //  0006    OR      03h         ; P = 0
        0xEC, 0x0E, 0x00,       //  0008    CALL    PO, x'000E
        0x76,                   //  000B    HALT
        0x76,                   //  000C    HALT
        0x76,                   //  000D    HALT
        0xF6, 0x08,             //  000E    OR      80h         ; P = 1
        0xEC, 0x0C, 0x00,       //  0010    CALL    PO, x'000C
        0x76,                   //  0013    HALT
        0x76,                   //  0014    HALT
        0x76,                   //  0015    HALT
        0x76      };            //  0016    HALT

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

    if (    (    CPU_REG_PC           != 0x0014 )
         || (    CPU_REG_SP           != 0x001E )
         || ( memory_get_16( 0x001E ) != 0x0B00 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_call_pe_00 failed:   [call  PE, nn]\n" );
        printf( "POST: PC       = 0x%04X\n", CPU_REG_PC );
        printf( "POST: SP       = 0x%04X\n", CPU_REG_SP );
        printf( "POST: (0x001E) = 0x%04X\n", memory_get_16( 0x001E ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  TEST_006:       CALL    P, nn
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
tc_call_p_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x00,                   //  0000    NOP
        0x31, 0x20, 0x00,       //  0001    LD      SP, x'0020
        0x3E, 0x20,             //  0004    LD      A, x'20
        0x87,                   //  0006    ADD     A           ; S = 0
        0xF4, 0x0E, 0x00,       //  0007    CALL    P, x'000E
        0x76,                   //  000A    HALT
        0x76,                   //  000B    HALT
        0x76,                   //  000C    HALT
        0x76,                   //  000D    HALT
        0x87,                   //  000E    ADD     A           ; S = 1
        0xF4, 0x0C, 0x00,       //  000F    CALL    P, x'000C
        0x76,                   //  0012    HALT
        0x76,                   //  0013    HALT
        0x76,                   //  0014    HALT
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

    if (    (    CPU_REG_PC           != 0x0013 )
         || (    CPU_REG_SP           != 0x001E )
         || ( memory_get_16( 0x001E ) != 0x0A00 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_call_p_00 failed:   [call  P, nn]\n" );
        printf( "POST: PC       = 0x%04X\n", CPU_REG_PC );
        printf( "POST: SP       = 0x%04X\n", CPU_REG_SP );
        printf( "POST: (0x001E) = 0x%04X\n", memory_get_16( 0x001E ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  TEST_007:       CALL    M, nn
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
tc_call_m_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x00,                   //  0000    NOP
        0x31, 0x20, 0x00,       //  0001    LD      SP, x'0020
        0x3E, 0x40,             //  0004    LD      A, x'40
        0x87,                   //  0006    ADD     A           ; S = 1
        0xFC, 0x0E, 0x00,       //  0007    CALL    M, x'000E
        0x76,                   //  000A    HALT
        0x76,                   //  000B    HALT
        0x76,                   //  000C    HALT
        0x76,                   //  000D    HALT
        0x87,                   //  000E    ADD     A           ; S = 0
        0xFC, 0x0C, 0x00,       //  000F    CALL    M, x'000C
        0x76,                   //  0012    HALT
        0x76,                   //  0013    HALT
        0x76,                   //  0014    HALT
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

    if (    (    CPU_REG_PC           != 0x0013 )
         || (    CPU_REG_SP           != 0x001E )
         || ( memory_get_16( 0x001E ) != 0x0A00 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_call_m_00 failed:   [call  M, nn]\n" );
        printf( "POST: PC       = 0x%04X\n", CPU_REG_PC );
        printf( "POST: SP       = 0x%04X\n", CPU_REG_SP );
        printf( "POST: (0x001E) = 0x%04X\n", memory_get_16( 0x001E ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  RET
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
tc_ret_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x00,                   //  0000    NOP
        0x31, 0x20, 0x00,       //  0001    LD      SP, x'0020
        0xCD, 0x0B, 0x00,       //  0004    CALL    x'000B
        0x76,                   //  0007    HALT
        0x76,                   //  0008    HALT
        0x76,                   //  0009    HALT
        0x76,                   //  000A    HALT
        0xC9      };            //  000B    RET

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

    if (    (    CPU_REG_PC           != 0x0008 )
         || (    CPU_REG_SP           != 0x0020 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ret_00 failed:     [ret]\n" );
        printf( "POST: PC       = 0x%04X\n", CPU_REG_PC );
        printf( "POST: SP       = 0x%04X\n", CPU_REG_SP );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  RET     NZ
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
tc_ret_nz_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x00,                   //  0000    NOP
        0x31, 0x20, 0x00,       //  0001    LD      SP, x'0020
        0xCD, 0x0C, 0x00,       //  0004    CALL    x'000C
        0xCD, 0x12, 0x00,       //  0007    CALL    x'0012
        0x76,                   //  000A    HALT
        0x76,                   //  000B    HALT
        0x3E, 0x01,             //  000C    LD      A, x'01
        0x87,                   //  000E    ADD     A           ; Z = 0
        0xC0,                   //  000F    RET     NZ
        0x76,                   //  0010    HALT
        0x76,                   //  0011    HALT
        0x97,                   //  0012    SUB     A           ; Z = 1
        0xC0,                   //  0013    RET     NZ
        0x76,                   //  0014    HALT
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

    if (    (    CPU_REG_PC           != 0x0015 )
         || (    CPU_REG_SP           != 0x001E )
         || ( memory_get_16( 0x001E ) != 0x0A00 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ret_nz_00 failed:   [ret  NZ]\n" );
        printf( "POST: PC       = 0x%04X\n", CPU_REG_PC );
        printf( "POST: SP       = 0x%04X\n", CPU_REG_SP );
        printf( "POST: (0x001E) = 0x%04X\n", memory_get_16( 0x001E ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  RET     Z
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
tc_ret_z_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x00,                   //  0000    NOP
        0x31, 0x20, 0x00,       //  0001    LD      SP, x'0020
        0xCD, 0x0C, 0x00,       //  0004    CALL    x'000C
        0xCD, 0x12, 0x00,       //  0007    CALL    x'0012
        0x76,                   //  000A    HALT
        0x76,                   //  000B    HALT
        0x3E, 0x01,             //  000C    LD      A, x'01
        0x97,                   //  000E    SUB     A           ; Z = 1
        0xC8,                   //  000F    RET     Z
        0x76,                   //  0010    HALT
        0x76,                   //  0011    HALT
        0x3C,                   //  0012    INC     A           ; Z = 0
        0xC8,                   //  0013    RET     Z
        0x76,                   //  0014    HALT
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

    if (    (    CPU_REG_PC           != 0x0015 )
         || (    CPU_REG_SP           != 0x001E )
         || ( memory_get_16( 0x001E ) != 0x0A00 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ret_z_00 failed:   [ret  Z]\n" );
        printf( "POST: PC       = 0x%04X\n", CPU_REG_PC );
        printf( "POST: SP       = 0x%04X\n", CPU_REG_SP );
        printf( "POST: (0x001E) = 0x%04X\n", memory_get_16( 0x001E ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  RET     NC
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
tc_ret_nc_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x00,                   //  0000    NOP
        0x31, 0x20, 0x00,       //  0001    LD      SP, x'0020
        0xCD, 0x0C, 0x00,       //  0004    CALL    x'000C
        0xCD, 0x12, 0x00,       //  0007    CALL    x'0012
        0x76,                   //  000A    HALT
        0x76,                   //  000B    HALT
        0x3E, 0x40,             //  000C    LD      A, x'40
        0x87,                   //  000E    ADD     A           ; C = 0
        0xD0,                   //  000F    RET     NC
        0x76,                   //  0010    HALT
        0x76,                   //  0011    HALT
        0x87,                   //  0012    ADD     A           ; C = 1
        0xD0,                   //  0013    RET     NC
        0x76,                   //  0014    HALT
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

    if (    (    CPU_REG_PC           != 0x0015 )
         || (    CPU_REG_SP           != 0x001E )
         || ( memory_get_16( 0x001E ) != 0x0A00 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ret_nc_00 failed:   [ret  NC]\n" );
        printf( "POST: PC       = 0x%04X\n", CPU_REG_PC );
        printf( "POST: SP       = 0x%04X\n", CPU_REG_SP );
        printf( "POST: (0x001E) = 0x%04X\n", memory_get_16( 0x001E ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  RET     C
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
tc_ret_c_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x00,                   //  0000    NOP
        0x31, 0x20, 0x00,       //  0001    LD      SP, x'0020
        0xCD, 0x0C, 0x00,       //  0004    CALL    x'000C
        0xCD, 0x12, 0x00,       //  0007    CALL    x'0012
        0x76,                   //  000A    HALT
        0x76,                   //  000B    HALT
        0x3E, 0x80,             //  000C    LD      A, x'80
        0x87,                   //  000E    ADD     A           ; C = 1
        0xD8,                   //  000F    RET     NC
        0x76,                   //  0010    HALT
        0x76,                   //  0011    HALT
        0x87,                   //  0012    ADD     A           ; C = 0
        0xD8,                   //  0013    RET     NC
        0x76,                   //  0014    HALT
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

    if (    (    CPU_REG_PC           != 0x0015 )
         || (    CPU_REG_SP           != 0x001E )
         || ( memory_get_16( 0x001E ) != 0x0A00 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ret_c_00 failed:   [ret  C]\n" );
        printf( "POST: PC       = 0x%04X\n", CPU_REG_PC );
        printf( "POST: SP       = 0x%04X\n", CPU_REG_SP );
        printf( "POST: (0x001E) = 0x%04X\n", memory_get_16( 0x001E ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  RET     PO
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
tc_ret_po_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x00,                   //  0000    NOP
        0x31, 0x20, 0x00,       //  0001    LD      SP, x'0020
        0xCD, 0x0C, 0x00,       //  0004    CALL    x'000C
        0xCD, 0x13, 0x00,       //  0007    CALL    x'0013
        0x76,                   //  000A    HALT
        0x76,                   //  000B    HALT
        0x3E, 0x00,             //  000C    LD      A, 00h
        0xF6, 0x02,             //  000E    OR      02h         ; P = 1
        0xE0,                   //  0010    RET     NC
        0x76,                   //  0011    HALT
        0x76,                   //  0012    HALT
        0xF6, 0x08,             //  0013    OR      80h         ; P = 0
        0xE0,                   //  0015    RET     NC
        0x76,                   //  0016    HALT
        0x76      };            //  0017    HALT

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

    if (    (    CPU_REG_PC           != 0x0017 )
         || (    CPU_REG_SP           != 0x001E )
         || ( memory_get_16( 0x001E ) != 0x0A00 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ret_po_00 failed:   [ret  PO]\n" );
        printf( "POST: PC       = 0x%04X\n", CPU_REG_PC );
        printf( "POST: SP       = 0x%04X\n", CPU_REG_SP );
        printf( "POST: (0x001E) = 0x%04X\n", memory_get_16( 0x001E ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  RET     PE
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
tc_ret_pe_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x00,                   //  0000    NOP
        0x31, 0x20, 0x00,       //  0001    LD      SP, x'0020
        0xCD, 0x0C, 0x00,       //  0004    CALL    x'000C
        0xCD, 0x13, 0x00,       //  0007    CALL    x'0013
        0x76,                   //  000A    HALT
        0x76,                   //  000B    HALT
        0x3E, 0x00,             //  000C    LD      A, 00h
        0xF6, 0x03,             //  000E    OR      03h         ; P = 0
        0xE8,                   //  0010    RET     PE
        0x76,                   //  0011    HALT
        0x76,                   //  0012    HALT
        0xF6, 0x08,             //  0013    OR      80h         ; P = 1
        0xE8,                   //  0015    RET     PE
        0x76,                   //  0016    HALT
        0x76      };            //  0017    HALT

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

    if (    (    CPU_REG_PC           != 0x0017 )
         || (    CPU_REG_SP           != 0x001E )
         || ( memory_get_16( 0x001E ) != 0x0A00 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ret_pe_00 failed:   [ret  PE]\n" );
        printf( "POST: PC       = 0x%04X\n", CPU_REG_PC );
        printf( "POST: SP       = 0x%04X\n", CPU_REG_SP );
        printf( "POST: (0x001E) = 0x%04X\n", memory_get_16( 0x001E ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  RET     P
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
tc_ret_p_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x00,                   //  0000    NOP
        0x31, 0x20, 0x00,       //  0001    LD      SP, x'0020
        0xCD, 0x0C, 0x00,       //  0004    CALL    x'000C
        0xCD, 0x12, 0x00,       //  0007    CALL    x'0012
        0x76,                   //  000A    HALT
        0x76,                   //  000B    HALT
        0x3E, 0x20,             //  000C    LD      A, x'20
        0x87,                   //  000E    ADD     A           ; S = 0
        0xF0,                   //  000F    RET     NC
        0x76,                   //  0010    HALT
        0x76,                   //  0011    HALT
        0x87,                   //  0012    ADD     A           ; S = 1
        0xF0,                   //  0013    RET     NC
        0x76,                   //  0014    HALT
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

    if (    (    CPU_REG_PC           != 0x0015 )
         || (    CPU_REG_SP           != 0x001E )
         || ( memory_get_16( 0x001E ) != 0x0A00 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ret_p_00 failed:   [ret  P]\n" );
        printf( "POST: PC       = 0x%04X\n", CPU_REG_PC );
        printf( "POST: SP       = 0x%04X\n", CPU_REG_SP );
        printf( "POST: (0x001E) = 0x%04X\n", memory_get_16( 0x001E ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  RET     M
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
tc_ret_m_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0x00,                   //  0000    NOP
        0x31, 0x20, 0x00,       //  0001    LD      SP, x'0020
        0xCD, 0x0C, 0x00,       //  0004    CALL    x'000C
        0xCD, 0x12, 0x00,       //  0007    CALL    x'0012
        0x76,                   //  000A    HALT
        0x76,                   //  000B    HALT
        0x3E, 0x40,             //  000C    LD      A, x'40
        0x87,                   //  000E    ADD     A           ; S = 1
        0xF8,                   //  000F    RET     NC
        0x76,                   //  0010    HALT
        0x76,                   //  0011    HALT
        0x87,                   //  0012    ADD     A           ; S = 0
        0xF8,                   //  0013    RET     NC
        0x76,                   //  0014    HALT
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

    if (    (    CPU_REG_PC           != 0x0015 )
         || (    CPU_REG_SP           != 0x001E )
         || ( memory_get_16( 0x001E ) != 0x0A00 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_ret_m_00 failed:   [ret  M]\n" );
        printf( "POST: PC       = 0x%04X\n", CPU_REG_PC );
        printf( "POST: SP       = 0x%04X\n", CPU_REG_SP );
        printf( "POST: (0x001E) = 0x%04X\n", memory_get_16( 0x001E ) );

        //  Set the return code to FALSE.
        post_rc = false;
    }

    //  DONE!
    return( post_rc );
}

/****************************************************************************/
/**
 *  RET     M
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      The reset address for the CPU is address x'0000 which is also the
 *      RST 0 address.  To get around this an immediate jump to x'0040
 *      which immediately overwrites the op_codes at x'0000 to NOP instructions.
 *
 ****************************************************************************/

static
int
tc_rst_t_00(
    void
    )
{
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                */
    int                         post_rc;

    /**
     *  @param  program             The test program                        */
    uint8_t                     program[ ] = {
        0xC3, 0x40, 0x00,       //  0000    JP      x'0040
        0x3E, 0x00,             //  0003    LD      A, x'00
        0xC9,                   //  0005    RET
        0x76, 0x76,             //  0006    HALT

        0x3C,                   //  0008    INC     A
        0xC9,                   //  0009    RET
        0x76, 0x76, 0x76,       //  000A    HALT
        0x76, 0x76, 0x76,       //  000D    HALT

        0x3C,                   //  0010    INC     A
        0xC9,                   //  0011    RET
        0x76, 0x76, 0x76,       //  0012    HALT
        0x76, 0x76, 0x76,       //  0015    HALT

        0x3C,                   //  0018    INC     A
        0xC9,                   //  0019    RET
        0x76, 0x76, 0x76,       //  001A    HALT
        0x76, 0x76, 0x76,       //  001D    HALT

        0x3C,                   //  0020    INC     A
        0xC9,                   //  0021    RET
        0x76, 0x76, 0x76,       //  0022    HALT
        0x76, 0x76, 0x76,       //  0025    HALT

        0x3C,                   //  0028    INC     A
        0xC9,                   //  0029    RET
        0x76, 0x76, 0x76,       //  002A    HALT
        0x76, 0x76, 0x76,       //  002D    HALT

        0x3C,                   //  0030    INC     A
        0xC9,                   //  0031    RET
        0x76, 0x76, 0x76,       //  0032    HALT
        0x76, 0x76, 0x76,       //  0035    HALT

        0x3C,                   //  0038    INC     A
        0xC9,                   //  0039    RET
        0x76, 0x76, 0x76,       //  003A    HALT
        0x76, 0x76, 0x76,       //  003D    HALT

        0x3E, 0x00,             //  0040    LD      A, x'00
        0x32, 0x00, 0x00,       //  0042    LD      (x'0000), A
        0x32, 0x01, 0x00,       //  0045    LD      (x'0000), A
        0x32, 0x02, 0x00,       //  0048    LD      (x'0000), A

        0x31, 0x80, 0x00,       //  004B    LD      SP, x'0080
        0xC7,                   //  004E    RST     0
        0xCF,                   //  004F    RST     1
        0xD7,                   //  0050    RST     2
        0xDF,                   //  0051    RST     3
        0xE7,                   //  0052    RST     4
        0xEF,                   //  0053    RST     5
        0xF7,                   //  0054    RST     6
        0xFF,                   //  0055    RST     7

        0x76,                   //  0056    HALT
        0x76,                   //  0057    HALT
        0x76      };            //  0058    HALT

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

    if (    (    CPU_REG_PC           != 0x0057 )
         || (    CPU_REG_SP           != 0x0080 )
         || (    GET_A( )             !=   0x07 ) )
    {
        //  NO:     Write an error message
        printf( "POST: tc_rst_t_00 failed:   [rst  t]\n" );
        printf( "POST: PC       = 0x%04X\n", CPU_REG_PC );
        printf( "POST: SP       = 0x%04X\n", CPU_REG_SP );
        printf( "POST: A        = 0x%02X\n", GET_A( ) );

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
call_post(
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
        if ( post_rc == true )      post_rc = tc_call_00( );        //  CALL nn

        if ( post_rc == true )      post_rc = tc_call_nz_00( );     //  CALL NZ, nn
        if ( post_rc == true )      post_rc = tc_call_z_00( );      //  CALL Z, nn
        if ( post_rc == true )      post_rc = tc_call_nc_00( );     //  CALL NC, nn
        if ( post_rc == true )      post_rc = tc_call_c_00( );      //  CALL C, nn
        if ( post_rc == true )      post_rc = tc_call_po_00( );     //  CALL PO, nn
        if ( post_rc == true )      post_rc = tc_call_pe_00( );     //  CALL PE, nn
        if ( post_rc == true )      post_rc = tc_call_p_00( );      //  CALL P, nn
        if ( post_rc == true )      post_rc = tc_call_m_00( );      //  CALL M, nn

        if ( post_rc == true )      post_rc = tc_ret_00( );         //  RET

        if ( post_rc == true )      post_rc = tc_ret_nz_00( );      //  RET  NZ
        if ( post_rc == true )      post_rc = tc_ret_z_00( );       //  RET  Z
        if ( post_rc == true )      post_rc = tc_ret_nc_00( );      //  RET  NC
        if ( post_rc == true )      post_rc = tc_ret_c_00( );       //  RET  C
        if ( post_rc == true )      post_rc = tc_ret_po_00( );      //  RET  PO
        if ( post_rc == true )      post_rc = tc_ret_pe_00( );      //  RET  PE
        if ( post_rc == true )      post_rc = tc_ret_p_00( );       //  RET  P
        if ( post_rc == true )      post_rc = tc_ret_m_00( );       //  RET  M

        if ( post_rc == true )      post_rc = tc_rst_t_00( );       //  RET  T

        //  Z80 ONLY instructions
        if( CPU == CPU_Z80 )
        {
        }

        //  Was the test suite successfully complete :
        if( post_rc == true )
        {
            //  YES:    Write a completion message
            printf( "POST: CALL    complete %s mode.\n",
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