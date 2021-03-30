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
#define     BOOT_FROM_FILE  ( 0 )

//  @NOTE:  Only one of the following may be enabled.
#define     CON_V3          ( 1 )
#define     CON_V2          ( 0 )
#define     CON_V1          ( 0 )

/****************************************************************************
 * System Function
 ****************************************************************************/

                                //*******************************************
#include <stdbool.h>            //  TRUE, FALSE, etc.
#include <stdint.h>             //  Alternative storage types
#include <stdlib.h>             //  ANSI standard library.
#include <unistd.h>             //  UNIX standard library.
#include <stdio.h>              //  Standard I/O definitions
#include <string.h>             //  Functions for managing strings
                                //*******************************************
#include <ctype.h>              //
#include <sys/types.h>          //
#include <sys/stat.h>           //
#include <fcntl.h>              //
#include <errno.h>              //
#include <curses.h>             //
#include <ncurses.h>            //
#include <termios.h>            //
                                //*******************************************

/****************************************************************************
 * Application
 ****************************************************************************/

                                //*******************************************
#include "global.h"             //  Global definitions
#include "memory.h"             //  Memory management and access
#include "registers.h"          //  All things CPU registers.
#include "boot_rom.h"           //  Boot ROM
#include "bios.h"               //  CP/M BIOS
#include "cp.h"                 //  Command Processor
                                //*******************************************

/****************************************************************************
 * Enumerations
 ****************************************************************************/

//----------------------------------------------------------------------------

enum disk_state_e
{
    DS_CLOSED = 0,              //  The disk file system is closed
    DS_OPEN = 1                 //  The disk file system is open
};
//----------------------------------------------------------------------------

/****************************************************************************
 * Definitions
 ****************************************************************************/

//----------------------------------------------------------------------------
#define DISK_A                  "/home/greg/CPM/DiskImages/A.img"
#define DISK_B                  "/home/greg/CPM/DiskImages/B.img"
#define DISK_C                  "/home/greg/CPM/DiskImages/C.img"
#define DISK_D                  "/home/greg/CPM/DiskImages/D.img"
#define CPM_SYS                 "/home/greg/CPM/DiskImages/CPM.SYS"
#define PUNCH                   "/home/greg/CPM/punch.txt"
#define READER                  "/home/greg/CPM/reader.txt"
#define PRINTER                 "/home/greg/CPM/printer.txt"
//----------------------------------------------------------------------------
#define BLOCK_SIZE              0x0080
//----------------------------------------------------------------------------
#define I8080_MAJ               1
#define I8080_MIN               0
#define I8080_PTF               1
//----------------------------------------------------------------------------
#define VCPM_MAJ                0
#define VCPM_MIN               54
#define VCPM_PTF                2
//----------------------------------------------------------------------------
#define CPM_MAJ                 2
#define CPM_MIN                 2
#define CPM_PTF                 0
//----------------------------------------------------------------------------
#define SCREEN_WIDTH           80
#define SCREEN_HEIGHT          24
//----------------------------------------------------------------------------

/****************************************************************************
 * Private Structures
 ****************************************************************************/

//----------------------------------------------------------------------------
struct  disk_io_t
{
    /**
     *  @param  disk_fd             RAM Disk File Descriptor                */
    int                         disk_fd;
    /**
     *  @param  sector              Sector number                           */
    uint8_t                     sector;
    /**
     *  @param  track               Track  number                           */
    uint8_t                     track;
    /**
     *  @param  data                Read or write data.                     */
    uint8_t                     data[ BLOCK_SIZE ];
    /**
     *  @param  track_num           Track number for the next W/R           */
    uint16_t                    track_num;
    /**
     *  @param  sector_num          Sector number for the next W/R          */
    uint16_t                    sector_num;
    /**
     *  @param  dma_addr            Disk data W/R transfer address          */
    uint16_t                    dma_addr;
    /**
     *  @param  sec_track           Number of sectors per track             */
    uint16_t                    sec_track;
    /**
     *  @param  disk_parm_tbl       Disk Parameter Table                    */
    uint16_t                    disk_parm_tbl;
    /**
     *  @param  lba                 Logical Block Address                   */
    int                         lba;
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

//----------------------------------------------------------------------------
/**
 *  @param  disk_id                 Currently selected disk ID              */
uint8_t                         disk_id;
//----------------------------------------------------------------------------
/**
 *  @param  disk_io                 Management information for DRIVE-0      */
struct  disk_io_t               disk_io[ MAX_DISK ];
//----------------------------------------------------------------------------
/**
 *  @param  punch_fp                Paper Tape Punch File Descriptor        */
FILE                        *   punch_fp;
//----------------------------------------------------------------------------
/**
 *  @param  reader_fp               Paper Tape Reader File Descriptor       */
FILE                        *   reader_fp;
//----------------------------------------------------------------------------
/**
 *  @param  printer_fp              Line Printer File Descriptor            */
FILE                        *   printer_fp;
//----------------------------------------------------------------------------
/**
 *  @param  kb_buffer               Keyboard (stdin) buffer                 */
uint8_t                         kb_read_size;
uint8_t                         kb_buffer[ 128 ];
//----------------------------------------------------------------------------

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************/
/**
 *  SELDSK          Select disc drive
 *      Select the disc drive in register C (0=A:, 1=B: ...). Called with E=0
 *      or 0FFFFh.
 *
 *      If bit 0 of E is 0, then the disc is logged in as if new; if the format
 *      has to be determined from the boot sector, for example, this will be
 *      done.
 *
 *      If bit 0 if E is 1, then the disc has been logged in before. The disc
 *      is not accessed; the DPH address (or zero) is returned immediately.
 *
 *      SELDSK returns the address of a Disc Parameter Header in HL. The exact
 *      format of a DPH varies between CP/M versions. If the disc could not
 *      be selected it returns HL=0.
 *
 *  @param
 *
 *  @return                         No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

static
void
bios_seldsk(
    void
    )
{
    /**
     *  @param  dpb                 Disk Parameter Block                    */
    uint16_t                    dpb;

#if DEBUG_MODE
    //  Log the call
    printf( "===========================================================\r\n" );
    printf( "DEBUG: BIOS call 'SELDSK'\r\n" );
    printf( "\tDisk   Number =  A = x'%02X\r\n", GET_A( ) );
#endif

