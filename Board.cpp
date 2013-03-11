#include "Board.hpp"
#include "SDL/SDL_opengl.h"
#include <stdlib.h>
#include <time.h>
#include "Primitives.hpp"

namespace RicochetRobots
{
	SubBoard::SubBoard(unsigned int type)
	{
		loadType(type);
	}

	void SubBoard::loadType(unsigned int type)
	{
		for (unsigned int i = 0; i < BOARDSIZE/2; i++)
			for (unsigned int j = 0; j < BOARDSIZE/2; j++)
			{
				m_gridA[i][j].isOpenN = true;
				m_gridA[i][j].isOpenE = true;
				m_gridA[i][j].isOpenS = true;
				m_gridA[i][j].isOpenW = true;

				m_gridA[i][j].bumper = NOBUMPER;
				m_gridA[i][j].goalPiece = NOGOALPIECE;

				m_gridB[i][j].isOpenN = true;
				m_gridB[i][j].isOpenE = true;
				m_gridB[i][j].isOpenS = true;
				m_gridB[i][j].isOpenW = true;

				m_gridB[i][j].bumper = NOBUMPER;
				m_gridB[i][j].goalPiece = NOGOALPIECE;
			}

		switch (type)
		{
		/*case 0:*/
		default:
		case 0:
			m_gridA[0][1].isOpenE = false;
			m_gridA[0][2].isOpenW = false;
			m_gridA[0][3].isOpenS = false;

			m_gridA[1][2].isOpenE = false;
			m_gridA[1][3].isOpenW = false;
			m_gridA[1][3].isOpenN = false;
			m_gridA[1][3].goalPiece = GREENTRIANGLE;

			m_gridA[3][6].isOpenE = false;
			m_gridA[3][6].isOpenS = false;
			m_gridA[3][6].goalPiece = YELLOWDIAMOND;
			m_gridA[3][7].isOpenW = false;

			m_gridA[4][0].isOpenE = false;
			m_gridA[4][1].isOpenW = false;
			m_gridA[4][1].isOpenS = false;
			m_gridA[4][1].goalPiece = REDCIRCLE;
			m_gridA[4][6].isOpenN = false;

			m_gridA[5][1].isOpenN = false;
			m_gridA[5][4].isOpenS = false;

			m_gridA[6][0].isOpenS = false;
			m_gridA[6][4].isOpenE = false;
			m_gridA[6][4].isOpenN = false;
			m_gridA[6][4].goalPiece = BLUESQUARE;
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
			m_gridB[3][1].goalPiece = REDCIRCLE;

			m_gridB[4][6].isOpenE = false;
			m_gridB[4][6].isOpenS = false;
			m_gridB[4][6].goalPiece = YELLOWDIAMOND;

			m_gridB[4][7].isOpenW = false;

			m_gridB[5][0].isOpenS = false;
			m_gridB[5][2].isOpenS = false;
			m_gridB[5][6].isOpenN = false;

			m_gridB[6][0].isOpenN = false;
			m_gridB[6][2].isOpenN = false;
			m_gridB[6][2].isOpenE = false;
			m_gridB[6][2].goalPiece = GREENTRIANGLE;
			m_gridB[6][3].isOpenW = false;
			m_gridB[6][3].isOpenS = false;
			m_gridB[6][3].goalPiece = BLUESQUARE;
			m_gridB[6][7].isOpenS = false;

			m_gridB[7][3].isOpenN = false;
			m_gridB[7][5].bumper = YELLOWBACKWARD;
			m_gridB[7][6].isOpenE = false;
			m_gridB[7][7].isOpenW = false;
			m_gridB[7][7].isOpenN = false;

			break;
		case 1:
			m_gridA[0][1].isOpenE = false;
			m_gridA[0][2].isOpenW = false;
			m_gridA[0][4].isOpenS = false;

			m_gridA[1][4].isOpenN = false;
			m_gridA[1][4].isOpenE = false;
			m_gridA[1][4].goalPiece = GREENCIRCLE;
			m_gridA[1][5].isOpenW = false;

			
			m_gridA[3][0].isOpenE = false;
			
			m_gridA[3][1].isOpenW = false;
			m_gridA[3][1].isOpenS = false;
			m_gridA[3][1].goalPiece = REDTRIANGLE;
			
			m_gridA[4][1].isOpenN = false;
			m_gridA[4][5].isOpenS = false;
			
			m_gridA[5][0].isOpenS = false;
			m_gridA[5][4].isOpenE = false;
			m_gridA[5][5].isOpenW = false;
			m_gridA[5][5].isOpenN = false;
			m_gridA[5][5].goalPiece = YELLOWSQUARE;
			
			m_gridA[6][0].isOpenN = false;
			m_gridA[6][3].isOpenS = false;
			m_gridA[6][3].isOpenE = false;
			m_gridA[6][3].goalPiece = BLUEDIAMOND;
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
			m_gridB[2][6].goalPiece = BLUEDIAMOND;
			m_gridB[2][7].isOpenW = false;

			m_gridB[3][0].isOpenN = false;
			m_gridB[3][2].isOpenS = false;
			m_gridB[3][6].isOpenN = false;
			m_gridB[3][6].bumper = YELLOWBACKWARD;

			m_gridB[4][2].isOpenN = false;
			m_gridB[4][2].isOpenE = false;
			m_gridB[4][2].goalPiece = GREENCIRCLE;
			m_gridB[4][3].isOpenW = false;
			m_gridB[4][3].isOpenS = false;
			m_gridB[4][3].goalPiece = REDTRIANGLE;

			m_gridB[5][3].isOpenN = false;
			m_gridB[5][5].isOpenS = false;

			m_gridB[6][4].isOpenE = false;
			m_gridB[6][5].isOpenW = false;
			m_gridB[6][5].isOpenN = false;
			m_gridB[6][5].goalPiece = YELLOWSQUARE;
			m_gridB[6][7].isOpenS = false;

			m_gridB[7][6].isOpenE = false;
			m_gridB[7][7].isOpenN = false;
			m_gridB[7][7].isOpenW = false;
			break;
		case 2:
			m_gridA[0][5].isOpenE = false;
			m_gridA[0][6].isOpenW = false;

			m_gridA[1][3].isOpenS = false;
		
			m_gridA[2][2].isOpenE = false;
			m_gridA[2][3].isOpenW = false;
			m_gridA[2][3].isOpenN = false;
			m_gridA[2][3].goalPiece = YELLOWCIRCLE;

			m_gridA[3][0].isOpenS = false;			
			m_gridA[3][2].isOpenS = false;
			m_gridA[3][4].isOpenE = false;
			m_gridA[3][5].isOpenW = false;
			m_gridA[3][5].isOpenS = false;
			m_gridA[3][5].goalPiece = BLUETRIANGLE;
			
			m_gridA[4][0].isOpenN = false;
			m_gridA[4][2].isOpenN = false;
			m_gridA[4][2].isOpenE = false;
			m_gridA[4][2].goalPiece = REDSQUARE;
			m_gridA[4][3].isOpenW = false;
			m_gridA[4][5].isOpenN = false;
			
			m_gridA[5][4].isOpenE = false;
			m_gridA[5][4].isOpenS = false;
			m_gridA[5][4].goalPiece = GREENDIAMOND;
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
			m_gridB[2][5].goalPiece = GREENDIAMOND;
			m_gridB[2][6].isOpenN = false;
			m_gridB[2][6].isOpenW = false;
			m_gridB[2][6].goalPiece = YELLOWCIRCLE;
						
			m_gridB[3][5].isOpenN = false;
			
			m_gridB[4][7].bumper = REDBACKWARD;
			
			m_gridB[5][0].isOpenE = false;
			m_gridB[5][1].isOpenW = false;
			m_gridB[5][1].isOpenS = false;
			m_gridB[5][1].goalPiece = REDSQUARE;
			
			m_gridB[6][0].isOpenS = false;
			m_gridB[6][1].isOpenN = false;
			m_gridB[6][4].isOpenS = false;
			m_gridB[6][7].isOpenS = false;
			
			m_gridB[7][0].isOpenN = false;
			m_gridB[7][4].isOpenN = false;
			m_gridB[7][4].isOpenE = false;
			m_gridB[7][4].goalPiece = BLUETRIANGLE;
			m_gridB[7][5].isOpenW = false;
			m_gridB[7][6].isOpenE = false;
			m_gridB[7][7].isOpenW = false;
			m_gridB[7][7].isOpenN = false;
			break;

		case 3:
			m_gridA[0][2].isOpenE = false;
			m_gridA[0][3].isOpenW = false;

			m_gridA[1][4].isOpenE = false;
			m_gridA[1][5].isOpenW = false;
			m_gridA[1][5].isOpenS = false;
			m_gridA[1][5].goalPiece = BLUECIRCLE;
		
			m_gridA[2][5].isOpenN = false;
			m_gridA[2][7].isOpenS = false;
			m_gridA[2][7].isOpenE = false;
			m_gridA[2][7].goalPiece = VORTEX;

			m_gridA[3][0].isOpenS = false;			
			m_gridA[3][7].isOpenN = false;			
			
			m_gridA[4][0].isOpenN = false;
			m_gridA[4][3].isOpenE = false;
			m_gridA[4][3].isOpenS = false;
			m_gridA[4][3].goalPiece = REDDIAMOND;
			m_gridA[4][4].isOpenW = false;
			m_gridA[4][6].isOpenS = false;
			
			m_gridA[5][1].isOpenS = false;
			m_gridA[5][3].isOpenN = false;
			m_gridA[5][5].isOpenE = false;
			m_gridA[5][6].isOpenW = false;
			m_gridA[5][6].isOpenN = false;
			m_gridA[5][6].goalPiece = GREENSQUARE;
			
			m_gridA[6][1].isOpenN = false;
			m_gridA[6][1].isOpenE = false;
			m_gridA[6][1].goalPiece = YELLOWTRIANGLE;
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
			m_gridB[2][6].goalPiece = YELLOWTRIANGLE;
						
			m_gridB[3][2].isOpenN = false;
			m_gridB[3][2].isOpenE = false;
			m_gridB[3][2].goalPiece = BLUECIRCLE;
			m_gridB[3][3].isOpenW = false;
			m_gridB[3][3].isOpenS = false;
			m_gridB[3][3].goalPiece = GREENSQUARE;
			
			m_gridB[4][3].isOpenN = false;
			
			m_gridB[5][1].isOpenE = false;
			m_gridB[5][1].isOpenS = false;
			m_gridB[5][1].goalPiece = REDDIAMOND;
			m_gridB[5][2].isOpenW = false;
			
			m_gridB[6][0].isOpenS = false;
			m_gridB[6][1].isOpenN = false;
			m_gridB[6][3].bumper = GREENBACKWARD;
			m_gridB[6][7].isOpenS = false;
			
			m_gridB[7][0].isOpenN = false;
			m_gridB[7][5].isOpenE = false;
			m_gridB[7][5].isOpenS = false;
			m_gridB[7][5].goalPiece = VORTEX;
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
				for (unsigned int i = 0; i < BOARDSIZE/2; i++)
					for (unsigned int j = 0; j < BOARDSIZE/2; j++)
						m_grid[i][j] = m_gridA[i][j];
			}
			else if (m_angle == 90)
			{
				for (unsigned int i = 0; i < BOARDSIZE/2; i++)
					for (unsigned int j = 0; j < BOARDSIZE/2; j++)
					{
						int u = j;
						int v = BOARDSIZE/2 - 1 - i;

						m_grid[i][j] = m_gridA[u][v];

						m_grid[i][j].isOpenE = m_gridA[u][v].isOpenS;
						m_grid[i][j].isOpenS = m_gridA[u][v].isOpenW;
						m_grid[i][j].isOpenW = m_gridA[u][v].isOpenN;
						m_grid[i][j].isOpenN = m_gridA[u][v].isOpenE;
					}
			}
			else if (m_angle == 180)
			{
				for (unsigned int i = 0; i < BOARDSIZE/2; i++)
					for (unsigned int j = 0; j < BOARDSIZE/2; j++)
					{
						int u = BOARDSIZE/2 - 1 - i;
						int v = BOARDSIZE/2 - 1 - j;

						m_grid[i][j] = m_gridA[u][v];

						m_grid[i][j].isOpenE = m_gridA[u][v].isOpenW;
						m_grid[i][j].isOpenS = m_gridA[u][v].isOpenN;
						m_grid[i][j].isOpenW = m_gridA[u][v].isOpenE;
						m_grid[i][j].isOpenN = m_gridA[u][v].isOpenS;
					}
			}
			else if (m_angle == 270)
			{
				for (unsigned int i = 0; i < BOARDSIZE/2; i++)
					for (unsigned int j = 0; j < BOARDSIZE/2; j++)
					{
						int u = BOARDSIZE/2 - 1 - j;
						int v = i;

						m_grid[i][j] = m_gridA[u][v];

						m_grid[i][j].isOpenE = m_gridA[u][v].isOpenN;
						m_grid[i][j].isOpenS = m_gridA[u][v].isOpenE;
						m_grid[i][j].isOpenW = m_gridA[u][v].isOpenS;
						m_grid[i][j].isOpenN = m_gridA[u][v].isOpenW;
					}
			}

		}
		else
		{
			if (m_angle == 0)
			{
				for (unsigned int i = 0; i < BOARDSIZE/2; i++)
					for (unsigned int j = 0; j < BOARDSIZE/2; j++)
						m_grid[i][j] = m_gridB[i][j];
			}
			else if (m_angle == 90)
			{
				for (unsigned int i = 0; i < BOARDSIZE/2; i++)
					for (unsigned int j = 0; j < BOARDSIZE/2; j++)
					{
						int u = j;
						int v = BOARDSIZE/2 - 1 - i;

						m_grid[i][j] = m_gridB[u][v];

						m_grid[i][j].isOpenE = m_gridB[u][v].isOpenS;
						m_grid[i][j].isOpenS = m_gridB[u][v].isOpenW;
						m_grid[i][j].isOpenW = m_gridB[u][v].isOpenN;
						m_grid[i][j].isOpenN = m_gridB[u][v].isOpenE;

						//Flip bumpers
						int bumperVal = m_grid[i][j].bumper;
						if (bumperVal != NOBUMPER)
						{
							if (bumperVal % 2 == 1)
								m_grid[i][j].bumper = (Bumper)(bumperVal + 1);
							else
								m_grid[i][j].bumper = (Bumper)(bumperVal - 1);
						}
					}
			}
			else if (m_angle == 180)
			{
				for (unsigned int i = 0; i < BOARDSIZE/2; i++)
					for (unsigned int j = 0; j < BOARDSIZE/2; j++)
					{
						int u = BOARDSIZE/2 - 1 - i;
						int v = BOARDSIZE/2 - 1 - j;

						m_grid[i][j] = m_gridB[u][v];

						m_grid[i][j].isOpenE = m_gridB[u][v].isOpenW;
						m_grid[i][j].isOpenS = m_gridB[u][v].isOpenN;
						m_grid[i][j].isOpenW = m_gridB[u][v].isOpenE;
						m_grid[i][j].isOpenN = m_gridB[u][v].isOpenS;
					}
			}
			else if (m_angle == 270)
			{
				for (unsigned int i = 0; i < BOARDSIZE/2; i++)
					for (unsigned int j = 0; j < BOARDSIZE/2; j++)
					{
						int u = BOARDSIZE/2 - 1 - j;
						int v = i;

						m_grid[i][j] = m_gridB[u][v];

						m_grid[i][j].isOpenE = m_gridB[u][v].isOpenN;
						m_grid[i][j].isOpenS = m_gridB[u][v].isOpenE;
						m_grid[i][j].isOpenW = m_gridB[u][v].isOpenS;
						m_grid[i][j].isOpenN = m_gridB[u][v].isOpenW;

						//Flip bumpers
						int bumperVal = m_grid[i][j].bumper;
						if (bumperVal != NOBUMPER)
						{
							if (bumperVal % 2 == 1)
								m_grid[i][j].bumper = (Bumper)(bumperVal + 1);
							else
								m_grid[i][j].bumper = (Bumper)(bumperVal - 1);
						}
					}
			}
		}
	}

	Board::Board(unsigned int seed)
	{
		pxSize = 32;
		createBoard(seed);
	}

	void Board::createBoard(unsigned int seed)
	{
		if (seed == 0)
			m_seed = time(NULL);
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
		for (unsigned int i = 0; i < BOARDSIZE; i++)
			for (unsigned int j = 0; j < BOARDSIZE; j++)
			{
				//Clear color is white, drawing white squares unneccesary
				/*
				glColor3f(1.0,1.0,1.0);
				glBegin(GL_QUADS);
					glVertex2i(16*i		,	16*j		);
					glVertex2i(16*i + 16,	16*j		);
					glVertex2i(16*i + 16,	16*j + 16	);
					glVertex2i(16*i		,	16*j + 16	);
				glEnd();
				*/
				
				//Draw grid lines
				glColor3f(0.75,0.75,0.75);
				glBegin(GL_LINE_LOOP);
					glVertex2i(pxSize*j			,	pxSize*i			);
					glVertex2i(pxSize*j + pxSize,	pxSize*i			);
					glVertex2i(pxSize*j + pxSize,	pxSize*i + pxSize	);
					glVertex2i(pxSize*j			,	pxSize*i + pxSize	);
				glEnd();
				

				//Draw walls
				glColor3f(0.0,0.0,0.0);
				glBegin(GL_LINE_LOOP);
					glVertex2i(0					, 0					);
					glVertex2i(BOARDSIZE * pxSize	, 0					);
					glVertex2i(BOARDSIZE * pxSize	, BOARDSIZE * pxSize);
					glVertex2i(0					, BOARDSIZE * pxSize);
				glEnd();

				glBegin(GL_LINES);
					if (m_grid[i][j].isOpenN == false)
					{
						glVertex2i(pxSize*j			,	pxSize*i + 1		);
						glVertex2i(pxSize*j + pxSize,	pxSize*i + 1		);
					}

					if (m_grid[i][j].isOpenE == false)
					{
						glVertex2i(pxSize*j + pxSize - 1,	pxSize*i + pxSize	);
						glVertex2i(pxSize*j	+ pxSize - 1,	pxSize*i			);
					}
					
					if (m_grid[i][j].isOpenS == false)
					{
						glVertex2i(pxSize*j			,	pxSize*i + pxSize - 1	);
						glVertex2i(pxSize*j + pxSize,	pxSize*i + pxSize - 1	);
					}
					
					if (m_grid[i][j].isOpenW == false)
					{
						glVertex2i(pxSize*j + 1	,	pxSize*i			);
						glVertex2i(pxSize*j + 1	,	pxSize*i + pxSize	);
					}
					
				glEnd();

				//Draw pieces
				switch (m_grid[i][j].goalPiece)
				{
				default:
				case NOGOALPIECE:
				
					break;
				case GREENTRIANGLE:
					glColor3f(0.0f	, 1.0f	, 0.0f	);
					Primitives::drawTriangle(pxSize*j + 2, pxSize*i + 2,pxSize - 4,pxSize - 4);
					break;			
				case GREENCIRCLE:
					glColor3f(0.0f	, 1.0f	, 0.0f);
					Primitives::drawCircle(pxSize*j + (pxSize/2), pxSize*i + (pxSize/2), (pxSize/2), 24);
					break;
				case GREENDIAMOND:
					glColor3f(0.0f	, 1.0f	, 0.0f);
					Primitives::drawDiamond(pxSize*j + 2,pxSize*i + 2,pxSize- 4,pxSize- 4);
					break;
				case GREENSQUARE:
					glColor3f(0.0f	, 1.0f	, 0.0f);	
					Primitives::drawSquare(pxSize*j + 2,pxSize*i + 2,pxSize- 4,pxSize- 4);
					break;

				case YELLOWTRIANGLE:
					glColor3f(1.0f	, 0.847f, 0.0f	);
					Primitives::drawTriangle(pxSize*j + 2, pxSize*i + 2,pxSize - 4,pxSize - 4);
					break;			
				case YELLOWCIRCLE:	
					glColor3f(1.0f	, 0.847f, 0.0f	);
					Primitives::drawCircle(pxSize*j + (pxSize/2), pxSize*i + (pxSize/2), (pxSize/2), 24);
					break;
				case YELLOWDIAMOND:
					glColor3f(1.0f	, 0.847f, 0.0f	);
					Primitives::drawDiamond(pxSize*j + 2,pxSize*i + 2,pxSize- 4,pxSize- 4);
					break;
				case YELLOWSQUARE:	
					glColor3f(1.0f	, 0.847f, 0.0f	);
					Primitives::drawSquare(pxSize*j + 2,pxSize*i + 2,pxSize- 4,pxSize- 4);
					break;				
					
				case BLUETRIANGLE:
					glColor3f(0.0f	, 0.0f	, 1.0f	);
					Primitives::drawTriangle(pxSize*j + 2, pxSize*i + 2,pxSize - 4,pxSize - 4);
					break;			
				case BLUECIRCLE:	
					glColor3f(0.0f	, 0.0f	, 1.0f	);
					Primitives::drawCircle(pxSize*j + (pxSize/2), pxSize*i + (pxSize/2), (pxSize/2), 24);
					break;
				case BLUEDIAMOND:
					glColor3f(0.0f	, 0.0f	, 1.0f	);
					Primitives::drawDiamond(pxSize*j + 2,pxSize*i + 2,pxSize- 4,pxSize- 4);
					break;
				case BLUESQUARE:	
					glColor3f(0.0f	, 0.0f	, 1.0f	);
					Primitives::drawSquare(pxSize*j + 2,pxSize*i + 2,pxSize- 4,pxSize- 4);
					break;
	
				case REDTRIANGLE:
					glColor3f(1.0f	, 0.0f	, 0.0f	);
					Primitives::drawTriangle(pxSize*j + 2, pxSize*i + 2,pxSize - 4,pxSize - 4);
					break;			
				case REDCIRCLE:	
					glColor3f(1.0f	, 0.0f	, 0.0f	);
					Primitives::drawCircle(pxSize*j + (pxSize/2), pxSize*i + (pxSize/2), (pxSize/2), 24);
					break;
				case REDDIAMOND:
					glColor3f(1.0f	, 0.0f	, 0.0f	);
					Primitives::drawDiamond(pxSize*j + 2,pxSize*i + 2,pxSize- 4,pxSize- 4);
					break;
				case REDSQUARE:	
					glColor3f(1.0f	, 0.0f	, 0.0f	);
					Primitives::drawSquare(pxSize*j + 2,pxSize*i + 2,pxSize- 4,pxSize- 4);
					break;

				case VORTEX:
					glColor3f(1.0f	, 0.0f	, 0.0f	);
					Primitives::drawCircle(pxSize*j + (pxSize/3), pxSize*i + (pxSize/3), (pxSize/6), 24);
					glColor3f(0.0f	, 1.0f	, 0.0f	);
					Primitives::drawCircle(pxSize*j + (pxSize * 2/3), pxSize*i + (pxSize/3), (pxSize/6), 24);
					glColor3f(0.0f	, 0.0f	, 1.0f	);
					Primitives::drawCircle(pxSize*j + (pxSize * 2/3), pxSize*i + (pxSize * 2/3), (pxSize/6), 24);
					glColor3f(1.0f	, 0.847f, 0.0f	);
					Primitives::drawCircle(pxSize*j + (pxSize/3), pxSize*i + (pxSize * 2/3), (pxSize/6), 24);
					break;

					
				}

				switch (m_grid[i][j].bumper)
				{
				default:
				case NOBUMPER:
				
					break;
				case GREENFORWARD:
					glColor3f(0.0f	, 1.0f	, 0.0f	);
					Primitives::drawForwardSlash(pxSize*j, pxSize*i, pxSize, pxSize);
					break;
				case GREENBACKWARD:
					glColor3f(0.0f	, 1.0f	, 0.0f	);
					Primitives::drawBackwardSlash(pxSize*j, pxSize*i, pxSize, pxSize);
					break;
				case YELLOWFORWARD:
					glColor3f(1.0f	, 0.847f, 0.0f	);
					Primitives::drawForwardSlash(pxSize*j, pxSize*i, pxSize, pxSize);
					break;
				case YELLOWBACKWARD:
					glColor3f(1.0f	, 0.847f, 0.0f	);
					Primitives::drawBackwardSlash(pxSize*j, pxSize*i, pxSize, pxSize);
					break;
				case BLUEFORWARD:
					glColor3f(0.0f	, 0.0f	, 1.0f	);
					Primitives::drawForwardSlash(pxSize*j, pxSize*i, pxSize, pxSize);
					break;
				case BLUEBACKWARD:
					glColor3f(0.0f	, 0.0f	, 1.0f	);
					Primitives::drawBackwardSlash(pxSize*j, pxSize*i, pxSize, pxSize);
					break;
				case REDFORWARD:
					glColor3f(1.0f	, 0.0f	, 0.0f	);
					Primitives::drawForwardSlash(pxSize*j, pxSize*i, pxSize, pxSize);
					break;
				case REDBACKWARD:
					glColor3f(1.0f	, 0.0f	, 0.0f	);
					Primitives::drawBackwardSlash(pxSize*j, pxSize*i, pxSize, pxSize);
					break;
				}


			}
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
	
		//Randomize each piece: front or back
		if ( rand() % 2 == 0)
			sub1.back();
		if ( rand() % 2 == 0)
			sub2.back();
		if ( rand() % 2 == 0)
			sub3.back();
		if ( rand() % 2 == 0)
			sub4.back();

		//Build the grid	
		for (unsigned int i = 0; i < BOARDSIZE/2; i++)
			for (unsigned int j = 0; j < BOARDSIZE/2; j++)
				m_grid[i][j] = sub1.get(i,j);
		

		sub2.rotate90();
		for (unsigned int i = 0; i < BOARDSIZE/2; i++)
			for (unsigned int j = 0; j < BOARDSIZE/2; j++)
				m_grid[i + BOARDSIZE/2][j] = sub2.get(i,j);
		
		sub3.rotate270();
		for (unsigned int i = 0; i < BOARDSIZE/2; i++)
			for (unsigned int j = 0; j < BOARDSIZE/2; j++)
				m_grid[i][j + BOARDSIZE/2] = sub3.get(i,j);
		
		sub4.rotate180();
		for (unsigned int i = 0; i < BOARDSIZE/2; i++)
			for (unsigned int j = 0; j < BOARDSIZE/2; j++)
				m_grid[i + BOARDSIZE/2][j + BOARDSIZE/2] = sub4.get(i,j);
	}
} //End Namespace
