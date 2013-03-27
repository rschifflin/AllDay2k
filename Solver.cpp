/* Implements Solver.hpp */

#include "Solver.hpp"

namespace RicochetRobots
{
	
	Solver::Solver(Board* board)
	{
		loadBoard(board);	
	}
	
	void Solver::loadBoard(Board* board)
	{
		if (m_isLoaded == true) //Board already loaded
			stop();				//Will clear the board and free memory
				
		for (int i = 0; i < 256; i++)
			hvalues[i] = 255; //Initialize grid to 255
		
		if (board == NULL)
		{
			m_isLoaded = false;
			m_isSolved = false;
			m_board = NULL;
		}
		else
		{
			//Initialize empty set with Initial State
			m_board = board;
			Color color;
			switch (m_board->getGoal())
			{
				case NOGOALPIECE:
				case VORTEX:
				case GREENTRIANGLE:
				case GREENDIAMOND:
				case GREENCIRCLE:
				case GREENSQUARE:
					color = GREEN;
					break;
					
				case YELLOWTRIANGLE:
				case YELLOWDIAMOND:
				case YELLOWCIRCLE:
				case YELLOWSQUARE:
					color = YELLOW;
					break;
					
				case BLUETRIANGLE:
				case BLUEDIAMOND:
				case BLUECIRCLE:
				case BLUESQUARE:			
					color = BLUE;
					break;
					
				case REDTRIANGLE:
				case REDDIAMOND:
				case REDCIRCLE:
				case REDSQUARE:
					color = RED;
					break;
			}
			m_precalcH(m_board->getGoalPos(), color);
			
			Node* root = new Node;
			
			root->parent = NULL;
			root->robots = board->getRobots();
			root->h = m_calcH(root->robots);
			root->d = 0;
			
			m_next.push(root);
			
			m_isLoaded = true;
			m_isSolved = false;
			
			
		}
	}
	