    //  Save the selected disk ID.
    disk_id = GET_C( );

    //  Is this a valid disk ID ?
    if (    (       disk_id < MAX_DISK       )
         && ( disk_io[ disk_id ].disk_fd > 0 ) )
    {
        //  Locate the Disk Parameter Header for this disk.
        disk_io[ disk_id ].disk_parm_tbl = ( DPH_BASE + ( disk_id * DPH_SIZE ) );
        CPU_REG_HL = disk_io[ disk_id ].disk_parm_tbl;

        //  Get the address of the disk parameter block
        dpb = memory_get_16_p( DPH_BASE + ( 16 * disk_id ) + DPH_DPB_OFFSET );
        disk_io[ disk_id ].sec_track = memory_get_16_p( dpb + DPB_SPT_OFFSET );
    }
    else
    {
        //  NO:     The select failed.
        CPU_REG_HL = 0;
    }

#if DEBUG_MODE
    //  Log the call
    printf( "\tParm Block    = HL = x'%04X\r\n", CPU_REG_HL );
#endif

}

/****************************************************************************/
/**
 *  SELTRK          Set track number
 *      Set the track in BC - 0 based
 *
 *  @param
 *
 *  @return                         No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

static
void
bios_settrk(
    void
    )
{
#if DEBUG_MODE
    //  Log the call
    printf( "===========================================================\r\n" );
    printf( "DEBUG: BIOS call 'SETTRK'\r\n" );
    printf( "\tTrack  Number = BC = x'%04X\r\n", CPU_REG_BC );
#endif

    //  Save the track number
    disk_io[ disk_id ].track_num = CPU_REG_BC;
}

/****************************************************************************/
/**
 *  SETSEC          Set sector number
 *      Set the sector in BC. Under CP/M 1 and 2 a sector is 128 bytes.
 *
 *      There has been discussion in comp.os.cpm about whether the parameter
 *      to this function is a byte or a word. The conclusion (based on examining
 *      the BDOS source) was that it is a word.
 *
 *  @param
 *
 *  @return                         No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

static
void
bios_setsec(
    void
    )
{
#if DEBUG_MODE
    //  Log the call
    printf( "===========================================================\r\n" );
    printf( "DEBUG: BIOS call 'SETSEC'\r\n" );
    printf( "\tSector Number = BC = x'%04X\r\n", CPU_REG_BC );
#endif
    //  Save the track number
    disk_io[ disk_id ].sector_num = CPU_REG_BC;
}

/****************************************************************************/
/**
 *  SECTRAN         Sector translation for skewing
 *      Translate sector numbers to take account of skewing.
 *
 *      On entry, BC=logical sector number (zero based) and DE=address of
 *      translation table. On exit, HL contains physical sector number. On a
 *      system with hardware skewing, this would normally ignore DE and return
 *      either BC or BC+1.
 *
 *  @param
 *
 *  @return                         No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

static
void
bios_sectran(
    void
    )
{
#if DEBUG_MODE
    //  Log the call
    printf( "===========================================================\r\n" );
    printf( "DEBUG: BIOS call 'SECTRAN'\r\n" );
    printf( "\tSector Number = BC = x'%04X\r\n", CPU_REG_BC );
    printf( "\tTable Address = DE = x'%04X\r\n", CPU_REG_DE );
#endif

    //  Is there a translation table for this drive ?
    if ( CPU_REG_DE != 0x0000 )
    {
        //  YES:    Get the translated sector number
        CPU_REG_HL = memory_get_8( CPU_REG_DE + CPU_REG_BC );
    }
    else
    {
        //  Add one so it is base 1
        CPU_REG_HL = CPU_REG_BC + 1;
    }
#if DEBUG_MODE
    printf( "\tSector Number = HL = x'%04X\r\n", CPU_REG_HL );
#endif
}

/****************************************************************************/
/**
 *  SETDMA          Set DMA address
 *      The next disc operation will read its data from (or write its data to)
 *      the address given in BC.
 *
 *  @param
 *
 *  @return                         No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

static
void
bios_setdma(
    void
    )
{
#if DEBUG_MODE
    //  Log the call
    printf( "===========================================================\r\n" );
    printf( "DEBUG: BIOS call 'SETDMA'\r\n" );
    printf( "\tDMA Address = BC = x'%04X\r\n", CPU_REG_BC );
#endif

    //  Save the W/R data address
    disk_io[ disk_id ].dma_addr = CPU_REG_BC;
}

/****************************************************************************/
/**
 *  HOME            Move disc head to track 0
 *      Move the current drive to track 0.
 *
 *  @param
 *
 *  @return                         No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

static
void
bios_home(
    void
    )
{
#if DEBUG_MODE
    //  Log the call
    printf( "===========================================================\r\n" );
    printf( "DEBUG: BIOS call 'HOME'\r\n" );
#endif

    //  Since there is only a RAM disk, there isn't much to do.
}

/****************************************************************************/
/**
 *  READ            Read a sector
 *      Read the currently set track and sector at the current DMA address.
 *      Returns A=0 for OK, 1 for unrecoverable error, 0FFh if media changed.
 *
 *  @param
 *
 *  @return                         No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

static
void
bios_read(
    void
    )
{
#if DEBUG_MODE
    //  Log the call
    printf( "===========================================================\r\n" );
    printf( "DEBUG: BIOS call 'READ'\r\n" );
#endif

    //  Calculate the logical block address
    disk_io[ disk_id ].lba
            = ( disk_io[ disk_id ].track_num * disk_io[ disk_id ].sec_track )
                + (disk_io[ disk_id ].sector_num - 1 );

    //  Seek to the first boot block
    lseek( disk_io[ disk_id ].disk_fd,
            BLOCK_SIZE * disk_io[ disk_id ].lba,
           SEEK_SET );

    //  Read a block from the disk
    read( disk_io[ disk_id ].disk_fd,
            disk_io[ disk_id ].data,
          BLOCK_SIZE );

    //  Copy the data block to CPU memory.
    memory_load( disk_io[ disk_id ].dma_addr,
            BLOCK_SIZE,
                 disk_io[ disk_id ].data );
#if DEBUG_MODE
    printf( "Disk: %d, Track: %2d, Sector: %2d, lSeek: %X, LBA: %04X\r\n",
            disk_id,
            disk_io[ disk_id ].track_num,
            disk_io[ disk_id ].sector_num,
            BLOCK_SIZE * disk_io[ disk_id ].lba,
            disk_io[ disk_id ].lba );

    memory_dump( disk_io[ disk_id ].dma_addr, BLOCK_SIZE );
#endif

    //  Set the return code
    PUT_A( 0x00 );

#if DEBUG_MODE
    //  Log the call
    printf( "\tReturn Code =  A = x'%02X\r\n", GET_A( )   );
#endif
}

/****************************************************************************/
/**
 *  WRITE           Write a sector
 *      Write the currently set track and sector. C contains a deblocking code:
 *
 *      C=0 - Write can be deferred
 *      C=1 - Write must be immediate
 *      C=2 - Write can be deferred, no pre-read is necessary.
 *
 *      Returns A=0 for OK, 1 for unrecoverable error, 2 if disc is readonly,
 *      0FFh if media changed.
 *
 *  @param
 *
 *  @return                         No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

static
void
bios_write(
    void
    )
{
    /**
     *  @param  seek_offset         The resulting offset  location          */
    off_t                       seek_offset;

