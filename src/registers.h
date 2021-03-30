/*******************************  COPYRIGHT  ********************************/
/*
 *  Author? "Gregory N. Leonhardt"
 *  License? "CC BY-NC 2.0"
 *           "https://creativecommons.org/licenses/by-nc/2.0/"
 *
 ****************************************************************************/

#ifndef REGISTERS_H
#define REGISTERS_H

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
#define HIGHBYTE( SRC ) ( ( SRC & 0xFF00 ) >> 8 )
#define LOWBYTE(  SRC ) ( ( SRC & 0x00FF )      )
//----------------------------------------------------------------------------
#define R_B     ( 0b000 )
#define R_C     ( 0b001 )
#define R_D     ( 0b010 )
#define R_E     ( 0b011 )
#define R_H     ( 0b100 )
#define R_L     ( 0b101 )
#define R_HL_p  ( 0b110 )
#define R_A     ( 0b111 )
//----------------------------------------------------------------------------
#define QQ_BC    ( 0b00 )
#define QQ_DE    ( 0b01 )
#define QQ_HL    ( 0b10 )
#define QQ_AF    ( 0b11 )
//----------------------------------------------------------------------------
#define SS_BC    ( 0b00 )
#define SS_DE    ( 0b01 )
#define SS_HL    ( 0b10 )
#define SS_SP    ( 0b11 )
//----------------------------------------------------------------------------
#define PP_BC    ( 0b00 )
#define PP_DE    ( 0b01 )
#define PP_IX    ( 0b10 )
#define PP_SP    ( 0b11 )
//----------------------------------------------------------------------------
#define RR_BC    ( 0b00 )
#define RR_DE    ( 0b01 )
#define RR_IY    ( 0b10 )
#define RR_SP    ( 0b11 )
//----------------------------------------------------------------------------
#define CC_NZ     ( 0b00 )
#define CC_Z      ( 0b01 )
#define CC_NC     ( 0b10 )
#define CC_C      ( 0b11 )
//----------------------------------------------------------------------------
#define CCC_NZ    ( 0b000 )
#define CCC_Z     ( 0b001 )
#define CCC_NC    ( 0b010 )
#define CCC_C     ( 0b011 )
#define CCC_PO    ( 0b100 )
#define CCC_PE    ( 0b101 )
#define CCC_P     ( 0b110 )
#define CCC_M     ( 0b111 )
//----------------------------------------------------------------------------
#define Q_BC    ( 0b00 )
#define Q_DE    ( 0b01 )
#define Q_HL    ( 0b10 )
#define Q_AF    ( 0b11 )
//----------------------------------------------------------------------------
#define CPU_FLAG_C              0b00000001      //  Carry
#define CPU_FLAG_NOT_C          0b11111110      //
#define CPU_FLAG_N              0b00000010      //  Add / Subtract
#define CPU_FLAG_NOT_N          0b11111101      //
#define CPU_FLAG_PV             0b00000100      //  Parity / Overflow
#define CPU_FLAG_NOT_PV         0b11111011      //
#define CPU_FLAG_X3             0b00001000      //  Not Used
#define CPU_FLAG_NOT_X3         0b11110111      //
#define CPU_FLAG_H              0b00010000      //  Half Carry
#define CPU_FLAG_NOT_H          0b11101111      //
#define CPU_FLAG_X5             0b00100000      //  Not Used
#define CPU_FLAG_NOT_X5         0b11011111      //
#define CPU_FLAG_Z              0b01000000      //  Zero
#define CPU_FLAG_NOT_Z          0b10111111      //
#define CPU_FLAG_S              0b10000000      //  Sign
#define CPU_FLAG_NOT_S          0b01111111      //
//----------------------------------------------------------------------------
#define GET_N( )                ( memory_get_8( CPU_REG_PC++ ) )
//----------------------------------------------------------------------------
#define GET_HL_p( )             ( memory_get_8( CPU_REG_HL ) )
#define PUT_HL_p( N )           ( memory_put_8( CPU_REG_HL, N ) )
//----------------------------------------------------------------------------
#define GET_A( )    ( ( CPU_REG_AF & 0xFF00 ) >> 8 )
#define GET_F( )    ( ( CPU_REG_AF & 0x00FF )      )

