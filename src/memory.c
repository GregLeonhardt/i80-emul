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
#include <string.h>             //  Functions for managing strings
#include <stdio.h>              //  Standard I/O definitions
                                //*******************************************
 #include <ctype.h>
                                //*******************************************

/****************************************************************************
 * Application
 ****************************************************************************/

                                //*******************************************
#include "global.h"             //  Global definitions
#include "registers.h"          //  All things CPU registers.
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
#define MEMORY_SIZE             ( 0x0000FFFF )
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
/**
 *  @param  CPU_MEM             CPU Main Memory                             */
uint8_t                     CPU_MEM[ MEMORY_SIZE ];
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
 *  Initialize all memory to x'00
 *
 *  @param
 *
 *  @return
 *
 *  @note
 *
 ****************************************************************************/

void
memory_init(
    void
    )
{
    //  Clear everything out of main memory
//  memset( CPU_MEM, 0x00, sizeof( CPU_MEM ) );     //  NOP
    memset( CPU_MEM, 0x76, sizeof( CPU_MEM ) );     //  HALT
}

/****************************************************************************/
/**
 *  Load memory with data.
 *
 *  @param  address             Starting memory address.
 *  @param  size                Number of bytes to load.
 *  @param  data_p              Pointer to the data to load.
 *
 *  @return
 *
 *  @note
 *
 ****************************************************************************/

void
memory_load(
    uint16_t                    address,
    uint16_t                    size,
    uint8_t                 *   data_p
    )
{
    //  Copy the data into memory
    memcpy( &CPU_MEM[ address ], data_p, size );
}

/****************************************************************************/
/**
 *  Read CPU memory.
 *
 *  @param  data_p              Pointer to the data to load.
 *  @param  size                Number of bytes to load.
 *  @param  address             Starting memory address.
 *
 *  @return
 *
 *  @note
 *
 ****************************************************************************/

void
memory_read(
    uint8_t                 *   data_p,
    uint16_t                    size,
    uint16_t                    address
    )
{
    //  Copy the data into memory
    memcpy( data_p, &CPU_MEM[ address ], size );
}

/****************************************************************************/
/**
 *  Get a byte of data from global memory using the provided address.
 *
 *  @param  address             Memory address
 *
 *  @return data                Data read from memory locatopn 'address'.
 *
 *  @note
 *
 ****************************************************************************/

uint8_t
memory_get_8(
    uint16_t                    address
    )
{
    /**
     *  @param  var                 var description                         */
    uint8_t                     data;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Function Code
     ************************************************************************/

    //  Memory read
    data = CPU_MEM[ address ];

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( data );
}

/****************************************************************************/
/**
 *  Get two bytes of data from global memory using the provided address.
 *
 *  @param  address             Memory address
 *
 *  @return data                Data read from memory locatopn 'address'.
 *
 *  @note
 *
 ****************************************************************************/

uint16_t
memory_get_16(
    uint16_t                    address
    )
{
    /**
     *  @param  var                 var description                         */
    uint16_t                    data;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Function Code
     ************************************************************************/

    //  Memory read
    data  = ( CPU_MEM[ address     ] << 8 );
    data |= ( CPU_MEM[ address + 1 ]      );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( data );
}

/****************************************************************************/
/**
 *  Put two bytes of data into global memory using the provided address.
 *
 *  @param  address             Memory address
 *  @param  data                Data to be stored.
 *
 *  @return                     No data is returned from this function.
 *
 *  @note
 *      Data is stored in reverse order. [ (LL), (HH) ]
 *
 ****************************************************************************/

uint16_t
memory_put_16_p(
    uint16_t                    address,
    uint16_t                    data
    )
{

    //  Memory read
    CPU_MEM[ address     ] = ( ( data & 0x00FF )      );
    CPU_MEM[ address + 1 ] = ( ( data & 0xFF00 ) >> 8 );

}

/****************************************************************************/
/**
 *  Get two bytes of data from global memory using the provided address.
 *
 *  @param  address             Memory address
 *
 *  @return data                Data read from memory locatopn 'address'.
 *
 *  @note
 *      Data is retrieved in reverse order. [ (LL), (HH) ]
 *
 ****************************************************************************/

uint16_t
memory_get_16_p(
    uint16_t                    address
    )
{
    /**
     *  @param  var                 var description                         */
    uint16_t                    data;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Function Code
     ************************************************************************/

    //  Memory read
    data  = ( CPU_MEM[ address     ]      );
    data |= ( CPU_MEM[ address + 1 ] << 8 );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
    return( data );
}

/****************************************************************************/
/**
 *  Get a bytes of data from global memory using the provided address.
 *
 *  @param  address             Memory address
 *  @param  data                Data to be written onto memory.
 *
 *  @return                     No information is returned from this function
 *
 *  @note
 *
 ****************************************************************************/

void
memory_put_8(
    uint16_t                    address,
    uint8_t                     data
    )
{

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Function Code
     ************************************************************************/

    //  Memory read
    CPU_MEM[ address ] = data;

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
}

/****************************************************************************/
/**
 *  Get two bytes of data from global memory using the provided address.
 *
 *  @param  address             Memory address
 *  @param  data                Data to be written onto memory.
 *
 *  @return                     No information is returned from this function
 *
 *  @note
 *
 ****************************************************************************/

