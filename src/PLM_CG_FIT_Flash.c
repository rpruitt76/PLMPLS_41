/***************************************************************/
/*                                                             */
/*      PROJECT NAME :  PLM_CG_FIT_Flash                       */
/*      FILE         :  PLM_CG_FIT_Flash.c                     */
/*      DESCRIPTION  :  Main Program                           */
/*      CPU SERIES   :  RX600                                  */
/*      CPU TYPE     :  RX64M                                  */
/*                                                             */
/*      This file is generated by e2 studio.                   */
/*                                                             */
/***************************************************************/                              
                                                                           
                                                                           
                                                                           
                                                                          
/***********************************************************************/
/*                                                                     */
/*  FILE        :Main.c or Main.cpp                                    */
/*  DATE        :Tue, Oct 31, 2006                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :                                                      */
/*                                                                     */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
//#include "typedefine.h"
#include "r_flash_rx_if.h"
#ifdef __cplusplus
//#include <ios>                        // Remove the comment when you use ios
//_SINT ios_base::Init::init_cnt;       // Remove the comment when you use ios
#endif

void main(void);
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

void main(void)
{
	flash_err_t err;

	// Initialize the API.
	err= R_FLASH_Open();

	// Check for errors.
	if (FLASH_SUCCESS != err)
	{
		while(1)
		{

		}
	}

}

#ifdef __cplusplus
void abort(void)
{

}
#endif