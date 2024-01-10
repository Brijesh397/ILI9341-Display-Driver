/****************************************FILE DESCRIPTION**************************************/
/* FILE 		: ILI9341.c
* PROJECT 		: HAL Library for STM32F4xx
* PROGRAMMER 	: Brijesh Mehta
* DESCRIPTION 	: Functions to control the ILI9341 Display
*/
/*********************************************************************************************/


/************************ Includes *************************/
#include "ILI9341.h"

/********************* Function Description *********************************
 * FUNCTION		:	lcdInit
 *
 * DESCRIPTION	:	This function is used to initialize the LCD
 *
 * PARAMETERS	:	SPI_Handle_t *spiHandleStructure - SPI Handle Structure
 *
 * RETURN		:	void
 *
 * **************************************************************************/
void lcdInit(SPI_Handle_t *spiHandleStructure)
{
	//Enabling SPI
	SPI_ENABLE(spiHandleStructure);

	//Intialisation Commands
	lcdReset();
	uint8_t params[15];
	lcdWriteCmd(spiHandleStructure,ILI9341_SWRESET);
	delay(120);
	lcdWriteCmd(spiHandleStructure,ILI9341_POWERB);
	params[0] = 0x00;
	params[1] = 0xD9;
	params[2] = 0x30;
	lcdWriteData(spiHandleStructure,params, 3);

	lcdWriteCmd(spiHandleStructure,ILI9341_POWER_SEQ);
	params[0]= 0x64;
	params[1]= 0x03;
	params[2]= 0X12;
	params[3]= 0X81;
	lcdWriteData(spiHandleStructure,params, 4);

	lcdWriteCmd(spiHandleStructure,ILI9341_DTCA);
	params[0]= 0x85;
	params[1]= 0x10;
	params[2]= 0x7A;
	lcdWriteData(spiHandleStructure,params, 3);

	lcdWriteCmd(spiHandleStructure,ILI9341_POWERA);
	params[0]= 0x39;
	params[1]= 0x2C;
	params[2]= 0x00;
	params[3]= 0x34;
	params[4]= 0x02;
	lcdWriteData(spiHandleStructure,params, 5);

	lcdWriteCmd(spiHandleStructure,ILI9341_PRC);
	params[0]= 0x20;
	lcdWriteData(spiHandleStructure,params, 1);

	lcdWriteCmd(spiHandleStructure,ILI9341_DTCB);
	params[0]= 0x00;
	params[1]= 0x00;
	lcdWriteData(spiHandleStructure,params, 2);

	lcdWriteCmd(spiHandleStructure,ILI9341_POWER1);
	params[0]= 0x1B;
	lcdWriteData(spiHandleStructure,params, 1);

	lcdWriteCmd(spiHandleStructure,ILI9341_POWER2);
	params[0]= 0x12;
	lcdWriteData(spiHandleStructure,params, 1);

	lcdWriteCmd(spiHandleStructure,ILI9341_VCOM1);
	params[0]= 0x08;
	params[1]= 0x26;
	lcdWriteData(spiHandleStructure,params, 2);

	lcdWriteCmd(spiHandleStructure,ILI9341_VCOM2);
	params[0]= 0XB7;
	lcdWriteData(spiHandleStructure,params, 1);

	uint8_t m;
	m = MADCTL_MV | MADCTL_MY| MADCTL_BGR;

	lcdWriteCmd(spiHandleStructure,ILI9341_MAC);    // Memory Access Control <Landscape setting>
	params[0]= m;
	lcdWriteData(spiHandleStructure,params, 1);

	lcdWriteCmd(spiHandleStructure,ILI9341_PIXEL_FORMAT);
	params[0]= 0x55; //select RGB565
	lcdWriteData(spiHandleStructure,params, 1);

	lcdWriteCmd(spiHandleStructure,ILI9341_FRMCTR1);
	params[0]= 0x00;
	params[1]= 0x1B;//frame rate = 70
	lcdWriteData(spiHandleStructure,params, 2);

	lcdWriteCmd(spiHandleStructure,ILI9341_DFC);    // Display Function Control
	params[0]= 0x0A;
	params[1]= 0xA2;
	lcdWriteData(spiHandleStructure,params, 2);

	lcdWriteCmd(spiHandleStructure,ILI9341_3GAMMA_EN);    // 3Gamma Function Disable
	params[0]= 0x02; //LCD_WR_DATA(0x00);
	lcdWriteData(spiHandleStructure,params, 1);

	lcdWriteCmd(spiHandleStructure,ILI9341_GAMMA);
	params[0]= 0x01;
	lcdWriteData(spiHandleStructure,params, 1);

	lcdWriteCmd(spiHandleStructure,ILI9341_PGAMMA);    //Set Gamma
	params[0]= 0x0F;
	params[1]= 0x1D;
	params[2]= 0x1A;
	params[3]= 0x0A;
	params[4]= 0x0D;
	params[5]= 0x07;
	params[6]= 0x49;
	params[7]= 0X66;
	params[8]= 0x3B;
	params[9]= 0x07;
	params[10]= 0x11;
	params[11]= 0x01;
	params[12]= 0x09;
	params[13]= 0x05;
	params[14]= 0x04;
	lcdWriteData(spiHandleStructure,params, 15);

	lcdWriteCmd(spiHandleStructure,ILI9341_NGAMMA);
	params[0]= 0x00;
	params[1]= 0x18;
	params[2]= 0x1D;
	params[3]= 0x02;
	params[4]= 0x0F;
	params[5]= 0x04;
	params[6]= 0x36;
	params[7]= 0x13;
	params[8]= 0x4C;
	params[9]= 0x07;
	params[10]= 0x13;
	params[11]= 0x0F;
	params[12]= 0x2E;
	params[13]= 0x2F;
	params[14]= 0x05;
	lcdWriteData(spiHandleStructure,params, 15);

	lcdWriteCmd(spiHandleStructure,ILI9341_RASET); //page address set
	params[0]= 0x00;
	params[1]= 0x00;
	params[2]= 0x00;
	params[3]= 0xf0; //240 rows = 0xf0
	lcdWriteData(spiHandleStructure,params, 4);

	lcdWriteCmd(spiHandleStructure,ILI9341_CASET);
	params[0]= 0x00;
	params[1]= 0x00;
	params[2]= 0x01;
	params[3]= 0x40; //320 columns = 0x140
	lcdWriteData(spiHandleStructure,params, 4);

	lcdWriteCmd(spiHandleStructure,ILI9341_SLEEP_OUT); //Exit Sleep
	delay(120);
	lcdWriteCmd(spiHandleStructure,ILI9341_DISPLAY_ON); //display on
}

