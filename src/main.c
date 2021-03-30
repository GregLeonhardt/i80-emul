/*******************************  COPYRIGHT  ********************************/
/*
 *  Author? "Gregory N. Leonhardt"
 *  License? "CC BY-NC 2.0"
 *           "https://creativecommons.org/licenses/by-nc/2.0/"
 *
 ****************************************************************************/

/******************************** JAVADOC ***********************************/
/**
 *  Z80 CPU emulator.
 *
 *  @note
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
#include <signal.h>             //  Signal processing
                                //*******************************************

/****************************************************************************
 * Application Functions
 ****************************************************************************/

                                //*******************************************
#include "global.h"             //  Global definitions
#include "memory.h"             //  Memory management and access
#include "registers.h"          //  All things CPU registers.
#include "op_code.h"            //  OP-Code instruction maps
#include "control.h"            //  Control (NOP, HLT, etc.) instrucions.
#include "load.h"               //  LD   *,*
#include "exchange.h"           //  EX   *,*
#include "math.h"               //  8 bit instrucions.
#include "logic.h"              //  Logic (AND, OR, XOR, CMP) instrucions.
#include "math_16.h"            //  16 bit Arithmatic instrucions.
#include "shift.h"              //  Shift and Rotate instructions
#include "jump.h"               //  Jump instructions
#include "call.h"               //  Call instructions
#include "io.h"                 //  Input & Output instructions
#include "bios.h"               //  CP/M BIOS
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
struct  inst_timing_t
{
    /**
     *  @param  M_Cycles            ...                                     */
    uint8_t                     M_Cycles;
    /**
     *  @param  T_States            ...                                     */
    uint8_t                     T_States;
    /**
     *  @param  MHz_E_T             ...                                     */
    float                       MHz_E_T;
};
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
 *  Signal handler.
 *
 *  @param  signo               The signal number that is being handled.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      Causes a memory dump to stdout.
 *
 ****************************************************************************/

void
sig_handler(
    int                         signo
    )
{
    if ( signo == SIGINT )
    {
#if DEBUG_MODE

        //  Notice of termination
        printf( "\n\nReceived SIGINT\n\n" );

        //  Memory dump (Page 0)
        printf( "Page-0\n" );
        memory_dump( 0x0000, 0x0100 );

        //  Memory dump (CCP)
        printf( "\nCCP:\n" );
        memory_dump( 0xDC00, 0x0800 );

        //  Memory dump (BDOS)
        printf( "\nBDOS:\n" );
        memory_dump( 0xE400, 0x0E00 );

        //  Memory dump (BIOS)
        printf( "\nBIOS:\n" );
        memory_dump( 0xF200, 0x0E00 );

        //  The last line feed and flush
        printf( "\n\n" );
        fflush( stdout );
#endif


        //  We are done
        exit( 0 );
    }
}

/****************************************************************************/
/**
 *  Find the parity of a byte
 *
 *  @param  data_byte           Find the parity of this byte.
 *
 *  @return parity              0 = ODD, 1 = EVEN
 *
 *  @note
 *
 ****************************************************************************/

int
parity_8(
    uint8_t                     data_byte
    )
{
    /**
     *  @param  bit_count           Return code                             */
    uint8_t                     bit_count;
    /**
     *  @param  bit                 Bit position                            */
    uint8_t                     bit_position;
    /**
     *  @param  byte                Work data byte                          */
    uint8_t                     byte;
    /**
     *  @param  rc                  Return Code                             */
    uint8_t                     rc;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Zero out the number of bits in the byte
    bit_count = 0;

    //  Load the data byte
    byte = data_byte;

    /************************************************************************
     *  Function Code
     ************************************************************************/

    //  Count the number of bits in the byte
    for ( bit_position = 0;
          bit_position < 8;
          bit_position += 1 )
    {
        //  Is this bit set ?
        if ( ( byte & 0x01 ) == 0x01 )
        {
            //  YES:    Increment the number of bits
            bit_count += 1;
        }
        //  Right shift one bit
        byte >>= 1;
    }

    //  Do we have an odd number of bits ?
    if ( ( bit_count & 0x01 ) == 0x01 )
        //  YES:    Odd parity
        rc = 0x00;
    else
        //  NO:     Even parity
        rc = 0x01;

    if(    ( CPU_REG_PC >= 0x0001 )
        && ( CPU_REG_PC <= 0x0001 ) )
        printf( "%04X - %d = parity_8( %02Xh ) [%d bits]\r\n", CPU_REG_PC, rc, data_byte, bit_count );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( rc );
}

