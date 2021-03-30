/*******************************  COPYRIGHT  ********************************/
/*
 *  Author? "Gregory N. Leonhardt"
 *  License? "CC BY-NC 2.0"
 *           "https://creativecommons.org/licenses/by-nc/2.0/"
 *
 ****************************************************************************/

/******************************** JAVADOC ***********************************/
/**
 *  Copy Linux files to a CP/M disk image.
 *
 *  @note
 *      cp_to_cpm   {filename} {disk_image}
 *
 *      {file_name}     is the full directory/file name to be copied
 *      {disk_image}    is the full directory/file name of a CP/M disk image.
 *
 ****************************************************************************/

/****************************************************************************
 *  Compiler directives
 ****************************************************************************/

#define     DEBUG_TYPE          0

/****************************************************************************
 * System Function
 ****************************************************************************/

                                //*******************************************
#include <stdbool.h>            //  TRUE, FALSE, etc.
#include <stdint.h>             //  Alternative storage types
#include <stdlib.h>             //  ANSI standard library.
#include <unistd.h>             //  UNIX standard library.
#include <stdio.h>              //  Standard I/O definitions
#include <string.h>             //  Character & String management
#include <fcntl.h>              //  File constructs
#include <ctype.h>              //  Testing and mapping characters
#include <sys/stat.h>           //  Get file status
#include <sys/types.h>          //  Defines data types used in system source
                                //*******************************************

/****************************************************************************
 * Application Functions
 ****************************************************************************/

                                //*******************************************
#include "libtools_api.h"       //  My Tools Library
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
#define BLOCK_SIZE              ( 8192 )
#define RECORD_SIZE             (  128 )
#define MAX_BLOCK               ( 1016 )
#define FCB_MAX_NDX             (   32 )
#define FCB_DAB_MAX             (    8 )
#define BLOCKS_PER_TRACK        (    6 )
#define DIRECTORY_SIZE          (    2 )
//----------------------------------------------------------------------------
#define FCB_SIZE                ( sizeof( struct fcb_t ) )
//----------------------------------------------------------------------------

/****************************************************************************
 * Structures
 ****************************************************************************/

//----------------------------------------------------------------------------
struct  fcb_t
{
    /**
     *  @param  dr              Drive Code  0=Default, 1=A:, 2=B:, 16=P:    */
    uint8_t                     dr;
    /**
     *  @param  fn              Upper case ASCII file name                  */
    uint8_t                     fn[ 8 ];
    /**
     *  @param  ft              Upper case ASCII file type                  */
    uint8_t                     ft[ 3 ];
    /**
     *  @param  ex              Extent number     (00-31)                   */
    uint8_t                     ex;
    /**
     *  @param  s1              ???????????????????????????                 */
    uint8_t                     s1;
    /**
     *  @param  s2              ???????????????????????????                 */
    uint8_t                     s2;
    /**
     *  @param  rc              Number of 128 byte records                  */
    uint8_t                     rc;
    /**
     *  @param  dab             Disk Allocation Blocks                      */
    uint16_t                    dab[ 8 ];
};
//----------------------------------------------------------------------------

/****************************************************************************
 * Storage Allocation
 ****************************************************************************/

//----------------------------------------------------------------------------
/**
 *  @param  src_fd          Source file descriptor                          */
char                        src_fd;
/**
 *  @param  dst_fd          Destination file descriptor                     */
char                        dst_fd;
/**
 *  @param  dir_list        Link list of the CP/M disk directory            */
struct  list_base_t     *   dir_list_p;
/**
 *  @param  disk_buf        A place to put write or read data               */
uint8_t                     data_buf[ BLOCK_SIZE ];
/**
 *  @param  dir_buf         A place to put directory write or read data     */
uint8_t                     dir_buf[ BLOCK_SIZE ];
/**
 *  @param  f_name          Source/Destination file name                    */
char                        f_name[ 9 ];
/**
 *  @param  f_type          Source/Destination file type                    */
char                        f_type[ 4 ];
/**
 *  @param  record_count    Number of 128 byte records written              */
int                         record_count;
/**
 *  @param  used_blocks     A map of used and unused disk blocks            */
uint16_t                    used_blocks[ MAX_BLOCK ];
/**
 *  @param  file_blocks     A map of blocks used for this write.            */
char                        file_blocks[ 128 ];
/**
 *  @param  statbuf         File statistics data                            */
