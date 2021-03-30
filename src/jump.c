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


/****************************************************************************
 * MAIN
 ****************************************************************************/

/****************************************************************************/
/**
 *                      Page        Op-Code
 *  JP  nn               262        11000011  addr_l addr_h
 *  JMP addr            4-11
 *
 *  Operand nn is loaded to register pair Program Counter (PC). The next
 *  instruction is fetched from the location designated by the new contents
 *  of the PC.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
jump_jpnn_i80(
    uint8_t                     op_code
    )
{
    //  JP  nn
    CPU_REG_PC = memory_get_16_pc_p(  );

    //  Set the number of states for this instruction
    operation_rc.states   =  10;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  JP   cc, nn          263        11ccc010  addr_l addr_h
 *  Jccc addr           4-11
 *
 *  If condition cc is true, the instruction loads operand nn to register pair
 *  Program Counter (PC), and the program continues with the instruction
 *  beginning at address nn. If condition cc is false, the Program Counter is
 *  incremented as usual, and the program continues with the next sequential
 *  instruction. Condition cc is programmed as one of eight statuses that
 *  correspond to condition bits in the Flag Register (Register F).
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
jump_jpccnn_i80(
    uint8_t                     op_code
    )
{
    //  Is the condition TRUE ?
    if ( is_ccc( op_code ) == true )
    {
        //  YES:    JP  nn
        CPU_REG_PC = memory_get_16_pc_p(  );
    }
    else
    {
        //  NO:     Step over the jump address and continue
        CPU_REG_PC += 2;
    }

    //  Set the number of states for this instruction
    operation_rc.states   =  10;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  JP   (HL)            275        11101001
 *  PCHL                4-12
 *
 *  The Program Counter (PC) is loaded with the contents of the HL register
 *  pair. The next instruction is fetched from the location designated by the
 *  new contents of the PC.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
jump_jphl_i80(
    uint8_t                     op_code
    )
{
    //  Copy the contents of HL into PC
    CPU_REG_PC = CPU_REG_HL;

    //  Set the number of states for this instruction
    operation_rc.states   =   4;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  DJNZ  e              278        00010000
 *
 *  This instruction is similar to the conditional jump instructions except
 *  that a register value is used to determine branching. Register B is
 *  decremented, and if a nonzero value remains, the value of displacement e
 *  is added to the Program Counter (PC). The next instruction is fetched from
 *  the location designated by the new contents of the PC. The jump is measured
 *  from the address of the instruction op code and contains a range of –126 to
 *  +129 bytes. The assembler automatically adjusts for the twice incremented
 *  PC.
 *  If the result of decrementing leaves B with a zero value, the next
 *  instruction executed is taken from the location following this instruction.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
jump_djnz_z80(
    uint8_t                     op_code
    )
{
    /**
     *  @param  displacement    Jump offset                                 */
    uint16_t                    displacement;

    //  Copy the contents of HL into PC
    PUT_B( ( GET_B( ) - 1 ) );

    //  Get the jump displacement
    displacement = memory_get_8( CPU_REG_PC++ );
    if( displacement & 0x80 ) displacement |= 0xFF00;

    //  Is REG-B NOT equal to zero ?
    if( GET_B( ) != 0 )
    {
        //  YES:    Compute the final offset
        CPU_REG_PC += (uint16_t)displacement;

        //  Set the number of states for this instruction
        operation_rc.states   =  13;
    }
    else
    {
        //  NO:     Set the number of states for this instruction
        operation_rc.states   =   8;
    }
}

/****************************************************************************/
/**                     Page        Op-Code
 *  JR    e              278        00010000
 *
 *  This instruction provides for unconditional branching to other segments of
 *  a program. The value of displacement e is added to the Program Counter (PC)
 *  and the next instruction is fetched from the location designated by the new
 *  contents of the PC. This jump is measured from the address of the
 *  instruction op code and contains a range of –126 to +129 bytes. The
 *  assembler automatically adjusts for the twice incremented PC.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
jump_jr_z80(
    uint8_t                     op_code
    )
{
    /**
     *  @param  displacement    Jump offset                                 */
    uint16_t                    displacement;

    //  Get the jump displacement
    displacement = memory_get_8( CPU_REG_PC++ );
    if( displacement & 0x80 ) displacement |= 0xFF00;

    //  YES:    Compute the final offset
    CPU_REG_PC += displacement;

    //  Set the number of states for this instruction
    operation_rc.states   =  12;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  JR    cc, e          278        001cc000
 *
 *  This instruction provides for conditional branching to other segments of a
 *  program depending on the results of a test on the Flag Condition. If the
 *  flag condition is TRUE, the value of displacement e is added to the Program
 *  Counter (PC) and the next instruction is fetched from the location
 *  designated by the new contents of the PC. The jump is measured from the
 *  address of the instruction op code and contains a range of –126 to +129
 *  bytes. The assembler automatically adjusts for the twice incremented PC.
 *  If the flag condition is false, the next instruction executed is taken from
 *  the location following this instruction.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
jump_jrcc_z80(
    uint8_t                     op_code
    )
{
    /**
     *  @param  displacement    Jump offset                                 */
    uint16_t                    displacement;

    //  Get the jump displacement
    displacement = memory_get_8( CPU_REG_PC++ );
    if( displacement & 0x80 ) displacement |= 0xFF00;

    //  Is the condition TRUE ?
    if ( is_cc( op_code ) == true )
    {
        //  YES:    Compute the final offset
        CPU_REG_PC += displacement;

        //  Set the number of states for this instruction
        operation_rc.states   =  12;
    }
    else
    {
        //  Set the number of states for this instruction
        operation_rc.states   =   7;
    }
}
/****************************************************************************/