/****************************************************************************/
/**
 *  Test for condition true
 *
 *  @param  op_code             Holds the condition map.
 *
 *  @return rc                  TRUE = Condition met, else FALSE is returned.
 *
 *  @note
 *
 ****************************************************************************/

int
is_ccc(
    uint8_t                     op_code
    )
{
    /**
     *  @param  rc                  Return code                             */
    uint8_t                     rc;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Assume the condition is NOT true.
    rc = false;

    /************************************************************************
     *  Function Code
     ************************************************************************/

    //  Map the condition
    switch( ( op_code & 0x38 ) >> 3 )
    {
        case    CCC_NZ:
            if ( ( CPU_REG_AF & CPU_FLAG_Z ) == 0 )
                rc = true;
            break;
        case    CCC_Z:
            if ( ( CPU_REG_AF & CPU_FLAG_Z ) != 0 )
                rc = true;
            break;
        case    CCC_NC:
            if ( ( CPU_REG_AF & CPU_FLAG_C ) == 0 )
                rc = true;
            break;
        case    CCC_C:
            if ( ( CPU_REG_AF & CPU_FLAG_C ) != 0 )
                rc = true;
            break;
        case    CCC_PE:         //  P/V = 1
            if ( ( CPU_REG_AF & CPU_FLAG_PV ) != 0 )
                rc = true;
            break;
        case    CCC_PO:         //  P/V = 0
            if ( ( CPU_REG_AF & CPU_FLAG_PV ) == 0 )
                rc = true;
            break;
        case    CCC_P:
            if ( ( CPU_REG_AF & CPU_FLAG_S ) == 0 )
                rc = true;
            break;
        case    CCC_M:
            if ( ( CPU_REG_AF & CPU_FLAG_S ) != 0 )
                rc = true;
            break;
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( rc );
}

/****************************************************************************/
/**
 *  Test for condition true
 *
 *  @param  op_code             Holds the condition map.
 *
 *  @return rc                  TRUE = Condition met, else FALSE is returned.
 *
 *  @note
 *
 ****************************************************************************/

int
is_cc(
    uint8_t                     op_code
    )
{
    /**
     *  @param  rc                  Return code                             */
    uint8_t                     rc;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Assume the condition is NOT true.
    rc = false;

    /************************************************************************
     *  Function Code
     ************************************************************************/

    //  Map the condition
    switch( ( op_code & 0x18 ) >> 3 )
    {
        case    CC_NZ:
            if ( ( CPU_REG_AF & CPU_FLAG_Z ) == 0 )
                rc = true;
            break;
        case    CC_Z:
            if ( ( CPU_REG_AF & CPU_FLAG_Z ) != 0 )
                rc = true;
            break;
        case    CCC_NC:
            if ( ( CPU_REG_AF & CPU_FLAG_C ) == 0 )
                rc = true;
            break;
        case    CC_C:
            if ( ( CPU_REG_AF & CPU_FLAG_C ) != 0 )
                rc = true;
            break;
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( rc );
}

/****************************************************************************/
/**
 *  Push data onto the stack.
 *
 *  @parm   data                    Data to be put on the stack.
 *
 *  @return                         No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
push(
    uint16_t                    data
    )
{
    //  Save the high byte on the stack
    memory_put_8( --CPU_REG_SP, ( ( data & 0xFF00 ) >> 8 ) );
    memory_put_8( --CPU_REG_SP, ( ( data & 0x00FF )      ) );
}

/****************************************************************************/
/**
 *  Pop data from the stack.
 *
 *  @parm   data                    Data to be put on the stack.
 *
 *  @return                         No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

uint16_t
pop(
    void
    )
{
    /**
     *  @parm   data                    Data removed from the stack         */
    uint16_t                    data;

    //  Save the high byte on the stack
    data  = ( memory_get_8( CPU_REG_SP++ )      );
    data |= ( memory_get_8( CPU_REG_SP++ ) << 8 );

    return( data );
}

#if 0           //  @ToDo   Move to the appropiate file
/****************************************************************************/
/**
 *  Extended Instruction Set 'CB'
 *
 *  @param  op_code             Should always be 0xCB
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

static
void
op_code_cb(
    uint8_t                     op_code
    )
{
    /**
     *  @param  op_code_cb          Current instruction code                */
    uint8_t                     op_code_cb;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Function Code
     ************************************************************************/

    //  Read the next instruction from main memory
    op_code_cb = memory_get_8( CPU_REG_PC++ );

    //  Mapped call to the op-code
    (*op_code_cb_table[ op_code_cb ])( op_code_cb );


    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
}
#endif