	void Solver::m_checkForGoal(Node* checkNode)
	{
		if (!m_isSolved && checkNode != NULL)
		{
			Goals goals = m_board->getGoals();
			
			switch (m_board->getGoal())
			{
						case NOGOALPIECE:
							break;
							
						case VORTEX:
							if (checkNode->robots.bluePos == goals.vortex 	||
								checkNode->robots.redPos == goals.vortex 	||
								checkNode->robots.greenPos == goals.vortex	||
								checkNode->robots.yellowPos == goals.vortex	 )
								m_isSolved = true;
							break;

						case GREENTRIANGLE:
							if (checkNode->robots.greenPos == goals.greenTriangle)
								m_isSolved = true;
							break;	
						case GREENCIRCLE:
							if (checkNode->robots.greenPos == goals.greenCircle)
								m_isSolved = true;
							break;
						case GREENDIAMOND:
							if (checkNode->robots.greenPos == goals.greenDiamond)
								m_isSolved = true;
							break;
						case GREENSQUARE:
							if (checkNode->robots.greenPos == goals.greenSquare)
								m_isSolved = true;
							break;
							
						case YELLOWTRIANGLE:
							if (checkNode->robots.yellowPos == goals.yellowTriangle)
								m_isSolved = true;
							break;
						case YELLOWCIRCLE:
							if (checkNode->robots.yellowPos == goals.yellowCircle)
								m_isSolved = true;
							break;
						case YELLOWDIAMOND:
							if (checkNode->robots.yellowPos == goals.yellowDiamond)
								m_isSolved = true;
							break;
						case YELLOWSQUARE:
							if (checkNode->robots.yellowPos == goals.yellowSquare)
								m_isSolved = true;
							break;
							
						case BLUETRIANGLE:
							if (checkNode->robots.bluePos == goals.blueTriangle)
								m_isSolved = true;
							break;
						case BLUECIRCLE:
							if (checkNode->robots.bluePos == goals.blueCircle)
								m_isSolved = true;
							break;
						case BLUEDIAMOND:
							if (checkNode->robots.bluePos == goals.blueDiamond)
								m_isSolved = true;
							break;
						case BLUESQUARE:
							if (checkNode->robots.bluePos == goals.blueSquare)
								m_isSolved = true;
							break;
							
						case REDTRIANGLE:
							if (checkNode->robots.redPos == goals.redTriangle)
								m_isSolved = true;
							break;
						case REDCIRCLE:
							if (checkNode->robots.redPos == goals.redCircle)
								m_isSolved = true;
							break;
						case REDDIAMOND:
							if (checkNode->robots.redPos == goals.redDiamond)
								m_isSolved = true;
							break;
						case REDSQUARE:
							if (checkNode->robots.redPos == goals.redSquare)
								m_isSolved = true;
							break;					
			}
			
			if (m_isSolved) //Create solution path and set iter
			{
				m_solutionPath.clear();

				for (Node* solNode = checkNode; solNode != NULL; solNode = solNode->parent)
					m_solutionPath.push_front(solNode);
				
				m_solutionIter = m_solutionPath.begin();
				m_board->setRobots( m_solutionPath.front()->robots );
			}
		}
			
			
	}
	uint16_t Solver::m_calcH(Robots robots)
	{
		//Heuristic has two parts
		//Most-Significant 8-bits: Admissable heuristic 'minimum rook moves with no other robots'
		//Leas-Significant 8-bits: Weight heuristic 'best blockers'
		uint16_t retval;
		
		uint8_t h1 = 0;
		uint8_t h2 = 0;
		
		Color color = NOCOLOR;
		Square square;
		
		switch (m_board->getGoal())
		{
			case NOGOALPIECE:
			case VORTEX:
			case GREENTRIANGLE:
			case GREENDIAMOND:
			case GREENCIRCLE:
			case GREENSQUARE:
				color = GREEN;
				h1 = hvalues[robots.greenPos];
				break;
				
			case YELLOWTRIANGLE:
			case YELLOWDIAMOND:
			case YELLOWCIRCLE:
			case YELLOWSQUARE:
				color = YELLOW;
				h1 = hvalues[robots.yellowPos];
				break;
				
			case BLUETRIANGLE:
			case BLUEDIAMOND:
			case BLUECIRCLE:
			case BLUESQUARE:			
				color = BLUE;
				h1 = hvalues[robots.bluePos];
				break;
				
			case REDTRIANGLE:
			case REDDIAMOND:
			case REDCIRCLE:
			case REDSQUARE:
				color = RED;
				h1 = hvalues[robots.redPos];
				break;
		}
		
		//Green
		if (color != GREEN)
		{
			square = m_board->getSquare( (robots.greenPos & 0xF0) >> 4, robots.greenPos & 0x0F );
			//N
			if ( (robots.greenPos & 0x0F) > 0 && square.isOpenN && hvalues[robots.greenPos - 1] < 5)
				h2 += hvalues[robots.greenPos - 1];
			else
				h2 += 5;
				
			//E
			if ( ((robots.greenPos & 0xF0) >> 4) < 15 && square.isOpenE && hvalues[robots.greenPos + 16] < 5)
				h2 += hvalues[robots.greenPos + 16];
			else
				h2 += 5;
				
			//S
			if ( (robots.greenPos & 0x0F) < 15 && square.isOpenS && hvalues[robots.greenPos + 1] < 5)
				h2 += hvalues[robots.greenPos + 1];
			else
				h2 += 5;
			
			//W
			if ( ((robots.greenPos & 0xF0) >> 4) > 0 && square.isOpenW && hvalues[robots.greenPos - 16] < 5)
				h2 += hvalues[robots.greenPos - 16];
			else
				h2 += 5;
		}
		
		//Yellow
		if (color != YELLOW)
		{
		square = m_board->getSquare( (robots.yellowPos & 0xF0) >> 4, robots.yellowPos & 0x0F );
		
			//N
			if ( (robots.yellowPos & 0x0F) > 0 && square.isOpenN && hvalues[robots.yellowPos - 1] < 5)
				h2 += hvalues[robots.yellowPos - 1];
			else
				h2 += 5;
				
			//E
			if ( ((robots.yellowPos & 0xF0) >> 4) < 15 && square.isOpenE && hvalues[robots.yellowPos + 16] < 5)
				h2 += hvalues[robots.yellowPos + 16];
			else
				h2 += 5;
				
			//S
			if ( (robots.yellowPos & 0x0F) < 15 && square.isOpenS && hvalues[robots.yellowPos + 1] < 5)
				h2 += hvalues[robots.yellowPos + 1];
			else
				h2 += 5;
			
			//W
			if ( ((robots.yellowPos & 0xF0) >> 4) > 0 && square.isOpenW && hvalues[robots.yellowPos - 16] < 5)
				h2 += hvalues[robots.yellowPos - 16];
			else
				h2 += 5;
		}
		
		//Blue
		if (color != BLUE)
		{
		square = m_board->getSquare( (robots.bluePos & 0xF0) >> 4, robots.bluePos & 0x0F );
		
			//N
			if ( (robots.bluePos & 0x0F) > 0 && square.isOpenN && hvalues[robots.bluePos - 1] < 5)
				h2 += hvalues[robots.bluePos - 1];
			else
				h2 += 5;
				
			//E
			if ( ((robots.bluePos & 0xF0) >> 4) < 15 && square.isOpenE && hvalues[robots.bluePos + 16] < 5)
				h2 += hvalues[robots.bluePos + 16];
			else
				h2 += 5;
				
			//S
			if ( (robots.bluePos & 0x0F) < 15 && square.isOpenS && hvalues[robots.bluePos + 1] < 5)
				h2 += hvalues[robots.bluePos + 1];
			else
				h2 += 5;
			
			//W
			if ( ((robots.bluePos & 0xF0) >> 4) > 0 && square.isOpenW && hvalues[robots.bluePos - 16] < 5)
				h2 += hvalues[robots.bluePos - 16];
			else
				h2 += 5;
		}	
		
		//Red
		if (color != RED)
		{
		square = m_board->getSquare( (robots.redPos & 0xF0) >> 4, robots.redPos & 0x0F );
		
			//N
			if ( (robots.redPos & 0x0F) > 0 && square.isOpenN && hvalues[robots.redPos - 1] < 5)
				h2 += hvalues[robots.redPos - 1];
			else
				h2 += 5;
				
			//E
			if ( ((robots.redPos & 0xF0) >> 4) < 15 && square.isOpenE && hvalues[robots.redPos + 16] < 5)
				h2 += hvalues[robots.redPos + 16];
			else
				h2 += 5;
				
			//S
			if ( (robots.redPos & 0x0F) < 15 && square.isOpenS && hvalues[robots.redPos + 1] < 5)
				h2 += hvalues[robots.redPos + 1];
			else
				h2 += 5;
			
			//W
			if ( ((robots.redPos & 0xF0) >> 4) > 0 && square.isOpenW && hvalues[robots.redPos - 16] < 5)
				h2 += hvalues[robots.redPos - 16];
			else
				h2 += 5;		
		}
		
		//Black
			square = m_board->getSquare( (robots.blackPos & 0xF0) >> 4, robots.blackPos & 0x0F );
		
			//N
			if ( (robots.blackPos & 0x0F) > 0 && square.isOpenN && hvalues[robots.blackPos - 1] < 5)
				h2 += hvalues[robots.blackPos - 1];
			else
				h2 += 5;
				
			//E
			if ( ((robots.blackPos & 0xF0) >> 4) < 15 && square.isOpenE && hvalues[robots.blackPos + 16] < 5)
				h2 += hvalues[robots.blackPos + 16];
			else
				h2 += 5;
				
			//S
			if ( (robots.blackPos & 0x0F) < 15 && square.isOpenS && hvalues[robots.blackPos + 1] < 5)
				h2 += hvalues[robots.blackPos + 1];
			else
				h2 += 5;
			
			//W
			if ( ( (robots.blackPos & 0xF0) >> 4) > 0 && square.isOpenW && hvalues[robots.blackPos - 16] < 5)
				h2 += hvalues[robots.blackPos - 16];
			else
				h2 += 5;
					
		retval = h1;
		retval = retval << 8;
		retval += h2;
		
		return retval;
	}

