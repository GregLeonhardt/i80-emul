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

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * MAIN
 ****************************************************************************/

/****************************************************************************/
/**                     Page        Op-Code
 *  CALL nn              281        11001011  addr_l addr_h
 *  CALL addr           4-11
 *
 *  The current contents of the Program Counter (PC) are pushed onto the top of
 *  the external memory stack. The operands nn are then loaded to the PC to
 *  point to the address in memory at which the first op code of a subroutine
 *  is to be fetched. At the end of the subroutine, a RETurn instruction can be
 *  used to return to the original program flow by popping the top of the stack
 *  back to the PC. The push is accomplished by first decrementing the current
 *  contents of the Stack Pointer (register pair SP), loading the high-order
 *  byte of the PC contents to the memory address now pointed to by the SP; then
 *  decrementing SP again, and loading the low-order byte of the PC contents to
 *  the top of stack.
 *  Because this process is a 3-byte instruction, the Program Counter was
 *  incremented by three before the push is executed.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
call_nn_i80(
    uint8_t                     op_code
    )
{
    /**
     *  @param  address             The eventual jump address               */
    uint16_t                    address;

    //  Get the jump address
    address = memory_get_16_pc_p(  );

    //  Push the current PC to the stack
    push( CPU_REG_PC );

    //  Jump to the address
    CPU_REG_PC = address;

    //  Set the number of states for this instruction
    operation_rc.states   =  17;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  CALL cc, nn          283        11ccc100  addr_l addr_h
 *  Cccc addr           4-12
 *
 *  If condition cc is true, this instruction pushes the current contents of the
 *  Program Counter (PC) onto the top of the external memory stack, then loads
 *  the operands nn to PC to point to the address in memory at which the first
 *  op code of a subroutine is to be fetched. At the end of the subroutine, a
 *  RETurn instruction can be used to return to the original program flow by
 *  popping the top of the stack back to PC. If condition cc is false, the
 *  Program Counter is incremented as usual, and the program continues with the
 *  next sequential instruction. The stack push is accomplished by first
 *  decrementing the current contents of the Stack Pointer (SP), loading the
 *  high-order byte of the PC contents to the memory address now pointed to by
 *  SP; then decrementing SP again, and loading the low-order byte of the PC
 *  contents to the top of the stack.
 *  Because this process is a 3-byte instruction, the Program Counter was
 *  incremented by three before the push is executed.
 *  Condition cc is programmed as one of eight statuses that corresponds to
 *  condition bits in the Flag Register (Register F). These eight statuses are
 *  defined in the following table, which also specifies the corresponding cc
 *  bit fields in the assembled object code.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
call_ccnn_i80(
    uint8_t                     op_code
    )
{
    /**
     *  @param  address             The eventual jump address               */
    uint16_t                    address;

    //  Get the jump address
    address = memory_get_16_pc_p(  );

    //  Is the condition TRUE ?
    if ( is_ccc( op_code ) == true )
    {
        //  YES:    Push the current PC to the stack
        push( CPU_REG_PC );

        //  Jump to the address
        CPU_REG_PC = address;

        //  Set the number of states for this instruction
        operation_rc.states   =  17;
    }
    else
    {
        //  NO:     The the program continues with the next instruction

        //  Set the number of states for this instruction
        operation_rc.states   =  10;
    }
}

