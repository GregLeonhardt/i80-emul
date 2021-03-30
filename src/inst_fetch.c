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
#include <time.h>               //  Time stuff
#include <string.h>             //  Functions for managing strings
                                //*******************************************


/****************************************************************************
 * Application
 ****************************************************************************/

                                //*******************************************
#include "global.h"             //  Global definitions
#include "memory.h"             //  Memory management and access
#include "registers.h"          //  All things CPU registers.
#include "op_code.h"            //  OP-Code instruction maps
#include "disassemble.h"        //  For debug
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
/**
 *  @param  PC              Program Counter (PC)                            */
uint16_t                    PC;
//---------------------------------------------------------------------------

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************/
/**
 *  Fetch a new instruction from main memory
 *
 *  @param
 *
 *  @return op_code             The opcode pointed to by the program counter (PC).
 *
 *  @note
 *
 ****************************************************************************/

static
uint8_t
instruction_fetch(
    )
{
    /**
     *  @param  op_code             Contents of main memory (PC).           */
    uint8_t                     op_code;
    /**
     *  @param  r_7                 Refresh register bit 7                  */
    uint8_t                     r_7;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Function code
     ************************************************************************/

    //  Fetch a new CPU instruction operation code
    op_code = memory_get_8( CPU_REG_PC++ );

    //  Increment the refresh register
    r_7 = CPU_REG_R & 0x80;
    CPU_REG_R = ( ( CPU_REG_R + 1 ) & 0x7F ) | r_7;

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( op_code );
}

/****************************************************************************/
/**
 *  RESET.
 *  Reset (input, active Low). RESET initializes the CPU as follows:
 *  it resets the interrupt enable flip-flop, clears the Program Counter
 *  and registers I and R, and sets the interrupt status to Mode 0. During
 *  reset time, the address and data bus enter a high-impedance state, and
 *  all control output signals enter an inactive state. RESET must be active
 *  for a minimum of three full clock cycles before a reset operation
 *  is complete.
 *
 *  @param
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

static
void
cpu_reset(
    )
{
    /**
     *  @param  parm_name           Parm description                    */

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Clear CPU registers
    //  Clear everything from all CPU registers
    CPU_REG_AF = 0;
    CPU_REG_BC = 0;
    CPU_REG_DE = 0;
    CPU_REG_HL = 0;
    CPU_REG_PC = 0;
    CPU_REG_I  = 0;
    CPU_REG_R  = 0;

    //  Not needed but makes testing easier when all flags start in a
    //  known state.
    PUT_F( 0 );

    //  @ToDo   Reset the interrupt enable flag

    //  @ToDo   Set interrupt status to 'Mode-0'

    /************************************************************************
     *  Function code
     ************************************************************************/


    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
}

/****************************************************************************/
/**
 *  Z80-EIS-CB
 *
 *  @param  op_code             Current instruction code
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
inst_fetch_CB(
    uint8_t                     op_code
    )
{
    /**
     *  @param  op_code             Current instruction code                */
    uint8_t                     CB_op_code;

    //  Set Extended Instruction Set = CB
    EIS = EIS_CB;

    //  Read the next instruction from main memory
    CB_op_code = memory_get_8( CPU_REG_PC++ );

    (*op_code_CB_table[ CB_op_code ])( CB_op_code);
}

/****************************************************************************/
/**
 *  Z80-EIS-DD
 *
 *  @param  op_code             Current instruction code
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
inst_fetch_DD(
    uint8_t                     op_code
    )
{
    /**
     *  @param  op_code             Current instruction code                */
    uint8_t                     DD_op_code;

    //  Set Extended Instruction Set = DD
    EIS = EIS_DD;

    //  Read the next instruction from main memory
    DD_op_code = memory_get_8( CPU_REG_PC++ );

    (*op_code_DD_table[ DD_op_code ])( DD_op_code);
}

/****************************************************************************/
/**
 *  Z80-EIS-DDCB
 *
 *  @param  op_code             Current instruction code
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
inst_fetch_DDCB(
    uint8_t                     op_code
    )
{
    /**
     *  @param  op_code             Current instruction code                */
    uint8_t                     DDCB_op_code;

    //  Set Extended Instruction Set = DDCB
    EIS = EIS_DDCB;

    //  Read the next instruction from main memory
    DDCB_op_code = memory_get_8( CPU_REG_PC++ );

    (*op_code_DDCB_table[ DDCB_op_code ])( DDCB_op_code);
}

