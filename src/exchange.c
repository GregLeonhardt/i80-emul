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
#include "exchange.h"           //  EX   *,*
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
/**                     Page        Op-Code
 *  EX DE, HL            124        11101011
 *  XCHG                 4-5
 *
 *  The 2-byte contents of register pairs DE and HL are exchanged.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
ex_dehl_i80(
    uint8_t                     op_code
    )
{
    /**
     *  @param  tmp                 Temporary data buffer                   */
    uint16_t                    tmp;

    //  EX  DE, HL
    tmp = CPU_REG_HL;
    CPU_REG_HL = CPU_REG_DE;
    CPU_REG_DE = tmp;

    //  Set the number of states for this instruction
    operation_rc.states =   4;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  EX (SP), HL          127        11100011
 *  XCHG                4-14
 *
 *  The low-order byte contained in register pair HL is exchanged with the
 *  contents of the memory address specified by the contents of register pair
 *  SP (Stack Pointer), and the high-order byte of HL is exchanged with the
 *  next highest memory address (SP+1).
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      If the HL register pair contains 7012h , the SP register pair contains
 *      8856h , the memory location 8856h contains byte 11h , and memory
 *      location 8857h contains byte 22h , then the instruction EX (SP), HL
 *      results in the HL register pair containing number 2211h, memory
 *      location 8856h containing byte 12h , memory location 8857h containing
 *      byte 70h and Stack Pointer containing 8856h .
 *
 ****************************************************************************/

void
ex_sphl_i80(
    uint8_t                     op_code
    )
{
    /**
     *  @param  tmp                 Temporary data buffer                   */
    uint16_t                    tmp;

    //  EX  (SP), HL
    tmp = CPU_REG_HL;

    PUT_L( memory_get_8( CPU_REG_SP     ) );
    PUT_H( memory_get_8( CPU_REG_SP + 1 ) );

    memory_put_8( ( CPU_REG_SP     ), ( tmp & 0x00FF )      );
    memory_put_8( ( CPU_REG_SP + 1 ), ( tmp & 0xFF00 ) >> 8 );

    //  Set the number of states for this instruction
    operation_rc.states =  19;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  EX AF, AF'           125       00001000
 *
 *  The 2-byte contents of the register pairs AF and AF' are exchanged.
 *  Register pair AF consists of registers A′ and F′.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      @ToDo:  POST Test is needed.
 *
 ****************************************************************************/

void
ex_afaf_z80(
    uint8_t                     op_code
    )
{
    /**
     *  @param  tmp                 Temporary register holding buffers      */
    uint16_t                    tmp_AF;

    //  Temporary register holding place
    tmp_AF = CPU_REG_AF;

    //  Swap AF with AF'
    CPU_REG_AF = CPU_REG_AF_;
    CPU_REG_AF_ = tmp_AF;

    //  Set the number of states for this instruction
    operation_rc.states =  4;
}

/****************************************************************************/
/**                     Page        Op-Code
 *  EXX                  126       11011001
 *
 *  Each 2-byte value in register pairs BC, DE, and HL is exchanged with the
 *  2-byte value in BC', DE', and HL', respectively.
 *
 *  @parm   op_code             The operation code of the current instruction.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      @ToDo:  POST Test is needed.
 *
 ****************************************************************************/

void
ex_exx_z80(
    uint8_t                     op_code
    )
{
    /**
     *  @param  tmp                 Temporary register holding buffers      */
    uint16_t                    tmp_BC;
    uint16_t                    tmp_DE;
    uint16_t                    tmp_HL;

    //  Temporary register holding place
    tmp_BC = CPU_REG_BC;
    tmp_DE = CPU_REG_DE;
    tmp_HL = CPU_REG_HL;

    //  Swap AF with AF'
    CPU_REG_BC = CPU_REG_BC_;
    CPU_REG_BC_ = tmp_BC;
    CPU_REG_DE = CPU_REG_DE_;
    CPU_REG_DE_ = tmp_DE;
    CPU_REG_HL = CPU_REG_HL_;
    CPU_REG_HL_ = tmp_HL;

    //  Set the number of states for this instruction
    operation_rc.states =  4;
}
/****************************************************************************/