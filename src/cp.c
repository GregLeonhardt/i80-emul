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
#include <strings.h>            //  For manipulating arrays of characters
#include <string.h>             //
#include <ctype.h>              //
#include <sys/types.h>          //
#include <sys/stat.h>           //
#include <fcntl.h>              //
#include <errno.h>              //
#include <ncurses.h>            //
                                //*******************************************

/****************************************************************************
 * Application
 ****************************************************************************/

                                //*******************************************
#include "global.h"             //  Global definitions
#include "memory.h"             //  Memory management and access
#include "registers.h"          //  All things CPU registers.
#include "op_code.h"            //  OP-Code instruction maps
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

/****************************************************************************/
/**
 *  #CP BOOT
 *      Perform a CP/M Cold Boot.
 *
 *  @param
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
cp_boot(
    void
    )
{
    //  Make a COLD BOOT vector jump
    memory_put_8( 0x0000, 0xC3 );
    memory_put_8( 0x0001, 0x00 );
    memory_put_8( 0x0002, 0xF2 );

    //  Change the program counter to go there
    CPU_REG_PC = 0x0000;
}

/****************************************************************************/
/**
 *  #CP SHUTDOWN
 *      Shutdown the virtual machine.
 *
 *  @param
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      The following message is displayed:
 *          "DEBUG: 'HLT' instruction (x'76) detected @ address x'0000"
 *
 ****************************************************************************/

void
cp_shutdown(
    void
    )
{
    printf( "\r\nShutting down\r\n" );

    //  terminate the program
    exit( 0 );
}

/****************************************************************************/
/**
 *  #CP EJECT {drive_letter}:
 *      Eject one of the drives.
 *
 *  @param
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
cp_eject(
    char                    *   command
    )
{
    /**
     *  @param  drive_num       Number reflecting the drive letter A=1 etc  */
    int                         drive_num;
    /**
     *  @param  cmd_ndx         Index into the command buffer               */
    int                         cmd_ndx;

    //  Assume an invalid command format
    drive_num = -1;

    //  Look for the drive letter
    for ( cmd_ndx = 0;
          cmd_ndx < strlen( command );
          cmd_ndx += 1 )
    {
        if (    ( isalpha( command[ cmd_ndx ] ) !=  0  )
             && ( command[ cmd_ndx + 1 ]        == ':' ) )
        {
            //  Translate the letter to a number (a=A=1, b=B=2, etc)
            drive_num = command[ cmd_ndx ] & 0x0F;

            //  Exit the loop now that we have a drive letter
            break;
        }
    }

    //  Was the command format valid ?
    if ( drive_num > 0 && 15 > drive_num )
    {
        //  YES:    This has to be done in the BIOS code
        bios_eject( ( drive_num - 1 ) );
    }
    else
    {
        //  Write an error / help message
        printf( "\r\nCP EJECT: Improper drive defined\r\n" );
        printf( "          Try 'eject {drive_letter}:\r\n" );
        printf( "          For example:  eject A:\r\n" );
        printf( "          or            EJECT b:\r\n" );
    }
}