	unsigned char Solver::m_getMove(unsigned char currentPos, Direction dir, Color color)
	{
		/*	CurrentPos = 8bits
			xxxx		yyyy
			----		----
			0-15xpos 	0-15ypos			
		*/
		
		unsigned char initialPos = currentPos;
		
		
		
		switch (dir)
		{
			case NORTH:
				while ( (currentPos & 0x0F) > 0 )
				{
					Square currentSquare = m_board->getSquare( (currentPos & 0xF0) >> 4, (currentPos & 0x0F) );
					Color bumperColor = NOCOLOR;
					bool bumperIsForward = false;
					
					if ( currentSquare.bumper != NOBUMPER && initialPos != currentPos)
					{
						switch (currentSquare.bumper)
						{
								case GREENFORWARD:
								case GREENBACKWARD:
									bumperColor = GREEN;
									break;
								case YELLOWFORWARD:
								case YELLOWBACKWARD:
									bumperColor = YELLOW;
									break;
								case BLUEFORWARD:
								case BLUEBACKWARD:
									bumperColor = BLUE;
									break;
								case REDFORWARD:
								case REDBACKWARD:
									bumperColor = RED;
									break;
								default:
									break;
						}
						switch (currentSquare.bumper)
						{
								case GREENFORWARD:
								case YELLOWFORWARD:
								case BLUEFORWARD:
								case REDFORWARD:
									bumperIsForward = true;
									break;
								default:
									break;
						}					
					}	
					
					if (color != bumperColor && bumperColor != NOCOLOR)
					{
							if (bumperIsForward)
								currentPos = m_getMove(currentPos, EAST, color);
							else
								currentPos = m_getMove(currentPos, WEST, color);
							break;
					}
					
					if (currentSquare.isOpenN == false)
						break;
								
					if ( m_board->getSquare( (currentPos & 0xF0) >> 4, (currentPos & 0x0F) - 1).isOpenS == false)
						break;
						
					if ( 	(m_board->getRobots().greenPos  == currentPos - 1 	&& color != GREEN )||
							(m_board->getRobots().yellowPos == currentPos - 1 	&& color != YELLOW)||
							(m_board->getRobots().bluePos   == currentPos - 1	&& color != BLUE)  ||
							(m_board->getRobots().redPos    == currentPos - 1	&& color != RED)   ||
							(m_board->getRobots().blackPos  == currentPos - 1	&& color != BLACK)	 )
						break;
						
					currentPos -= 1;
				}
				break;
				
			case SOUTH:
				while ( (currentPos & 0x0F) < 15 )
				{
					Square currentSquare = m_board->getSquare( (currentPos & 0xF0) >> 4, (currentPos & 0x0F) );
					Color bumperColor = NOCOLOR;
					bool bumperIsForward = false;
					
					if ( currentSquare.bumper != NOBUMPER && initialPos != currentPos)
					{
						switch (currentSquare.bumper)
						{
								case GREENFORWARD:
								case GREENBACKWARD:
									bumperColor = GREEN;
									break;
								case YELLOWFORWARD:
								case YELLOWBACKWARD:
									bumperColor = YELLOW;
									break;
								case BLUEFORWARD:
								case BLUEBACKWARD:
									bumperColor = BLUE;
									break;
								case REDFORWARD:
								case REDBACKWARD:
									bumperColor = RED;
									break;
								default:
									break;
						}
						switch (currentSquare.bumper)
						{
								case GREENFORWARD:
								case YELLOWFORWARD:
								case BLUEFORWARD:
								case REDFORWARD:
									bumperIsForward = true;
									break;
								default:
									break;
						}					
					}	
					
					if (color != bumperColor && bumperColor != NOCOLOR)
					{
							if (bumperIsForward)
								currentPos = m_getMove(currentPos, WEST, color);
							else
								currentPos = m_getMove(currentPos, EAST, color);
							break;
					}
					
					if ( currentSquare.isOpenS == false)
						break;
						
					if ( m_board->getSquare( (currentPos & 0xF0) >> 4, (currentPos & 0x0F) + 1).isOpenN == false)
						break;
						
					if ( 	(m_board->getRobots().greenPos  == currentPos + 1 	&& color != GREEN )||
							(m_board->getRobots().yellowPos == currentPos + 1 	&& color != YELLOW)||
							(m_board->getRobots().bluePos   == currentPos + 1	&& color != BLUE)  ||
							(m_board->getRobots().redPos    == currentPos + 1	&& color != RED)   ||
							(m_board->getRobots().blackPos  == currentPos + 1	&& color != BLACK)	 )
						break;
						
					currentPos += 1;
				}
				break;
			
			case EAST:
				while ( ((currentPos & 0xF0) >> 4) < 15 )
				{
					Square currentSquare = m_board->getSquare( (currentPos & 0xF0) >> 4, (currentPos & 0x0F) );
					Color bumperColor = NOCOLOR;
					bool bumperIsForward = false;
					
					if ( currentSquare.bumper != NOBUMPER && initialPos != currentPos)
					{
						switch (currentSquare.bumper)
						{
								case GREENFORWARD:
								case GREENBACKWARD:
									bumperColor = GREEN;
									break;
								case YELLOWFORWARD:
								case YELLOWBACKWARD:
									bumperColor = YELLOW;
									break;
								case BLUEFORWARD:
								case BLUEBACKWARD:
									bumperColor = BLUE;
									break;
								case REDFORWARD:
								case REDBACKWARD:
									bumperColor = RED;
									break;
								default:
									break;
						}
						switch (currentSquare.bumper)
						{
								case GREENFORWARD:
								case YELLOWFORWARD:
								case BLUEFORWARD:
								case REDFORWARD:
									bumperIsForward = true;
									break;
								default:
									break;
						}					
					}	
					
					if (color != bumperColor && bumperColor != NOCOLOR)
					{
							if (bumperIsForward)
								currentPos = m_getMove(currentPos, NORTH, color);
							else
								currentPos = m_getMove(currentPos, SOUTH, color);
							break;
					}
					
					if ( currentSquare.isOpenE == false )
						break;
						
					if ( m_board->getSquare( ((currentPos & 0xF0) >> 4) + 1, (currentPos & 0x0F) ).isOpenW == false)
						break;
						
					if ( 	(m_board->getRobots().greenPos  == currentPos + 16 	&& color != GREEN )||
							(m_board->getRobots().yellowPos == currentPos + 16 	&& color != YELLOW)||
							(m_board->getRobots().bluePos   == currentPos + 16	&& color != BLUE)  ||
							(m_board->getRobots().redPos    == currentPos + 16	&& color != RED)   ||
							(m_board->getRobots().blackPos  == currentPos + 16	&& color != BLACK)	 )
						break;
						
					currentPos += 16;
				}
				break;
				
			case WEST:
				while ( ((currentPos & 0xF0) >> 4) > 0 )
				{
					Square currentSquare = m_board->getSquare( (currentPos & 0xF0) >> 4, (currentPos & 0x0F) );
					Color bumperColor = NOCOLOR;
					bool bumperIsForward = false;
					
					if ( currentSquare.bumper != NOBUMPER && initialPos != currentPos)
					{
						switch (currentSquare.bumper)
						{
								case GREENFORWARD:
								case GREENBACKWARD:
									bumperColor = GREEN;
									break;
								case YELLOWFORWARD:
								case YELLOWBACKWARD:
									bumperColor = YELLOW;
									break;
								case BLUEFORWARD:
								case BLUEBACKWARD:
									bumperColor = BLUE;
									break;
								case REDFORWARD:
								case REDBACKWARD:
									bumperColor = RED;
									break;
								default:
									break;
						}
						switch (currentSquare.bumper)
						{
								case GREENFORWARD:
								case YELLOWFORWARD:
								case BLUEFORWARD:
								case REDFORWARD:
									bumperIsForward = true;
									break;
								default:
									break;
						}					
					}	
					
					if (color != bumperColor && bumperColor != NOCOLOR)
					{
							if (bumperIsForward)
								currentPos = m_getMove(currentPos, SOUTH, color);
							else
								currentPos = m_getMove(currentPos, NORTH, color);
							break;
					}
					
					if ( currentSquare.isOpenW == false )
						break;
						
					if ( m_board->getSquare( ((currentPos & 0xF0) >> 4) - 1, (currentPos & 0x0F) ).isOpenE == false)
						break;
						
					if ( 	(m_board->getRobots().greenPos  == currentPos - 16 	&& color != GREEN )||
							(m_board->getRobots().yellowPos == currentPos - 16 	&& color != YELLOW)||
							(m_board->getRobots().bluePos   == currentPos - 16	&& color != BLUE)  ||
							(m_board->getRobots().redPos    == currentPos - 16	&& color != RED)   ||
							(m_board->getRobots().blackPos  == currentPos - 16	&& color != BLACK)	 )
						break;
						
					currentPos -= 16;
				}
				break;
		}
		
		return currentPos;
	}	
	