void
memory_put_16(
    uint16_t                    address,
    uint16_t                    data
    )
{

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  Function Code
     ************************************************************************/

    //  Memory read
    CPU_MEM[ ( address     ) ] = ( ( data & 0xFF00 ) >> 8 );
    CPU_MEM[ ( address + 1 ) ] = ( ( data & 0x00FF )      );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  DONE!
}

/****************************************************************************/
/**
 *  Program Counter (PC) is pointing to address_low and PC + 1 is pointing to
 *  address_high.  Read these two bytes and return with the address.
 *
 *  @parm
 *
 *  @return address             The address.
 *
 *  @note
 *
 ****************************************************************************/

uint16_t
memory_get_16_pc_p(
    void
    )
{
    /**
     *  @param  address             Address of the source data              */
    uint16_t                    address;

    //  Get the data address.
    address  = ( memory_get_8( CPU_REG_PC++ )      );
    address |= ( memory_get_8( CPU_REG_PC++ ) << 8 );

    return( address );
}

/****************************************************************************/
/**
 *  Dump the contents of CPU memory
 *
 *  @parm   address                 Starting memory address
 *  @parm   length                  Number of bytes to dump
 *
 *  @return                         No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
memory_dump(
    uint16_t                    address,
    uint16_t                    length
    )
{
    /**
     *  @param  ndx                 Index into memory                       */
    uint16_t                    ndx;
    /**
     *  @param  c                   Text display data                       */
    unsigned char               c;
    /**
     *  @param  text                Text display data                       */
    unsigned char               text[ 17 ];

    memset( text, 0x00, sizeof( text ) );

    //  DUMP MEMORY
    for ( ndx = 0;
          ndx < length;
          ndx += 1 )
    {
        if ( ( ndx % 16 ) == 0 )
        {
            //  Is there data in the text buffer ?
            if ( strlen( text ) > 0 )
            {
                //  YES:    Display it.
                printf( "%s", text );
                memset( text, 0x00, sizeof( text ) );
            }
            printf( "\n%04X - ", ( address + ndx ) );
        }
        if ( ( ndx % 4 ) == 0 )
        {
            printf( " " );
        }
        if ( ( ndx % 8 ) == 0 )
        {
            printf( " " );
        }

        c = (unsigned char)memory_get_8( address + ndx );

        printf( "%02X ", c );

        //  Is this a printable character ?
        if ( isprint( c ) )
        {
            //  YES:    Add it to the text buffer
            strncat( text, &c, 1 );
        }
        else
        {
            //  NO:     Add a pad character
            strncat( text, "..", 1 );
        }
    }
    //  End the current line
    printf( "\n" );
}

/****************************************************************************/
/**
 *  Memory Power On Self Test
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
memory_post(
    void
    )
{
    /**
     *  @param  address             Current Write/Read location             */
    uint16_t                    address;
    /**
     *  @param  data_8              A byte of data                          */
    uint8_t                     data_8;
    /**
     *  @param  data_8              A word of data                          */
    uint16_t                    data_16;
    /**
     *  @param  post_rc             0 (FALSE) = tests passes                 */
    int                         post_rc;

    /************************************************************************
     *  Function Initialization
     ************************************************************************/

    //  Start bu setting all memory cells to 0x00
    memory_init( );

    //  Assume the test is going to pass
    post_rc = true;

    /************************************************************************
     *  Byte Write & Read
     ************************************************************************/

    // Loop through all memory writing data
    for ( address = 0;
          address != MEMORY_SIZE;
          address += 1 )
    {
        memory_put_8( address, ( address & 0x00FF ) );
    }

    //  This time read and verify the data
    for ( address = 0;
          address != MEMORY_SIZE;
          address += 1 )
    {
        data_8 = memory_get_8( address );

        //  Is it the expected data ?
        if ( data_8 != ( address & 0x00FF ) )
        {
            //  NO:     Write an error message
            printf( "POST: Memory byte R/W failed at address %08X\n", address );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }

    /************************************************************************
     *  Word Write & Read   (EVEN)
     ************************************************************************/

    // Loop through all memory writing data
    for ( address = 0;
          address != ( MEMORY_SIZE - 1 );
          address += 2 )
    {
        memory_put_16( address, address );
    }

    //  This time read and verify the data
    for ( address = 0;
          address != ( MEMORY_SIZE - 1 );
          address += 2 )
    {
        data_16 = memory_get_16( address );

        //  Is it the expected data ?
        if ( data_16 != address )
        {
            //  NO:     Write an error message
            printf( "POST: Memory word R/W failed at address %04X\n", address );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }

    /************************************************************************
     *  Word Write & Read (ODD)
     ************************************************************************/

    // Loop through all memory writing data
    for ( address = 1;
          address < ( MEMORY_SIZE - 1 );
          address += 2 )
    {
        memory_put_16( address, address );
    }

    //  This time read and verify the data
    for ( address = 1;
          address < ( MEMORY_SIZE - 1 );
          address += 2 )
    {
        data_16 = memory_get_16( address );

        //  Is it the expected data ?
        if ( data_16 != address )
        {
            //  NO:     Write an error message
            printf( "POST: Memory word R/W failed at address %08X\n", address );

            //  Set the return code to FALSE.
            post_rc = false;
        }
    }

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  Write a completion message
    printf( "POST: MEMORY  complete\n" );

    //  DONE!
    return( post_rc );
}
/****************************************************************************/