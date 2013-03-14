#include "Board.hpp"
#include <stdlib.h>
#include <time.h>
#include "Primitives.hpp"

namespace RicochetRobots
{
	SubBoard::SubBoard(int type)
	{
		loadType(type);
	}

	void SubBoard::loadType(int type)
	{
		for (int i = 0; i < BOARDSIZE/2; i++)
			for (int j = 0; j < BOARDSIZE/2; j++)
			{
				m_gridA[i][j].isOpenN = true;
				m_gridA[i][j].isOpenE = true;
				m_gridA[i][j].isOpenS = true;
				m_gridA[i][j].isOpenW = true;

				m_gridA[i][j].bumper = NOBUMPER;

				m_gridB[i][j].isOpenN = true;
				m_gridB[i][j].isOpenE = true;
				m_gridB[i][j].isOpenS = true;
				m_gridB[i][j].isOpenW = true;

				m_gridB[i][j].bumper = NOBUMPER;
			}

		switch (type)
		{
		/*case 0:*/
		default:
		case 0:
			m_subGoalA[0].type = m_subGoalB[0].type = GREENTRIANGLE;
			m_subGoalA[0].pos = (unsigned char)((3 << 4) + 1);
			m_subGoalB[0].pos = (unsigned char)((2 << 4) + 6); 
			
			m_subGoalA[1].type = m_subGoalB[1].type = YELLOWDIAMOND;
			m_subGoalA[1].pos = (unsigned char)((6 << 4) + 3);
			m_subGoalB[1].pos = (unsigned char)((6 << 4) + 4); 

			m_subGoalA[2].type = m_subGoalB[2].type = BLUESQUARE;
			m_subGoalA[2].pos = (unsigned char)((4 << 4) + 6);
			m_subGoalB[2].pos = (unsigned char)((3 << 4) + 6); 

			m_subGoalA[3].type = m_subGoalB[3].type = REDCIRCLE;
			m_subGoalA[3].pos = (unsigned char)((1 << 4) + 4);
			m_subGoalB[3].pos = (unsigned char)((1 << 4) + 3); 

			m_subGoalA[4].type = m_subGoalB[4].type = NOGOALPIECE;
			m_subGoalA[4].pos = 0;
			m_subGoalB[4].pos = 0;
			
			m_gridA[0][1].isOpenE = false;
			m_gridA[0][2].isOpenW = false;
			m_gridA[0][3].isOpenS = false;

			m_gridA[1][2].isOpenE = false;
			m_gridA[1][3].isOpenW = false;
			m_gridA[1][3].isOpenN = false;

			m_gridA[3][6].isOpenE = false;
			m_gridA[3][6].isOpenS = false;
			m_gridA[3][7].isOpenW = false;

			m_gridA[4][0].isOpenE = false;
			m_gridA[4][1].isOpenW = false;
			m_gridA[4][1].isOpenS = false;
			m_gridA[4][6].isOpenN = false;

			m_gridA[5][1].isOpenN = false;
			m_gridA[5][4].isOpenS = false;

			m_gridA[6][0].isOpenS = false;
			m_gridA[6][4].isOpenE = false;
			m_gridA[6][4].isOpenN = false;
			m_gridA[6][5].isOpenW = false;
			m_gridA[6][7].isOpenS = false;

			m_gridA[7][0].isOpenN = false;
			m_gridA[7][6].isOpenE = false;
			m_gridA[7][7].isOpenW = false;
			m_gridA[7][7].isOpenN = false;

			m_gridB[0][5].isOpenE = false;
			m_gridB[0][6].isOpenW = false;
			
			m_gridB[1][4].bumper = GREENFORWARD;

			m_gridB[2][1].isOpenS = false;

			m_gridB[3][0].isOpenE = false;
			m_gridB[3][1].isOpenW = false;
			m_gridB[3][1].isOpenN = false;

			m_gridB[4][6].isOpenE = false;
			m_gridB[4][6].isOpenS = false;

			m_gridB[4][7].isOpenW = false;

			m_gridB[5][0].isOpenS = false;
			m_gridB[5][2].isOpenS = false;
			m_gridB[5][6].isOpenN = false;

			m_gridB[6][0].isOpenN = false;
			m_gridB[6][2].isOpenN = false;
			m_gridB[6][2].isOpenE = false;
			m_gridB[6][3].isOpenW = false;
			m_gridB[6][3].isOpenS = false;
			m_gridB[6][7].isOpenS = false;

			m_gridB[7][3].isOpenN = false;
			m_gridB[7][5].bumper = YELLOWBACKWARD;
			m_gridB[7][6].isOpenE = false;
			m_gridB[7][7].isOpenW = false;
			m_gridB[7][7].isOpenN = false;

			break;
		case 1:			
			m_subGoalA[0].type = m_subGoalB[0].type = GREENCIRCLE;
			m_subGoalA[0].pos = (unsigned char)((4 << 4) + 1);
			m_subGoalB[0].pos = (unsigned char)((2 << 4) + 4); 
			
			m_subGoalA[1].type = m_subGoalB[1].type = YELLOWSQUARE;
			m_subGoalA[1].pos = (unsigned char)((5 << 4) + 5);
			m_subGoalB[1].pos = (unsigned char)((5 << 4) + 6); 

			m_subGoalA[2].type = m_subGoalB[2].type = BLUEDIAMOND;
			m_subGoalA[2].pos = (unsigned char)((3 << 4) + 6);
			m_subGoalB[2].pos = (unsigned char)((6 << 4) + 2); 

			m_subGoalA[3].type = m_subGoalB[3].type = REDTRIANGLE;
			m_subGoalA[3].pos = (unsigned char)((1 << 4) + 3);
			m_subGoalB[3].pos = (unsigned char)((3 << 4) + 4); 

			m_subGoalA[4].type = m_subGoalB[4].type = NOGOALPIECE;
			m_subGoalA[4].pos = 0;
			m_subGoalB[4].pos = 0;
	
			m_gridA[0][1].isOpenE = false;
			m_gridA[0][2].isOpenW = false;
			m_gridA[0][4].isOpenS = false;

			m_gridA[1][4].isOpenN = false;
			m_gridA[1][4].isOpenE = false;
			m_gridA[1][5].isOpenW = false;

			m_gridA[3][0].isOpenE = false;
			
			m_gridA[3][1].isOpenW = false;
			m_gridA[3][1].isOpenS = false;
			
			m_gridA[4][1].isOpenN = false;
			m_gridA[4][5].isOpenS = false;
			
			m_gridA[5][0].isOpenS = false;
			m_gridA[5][4].isOpenE = false;
			m_gridA[5][5].isOpenW = false;
			m_gridA[5][5].isOpenN = false;
			
			m_gridA[6][0].isOpenN = false;
			m_gridA[6][3].isOpenS = false;
			m_gridA[6][3].isOpenE = false;
			m_gridA[6][4].isOpenW = false;
			m_gridA[6][7].isOpenS = false;
			
			m_gridA[7][3].isOpenN = false;
			m_gridA[7][6].isOpenE = false;
			m_gridA[7][7].isOpenW = false;
			m_gridA[7][7].isOpenN = false;
				
			m_gridB[0][4].isOpenE = false;
			m_gridB[0][5].isOpenW = false;
			
			m_gridB[1][4].bumper = BLUEBACKWARD;

			m_gridB[2][0].isOpenS = false;	
			m_gridB[2][6].isOpenE = false;			
			m_gridB[2][6].isOpenS = false;	
			m_gridB[2][7].isOpenW = false;

			m_gridB[3][0].isOpenN = false;
			m_gridB[3][2].isOpenS = false;
			m_gridB[3][6].isOpenN = false;
			m_gridB[3][6].bumper = YELLOWBACKWARD;

			m_gridB[4][2].isOpenN = false;
			m_gridB[4][2].isOpenE = false;
			m_gridB[4][3].isOpenW = false;
			m_gridB[4][3].isOpenS = false;

			m_gridB[5][3].isOpenN = false;
			m_gridB[5][5].isOpenS = false;

			m_gridB[6][4].isOpenE = false;
			m_gridB[6][5].isOpenW = false;
			m_gridB[6][5].isOpenN = false;		
			m_gridB[6][7].isOpenS = false;

			m_gridB[7][6].isOpenE = false;
			m_gridB[7][7].isOpenN = false;
			m_gridB[7][7].isOpenW = false;
			break;
		case 2:
			m_subGoalA[0].type = m_subGoalB[0].type = GREENDIAMOND;
			m_subGoalA[0].pos = (unsigned char)((4 << 4) + 5);
			m_subGoalB[0].pos = (unsigned char)((5 << 4) + 2); 
			
			m_subGoalA[1].type = m_subGoalB[1].type = YELLOWCIRCLE;
			m_subGoalA[1].pos = (unsigned char)((3 << 4) + 2);
			m_subGoalB[1].pos = (unsigned char)((6 << 4) + 2); 

			m_subGoalA[2].type = m_subGoalB[2].type = BLUETRIANGLE;
			m_subGoalA[2].pos = (unsigned char)((5 << 4) + 3);
			m_subGoalB[2].pos = (unsigned char)((4 << 4) + 7); 

			m_subGoalA[3].type = m_subGoalB[3].type = REDSQUARE;
			m_subGoalA[3].pos = (unsigned char)((2 << 4) + 4);
			m_subGoalB[3].pos = (unsigned char)((1 << 4) + 5); 

			m_subGoalA[4].type = m_subGoalB[4].type = NOGOALPIECE;
			m_subGoalA[4].pos = 0;
			m_subGoalB[4].pos = 0;

			m_gridA[0][5].isOpenE = false;
			m_gridA[0][6].isOpenW = false;

			m_gridA[1][3].isOpenS = false;
		
			m_gridA[2][2].isOpenE = false;
			m_gridA[2][3].isOpenW = false;
			m_gridA[2][3].isOpenN = false;

			m_gridA[3][0].isOpenS = false;			
			m_gridA[3][2].isOpenS = false;
			m_gridA[3][4].isOpenE = false;
			m_gridA[3][5].isOpenW = false;
			m_gridA[3][5].isOpenS = false;
			
			m_gridA[4][0].isOpenN = false;
			m_gridA[4][2].isOpenN = false;
			m_gridA[4][2].isOpenE = false;
			m_gridA[4][3].isOpenW = false;
			m_gridA[4][5].isOpenN = false;
			
			m_gridA[5][4].isOpenE = false;
			m_gridA[5][4].isOpenS = false;
			m_gridA[5][5].isOpenW = false;
			
			m_gridA[6][4].isOpenN = false;
			m_gridA[6][7].isOpenS = false;
			
			m_gridA[7][6].isOpenE = false;
			m_gridA[7][7].isOpenW = false;
			m_gridA[7][7].isOpenN = false;

			m_gridB[0][2].isOpenE = false;
			m_gridB[0][3].isOpenW = false;

			m_gridB[1][2].bumper = BLUEFORWARD;
			m_gridB[1][6].isOpenS = false;			

			m_gridB[2][5].isOpenS = false;
			m_gridB[2][5].isOpenE = false;
			m_gridB[2][6].isOpenN = false;
			m_gridB[2][6].isOpenW = false;
						
			m_gridB[3][5].isOpenN = false;
			
			m_gridB[4][7].bumper = REDBACKWARD;
			
			m_gridB[5][0].isOpenE = false;
			m_gridB[5][1].isOpenW = false;
			m_gridB[5][1].isOpenS = false;
			
			m_gridB[6][0].isOpenS = false;
			m_gridB[6][1].isOpenN = false;
			m_gridB[6][4].isOpenS = false;
			m_gridB[6][7].isOpenS = false;
			
			m_gridB[7][0].isOpenN = false;
			m_gridB[7][4].isOpenN = false;
			m_gridB[7][4].isOpenE = false;
			m_gridB[7][5].isOpenW = false;
			m_gridB[7][6].isOpenE = false;
			m_gridB[7][7].isOpenW = false;
			m_gridB[7][7].isOpenN = false;
			break;

		case 3:
			m_subGoalA[0].type = m_subGoalB[0].type = GREENSQUARE;
			m_subGoalA[0].pos = (unsigned char)((6 << 4) + 5);
			m_subGoalB[0].pos = (unsigned char)((3 << 4) + 3); 
			
			m_subGoalA[1].type = m_subGoalB[1].type = YELLOWTRIANGLE;
			m_subGoalA[1].pos = (unsigned char)((1 << 4) + 6);
			m_subGoalB[1].pos = (unsigned char)((6 << 4) + 2); 

			m_subGoalA[2].type = m_subGoalB[2].type = BLUECIRCLE;
			m_subGoalA[2].pos = (unsigned char)((5 << 4) + 1);
			m_subGoalB[2].pos = (unsigned char)((2 << 4) + 3); 

			m_subGoalA[3].type = m_subGoalB[3].type = REDDIAMOND;
			m_subGoalA[3].pos = (unsigned char)((3 << 4) + 4);
			m_subGoalB[3].pos = (unsigned char)((1 << 4) + 5); 

			m_subGoalA[4].type = m_subGoalB[4].type = VORTEX;
			m_subGoalA[4].pos = (unsigned char)((7 << 4) + 2);
			m_subGoalB[4].pos = (unsigned char)((5 << 4) + 7);

			m_gridA[0][2].isOpenE = false;
			m_gridA[0][3].isOpenW = false;

			m_gridA[1][4].isOpenE = false;
			m_gridA[1][5].isOpenW = false;
			m_gridA[1][5].isOpenS = false;
		
			m_gridA[2][5].isOpenN = false;
			m_gridA[2][7].isOpenS = false;
			m_gridA[2][7].isOpenE = false;

			m_gridA[3][0].isOpenS = false;			
			m_gridA[3][7].isOpenN = false;			
			
			m_gridA[4][0].isOpenN = false;
			m_gridA[4][3].isOpenE = false;
			m_gridA[4][3].isOpenS = false;
			m_gridA[4][4].isOpenW = false;
			m_gridA[4][6].isOpenS = false;
			
			m_gridA[5][1].isOpenS = false;
			m_gridA[5][3].isOpenN = false;
			m_gridA[5][5].isOpenE = false;
			m_gridA[5][6].isOpenW = false;
			m_gridA[5][6].isOpenN = false;
			
			m_gridA[6][1].isOpenN = false;
			m_gridA[6][1].isOpenE = false;	
			m_gridA[6][2].isOpenW = false;
			m_gridA[6][7].isOpenS = false;
			
			m_gridA[7][6].isOpenE = false;
			m_gridA[7][7].isOpenW = false;
			m_gridA[7][7].isOpenN = false;

			m_gridB[0][4].isOpenE = false;
			m_gridB[0][5].isOpenW = false;

			m_gridB[1][2].bumper = REDBACKWARD;
			m_gridB[1][6].isOpenS = false;			

			m_gridB[2][2].isOpenS = false;
			m_gridB[2][5].isOpenE = false;
			m_gridB[2][6].isOpenN = false;
			m_gridB[2][6].isOpenW = false;
						
			m_gridB[3][2].isOpenN = false;
			m_gridB[3][2].isOpenE = false;
			m_gridB[3][3].isOpenW = false;
			m_gridB[3][3].isOpenS = false;
			
			m_gridB[4][3].isOpenN = false;
			
			m_gridB[5][1].isOpenE = false;
			m_gridB[5][1].isOpenS = false;
			m_gridB[5][2].isOpenW = false;
			
			m_gridB[6][0].isOpenS = false;
			m_gridB[6][1].isOpenN = false;
			m_gridB[6][3].bumper = GREENBACKWARD;
			m_gridB[6][7].isOpenS = false;
			
			m_gridB[7][0].isOpenN = false;
			m_gridB[7][5].isOpenE = false;
			m_gridB[7][5].isOpenS = false;
			m_gridB[7][6].isOpenW = false;
			m_gridB[7][6].isOpenE = false;
			m_gridB[7][7].isOpenW = false;
			m_gridB[7][7].isOpenN = false;
				
			break;	
		} //End switch(type)

		m_isFront = true;
		m_angle = 0;
		m_assignGrid();
	}//End loadType