/********************* Function Description *********************************
 * FUNCTION		:	lcdWriteCmd
 *
 * DESCRIPTION	:	This function is used to write a command to the LCD
 *
 * PARAMETERS	:	SPI_Handle_t *spiHandleStructure - SPI Handle Structure
 * 					uint8_t cmd - Command to be written
 *
 * RETURN		:	void
 *
 * **************************************************************************/
void lcdWriteCmd(SPI_Handle_t *spiHandleStructure, uint8_t cmd)
{
	uint8_t tempArr[] = {cmd};

	LCD_CSX_LOW();	//To start transmission
	LCD_DCX_LOW();	//To indicate Command

	spiTransmit(spiHandleStructure, tempArr, 1, 100);	//Transmitting the command

	LCD_CSX_HIGH();//To stop transmission
}

/********************* Function Description *********************************
 * FUNCTION		:	lcdWriteData
 *
 * DESCRIPTION	:	This function is used to write data to the LCD
 *
 * PARAMETERS	:	SPI_Handle_t *spiHandleStructure - SPI Handle Structure
 * 					uint8_t *ptxData - Pointer to the data array
 * 					uint16_t sizeOfData - size of the data to be transmitted
 *
 * RETURN		:	void
 *
 * **************************************************************************/
void lcdWriteData(SPI_Handle_t *spiHandleStructure, uint8_t *ptxData, uint16_t sizeOfData)
{
	LCD_CSX_LOW();	//To start transmission
	LCD_DCX_HIGH();	//To indicate data

	spiTransmit(spiHandleStructure, ptxData, sizeOfData, 100);	//Transmitting the data

	LCD_CSX_HIGH();//To stop transmission
}

