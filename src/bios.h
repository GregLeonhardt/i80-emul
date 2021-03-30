/*******************************  COPYRIGHT  ********************************/
/*
 *  Author? "Gregory N. Leonhardt"
 *  License? "CC BY-NC 2.0"
 *           "https://creativecommons.org/licenses/by-nc/2.0/"
 *
 ****************************************************************************/

#ifndef BIOS_H
#define BIOS_H

/******************************** JAVADOC ***********************************/
/**
 *  This file contains definitions (etc.) for the CPU registers.
 *
 *  @note
 *
 ****************************************************************************/

/****************************************************************************
 *  Compiler directives
 ****************************************************************************/

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

/****************************************************************************
 * System APIs
 ****************************************************************************/

                                //*******************************************
                                //*******************************************

/****************************************************************************
 * Application APIs
 ****************************************************************************/

                                //*******************************************
                                //*******************************************

/****************************************************************************
 * Definitions
 ****************************************************************************/

//----------------------------------------------------------------------------
#define RST_0_ADDRESS           0x0000
#define BOOT_BASE               0x0080
#define CCP_BASE                0xDC00
#define BDOS_BASE               0xE400
#define BIOS_BASE               0xF200
//----------------------------------------------------------------------------
#define BOOT_VECTOR             ( BIOS_BASE )
#define WBOOT_VECTOR            ( BOOT_VECTOR   + 3 )
#define CONST_VECTOR            ( WBOOT_VECTOR  + 3 )
#define CONIN_VECTOR            ( CONST_VECTOR  + 3 )
#define CONOUT_VECTOR           ( CONIN_VECTOR  + 3 )
#define LIST_VECTOR             ( CONOUT_VECTOR + 3 )
#define PUNCH_VECTOR            ( LIST_VECTOR   + 3 )
#define READER_VECTOR           ( PUNCH_VECTOR  + 3 )
#define HOME_VECTOR             ( READER_VECTOR + 3 )
#define SELDSK_VECTOR           ( HOME_VECTOR   + 3 )
#define SETTRK_VECTOR           ( SELDSK_VECTOR + 3 )
#define SETSEC_VECTOR           ( SETTRK_VECTOR + 3 )
#define SETDMA_VECTOR           ( SETSEC_VECTOR + 3 )
#define READ_VECTOR             ( SETDMA_VECTOR + 3 )
#define WRITE_VECTOR            ( READ_VECTOR   + 3 )
#define LISTST_VECTOR           ( WRITE_VECTOR  + 3 )
#define SECTRAN_VECTOR          ( LISTST_VECTOR + 3 )
//----------------------------------------------------------------------------
#define SXT_BASE                ( BIOS_BASE + 0x0080 )
#define SXT_SIZE                ( sizeof( sec_xlate_tbl ) )
//----------------------------------------------------------------------------
#define DPH_BASE                ( BIOS_BASE + 0x0100 )
#define DPH_TRANSLATE_OFFSET     0
#define DPH_DIRBUF_OFFSET        8
#define DPH_DPB_OFFSET          10
#define DPH_CHK_OFFSET          12
#define DPH_ALL_OFFSET          14
#define DPH_SIZE                16
#define DPH_BASE_SIZE           ( sizeof( dph ) )
//----------------------------------------------------------------------------
#define DPB_BASE                ( BIOS_BASE + 0x0180 )
#define DPB_SPT_OFFSET           0
#define DPB_BSF_OFFSET           2
#define DPB_MASK_OFFSET          3
#define DPB_NULL_OFFSET          4
#define DPB_SIZE_OFFSET          5
#define DPB_DIRMAX_OFFSET        7
#define DPB_ALL0_OFFSET          9
#define DPB_ALL1_OFFSET         10
#define DPB_CS_OFFSET           11
#define DPB_TO_OFFSET           13
#define DPB_SIZE                ( sizeof( dpb ) )
#define BOOT_SIZE               ( sizeof( bdos_init ) )
//----------------------------------------------------------------------------
#define MAX_DISK                4
//----------------------------------------------------------------------------

/****************************************************************************
 * Enumerations
 ****************************************************************************/

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

/****************************************************************************
 * Structures
 ****************************************************************************/

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

/****************************************************************************
 * Storage Allocation
 ****************************************************************************/

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

/****************************************************************************
 * Prototypes
 ****************************************************************************/

//----------------------------------------------------------------------------
void
bios_cfg(
    void
    );
//----------------------------------------------------------------------------
void
bios_eject(
    int                         drive_num
    );
//----------------------------------------------------------------------------
void
bios_mount(
    int                         drive_num,
    char                    *   file_name
    );
//----------------------------------------------------------------------------
void
cpm_bios(
    void
    );
//----------------------------------------------------------------------------
void
bios_shutdown(
    void
    );
//----------------------------------------------------------------------------

/****************************************************************************/

#endif                      //    BIOS_H