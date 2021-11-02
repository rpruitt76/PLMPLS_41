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
* File Name		: usb_fud.c
* Version 		: 1.00
* Device 		: Renesas RX630 (or generic)
* Tool Chain 	: HEW
* H/W Platform	: RSK Generic
* Description 	: Flash Update Routines
			Uses the USB MSD drivers
         Uses the Flash Api drivers
******************************************************************************/
/******************************************************************************
* History 		: 2012 Ver. 1.00 First Release
******************************************************************************/

/***********************************************************************************
System Includes
***********************************************************************************/
#include <string.h>
#include <stdio.h>

/***********************************************************************************
User Includes
***********************************************************************************/
#include "usb_common.h"
#include "iodefine.h"
#include "usb_fud.h"
#include "ram_disk.h"
#include "device_id.h"
#include "LaserPShrt.h"

/***********************************************************************************
Modular Variables
***********************************************************************************/
FudStates fudState;        ///< Tracks the operating state of the update device

uint8_t  timeToReset = 0;  ///< Flag that indicates to USB stack that is time to reset

// Sized big enough to handle a 255 byte srec line
uint8_t  sData[256];    ///< Holds Ascii to binary data
uint32_t mAddress;      ///< srec line to program
char     mLine[640];    ///< Holds next srec line in Ascii

// Flash buffer variables
#define PBUF_SIZE    256
uint8_t  pBuf[PBUF_SIZE];  ///< program buffer (256 bytes for rx630)
uint32_t pBufFirst;        ///< address of first data byte in pBuf
uint32_t pBufLast;         ///< address of last data byte in pBuf

// Status variables
char        tLine[128];             ///< Temp buffer to build status lines
char        progStatusText[255];    ///< Status text to write to RAM Drive
int         progByteCount;          ///< Program byte count
int         progLineCount;          ///< Program line count
uint32_t    progCksm;               ///< Program Checksum

/***********************************************************************************
Private Functions
***********************************************************************************/

/**********************************************************************
* Outline 		: ResetDevice
* Description 	: Reset and Re-enumerate USB MSD
*				  
* Argument  	: none
* Return value  : none
**********************************************************************/
void ResetUsbDevice(void)
{
   int i;
   
   DEBUG_MSG_LOW(("USB_FUD: Reset USB DP to re-enumerate."));


   // Clear the USB DP Pull UP
   USB0.SYSCFG.BIT.DPRPU = 0;
   
   for (i=0; i<10000000; ++i)
   {}
   
   // Reset Pull up
   USB0.SYSCFG.BIT.DPRPU = 1;
    
} // Reset Device

/**********************************************************************
* Outline 		: ProgramError
* Description 	: Called when a programming error is discovered.  Updates
*                 progStatusText, which is reported back in ERROR.TXT
*   
*				  
* Argument  	:  err   error description string
* Return value  : none
**********************************************************************/

void ProgramError(char *err)
{
   // Set state variables
   fudState = FudState_Error;

   strcat(progStatusText, err);
}

/**********************************************************************
* Outline 		: UpdateResultFile
* Description 	: Updates the name and content of the status result file
*                 in the MSD after re-enumeration
*                Updates the File Entry and Data cluster.
*   
*				  
* Argument  	: none
* Return value  : none
**********************************************************************/
void UpdateResultFile(void)
{
   uint8_t newSize;

   // Check for successful write
   if (fudState == FudState_Finished)
   {
      // Change Filename in FAT
      WriteIntoRamDisk(g_RAMDRIVE_FILE, ADD_FILENAME, (uint8_t*)"SUCCESS ", 8);

      // update data when file is opened.
      sprintf(tLine, "Programmed Bytes: 0x%x\r\n", progByteCount);
      strcat(progStatusText, tLine);

      sprintf(tLine, "Program Checksum: 0x%08x\r\n", progCksm);
      strcat(progStatusText, tLine);
   } // if SystemSuccess
   
   // System Error
   else 
   {
      // Change Filename in FAT
      WriteIntoRamDisk(g_RAMDRIVE_FILE, ADD_FILENAME, (uint8_t*)"ERROR   ", 8);

   } // else SystemError

   // Write result data into RAMDisk in either case
   WriteIntoRamDisk(g_RAMDRIVE_DATA, 0, (uint8_t*)progStatusText, 255);

   // Change file size
   newSize = 255;
   WriteIntoRamDisk(g_RAMDRIVE_FILE, ADD_FILESIZE, &newSize, 1);
}

