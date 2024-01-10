# ILI9341-Display-Driver
 
This project contains display drivers for the ILI9341 LCD Display to display Bitmaps, Characters, and Strings.<br>
I have created my own Font Library and Algorithm to display the characters and strings on the Display.<br>

There is a Font Array and a Font Handler Structure.

Inside the Font Array each Bit represents a pixel. If you need to fill the pixel then the Bit is 1 or else the Bit is 0.<br>
If the Font size is 24x24 Pixels then in total there a 576 pixels if we use 576 values to represent each pixel then we will run out of space, that is why I have used 1 Bit to represent each pixel.<br>
Thus, each character consumes 72 Bytes of data in this example.

To identify the position(Start and End) of each character inside the Font Array the Font Handler Structure is used.<br>
The Font Handler structure uses ASCII values to position each character.

The lcdWriteChar Function iterrates over each bit of the character inside the font array and if the Bit is 1 then fills the pixel with desired color. Thus, displaying the whole character.