struct  stat                statbuf;
/**
 *  @param  file_fcb        FCB for the source file                         */
struct  fcb_t               file_fcb;
//----------------------------------------------------------------------------

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************/
/**
 *  Memory dump for debug
 *
 *  @param  address_p           Pointer to dump area
 *  @param  data_l              Dump size
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
debug_dump(
    unsigned char           *   address_p,
    int                         data_l
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
          ndx < data_l;
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
            printf( "\n%04X - ", ndx );
        }
        if ( ( ndx % 4 ) == 0 )
        {
            printf( " " );
        }
        if ( ( ndx % 8 ) == 0 )
        {
            printf( " " );
        }

        c = address_p[ ndx ];

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
 *  Search the directory list for a file name match.
 *
 *  @param  void
 *
 *  @return func_rc             TRUE if the file exists, else FALSE
 *
 *  @note
 *
 ****************************************************************************/

int
if_exists(
    )
{
    /**
     *  @param  ndx             Index into memory                           */
    int                         func_rc;
    /**
     *  @param  ndx             Index into memory                           */
    char                        filename[ 12 ];
    /**
     *  @param  fcb_p           Pointer to a File Control Block             */
    struct  fcb_t           *   fcb_p;

    //  Set the default value to NO match
    func_rc = false;

    //  Build the whole filename.type
    memset( filename, '\0', sizeof( filename ) );
    memcpy( filename,       f_name, 8 );
    memcpy( &filename[ 8 ], f_type, 3 );

    //  Loop looking for a match
    for( fcb_p = list_get_first( dir_list_p );
         fcb_p != NULL;
         fcb_p = list_get_next( dir_list_p, fcb_p ) )
    {
        //  Is this a match for the filename.type we are looking for ?
        if ( strncmp( &fcb_p->fn[ 0 ], filename, 11 ) == 0 )
        {
            //  Found an exact match
            func_rc = true;
            break;
        }
    }

    return( func_rc );
}

/****************************************************************************/
/**
 *  Read a data block from the disk
 *
 *  @param  block_num           Block number to read
 *  @param  data_p              Pointer to the write data buffer
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
disk_read(
    int                         block_num,
    uint8_t                 *   data_p
    )
{
    /**
     *  @param  seek_offset     Current seek position                       */
    int                         seek_offset;
    /**
     *  @param  bytes_read      Number of bytes read from the file          */
    int                         bytes_read;

    //  Seek to the data block
    seek_offset = lseek( dst_fd,
                        ( BLOCK_SIZE * ( block_num + BLOCKS_PER_TRACK ) ),
                        SEEK_SET );

    //  Successful ?
    if ( seek_offset != ( BLOCK_SIZE * ( block_num + BLOCKS_PER_TRACK ) ) )
    {
        //  Not good..
        printf( "disk_read( ):  Seek failure on block %04X.\n", block_num );
        exit( -1 );
    }

    //  Read a block from the disk
    bytes_read = read( dst_fd, data_p, BLOCK_SIZE );

    //  Successful ?
    if ( bytes_read != BLOCK_SIZE )
    {
        //  NO:     Not good..
        printf( "disk_read( ):  Read failure on block %04X.\n", block_num );
        printf( "               Requested:            %04X.\n", BLOCK_SIZE );
        printf( "               Received :            %04X.\n", (int)bytes_read );
        perror( "\t" );
        exit( -1 );
    }
}

/****************************************************************************/
/**
 *  Write a data block to the disk
 *
 *  @param  block_num           Block number to read
 *  @param  data_p              Pointer to the write data buffer
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
disk_write(
    int                         block_num,
    uint8_t                 *   data_p
    )
{
    /**
     *  @param  seek_offset     Current seek position                       */
    int                         seek_offset;
    /**
     *  @param  bytes_written   Number of bytes written to the file         */
    int                         bytes_written;

    //  Seek to the data block
    seek_offset = lseek( dst_fd,
                        ( BLOCK_SIZE * ( block_num + BLOCKS_PER_TRACK ) ),
                        SEEK_SET );

    //  Successful ?
    if ( seek_offset != ( BLOCK_SIZE * ( block_num + BLOCKS_PER_TRACK ) ) )
    {
        //  Not good..
        printf( "disk_write( ):  Seek failure on block %04X.\n", block_num );
        exit( -1 );
    }

    //  Read a block from the disk
    bytes_written = write( dst_fd, data_p, BLOCK_SIZE );

    //  Successful ?
    if ( bytes_written != BLOCK_SIZE )
    {
        //  NO:     Not good..
        printf( "disk_write( ):  Read failure on block %04X.\n", block_num );
        printf( "                Requested:            %04X.\n", BLOCK_SIZE );
        printf( "                Received :            %04X.\n", (int)bytes_written );
        perror( "\t" );
        exit( -1 );
    }
}