#if DEBUG_MODE
    //  Log the call
    printf( "===========================================================\r\n" );
    printf( "DEBUG: BIOS call 'WRITE'\r\n" );
#endif

    //  Copy the data block from CPU memory.
    memory_read( disk_io[ disk_id ].data,
                 BLOCK_SIZE,
                 disk_io[ disk_id ].dma_addr );

    //  Calculate the logical block address
    disk_io[ disk_id ].lba
             =    ( disk_io[ disk_id ].track_num * disk_io[ disk_id ].sec_track )
                + ( disk_io[ disk_id ].sector_num - 1 );

    //  Seek to the first boot block
    seek_offset = lseek( disk_io[ disk_id ].disk_fd,
                         BLOCK_SIZE * disk_io[ disk_id ].lba,
                         SEEK_SET );

    //  Was the disk successful ?
    if ( seek_offset == -1 )
    {
        //  NO:
        printf( "BIOS: bios_write( ); Seek failure.\r\n:" );
        perror( "                     " );
    }
#if DEBUG_MODE
    //  Log the call
    printf( "Disk: %d, Track: %2d, Sector: %2d, lSeek: %X, LBA: %04X\r\n",
            disk_id,
            disk_io[ disk_id ].track_num,
            disk_io[ disk_id ].sector_num,
            BLOCK_SIZE * disk_io[ disk_id ].lba,
            disk_io[ disk_id ].lba );

    memory_dump( disk_io[ disk_id ].dma_addr, BLOCK_SIZE );
#endif

    //  Read a block from the disk
    write( disk_io[ disk_id ].disk_fd,
           disk_io[ disk_id ].data,
           BLOCK_SIZE );

    //  Set the return code
    PUT_A( 0x00 );

#if DEBUG_MODE
    //  Log the call
    printf( "\tReturn Code =  A = x'%02X\r\n", GET_A( )   );
#endif
}

/****************************************************************************/
/**
 *  BOOT        Cold start routine
 *      This function is completely implementation-dependent and should never
 *      be called from user code.
 *
 *  @param
 *
 *  @return                         No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

static
void
bios_boot(
    void
    )
{
    /**
     *  @param  disk                Disk being initialized                  */
    uint8_t                     disk;
#if DEBUG_MODE
    printf( "===========================================================\r\n" );
    printf( "DEBUG: BIOS call 'BOOT'\r\n" );
#endif

#if CON_V3

    //  List programs and version numbers.
    printf( "i8080 emulation:   %02d.%02d.%02d\r\n",
            I8080_MAJ, I8080_MIN, I8080_PTF );
    printf( "Virtual CP/M 80:   %02d.%02d.%02d\r\n",
            VCPM_MAJ, VCPM_MIN, VCPM_PTF );
    printf( "CP/M version:      %02d.%02d.%02d\r\n",
            CPM_MAJ, CPM_MIN, CPM_PTF );

    //  NCURSES initialization

    //  Start curses mode
    filter( );
    initscr( );

    //  Line buffering disabled
    cbreak( );
    raw( );

    //  We get F1, F2 etc..
    keypad( stdscr, TRUE );

    //  Don't echo() while we do getch
    noecho( );

#elif CON_V2

    //  List programs and version numbers.
    printf( "\033[2J \033[H\n" );
    printf( "i8080 emulation:   %02d.%02d.%02d\n",
            I8080_MAJ, I8080_MIN, I8080_PTF );
    printf( "Virtual CP/M 80:   %02d.%02d.%02d\n",
            VCPM_MAJ, VCPM_MIN, VCPM_PTF );
    printf( "CP/M version:      %02d.%02d.%02d\n",
            CPM_MAJ, CPM_MIN, CPM_PTF );

    int flags = fcntl( STDIN_FILENO, F_GETFL, 0 );
    fcntl( STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

  struct termios tattr;
/* Make sure stdin is a terminal. */
  if (!isatty (STDIN_FILENO))
    {
      fprintf (stderr, "Not a terminal.\n");
      exit (EXIT_FAILURE);
    }

/* Set the funny terminal modes. */
  tcgetattr (STDIN_FILENO, &tattr);
  tattr.c_lflag &= ~(ICANON | ECHO);	/* Clear ICANON and ECHO. */
  tattr.c_cc[VMIN] = 1;
  tattr.c_cc[VTIME] = 0;
  tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);
#elif CON_V1
    //  Set stdin (the keyboard) to be NON-BLOCKING.
    fcntl( 0, F_SETFL, fcntl( 0, F_GETFL ) | O_NONBLOCK );