	uint64_t Solver::m_hash(Robots robots)
	{
			uint64_t retval = 0;
			retval += robots.greenPos;
			retval = retval << 8;
			retval += robots.yellowPos;
			retval = retval << 8;
			retval += robots.bluePos;
			retval = retval << 8;
			retval += robots.redPos;
			retval = retval << 8;
			retval += robots.blackPos;
			return retval;
	}
	
	void Solver::m_precalcH(unsigned char goalPos, Color goalColor, Direction dir)
	{	
		static unsigned char cost = 0;
		if (hvalues[goalPos] > cost)
		{
			hvalues[goalPos] = cost;
			Square currentSquare = m_board->getSquare( (goalPos & 0xF0) >> 4, goalPos & 0x0F );
			if (currentSquare.bumper != NOBUMPER)
			{
				Color bumperColor = NOCOLOR;
				bool bumperIsForward = false;
				
				switch (currentSquare.bumper)
				{
						case GREENFORWARD:
						case GREENBACKWARD:
							bumperColor = GREEN;
							break;
						case YELLOWFORWARD:
						case YELLOWBACKWARD:
							bumperColor = YELLOW;
							break;
						case BLUEFORWARD:
						case BLUEBACKWARD:
							bumperColor = BLUE;
							break;
						case REDFORWARD:
						case REDBACKWARD:
							bumperColor = RED;
							break;
						default:
							break;
				}
				switch (currentSquare.bumper)
				{
						case GREENFORWARD:
						case YELLOWFORWARD:
						case BLUEFORWARD:
						case REDFORWARD:
							bumperIsForward = true;
							break;
						default:
							break;
				}
				if (goalColor != bumperColor && bumperColor != NOCOLOR)
				{
					if (bumperIsForward)
						switch (dir)
						{
								case NORTH:
									dir = EAST;
									break;
								case EAST:
									dir = NORTH;
									break;
								case SOUTH:
									dir = WEST;
									break;
								case WEST:
									dir = SOUTH;
									break;
						}
					else
						switch (dir)
						{
								case NORTH:
									dir = WEST;
									break;
								case EAST:
									dir = SOUTH;
									break;
								case SOUTH:
									dir = EAST;
									break;
								case WEST:
									dir = NORTH;
									break;								
						}
				}
					
			}
			
			switch (dir)
			{
				case NODIRECTION: //Initial state

					
					cost += 1;
					
					if ( (goalPos & 0x0F) > 0 && currentSquare.isOpenN)
						m_precalcH(goalPos - 1, goalColor, NORTH);
					if ( (goalPos & 0x0F) < 15 && currentSquare.isOpenS)
						m_precalcH(goalPos + 1, goalColor, SOUTH);
					if ( ((goalPos & 0xF0) >> 4) < 15 && currentSquare.isOpenE)
						m_precalcH(goalPos + 16, goalColor, EAST);
					if ( ((goalPos & 0xF0) >> 4) > 0 && currentSquare.isOpenW)
						m_precalcH(goalPos - 16, goalColor, WEST);
						
					cost -= 1;
				break;
				
				case NORTH: //Can look north for free, won't look south
				
					if ( (goalPos & 0x0F) > 0 && currentSquare.isOpenN)
						m_precalcH(goalPos - 1, goalColor, NORTH);
						
					cost += 1;
					if ( ((goalPos & 0xF0) >> 4) < 15 && currentSquare.isOpenE)
						m_precalcH(goalPos + 16, goalColor, EAST);
					if ( (goalPos & 0x0F) < 15 && currentSquare.isOpenS)
						m_precalcH(goalPos + 1, goalColor, SOUTH);
					if ( ((goalPos & 0xF0) >> 4) > 0 && currentSquare.isOpenW)
						m_precalcH(goalPos - 16, goalColor, WEST);
					cost -= 1;					
				break;
				
				case EAST: //Can look east for free, won't look west
					if ( ((goalPos & 0xF0) >> 4) < 15 && currentSquare.isOpenE)
						m_precalcH(goalPos + 16, goalColor, EAST);
						
					cost += 1;
					if ( (goalPos & 0x0F) > 0 && currentSquare.isOpenN)
						m_precalcH(goalPos - 1, goalColor, NORTH);
					if ( (goalPos & 0x0F) < 15 && currentSquare.isOpenS)
						m_precalcH(goalPos + 1, goalColor, SOUTH);		
					if ( ((goalPos & 0xF0) >> 4) > 0 && currentSquare.isOpenW)
						m_precalcH(goalPos - 16, goalColor, WEST);
					cost -= 1;
				break;
				
				case SOUTH: //Can look south for free, won't look north
					if ( (goalPos & 0x0F) < 15 && currentSquare.isOpenS)
						m_precalcH(goalPos + 1, goalColor, SOUTH);
						
					cost += 1;
					if ( (goalPos & 0x0F) > 0 && currentSquare.isOpenN)
						m_precalcH(goalPos - 1, goalColor, NORTH);
					if ( ((goalPos & 0xF0) >> 4) < 15 && currentSquare.isOpenE)
						m_precalcH(goalPos + 16, goalColor, EAST);
					if ( ((goalPos & 0xF0) >> 4) > 0 && currentSquare.isOpenW)
						m_precalcH(goalPos - 16, goalColor, WEST);
					cost -= 1;
				break;
				
				case WEST: //Can look west for free, won't look east
					if ( ((goalPos & 0xF0) >> 4) > 0 && currentSquare.isOpenW)
						m_precalcH(goalPos - 16, goalColor, WEST);
						
					cost += 1;
					if ( (goalPos & 0x0F) > 0 && currentSquare.isOpenN)
						m_precalcH(goalPos - 1, goalColor, NORTH);
					if ( ((goalPos & 0xF0) >> 4) < 15 && currentSquare.isOpenE)
						m_precalcH(goalPos + 16, goalColor, EAST);
					if ( (goalPos & 0x0F) < 15 && currentSquare.isOpenS)
						m_precalcH(goalPos + 1, goalColor, SOUTH);	
					cost -= 1;
				break;
			}
		}
	}
	