#define GET_B( )    ( ( CPU_REG_BC & 0xFF00 ) >> 8 )
#define GET_C( )    ( ( CPU_REG_BC & 0x00FF )      )

#define GET_D( )    ( ( CPU_REG_DE & 0xFF00 ) >> 8 )
#define GET_E( )    ( ( CPU_REG_DE & 0x00FF )      )

#define GET_H( )    ( ( CPU_REG_HL & 0xFF00 ) >> 8 )
#define GET_L( )    ( ( CPU_REG_HL & 0x00FF )      )

#define PUT_A( X )  CPU_REG_AF = ( ( (uint16_t)X << 8 ) | ( CPU_REG_AF & 0x00FF ) )
#define PUT_F( X )  CPU_REG_AF = ( ( CPU_REG_AF & 0xFF00 ) | X )

#define PUT_B( X )  CPU_REG_BC = ( ( (uint16_t)X << 8 ) | ( CPU_REG_BC & 0x00FF ) )
#define PUT_C( X )  CPU_REG_BC = ( ( CPU_REG_BC & 0xFF00 ) | X )

#define PUT_D( X )  CPU_REG_DE = ( ( (uint16_t)X << 8 ) | ( CPU_REG_DE & 0x00FF ) )
#define PUT_E( X )  CPU_REG_DE = ( ( CPU_REG_DE & 0xFF00 ) | X )

#define PUT_H( X )  CPU_REG_HL = ( ( (uint16_t)X << 8 ) | ( CPU_REG_HL & 0x00FF ) )
#define PUT_L( X )  CPU_REG_HL = ( ( CPU_REG_HL & 0xFF00 ) | X )
//----------------------------------------------------------------------------
#define CLEAR_FLAG_C( )     PUT_F( GET_F( ) & CPU_FLAG_NOT_C )
#define SET_FLAG_C( )       PUT_F( GET_F( ) | CPU_FLAG_C )
#define GET_FLAG_C( )       ( GET_F( ) & CPU_FLAG_C )
//----------------------------------------------------------------------------
#define CLEAR_FLAG_N( )     PUT_F( GET_F( ) & CPU_FLAG_NOT_N )
#define SET_FLAG_N( )       PUT_F( GET_F( ) | CPU_FLAG_N )
#define GET_FLAG_N( )       ( ( GET_F( ) & CPU_FLAG_N ) >> 1 )
//----------------------------------------------------------------------------
#define CLEAR_FLAG_PV( )    PUT_F( GET_F( ) & CPU_FLAG_NOT_PV )
#define SET_FLAG_PV( )      PUT_F( GET_F( ) | CPU_FLAG_PV )
#define GET_FLAG_PV( )      ( ( GET_F( ) & CPU_FLAG_PV ) >> 2 )
//----------------------------------------------------------------------------
#define CLEAR_FLAG_H( )     PUT_F( GET_F( ) & CPU_FLAG_NOT_H )
#define SET_FLAG_H( )       PUT_F( GET_F( ) | CPU_FLAG_H )
#define GET_FLAG_H( )       ( ( GET_F( ) & CPU_FLAG_H ) >> 4 )
//----------------------------------------------------------------------------
#define CLEAR_FLAG_Z( )     PUT_F( GET_F( ) & CPU_FLAG_NOT_Z )
#define SET_FLAG_Z( )       PUT_F( GET_F( ) | CPU_FLAG_Z )
#define GET_FLAG_Z( )       ( ( GET_F( ) & CPU_FLAG_Z ) >> 6 )
//----------------------------------------------------------------------------
#define CLEAR_FLAG_S( )     PUT_F( GET_F( ) & CPU_FLAG_NOT_S )
#define SET_FLAG_S( )       PUT_F( GET_F( ) | CPU_FLAG_S )
#define GET_FLAG_S( )       ( ( GET_F( ) & CPU_FLAG_S ) >> 7 )
//----------------------------------------------------------------------------

