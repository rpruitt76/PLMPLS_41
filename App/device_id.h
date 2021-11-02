/* Parameters used to confirm correct file to program */

#define DEVICE_ID_LENGTH	8		// SREC output form hew truncates at 8 characters		
unsigned char i;					// index used in for loop
unsigned char s0_valid = 0;			// flag to indicate that the s) has been checked and was valid

/* PRODUCT_MAJ, PRODUCT_MIN */
char device_id_string[ DEVICE_ID_LENGTH ] = {'m','9','0','5','_','A','C','U'};		// Change this based on product