/****************************************************************************/
/**
 *  Z80-EIS-ED
 *
 *  @param  op_code             Current instruction code
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
inst_fetch_ED(
    uint8_t                     op_code
    )
{
    /**
     *  @param  op_code             Current instruction code                */
    uint8_t                     ED_op_code;

    //  Set Extended Instruction Set = ED
    EIS = EIS_ED;

    //  Read the next instruction from main memory
    ED_op_code = memory_get_8( CPU_REG_PC++ );

    (*op_code_ED_table[ ED_op_code ])( ED_op_code);

#if DEBUG_MODE
        disassemble( PC, ED_op_code );
#endif
}

/****************************************************************************/
/**
 *  Z80-EIS-FD
 *
 *  @param  op_code             Current instruction code
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
inst_fetch_FD(
    uint8_t                     op_code
    )
{
    /**
     *  @param  op_code             Current instruction code                */
    uint8_t                     FD_op_code;

    //  Set Extended Instruction Set = FD
    EIS = EIS_FD;

    //  Read the next instruction from main memory
    FD_op_code = memory_get_8( CPU_REG_PC++ );

    (*op_code_FD_table[ FD_op_code ])( FD_op_code);
}

/****************************************************************************/
/**
 *  Z80-EIS-FDCB
 *
 *  @param  op_code             Current instruction code
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
inst_fetch_FDCB(
    uint8_t                     op_code
    )
{
    /**
     *  @param  op_code             Current instruction code                */
    uint8_t                     FDCB_op_code;

    //  Set Extended Instruction Set = FDCB
    EIS = EIS_FDCB;

    //  Read the next instruction from main memory
    FDCB_op_code = memory_get_8( CPU_REG_PC++ );

    (*op_code_FDCB_table[ FDCB_op_code ])( FDCB_op_code);
}

/****************************************************************************
 * MAIN
 ****************************************************************************/


/****************************************************************************/
/**
 *  Run the program in memory starting at address x'0000.
 *
 *  @param
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
inst_fetch(
    void
    )
{
    /**
     *  @param  op_code         Current instruction code                    */
    uint8_t                     op_code;
    /**
     *  @param  refresh         Refresh count tracker                       */
    uint8_t                     refresh;
    /**
     *  @param  rb7             Save refresh register bit 7                 */
    uint8_t                     rb7;

    //  Reset the CPU for a normalized start
    cpu_reset( );

    //  Initialize the refresh tracker
    refresh = 0;

    /************************************************************************
     *  Main instruction fetch loop
     ************************************************************************/

    // Start executing instructions
    while( 1 )
    {
        //  Set the instruction set to 'BASIC'
        EIS = EIS_BASE;

        //  Save the current Program Counter
        PC = CPU_REG_PC;

        //  Read the next instruction from main memory
        op_code = memory_get_8( CPU_REG_PC++ );

        //  Are we running in Intel 8080 mode ?
        if ( CPU == CPU_I80 )
        {
            //  YES:    Use the 8080 instruction set
            (*op_code_i80_table[ op_code ])( op_code);
        }
        else
        {
            //  NO:     Use the Zilog Z80 instruction set
            (*op_code_z80_table[ op_code ])( op_code);
        }

        //  Was the op-code execution successful ?
        if ( operation_rc.states == 0 )
        {
            //  Terminate
            break;
        }

        //  Update the refresh register
        refresh += operation_rc.states;
        rb7 = ( CPU_REG_R & 0x80 );
        CPU_REG_R = ( ( CPU_REG_R + ( refresh / 4 ) ) & 0x7F );
        CPU_REG_R |= rb7;
        refresh %= 4;

#if DEBUG_MODE
        if( EIS == EIS_BASE )
            disassemble( PC, op_code );
#endif

#if 0   //  This implementation is just wrong.  I need something that will
        //  emulate the real world instruction time not the emulation time
        //  plus the real world instruction time.
{
#define STEP_STATE_FACTOR       250
        /**
         *  @param  remaing_steps                                            */
        static
        int                         remaing_steps;
        /**
         *  @param  tim                                                      */
        struct timespec             tim;
        /**
         *  @param  tim                                                      */
        struct timespec             tim2;

        remaing_steps += operation_rc.states;

        tim.tv_sec = 0;
        tim.tv_nsec = ( remaing_steps / STEP_STATE_FACTOR );

        if( tim.tv_nsec >= 1 )
        {
            //  Subtract the used steps from the total
            remaing_steps -= ( tim.tv_nsec * STEP_STATE_FACTOR );

            //  Continue until the time has expired
            nanosleep( &tim , &tim2 );
        }
}
#endif
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

}
/****************************************************************************/