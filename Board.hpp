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
#include "SDL/SDL_opengl.h"
namespace RicochetRobots
{

	enum GoalPiece
	{
		GREENTRIANGLE,
		GREENCIRCLE,
		GREENDIAMOND,
		GREENSQUARE,
		
		YELLOWTRIANGLE,
		YELLOWCIRCLE,
		YELLOWDIAMOND,
		YELLOWSQUARE,

		BLUETRIANGLE,
		BLUECIRCLE,
		BLUEDIAMOND,
		BLUESQUARE,

		REDTRIANGLE,
		REDCIRCLE,
		REDDIAMOND,
		REDSQUARE,
		
		VORTEX,

		NOGOALPIECE
	};

	enum Bumper
	{
		/*
			Forward  looks like: /
			Backward looks like: \
		*/
		REDFORWARD, 
		REDBACKWARD, 

		BLUEFORWARD,
		BLUEBACKWARD,

		GREENFORWARD,
		GREENBACKWARD,

		YELLOWFORWARD,
		YELLOWBACKWARD,

		NOBUMPER
	};

	struct Robots
	{
		unsigned char greenPos;
		unsigned char yellowPos;
		unsigned char bluePos;
		unsigned char redPos;		
		unsigned char blackPos;
	};
	struct Goals
	{
		unsigned char greenTriangle;
		unsigned char greenCircle;
		unsigned char greenDiamond;
		unsigned char greenSquare;

		unsigned char yellowTriangle;
		unsigned char yellowCircle;
		unsigned char yellowDiamond;
		unsigned char yellowSquare;
		
		unsigned char blueTriangle;
		unsigned char blueCircle;
		unsigned char blueDiamond;
		unsigned char blueSquare;
		
		unsigned char redTriangle;
		unsigned char redCircle;
		unsigned char redDiamond;
		unsigned char redSquare;

		unsigned char vortex;	
	};
	struct SubGoal
	{	
		GoalPiece type;
		unsigned char pos;
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

	const int BOARDSIZE = 16;

	class SubBoard
	{
		Square m_grid[BOARDSIZE/2][BOARDSIZE/2];  //Actual orientation
		Square m_gridA[BOARDSIZE/2][BOARDSIZE/2]; //Front side reference
		Square m_gridB[BOARDSIZE/2][BOARDSIZE/2]; //Back side reference
		
		SubGoal m_subGoal[5]; //Actual subGoal reference
		SubGoal m_subGoalA[5]; //Front side reference
		SubGoal m_subGoalB[5]; //Back side reference

		bool m_isFront;
		int m_angle;
		void m_assignGrid(); //Uses front flag and angle to set m_grid to the correct orientation
	public:
		SubBoard(int type = 0);

		Square get(unsigned int i, unsigned int j) const { if (i < BOARDSIZE/2 && j < BOARDSIZE/2) return m_grid[i][j]; return m_grid[0][0]; }
		SubGoal getSubGoal(int index) const { if (index >= 0 && index <= 4) return m_subGoal[index]; return m_subGoal[0]; }

		void loadType(int type); //Creates one of four subboard types

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
		Robots m_robots;
		Goals m_goals;
		GoalPiece m_goal;
		
		GLint m_pxSize;
		void m_buildGrid(); //Sets m_grid to the four combined boards
		void m_assignGoals(SubBoard subBoard, int rotation); //Take the SubGoals from subBoard and insert them into m_goals
	public:
		Board(unsigned int seed = 0); //Can specify a specific board if needed; 0 is a random board

		void resetBoard();				//Reset board with current seed
		void createBoard(unsigned int seed = 0);	//Create new board with specified seed; 0 is a random board
		void draw();					//Render the board to the screen

		int getSize() const {return BOARDSIZE;}

		Square getSquare(unsigned int x, unsigned int y) const { if (x < BOARDSIZE && y < BOARDSIZE) return m_grid[y][x]; /*Else error: invalid bounds*/ return m_grid[0][0]; }
	};
} //End Namespace

#endif //RS_BOARD

