#include "GLNumbers.hpp"
#include "SDL/SDL_opengl.h"

namespace GLNumbers
{

		void drawNumber(int xpos, int ypos, int charW, int charH, int number)
		{
				//Trivial case: if number is 0, draw 0
				if (number == 0)
						drawDigit(xpos, ypos, charW, charH, 0);
				else
				{
					//No negative numbers
					if (number < 0)
						number = -number;
					
					//Get each individual base10 digit- limit 32 digit numbers
					int placeholder = number;
					int nDigits = 0;
					char base10digits[32];
					
					while (placeholder > 0 && nDigits < 32)
					{
							base10digits[nDigits] = placeholder - ((placeholder/10)*10);
							placeholder /= 10;
							nDigits++;
					}
					nDigits -= 1; //nDigits incremented 1 past the goal
					
					for (int i = nDigits; i >= 0; i--)
							drawDigit(xpos + ( (charW+4) * (nDigits- i)), ypos, charW, charH, base10digits[i]);
				}
		}
	
		void drawDigit(int xpos, int ypos, int charW, int charH, int digit)
		{
			switch (digit)
			{
				default:
				case 0:
					glBegin(GL_LINE_LOOP);
						glVertex2i(xpos			, ypos			);
						glVertex2i(xpos + charW	, ypos			);
						glVertex2i(xpos + charW	, ypos + charH	);
						glVertex2i(xpos			, ypos + charH	);					
					glEnd();
					break;
					
				case 1:
					glBegin(GL_LINES);
						glVertex2i(xpos	+ charW	, ypos			);
						glVertex2i(xpos	+ charW	, ypos + charH	);
					glEnd();
					break;
					
				case 2:
					glBegin(GL_LINE_STRIP);
						glVertex2i(xpos			, ypos				);
						glVertex2i(xpos	+ charW	, ypos 				);
						glVertex2i(xpos	+ charW	, ypos + (charH / 2));
						glVertex2i(xpos			, ypos + (charH / 2));
						glVertex2i(xpos			, ypos + charH		);
						glVertex2i(xpos	+ charW	, ypos + charH		);
					glEnd();
					break;
					
				case 3:
					glBegin(GL_LINES);
						glVertex2i(xpos			, ypos				);
						glVertex2i(xpos	+ charW	, ypos 				);
						
						glVertex2i(xpos			, ypos + (charH / 2));
						glVertex2i(xpos	+ charW	, ypos + (charH / 2));
						
						glVertex2i(xpos			, ypos + charH		);
						glVertex2i(xpos	+ charW	, ypos + charH		);
						
						glVertex2i(xpos	+ charW	, ypos				);
						glVertex2i(xpos	+ charW	, ypos + charH		);
					glEnd();
					break;
					
				case 4:
					glBegin(GL_LINES);
						glVertex2i(xpos			, ypos 				);
						glVertex2i(xpos			, ypos + (charH / 2));
						
						glVertex2i(xpos			, ypos + (charH / 2));
						glVertex2i(xpos	+ charW	, ypos + (charH / 2));
						
						glVertex2i(xpos	+ charW	, ypos 				);
						glVertex2i(xpos	+ charW	, ypos + charH		);
					glEnd();
					break;
					
				case 5:
					glBegin(GL_LINE_STRIP);
						glVertex2i(xpos	+ charW	, ypos 				);
						glVertex2i(xpos			, ypos				);
						glVertex2i(xpos			, ypos + (charH / 2));
						glVertex2i(xpos	+ charW	, ypos + (charH / 2));
						glVertex2i(xpos	+ charW	, ypos + charH		);
						glVertex2i(xpos			, ypos + charH		);
					glEnd();
					break;
					
				case 6:
					glBegin(GL_LINE_STRIP);
						glVertex2i(xpos			, ypos				);
						glVertex2i(xpos			, ypos + charH		);
						glVertex2i(xpos	+ charW	, ypos + charH		);
						glVertex2i(xpos	+ charW	, ypos + (charH / 2));
						glVertex2i(xpos			, ypos + (charH / 2));
					glEnd();
					break;
				
				case 7:
					glBegin(GL_LINE_STRIP);
						glVertex2i(xpos			, ypos			);
						glVertex2i(xpos	+ charW	, ypos			);
						glVertex2i(xpos	+ charW	, ypos + charH	);
					glEnd();
					break;
					
				case 8:
					glBegin(GL_LINE_STRIP);
						glVertex2i(xpos			, ypos + (charH / 2));
						glVertex2i(xpos			, ypos				);
						glVertex2i(xpos	+ charW	, ypos				);
						glVertex2i(xpos + charW , ypos + (charH / 2));
						glVertex2i(xpos 		, ypos + (charH / 2));
						glVertex2i(xpos 		, ypos + charH		);
						glVertex2i(xpos + charW	, ypos + charH		);
						glVertex2i(xpos + charW	, ypos + (charH / 2));
					glEnd();				
					break;
				
				case 9:
					glBegin(GL_LINE_STRIP);
						glVertex2i(xpos	+ charW	, ypos + charH		);
						glVertex2i(xpos	+ charW	, ypos				);
						glVertex2i(xpos			, ypos				);
						glVertex2i(xpos			, ypos + (charH / 2));
						glVertex2i(xpos	+ charW	, ypos + (charH / 2));
					glEnd();						
					break;
				
				case 10: //Colon for time output
					glPointSize(5.0);
					glBegin(GL_POINTS);
						glVertex2i(xpos + (charW/2)	, ypos + (charH * 0.25)	);
						glVertex2i(xpos + (charW/2)	, ypos + (charH * 0.75)	);
					glEnd();
					break;
			}
		
		}
		
