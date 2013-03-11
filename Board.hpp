#ifndef RS_BOARD
#define RS_BOARD

/*
A Board object holds a 16x16 grid of 'squares'
Each square has a few properties

1. A boolean for each cardinal direction, representing whether or not the corresponding edge of that square is 'solid'
2. One of 16 possible 'goal' pieces, or a non-goal piece
3. The presence of a colored bumper and its orientation (Either 'ForwardSlash' or 'BackSlash')
4. The presence of a robot piece

The 16x16 grid is composed of 4 double-sided 8x8 subgrids, each rotated in one of four orientations

Members:

Methods
	void Create()
	Pre: None
	Post: 
	

*/

namespace RicochetRobots
{

	enum GoalPiece
	{
		NOGOALPIECE,
	
		REDCIRCLE,
		REDSQUARE,
		REDTRIANGLE,
		REDDIAMOND,

		BLUECIRCLE,
		BLUESQUARE,
		BLUETRIANGLE,
		BLUEDIAMOND,

		GREENCIRCLE,
		GREENSQUARE,
		GREENTRIANGLE,
		GREENDIAMOND,

		YELLOWCIRCLE,
		YELLOWSQUARE,
		YELLOWTRIANGLE,
		YELLOWDIAMOND,

		VORTEX
	};

	enum Bumper
	{
		/*
			Forward  looks like: /
			Backward looks like: \
		*/
		NOBUMPER,

		REDFORWARD, 
		REDBACKWARD, 

		BLUEFORWARD,
		BLUEBACKWARD,

		GREENFORWARD,
		GREENBACKWARD,

		YELLOWFORWARD,
		YELLOWBACKWARD
	};

	struct Square
	{
		bool isOpenN;
		bool isOpenE;
		bool isOpenS;
		bool isOpenW;

		GoalPiece goalPiece;
		Bumper bumper;
	};

	const unsigned int BOARDSIZE = 16;

	class SubBoard
	{
		Square m_grid[BOARDSIZE/2][BOARDSIZE/2];  //Actual orientation

		Square m_gridA[BOARDSIZE/2][BOARDSIZE/2]; //Front side reference
		Square m_gridB[BOARDSIZE/2][BOARDSIZE/2]; //Back side reference
		
		bool m_isFront;
		int m_angle;
		void m_assignGrid(); //Uses front flag and angle to set m_grid to the correct orientation

	public:
		SubBoard(unsigned int type = 0);

		Square get(unsigned int i, unsigned int j) { if (i < BOARDSIZE/2 && j < BOARDSIZE/2) return m_grid[i][j]; return m_grid[0][0]; }

		void loadType(unsigned int type); //Creates one of four subboard types

		void front() {if (!m_isFront) { m_isFront = true; m_assignGrid(); } }
		void back() {if (m_isFront) { m_isFront = false; m_assignGrid(); } }

		void rotate0() {if (m_angle != 0) { m_angle = 0; m_assignGrid(); } }
		void rotate90() {if (m_angle != 90) { m_angle = 90; m_assignGrid(); } }
		void rotate180() {if (m_angle != 180) { m_angle = 180; m_assignGrid(); } }
		void rotate270() {if (m_angle != 270) { m_angle = 270; m_assignGrid(); } }
	};

	class Board
	{
		unsigned int m_seed;
		Square m_grid[BOARDSIZE][BOARDSIZE];
		
		int pxSize;
		void m_buildGrid(); //Sets m_grid to the four combined boards
	public:
		Board(unsigned int seed = 0); //Can specify a specific board if needed; 0 is a random board

		void resetBoard();				//Reset board with current seed
		void createBoard(unsigned int seed = 0);	//Create new board with specified seed; 0 is a random board
		void draw();					//Render the board to the screen

		int getSize() {return BOARDSIZE;}

		Square getSquare(unsigned int x, unsigned int y){ if (x < BOARDSIZE && y < BOARDSIZE) return m_grid[y][x]; /*Else error: invalid bounds*/ return m_grid[0][0]; }
		
		
	};

} //End Namespace RicochetRobots
#endif //RS_BOARD