/****************************************************************************/
/**
 *  Read the entire directory of the destination CP/M disk image
 *
 *  @param  void
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
read_dir(
    )
{
    /**
     *  @param  block_num       Current disk block number                   */
    int                         block_num;
    /**
     *  @param  fcb_ndx         FCB index in the directory block            */
    int                         fcb_ndx;
    /**
     *  @param  fcb_p           Pointer to a File Control Block             */
    struct  fcb_t           *   fcb_p;

    //  Create a new list for the disk directory
    dir_list_p = list_new( );

    //  Disk read loop
    for( block_num = 0;
         block_num < DIRECTORY_SIZE;
         block_num += 1 )
    {
        //  Read data from the disk
        disk_read( block_num, dir_buf );

        //  Loop through all FCBs in this directory block
        for( fcb_ndx = 0;
             fcb_ndx < ( BLOCK_SIZE / sizeof( struct fcb_t  ) );
             fcb_ndx += 1 )
        {
            //  Is this FCB in use ?
            if ( ( dir_buf + ( FCB_SIZE * fcb_ndx ) )[ 0 ] == 0x00 )
            {
                //  YES:    Allocate memory for a new FCB
                fcb_p = mem_malloc( sizeof( struct fcb_t ) );

                //  Copy the FCB
                memcpy( fcb_p, ( dir_buf + ( FCB_SIZE * fcb_ndx ) ), FCB_SIZE );

                //  Add it to the list
                if ( list_put_last( dir_list_p, fcb_p ) != true )
                {
                    //  System failure
                    printf( "read_dir: Internal failure adding to list\n" );
                    exit( -1 );
                }
#if DEBUG_TYPE != 0
                //  @DEBUG
                debug_dump( (unsigned char*)fcb_p, sizeof( struct fcb_t ) );
#endif
            }
        }
    }
}

/****************************************************************************/
/**
 *  Read the entire directory of the destination CP/M disk image
 *
 *  @param  void
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
map_used_blocks(
    )
{
    /**
     *  @param  fcb_p           Pointer to a File Control Block             */
    struct  fcb_t           *   fcb_p;
    /**
     *  @param  block_ndx       Index into the FCB block list               */
    int                         block_ndx;
    /**
     *  @param  block_num       The current allocation block                */
    int                         block_num;

    //  Assume the disk block is NOT used
    memset( used_blocks, 0xFF, sizeof( used_blocks ) );

    //  Block 0 and 1 are used by the directory.
    used_blocks[ 0 ] = 0;
    used_blocks[ 1 ] = 0;

    for( fcb_p = list_get_first( dir_list_p );
         fcb_p != NULL;
         fcb_p = list_get_next( dir_list_p, fcb_p ) )
    {
        //  Loop through all allocation blocks for this FCB
        for( block_ndx = 0;
             block_ndx < 8;
             block_ndx += 1 )
        {
            //  Get the block number
            //  @NOTE: It is stored reverse (low,high)
            block_num = fcb_p->dab[ block_ndx ];

            //  Is there an allocated block ?
            if ( block_num != 0 )
            {
                //  YES:    Mark it "IN-USE"
                used_blocks[ block_num ] = 0;
            }
        }
    }
}