#endif

    //  Close all open disks
    for ( disk = 0;
            disk < MAX_DISK;
          disk += 1 )
    {
        //  Is this disk opened ?
        if ( disk_io[ disk ].disk_fd > 0 )
        {
            //  YES:    Close it
            close( disk_io[ disk ].disk_fd );
        }
        //  Mark it as closed
        disk_io[ disk ].disk_fd = -1;
    }

    //------------------------------------------------------------------------
    //  Mount disk      A:
    //------------------------------------------------------------------------

    //  Open the primary disk for write & read operations
    disk_io[ 0 ].disk_fd = open( DISK_A, O_RDWR );

    //  Was the open successful ?
    if ( disk_io[ 0 ].disk_fd <= 0 )
    {
        //  NO:     Message and terminate
        printf( "BIOS: bios_boot( ); "
                "Unable to mount DISK 0 [ A: ] (%s)\r\n:", DISK_A );
        perror( "                    " );
    }

    //------------------------------------------------------------------------
    //  Mount disk      B:
    //------------------------------------------------------------------------

    //  Open the primary disk for write & read operations
    disk_io[ 1 ].disk_fd = open( DISK_B, O_RDWR );

    //  Was the open successful ?
    if ( disk_io[ 1 ].disk_fd <= 0 )
    {
        //  NO:     Message and terminate
        printf( "BIOS: bios_boot( ); "
                "Unable to mount DISK 1 [ B: ] (%s)\r\n:", DISK_B );
        perror( "                    " );
    }

    //------------------------------------------------------------------------
    //  Mount disk      C:
    //------------------------------------------------------------------------

    //  Open the primary disk for write & read operations
    disk_io[ 2 ].disk_fd = open( DISK_C, O_RDWR );

    //  Was the open successful ?
    if ( disk_io[ 2 ].disk_fd <= 0 )
    {
        //  NO:     Message and terminate
        printf( "BIOS: bios_boot( ); "
                "Unable to mount DISK 2 [ C: ] (%s)\r\n:", DISK_C );
        perror( "                    " );
    }

    //------------------------------------------------------------------------
    //  Mount disk      D:
    //------------------------------------------------------------------------

    //  Open the primary disk for write & read operations
    disk_io[ 3 ].disk_fd = open( DISK_D, O_RDWR );

    //  Was the open successful ?
    if ( disk_io[ 3 ].disk_fd <= 0 )
    {
        //  NO:     Message and terminate
        printf( "BIOS: bios_boot( ); "
                "Unable to mount DISK 3 [ D: ] (%s)\r\n:", DISK_D );
        perror( "                    " );
    }

    //------------------------------------------------------------------------
    //  Punch
    //------------------------------------------------------------------------

    //  Open the primary disk for write & read operations
    punch_fp = fopen( PUNCH, "a+" );

    //  Was the open successful ?
    if ( punch_fp <= 0 )
    {
        //  NO:     Message and terminate
        printf( "BIOS: bios_boot( ); "
                "Unable to mount paper tape punch (%s)\r\n:", PUNCH );
        perror( "                    " );
    }

    //------------------------------------------------------------------------
    //  Reader
    //------------------------------------------------------------------------

    //  Is the paper tape reader open ?
    if( reader_fp > 0 )
    {
        //  YES:    Close it.
        fclose( reader_fp );
        reader_fp = NULL;
    }

    //------------------------------------------------------------------------
    //  Printer
    //------------------------------------------------------------------------

    //  Open the primary disk for write & read operations
    printer_fp = fopen( PRINTER, "a" );

    //  Was the open successful ?
    if ( printer_fp <= 0 )
    {
        //  NO:     Message and terminate
        printf( "BIOS: bios_boot( ); "
                "Unable to mount printer (%s)\r\n:", PRINTER );
        perror( "                    " );
    }
}

/****************************************************************************/
/**
 *  WBOOT           Warm boot - reload command processor
 *      Reloads the command processor and (on some systems) the BDOS as well.
 *      How it does this is implementation-dependent; it may use the reserved
 *      tracks of a floppy disc or extra memory.
 *
 *  @param
 *
 *  @return                         No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

static
void
bios_wboot(
    void
    )
{
    /**
     *  @param  block_num       The disk block we are reading               */
    int                         block_num;
    /**
     *  @param  dma_ddress      Location to store the BOOT data             */
    int                         dma_address;
    /**
     *  @param  old_disk_id     The previously used DISK-ID                 */
    uint8_t                     old_disk_id;

    //  Log the call
#if DEBUG_MODE
    printf( "===========================================================\r\n" );
    printf( "DEBUG: BIOS call 'WBOOT'\r\n" );
#endif

    //

#if BOOY_FROM_FILE
    //  @NOTE:
    //      This code block is here for debug or emergency recovery of a boot
    //      disk becoming corrupted.  Should that happen, enable the code block
    //      and you will be able to boot from Linux file.
    /**
     *  @param  disk_fd             File Descripter for boot file           */
    int                         disk_fd;

    //  Open the primary disk for write & read operations
    disk_fd = open( CPM_SYS, O_RDONLY );

    //  Was the open successful ?
    if ( disk_fd <= 0 )
    {
        //  NO:     Message and terminate
        printf( "BIOS: bios_wboot( ); "
                "Unable to open CP/M system file [ %s ]\r\n:", CPM_SYS );
        perror( "                     " );
        exit( 0 );
    }

    //  Set the starting address.
    dma_address = CCP_BASE;

    //  Main read loop
    for ( block_num = 0;
          block_num < 44;
          block_num += 1 )
    {
        uint8_t data[ BLOCK_SIZE ];
        memset( data, 0x00, BLOCK_SIZE );

        //  Calculate the logical block address
        //  Seek to the first boot block
        int seek = block_num * BLOCK_SIZE;

        seek = lseek( disk_fd, ( block_num * BLOCK_SIZE ), SEEK_SET );

        //  Read a block from the disk
        seek = read( disk_fd, data, BLOCK_SIZE );

        //  Copy the data block to CPU memory.
        memory_load( dma_address, BLOCK_SIZE, data );

#if DEBUG_MODE
        //  DEBUG
        //      memory_dump( dma_address, 16 );
#endif

        //  Update the DMA address for the next read.
        dma_address += BLOCK_SIZE;
    }

    //  Close the boot file.
    close( disk_fd );
