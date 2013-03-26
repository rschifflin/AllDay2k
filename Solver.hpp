/*
	Solver for a Ricochet Robots board
*/

#ifndef RS_SOLVER
#define RS_SOLVER

#include "Board.hpp" //Used to get state
#include "OpenSet.hpp" //Used to store open set
#include <unordered_map> //Used to store closed set
#include <list> //Used to store solution path

namespace RicochetRobots
{
	
	uint64_t hashState(Robots m_robots);

	class Solver
	{
		/* We want nodes to be as small as possible 
			Robots requires 64 bits
			parent ptr is 32 bits (Compile with -m32)
			hvalue is 16 bits;
			depth value is 16bits;

			minimum size: 128 = 4 memory locations in 32bit mode.
			Max indexable memory: 2^32 memory locations
			Max theoretical search size: 2^32 / 2^2 = 2^30 = 1,073,741,824 nodes

			Note: The open set has two parts- the heap and the handles. So in essence the open set
			takes up (nOpenNodes + nOpenHandles) space. Since A* is very bushy, this will eat up a large amount of space.
		*/

		struct Node
		{
			Node* parent;
			Robots robots;
			uint16_t h;
			uint16_t d;
		};
		
		enum Direction
		{
			NORTH,
			EAST,
			SOUTH,
			WEST,
			NODIRECTION
		};
		
	public:
		class cmpNodes
		{
		public:
			bool operator()(const Node* A, const Node* B)
			{
					return ( (A->h + (256 * A->d)) < (B->h + (256 * B->d)) );
			}
		};
		
	private:
		unsigned char hvalues[256]; //Pre-computed h-value for every position on the board.
		
		bool m_isLoaded; //Can only execute if a Board is loaded.
		bool m_isSolved; //Can only traverse a completed board if it is solved.
		void m_checkForGoal(Node* checkNode); //If checkNode matches the goal state, it sets m_isSolved to true and generates an m_solutionPath.
		Board* m_board; //Holds board walls, bumpers, goals and the current goal state. Holds the robots for initial state.

		uint16_t m_calcH(Robots robots); //Calculates the heuristic based on robot positions and goal spot.
		uint64_t m_hash(Robots robots); //Converts Robots to a 64-bit hash key
		void m_expandNode(Node* nodeToExpand); //Adds node to Closed; adds children to open, calculates children's h-value and d-value.
		
		//Helper functions for calculating moves
		unsigned char m_getMove(unsigned char currentPos, Direction dir);

		//Helper function: pre-calculate board hvalues
		void m_precalcH(unsigned char goalPos, GoalPiece goalPiece, Direction dir = NODIRECTION);

		//Closed set stored as hash
		std::unordered_map<uint64_t, Node*> m_closed;

		//Open set stored as heap with top value the move with the lowest cost
		//Making our own version for ability to erase
		OpenSet<Node*, cmpNodes> m_next;

		//Doubly-linked list stores traversable solution path
		std::list<Node*> m_solutionPath;
		std::list<Node*>::iterator m_solutionIter;

		public:
		
		Solver(): m_isLoaded(false), m_isSolved(false), m_board(NULL) {}
		Solver(Board* board);

		void loadBoard(Board* board);	//Initializes solver for searching. Resets everything.
		void search();					//Takes a single node from open, moves it to closed, pushes children to open, checks if any child is a solution.

		void stop();	 				//Ends the search, frees up the occupied memory
		void solutionNext();			//Updates the board's Robots to be the next move in the solution path
		void solutionPrev();			//Updates the board's Robots to be the prev move in the solution path
		int  getSolutionStep() const;	//Returns the current move in the solution path
		int  getSolutionSize() const;   //Returns the current size of the solution path
		
		bool isSolved() const {return m_isSolved;}
		
		unsigned char getH(unsigned char pos) { return hvalues[pos]; }
		
	}; //End Class Solver

} //End Namespace RicochetRobots

#endif //RS_SOLVER