/****************************************************************************/
/**
 *  Insert the FCB into the directory structure
 *
 *  @param  void
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
insert_fcb(
    )
{
    /**
     *  @param  block_num       Current disk block number                   */
    int                         block_num;
    /**
     *  @param  fcb_ndx         FCB index in the directory block            */
    int                         fcb_ndx;
    /**
     *  @param  block_ndx       File Control Block block index              */
    int                         block_ndx;
    /**
     *  @param  done            Done writing everything                     */
    int                         done;

    //  We haven't started so we can't possibly be done yet.
    done = false;

    /************************************************************************
     *  Set EX and RC
     ************************************************************************/

    //  Are we on an extent boundary ?
    if ( ( record_count % 0x0080 ) == 0 )
    {
        //  YES:    Leave one extent worth in the record count
        file_fcb.rc = 0x80;
        file_fcb.ex = ( record_count - 1 ) / 0x0080;
    }
    else
    {
        //  NO:     Just set the numbers
        file_fcb.rc = record_count % 0x0080;
        file_fcb.ex = record_count / 0x0080;
    }

    /************************************************************************
     *  Locate an unused FCB and use it
     ************************************************************************/

    //  Disk read loop
    for( block_num = 0;
         block_num < DIRECTORY_SIZE && done == false;
         block_num += 1 )
    {
        //  Read data from the disk
        disk_read( block_num, dir_buf );

        //  Loop through all FCBs in this directory block
        for( fcb_ndx = 0;
             fcb_ndx < ( BLOCK_SIZE / sizeof( struct fcb_t  ) );
             fcb_ndx += 1 )
        {
            //  Is this FCB in use ?
            if ( ( dir_buf + ( FCB_SIZE * fcb_ndx ) )[ 0 ] == 0xE5 )
            {
                //  NO:     Replace it with this one
                memcpy( ( dir_buf + ( FCB_SIZE * fcb_ndx ) ), &file_fcb, FCB_SIZE );

                //  Write the directory block back to the disk.
                disk_write( block_num, dir_buf );

                //  That's it.
                done = true;
                break;
            }
        }
    }

    //  Is the directory full ?
    if ( block_num == DIRECTORY_SIZE )
    {
        //  YES:    Let the user know
        printf( "insert_fcb( ): The CP/M directory is full.\n" );
        exit( -1 );
    }

    /************************************************************************
     *  Prepare the File Control Block for the next extent.
     ************************************************************************/

    //  Loop for each block number in the FCB
    for( block_ndx = 0;
         block_ndx < FCB_DAB_MAX;
         block_ndx += 1 )
    {
        //  Zero it out
        file_fcb.dab[ block_ndx ] = 0;
    }
}