	void SubBoard::m_assignGrid()
	{
		
		if (m_isFront)
		{
			if (m_angle == 0)
			{
				for (int i = 0; i < 5; i++)
				{
					m_subGoal[i] = m_subGoalA[i];
				}
				for (int i = 0; i < BOARDSIZE/2; i++)
					for (int j = 0; j < BOARDSIZE/2; j++)
						m_grid[i][j] = m_gridA[i][j];
			}
			else if (m_angle == 90)
			{
				for (int i = 0; i < 5; i++)
				{
					unsigned char xpos = (m_subGoalA[i].pos & 0xF0) >> 4;
					unsigned char ypos = (m_subGoalA[i].pos & 0x0F);
					unsigned char xnew, ynew;
					ynew = BOARDSIZE/2 - 1 - xpos;
					xnew = ypos;
					m_subGoal[i].pos = (unsigned char)( (xnew << 4) + ynew);
					m_subGoal[i].type = m_subGoalA[i].type;

				}

				for (int i = 0; i < BOARDSIZE/2; i++)
					for (int j = 0; j < BOARDSIZE/2; j++)
					{
						int u = BOARDSIZE/2 - 1 - j;
						int v = i;

						m_grid[u][v] = m_gridA[i][j];

						m_grid[u][v].isOpenN = m_gridA[i][j].isOpenE;
						m_grid[u][v].isOpenE = m_gridA[i][j].isOpenS;
						m_grid[u][v].isOpenS = m_gridA[i][j].isOpenW;
						m_grid[u][v].isOpenW = m_gridA[i][j].isOpenN;
					}
			}
			else if (m_angle == 180)
			{
				for (int i = 0; i < 5; i++)
				{
					unsigned char xpos = (m_subGoalA[i].pos & 0xF0) >> 4;
					unsigned char ypos = (m_subGoalA[i].pos & 0x0F);
					unsigned char xnew, ynew;
					ynew = BOARDSIZE/2 - 1 - ypos;
					xnew = BOARDSIZE/2 - 1 - xpos;
					m_subGoal[i].pos = (unsigned char)( (xnew << 4) + ynew);
					m_subGoal[i].type = m_subGoalA[i].type;
					
				}
				for (int i = 0; i < BOARDSIZE/2; i++)
					for (int j = 0; j < BOARDSIZE/2; j++)
					{
						int u = BOARDSIZE/2 - 1 - i;
						int v = BOARDSIZE/2 - 1 - j;

						m_grid[u][v] = m_gridA[i][j];

						m_grid[u][v].isOpenW = m_gridA[i][j].isOpenE;
						m_grid[u][v].isOpenN = m_gridA[i][j].isOpenS;
						m_grid[u][v].isOpenE = m_gridA[i][j].isOpenW;
						m_grid[u][v].isOpenS = m_gridA[i][j].isOpenN;
					}
			}
			else if (m_angle == 270)
			{
				for (int i = 0; i < 5; i++)
				{
					unsigned char xpos = (m_subGoalA[i].pos & 0xF0) >> 4;
					unsigned char ypos = (m_subGoalA[i].pos & 0x0F);
					unsigned char xnew, ynew;
					ynew = xpos;
					xnew = BOARDSIZE/2 - 1 - ypos;
					m_subGoal[i].pos = (unsigned char)( (xnew << 4) + ynew);
					m_subGoal[i].type = m_subGoalA[i].type;

				}
				for (int i = 0; i < BOARDSIZE/2; i++)
					for (int j = 0; j < BOARDSIZE/2; j++)
					{
						int u = j;
						int v = BOARDSIZE/2 - 1 - i;

						m_grid[u][v] = m_gridA[i][j];

						m_grid[u][v].isOpenS = m_gridA[i][j].isOpenE;
						m_grid[u][v].isOpenW = m_gridA[i][j].isOpenS;
						m_grid[u][v].isOpenN = m_gridA[i][j].isOpenW;
						m_grid[u][v].isOpenE = m_gridA[i][j].isOpenN;
					}
			}

		}
		else
		{
			if (m_angle == 0)
			{
				for (int i = 0; i < 5; i++)
				{
					m_subGoal[i] = m_subGoalB[i];
				}

				for (int i = 0; i < BOARDSIZE/2; i++)
					for (int j = 0; j < BOARDSIZE/2; j++)
						m_grid[i][j] = m_gridB[i][j];
			}
			else if (m_angle == 90)
			{	
				for (int i = 0; i < 5; i++)
				{
					unsigned char xpos = (m_subGoalB[i].pos & 0xF0) >> 4;
					unsigned char ypos = (m_subGoalB[i].pos & 0x0F);
					unsigned char xnew, ynew;
					ynew = BOARDSIZE/2 - 1 - xpos;
					xnew = ypos;
					m_subGoal[i].pos = (unsigned char)( (xnew << 4) + ynew);
					m_subGoal[i].type = m_subGoalB[i].type;

				}

				for (int i = 0; i < BOARDSIZE/2; i++)
					for (int j = 0; j < BOARDSIZE/2; j++)
					{
						int u = BOARDSIZE/2 - 1 - j;
						int v = i;

						m_grid[u][v] = m_gridB[i][j];

						m_grid[u][v].isOpenN = m_gridB[i][j].isOpenE;
						m_grid[u][v].isOpenE = m_gridB[i][j].isOpenS;
						m_grid[u][v].isOpenS = m_gridB[i][j].isOpenW;
						m_grid[u][v].isOpenW = m_gridB[i][j].isOpenN;

						//Flip bumpers
						int bumperVal = m_grid[u][v].bumper;
						if (bumperVal != NOBUMPER)
						{
							if (bumperVal % 2 == 1)
								m_grid[u][v].bumper = (Bumper)(bumperVal - 1);
							else
								m_grid[u][v].bumper = (Bumper)(bumperVal + 1);
						}
					}
			}
			else if (m_angle == 180)
			{		
				for (int i = 0; i < 5; i++)
				{
					unsigned char xpos = (m_subGoalB[i].pos & 0xF0) >> 4;
					unsigned char ypos = (m_subGoalB[i].pos & 0x0F);
					unsigned char xnew, ynew;
					ynew = BOARDSIZE/2 - 1 - ypos;
					xnew = BOARDSIZE/2 - 1 - xpos;
					m_subGoal[i].pos = (unsigned char)( (xnew << 4) + ynew);
					m_subGoal[i].type = m_subGoalB[i].type;
				}

				for (int i = 0; i < BOARDSIZE/2; i++)
					for (int j = 0; j < BOARDSIZE/2; j++)
					{
						int u = BOARDSIZE/2 - 1 - i;
						int v = BOARDSIZE/2 - 1 - j;

						m_grid[u][v] = m_gridB[i][j];

						m_grid[u][v].isOpenW = m_gridB[i][j].isOpenE;
						m_grid[u][v].isOpenN = m_gridB[i][j].isOpenS;
						m_grid[u][v].isOpenE = m_gridB[i][j].isOpenW;
						m_grid[u][v].isOpenS = m_gridB[i][j].isOpenN;
					}
			}
			else if (m_angle == 270)
			{
				for (int i = 0; i < 5; i++)
				{
					unsigned char xpos = (m_subGoalB[i].pos & 0xF0) >> 4;
					unsigned char ypos = (m_subGoalB[i].pos & 0x0F);
					unsigned char xnew, ynew;
					ynew = xpos;
					xnew = BOARDSIZE/2 - 1 - ypos;
					m_subGoal[i].pos = (unsigned char)( (xnew << 4) + ynew);
					m_subGoal[i].type = m_subGoalB[i].type;

				}

				for (int i = 0; i < BOARDSIZE/2; i++)
					for (int j = 0; j < BOARDSIZE/2; j++)
					{
						int u = j;
						int v = BOARDSIZE/2 - 1 - i;

						m_grid[u][v] = m_gridB[i][j];

						m_grid[u][v].isOpenS = m_gridB[i][j].isOpenE;
						m_grid[u][v].isOpenW = m_gridB[i][j].isOpenS;
						m_grid[u][v].isOpenN = m_gridB[i][j].isOpenW;
						m_grid[u][v].isOpenE = m_gridB[i][j].isOpenN;

						//Flip bumpers
						int bumperVal = m_grid[u][v].bumper;
						if (bumperVal != NOBUMPER)
						{
							if (bumperVal % 2 == 1)
								m_grid[u][v].bumper = (Bumper)(bumperVal - 1);
							else
								m_grid[u][v].bumper = (Bumper)(bumperVal + 1);
						}
					}
			}
		}
	}

