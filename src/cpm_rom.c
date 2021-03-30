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
#include "bios.h"               //  CP/M BIOS
#include "boot_rom.h"           //  Boot ROM
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
/**
 *  Initialize the system and load the CP/M operating system.
 *
 *  @param  boot_code           Instructs the boot ROM how to boot.
 *
 *  @return                     No information is returned from this function.
 *
 *  @note
 *
 ****************************************************************************/

void
boot_eeprom(
    int                         boot_code
    )
{
    /**
     *  @param  rst_0_code          Address x'0000 boot jump block          */
    uint8_t                     rst_0_code[ ] = {
        //  Build the RST 0 instruction base.
        //  Literally insert 'JMP x'F200' instruction at address 0
        //  Which is a jump to the BIOS BOOT vector.
        0xC3, 0x00, 0xF2,       //  0000    JP      BIOS    ;   WARM_BOOT
        0x00,                   //  0003    DB      x'00    ;   ??
        0x00,                   //  0004    DB      x'00    ;   DISK & USR
        0xC3, 0x06, 0xE4    };  //  0005    JP      BDOS    ;   BDOS entry vector

    /**
     *  @param  bdos_init           BDOS Initialization                     */
    uint8_t                     bdos_init[ ] = {
        //  Build the RST 0 instruction base.
        //  Literally insert 'JMP x'F200' instruction at address 0
        //  Which is a jump to the BIOS BOOT vector.

        0x21, 0x00, 0x00,       //  0080    LD      HL, 0       ; 0000 C3 03 F2
        0x36, 0xC3,             //  0083    LD      (HL), 0C3h  ; JP WBOOT
        0x23,                   //  0085    INC     HL          ;
        0x36, 0x03,             //  0086    LD      (HL), 03h   ;
        0x23,                   //  0088    INC     HL          ;
        0x36, 0xF2,             //  0089    LD      (HL), 0F2h  ;

        0x23,                   //  008B    INC     HL          ; 0003 00
        0x36, 0x00,             //  008C    LD      (HL), 0F2h  ;   IOBYTE

        0x23,                   //  008E    INC     HL          ; 0004 00
        0x36, 0x00,             //  008F    LD      (HL), 0F2h  ;   DISK SELECT

        0x23,                   //  0090    INC     HL          ; 0005 C3 06 E4
        0x36, 0xC3,             //  0091    LD      (HL), 0C3h  ; JP CCP
        0x23,                   //  0093    INC     HL          ;
        0x36, 0x06,             //  0094    LD      (HL), 03h   ;
        0x23,                   //  0096    INC     HL          ;
        0x36, 0xE4,             //  0097    LD      (HL), 0F2h  ;

        0x0E, 0x0D,             //  0099    LD      C, 00Dh     ; DRV_ALLRESET
        0xCD, 0x05, 0x00,       //  009B    CALL    BDOS        ;   Do it.

        0x3A, 0x04, 0x00,       //  009E    LDA     CDISK       ; GET CURRENT DISK NUMBER
        0x4F,                   //  00F1    MOV     C, A        ; SEND TO THE CCP
        0xC3, 0x00, 0xDC        //  00F2    JMP     CCP         ; GO TO CP/M FOR FURTHER PROCESSING
    };

    /**
     *  @param  bios_vector_tbl     BIOS function vector table              */
    uint8_t                     bios_vector_tbl[ 51 ] = {
        0xD3, 0xFF,             //  F200    OUT     x'FF    ;   BOOT_VECTOR
        0x76,                   //  F202    HLT
        0xD3, 0xFF,             //  F203    OUT     x'FF    ;   WBOOT_VECTOR
        0x76,                   //  F205    HLT
        0xD3, 0xFF,             //  F206    OUT     x'FF    ;   CONST_VECTOR
        0xC9,                   //  F208    RET
        0xD3, 0xFF,             //  F209    OUT     x'FF    ;   CONIN_VECTOR
        0xC9,                   //  F20B    RET
        0xD3, 0xFF,             //  F20C    OUT     x'FF    ;   CONOUT_VECTOR
        0xC9,                   //  F20E    RET
        0xD3, 0xFF,             //  F20F    OUT     x'FF    ;   LIST_VECTOR
        0xC9,                   //  F211    RET
        0xD3, 0xFF,             //  F212    OUT     x'FF    ;   PUNCH_VECTOR
        0xC9,                   //  F214    RET
        0xD3, 0xFF,             //  F215    OUT     x'FF    ;   READER_VECTOR
        0xC9,                   //  F217    RET
        0xD3, 0xFF,             //  F218    OUT     x'FF    ;   HOME_VECTOR
        0xC9,                   //  F21A    RET
        0xD3, 0xFF,             //  F21B    OUT     x'FF    ;   SELDSK_VECTOR
        0xC9,                   //  F21D    RET
        0xD3, 0xFF,             //  F21E    OUT     x'FF    ;   SETTRK_VECTOR
        0xC9,                   //  F220    RET
        0xD3, 0xFF,             //  F221    OUT     x'FF    ;   SETSEC_VECTOR
        0xC9,                   //  F223    RET
        0xD3, 0xFF,             //  F224    OUT     x'FF    ;   SETDMA_VECTOR
        0xC9,                   //  F226    RET
        0xD3, 0xFF,             //  F227    OUT     x'FF    ;   READ_VECTOR
        0xC9,                   //  F229    RET
        0xD3, 0xFF,             //  F22A    OUT     x'FF    ;   WRITE_VECTOR
        0xC9,                   //  F22C    RET
        0xD3, 0xFF,             //  F22D    OUT     x'FF    ;   LISTST_VECTOR
        0xC9,                   //  F22F    RET
        0xD3, 0xFF,             //  F230    OUT     x'FF    ;   SECTRAN_VECTOR
        0xC9        };          //  F232    RET

    /************************************************************************
     *  FLOPPY DISK TRANSLATION TABLE [for compatibility]
     *  @note:      Base address = x'F280
     ************************************************************************/

    /**
     *  @param  sec_xlate_tbl       Sector Translation Table                */
    uint8_t                     sec_xlate_tbl[     ] = {
        //--------------------------------------------------------------------
        //  TRAN0:  IBM Standard 8" Single Sided 128 Bytes/Sector
        //          Skew factor 6
        //--------------------------------------------------------------------
         1,  7, 13, 19,         //  F280
        25,  5, 11, 17,         //  F284
        23,  3,  9, 15,         //  F288
        21,  2,  8, 14,         //  F28C
        20, 26,  6, 12,         //  F290
        18, 24,  4, 10,         //  F294
        16, 22,                 //  F298
        //--------------------------------------------------------------------
        //          Filler for alignment
        //--------------------------------------------------------------------
                 0,  0,         //  F29A
         0,  0,  0,  0,         //  F29C
        //--------------------------------------------------------------------
        //  TRAN8:  8" Double Density 512 Bytes/Sector
        //          Skew factor 4
        //--------------------------------------------------------------------
         1,  5,  9, 13,         //  F2A0
         2,  6, 10, 14,         //  F2A4
         3,  7, 11, 15,         //  F2A8
         4,  8, 12,             //  F2AC
        //--------------------------------------------------------------------
        //          Filler for alignment
        //--------------------------------------------------------------------
                     0,         //  F2AF
        //--------------------------------------------------------------------
        //  TRAN8:  5.25" Double Density 512 Bytes/Sector
        //          Skew factor 2
        //--------------------------------------------------------------------
         1,  3,  5,  7,         //  F2B0
         9,  2,  4,  6,         //  F2B4
         8,                     //  F2B8
        //--------------------------------------------------------------------
        //          Filler for alignment
        //--------------------------------------------------------------------
             0,  0,  0,         //  F2B9
         0,  0,  0,  0,         //  F2BC
        //--------------------------------------------------------------------
        //  TRAN24: 8" Double Density 555 Bytes/Sector
        //          No translation
        //--------------------------------------------------------------------

         1,  2,  3,  4,         //  F2C0
         5,  6,  7,  8,         //  F2C4
         9, 10, 11, 12,         //  F2C8
        13, 14, 15, 16,         //  F2CC
        17, 18, 19, 20,         //  F2D0
        21, 22, 23, 24,         //  F2D4
        25, 26  };              //  F2D8

    /************************************************************************
     *  DISK PARAMETER TABLEs
     *  @note:      Base address = x'F300
     ************************************************************************/

    /**
     *  @param  dph                 Disk Parameter Header for ALL disks     */
    uint8_t                     dph[ 128 ] = {
        //  Drive 0     A:
        0x00, 0x00,             //  00  Translation Table       x'F300
        0x00, 0x00,             //  02
        0x00, 0x00,             //  04
        0x00, 0x00,             //  06
        0x00, 0xF4,             //  08  Directory Buffer
        0x80, 0xF3,             //  0A  Disk Parameter Block
        0x80, 0xF4,             //  0C  CHK00
        0x80, 0xF5,             //  0E  ALL00
        //  Drive 1     B:
        0x00, 0x00,             //  10  Translation Table       x'F310
        0x00, 0x00,             //  12
        0x00, 0x00,             //  14
        0x00, 0x00,             //  16
        0x00, 0xF4,             //  18  Directory Buffer
        0x90, 0xF3,             //  1A  Disk Parameter Block
        0xA0, 0xF4,             //  1C  CHK01
        0x90, 0xF5,             //  1E  ALL01
        //  Drive 2     C:
        0x00, 0x00,             //  20  Translation Table       x'F320
        0x00, 0x00,             //  22
        0x00, 0x00,             //  24
        0x00, 0x00,             //  26
        0x00, 0xF4,             //  28  Directory Buffer
        0xA0, 0xF3,             //  2A  Disk Parameter Block
        0xC0, 0xF4,             //  2C  CHK02
        0xA0, 0xF5,             //  2E  ALL02
        //  Drive 3     D:
        0x00, 0x00,             //  30  Translation Table       NONE
        0x00, 0x00,             //  32
        0x00, 0x00,             //  34
        0x00, 0x00,             //  36
        0x00, 0xF4,             //  38  Directory Buffer
        0xB0, 0xF3,             //  3A  Disk Parameter Block
        0xE0, 0xF4,             //  3C  CHK03
        0xB0, 0xF5,             //  3E  ALL03
        //  Drive 4     E:
        0x80, 0xF2,             //  40  Translation Table       x'F340
        0x00, 0x00,             //  42
        0x00, 0x00,             //  44
        0x00, 0x00,             //  46
        0x00, 0xF4,             //  48  Directory Buffer
        0xC0, 0xF3,             //  4A  Disk Parameter Block
        0x00, 0xF5,             //  4C  CHK04
        0xC0, 0xF5,             //  4E  ALL04
        //  Drive 5     F:
        0x80, 0xF2,             //  50  Translation Table       x'F350
        0x00, 0x00,             //  52
        0x00, 0x00,             //  54
        0x00, 0x00,             //  56
        0x00, 0xF4,             //  58  Directory Buffer
        0xD0, 0xF3,             //  5A  Disk Parameter Block
        0x20, 0xF5,             //  5C  CHK05
        0xD0, 0xF5,             //  5E  ALL05
        //  Drive 6     G:
        0x80, 0xF2,             //  60  Translation Table       x'F360
        0x00, 0x00,             //  62
        0x00, 0x00,             //  64
        0x00, 0x00,             //  66
        0x00, 0xF4,             //  68  Directory Buffer
        0xE0, 0xF3,             //  6A  Disk Parameter Block
        0x40, 0xF5,             //  6C  CHK06
        0xE0, 0xF5,             //  6E  ALL06
        //  Drive 7     H:
        0x80, 0xF2,             //  70  Translation Table       x'F370
        0x00, 0x00,             //  72
        0x00, 0x00,             //  74
        0x00, 0x00,             //  76
        0x00, 0xF4,             //  78  Directory Buffer
        0xF0, 0xF3,             //  7A  Disk Parameter Block
        0x60, 0xF5,             //  7C  CHK07
        0xF0, 0xF5   };         //  7E  ALL07

    /************************************************************************
     *  DISK PARAMETER BLOCKs
     *  @note:      Base address = x'F380
     ************************************************************************/

    /**
     *  @param  dpb                 Disk Parameter Block                    */
    uint8_t                     dpb[ 128 ] = {
        //  Drive 0     A:      4 MB HDD                        x'F380
        0x80, 0x01,             //  F380      384   SEC:    Sectors/Track
        0x06,                   //  F382        6   BSH:    Block Shift
        0x3F,                   //  F383       63   BLM:    Block Mask
	0x03,                   //  F384        3   EXM:    Extent Mask
        0xEB, 0x01,             //  F385      491   DSM:    Storage Capacity
        0xFF, 0x01,             //  F387      511   DRM:    Directory Entries
        0xC0,                   //  F389 11000000b  AL0
        0x00,                   //  F38A        0   AL1
        0x00, 0x00,             //  F38B        0   CKS:    Dir Check Vector
        0x01, 0x00,             //  F38D        0   OFF:    Reserved Tracks
        0x00,                   //  F38F        Filler for memory alignment
        //  Drive 1     B:                                      x'F390
        0x80, 0x01,             //  F390      384   SEC:    Sectors/Track
        0x06,                   //  F392        6   BSH:    Block Shift
        0x3F,                   //  F393       63   BLM:    Block Mask
	0x03,                   //  F394        3   EXM:    Extent Mask
        0xEB, 0x01,             //  F395      491   DSM:    Storage Capacity
        0xFF, 0x01,             //  F397      511   DRM:    Directory Entries
        0xC0,                   //  F399 11000000b  AL0
        0x00,                   //  F39A        0   AL1
        0x00, 0x00,             //  F39B        0   CKS:    Dir Check Vector
        0x01, 0x00,             //  F39D        0   OFF:    Reserved Tracks
        0x00,                   //  F39F        Filler for memory alignment
        //  Drive 2     C:      4 MB HDD                        x'F3A0
        0x80, 0x01,             //  F3A0      384   SEC:    Sectors/Track
        0x06,                   //  F3A2        6   BSH:    Block Shift
        0x3F,                   //  F3A3       63   BLM:    Block Mask
	0x03,                   //  F3A4        3   EXM:    Extent Mask
        0xEB, 0x01,             //  F3A5      491   DSM:    Storage Capacity
        0xFF, 0x01,             //  F3A7      511   DRM:    Directory Entries
        0xC0,                   //  F3A9 11000000b  AL0
        0x00,                   //  F3AA        0   AL1
        0x00, 0x00,             //  F3AB        0   CKS:    Dir Check Vector
        0x01, 0x00,             //  F3AD        0   OFF:    Reserved Tracks
        0x00,                   //  F3AF        Filler for memory alignment
        //  Drive 3     D:                                      x'F3B0
        0x80, 0x01,             //  F3D0      384   SEC:    Sectors/Track
        0x06,                   //  F3D2        6   BSH:    Block Shift
        0x3F,                   //  F3D3       63   BLM:    Block Mask
	0x03,                   //  F3D4        3   EXM:    Extent Mask
        0xEB, 0x01,             //  F3D5      491   DSM:    Storage Capacity
        0xFF, 0x01,             //  F3D7      511   DRM:    Directory Entries
        0xC0,                   //  F3D9 11000000b  AL0
        0x00,                   //  F3DA        0   AL1
        0x00, 0x00,             //  F3DB        0   CKS:    Dir Check Vector
        0x00, 0x00,             //  F3DD        0   OFF:    Reserved Tracks
        0x00,                   //  F3DF        Filler for memory alignment
        //  Drive 4     E:                                      x'F3C0
        0x1A, 0x00,      	//  C0   26     SECTORS PER TRACK
        0x03,                   //  C2    3     BLOCK SHIFT FACTOR
        0x07,                   //  C3    7     BLOCK MASK
        0x00,                   //  C4    0     NULL MASK
        0xF2, 0x00,             //  C5  242     DISK SIZE-1
        0x3F, 0x00,             //  C7   63     DIRECTORY MAX
        0xC0,                   //  C9  192     ALLOC 0
        0x00,                   //  CA    0     ALLOC 1
        0x10, 0x00,             //  CB   16     CHECK SIZE
        0x02, 0x00,       	//  CD    2     TRACK OFFSET
        0x00,                   //  CF  ---     Filler for memory alignment
        //  Drive 5     F:                                      x'F3D0
        0x1A, 0x00,      	//  D0   26     SECTORS PER TRACK
        0x03,                   //  D2    3     BLOCK SHIFT FACTOR
        0x07,                   //  D3    7     BLOCK MASK
        0x00,                   //  D4    0     NULL MASK
        0xF2, 0x00,             //  D5  242     DISK SIZE-1
        0x3F, 0x00,             //  D7   63     DIRECTORY MAX
        0xC0,                   //  D9  192     ALLOC 0
        0x00,                   //  DA    0     ALLOC 1
        0x10, 0x00,             //  DB   16     CHECK SIZE
        0x02, 0x00,       	//  DD    2     TRACK OFFSET
        0x00,                   //  DF  ---     Filler for memory alignment
        //  Drive 6     G:                                      x'F3E0
        0x1A, 0x00,      	//  E0   26     SECTORS PER TRACK
        0x03,                   //  E2    3     BLOCK SHIFT FACTOR
        0x07,                   //  E3    7     BLOCK MASK
        0x00,                   //  E4    0     NULL MASK
        0xF2, 0x00,             //  E5  242     DISK SIZE-1
        0x3F, 0x00,             //  E7   63     DIRECTORY MAX
        0xC0,                   //  E9  192     ALLOC 0
        0x00,                   //  EA    0     ALLOC 1
        0x10, 0x00,             //  EB   16     CHECK SIZE
        0x02, 0x00,       	//  ED    2     TRACK OFFSET
        0x00,                   //  EF  ---     Filler for memory alignment
        //  Drive 7     H:                                      x'F3F0
        0x1A, 0x00,      	//  F0   26     SECTORS PER TRACK
        0x03,                   //  F2    3     BLOCK SHIFT FACTOR
        0x07,                   //  F3    7     BLOCK MASK
        0x00,                   //  F4    0     NULL MASK
        0xF2, 0x00,             //  F5  242     DISK SIZE-1
        0x3F, 0x00,             //  F7   63     DIRECTORY MAX
        0xC0,                   //  F9  192     ALLOC 0
        0x00,                   //  FA    0     ALLOC 1
        0x10, 0x00,             //  FB   16     CHECK SIZE
        0x02, 0x00,       	//  FD    2     TRACK OFFSET
        0x00        };          //  FF  ---     Filler for memory alignment
    /**
     *  @param  dpb                 Disk Parameter Block                    */
    uint8_t               dummy_dpb[     ] = {
        //--------------------------------------------------------------------
        //  ****    DISK PARAMETER BLOCKS FOR 8" FLORPY DISKS     ****
        //--------------------------------------------------------------------
        //  DPB0:   Single Sided Single Density 128 Bytes/Sector
        //--------------------------------------------------------------------
        0x1A, 0x00,             //  F380       26   SEC:    Sectors/Track
        0x03,                   //  F382        3   BSH:    Block Shift
        0x07,                   //  F383        7   BLM:    Block Mask
	0x00,                   //  F384        0   EXM:    Extent Mask
        0xF2, 0x00,             //  F385      242   DSM:    Storage Capacity
        0x3F, 0x00,             //  F387       63   DRM:    Directory Entries
        0xC0,                   //  F389 11000000b  AL0
        0x00,                   //  F38A        0   AL1
        0x10, 0x00,             //  F38B       16   CKS:    Dir Check Vector
        0x02, 0x00,             //  F38D        2   OFF:    Reserved Tracks
        //--------------------------------------------------------------------
        //          Filler for alignment
        //--------------------------------------------------------------------
        0x00,                   //  F38E
        //--------------------------------------------------------------------
        //  DPB0:   Double Sided Double Density 512 Bytes/Sector
        //--------------------------------------------------------------------
        0x78, 0x00,             //  F380      120   SEC:    Sectors/Track
        0x04,                   //  F382        4   BSH:    Block Shift
        0x0F,                   //  F383       15   BLM:    Block Mask
	0x00,                   //  F384        0   EXM:    Extent Mask
        0x32, 0x02,             //  F385      561   DSM:    Storage Capacity
        0x7F, 0x00,             //  F387      127   DRM:    Directory Entries
        0xC0,                   //  F389 11000000b  AL0
        0x00,                   //  F38A        0   AL1
        0x20, 0x00,             //  F38B       32   CKS:    Dir Check Vector
        0x02, 0x00,             //  F38D        2   OFF:    Reserved Tracks
        //--------------------------------------------------------------------
        //          Filler for alignment
        //--------------------------------------------------------------------
        0x00,                   //  F38E
        //--------------------------------------------------------------------
        //  DPB0:   Double Sided Double Density 512 Bytes/Sector
        //--------------------------------------------------------------------
        0x1A, 0x00,             //  F380       26   SEC:    Sectors/Track
        0x03,                   //  F382        3   BSH:    Block Shift
        0x07,                   //  F383        7   BLM:    Block Mask
	0x00,                   //  F384        0   EXM:    Extent Mask
        0xF2, 0x02,             //  F385      242   DSM:    Storage Capacity
        0x3F, 0x00,             //  F387       63   DRM:    Directory Entries
        0xC0,                   //  F389 11000000b  AL0
        0x00,                   //  F38A        0   AL1
        0x10, 0x00,             //  F38B       16   CKS:    Dir Check Vector
        0x00, 0x00,             //  F38D        0   OFF:    Reserved Tracks
        //--------------------------------------------------------------------
        //          Filler for alignment
        //--------------------------------------------------------------------
        0x00,                   //  F38E
        //--------------------------------------------------------------------
        //  DPB0:   Single Sided Double Density 512 Bytes/Sector
        //--------------------------------------------------------------------
        0x68, 0x00,             //  F380      104   SEC:    Sectors/Track
        0x04,                   //  F382        4   BSH:    Block Shift
        0x0F,                   //  F383       15   BLM:    Block Mask
	0x00,                   //  F384        0   EXM:    Extent Mask
        0xE5, 0x01,             //  F385      486   DSM:    Storage Capacity
        0x7F, 0x00,             //  F387      127   DRM:    Directory Entries
        0xC0,                   //  F389 11000000b  AL0
        0x00,                   //  F38A        0   AL1
        0x20, 0x00,             //  F38B       32   CKS:    Dir Check Vector
        0x00, 0x00,             //  F38D        0   OFF:    Reserved Tracks
        //--------------------------------------------------------------------
        //          Filler for alignment
        //--------------------------------------------------------------------
        0x00,                   //  F38E
        //--------------------------------------------------------------------
        //  ****    DISK PARAMETER BLOCKS FOR 5.25" FLOPPY DISKS     ****
        //--------------------------------------------------------------------
        //  DPB0:   Double Sided Double Density 512 Bytes/Sector
        //--------------------------------------------------------------------
        0x20, 0x00,             //  F380       32   SEC:    Sectors/Track
        0x03,                   //  F382        3   BSH:    Block Shift
        0x07,                   //  F383        7   BLM:    Block Mask
	0x00,                   //  F384        0   EXM:    Extent Mask
        0x90, 0x00,             //  F385      144   DSM:    Storage Capacity
        0x3F, 0x00,             //  F387       63   DRM:    Directory Entries
        0xC0,                   //  F389 11000000b  AL0
        0x00,                   //  F38A        0   AL1
        0x10, 0x00,             //  F38B       16   CKS:    Dir Check Vector
        0x00, 0x00,             //  F38D        0   OFF:    Reserved Tracks
        //--------------------------------------------------------------------
        //          Filler for alignment
        //--------------------------------------------------------------------
        0x00,                   //  F38E
        //--------------------------------------------------------------------
        //  DPB8:   Double Density 512 Bytes/Sector
        //--------------------------------------------------------------------
        0x40, 0x00,             //  F390       64   SEC:    Sectors/Track
        0x04,                   //  F392        4   BSH:    Block Shift
        0x0F,                   //  F393       15   BLM:    Block Mask
	0x01,                   //  F394        1   EXM:    Extent Mask
        0x90, 0x00,             //  F395      144   DSM:    Storage Capacity
        0x7F, 0x00,             //  F397      127   DRM:    Directory Entries
        0xC0,                   //  F399 11000000b  AL0
        0x00,                   //  F39A        0   AL1
        0x20, 0x00,             //  F39B       32   CKS:    Dir Check Vector
        0x00, 0x00,             //  F39D        0   OFF:    Reserved Tracks
        //--------------------------------------------------------------------
        //          Filler for alignment
        //--------------------------------------------------------------------
        0x00,                   //  F39E
        //--------------------------------------------------------------------
        //  DPB16:  Double Density 512 Bytes/Sector
        //--------------------------------------------------------------------
        0x48, 0x00,             //  F390       72   SEC:    Sectors/Track
        0x04,                   //  F392        4   BSH:    Block Shift
        0x0F,                   //  F393       15   BLM:    Block Mask
	0x01,                   //  F394        1   EXM:    Extent Mask
        0x86, 0x00,             //  F395      134   DSM:    Storage Capacity
        0x7F, 0x00,             //  F397      127   DRM:    Directory Entries
        0xC0,                   //  F399 11000000b  AL0
        0x00,                   //  F39A        0   AL1
        0x20, 0x00,             //  F39B       32   CKS:    Dir Check Vector
        0x00, 0x00,             //  F39D        2   OFF:    Reserved Tracks
        //--------------------------------------------------------------------
        //          Filler for alignment
        //--------------------------------------------------------------------
        0x00,                   //  F39E
        //--------------------------------------------------------------------
        //  DPB24:  8" Double Density 512 Bytes/Sector
        //--------------------------------------------------------------------
        0x7C, 0x00,             //  F390      120   SEC:    Sectors/Track
        0x04,                   //  F392        4   BSH:    Block Shift
        0x0F,                   //  F393       15   BLM:    Block Mask
	0x00,                   //  F394        0   EXM:    Extent Mask
        0xD7, 0x01,             //  F395      471   DSM:    Storage Capacity
        0x7F, 0x00,             //  F397      127   DRM:    Directory Entries
        0xC0,                   //  F399 11000000b  AL0
        0x00,                   //  F39A        0   AL1
        0x20, 0x00,             //  F39B       32   CKS:    Dir Check Vector
        0x00, 0x00,             //  F39D        2   OFF:    Reserved Tracks
        //--------------------------------------------------------------------
        //          Filler for alignment
        //--------------------------------------------------------------------
        0x00,                   //  F39E
        //--------------------------------------------------------------------
        //  DPB24:  8" Double Density 512 Bytes/Sector
        //--------------------------------------------------------------------
        0x7C, 0x00,             //  F390      120   SEC:    Sectors/Track
        0x04,                   //  F392        4   BSH:    Block Shift
        0x0F,                   //  F393       15   BLM:    Block Mask
	0x00,                   //  F394        0   EXM:    Extent Mask
        0xD7, 0x01,             //  F395      471   DSM:    Storage Capacity
        0x7F, 0x00,             //  F397      127   DRM:    Directory Entries
        0xC0,                   //  F399 11000000b  AL0
        0x00,                   //  F39A        0   AL1
        0x20, 0x00,             //  F39B       32   CKS:    Dir Check Vector
        0x00, 0x00,             //  F39D        2   OFF:    Reserved Tracks
        //--------------------------------------------------------------------
        //          Filler for alignment
        //--------------------------------------------------------------------
        0x00,                   //  F39E
        //--------------------------------------------------------------------
        //  DPB24:  HDD     1.1 MB
        //--------------------------------------------------------------------
        0x80, 0x01,             //  F390      384   SEC:    Sectors/Track
        0x04,                   //  F392        4   BSH:    Block Shift
        0x0F,                   //  F393       15   BLM:    Block Mask
	0x00,                   //  F394        0   EXM:    Extent Mask
        0xC1, 0x01,             //  F395      449   DSM:    Storage Capacity
        0x7F, 0x00,             //  F397      127   DRM:    Directory Entries
        0xC0,                   //  F399 11000000b  AL0
        0x00,                   //  F39A        0   AL1
        0x00, 0x00,             //  F39B        0   CKS:    Dir Check Vector
        0x03, 0x00,             //  F39D        3   OFF:    Reserved Tracks
        //--------------------------------------------------------------------
        //          Filler for alignment
        //--------------------------------------------------------------------
        0x00,                   //  F39E
        //--------------------------------------------------------------------
        //  DPB24:  HDD     0.8 MB
        //--------------------------------------------------------------------
        0x80, 0x01,             //  F390      384   SEC:    Sectors/Track
        0x04,                   //  F392        4   BSH:    Block Shift
        0x0F,                   //  F393       15   BLM:    Block Mask
	0x00,                   //  F394        1   EXM:    Extent Mask
        0x86, 0x00,             //  F395      134   DSM:    Storage Capacity
        0x7F, 0x00,             //  F397      127   DRM:    Directory Entries
        0xC0,                   //  F399 11000000b  AL0
        0x00,                   //  F39A        0   AL1
        0x00, 0x00,             //  F39B        0   CKS:    Dir Check Vector
        0x03, 0x00,             //  F39D        3   OFF:    Reserved Tracks
        //--------------------------------------------------------------------
        //          Filler for alignment
        //--------------------------------------------------------------------
        0x00,                   //  F39E
        //--------------------------------------------------------------------
        //  DPB24:  HDD     2.0 MB
        //--------------------------------------------------------------------
        0x80, 0x01,             //  F390      384   SEC:    Sectors/Track
        0x05,                   //  F392        5   BSH:    Block Shift
        0x1F,                   //  F393       31   BLM:    Block Mask
	0x01,                   //  F394        1   EXM:    Extent Mask
        0xEB, 0x01,             //  F395      491   DSM:    Storage Capacity
        0xFF, 0x01,             //  F397      511   DRM:    Directory Entries
        0xC0,                   //  F399 11000000b  AL0
        0x00,                   //  F39A        0   AL1
        0x00, 0x00,             //  F39B        0   CKS:    Dir Check Vector
        0x1B, 0x00,             //  F39D       27   OFF:    Reserved Tracks
        //--------------------------------------------------------------------
        //          Filler for alignment
        //--------------------------------------------------------------------
        0x00,                   //  F39E
        //--------------------------------------------------------------------
        //  DPB24:  HDD     4.0 MB
        //--------------------------------------------------------------------
        0x80, 0x01,             //  F390      384   SEC:    Sectors/Track
        0x06,                   //  F392        6   BSH:    Block Shift
        0x3F,                   //  F393       63   BLM:    Block Mask
	0x03,                   //  F394        3   EXM:    Extent Mask
        0xEB, 0x01,             //  F395      491   DSM:    Storage Capacity
        0xFF, 0x01,             //  F397      511   DRM:    Directory Entries
        0xC0,                   //  F399 11000000b  AL0
        0x00,                   //  F39A        0   AL1
        0x00, 0x00,             //  F39B        0   CKS:    Dir Check Vector
        0x1B, 0x00,             //  F39D       27   OFF:    Reserved Tracks
        //--------------------------------------------------------------------
        //          Filler for alignment
        //--------------------------------------------------------------------
        0x00,                   //  F39E
        //--------------------------------------------------------------------
        //  DPB24:  HDD     8.0 MB
        //--------------------------------------------------------------------
        0x80, 0x01,             //  F390      384   SEC:    Sectors/Track
        0x07,                   //  F392        7   BSH:    Block Shift
        0x7F,                   //  F393      127   BLM:    Block Mask
	0x07,                   //  F394        7   EXM:    Extent Mask
        0xEE, 0x01,             //  F395      494   DSM:    Storage Capacity
        0xFF, 0x01,             //  F397      511   DRM:    Directory Entries
        0xC0,                   //  F399 11000000b  AL0
        0x00,                   //  F39A        0   AL1
        0x00, 0x00,             //  F39B        0   CKS:    Dir Check Vector
        0x1B, 0x00,             //  F39D       27   OFF:    Reserved Tracks
        //--------------------------------------------------------------------
        //          Filler for alignment
        //--------------------------------------------------------------------
        0x00        };          //  F39E
#if 0
    /************************************************************************
     *  RESERVED FOR BDOS:
     *  @note:      Reference only, not copied into RAM.
     ************************************************************************/

    /**
     *  @param  dirbuf              Scratch Directory Area          x'F400  */
    uint8_t                     dirbuf[ 128 ];
    /**
     *  @param  all00               Allocation vector disk 0        x'F480  */
    uint8_t                     all00[ 31 ];
    /**
     *  @param  all01               Allocation vector disk 1        x'F4A0  */
    uint8_t                     all01[ 31 ];
    /**
     *  @param  all02               Allocation vector disk 2        x'F4C0  */
    uint8_t                     all02[ 31 ];
    /**
     *  @param  all03               Allocation vector disk 3        x'F4E0  */
    uint8_t                     all03[ 31 ];
    /**
     *  @param  all04               Allocation vector disk 4        x'F500  */
    uint8_t                     all04[ 31 ];
    /**
     *  @param  all05               Allocation vector disk 5        x'F520  */
    uint8_t                     all05[ 31 ];
    /**
     *  @param  all06               Allocation vector disk 6        x'F540  */
    uint8_t                     all06[ 31 ];
    /**
     *  @param  all07               Allocation vector disk 7        x'F560  */
    uint8_t                     all07[ 31 ];
    /**
     *  @param  chk00               Check vector disk 0             x'F580  */
    uint8_t                     chk00[ 16 ];
    /**
     *  @param  chk01               Check vector disk 1             x'F590  */
    uint8_t                     chk01[ 16 ];
    /**
     *  @param  chk02               Check vector disk 2             x'F5A0  */
    uint8_t                     chk02[ 16 ];
    /**
     *  @param  chk03               Check vector disk 3             x'F5B0  */
    uint8_t                     chk03[ 16 ];
    /**
     *  @param  chk04               Check vector disk 4             x'F5C0  */
    uint8_t                     chk04[ 16 ];
    /**
     *  @param  chk05               Check vector disk 5             x'F5D0  */
    uint8_t                     chk05[ 16 ];
    /**
     *  @param  chk06               Check vector disk 6             x'F5E0  */
    uint8_t                     chk06[ 16 ];
    /**
     *  @param  chk07               Check vector disk 7             x'F5F0  */
    uint8_t                     chk07[ 16 ];
#endif

    /************************************************************************
     *  RST 0
     ************************************************************************/

    //  Load the data
    memory_load( RST_0_ADDRESS, sizeof( rst_0_code ), rst_0_code );

#if DEBUG_MODE
    //  DEBUG
    memory_dump( RST_0_ADDRESS, 16 );
#endif

    /************************************************************************
     *  BIOS function vector table.
     ************************************************************************/

    //  Load the data
    memory_load( BIOS_BASE, sizeof( bios_vector_tbl ), bios_vector_tbl );

#if DEBUG_MODE
    //  DEBUG
    memory_dump( BIOS_BASE, 16 );
#endif

    /************************************************************************
     *  BIOS Disk Parameter Table
     ************************************************************************/

    //  Load the data
    memory_load( DPH_BASE, DPH_BASE_SIZE, dph );

#if DEBUG_MODE
    //  DEBUG
    memory_dump( DPH_BASE, 16 );
#endif

    /************************************************************************
     *  BIOS Sector Translation Table
     ************************************************************************/

    //  Load the data
    memory_load( SXT_BASE, SXT_SIZE, sec_xlate_tbl );

#if DEBUG_MODE
    //  DEBUG
    memory_dump( SXT_BASE, 16 );
#endif

    /************************************************************************
     *  Disk Parameter Block
     ************************************************************************/

    //  Load the data
    memory_load( DPB_BASE, DPB_SIZE, dpb );

#if DEBUG_MODE
    //  DEBUG
    memory_dump( DPB_BASE, 16 );
#endif

    /************************************************************************
     *  BOOT completion code is in CPU memory
     ************************************************************************/

    //  Load the data
    memory_load( BOOT_BASE, BOOT_SIZE, bdos_init );

#if DEBUG_MODE
    //  DEBUG
    memory_dump( BOOT_BASE, 16 );
#endif

}
/****************************************************************************/