/****************************************************************************/
/**                     Page        Op-Code
 *  RET                  285        11001001
 *  RET                 4-12
 *
 *  The byte at the memory location specified by the contents of the Stack
 *  Pointer (SP) Register pair is moved to the low-order eight bits of the
 *  Program Counter (PC). The SP is now incremented and the byte at the memory
 *  location specified by the new contents of this instruction is fetched from
 *  the memory location specified by the PC. This instruction is normally used
 *  to return to the main line program at the completion of a routine entered
 *  by a CALL instruction.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
ret_i80(
    uint8_t                     op_code
    )
{
    //  Jump to the address
    CPU_REG_PC = pop( );

    //  Set the number of states for this instruction
    operation_rc.states   =  10;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  RET cc               286        11ccc000
 *  Rccc                4-12
 *
 *  If condition cc is true, the byte at the memory location specified by the
 *  contents of the Stack Pointer (SP) Register pair is moved to the low-order
 *  eight bits of the Program Counter (PC). The SP is incremented and the byte
 *  at the memory location specified by the new contents of the SP are moved to
 *  the high-order eight bits of the PC. The SP is incremented again. The next
 *  op code following this instruction is fetched from the memory location
 *  specified by the PC. This instruction is normally used to return to the main
 *  line program at the completion of a routine entered by a CALL instruction.
 *  If condition cc is false, the PC is simply incremented as usual, and the
 *  program continues with the next sequential instruction. Condition cc is
 *  programmed as one of eight status that correspond to condition bits in the
 *  Flag Register (Register F).
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
ret_cc_i80(
    uint8_t                     op_code
    )
{
    /**
     *  @param  address             The eventual jump address               */
    uint16_t                    address;

    //  Is the condition TRUE ?
    if ( is_ccc( op_code ) == true )
    {
        //  YES:    Pop the new PC address from the stack
        CPU_REG_PC = pop( );

        //  Set the number of states for this instruction
        operation_rc.states   =  11;
    }
    else
    {
        //  NO:     The the program continues with the next instruction

        //  Set the number of states for this instruction
        operation_rc.states   =   5;
    }
}

/****************************************************************************/
/**                     Page        Op-Code
 *  RST  t               292        11ttt111
 *  RST  n              4-12
 *
 *  The current Program Counter (PC) contents are pushed onto the external
 *  memory stack, and the Page 0 memory location assigned by operand p is
 *  loaded to the PC. Program execution then begins with the op code in the
 *  address now pointed to by PC. The push is performed by first decrementing
 *  the contents of the Stack Pointer (SP), loading the high-order byte of PC
 *  to the memory address now pointed to by SP, decrementing SP again, and
 *  loading the low-order byte of PC to the address now pointed to by SP. The
 *  Restart instruction allows for a jump to one of eight addresses indicated
 *  in the following table. The operand p is assembled to the object code using
 *  the corresponding T state. Because all addresses are stored in Page 0 of
 *  memory, the high-order byte of PC is loaded with 00h . The number selected
 *  from the p column of the table is loaded to the low-order byte of PC.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *           p       t
 *          00h     000
 *          08h     001
 *          10h     010
 *          18h     011
 *          20h     100
 *          28h     101
 *          30h     110
 *          38h     111
 *
 ****************************************************************************/

void
rst_t_i80(
    uint8_t                     op_code
    )
{
    /**
     *  @param  address             The eventual jump address               */
    uint16_t                    address;

    //  Push the current PC to the stack
    push( CPU_REG_PC );

    //  YES:    Pop the new PC address from the stack
    CPU_REG_PC = ( op_code & 0x38 );

    //  Set the number of states for this instruction
    operation_rc.states   =  11;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  RETI                 288        01001101
 *
 *  This instruction is used at the end of a maskable interrupt service
 *  routine to:
 *      •   Restore the contents of the Program Counter (analogous to the RET
 *          instruction)
 *      •   Signal an I/O device that the interrupt routine is completed. The
 *          RETI instruction also facilitates the nesting of interrupts,
 *          allowing higher priority devices to temporarily suspend service of
 *          lower priority service routines. However, this instruction does not
 *          enable interrupts that were disabled when the interrupt routine was
 *          entered. Before doing the RETI instruction, the enable interrupt
 *          instruction (EI) should be executed to allow recognition of
 *          interrupts after completion of the current service routine.
 *
 *  @parm   op_code             The operation code of the current instruction.
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
reti_ED(
    uint8_t                     op_code
    )
{
    //  Set the number of states for this instruction
    operation_rc.states   =  14;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  RETN                 290        01000101
 *
 *  This instruction is used at the end of a nonmaskable interrupts service
 *  routine to restore the contents of the Program Counter (analogous to the
 *  RET instruction). The state of IFF2 is copied back to IFF1 so that maskable
 *  interrupts are enabled immediately following the RETN if they were enabled
 *  before the nonmaskable interrupt.
 *
 *  @parm   op_code             The operation code of the current instruction.
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
retn_ED(
    uint8_t                     op_code
    )
{
    //  Set the number of states for this instruction
    operation_rc.states   =  14;
}
/****************************************************************************/