	void Solver::m_expandNode(Node* nodeToExpand)
	{
			//Check for goal
			m_checkForGoal(nodeToExpand);
			
			if (!m_isSolved)
			{
				m_board->setRobots(nodeToExpand->robots);
				
				Node* nextNode = NULL;
				Robots nextMove;
				unsigned char oldPos, newPos;
				
				//Green
				nextMove = nodeToExpand->robots;
				oldPos = nodeToExpand->robots.greenPos;
				for (int i = 0; i < 4; i++)
				{
					newPos = m_getMove(oldPos, static_cast<Direction>(i), GREEN);
					if (newPos != oldPos)
					{
						nextMove.greenPos = newPos;
						
						nextNode = new Node;
						nextNode->parent = nodeToExpand;
						nextNode->robots = nextMove;
						nextNode->h = m_calcH(nextMove);
						nextNode->d = nodeToExpand->d + 1;
						m_next.push(nextNode);
						nextNode = NULL;
					}
				}
							
				//Yellow
				nextMove.greenPos = oldPos;
				oldPos = nextMove.yellowPos;
				for (int i = 0; i < 4; i++)
				{
					newPos = m_getMove(oldPos, static_cast<Direction>(i), YELLOW);
					if (newPos != oldPos)
					{
						nextMove.yellowPos = newPos;
						
						nextNode = new Node;
						nextNode->parent = nodeToExpand;
						nextNode->robots = nextMove;
						nextNode->h = m_calcH(nextMove);
						nextNode->d = nodeToExpand->d + 1;
						m_next.push(nextNode);
						nextNode = NULL;	
					}
				}
							
				//Blue
				nextMove.yellowPos = oldPos;
				oldPos = nextMove.bluePos;
				
				for (int i = 0; i < 4; i++)
				{
					newPos = m_getMove(oldPos, static_cast<Direction>(i), BLUE);
					if (newPos != oldPos)
					{
						nextMove.bluePos = newPos;
						
						nextNode = new Node;
						nextNode->parent = nodeToExpand;
						nextNode->robots = nextMove;
						nextNode->h = m_calcH(nextMove);
						nextNode->d = nodeToExpand->d + 1;
						m_next.push(nextNode);
						nextNode = NULL;	
					}
				}	
						
				//Red
				nextMove.bluePos = oldPos;
				oldPos = nextMove.redPos;
				for (int i = 0; i < 4; i++)
				{
					newPos = m_getMove(oldPos, static_cast<Direction>(i), RED);
					if (newPos != oldPos)
					{
						nextMove.redPos = newPos;
						
						nextNode = new Node;
						nextNode->parent = nodeToExpand;
						nextNode->robots = nextMove;
						nextNode->h = m_calcH(nextMove);
						nextNode->d = nodeToExpand->d + 1;
						m_next.push(nextNode);
						nextNode = NULL;	
					}
				}	
										
				//Black
				nextMove.redPos = oldPos;
				oldPos = nextMove.blackPos;
				for (int i = 0; i < 4; i++)
				{
					newPos = m_getMove(oldPos, static_cast<Direction>(i), BLACK);
					if (newPos != oldPos)
					{
						nextMove.blackPos = newPos;
						
						nextNode = new Node;
						nextNode->parent = nodeToExpand;
						nextNode->robots = nextMove;
						nextNode->h = m_calcH(nextMove);
						nextNode->d = nodeToExpand->d + 1;
						m_next.push(nextNode);
						nextNode = NULL;	
					}
				}
			}

			
			
	}
	