	Board::Board(unsigned int seed)
	{
		m_pxSize = 32;
		createBoard(seed);
	}

	void Board::createBoard(unsigned int seed)
	{
		if (seed == 0)
			m_seed = (unsigned int)time(NULL);
		else
			m_seed = seed;

		srand(m_seed);
		m_buildGrid();
	}

	void Board::resetBoard()
	{
		srand(m_seed);
		m_buildGrid();
	}

	void Board::draw()
	{
		for (GLint i = 0; i < BOARDSIZE; i++)
			for (GLint j = 0; j < BOARDSIZE; j++)
			{
				//Clear color is white, drawing white squares unneccesary
				/*
				glColor3f(1.0,1.0,1.0);
				glBegin(GL_QUADS);
					glVertex2i(16*i		, 16*j		);
					glVertex2i(16*i + 16	, 16*j		);
					glVertex2i(16*i + 16	, 16*j + 16	);
					glVertex2i(16*i		, 16*j + 16	);
				glEnd();
				*/
				
				//Draw grid lines
				glColor3f(0.75,0.75,0.75);
				glBegin(GL_LINE_LOOP);
					glVertex2i(m_pxSize*j		, m_pxSize*i		);
					glVertex2i(m_pxSize*j + m_pxSize, m_pxSize*i		);
					glVertex2i(m_pxSize*j + m_pxSize, m_pxSize*i + m_pxSize	);
					glVertex2i(m_pxSize*j		, m_pxSize*i + m_pxSize	);
				glEnd();
				

				//Draw walls
				glColor3f(0.0,0.0,0.0);
				glBegin(GL_LINE_LOOP);
					glVertex2i(0			, 0			);
					glVertex2i(BOARDSIZE * m_pxSize	, 0			);
					glVertex2i(BOARDSIZE * m_pxSize	, BOARDSIZE * m_pxSize	);
					glVertex2i(0			, BOARDSIZE * m_pxSize	);
				glEnd();

				glBegin(GL_LINES);
					if (m_grid[i][j].isOpenN == false)
					{
						glVertex2i(m_pxSize*j		, m_pxSize*i + 1);
						glVertex2i(m_pxSize*j + m_pxSize, m_pxSize*i + 1);
					}

					if (m_grid[i][j].isOpenE == false)
					{
						glVertex2i(m_pxSize*j + m_pxSize - 1, m_pxSize*i + m_pxSize	);
						glVertex2i(m_pxSize*j + m_pxSize - 1, m_pxSize*i		);
					}
					
					if (m_grid[i][j].isOpenS == false)
					{
						glVertex2i(m_pxSize*j		, m_pxSize*i + m_pxSize - 1	);
						glVertex2i(m_pxSize*j + m_pxSize, m_pxSize*i + m_pxSize - 1	);
					}
					
					if (m_grid[i][j].isOpenW == false)
					{
						glVertex2i(m_pxSize*j + 1	, m_pxSize*i		);
						glVertex2i(m_pxSize*j + 1	, m_pxSize*i + m_pxSize	);
					}
					
				glEnd();
				//Draw pieces

				switch (m_grid[i][j].bumper)
				{
				default:
				case NOBUMPER:
				
					break;
				case GREENFORWARD:
					glColor3f(0.0f	, 1.0f	, 0.0f	);
					Primitives::drawForwardSlash(m_pxSize*j, m_pxSize*i, m_pxSize, m_pxSize);
					break;
				case GREENBACKWARD:
					glColor3f(0.0f	, 1.0f	, 0.0f	);
					Primitives::drawBackwardSlash(m_pxSize*j, m_pxSize*i, m_pxSize, m_pxSize);
					break;
				case YELLOWFORWARD:
					glColor3f(1.0f	, 0.847f, 0.0f	);
					Primitives::drawForwardSlash(m_pxSize*j, m_pxSize*i, m_pxSize, m_pxSize);
					break;
				case YELLOWBACKWARD:
					glColor3f(1.0f	, 0.847f, 0.0f	);
					Primitives::drawBackwardSlash(m_pxSize*j, m_pxSize*i, m_pxSize, m_pxSize);
					break;
				case BLUEFORWARD:
					glColor3f(0.0f	, 0.0f	, 1.0f	);
					Primitives::drawForwardSlash(m_pxSize*j, m_pxSize*i, m_pxSize, m_pxSize);
					break;
				case BLUEBACKWARD:
					glColor3f(0.0f	, 0.0f	, 1.0f	);
					Primitives::drawBackwardSlash(m_pxSize*j, m_pxSize*i, m_pxSize, m_pxSize);
					break;
				case REDFORWARD:
					glColor3f(1.0f	, 0.0f	, 0.0f	);
					Primitives::drawForwardSlash(m_pxSize*j, m_pxSize*i, m_pxSize, m_pxSize);
					break;
				case REDBACKWARD:
					glColor3f(1.0f	, 0.0f	, 0.0f	);
					Primitives::drawBackwardSlash(m_pxSize*j, m_pxSize*i, m_pxSize, m_pxSize);
					break;
				}


			}
		//Draw goals		
		unsigned char xpos = 0;
		unsigned char ypos = 0;

		//Green Goals:	
		glColor3f(0.0f	, 1.0f	, 0.0f	);
			
			//Triangle:
			xpos = (m_goals.greenTriangle & 0xF0) >> 4;
			ypos = m_goals.greenTriangle & 0x0F;
			Primitives::drawTriangle(m_pxSize*xpos + (m_pxSize / 4), m_pxSize*ypos + (m_pxSize / 4), (m_pxSize - 2*(m_pxSize / 4) ), (m_pxSize - 2*(m_pxSize/4)) );

			//Circle
			xpos = (m_goals.greenCircle & 0xF0) >> 4;
			ypos = m_goals.greenCircle & 0x0F;
			Primitives::drawCircle(m_pxSize*xpos + (m_pxSize/2), m_pxSize*ypos + (m_pxSize/2), (m_pxSize/4), 12);

			//Diamond:
			xpos = (m_goals.greenDiamond & 0xF0) >> 4;
			ypos = m_goals.greenDiamond & 0x0F;
			Primitives::drawDiamond(m_pxSize*xpos + (m_pxSize / 4), m_pxSize*ypos + (m_pxSize / 4), (m_pxSize - 2*(m_pxSize / 4) ), (m_pxSize - 2*(m_pxSize/4)) );

			//Square
			xpos = (m_goals.greenSquare & 0xF0) >> 4;
			ypos = m_goals.greenSquare & 0x0F;
			Primitives::drawSquare(m_pxSize*xpos + (m_pxSize / 4), m_pxSize*ypos + (m_pxSize / 4), (m_pxSize - 2*(m_pxSize / 4) ), (m_pxSize - 2*(m_pxSize/4)) );
			
		//Yellow Goals:
		glColor3f(1.0f	, 0.847f, 0.0f	);
		
			//Triangle:
			xpos = (m_goals.yellowTriangle & 0xF0) >> 4;
			ypos = m_goals.yellowTriangle & 0x0F;
			Primitives::drawTriangle(m_pxSize*xpos + (m_pxSize / 4), m_pxSize*ypos + (m_pxSize / 4), (m_pxSize - 2*(m_pxSize / 4) ), (m_pxSize - 2*(m_pxSize/4)) );

			//Circle
			xpos = (m_goals.yellowCircle & 0xF0) >> 4;
			ypos = m_goals.yellowCircle & 0x0F;
			Primitives::drawCircle(m_pxSize*xpos + (m_pxSize/2), m_pxSize*ypos + (m_pxSize/2), (m_pxSize/4), 12);

			//Diamond:
			xpos = (m_goals.yellowDiamond & 0xF0) >> 4;
			ypos = m_goals.yellowDiamond & 0x0F;
			Primitives::drawDiamond(m_pxSize*xpos + (m_pxSize / 4), m_pxSize*ypos + (m_pxSize / 4), (m_pxSize - 2*(m_pxSize / 4) ), (m_pxSize - 2*(m_pxSize/4)) );

			//Square
			xpos = (m_goals.yellowSquare & 0xF0) >> 4;
			ypos = m_goals.yellowSquare & 0x0F;
			Primitives::drawSquare(m_pxSize*xpos + (m_pxSize / 4), m_pxSize*ypos + (m_pxSize / 4), (m_pxSize - 2*(m_pxSize / 4) ), (m_pxSize - 2*(m_pxSize/4)) );	

		//Blue Goals:
		glColor3f(0.0f	, 0.0f	, 1.0f	);

			//Triangle:
			xpos = (m_goals.blueTriangle & 0xF0) >> 4;
			ypos = m_goals.blueTriangle & 0x0F;
			Primitives::drawTriangle(m_pxSize*xpos + (m_pxSize / 4), m_pxSize*ypos + (m_pxSize / 4), (m_pxSize - 2*(m_pxSize / 4) ), (m_pxSize - 2*(m_pxSize/4)) );

			//Circle
			xpos = (m_goals.blueCircle & 0xF0) >> 4;
			ypos = m_goals.blueCircle & 0x0F;
			Primitives::drawCircle(m_pxSize*xpos + (m_pxSize/2), m_pxSize*ypos + (m_pxSize/2), (m_pxSize/4), 12);

			//Diamond:
			xpos = (m_goals.blueDiamond & 0xF0) >> 4;
			ypos = m_goals.blueDiamond & 0x0F;
			Primitives::drawDiamond(m_pxSize*xpos + (m_pxSize / 4), m_pxSize*ypos + (m_pxSize / 4), (m_pxSize - 2*(m_pxSize / 4) ), (m_pxSize - 2*(m_pxSize/4)) );

			//Square
			xpos = (m_goals.blueSquare & 0xF0) >> 4;
			ypos = m_goals.blueSquare & 0x0F;
			Primitives::drawSquare(m_pxSize*xpos + (m_pxSize / 4), m_pxSize*ypos + (m_pxSize / 4), (m_pxSize - 2*(m_pxSize / 4) ), (m_pxSize - 2*(m_pxSize/4)) );	

		//Red Goals:
		glColor3f(1.0f	, 0.0f	, 0.0f	);
	
			//Triangle:
			xpos = (m_goals.redTriangle & 0xF0) >> 4;
			ypos = m_goals.redTriangle & 0x0F;
			Primitives::drawTriangle(m_pxSize*xpos + (m_pxSize / 4), m_pxSize*ypos + (m_pxSize / 4), (m_pxSize - 2*(m_pxSize / 4) ), (m_pxSize - 2*(m_pxSize/4)) );

			//Circle
			xpos = (m_goals.redCircle & 0xF0) >> 4;
			ypos = m_goals.redCircle & 0x0F;
			Primitives::drawCircle(m_pxSize*xpos + (m_pxSize/2), m_pxSize*ypos + (m_pxSize/2), (m_pxSize/4), 12);

			//Diamond:
			xpos = (m_goals.redDiamond & 0xF0) >> 4;
			ypos = m_goals.redDiamond & 0x0F;
			Primitives::drawDiamond(m_pxSize*xpos + (m_pxSize / 4), m_pxSize*ypos + (m_pxSize / 4), (m_pxSize - 2*(m_pxSize / 4) ), (m_pxSize - 2*(m_pxSize/4)) );

			//Square
			xpos = (m_goals.redSquare & 0xF0) >> 4;
			ypos = m_goals.redSquare & 0x0F;
			Primitives::drawSquare(m_pxSize*xpos + (m_pxSize / 4), m_pxSize*ypos + (m_pxSize / 4), (m_pxSize - 2*(m_pxSize / 4) ), (m_pxSize - 2*(m_pxSize/4)) );

		//Vortex
			xpos = (m_goals.vortex & 0xF0) >> 4;
			ypos = m_goals.vortex & 0x0F;
	
			glColor3f(1.0f	, 0.0f	, 0.0f	);
			Primitives::drawCircle(m_pxSize*xpos + (m_pxSize/3), m_pxSize*ypos + (m_pxSize/3), (m_pxSize/6), 24);
			glColor3f(0.0f	, 1.0f	, 0.0f	);
			Primitives::drawCircle(m_pxSize*xpos + (m_pxSize * 2/3), m_pxSize*ypos + (m_pxSize/3), (m_pxSize/6), 24);
			glColor3f(0.0f	, 0.0f	, 1.0f	);
			Primitives::drawCircle(m_pxSize*xpos + (m_pxSize * 2/3), m_pxSize*ypos + (m_pxSize * 2/3), (m_pxSize/6), 24);
			glColor3f(1.0f	, 0.847f, 0.0f	);
			Primitives::drawCircle(m_pxSize*xpos + (m_pxSize/3), m_pxSize*ypos + (m_pxSize * 2/3), (m_pxSize/6), 24);

		//Draw robots
		xpos = m_robots.greenPos & 0xF0;
		xpos = xpos >> 4;
		ypos = m_robots.greenPos & 0x0F;
		glColor3f(0.0f	, 1.0f	, 0.0f);
		Primitives::drawRing(m_pxSize*xpos + (m_pxSize/2), m_pxSize*ypos + (m_pxSize/2), (m_pxSize/2), 24, 4);

		xpos = m_robots.yellowPos & 0xF0;
		xpos = xpos >> 4;
		ypos = m_robots.yellowPos & 0x0F;
		glColor3f(1.0f	, 0.847f, 0.0f);
		Primitives::drawRing(m_pxSize*xpos + (m_pxSize/2), m_pxSize*ypos + (m_pxSize/2), (m_pxSize/2), 24, 4);

		xpos = m_robots.bluePos & 0xF0;
		xpos = xpos >> 4;
		ypos = m_robots.bluePos & 0x0F;
		glColor3f(0.0f	, 0.0f	, 1.0f);
		Primitives::drawRing(m_pxSize*xpos + (m_pxSize/2), m_pxSize*ypos + (m_pxSize/2), (m_pxSize/2), 24, 4);
		
		xpos = m_robots.redPos & 0xF0;
		xpos = xpos >> 4;
		ypos = m_robots.redPos & 0x0F;
		glColor3f(1.0f	, 0.0f	, 0.0f);
		Primitives::drawRing(m_pxSize*xpos + (m_pxSize/2), m_pxSize*ypos + (m_pxSize/2), (m_pxSize/2), 24, 4);

		//Draw Goal Piece
		switch (m_goal)
		{	
			case NOGOALPIECE:
			
				break;
			case GREENTRIANGLE:
				glColor3f(0.0f	, 1.0f	, 0.0f);
				Primitives::drawTriangle(BOARDSIZE/2 * m_pxSize - (m_pxSize/2), BOARDSIZE/2 * m_pxSize - (m_pxSize/2), m_pxSize, m_pxSize );
				break;			
			case GREENCIRCLE:
				glColor3f(0.0f	, 1.0f	, 0.0f);
				Primitives::drawCircle(BOARDSIZE/2 * m_pxSize, BOARDSIZE/2 * m_pxSize, m_pxSize/2, 24);
				break;
			case GREENDIAMOND:
				glColor3f(0.0f	, 1.0f	, 0.0f);
				Primitives::drawDiamond(BOARDSIZE/2 * m_pxSize - (m_pxSize/2), BOARDSIZE/2 * m_pxSize - (m_pxSize/2), m_pxSize, m_pxSize );
				break;
			case GREENSQUARE:
				glColor3f(0.0f	, 1.0f	, 0.0f);	
				Primitives::drawSquare(BOARDSIZE/2 * m_pxSize - (m_pxSize/2), BOARDSIZE/2 * m_pxSize - (m_pxSize/2), m_pxSize, m_pxSize );
				break;

			case YELLOWTRIANGLE:
				glColor3f(1.0f	, 0.847f, 0.0f	);
				Primitives::drawTriangle(BOARDSIZE/2 * m_pxSize - (m_pxSize/2), BOARDSIZE/2 * m_pxSize - (m_pxSize/2), m_pxSize, m_pxSize );
				break;			
			case YELLOWCIRCLE:	
				glColor3f(1.0f	, 0.847f, 0.0f	);
				Primitives::drawCircle(BOARDSIZE/2 * m_pxSize, BOARDSIZE/2 * m_pxSize, m_pxSize/2, 24);
				break;
			case YELLOWDIAMOND:
				glColor3f(1.0f	, 0.847f, 0.0f	);
				Primitives::drawDiamond(BOARDSIZE/2 * m_pxSize - (m_pxSize/2), BOARDSIZE/2 * m_pxSize - (m_pxSize/2), m_pxSize, m_pxSize );
				break;
			case YELLOWSQUARE:	
				glColor3f(1.0f	, 0.847f, 0.0f	);
				Primitives::drawSquare(BOARDSIZE/2 * m_pxSize - (m_pxSize/2), BOARDSIZE/2 * m_pxSize - (m_pxSize/2), m_pxSize, m_pxSize );
				break;		

			case BLUETRIANGLE:
				glColor3f(0.0f	, 0.0f	, 1.0f	);	
				Primitives::drawTriangle(BOARDSIZE/2 * m_pxSize - (m_pxSize/2), BOARDSIZE/2 * m_pxSize - (m_pxSize/2), m_pxSize, m_pxSize );
				break;
			case BLUECIRCLE:	
				glColor3f(0.0f	, 0.0f	, 1.0f	);	
				Primitives::drawCircle(BOARDSIZE/2 * m_pxSize, BOARDSIZE/2 * m_pxSize, m_pxSize/2, 24);
				break;
			case BLUEDIAMOND:
				glColor3f(0.0f	, 0.0f	, 1.0f	);
				Primitives::drawDiamond(BOARDSIZE/2 * m_pxSize - (m_pxSize/2), BOARDSIZE/2 * m_pxSize - (m_pxSize/2), m_pxSize, m_pxSize );
				break;
			case BLUESQUARE:	
				glColor3f(0.0f	, 0.0f	, 1.0f	);
				Primitives::drawSquare(BOARDSIZE/2 * m_pxSize - (m_pxSize/2), BOARDSIZE/2 * m_pxSize - (m_pxSize/2), m_pxSize, m_pxSize );
				break;

			case REDTRIANGLE:
				glColor3f(1.0f	, 0.0f	, 0.0f	);	
				Primitives::drawTriangle(BOARDSIZE/2 * m_pxSize - (m_pxSize/2), BOARDSIZE/2 * m_pxSize - (m_pxSize/2), m_pxSize, m_pxSize );
				break;			
			case REDCIRCLE:	
				glColor3f(1.0f	, 0.0f	, 0.0f	);
				Primitives::drawCircle(BOARDSIZE/2 * m_pxSize, BOARDSIZE/2 * m_pxSize, m_pxSize/2, 24);
				break;
			case REDDIAMOND:
				glColor3f(1.0f	, 0.0f	, 0.0f	);
				Primitives::drawDiamond(BOARDSIZE/2 * m_pxSize - (m_pxSize/2), BOARDSIZE/2 * m_pxSize - (m_pxSize/2), m_pxSize, m_pxSize );
				break;
			case REDSQUARE:	
				glColor3f(1.0f	, 0.0f	, 0.0f	);
				Primitives::drawSquare(BOARDSIZE/2 * m_pxSize - (m_pxSize/2), BOARDSIZE/2 * m_pxSize - (m_pxSize/2), m_pxSize, m_pxSize );
				break;

			case VORTEX:
				glColor3f(1.0f	, 0.0f	, 0.0f	);
				Primitives::drawCircle(BOARDSIZE/2 * m_pxSize - (m_pxSize/2), BOARDSIZE/2 * m_pxSize - (m_pxSize/2), m_pxSize/4, 24);
			
				glColor3f(0.0f	, 1.0f	, 0.0f	);
				Primitives::drawCircle(BOARDSIZE/2 * m_pxSize + (m_pxSize/2), BOARDSIZE/2 * m_pxSize - (m_pxSize/2), m_pxSize/4, 24);
		
				glColor3f(0.0f	, 0.0f	, 1.0f	);
				Primitives::drawCircle(BOARDSIZE/2 * m_pxSize + (m_pxSize/2), BOARDSIZE/2 * m_pxSize + (m_pxSize/2), m_pxSize/4, 24);
	
				glColor3f(1.0f	, 0.847f, 0.0f	);
				Primitives::drawCircle(BOARDSIZE/2 * m_pxSize - (m_pxSize/2), BOARDSIZE/2 * m_pxSize + (m_pxSize/2), m_pxSize/4, 24);

				break;

					
		};
	}