#else

    //  Save the currently selected DISK-ID
    old_disk_id = disk_id;

    //  Select disk 0 (A:) for the boot
    PUT_C( 0 );
    bios_seldsk( );
    disk_io[ disk_id ].disk_parm_tbl = CPU_REG_HL;

    //  Was the selection successful ?
    if ( disk_io[ disk_id ].disk_parm_tbl == 0 )
    {
        //  NO:     OOPS..
        printf( "BIOS: Unable to select boot device\n:" );
        exit( 0 );
    }

    //  Set the starting address.
    dma_address = CCP_BASE;

    //  Main read loop
    for ( block_num = 2;
          block_num < 46;
          block_num += 1 )
    {
        //  Set the track number
        CPU_REG_BC = ( block_num / disk_io[ disk_id ].sec_track );
        bios_settrk( );

#if 0   //  @ToDo   Pick one
        //  @NOTE:  Sector translation
        //  Translate the sector number
        CPU_REG_BC = ( block_num % disk_io[ disk_id ].sec_track );
        CPU_REG_DE = memory_get_16_p( disk_io[ disk_id ].disk_parm_tbl
                                      + DPH_TRANSLATE_OFFSET );
        bios_sectran( );

        //  Set the sector number
        CPU_REG_BC = CPU_REG_HL;
        bios_setsec( );
#else   //  @NOTE:  No sector translation
        //  Set the sector number
        CPU_REG_BC = ( block_num % disk_io[ disk_id ].sec_track );
        bios_setsec( );
#endif

        //  Calculate where this data block is to be stored.
        CPU_REG_BC = dma_address;
        bios_setdma( );

        //  Read a block of data from the disk.
        bios_read( );

        //  Update the DMA address for the next read.
        dma_address += BLOCK_SIZE;
    }
#endif

    //  Change the jump @ 0000h from cold-boot to warm-boot
    memory_put_8( 0x0001, 0x03 );

    //  Was the last drive used a valid DISK-ID ?
    if( old_disk_id <= MAX_DISK )
    {
        //  YES:    Continue using it
        PUT_C( old_disk_id );
    }
    else
    {
        //  NO:     Use the 'A:' drive
        PUT_C( 0 );
    }
}

/****************************************************************************/
/**
 *  CONST           Console status
 *      Returns its status in A; 0 if no character is ready, 0FFh if one is.
 *
 *  @param
 *
 *  @return                         No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

#if CON_V3
#include <sys/ioctl.h>
#elif CON_V2
#include <sys/ioctl.h>
#endif

static
void
bios_const(
    void
    )
{
#if CON_V3
//    PUT_A( 0 );
    /**
     *  @param  bytes               Number of data bytes waiting            */
    unsigned long               bytes;

    //  Initialize the value
    bytes = 0;

    //  NO:     iS THERE KEYBOARD DATA WAITING ?
    if (    ( ioctl( 0, FIONREAD, &bytes ) == 0 )
         && ( bytes                        == 0 ) )
    {
        //  NO:     Set a return code for no data.
        PUT_A( 0 );
    }
    else
    {
        //  YES:    Set a return code for data available.
        PUT_A( 0xFF );
    }
#elif CON_V2
    /**
     *  @param  bytes               Number of data bytes waiting            */
    unsigned long               bytes;

    //  Initialize the value
    bytes = 0;

    //  NO:     iS THERE KEYBOARD DATA WAITING ?
    if (    ( ioctl( 0, FIONREAD, &bytes ) == 0 )
         && ( bytes                        == 0 ) )
    {
        //  NO:     Set a return code for no data.
        PUT_A( 0 );
    }
    else
    {
        //  YES:    Set a return code for data available.
        PUT_A( 0xFF );
    }
#elif CON_V1
    //  Is there any data in the keyboard buffer ?
    if ( strlen( kb_buffer ) > 0 )
    {
        //  YES:    Set a return code for data available.
        PUT_A( 0xFF );
    }
    else
    {
        //  NO:     Try reading to see if there is new data
        kb_read_size = read( 0, kb_buffer, sizeof ( kb_buffer ) );

        if ( kb_read_size != 255 )
        {
            //  YES:    Set a return code for data available.
            PUT_A( 0xFF );
        }
        else
        {
            //  Set a return code for no data.
            PUT_A( 0 );
        }
    }
#endif
}

/****************************************************************************/
/**
 *  p_conin         Physical Consile Input
 *      Wait until the keyboard is ready to provide a character, and return
 *      it in A.
 *
 *  @param
 *
 *  @return                         No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

static
void
p_conin(
    void
    )
{

#if CON_V3
#elif CON_V2
    /**
     *  @param  kb_char             Input character from keyboard           */
    char                        kb_char;

    do
    {
        //  Don't take 100% CPU.  Sleep 100 milliseconds.
        usleep( 100 );

        //  Test for a character typed.
        bios_const( );

        //  Loop if nothing has been typed.
    }   while ( GET_A( ) == 0x00 );

    //  Got a character.  Return it in REG-A.
    kb_char = fgetc( stdin );

    //  Put the character in register A to return to CP/M
    PUT_A( kb_char );

    //  Are we switching to the command processor ?
    if ( kb_char == 0x06 )      //  CTL-F
    {
        //  YES:    The command processor will read the remainder
        cp( );

        //  Get the CP/M command prompt back
        PUT_A( 0x0A );
    }
#elif CON_V1
    //  Sanity check: Is there data in the buffer ?
    if ( strlen( kb_buffer ) > 0 )
    {
        //  Return the first character.
        PUT_A( kb_buffer[ 0 ] );

        //  Left shift the data buffer
        memcpy( &kb_buffer[ 0 ], &kb_buffer[ 1 ], strlen( kb_buffer ) );

        //  Was that the last byte in the buffer ?
        //      if ( strlen( kb_buffer ) == 0 )
        //      {
        //          //  YES:    Flush any stray characters remaining
        //          memset( kb_buffer, '\0', sizeof( kb_buffer ) );

        //  And attempt to read more data
        //          bios_const( );
        //      }
    }
    else
    {
        //  NO:     We need to get something before we return
        do
        {
            //  Get data from the keyboard
            bios_const( );
        } while ( strlen( kb_buffer ) == 0 );

        //  Return the first character.
        PUT_A( kb_buffer[ 0 ] );

        //  Left shift the data buffer
        memcpy( &kb_buffer[ 0 ], &kb_buffer[ 1 ], strlen( kb_buffer ) );
    }
