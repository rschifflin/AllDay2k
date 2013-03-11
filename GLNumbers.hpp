/*
	This file provides functions for printing out strings of numbers, including time
	in hh:mm:ss:ms format
*/

#ifndef RS_GLNUMBERS
#define RS_GLNUMBERS


namespace GLNumbers
{
	void drawNumber(int xpos, int ypos, int charW, int charH, int number);
	
	void drawDigit(int xpos, int ypos, int charW, int charH, int digit);
	
	void drawTime(int xpos, int ypos, int charW, int charH, int milliseconds);
}


#endif //RS_GL_NUMBERS