		void drawTime(int xpos, int ypos, int charW, int charH, int milliseconds)
		{
			//If timer is maxed out, stop updating, draw maxvalue
			if (milliseconds >= 5999999)
			{
				drawNumber(xpos, ypos, charW, charH, 99);
				xpos += 2*(charW + 4);
				drawDigit(xpos, ypos, charW, charH, 10);
				xpos += charW + 4;
				
				drawNumber(xpos, ypos, charW, charH, 59);
				xpos += 2*(charW + 4);
				drawDigit(xpos, ypos, charW, charH, 10);
				xpos += charW + 4;
				
				drawNumber(xpos, ypos, charW, charH, 999);
			}
			//If timer is 0, don't bother calculating it
			else if (milliseconds == 0)
			{
				drawDigit(xpos, ypos, charW, charH, 0);
				xpos += charW + 4;
				drawDigit(xpos, ypos, charW, charH, 0);
				xpos += charW + 4;
				drawDigit(xpos, ypos, charW, charH, 10);
				xpos += charW + 4;
				
				drawDigit(xpos, ypos, charW, charH, 0);
				xpos += charW + 4;
				drawDigit(xpos, ypos, charW, charH, 0);
				xpos += charW + 4;
				drawDigit(xpos, ypos, charW, charH, 10);
				xpos += charW + 4;
				
				drawDigit(xpos, ypos, charW, charH, 0);
				xpos += charW + 4;
				drawDigit(xpos, ypos, charW, charH, 0);
				xpos += charW + 4;
				drawDigit(xpos, ypos, charW, charH, 0);
			}
			else
			{
				// # of ms per minute: 60000
				// # of ms per second: 1000

				int minutes = milliseconds / 60000;
				milliseconds -= (minutes * 60000);
				
				int seconds = milliseconds / 1000;
				milliseconds -= (seconds * 1000);
				
				//Draw mm:ss:mss
			
				//Minutes 'mm:'
				if (minutes < 10)
				{
					drawDigit(xpos, ypos, charW, charH, 0);
					xpos += charW + 4;
					drawNumber(xpos, ypos, charW, charH, minutes);
					xpos += charW + 4;
				}
				else
				{
					drawNumber(xpos, ypos, charW, charH, minutes);
					xpos += 2*(charW + 4);	
				}
				drawDigit(xpos, ypos, charW, charH, 10);
				xpos += charW + 4;			
				
				//Seconds 'ss:'
				if (seconds < 10)
				{
					drawDigit(xpos, ypos, charW, charH, 0);
					xpos += charW + 4;
					drawNumber(xpos, ypos, charW, charH, seconds);
					xpos += charW + 4;	
				}
				else
				{
					drawNumber(xpos, ypos, charW, charH, seconds);
					xpos += 2*(charW + 4);
				}
				
				drawDigit(xpos, ypos, charW, charH, 10);
				xpos += charW + 4;
				
				//Milliseconds 'mss'
				if (milliseconds < 100)
				{
					drawDigit(xpos, ypos, charW, charH, 0);
					xpos += charW + 4;
				}
				if (milliseconds < 10)
				{
					drawDigit(xpos, ypos, charW, charH, 0);
					xpos += charW + 4;
				}
				drawNumber(xpos, ypos, charW, charH, milliseconds);
			}
			
		}
}
