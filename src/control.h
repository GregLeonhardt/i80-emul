/*******************************  COPYRIGHT  ********************************/
/*
 *  Author? "Gregory N. Leonhardt"
 *  License? "CC BY-NC 2.0"
 *           "https://creativecommons.org/licenses/by-nc/2.0/"
 *
 ****************************************************************************/

#ifndef CONTROL_H
#define CONTROL_H

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

//------------------------------------------------------------------------ 180
void
control_nop_i80(
    uint8_t                     op_code
    );
//------------------------------------------------------------------------ 181
void
control_hlt_i80(
    uint8_t                     op_code
    );
//------------------------------------------------------------------------ 182
void
control_di_i80(
    uint8_t                     op_code
    );
//------------------------------------------------------------------------ 183
void
control_ei_api(
    uint8_t                     op_code
    );
//------------------------------------------------------------------------ 184
void
control_im_ED(
    uint8_t                     op_code
    );
//----------------------------------------------------------------------------

/****************************************************************************/

#endif                      //    CONTROL_H