/****************************************************************************
 * Enumerations
 ****************************************************************************/

//----------------------------------------------------------------------------
/**
 *  @param  EIS_e               Extended Instruction Set type               */
enum                        EIS_e
{
    EIS_BASE                = 0,                //  8080 / Z80
    EIS_CB                  = 1,                //  Z80 CB
    EIS_ED                  = 2,                //  Z80 ED
    EIS_DD                  = 3,                //  Z80 DD
    EIS_DDCB                = 4,                //  Z80 DD CB
    EIS_FD                  = 5,                //  Z80 FD
    EIS_FDCB                = 6                 //  Z80 FD ED
};
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
//      CPU Execution Flags
/**
 *  @param  Extended Instruction Set    (CB), (DD), (DE), (FD)              */
enum    EIS_e               EIS;
//----------------------------------------------------------------------------
/*      Main Register Set                                                   */
/**
 *  @param  CPU_REG_BC                                                      */
uint16_t                    CPU_REG_AF;
/**
 *  @param  CPU_REG_BC                                                      */
uint16_t                    CPU_REG_BC;
/**
 *  @param  CPU_REG_DE                                                      */
uint16_t                    CPU_REG_DE;
/**
 *  @param  CPU_REG_HL                                                      */
uint16_t                    CPU_REG_HL;
//----------------------------------------------------------------------------
/*      Alternate Register Set                                              */
/**
 *  @param  CPU_REG_AF_                                                     */
uint16_t                    CPU_REG_AF_;
/**
 *  @param  CPU_REG_BC_                                                     */
uint16_t                    CPU_REG_BC_;
/**
 *  @param  CPU_REG_DE_                                                     */
uint16_t                    CPU_REG_DE_;
/**
 *  @param  CPU_REG_HL_                                                     */
uint16_t                    CPU_REG_HL_;
//----------------------------------------------------------------------------
/*      Special Purpose Registers                                           */
/**
 *  @param  CPU_REG_PC          Program Counter                             */
uint16_t                    CPU_REG_PC;
/**
 *  @param  CPU_REG_SP          Stack Pointer                               */
uint16_t                    CPU_REG_SP;
/**
 *  @param  CPU_REG_IX          Index-X                                     */
uint16_t                    CPU_REG_IX;
/**
 *  @param  CPU_REG_IY          Index-Y                                     */
uint16_t                    CPU_REG_IY;
/**
 *  @param  CPU_REG_I           Interrupt                                   */
uint8_t                     CPU_REG_I;
/**
 *  @param  CPU_REG_R           Refresh                                     */
uint8_t                     CPU_REG_R;
//----------------------------------------------------------------------------

/****************************************************************************
 * Prototypes
 ****************************************************************************/

//----------------------------------------------------------------------------
uint8_t
reg_get_sr(
    uint8_t                     op_code
    );
//----------------------------------------------------------------------------
uint8_t
reg_get_dr(
    uint8_t                     op_code
    );
//----------------------------------------------------------------------------
void
reg_put_dr(
    uint8_t                     op_code,
    uint8_t                     data
    );
//----------------------------------------------------------------------------
uint16_t
reg_get_ss(
    uint8_t                     op_code
    );
//----------------------------------------------------------------------------
void
reg_put_ss(
    uint8_t                     op_code,
    uint16_t                    data
    );
//----------------------------------------------------------------------------
uint16_t
reg_get_qq(
    uint8_t                     op_code
    );
//----------------------------------------------------------------------------
void
reg_put_qq(
    uint8_t                     op_code,
    uint16_t                    data
    );
//----------------------------------------------------------------------------

/****************************************************************************/

#endif                      //    REGISTERS_H