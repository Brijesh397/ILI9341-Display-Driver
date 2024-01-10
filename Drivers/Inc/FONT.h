/****************************************FILE DESCRIPTION**************************************/
/* FILE 		: FONT.h
* PROJECT 		: HAL Library for STM32F4xx
* PROGRAMMER 	: Brijesh Mehta
* DESCRIPTION 	: Font Header File
*/
/*********************************************************************************************/

#ifndef DRIVER_INC_FONT_H_
#define DRIVER_INC_FONT_H_

/****************** Includes *****************************/
#include <stdint.h>

/********************Font Handler Structure ***************************/
typedef struct
{
	uint16_t ascii_value;	//Ascii value of the character

	uint16_t  char_value;	//Actual Character

	uint16_t start;			//Start position of  Character inside the font array

	uint16_t clipping;		/* The amount of blank columns inside the specified font grid
							 * So if the font is 24x24 and the character is just utilizing
							 * 20 columns then you clip the remaining 4 columns to avoid unnecessary
							 * space between two characters.
							 */
}Font_Handler_t;

#endif /* DRIVER_INC_FONT_H_ */
