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
#include "control.h"            //  Control (NOP, HLT, etc.) instrucions.
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


/****************************************************************************
 * MAIN
 ****************************************************************************/

/****************************************************************************/
/**
/**                     Page        Op-Code
 *  NOP                  180        00000000
 *  NOP                 4-14
 *
 *  The CPU performs no operation during this machine cycle.
 *
 *  @param  op_code             Operation Code.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
control_nop_i80(
    uint8_t                     op_code
    )
{
    //  Set the number of states for this instruction
    operation_rc.states =   4;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  HLT                  181        00110110
 *  HLT                 4-14
 *
 *  The HALT instruction suspends CPU operation until a subsequent interrupt or
 *  reset is received. While in the HALT state, the processor executes NOPs to
 *  maintain memory refresh logic.
 *
 *  @param  op_code             Operation Code.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      This is ONLY a placeholder instruction for the foreseeable future.
 *      We are running in a simulator and there isn't any hardware or anything
 *      else that could resume processing.  Effectively this would be a wait
 *      forever loop.
 *
 ****************************************************************************/

void
control_hlt_i80(
    uint8_t                     op_code
    )
{
    //  Set the number of states for this instruction
    operation_rc.states =   4;

    //  @note   Setting the states value to zero '0' will terminate.
    operation_rc.states =   0;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  DI                   182        11110011
 *  DI                  4-14
 *
 *  DI disables the maskable interrupt by resetting the interrupt enable
 *  flip-flops (IFF1 and IFF2).
 *
 *  @param  op_code             Operation Code.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      This is ONLY a placeholder instruction for the foreseeable future.
 *      We are running in a simulator and there isn't any hardware and
 *      thus no interrupts.
 *
 ****************************************************************************/

void
control_di_i80(
    uint8_t                     op_code
    )
{
    //  Set the number of states for this instruction
    operation_rc.states =   4;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  EI                   183        11111011
 *  EI                  4-14
 *
 *  The enable interrupt instruction sets both interrupt enable flip flops
 *  (IFFI and IFF2) to a logic 1, allowing recognition of any maskable interrupt.
 *
 *  @param  op_code             Operation Code.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      This is ONLY a placeholder instruction for the foreseeable future.
 *      We are running in a simulator and there isn't any hardware and
 *      thus no interrupts.
 *
 ****************************************************************************/

void
control_ei_api(
    uint8_t                     op_code
    )
{
    //  Set the number of states for this instruction
    operation_rc.states =   4;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  IM   m               184     ED 010mm110
 *
 *  The IM 0 instruction sets Interrupt Mode 0. In this mode, the interrupting
 *  device can insert any instruction on the data bus for execution by the CPU.
 *  The first byte of a multi-byte instruction is read during the interrupt
 *  acknowledge cycle. Subsequent bytes are read in by a normal memory read
 *  sequence.
 *
 *  The IM 1 instruction sets Interrupt Mode 1. In this mode, the processor
 *  responds to an interrupt by executing a restart at address 0038h.
 *
 *  The IM 2 instruction sets the vectored Interrupt Mode 2. This mode allows
 *  an indirect call to any memory location by an 8-bit vector supplied from
 *  the peripheral device. This vector then becomes the least-significant eight
 *  bits of the indirect pointer, while the I Register in the CPU provides the
 *  most-significant eight bits. This address points to an address in a vector
 *  table that is the starting address for the interrupt service routine.
 *
 *  @param  op_code             Operation Code.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      This is ONLY a placeholder instruction for the foreseeable future.
 *      We are running in a simulator and there isn't any hardware and
 *      thus no interrupts.
 *
 ****************************************************************************/

void
control_im_ED(
    uint8_t                     op_code
    )
{
    //  Mode detection
    switch( ( op_code >> 3 ) & 0x03 )
    {
        case    0:              // Mode 0
            break;
        case    1:              // Mode ?
            break;
        case    2:              // Mode 1
            break;
        case    3:              // Mode 2
            break;
    }

    //  Set the number of states for this instruction
    operation_rc.states =   9;
}
/****************************************************************************/