#if 0           //  @ToDo   Move to the appropiate file
/****************************************************************************/
/**
 *  Extended Instruction Set 'DD'
 *
 *  @param  op_code             Should always be 0xDD
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

static
void
op_code_dd(
    uint8_t                     op_code
    )
{
    /**
     *  @param  op_code_dd          Current instruction code                */
    uint8_t                     op_code_dd;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Function Code
     ************************************************************************/

    //  Read the next instruction from main memory
    op_code_dd = memory_get_8( CPU_REG_PC++ );

    //  Mapped call to the op-code
    (*op_code_dd_table[ op_code_dd ])( op_code_dd );


    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
}
#endif

#if 0           //  @ToDo   Move to the appropiate file
/****************************************************************************/
/**
 *  Extended Instruction Set 'DE'
 *
 *  @param  op_code             Should always be 0xDE
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

static
void
op_code_de(
    uint8_t                     op_code
    )
{
    /**
     *  @param  op_code_de          Current instruction code                */
    uint8_t                     op_code_de;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Function Code
     ************************************************************************/

    //  Read the next instruction from main memory
    op_code_de = memory_get_8( CPU_REG_PC++ );

    //  Mapped call to the op-code
    (*op_code_de_table[ op_code_de ])( op_code_de );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
}
#endif

#if 0           //  @ToDo   Move to the appropiate file
/****************************************************************************/
/**
 *  Extended Instruction Set 'FD'
 *
 *  @param  op_code             Should always be 0xFD
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

static
void
op_code_fd(
    uint8_t                     op_code
    )
{
    /**
     *  @param  op_code_fd          Current instruction code                */
    uint8_t                     op_code_fd;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Function Code
     ************************************************************************/

    //  Read the next instruction from main memory
    op_code_fd = memory_get_8( CPU_REG_PC++ );

    //  Mapped call to the op-code
    (*op_code_fd_table[ op_code_fd ])( op_code_fd );


    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
}
#endif

/****************************************************************************
 * MAIN
 ****************************************************************************/

/****************************************************************************/
/**
 *  Function description
 *
 *  @param  argc                Number of command line parameters.
 *  @param  argv                Indexed list of command line parameters
 *
 *  @return                     Zero for success. Any other value is an error.
 *
 *  @note
 *
 ****************************************************************************/

int
main(
    int                             argc,
    char                        *   argv[ ]
    )
{
    /**
     *  @param  post_rc             1 (TRUE) = tests passes                 */
    int                         post_rc;
    /**
     *  @param  op_code             Current instruction code                */
    uint8_t                     op_code;

    /************************************************************************
     *  OP-Code Table Initialization
     ************************************************************************/

    //  Initialize the instruction maps.
    op_code_i80_init( );
    op_code_z80_init( );
    op_code_CB_init( );
    op_code_DD_init( );
    op_code_DDCB_init( );
    op_code_ED_init( );
    op_code_FD_init( );
    op_code_FDCB_init( );

    //  Install the signal handler
    if ( signal( SIGINT, sig_handler ) == SIG_ERR )
    {
        printf( "\nCan't catch SIGINT\n" );
    }

    /************************************************************************
     *  Power On Self Test
     ************************************************************************/

    //  Initialize the return code
    post_rc = true;

#if 1
    //  Memory access
    if ( post_rc == true )  post_rc = memory_post( );
    //  LOAD
    if ( post_rc == true )  post_rc = ld_post( );
    //  EXCHANGE
    if ( post_rc == true )  post_rc = ex_post( );
    //  MATH
    if ( post_rc == true )  post_rc = math_post( );
    //  LOGIC
    if ( post_rc == true )  post_rc = logic_post( );
    //  MATH_16
    if ( post_rc == true )  post_rc = math_16_post( );
    //  SHIFT & ROTATE
    if ( post_rc == true )  post_rc = shift_post( );
    //  JUMP
    if ( post_rc == true )  post_rc = jump_post( );
    //  CALL
    if ( post_rc == true )  post_rc = call_post( );
    //  IO
    if ( post_rc == true )  post_rc = io_post( );

    //  Have all tests passes so far ?
    if ( post_rc == true )
    {
        //  YES:    Initialize memory
    memory_init( );
    }
#endif

    //  Start-up in Intel 8080 mode
    CPU = CPU_I80;

    /************************************************************************
     *  System Initialization.
     ************************************************************************/

    //  Start the system boot process.
    bios_cfg( );

    /************************************************************************
     *  Run The Program
     ************************************************************************/

    //  Have all tests passes so far ?
    if ( post_rc == true )
    {
        //  YES:    Start executing the instructions in memory
        inst_fetch( );
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  Shutdown
    bios_shutdown( );

    return( 0 );
}
/****************************************************************************/