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
* File Name		: ram_disk.c
* Version 		: 1.00
* Device 		: Renesas Generic MCU.
* Tool Chain 	: HEW
* H/W Platform	: RSK Generic
* Description 	: Simple RAM Disk.
			Accesses RAM like a block driver.
			Provides access directly to the RAM.
			Initialised with a FAT file system as stored
			in section FATExample.
***********************************************************************************/
/***********************************************************************************
* History 		: 23.01.2012 Ver. 1.00 First Release
***********************************************************************************/

/***********************************************************************************
System Includes
***********************************************************************************/
#include <string.h>

/***********************************************************************************
User Includes
***********************************************************************************/
//#include "FAT_Image_Arrays.h"
#include "ram_disk.h"
#include "usb_fud.h"


/***********************************************************************************
Defines
***********************************************************************************/
/*	If FORMAT_WITH_FAT_Example is defined then the RAM disk will
	be initialised with the data in the FATExample section.
	This can be a FAT image.
	If FORMAT_WITH_FAT_Example is not defined then the RAM disk
	will be unformatted. This will cause Windows to ask if you want
	to format it.*/
#define FORMAT_WITH_FAT_Example
//#define SINGLE_FAT_BINARY

/***********************************************************************************
Variables
***********************************************************************************/
/*The RAM storage*/	
/*NOTE1: When using this as an example on other hardware where external RAM may be
avialable you can create the disk in the external space. To do this locate the
g_RAM_DATA array in external memory. In this case the size of the RAM disk can
be increased using the "NUM_BLOCKS" define above. Please also note the
limitation below.*/	
//static uint8_t g_RAM_DATA[NUM_BLOCKS*(BLOCK_SIZE)];
static uint8_t g_RAM_WRITE_DATA[0x10000];

uint8_t   g_RAMDRIVE_MBR[4096];
uint8_t   g_RAMDRIVE_FAT[512];
uint8_t   g_RAMDRIVE_DATA[512];
uint8_t   g_RAMDRIVE_FILE[512];
uint8_t   g_RAMDRIVE_OTHER[1024];

int currentLba;

//static uint8_t Fake_RAM_DATA[4096];      ///< Fake RAM disk buffer


void WriteIntoRamDisk(uint8_t *buffer, uint32_t offset, uint8_t *data, uint32_t count)
{
   while (count)
   {
      buffer[offset] = *data;
      ++data;
      ++offset;
      --count;
   }
}


/**********************************************************************
* Outline 		: RamDiskInit
* Description 	: Initialise this RAM disk.
*				  Copies the contents in section FATExample to it.
* Argument  	: none
* Return value  : none
**********************************************************************/

void RamDiskInit(void)
{
	#ifdef FORMAT_WITH_FAT_Example
	
		   #ifdef SINGLE_FAT_BINARY
		
			   /*FATExample section is where an image of a FAT file system is.
			    The image was created by being copied from RAM, using an emulator,
			    after Windows had formatted it.*/
			   memcpy(&g_RAM_DATA, (void*)__sectop("FATExample_00"),
					    (size_t)NUM_BLOCKS*BLOCK_SIZE);
		   #else /*NOT SINGLE_FAT_BINARY*/
		

			/* In order to conserve ROM the whole FAT image has not been stored:
			The parts of the FAT image that contain non zero data have been
			seperated out into 4 seperate sections.*/
			
			size_t SectionSize;
			
			/*Start by setting whole whole RAMDisk data to zero and then
			can copy in the sections that contain non-zero data */
			//memset(g_RAM_DATA, 0, (size_t)NUM_BLOCKS*BLOCK_SIZE);
			
			/*1st section at offse 0   MASTER BOOT SECTOR */
			SectionSize = (size_t)__secend("FATExample_MBR")-(size_t)__sectop("FATExample_MBR");	
			memcpy((void*)g_RAMDRIVE_MBR, (void*)__sectop("FATExample_MBR"), SectionSize);
				
			/*2nd section at offset h'C00*/
			SectionSize = (size_t)__secend("FATExample_FAT")-(size_t)__sectop("FATExample_FAT");	
			memcpy((void*)g_RAMDRIVE_FAT, (void*)__sectop("FATExample_FAT"), SectionSize );

			/*4th section at offset h'5000  FAT Entry*/
			SectionSize = (size_t)__secend("FATExample_FILE")-(size_t)__sectop("FATExample_FILE");	
			memcpy((void*)g_RAMDRIVE_FILE, (void*)__sectop("FATExample_FILE"), SectionSize);
	
			/*5th section at offset h'5600  FILE DATA*/
			SectionSize = (size_t)__secend("FATExample_DATA")-(size_t)__sectop("FATExample_DATA");	
			memcpy((void*)g_RAMDRIVE_DATA, (void*)__sectop("FATExample_DATA"), SectionSize);         
         #endif		
	#else /*FORMAT_WITH_FAT_Example*/
	
		/*Zero all, then Windows will ask for it to be formatted*/
		memset(g_RAM_DATA, 0, (size_t)NUM_BLOCKS*BLOCK_SIZE);	
	#endif
}
/**********************************************************************************
End of function RamDiskInit
***********************************************************************************/   

