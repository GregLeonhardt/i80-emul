/*******************************  COPYRIGHT  ********************************/
/*
 *  Author? "Gregory N. Leonhardt"
 *  License? "CC BY-NC 2.0"
 *           "https://creativecommons.org/licenses/by-nc/2.0/"
 *
 ****************************************************************************/

#ifndef CALL_H
#define CALL_H

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

//------------------------------------------------------------------------ 281
void
call_nn_i80(
    uint8_t                     op_code
    );
//------------------------------------------------------------------------ 283
void
call_ccnn_i80(
    uint8_t                     op_code
    );
//------------------------------------------------------------------------ 285
void
ret_i80(
    uint8_t                     op_code
    );
//------------------------------------------------------------------------ 286
void
ret_cc_i80(
    uint8_t                     op_code
    );
//------------------------------------------------------------------------ 292
void
rst_t_i80(
    uint8_t                     op_code
    );
//------------------------------------------------------------------------ 288
void
reti_ED(
    uint8_t                     op_code
    );
//------------------------------------------------------------------------ 290
void
retn_ED(
    uint8_t                     op_code
    );
//----------------------------------------------------------------------------
int
call_post(
    void
    );
//----------------------------------------------------------------------------

/****************************************************************************/

#endif                      //    CALL_H