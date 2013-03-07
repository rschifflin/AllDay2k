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
			m_seed = (unsigned int)time(NULL);
		else
			m_seed = seed;

		srand( seed );
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
				case YELLOWDIAMOND:
					glColor3f(1.0f	, 0.847f, 0.0f	);
					Primitives::drawDiamond(pxSize*j + 2,pxSize*i + 2,pxSize- 4,pxSize- 4);
					break;
				case REDCIRCLE:
					glColor3f(1.0f	, 0.0f	, 0.0f);
					Primitives::drawCircle(pxSize*j + (pxSize/2), pxSize*i + (pxSize/2), (pxSize/2), 24);
					break;
				case BLUESQUARE:
					glColor3f(0.0f	, 0.0f	, 1.0f	);
					Primitives::drawSquare(pxSize*j + 2,pxSize*i + 2,pxSize- 4,pxSize- 4);
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
				}


			}
	}

	void Board::m_buildGrid()
	{
		SubBoard sub;
		sub.loadType(0);

		sub.back();
		for (unsigned int i = 0; i < BOARDSIZE/2; i++)
			for (unsigned int j = 0; j < BOARDSIZE/2; j++)
				m_grid[i][j] = sub.get(i,j);
			
		sub.rotate90();
		for (unsigned int i = 0; i < BOARDSIZE/2; i++)
			for (unsigned int j = 0; j < BOARDSIZE/2; j++)
				m_grid[i + BOARDSIZE/2][j] = sub.get(i,j);
		
	
		sub.rotate270();
		for (unsigned int i = 0; i < BOARDSIZE/2; i++)
			for (unsigned int j = 0; j < BOARDSIZE/2; j++)
				m_grid[i][j + BOARDSIZE/2] = sub.get(i,j);
			
		sub.rotate180();
		for (unsigned int i = 0; i < BOARDSIZE/2; i++)
			for (unsigned int j = 0; j < BOARDSIZE/2; j++)
				m_grid[i + BOARDSIZE/2][j + BOARDSIZE/2] = sub.get(i,j);
	}
} //End Namespace