/**********************************************************************
* Outline 		: RamDiskGetBlockSize
* Description 	: The RAM is split into blocks.
*				  This returns the size of a block.
* Argument  	: none
* Return value  : Block size in bytes.
**********************************************************************/

uint16_t RamDiskGetBlockSize(void)
{
	return BLOCK_SIZE;
}
/**********************************************************************************
End of function RamDiskGetBlockSize
***********************************************************************************/   

/**********************************************************************
* Outline 		: RamDiskGetNumBlocks
* Description 	: The RAM is split into blocks.
*				  This returns the number of blocks.
* Argument  	: none
* Return value  : Number of blocks. 
**********************************************************************/

uint16_t RamDiskGetNumBlocks(void)
{
	//return NUM_BLOCKS;
   //return FAKE_NUM_BLOCKS;
      //return 10*1024;
   return DISK_BLOCK_COUNT;
}
/**********************************************************************************
End of function RamDiskGetNumBlocks
***********************************************************************************/   

/**********************************************************************
* Outline 		: RamDiskGetBufferRead
* Description 	: Provides direct access to the RAM at a specified LBA.
                 Host Read.
* Argument  	: _LBA: Logical Block Address
* Return value  : Pointer to the actual RAM.
**********************************************************************/
uint8_t* RamDiskGetBufferRead(uint16_t _LBA)
{
   uint8_t *retval = 0;
   
   if (_LBA == LBA_MBR)
      retval = g_RAMDRIVE_MBR;
   else if (_LBA == LBA_FAT || _LBA == 8)
      retval = g_RAMDRIVE_FAT;
   else if (_LBA == LBA_DATA)
      retval = g_RAMDRIVE_DATA;
   else if (_LBA == LBA_FILE)
      retval = g_RAMDRIVE_FILE;
   else 
      retval = g_RAMDRIVE_OTHER;
      
   return retval;
	//return (uint8_t*)( (unsigned long)g_RAM_DATA + (_LBA*BLOCK_SIZE));
   //return g_RAM_WRITE_DATA;
} // RamDiskGetBufferRead


/**********************************************************************
* Outline 		: RamDiskGetBufferWrite
* Description 	: Provides direct access to the RAM at a specified LBA.
                 Host Write.  Does not update the RAM drive.
* Argument  	: _LBA: Logical Block Address
* Return value  : Pointer to the actual RAM.
**********************************************************************/
uint8_t* RamDiskGetBufferWrite(uint16_t _LBA, uint32_t _bytes)
{
   uint8_t *retval;
   currentLba = _LBA;   
   
   // Determine file type of dragged file
   if (_LBA == LBA_FILE)
   {
      SetFudFileSector();
   } // file file entry lba
   
   // Determine if the current buffer will be processed by FUD when full
   if (_LBA > LBA_DATA)
   {
      SetFudProgramming();
   }

   // Return the working buffer
   retval = (uint8_t*)( (unsigned long)g_RAM_WRITE_DATA);

	return retval;
} // RamDiskGetBufferWrite

#ifdef GETNEWFAT
uint8_t* RamDiskGetBufferWrite(uint16_t _LBA, uint32_t _bytes)
{
   uint8_t *retval = g_RAMDRIVE_OTHER;
   currentLba = _LBA;
   
   if (_LBA == LBA_MBR)
      retval = g_RAM_WRITE_DATA;
   else if (_LBA == 6)
      retval = g_RAM_WRITE_DATA;
   else if (_LBA == 7)
      retval = g_RAM_WRITE_DATA;
   else if (_LBA == 40)
      retval = g_RAM_WRITE_DATA;
   else if (_LBA == 16383)
      retval = g_RAM_WRITE_DATA;
   else
      retval = g_RAM_WRITE_DATA;   
      
   return retval;
	//return (uint8_t*)( (unsigned long)g_RAM_DATA + (_LBA*BLOCK_SIZE));
} // RamDiskGetBufferRead
#endif

uint8_t*	RamDiskGetWorkingBuffer(void)
{
   return g_RAM_WRITE_DATA;
} // 