/****************************************************************************/
/**
 *  #CP MOUNT {drive_letter}: {file_name}
 *      Eject one of the drives.
 *
 *  @param
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
cp_mount(
    char                    *   command
    )
{
    /**
     *  @param  drive_num       Number reflecting the drive letter A=1 etc  */
    int                         drive_num;
    /**
     *  @param  file_name       Name of the file to be mounted              */
    char                        file_name[ 255 ];
    /**
     *  @param  cmd_ndx         Index into the command buffer               */
    int                         cmd_ndx;

    //  Assume an invalid command format
    drive_num = -1;

    //  Look for the drive letter
    for ( cmd_ndx = 0;
          cmd_ndx < strlen( command );
          cmd_ndx += 1 )
    {
        if (    ( isalpha( command[ cmd_ndx ] ) !=  0  )
             && ( command[ cmd_ndx + 1 ]        == ':' ) )
        {
            //  Translate the letter to a number (a=A=1, b=B=2, etc)
            drive_num = command[ cmd_ndx ] & 0x0F;

            //  Exit the loop now that we have a drive letter
            break;
        }
    }

    //  Was the command format valid ?
    if ( drive_num > 0 && 15 > drive_num )
    {
        //  Move past all space characters between the drive and file name.
        for ( cmd_ndx = ( cmd_ndx + 2 );
              cmd_ndx < strlen( command );
              cmd_ndx += 1 )
        {
            //  is this another space character ?
            if ( command[ cmd_ndx ] != ' ' )
            {
                //  NO:     This is the start of the file name.
                break;
            }
        }

        //  Verify it will fit into the file name buffer ?
        if ( strlen( &command[ cmd_ndx ] ) < sizeof( file_name ) )
        {
            //  YES:    Was a file name present ?
            if ( strlen( &command[ cmd_ndx ] ) > 0 )
            {
                //  YES:    Copy the file name to the file name buffer
                memset( file_name, '\0', sizeof( file_name ) );
                memcpy( file_name, &command[ cmd_ndx ], strlen( &command[ cmd_ndx ] ) );

                //  Pass the information over to the BIOS to perform the mount
                bios_mount( ( drive_num - 1 ), file_name );
            }
            else
            {
                //  NO:     Failed to include a file name
                printf( "\r\nCP MOUNT: No file name in the command.\r\n" );
            }
        }
        else
        {
            //  The length of the file name is bigger than the allocated buffer
            printf( "\r\nCP MOUNT: The specified file name is too long\r\n" );
        }

    }
    else
    {
        //  Write an error / help message
        printf( "\r\nCP MOUNT: Improper drive defined\r\n" );
        printf( "            Try 'mount {drive_letter}: {file_name}\r\n" );
        printf( "            For example:  mount A: cpm_A.img\r\n" );
        printf( "            or            MOUNT b: cpm_B.img\r\n" );
    }
}

/****************************************************************************/
/**
 *  #CP MKDSK {file_name}:
 *      Create a new virtual disk on the Linux file system.
 *
 *  @param
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
cp_mkdsk(
    char                    *   command
    )
{
    /**
     *  @param  cmd_ndx         Index into the command buffer               */
    int                         cmd_ndx;
    /**
     *  @param  file_name       Name of the file to be mounted              */
    char                        file_name[ 255 ];
    /**
     *  @param  fd              File Descriptor                             */
    int                         fd;
    /**
     *  @param  dummy_data      Data that will be written to the file       */
    char                        dummy_data[ 1024 ];

    //  Move the index past the command {MkDsk} and spaces.
    for ( cmd_ndx = 6;
          cmd_ndx < strlen( command );
          cmd_ndx += 1 )
    {
        //  is this another space character ?
        if ( command[ cmd_ndx ] != ' ' )
        {
            //  NO:     This is the start of the file name.
            break;
        }
    }

    //  Verify it will fit into the file name buffer ?
    if ( strlen( &command[ cmd_ndx ] ) < sizeof( file_name ) )
    {
        //  YES:    Was a file name present ?
        if ( strlen( &command[ cmd_ndx ] ) > 0 )
        {
            //  YES:    Copy the file name to the file name buffer
            memset( file_name, '\0', sizeof( file_name ) );
            memcpy( file_name, &command[ cmd_ndx ], strlen( &command[ cmd_ndx ] ) );

            //  Open the file
            fd = open( file_name, ( O_CREAT | O_RDWR ), ( S_IRUSR | S_IWUSR ) );

            //  Was the file open successful ?
            if ( fd < 0 )
            {
                //  NO:
                printf( "\r\nCP MKDSK: "
                        "Unable to open file '%s'\r\n:", file_name );
                fprintf( stderr, "Value of errno: %d\r\n", errno );
                perror( "Error printed by perror" );

                //  We're done
                return;
            }
            else
            {
                /**
                 *  @param  block_count     Current data block number       */
                int                         block_count;

                //  YES:    Fill the buffer with dummy data
                memset( dummy_data, 0xE5, sizeof( dummy_data ) );

                //  Write 8192 * 1024 bytes
                for( block_count = 0;
                     block_count < 4096;
                     block_count += 1 )
                {
                    write( fd, dummy_data, sizeof( dummy_data ) );
                }

                //  All done, close the file
                close( fd );
            }
        }
        else
        {
            //  NO:     Failed to include a file name
            printf( "\r\nCP MKDSK: No file name in the command.\r\n" );
        }
    }
    else
    {
        //  The length of the file name is bigger than the allocated buffer
        printf( "\r\nCP MKDSK: The specified file name is too long\r\n" );
    }


}

