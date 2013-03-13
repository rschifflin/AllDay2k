/*
	This file provides functions for printing out strings of numbers, including time
	in hh:mm:ss:ms format
*/

#ifndef RS_GLNUMBERS
#define RS_GLNUMBERS


namespace GLNumbers
{
	void drawNumber(int xpos, int ypos, int charW, int charH, unsigned int number);
	
	void drawDigit(int xpos, int ypos, int charW, int charH, unsigned int digit);
	
	void drawTime(int xpos, int ypos, int charW, int charH, unsigned int milliseconds);
}


#endif //RS_GL_NUMBERS