#endif
}

/****************************************************************************/
/**
 *  CONIN           Console input
 *      Wait until the keyboard is ready to provide a character, and return
 *      it in A.
 *
 *  @param
 *
 *  @return                         No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

enum    conin_state_e
{
    CS_IDLE                 =   0,
    CS_1B                   =   1,
    CS_5B                   =   2,
    CS_7E                   =   3
};
    /**
     *  @param  conin_state     Extended character sequence                 */
static
    enum    conin_state_e       conin_state = CS_IDLE;

static
void
bios_conin(
    void
    )
{
#if CON_V3
    /** @param  kb_char         Data from the keyboard                      */
    int                         kb_char;

    do
    {
        //  Read from keyboard
        kb_char = getch( );

    }   while( ( kb_char & 0xFF ) == 0xFFFF );

    //  Character translation
    switch( kb_char )
    {
        case    0x109:          //      F1
            cp( );
            PUT_A( 0x0A );
            break;
        case    0x221:          //      WORD    -   PREVIOUS
            PUT_A( 0x01 );      //                          CTL-A
            break;
        case    0x102:          //      ARROW   -   DOWN
            PUT_A( 0x03 );      //                          CTL-C
            break;
        case    0x105:          //      ARROW   -   RIGHT
            PUT_A( 0x04 );      //                          CTL-D
            break;
        case    0x103:          //      ARROW   -   UP
            PUT_A( 0x05 );      //                          CTL-E
            break;
        case    0x230:          //      WORD    -   NEXT
            PUT_A( 0x06 );      //                          CTL-F
            break;
        case    0x107:          //      BACKSPACE
            PUT_A( 0x08 );      //                          CTL-H
            break;
        case    0x111:          //      FORM FEED
            PUT_A( 0x12 );      //                          CTL-L
            break;
        case    0x00A:          //      ENTER
            PUT_A( 0x0D );      //                          CTL-M
            break;
        case    0x157:          //      RIGHT-ENTER
            PUT_A( 0x0D );      //                          CTL-M
            break;
        case    0x14B:          //      INSERT
            PUT_A( 0x0E );      //                          CTL-N
            break;
        case    0x104:          //      ARROW   -   LEFT
            PUT_A( 0x13 );      //                          CTL-S
            break;
        case    0x153:          //      PAGE    -   UP
            PUT_A( 0x17 );      //                          CTL-W
            break;
        case    0x152:          //      PAGE    -   DOWN
            PUT_A( 0x18 );      //                          CTL-X
            break;
        case    0x14A:          //      DELETE
            PUT_A( 0x7F );      //                          CTL-
            break;
        default:
            PUT_A( kb_char );

#if 0
COMMAND CONTROL CHARACTERS
  C               03h       Reboot - CP/M warm boot
  E               05h       Start new line
  H               08h       Backspace and delete (V2.x)
  I               09h       Tab 8 columns
  J               0Ah       Line feed
  M               0Dh       Carriage return
  P               10h       Printer on/Printer off
  R               12h       Retype current line
  S               13h       Stop display outout (any char except ^C restarts)
  U               15h       Delete line
  X               18h       Same as Û (V1.4)
  Z               1Ah       End of console input (ED & PIP)
#endif

    }
//  printf( "kb_char = %04X - A = %02X\r\n", kb_char, GET_A( ) );
#elif CON_V2
    do
    {
        //  Read another character from the keyboard
        p_conin( );

        //  Set the rules based on the previous character
        switch ( conin_state )
        {
            //----------------------------------------------------------------
            case CS_IDLE:
            {
                //  Start od an extended keyboard string ?
                if ( GET_A( ) == 0x1B )
                {
                    //  YES:    Change state
                    conin_state = CS_1B;
                }
                //  Keyboard backspace to ASCII backspace
                else
                if ( GET_A( ) == 0x7F )
                {
                    //  YES:
                    PUT_A( 0x08 );
                }
            }   break;
            //----------------------------------------------------------------
            case CS_1B:
            {
                //  Start od an extended keyboard string ?
                if ( GET_A( ) == 0x5B )
                {
                    //  YES:    Change state
                    conin_state = CS_5B;
                }
            }   break;
            //----------------------------------------------------------------
            case CS_5B:
            {
                switch( GET_A( ) )
                {
                    case    '5':            //  Page UP
                        PUT_A( 0x00 );
                        break;
                    case    '6':            //  Page DOWN
                        PUT_A( 0x00 );
                        break;
                    case    'H':            //  Page HOME
                        PUT_A( 0x00 );
                        break;
                    case    'F':            //  Page END
                        PUT_A( 0x00 );
                        break;
                    case    'A':            //  Arrow UP
                        PUT_A( 0x05 );
                        break;
                    case    'B':            //  Arrow DOWN
                        PUT_A( 0x16 );
                        break;
                    case    'C':            //  Arrow RIGHT
                        PUT_A( 0x08 );
                        break;
                    case    'D':            //  Arrow LEFT
                        PUT_A( 0x13 );
                        break;
                }
                //  Update the keyboard state
                conin_state = CS_IDLE;

            }   break;
            //----------------------------------------------------------------
            case CS_7E:
            {
            }   break;
        }

    //  Are we done reading a character ?
    }   while ( conin_state != CS_IDLE );
#elif CON_V1
    //  Read another character from the keyboard
    p_conin( );
#endif

#if DEBUG_MODE
    //  Log the call
    printf( "===========================================================\r\n" );
    printf( "DEBUG: BIOS call 'CONIN'-r\n" );
    if ( isprint( GET_C( ) ) )
        printf( "\tCharacter   =  A = x'%02X - '%c'\r\n", GET_A( ), GET_A( ) );
    else
        printf( "\tCharacter   =  A = x'%02X\r\n", GET_A( ) );
#endif
}