/****************************************************************************/
/**
 *  #CP IMPORT {file_name}
 *      Create a new virtual disk on the Linux file system.
 *
 *  @param
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *      This function runs in two parts:  1) The Linux file is identified
 *      and read into CPU memory.  2) A CP/M copy program is loaded into
 *      CPU memory and run.
 *
 *      The CP/M program will write the data to a CP/M file.
 *
 ****************************************************************************/

void
cp_import(
    char                    *   command
    )
{
    /**
     *  @param  cmd_ndx         Index into the command buffer               */
    int                         cmd_ndx;
    /**
     *  @param  file_path       File path & name                            */
    char                        file_path[ 255 ];
    /**
     *  @param  fd              File Descriptor                             */
    int                         fd;
    /**
     *  @param  file_data       Import data                                 */
    char                        file_data[ 256 ];
    /**
     *  @param  bytes_read      Number of data bytes read from the file     */
    int                         bytes_read;
    /**
     *  @param  block_count     Current data block number                   */
    int                         block_count;

    //  Move the index past the command {MkDsk} and spaces.
    for ( cmd_ndx = 6;
          cmd_ndx < strlen( command );
          cmd_ndx += 1 )
    {
        //  is this another space character ?
        if ( command[ cmd_ndx ] != ' ' )
        {
            //  NO:     This is the start of the file name.
            break;
        }
    }

    //  Verify it will fit into the file name buffer ?
    if ( strlen( &command[ cmd_ndx ] ) < sizeof( file_path ) )
    {
        //  YES:    Was a file name present ?
        if ( strlen( &command[ cmd_ndx ] ) > 0 )
        {
            //  YES:    Copy the file name to the file name buffer
            memset( file_path, '\0', sizeof( file_path ) );
            memcpy( file_path, &command[ cmd_ndx ], strlen( &command[ cmd_ndx ] ) );

            //  Open the file
            fd = open( file_path, ( O_RDONLY ) );

            //  Was the file open successful ?
            if ( fd < 0 )
            {
                //  NO:
                printf( "\r\nCP IMPORT: "
                        "Unable to open file '%s'\r\n:", file_path );
                perror(   "           Error printed by perror" );

                //  We're done
                return;
            }
            else
            {
                //  Set the block count to the start of the file
                block_count = 0;

                //  Import data loop
                do
                {
                    //  YES:    Fill the buffer with dummy data
                    memset( file_data, 0x00, sizeof( file_data ) );

                    bytes_read = read( fd, file_data, sizeof( file_data ) );

                    //  Was the read successful ?
                    if ( bytes_read > 0 )
                    {
                        //  YES:    Load the data into CPU memory
                        memory_load( ( 0x0100 + ( block_count * sizeof( file_data ) ) ),
                                     bytes_read, (uint8_t*)file_data );

                        //  Setup for the next data block
                        block_count += 1;
                    }

                //  Keep looping as long as we keep getting more data
                } while ( bytes_read > 0 );

                //  All done, close the file
                close( fd );

                //  Show the user the number of blocks that were copied.
                printf( "\r\n#CP IMPORT: %d blocks were copied\r\n", block_count );
            }
        }
        else
        {
            //  NO:     Failed to include a file name
            printf( "\r\nCP IMPORT: No file name in the command.\r\n" );
        }
    }
    else
    {
        //  The length of the file name is bigger than the allocated buffer
        printf( "\r\nCP IMPORT: The specified file name is too long\r\n" );
    }


}

/****************************************************************************
 * MAIN
 ****************************************************************************/


/****************************************************************************/
/**
 *  Command Processor
 *
 *  @param
 *
 *  @return post_rc             TRUE when all POST tests pass, else
 *                              FALSE is returned.
 *
 *  @note
 *      COMMANDS:
 *          BOOT                BOOT / REBOOT CP/M
 *          SHUTDOWN            Terminate CP/M
 *          IMPORT              Copy a Linux file to a CP/M file.
 *          EXPORT              Copy a CP/M file to a Linux file.
 *          DEBUG               Set debug mode.
 *          MOUNT               Mount a Linux file to a CP/M drive.
 *          EJECT               Dismount a CP/M drive.
 *          MKDSK               Create a new CP/M Disk
 *
 ****************************************************************************/