/**********************************************************************
* Outline 		: ClearPBuf
* Description 	: Clears the program buffer
*   
*				  
* Argument  	: none
* Return value  : none
**********************************************************************/
void ClearPBuf(void)
{
   memset(pBuf, 0xff, PBUF_SIZE);
   pBufFirst = pBufLast = 0;
} // ClearPBuf

/**********************************************************************
* Outline 		: AddByteToPBuf
* Description 	: Adds a byte to the current program buffer.  If the 
*                 address in is range, the byte is simply added.  If 
*                 out of range, the buffer is programmed and a bew buffer
*                 is set up.  Boundaries are calculated.
*   
*				  
* Argument  	:  add:  address of byte to add
                  data  data to write
* Return value  : none
**********************************************************************/
void AddByteToPBuf(uint32_t add, uint8_t data)
{
   // check for byte in pBuf address range
   if (add >= pBufFirst && add <= pBufLast)
   {
      pBuf[add - pBufFirst] = data;
   } // if data fits
   else
   {
      // Not a new buffer, program old and clear
      if (pBufFirst != 0)
      {
    	  R_FLASH_Write((uint32_t)pBuf, pBufFirst, PBUF_SIZE);
         ClearPBuf();
      } // program current buffer

      // New buffer at this point, add data and set boundaries
      pBufFirst = add & 0xffffff00;
      pBufLast  = pBufFirst + PBUF_SIZE - 1;
      pBuf[add-pBufFirst] = data;
   } // else need a new pBuf

   // Update the status counters
   progCksm += data;
   ++progByteCount;
} // AddByteToPBuf

/**********************************************************************
* Outline 		: ConvertCharToBin
* Description 	: Converts a single character to equiv binary
*   
*				  
* Argument  	: c   ascii character
* Return value  : binary equiv
**********************************************************************/
int ConvertCharToBin(uint8_t c)
{
  int retval = 0;

  if (c >= '0' && c <= '9')
     retval = c & 0xf;

  else if (c >= 'A' && c <= 'F')
     retval = c - 0x37;
  
  return retval;
} // ConvertCharToBin

/**********************************************************************
* Outline 		: CopyAsciiToBinary
* Description 	: Converts a sting of ascii characters to array of binary
*                 equivalents.
*   
*				  
* Argument  	:  *line    line of ascii hex characters (0 terminated)
                  *data    (output) converted data.  Must be allocated by 
                           caller.
* Return value  : numer of converted characters
**********************************************************************/
int CopyAsciiToBinary(char *line, uint8_t *data)
{
   int retval = 0;

   while (*line != 0)
   {
      *data = ConvertCharToBin(*line++)*16;
      *data += ConvertCharToBin(*line++);
      
      ++data;
      ++retval;
   }

   return retval;
} // CopyAsciiToBinary

/**********************************************************************
* Outline 		: EraseAllFlash
* Description 	: Erase all user Flash
*   
*				  
* Argument  	: none
* Return value  : none
**********************************************************************/
void EraseAllFlash(void)
{
   uint16_t block;
   uint8_t result;

   // Erase the FVT area
   result = R_FLASH_Erase(FLASH_CF_BLOCK_0, 1);

   // Erase all blocks
   for (block = (uint16_t)USER_FLASH_START_BLOCK; block <= (uint16_t)USER_FLASH_END_BLOCK; ++block)
   {
      result = R_FLASH_Erase((flash_block_address_t)block, 1);
      if (result !=0)
         break;
   }
} // EraseAllFlash


/***********************************************************************************
Public Functions
***********************************************************************************/

/**********************************************************************
* Outline 		: InitFud
* Description 	: Initialize the Flash Update Device.
*                 Called from: CBCable() in usb_msc.c
*				  
* Argument  	: none
* Return value  : none
**********************************************************************/
void InitFud(void)
{
   // Reset State Variables
   fudState = FudState_Idle;

   // Reset the RAM disk
   RamDiskInit();

   // Clear error line
   memset(mLine, 0, sizeof(mLine));
} // InitFud

/**********************************************************************
* Outline 		: TestFudReset
* Description 	: Called by SCSI module of USB stack on reception of
*                 every TEST_UNIT_READY command from Host.
*                 Test to see if a USB device reset was requested.
*   
*				  
* Argument  	: none
* Return value  : none
**********************************************************************/
void TestFudReset(void)
{
   if (timeToReset)
   {
      timeToReset = 0;
      ResetUsbDevice();  
   }
} // TestFudReset