/****************************************************************************/
/**
 *  CONOUT          Console output
 *      Write the character in C to the screen.
 *
 *  @param
 *
 *  @return                         No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

static
void
bios_conout(
    void
    )
{
#if DEBUG_MODE
    //  Log the call
    printf( "===========================================================\r\n" );
    printf( "DEBUG: BIOS call 'CONOUT'-r\n" );
    if ( isprint( GET_C( ) ) )
        printf( "\tCharacter   =  C = x'%02X - '%c'\r\n", GET_C( ), GET_C( ) );
    else
        printf( "\tCharacter   =  C = x'%02X\r\n", GET_C( ) );
#endif

    //  Write a single character
    fputc( GET_C( ), stdout);

    //  Update the display for each and every character.
    fflush( stdout );
}

/****************************************************************************/
/**
 *  LIST            Printer output
 *      Write the character in C to the printer. If the printer isn't ready,
 *      wait until it is.
 *
 *  @param
 *
 *  @return                         No information is returned from this function.
 *
 *  @note
 *      @ToDo   BIOS-LIST
 *
 ****************************************************************************/

static
void
bios_list(
    void
    )
{
#if DEBUG_MODE
    //  Log the call
    printf( "===========================================================\r\n" );
    printf( "DEBUG: BIOS call 'LIST'\r\n" );
    if ( isprint( GET_C( ) ) != 0 )
        printf( "       C = Char = '%c'\r\n", GET_C( ) );
    else
        printf( "       C = Char = 'x'%02X'\r\n", GET_C( ) );
#endif

    //  Write a single character
    putc( (int)GET_C( ), printer_fp );

    //  Update the display for each and every character.
    fflush( printer_fp );
}

/****************************************************************************/
/**
 *  PUNCH           Paper tape punch output
 *      Write the character in C to the "paper tape punch" - or whatever the
 *      current auxiliary device is. If the device isn't ready, wait until it
 *      is.
 *      This function is called PUNCH in CP/M 2.x, AUXOUT in CP/M 3.
 *
 *  @param
 *
 *  @return                         No information is returned from this function.
 *
 *  @note
 *      @ToDo   BIOS-PUNCH
 *
 ****************************************************************************/

static
void
bios_punch(
    void
    )
{
#if DEBUG_MODE
    //  Log the call
    printf( "===========================================================\r\n" );
    printf( "DEBUG: BIOS call 'PUNCH'\r\n" );
    if ( isprint( GET_C( ) ) != 0 )
        printf( "       C = Char = '%c'\r\n", GET_C( ) );
    else
        printf( "       C = Char = 'x'%02X'\r\n", GET_C( ) );
#endif

    //  Write a single character
    fputc( GET_C( ), punch_fp );

    //  Update the display for each and every character.
    fflush( punch_fp );
}

/****************************************************************************/
/**
 *  READER      Paper tape reader input
 *      Read a character from the "paper tape reader" - or whatever the current
 *      auxiliary device is. If the device isn't ready, wait until it is. The
 *      character will be returned in A. If this device isn't implemented,
 *      return character 26 (^Z).
 *      This function is called READER in CP/M 2.x, AUXIN in CP/M 3.
 *
 *  @param
 *
 *  @return                         No information is returned from this function.
 *
 *  @note
 *      @ToDo   BIOS-READER
 *
 ****************************************************************************/

static
void
bios_reader(
    void
    )
{
    /**
     *  @param  rdr_c           Character from the reader                   */
    uint8_t                     rdr_c;

#if DEBUG_MODE
    //  Log the call
    printf( "===========================================================\r\n" );
    printf( "DEBUG: BIOS call 'READER'\r\n" );
#endif

    //------------------------------------------------------------------------
    //  Open the device as necessary
    //------------------------------------------------------------------------

    //  Is the reader already opened ?
    if( reader_fp == NULL )
    {
        //  NO:     Open it.
        reader_fp = fopen( READER, "a+" );

        //  Was the open successful ?
        if ( reader_fp == NULL )
        {
            //  NO:     Message and terminate
            printf( "BIOS: bios_boot( ); "
                    "Unable to mount paper tape reader (%s)\r\n:", PUNCH );
            perror( "                    " );
            printf( "\r\n" );
        }
    }

    //------------------------------------------------------------------------
    //  Read, Process and Return a byte of data.
    //------------------------------------------------------------------------

    //  Read a character from the reader
    rdr_c = fgetc( reader_fp );

    //  Was there something to read ?
    if( rdr_c == 0xFF )
    {
        //  NO:     Default character is 'EOF'
        rdr_c = 0x1A;

        //  And close the device
        fclose( reader_fp );
        reader_fp = NULL;
    }

    //  Put the read character in register 'A'
    PUT_A( rdr_c );

#if DEBUG_MODE
    printf( "\t\tREG-A = %02X\r\n", rdr_c );
#endif
}

/****************************************************************************/
/**
 *  LISTST          Status of list device
 *      Return status of current printer device.
 *
 *      Returns A=0 (not ready) or A=0FFh (ready).
 *
 *  @param
 *
 *  @return                         No information is returned from this function.
 *
 *  @note
 *      @ToDo   BIOS-LISTST
 *
 ****************************************************************************/

static
void
bios_listst(
    void
    )
{
#if DEBUG_MODE
    //  Log the call
    printf( "===========================================================\r\n" );
    printf( "DEBUG: BIOS call 'LISTST'\r\n" );
#endif

    //  Is the printer file opened ?
    if( printer_fp < 0 )
    {
        //  NO:     Report NOT READY
        PUT_A( 0 );
    }
    else
    {
        //  YES:    Report READY
        PUT_A( 0xFF );
    }
}

/****************************************************************************
 * MAIN
 ****************************************************************************/

/****************************************************************************/
/**
 *  The emulator has just started.  Configure the system as needed and
 *  start the boot process.
 *
 *  @param
 *
 *  @return                         No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
bios_cfg(
    void
    )
{

    /************************************************************************
     *  Function Initialization
     ************************************************************************/


    /************************************************************************
     *  POST Code
     ************************************************************************/


    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  Start the boot process.
    boot_eeprom( 0 );
}