	void Solver::search()
	{
			if (m_isLoaded && !m_isSolved)
			{
					if (m_next.isEmpty() == false)
					{
						Node* nodeToExpand = m_next.peek();
						m_next.pop();
						
						
						//Check if node is on closed
						uint64_t key = m_hash(nodeToExpand->robots);
						
						if (m_closed.count(key) > 0)
						{	
							if (m_closed[key]->d > nodeToExpand->d) //If this state is on Closed already, update it to be the cheaper node
							{
									m_closed[key]->d = nodeToExpand->d;
									m_closed[key]->parent = nodeToExpand->parent;
							}
							
							delete nodeToExpand;
							nodeToExpand = NULL;	
						}
						else
						{
							m_closed[key] = nodeToExpand;
							m_expandNode(nodeToExpand);
						}
					}
			}
	}
	
	void Solver::stop()
	{
			//Cancel search- free up all the used memory
			m_next.clearAndFree();
			for (auto i = m_closed.begin(); i != m_closed.end(); i++)
			{
					delete i->second;
					i->second = NULL;
			}
			m_closed.clear();
			m_solutionPath.clear();
			m_solutionIter = m_solutionPath.end();
			
			m_isLoaded = false;
			m_isSolved = false;
	}
	
	
	void Solver::solutionNext()
	{
		if (m_isSolved)
		{
			auto iterEnd = m_solutionPath.end();
			std::advance(iterEnd, -1);
			if (m_solutionIter != iterEnd)
			{
				
				std::advance(m_solutionIter, 1);
					m_board->setRobots( (*m_solutionIter)->robots );
			}
		}
	}
	
	void Solver::solutionPrev()
	{
		if (m_isSolved)
		{
				if (m_solutionIter != m_solutionPath.begin() )
					std::advance(m_solutionIter, -1);
				m_board->setRobots( (*m_solutionIter)->robots );
		}
	}
	
	int Solver::getSolutionSize() const
	{
		if (m_isSolved)
		{
				return static_cast<int>( m_solutionPath.size() );
		}
		
		return -1;
	}
	
	int Solver::getSolutionStep() const
	{
		if (m_isSolved)
		{
				/*...*/
		}
		
		return -1;
	}
}