	void Board::m_buildGrid()
	{
		SubBoard sub1, sub2, sub3, sub4;	
		
		//Randomize the directions: 0,90,180,270
		int choices[4] = {1, 2, 3, 4};
		for (int size = 4; size > 0; size--)
		{
			int pick = rand() % size;
			
			switch (choices[pick])
			{
				case 1:	sub1.loadType(4 - size);
					break;
				case 2: sub2.loadType(4 - size);
					break;
				case 3: sub3.loadType(4 - size);
					break;
				case 4: sub4.loadType(4 - size);
					break;
			}

			//Swap the chosen value with the 'tail' of the list
			choices[pick] = choices[3 - (4 - size)];
		}
	
		//Randomize each subboard: front or back
		
		if ( rand() % 2 == 0)
			sub1.back();
		if ( rand() % 2 == 0)
			sub2.back();
		if ( rand() % 2 == 0)
			sub3.back();
		if ( rand() % 2 == 0)
			sub4.back();
	
		//Randomize each robot's starting position
		/*
			[q1][q2]
			[q3][q4]
		char q# = 0x 0000 0000
		             ____ ____
			     xpos ypos
		*/
		unsigned char q[4] = {0, 0, 0, 0};
		unsigned char xpos, ypos;

		//q1 ranges from (0,0) to (7,7), but excludes the (7,7) corner
		xpos = rand() % 8;
		(xpos == 7) ? ypos = rand() % 7 : ypos = rand() % 8;
		q[0] = xpos;
		q[0] = (unsigned char)(q[0] << 4);
		q[0] += ypos;

		//q2 ranges from (8,0) to (15,7), but excludes the (8,7) corner
		xpos = rand() % 8 + 8;
		(xpos == 8) ? ypos = rand() % 7 : ypos = rand() % 8;
		q[1] = xpos;
		q[1] = (unsigned char)(q[1] << 4);
		q[1] += ypos;

		//q3 ranges from (0,8) to (7,15), but excludes the (7,8) corner
		xpos = rand() % 8;
		(xpos == 7) ? ypos = rand() % 7 + 9 : ypos = rand() % 8 + 8;
		q[2] = xpos;
		q[2] = (unsigned char)(q[2] << 4);
		q[2] += ypos;

		//q4 ranges from (8,8) to (15,15), but excludes the (8,8) corner
		xpos = rand() % 8 + 8;
		(xpos == 8) ? ypos = rand() % 7 + 9 : ypos = rand() % 8 + 8;
		q[3] = xpos;
		q[3] = (unsigned char)(q[3] << 4);
		q[3] += ypos;	
	
		choices[0] = 0;
		choices[1] = 1;
		choices[2] = 2;
		choices[3] = 3;
		for (int size = 4; size > 0; size--)
		{
			int pick = rand() % size;
			switch (choices[pick])
			{
				case 0:
					m_robots.redPos = q[4 - size];
					break;
				case 1:
					m_robots.yellowPos = q[4 - size];
					break;
				case 2:
					m_robots.greenPos = q[4 - size];
					break;
				case 3:
					m_robots.bluePos = q[4 - size];
					break;
			};
			choices[pick] = choices[3 - (4 - size)];
		}
		
		//Randomize the goal piece chosen
		m_goal = (GoalPiece)(rand() % 17);
		
		m_assignGoals(sub1, 0);
		for (unsigned int i = 0; i < BOARDSIZE/2; i++)
			for (unsigned int j = 0; j < BOARDSIZE/2; j++)
				m_grid[i][j] = sub1.get(i,j);

		sub2.rotate90();
		m_assignGoals(sub2, 90);
		for (unsigned int i = 0; i < BOARDSIZE/2; i++)
			for (unsigned int j = 0; j < BOARDSIZE/2; j++)
				m_grid[i + BOARDSIZE/2][j] = sub2.get(i,j);
		
		sub3.rotate180();
		m_assignGoals(sub3, 180);
		for (unsigned int i = 0; i < BOARDSIZE/2; i++)
			for (unsigned int j = 0; j < BOARDSIZE/2; j++)
				m_grid[i + BOARDSIZE/2][j + BOARDSIZE/2] = sub3.get(i,j);
		
		sub4.rotate270();
		m_assignGoals(sub4, 270);
		for (unsigned int i = 0; i < BOARDSIZE/2; i++)
			for (unsigned int j = 0; j < BOARDSIZE/2; j++)
				m_grid[i][j + BOARDSIZE/2] = sub4.get(i,j);

		//Seal off the 'Vortex' goal's open border
		xpos = (m_goals.vortex & 0xF0) >> 4;
		ypos = (m_goals.vortex & 0x0F);
		if (xpos == 7 || xpos == 8 || ypos == 7 || ypos == 8) //If the vortex is along the seam...
		{
			if (m_grid[ypos][xpos].isOpenN == false && ypos > 0)
				m_grid[ypos - 1][xpos].isOpenS = false;

			if (m_grid[ypos][xpos].isOpenE == false && xpos < BOARDSIZE - 1)
				m_grid[ypos][xpos + 1].isOpenW = false;

			if (m_grid[ypos][xpos].isOpenS == false && ypos < BOARDSIZE - 1)
				m_grid[ypos + 1][xpos].isOpenN = false;

			if (m_grid[ypos][xpos].isOpenW == false && xpos > 0)
				m_grid[ypos][xpos - 1].isOpenE = false;
		}
	}