/****************************************************************************/
/**
 *  Locate an empty block and write the buffered data to it.
 *
 *  @param  bytes_to_write      The number of bytes to write to the CP/M disk
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
cpm_write(
    int                         bytes_to_write
    )
{
    /**
     *  @param  search_ndx      Search for available block index            */
    int                         search_ndx;
    /**
     *  @param  fcb_block_ndx   File Control Block block index              */
    int                         fcb_dab_ndx;

    //  Is all the data written ?
    if ( bytes_to_write == 0 )
    {
        //  YES:    Insert the File Control Block into the directory structure
        insert_fcb( );
    }
    else
    {
        //  NO:     Loop through each data block
        for( fcb_dab_ndx = 0;
             fcb_dab_ndx < FCB_DAB_MAX;
             fcb_dab_ndx += 1 )
        {
            //  Is this block already have a data block ?
            if ( file_fcb.dab[ fcb_dab_ndx ] == 0 )
            {
                //  NO:     Use this one
                break;
            }
        }

        //  Are all the Data Allocation Blocks in use ?
        if ( fcb_dab_ndx == FCB_DAB_MAX )
        {
            //  YES:    Insert the File Control Block into the directory structure
            insert_fcb( );

            //  Starting over.
            fcb_dab_ndx = 0;
        }

        //  Look for an available block number
        for( search_ndx = 0;
             search_ndx < MAX_BLOCK;
             search_ndx += 1 )
        {
            //  Is this block "IN-USE" ?
            if ( used_blocks[ search_ndx ] == 0xFFFF )
            {
                //  NO:     Mark it "IN-USE"
                used_blocks[ search_ndx ] = 0;

                //  Add the block to the FCB
                //  @NOTE: It is stored reverse (low,high)
                file_fcb.dab[ fcb_dab_ndx ] = search_ndx;

                //  Write the data to the CP/M disk
                disk_write( search_ndx, data_buf );

                //  Exact size of a record
                if ( ( bytes_to_write % RECORD_SIZE ) == 0 )
                {
                    //  YES:    Update the record count
                    record_count += ( bytes_to_write / RECORD_SIZE );

                    //  The data is written and the FCB updated
                    break;
                }
                else
                {
                    //  NO:     Update the record count
                    record_count += ( bytes_to_write / RECORD_SIZE ) + 1;

                    //  The data is written and the FCB updated
                    break;
                }
            }
        }

        //  Is the disk full ?
        if ( search_ndx == MAX_BLOCK )
        {
            //  YES:    Let the user know
            printf( "cpm_write( ): The CP/M disk is full.\n" );
            exit( -1 );
        }
    }
}

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
    int                         argc,
    char                    *   argv[ ]
    )
{
    /**
     *  @param  src_p           Source file name pointer                    */
    char                    *   src_p;
    /**
     *  @param  dst_p           Destination file name pointer               */
    char                    *   dst_p;
    /**
     *  @param  tmp_name_p      Temporary file name pointer                 */
    char                    *   tmp_name_p;
    /**
     *  @param  tmp_type_p      Temporary file type pointer                 */
    char                    *   tmp_type_p;
    /**
     *  @param  tmp_ndx         Temporary index counter                     */
    int                         tmp_ndx;
    /**
     *  @param  bytes_read      Number of source file bytes read            */
    int                         bytes_read;
    /**
     *  @param  file_rc         Return Code                                 */
    int                         file_rc;

    /************************************************************************
     *  Command line parameters
     ************************************************************************/

#if DEBUG_TYPE != 0
    src_p = "cpm22.asm";
    dst_p = "/home/greg/CPM/DiskImages/test.img";
#else
    //  Does the source and destination file names exist ?
    if ( argc < 3 )
    {
        //  NO:     A little help please:
        printf( "Missing parameter, please try:\n" );
        printf( "   cp_to_cpm (file) (image)\n" );
        printf( "\n" );
        printf( "Where:\n" );
        printf( "   {file_name}     is the full directory/file name to "
                "be copied\n" );
        printf( "   {disk_image}    is the full directory/file name of "
                "a CP/M disk image.\n" );
        exit( -1 );
    }
    //  Set the source file pointer
    src_p = argv[ 1 ];

    //  Set the destination file pointer
    dst_p = argv[ 2 ];
#endif

    /************************************************************************
     *  Open the source file
     ************************************************************************/

    //  Open for read.
    src_fd = open( src_p, O_RDONLY );

    //  Successful open ?
    if ( src_fd < 0 )
    {
        //  NO:     Some help
        printf( "Unable to open source file '%s'\n", src_p );
        perror( "\t" );
        exit( -1 );
    }

    /************************************************************************
     *  Open the destination file
     ************************************************************************/

    //  Open for write.
    dst_fd = open( dst_p, O_RDWR );

    //  Successful open ?
    if ( src_fd < 0 )
    {
        //  NO:     Some help
        printf( "Unable to open destination file '%s'\n", dst_p );
        perror( "\t" );
        exit( -1 );
    }

    /************************************************************************
     *  Initialize the file name & type buffers.
     ************************************************************************/

    //  Set the file name & type to all spaces
    memset( f_name, ' ', sizeof( f_name ) );
    memset( f_type, ' ', sizeof( f_type ) );

    //  NULL terminate the strings
    f_name[ sizeof( f_name ) - 1 ] = '\0';
    f_type[ sizeof( f_type ) - 1 ] = '\0';

    /************************************************************************
     *  Capture the source file name and type
     ************************************************************************/

    //  Copy the name to a my buffer
    strncpy( data_buf, src_p, sizeof( data_buf ) );

    //  Isolate the directory path from the file name
    tmp_name_p = ( strrchr( data_buf, '/' ) );

    //  Is there a directory path preceding the file name ?
    if ( tmp_name_p == NULL )
    {
        //  NO:     The tmp_name_p is used from here on.
        tmp_name_p = data_buf;
    }
    else
    {
        //  Point past the search character '/'
        tmp_name_p += 1;
    }

    //  Is there a file type ?
    tmp_type_p = strchr( tmp_name_p, '.' );

    //  Will the file name fit into the file name buffer ?
    if( tmp_type_p != NULL )
    {
        //  NULL terminate the file name string
        tmp_type_p[ 0 ] = 0;

        //  And point to the first character of 'file type'
        tmp_type_p += 1;

        //  Will the file name fit into the buffer ?
        if (    ( strlen( tmp_name_p ) > sizeof( f_name ) )
             || ( strlen( tmp_type_p ) > sizeof( f_type ) ) )
        {
            //  NO:     Needs operator intervention
            printf( "The file name or file type exceed the CP/M requirements.\n" );
            printf( "FileName:'%s', FileType: '%s'\n", f_name, f_type );
            printf( "A file name is limited to eight (8) characters\n" );
            printf( "and a file type is limited to three (3) characters\n" );
            printf( "Please correct the name and/or type and try again\n" );
            exit( -1 );
        }
        else
        {
            //  YES:    Copy the names
            memcpy( f_name, tmp_name_p, strlen( tmp_name_p ) );
            memcpy( f_type, tmp_type_p, strlen( tmp_type_p ) );
        }
    }
    else
    if ( ( strlen( tmp_name_p ) > sizeof( f_name ) ) )
    {
        //  NO:     Needs operator intervention
        printf( "The file name exceed the CP/M requirements.\n" );
        printf( "A file name is limited to eight (8) characters.\n" );
        printf( "Please correct the name and/or type and try again\n" );
        exit( -1 );
    }
    else
    {
        //  YES:    Copy the file name
        memcpy( f_name, tmp_name_p, strlen( tmp_name_p ) );
    }

    /************************************************************************
     *  Transform FileName and FileType to UPPER CASE
     ************************************************************************/

    //  Make the filename & type uppercase
    for( tmp_ndx = 0;
            tmp_ndx < strlen( f_name );
            tmp_ndx += 1 )
    {
        //  Make it UPPER CASE
        f_name[ tmp_ndx ] = toupper( f_name[ tmp_ndx ] );
    }

    //  Make the filename & type uppercase
    for( tmp_ndx = 0;
            tmp_ndx < strlen( f_type );
            tmp_ndx += 1 )
    {
        //  Make it UPPER CASE
        f_type[ tmp_ndx ] = toupper( f_type[ tmp_ndx ] );
    }

    /************************************************************************
     *  Initialize the File Control Block
     ************************************************************************/

    //  Start with an empty FCB
    memset( &file_fcb, 0x00, sizeof( struct fcb_t ) );

    //  Add the file name
    memcpy( file_fcb.fn, f_name, sizeof( file_fcb.fn ) );

    //  Add the file type
    memcpy( file_fcb.ft, f_type, sizeof( file_fcb.ft ) );

    /************************************************************************
     *  Read  and manage the disk directory structure
     ************************************************************************/

    //  Read the directory for the selected disk
    read_dir( );

    //  Does the file already exist on the disk ?
    if( if_exists( ) == true )
    {
        //  YES:    Can't (won't) overwrite the file.
        printf( "File '%s' already exists on the disk.\n", src_p );
        printf( "This program will NOT overwrite existing files!\n" );
        exit( -1 );
    }

    //  Map out the used disk blocks
    map_used_blocks( );

    /************************************************************************
     *  Get statistics from the source file.
     ************************************************************************/

    //  Get statistics for the file name
    file_rc = stat( src_p, &statbuf );

    //  Were we successful at getting the statistics data ?
    if ( file_rc != -1 )
    {
        //  YES:    File Size
        if ( statbuf.st_size < 1000 )
        {
            printf( "Copying\t%ld bytes\tfrom\t'%s:%s'\n",
                    statbuf.st_size, f_name, f_type );
        }
        else
        {
            printf( "Copying\t%ld K bytes\tfrom\t'%s:%s'\n",
                    ( statbuf.st_size / 1000 ), f_name, f_type );
        }
    }

    /************************************************************************
     *  Copy the source file to the destination disk
     ************************************************************************/

    //  First zero extent and record counters
    record_count = 0;

    do
    {
        bytes_read = 0;

        //  Clear the data buffer
        memset( data_buf, 0x1A, sizeof( data_buf ) );

        //  Read some data from the source file.
        bytes_read = read( src_fd, data_buf, BLOCK_SIZE );

        /********************************************************************/
        /*  @NOTE:  Though not an absolute fact there is an assumption      */
        /*          here that there the only partial read will be the       */
        /*          last read.                                              */
        /********************************************************************/

        //  Write the data to the CP/M disk
        cpm_write( bytes_read );

    }   while( bytes_read != 0 );

    /************************************************************************
     *  Function Exit
     ************************************************************************/

    //  Close the open files
    if ( src_fd != -1 )
        close( src_fd );

    if ( dst_fd != -1 )
        close( dst_fd );

    //  Bye.
    return( 0 );
}
/****************************************************************************/