/********************* Function Description *********************************
 * FUNCTION		:	lcdReset
 *
 * DESCRIPTION	:	This function is used to reset the LCD
 *
 * PARAMETERS	:	void
 *
 * RETURN		:	void
 *
 * **************************************************************************/
void lcdReset(void)
{
	LCD_RESX_LOW();
	delay(50);
	LCD_RESX_HIGH();
}

/********************* Function Description *********************************
 * FUNCTION		:	lcdSetWriteAre
 *
 * DESCRIPTION	:	This function sets the write area.
 *
 * PARAMETERS	:	SPI_Handle_t *spiHandleStructure - SPI Handle Struct
 * 					uint16_t x1	- first x coordinate
 * 					uint16_t x2 - second x coordinate
 * 					uint16_t y1 - first y coordinate
 * 					uint16_t y2 - second y coordinate
 *
 * RETURN		:	void
 *
 * **************************************************************************/
void lcdSetWriteArea(SPI_Handle_t *spiHandleStructure,uint16_t x1,uint16_t x2,uint16_t y1,uint16_t y2)
{
	uint8_t param[4];
	lcdWriteCmd(spiHandleStructure,ILI9341_CASET);//column address
	param[0] = (x1>>8);	//bit 15-8
	param[1] = (x1);	//bit 7-0
	param[2] = (x2>>8); //bit 15-8
	param[3] = (x2);	//bit 7-0
	lcdWriteData(spiHandleStructure, param, 4);

	lcdWriteCmd(spiHandleStructure,ILI9341_RASET); //page/row address set
	param[0] = (y1>>8);	//bit 15-8
	param[1] = (y1);	//bit 7-0
	param[2] = (y2>>8);	//bit 15-8
	param[3] = (y2);	//bit 7-0
	lcdWriteData(spiHandleStructure, param, 4);
}

/********************* Function Description *********************************
 * FUNCTION		:	lcdSetWriteArea
 *
 * DESCRIPTION	:	This function sets the write area.
 *
 * PARAMETERS	:	SPI_Handle_t *spiHandleStructure - SPI Handle Struct
 * 					uint16_t x1	- first x coordinate
 * 					uint16_t x2 - second x coordinate
 * 					uint16_t y1 - first y coordinate
 * 					uint16_t y2 - second y coordinate
 *
 * RETURN		:	void
 *
 * **************************************************************************/
void lcdWriteArea(SPI_Handle_t *spiHandleStructure,uint8_t *ptxData, uint32_t len, uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2)
{
	lcdSetWriteArea(spiHandleStructure, x1, x2, y1, y2);

	lcdWriteCmd(spiHandleStructure,ILI9341_GRAM);

	LCD_CSX_LOW();	//To start transmission
	LCD_DCX_HIGH();	//To indicate data

	lcdWriteData(spiHandleStructure, ptxData, len);

	LCD_CSX_HIGH();//To stop transmission
}

/********************* Function Description *********************************
 * FUNCTION		:	lcdFill
 *
 * DESCRIPTION	:	This function set the background color
 *
 * PARAMETERS	:	SPI_Handle_t *spiHandleStructure - SPI Handle Struct
 * 					uint16_t color - Color to be set as background
 *
 * RETURN		:	void
 *
 * **************************************************************************/
