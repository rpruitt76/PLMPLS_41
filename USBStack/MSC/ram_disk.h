/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*******************************************************************************/
/* Copyright (C) 2012 Renesas Electronics Corporation. All rights reserved.   */
/*******************************************************************************
* File Name		: ram_disk.h
* Version 		: 1.00
* Device 		: Renesas Generic MCU.
* Tool Chain 	: HEW
* H/W Platform	: RSK Generic
* Description 	: Simple RAM Disk.
			Accesses RAM like a block driver.
			Provides access directly to the RAM.
			Initialised with a FAT file system as stored
			in section FATExample.
******************************************************************************/
/******************************************************************************
* History 		: 23.01.2012 Ver. 1.00 First Release
******************************************************************************/

#ifndef RAM_DISK_H
#define RAM_DISK_H

/******************************************************************************
Sysyem Includes
******************************************************************************/
#include <stdint.h>


/******************************************************************************
Global Variables
******************************************************************************/
extern  uint8_t   g_RAMDRIVE_MBR[];
extern  uint8_t   g_RAMDRIVE_FAT[];
extern  uint8_t   g_RAMDRIVE_DATA[];
extern  uint8_t   g_RAMDRIVE_FILE[];
extern  uint8_t   g_RAMDRIVE_OTHER[];

/******************************************************************************
Function Prototypes
******************************************************************************/
void		RamDiskInit(void);
uint16_t	RamDiskGetBlockSize(void);
uint16_t	RamDiskGetNumBlocks(void);
//uint8_t*	RamDiskGetBuffer(uint16_t _LBA);
uint8_t* RamDiskGetBufferWrite(uint16_t _LBA, uint32_t _bytes);
uint8_t* RamDiskGetBufferRead(uint16_t _LBA);

uint8_t*	RamDiskGetWorkingBuffer(void);

void     WriteIntoRamDisk(uint8_t *buf, uint32_t add, uint8_t *data, uint32_t count);

//uint8_t*	FakeRamDiskGetBuffer(uint16_t _LBA);    ///< Used to return the fake RAM disk buffer


/******************************************************************************
RAM Drive parameters
******************************************************************************/

/// Pre-Rolled Ram Drive FAT Parameters
// LBA values
#define LBA_MBR      0
#define LBA_FAT      24
#define LBA_FILE     40
#define LBA_DATA     80    ///< LBA value of data record for READY.TXT
                           ///< A new file's data will start at LBA 44
// LBA address offsets
//#define ADD_MBR      (LBA_MBR * BLOCK_SIZE)
//#define ADD_FAT      (LBA_FAT * BLOCK_SIZE)
//#define ADD_FILE     (LBA_FILE * BLOCK_SIZE)
//#define ADD_DATA     (LBA_DATA * BLOCK_SIZE)

// First file in root directory offsets
#define ADD_FILENAME (0x40)  ///< FileName Offset into FILE entry
#define ADD_FILESIZE (0x5c)  ///< File data size offset into FILE entry

#define RAM_DISK_SIZE      16       ///< Size of RAM Disk in MB
#define DISK_BLOCK_COUNT   (RAM_DISK_SIZE * 2048)

#define NUM_BLOCKS 0x00000030 /*Number of logical blocks */
#define BLOCK_SIZE 0x00000200 /*512 BYTES within a block*/



#define FAKE_NUM_BLOCKS 0x00100000
/*RAM_DISK_H*/
#endif 