void
cp(
    void
    )
{
    /**
     *  @param  command             The CP command to process               */
    char                        command[ 128 ];
    /**
     *  @param  kb_char             Input character from keyboard           */
    char                        kb_char;
    /**
     *  @param  cmd_ndx             Index into the command buffer           */
    int                         cmd_ndx;

    //  Change the command prompt to CP mode.
    printf( "\r\n#CP> " );
    fflush( stdout );

    //  Clear the command buffer
    memset( command, '\0', sizeof( command ) );

    //  Read the maximum buffer size
    for( cmd_ndx = 0;
         cmd_ndx < sizeof( command );
         )
    {
        do
        {
            //  Read from keyboard
            kb_char = getch( );

        }   while( ( kb_char & 0xFF ) == 0xFFFF );

        //  YES:    Is it an End-Of-Line character ?
        if ( kb_char == 0x0A )
        {
            //  YES:    That's the end of the input
            break;
        }
        else
        {
            //  NO:     Append it to the command
            command[ cmd_ndx ] = kb_char;

            //  And echo it to the screen
            fputc( kb_char, stdout );
            fflush( stdout );

            //  Increment the command index
            cmd_ndx += 1;
        }
    }
    printf( "\r\n" );
    fflush( stdout );

    //========================================================================
    //  BOOT                BOOT / REBOOT CP/M ?
    if ( strncasecmp( command, "BOOT",      4 ) == 0 )
    {
        //  YES:    Do it.
        cp_boot( );
    }
    //========================================================================
    //  DEBUG               Set debug mode ?
    else
    if ( strncasecmp( command, "DEBUG",     5 ) == 0 )
    {
    }
    //========================================================================
    //  MOUNT               Mount a Linux file to a CP/M drive ?
    else
    if ( strncasecmp( command, "MOUNT",     5 ) == 0 )
    {
        //  YES:    Do it.
        cp_mount( command );
    }
    //========================================================================
    //  EJECT               Dismount a CP/M drive ?
    else
    if ( strncasecmp( command, "EJECT",     5 ) == 0 )
    {
        //  YES:    Do it.
        cp_eject( command );
    }
    //========================================================================
    //  MKDSK               Create a new CP/M Disk ?
    else
    if ( strncasecmp( command, "MKDSK",     5 ) == 0 )
    {
        //  YES:    Do it.
        cp_mkdsk( command );
    }
    //========================================================================
    //  IMPORT              Copy a Linux file to a CP/M file ?
    else
    if ( strncasecmp( command, "IMPORT",    6 ) == 0 )
    {
        //  YES:    Do it.
        cp_import( command );
    }
    //========================================================================
    //  EXPORT              Copy a CP/M file to a Linux file. ?
    else
    if ( strncasecmp( command, "EXPORT",    6 ) == 0 )
    {
    }
    //========================================================================
    //  SHUTDOWN            Terminate CP/M ?
    else
    if ( strncasecmp( command, "SHUTDOWN",  8 ) == 0 )
    {
        //  YES:    Do it.
        cp_shutdown( );
    }
    //========================================================================
    //  Not a valid command
    else
    {
        printf( "\r\n'%s' is NOT a valid CP command.\r\n", command );
        printf( "BOOT                   - BOOT / REBOOT CP/M\r\n" );
        printf( "SHUTDOWN               - Terminate CP/M\r\n" );
        printf( "IMPORT {disk}: {file}  - Copy a Linux file to a CP/M file.\r\n" );
        printf( "EXPORT {disk}:{file}   - Copy a CP/M file to a Linux file.\r\n" );
        printf( "DEBUG  {mode}          - Set debug mode.\r\n" );
        printf( "MOUNT  {disk}: {file}  - Mount a Linux file to a CP/M drive.\r\n" );
        printf( "EJECT  {disk}:         - Dismount a CP/M drive.\r\n" );
        printf( "MKDSK  {file}          - Create a new CP/M Disk\r\n" );
    }
}
/****************************************************************************/