/****************************************************************************/
/**
 *  FooBar Power On Self Test
 *
 *  @param
 *
 *  @return                         No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
cpm_bios(
    void
    )
{

    /************************************************************************
     *  BIOS Function Decode
     ************************************************************************/

    //
    switch( CPU_REG_PC )
    {
        case    ( BOOT_VECTOR + 2 ):            //  F200    BOOT
        {
            //  Initialize memory
            memory_init( );

            //  Rebuild key memory locations
            boot_eeprom( 0 );

            //  Start with the cold boot sequence
            bios_boot( );
        }   //  Falls through to run warm boot
        case    ( WBOOT_VECTOR + 2 ):           //  F203    WBOOT
        {
            bios_wboot( );

            //  Initialize all CPU registers
            CPU_REG_DE = 0;
            CPU_REG_HL = 0;
            CPU_REG_I  = 0;
            CPU_REG_R  = 0;
            CPU_REG_PC = CCP_BASE;

        }   break;
        case    ( CONST_VECTOR + 2 ):               //  F206    CONST
        {
#if DEBUG_MODE
            //  Log the call
            printf( "===========================================================\r\n" );
            printf( "DEBUG: BIOS call 'CONST'\r\n" );
#endif
            bios_const( );
#if DEBUG_MODE
            printf( "\tReturn Code =  A = x'%02X\r\n", GET_A( ) );
#endif
        }   break;
        case    ( CONIN_VECTOR + 2 ):               //  F209    CONIN
        {
#if DEBUG_MODE
            //  Log the call
            printf( "===========================================================\r\n" );
            printf( "DEBUG: BIOS call 'CONIN'\r\n" );
#endif

            bios_conin( );
#if DEBUG_MODE
            if ( isprint( GET_A( ) ) )
                printf( "\tReturn      =  A = x'%02X - '%c'\r\n", GET_A( ), GET_A( ) );
            else
                printf( "\tReturn      =  A = x'%02X\r\n", GET_A( ) );
#endif
        }   break;
        case    ( CONOUT_VECTOR + 2 ):              //  F20C    CONOUT
        {
            bios_conout( );
        }   break;
        case    ( LIST_VECTOR + 2 ):                //  F20F    LIST
        {
            bios_list( );
        }   break;
        case    ( PUNCH_VECTOR + 2 ):               //  F212    PUNCH
        {
            bios_punch( );
        }   break;
        case    ( READER_VECTOR + 2 ):              //  F215    READER
        {
            bios_reader( );
        }   break;
        case    ( HOME_VECTOR + 2 ):                //  F218    HOME
        {
            bios_home( );
        }   break;
        case    ( SELDSK_VECTOR + 2 ):              //  F21B    SELDSK
        {
            bios_seldsk( );
        }   break;
        case    ( SETTRK_VECTOR + 2 ):              //  F21E    SETTRK
        {
            bios_settrk( );
        }   break;
        case    ( SETSEC_VECTOR + 2 ):              //  F221    SETSEC
        {
            bios_setsec( );
        }   break;
        case    ( SETDMA_VECTOR + 2 ):              //  F224    SETDMA
        {
            bios_setdma( );
        }   break;
        case    ( READ_VECTOR + 2 ):                //  F227    READ
        {
            bios_read( );
        }   break;
        case    ( WRITE_VECTOR + 2 ):               //  F22A    WRITE
        {
            bios_write( );
        }   break;
        case    ( LISTST_VECTOR + 2 ):              //  F22D    LISTST
        {
            bios_listst( );
        }   break;
        case    ( SECTRAN_VECTOR + 2 ):             //  F230    SECTRAN
        {
            bios_sectran( );
        }   break;
        default:
        {
            printf( "Unknown BIOS vector address x'%04X\r\n", CPU_REG_PC );
        };
    }

    /************************************************************************
     *  POST Code
     ************************************************************************/

    fflush(stdout);

    /************************************************************************
     *  Function Exit
     ************************************************************************/
}

/****************************************************************************/
/**
 *  Eject
 *
 *  @param  drive_num           Number reflecting the drive letter A=1 etc
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
bios_eject(
    int                         drive_num
    )
{
    //  Is this disk opened ?
    if ( disk_io[ drive_num ].disk_fd > 0 )
    {
        //  YES:    Close it
        close( disk_io[ drive_num ].disk_fd );

        //  Mark it as closed
        disk_io[ drive_num ].disk_fd = -1;
    }
    else
    {
        //  Error Message
        printf( "\r\nCP EJECT: Failed because nothing is mounted\r\n" );
    }
}

/****************************************************************************/
/**
 *  mount
 *
 *  @param  drive_num           Number reflecting the drive letter A=1 etc
 *  @param  file_name           File name of disk image to be mounted.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
bios_mount(
    int                         drive_num,
    char                    *   file_name
    )
{
    //  Is this disk opened ?
    if ( drive_num < MAX_DISK )
    {
        if ( disk_io[ drive_num ].disk_fd == -1 )
        {
            //  Open the primary disk for write & read operations
            disk_io[ drive_num ].disk_fd = open( file_name, O_RDWR );

            //  Was the open successful ?
            if ( disk_io[ drive_num ].disk_fd <= 0 )
            {
                //  NO:     Message and terminate
                printf( "\r\nCP MOUNT: Unable to open file '%s'\r\n:", file_name );
                perror(   "          " );
            }
        }
        else
        {
            //  Error Message
            printf( "\r\nCP MOUNT: Drive %c: is already mounted\r\n", ( ( drive_num + 1 ) | '@' ) );
        }
    }
    else
    {
        //  Error Message
        printf( "\r\nCP MOUNT: Drive %c: is not a valid drive letter.\r\n", ( ( drive_num + 1 ) | '@' ) );
    }
}

/****************************************************************************/
/**
 *  This functin is only called when shutting the system down.
 *
 *  @param  void
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
bios_shutdown(
    void
    )
{
    //  Shutdown the curses interface
    endwin( );

    //  Close the disk drives
    if( disk_io[ 0 ].disk_fd != -1 );
        close( disk_io[ 0 ].disk_fd );
    if( disk_io[ 1 ].disk_fd != -1 );
        close( disk_io[ 1 ].disk_fd );
    if( disk_io[ 1 ].disk_fd != -1 );
        close( disk_io[ 2 ].disk_fd );
    if( disk_io[ 1 ].disk_fd != -1 );
        close( disk_io[ 3 ].disk_fd );
}
/****************************************************************************/