/**********************************************************************
* Outline 		: JumpToApplication
* Description 	: Jumps to user application at Vector specified by macro
*                 FL_TARGET_REST_VECT_ADDR.  If no vector, program continues.
*                 Called by CBCable->Disconnected in SCSI module of USB stack
*				  
* Argument  	: none
* Return value  : none
**********************************************************************/
void JumpToApplication(void)
{
   uint32_t    *trgt_vctr_tmp;
   char tempstr[80];
	void (*trgt_fnc)(void);   

  
   /* ==== Set target reset vector ==== */
	trgt_vctr_tmp = (uint32_t *)FL_TARGET_REST_VECT_ADDR;  

	if(*trgt_vctr_tmp != 0xFFFFFFFFu)
   {
      //DEBUG_MSG_LOW(("USB_FUD: Jumping to application @ 0x%08x", (uint32_t) *trgt_vctr_tmp));

	  sprintf(tempstr,"USB_FUD: Jumping to application @ 0x%08x", (uint32_t) *trgt_vctr_tmp);
	  DEBUG_MSG_LOW((tempstr));

		/* ==== Call user function ==== */
		trgt_fnc = (void (*)())(*trgt_vctr_tmp);
		trgt_fnc();
	}
	else
   {
      DEBUG_MSG_LOW(("USB_FUD: No Application Loaded.  Continue Bootloader."));
		//while(1);
	}    
} // JumpToApplication

/**********************************************************************
* Outline 		: ProcessFud
* Description 	: Processes the current buffer once filled.  Called by 
*                 SCSI module of USB stack when the data buffer is filled
*                 by host.
*   
*				  
* Argument  	:  numBytes:   Number of bytes in buffer
                  *pBuffer:   data buffer pointer
* Return value  : current FUD state
**********************************************************************/