void lcdFill(SPI_Handle_t *spiHandleStructure,uint16_t color)
{
	/*
	 * 320 pixels per line
	 * 30 lines
	 * 2 values of colour per pixel
	 * so 320*30*2 = 19200
	 */
	uint8_t tempcolarr[19200];
	for(uint16_t i=0;i<19200;i++)
	{
		tempcolarr[i] = color>>8;
		tempcolarr[i+1] = color & 0xFF;
		i++;
	}

	for(uint16_t j=0;j<240;j+=30)	//Writing 30 lines at a time
	{
		lcdWriteArea(spiHandleStructure, tempcolarr,19200,0,320,j,j+30);
	}
}

/********************* Function Description *********************************
 * FUNCTION		:	lcdWritePixel
 *
 * DESCRIPTION	:	This function is used to write a pixel
 *
 * PARAMETERS	:	SPI_Handle_t *spiHandleStructure
 * 					uint16_t color
 * 					uint16_t x
 * 					uint16_t y
 *
 * RETURN		:	void
 *
 * **************************************************************************/
void lcdWritePixel(SPI_Handle_t *spiHandleStructure, uint16_t color, uint16_t x, uint16_t y)
{
	uint8_t tempArr[2];
	tempArr[0] = color>>8;
	tempArr[1] = color & 0xFF;

	lcdSetWriteArea(spiHandleStructure,x,x,y,y);

	lcdWriteCmd(spiHandleStructure,ILI9341_GRAM);
	LCD_CSX_LOW();	//To start transmission
	LCD_DCX_HIGH();	//To indicate data

	lcdWriteData(spiHandleStructure, tempArr, 2);

	LCD_CSX_HIGH();//To stop transmission
}

/********************* Function Description *********************************
 * FUNCTION		:	lcdWriteChar
 *
 * DESCRIPTION	:	This function is used to write a char to the Display
 *
 *
 * PARAMETERS	:	SPI_Handle_t *spiHandleStructure
 * 					char character
 * 					Font_Handler_t font_handler[]
 * 					uint16_t color
 * 					uint16_t x
 * 					uint16_t y
 *
 * RETURN		:	void
 *
 * **************************************************************************/
void lcdWriteChar(SPI_Handle_t *spiHandleStructure,char character,Font_Handler_t font_handler[],uint16_t color,uint16_t x,uint16_t y)
{
	uint8_t font_height = 0;
	uint8_t font_width = 0;
	uint8_t ascii = 0;
	uint16_t start = 0;
	uint16_t end =0;
	uint16_t clipping = 0;
	uint16_t no_of_bytes_per_column = 0;
	uint16_t y1 = y;
	uint16_t counter = 0;
	uint8_t *font;

	if(font_handler == Arial24x24_t)
	{
		font_height = 24;	//16 pixels
		font_width = 24;		//2Bytes = 16 Pixels
		font = (uint8_t*)Arial24x24;
	}
	else if(font_handler == Arial32x32Bold_t)
	{
		font_height = 32;	//16 pixels
		font_width = 32;		//2Bytes = 16 Pixels
		font = (uint8_t*)Arial32x32Bold;
	}

	//Identifying the start and end position of the character inside the font array
	ascii = character;
	//Font Array
	start = font_handler[ascii].start;	//Starting Point of char inside Font Array
	clipping = font_handler[ascii].clipping;//columns to be clipped from the Font Array
	end = start+font_width-clipping;	//End Point of Char inside the Font Array
	no_of_bytes_per_column = font_height/8; //No of Bytes per column inside the Font Array
	counter = start;


	for(uint16_t i=start;i<end;i++)//Counting Columns inside the Font Array
	{
		for(uint16_t j=0;j<no_of_bytes_per_column;j++)//Counting Number of Bytes per column inside the Font Array
		{
			for(int16_t k=7;k>=0;k--)//Counting Number of Bits per Byte (one bit = one pixel)
			{
				if((font[counter]&(1<<k))>=1)	//If the Bit is set then you write the pixel using the color
				{
					lcdWritePixel(spiHandleStructure, color, x, y1);
					y1++;	//Incrementing the Y pos
				}
				else
				{
					/*
					 * If the Bit is not set then write the pixel using the BG color
					 * as if you are over writing already written space then the previously written
					 * character will not be superimposed over the new one
					 */
					lcdWritePixel(spiHandleStructure, BG, x, y1);
					y1++;	//Incrementing the Y pos
				}
			}
			counter++;
		}
		y1=y;
		x++;	//Incrementing the X Pos
	}
}