	void Board::m_assignGoals(SubBoard subBoard, int rotation)
	{
		unsigned char xOffset = 0;
		unsigned char yOffset = 0;
		switch (rotation)
		{
			default:
			case 0:
				break;
			case 90:
				yOffset = BOARDSIZE/2;
				break;
			case 180:
				xOffset = BOARDSIZE/2;
				yOffset = BOARDSIZE/2;
				break;
			case 270:
				xOffset = BOARDSIZE/2;
				break;
		}

		for (int i = 0; i < 5; i++)
		{
			SubGoal sg = subBoard.getSubGoal(i);
			switch (sg.type)
			{
				case GREENTRIANGLE:
					m_goals.greenTriangle = (unsigned char)(sg.pos + (xOffset << 4) + yOffset);
					break;
				case GREENCIRCLE:	
					m_goals.greenCircle = (unsigned char)(sg.pos + (xOffset << 4) + yOffset);
					break;
				case GREENDIAMOND:
					m_goals.greenDiamond = (unsigned char)(sg.pos + (xOffset << 4) + yOffset);
					break;
				case GREENSQUARE:
					m_goals.greenSquare = (unsigned char)(sg.pos + (xOffset << 4) + yOffset);
					break;

				case YELLOWTRIANGLE:
					m_goals.yellowTriangle = (unsigned char)(sg.pos + (xOffset << 4) + yOffset);
					break;
				case YELLOWCIRCLE:
					m_goals.yellowCircle = (unsigned char)(sg.pos + (xOffset << 4) + yOffset);
					break;
				case YELLOWDIAMOND:
					m_goals.yellowDiamond = (unsigned char)(sg.pos + (xOffset << 4) + yOffset);
					break;
				case YELLOWSQUARE:
					m_goals.yellowSquare = (unsigned char)(sg.pos + (xOffset << 4) + yOffset);
					break;

				case BLUETRIANGLE:
					m_goals.blueTriangle = (unsigned char)(sg.pos + (xOffset << 4) + yOffset);
					break;
				case BLUECIRCLE:
					m_goals.blueCircle = (unsigned char)(sg.pos + (xOffset << 4) + yOffset);
					break;
				case BLUEDIAMOND:
					m_goals.blueDiamond = (unsigned char)(sg.pos + (xOffset << 4) + yOffset);
					break;
				case BLUESQUARE:
					m_goals.blueSquare = (unsigned char)(sg.pos + (xOffset << 4) + yOffset);
					break;

				case REDTRIANGLE:
					m_goals.redTriangle = (unsigned char)(sg.pos + (xOffset << 4) + yOffset);
					break;
				case REDCIRCLE:
					m_goals.redCircle = (unsigned char)(sg.pos + (xOffset << 4) + yOffset);
					break;
				case REDDIAMOND:
					m_goals.redDiamond = (unsigned char)(sg.pos + (xOffset << 4) + yOffset);
					break;
				case REDSQUARE:
					m_goals.redSquare = (unsigned char)(sg.pos + (xOffset << 4) + yOffset);
					break;
				
				case VORTEX:
					m_goals.vortex = (unsigned char)(sg.pos + (xOffset << 4) + yOffset);
				default:
					break;
			}
		}
	}
} //End Namespace