int ProcessFud(uint32_t numBytes, uint8_t* pBuffer)
{
   uint8_t sum=0;
   char tempstr[80];
   int dc;

   // Check for file sector state (test for proper extension)
   if (fudState == FudState_FileSector)
   {
      
      // File check test goes here
      //if (pBuffer[0x68] != 'M' || pBuffer[0x69] != 'O' || pBuffer[0x6A] != 'T')
      //   fudState = FudState_Idle;  //FudState_Error;
      //else 
      //   fudState = FudState_Idle;
      fudState = FudState_WaitData;
   }

   // Check for programming state
   else if (fudState == FudState_Programming)
   {
      //DEBUG_MSG_MID(("USB_FUD: Programming data, %i bytes in cluster.", numBytes));

	  sprintf(tempstr,"USB_FUD: Programming data, %i bytes in cluster.", numBytes);
	  DEBUG_MSG_MID((tempstr));
	  // Process data in buffer
      while (numBytes)
      {
         // Add data to Ascii string
         if (*pBuffer >= '0' && *pBuffer <= 'Z')
         {
            strncat(mLine, (const char*)pBuffer, 1);
         } // if valid character
         else if (*pBuffer == 0x0d)
         {
            // Test for Valid S record line (begins with 'S')
            if (mLine[0] != 'S')
            {
               sprintf(tLine, "PROGRAM ERROR: Invalid S-Record, line: %i", progLineCount);
               ProgramError(tLine);

               timeToReset = 1;

               // Update the result file
               UpdateResultFile();
               
               goto FudProcessEnd;

            } // if S record line invalid

            // convert Ascii string to binary array
            // The S# byte is converted to 0#
            dc = CopyAsciiToBinary(mLine, sData);

            ++progLineCount;

            // Test Checksum
            sum = 0;
            for (int i=1; i<(dc); ++i) sum += sData[i];
            if (sum != 0xff)
            {
               sprintf(tLine, "PROGRAM ERROR: Checksum S-Record, line: %i.  Expected 0x%02x, Calc 0x%02x\r\n", 
                  progLineCount,
                  sData[dc-1],
                  (uint8_t)~(sum-sData[dc-1])
                  );
               ProgramError(tLine);

               timeToReset = 1;

               // Update the result file
               UpdateResultFile();
               
               goto FudProcessEnd;
            } // if checksum error

            // Decode S record line
            switch(sData[0])
            {
               // S0:  Block Header
               case 0:
                  	
					/* S0 record must contain the appropriate device ID string.  Failure to match result sin error */
				  	for( i=0;i<DEVICE_ID_LENGTH;i++ )
						{
						if( sData[i+4] != device_id_string[i] )
							{
						   	sprintf(tLine, "PROGRAM ERROR: Incorrect file for this device.\r\n");
		                    ProgramError(tLine);

		                    timeToReset = 1;

		                    // Update the result file
		                    UpdateResultFile();
               
		                    goto FudProcessEnd;  
							}
						}
				  
				  /* Set flag that s0 is valid */
				  s0_valid = 1;
				  
				  /* Device ID is a match */
                  EraseAllFlash();
                  
                  // Setup report variables
                  progLineCount = 0;
                  progByteCount = 0;
                  progCksm = 0;
                  memset(progStatusText, 0, sizeof(progStatusText));

                  break;

               // S3:  32 Bit address data record
               case 3:
					/* Test valid S0 record recvd */
					if( !s0_valid )
						{
					   	sprintf(tLine, "PROGRAM ERROR: Incorrect file for this device.\r\n");
	                    ProgramError(tLine);

	                    timeToReset = 1;

	                    // Update the result file
	                    UpdateResultFile();
   
	                    goto FudProcessEnd; 
						}

                  // build address
                  mAddress =  sData[5] +
                              (sData[4] << 8) +
                              (sData[3] << 16) +
                              (sData[2] << 24);
                  
                  // Test address to be sure we are not writing on boot loader
                  if ((mAddress >= BOOT_ADDRESS_LOW) && (mAddress <= BOOT_ADDERSS_HIGH))
                  {
                     sprintf(tLine, "PROGRAM ERROR: Invalid Address: 0x%08x.\r\n", 
                        mAddress);
                     ProgramError(tLine);

                     timeToReset = 1;

                     // Update the result file
                     UpdateResultFile();
               
                     goto FudProcessEnd;                     
                  } // if address is in boot area

                  // Get Data Byte Count
                  dc = sData[1] - 5;  // 4 bytes address, 1 byte cksm

                  // Write bytes to pBuf to be programmed into Flash
                  for (int i=0; i<dc; ++i)
                     AddByteToPBuf(mAddress + i, sData[6+i]);

                  break;

               // S7-9:  Block End marker
               case 7:
               case 8:
               case 9:
					/* Test valid S0 record recvd */
					if( !s0_valid )
						{
					   	sprintf(tLine, "PROGRAM ERROR: Incorrect file for this device.\r\n");
	                    ProgramError(tLine);

	                    timeToReset = 1;

	                    // Update the result file
	                    UpdateResultFile();
   
	                    goto FudProcessEnd; 
						}
                  // Flush last pBuf
                  if (pBufFirst != 0)
                  {
                	 R_FLASH_Write((uint32_t)pBuf, pBufFirst, PBUF_SIZE);
                     ClearPBuf();
                  } // program current buffer                  // Update the FAT with results
                  
                  // Reset the MSC connection
                  //ResetDevice();
                  timeToReset = 1;

                  // Update the result file
                  fudState = FudState_Finished;
                  UpdateResultFile();
                  goto FudProcessEnd;                
                  break;

               default:
                  // Unknown srec line error
                  break;

            } // switch            
            
            // clear the string
            memset(mLine, 0, sizeof(mLine)); 

         } // end of line character
         else
         {
            // ignore all other characters 
            // including the 0x0a that follows the 0x0d
         } // other character
         --numBytes;
         ++pBuffer;

      } // while
      
      fudState = FudState_WaitData;
   } // if FudStateProgram

FudProcessEnd:
   return (int)fudState;
} // ProcessFud


void SetFudFileSector(void)
{
   if (fudState == FudState_Idle)
      fudState = FudState_FileSector;
}

/**********************************************************************
* Outline 		: SetFudProgramming
* Description 	: Attempts to set next state to Programming
*   
*				  
* Argument  	: none
* Return value  : none
**********************************************************************/
void SetFudProgramming(void)
{
   if (fudState == FudState_WaitData)
   {
      // Set Next State
      fudState = FudState_Programming;
   }
} // SetFudProgramming

/**********************************************************************
* Outline 		: SetFudError
* Description 	: Set state to error.  Nothing else can happen when in 
*                 error state.
*   
*				  
* Argument  	: none
* Return value  : none
**********************************************************************/
void SetFudError(void)
{
   fudState = FudState_Error;
} // SetFudError

/**********************************************************************
* Outline 		: GetFudState
* Description 	: Return current FUD state
*   
*				  
* Argument  	: none
* Return value  : current FUD state
**********************************************************************/
FudStates GetFudState(void)
{
   return fudState;
} // GetFudState

/**********************************************************************
* Outline 		: SetFudState
* Description 	: Force FUD state.  Should only be used for test.
*   
*				  
* Argument  	:  newState:   new FUD state
* Return value  : current FUD state
**********************************************************************/
void SetFudState(FudStates newState)
{
   fudState = newState;
} // SetFudState