/********************* Function Description *********************************
 * FUNCTION		:	lcdWriteString
 *
 * DESCRIPTION	:	This function is used to write a string to the Display
 *
 * PARAMETERS	:	SPI_Handle_t *spiHandleStructure
 * 					char *string
 * 					Font_Handler_t font_handler[]
 * 					uint16_t color
 * 					uint16_t x
 * 					uint16_t y
 *
 * RETURN		:	void
 *
 * **************************************************************************/
void lcdWriteString(SPI_Handle_t *spiHandleStructure,char *string,Font_Handler_t font_handler[],uint16_t color,uint8_t spacing,uint16_t x,uint16_t y)
{
	uint8_t font_height = 0;
	uint8_t font_width = 0;
	uint8_t ascii = 0;
	uint8_t len = strlen(string);
	uint16_t start = 0;
	uint16_t end =0;
	uint16_t clipping = 0;
	uint16_t no_of_bytes_per_column = 0;
	uint16_t y1 = 0;
	uint16_t x1 = x;
	uint16_t counter = 0;
	uint8_t *font;

	if(font_handler == Arial24x24_t)
	{
		font_height = 24;	//16 pixels
		font_width = 24;		//2Bytes = 16 Pixels
		font = (uint8_t*)Arial24x24;
	}
	else if(font_handler == Arial32x32Bold_t)
	{
		font_height = 32;	//16 pixels
		font_width = 32;		//2Bytes = 16 Pixels
		font = (uint8_t*)Arial32x32Bold;
	}

	for(uint32_t i=0;i<len;i++)
	{
		ascii = string[i];
		start = font_handler[ascii].start;	//Starting Point of char inside Font Array
		clipping = font_handler[ascii].clipping;//columns to be clipped from the Font Array
		if(ascii == 32)
		{
			end = 8;
		}
		else
		{
			end = start+font_width-clipping;	//End Point of Char inside the Font Array
		}
		no_of_bytes_per_column = font_height/8; //No of Bytes per column inside the Font Array
		counter = start;

		//Checking if character will fit in particular row
		if((x1+(end-start))>320)
		{
			y+=font_height;	//Moving to the next line
			x1 = x;

		}

		y1 = y;

		//Writing the Character
		for(uint16_t i=start;i<end;i++)//Counting Columns inside the Font Array
		{
			for(uint16_t j=0;j<no_of_bytes_per_column;j++)//Counting Number of Bytes per column inside the Font Array
			{
				for(int16_t k=7;k>=0;k--)//Counting Number of Bits per Byte (one bit = one pixel)
				{
					if((font[counter]&(1<<k))>=1)	//If the Bit is set then you write the pixel using the color
					{
						lcdWritePixel(spiHandleStructure, color, x1, y1);
						y1++;	//Incrementing the Y pos
					}
					else
					{
						/*
						 * If the Bit is not set then write the pixel using the BG color
						 * as if you are over writing already written space then the previously written
						 * character will not be superimposed over the new one
						 */
						lcdWritePixel(spiHandleStructure, BG, x1, y1);
						y1++;	//Incrementing the Y pos
					}
				}
				counter++;
			}
			y1=y;
			x1++;	//Incrementing the X Pos
		}

		//Creating the Spacing
		x1+=spacing;
	}
}
