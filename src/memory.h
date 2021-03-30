/*******************************  COPYRIGHT  ********************************/
/*
 *  Author? "Gregory N. Leonhardt"
 *  License? "CC BY-NC 2.0"
 *           "https://creativecommons.org/licenses/by-nc/2.0/"
 *
 ****************************************************************************/

#ifndef MEMORY_H
#define MEMORY_H

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

//----------------------------------------------------------------------------
void
memory_init(
    void
    );
//----------------------------------------------------------------------------
void
memory_load(
    uint16_t                    address,
    uint16_t                    size,
    uint8_t                 *   data_p
    );
//----------------------------------------------------------------------------
void
memory_read(
    uint8_t                 *   data_p,
    uint16_t                    size,
    uint16_t                    address
    );
//----------------------------------------------------------------------------
uint8_t
memory_get_8(
    uint16_t                    address
    );
//----------------------------------------------------------------------------
uint16_t
memory_get_16(
    uint16_t                    address
    );
//----------------------------------------------------------------------------
uint16_t
memory_put_16_p(
    uint16_t                    address,
    uint16_t                    data
    );
//----------------------------------------------------------------------------
uint16_t
memory_get_16_p(
    uint16_t                    address
    );
//----------------------------------------------------------------------------
void
memory_put_8(
    uint16_t                    address,
    uint8_t                     data
    );
//----------------------------------------------------------------------------
void
memory_put_16(
    uint16_t                    address,
    uint16_t                    data
    );
//----------------------------------------------------------------------------
uint16_t
memory_get_16_pc_p(
    void
    );
//----------------------------------------------------------------------------
int
memory_post(
    void
    );
//----------------------------------------------------------------------------
void
memory_dump(
    uint16_t                    address,
    uint16_t                    length
    );
//----------------------------------------------------------------------------

/****************************************************************************/

#endif                      //    MEMORY_H