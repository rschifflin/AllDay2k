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
			
		if (board == NULL)
		{
			m_isLoaded = false;
			m_isSolved = false;
		}
		else
		{
			//Initialize empty set with Initial State
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
			GoalPiece goal = board->getGoal();
			Goals goalPos = board->getGoalPos();
			unsigned char robotPos;
			
			if (goal != VORTEX && goal != NOGOALPIECE)
			{
				switch (goal)
				{
						case GREENTRIANGLE:
						case GREENCIRCLE:
						case GREENDIAMOND:
						case GREENSQUARE:
							robotPos = checkNode->robots.greenPos;
							break;
							
						case YELLOWTRIANGLE:
						case YELLOWCIRCLE:
						case YELLOWDIAMOND:
						case YELLOWSQUARE:
							robotPos = checkNode->robots.yellowPos;
							break;
							
						case BLUETRIANGLE:
						case BLUECIRCLE:
						case BLUEDIAMOND:
						case BLUESQUARE:
							robotPos = checkNode->robots.bluePos;
							break;
							
						case REDTRIANGLE:
						case REDCIRCLE:
						case REDDIAMOND:
						case REDSQUARE:
							robotPos = checkNode->robots.redPos;
							break;						
				}
				
				if (robotPos == goalPos[goal])
						m_isSolved = true;
						
			}
			else if (	goal == VORTEX && 
						(
							checkNode->robots.bluePos == goalPos[goal]
							||	checkNode->robots.redPos == goalPos[goal]
							||	checkNode->robots.greenPos == goalPos[goal]
							||	checkNode->robots.yellowPos == goalPos[goal]
						)
					)
					m_isSolved = true;
					
			
			if (m_isSolved) //Create solution path and set iter
			{
				m_solutionPath.clear();

				for (Node* solNode = checkNode; solNode != NULL; solNode = solNode->parent)
					m_solutionPath.pushFront(solNode);
				
				m_solutionIter = m_solutionPath.begin();
			}
		}
			
			
	}
	
	void Solver::m_hash(Robots robots)
	{
			uint64_t retval = 0;
			retval += robots.greenPos;
			retval << 4;
			retval += robots.yellowPos;
			retval << 4;
			retval += robots.bluePos;
			retval << 4;
			retval += robots.redPos;
			retval << 4;
			retval += robots.blackPos;
			return retval;
	}
	
	void Solver::m_expandNode(Node* nodeToExpand)
	{
			//Check for goal
			m_checkForGoal(nodeToExpand);
			
			if (!m_isSolved)
			{
				unsigned char xpos, ypos;
				xpos = (nodeToExpand->robots.redPos & 0x0F) >> 4;
				ypos = nodeToExpand->robots.redPos & 0xF0;
				
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
			m_open.clearAndFree();
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
			/*...*/
		}
	}
	
	void Solver::solutionPrev()
	{
		if (m_isSolved)
		{
				/*...*/
		}
	}
	
	int Solver::getSolutionSize() const
	{
		if (m_isSolved)
		{
				/*...*/
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
