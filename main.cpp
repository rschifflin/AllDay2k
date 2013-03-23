//Program generates and solves arbitrary Ricochet Robots boards

//Program has 3 stages
/*
	'Unsolved'; takes parameters for setting up a random board
 
	'Solving'; uses A* to search for a solution in optimal # of moves
   
	'Solved'; Allows user to navigate solution with left/right arrows, or revert to Unsolved
 */

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include "Primitives.hpp" //Draw primitives
#include "GLNumbers.hpp" //Draw numbers
#include "Board.hpp" //Board object
#include "Timer.hpp" //Timer object
#include "GUI.hpp" //GUI objects
//#include "Solver.hpp" //Solver object; requires setup(Board) before solving can begin; 

int init();
int SDLInit();
int OpenGLInit();
int GUIInit();

void handleInput();
void draw();

//Hook functions for GUI
void onClickRandomize();
void onClickSolve();
void onClickStop();
void drawRandomize(GLint xpos, GLint ypos, GLint w, GLint h);
void drawSolve(GLint xpos, GLint ypos, GLint w, GLint h);
void drawStop(GLint xpos, GLint ypos, GLint w, GLint h);

int SCREENWIDTH = 512;
int SCREENHEIGHT = 548;

const int FRAMES_PER_SEC = 30;
const int MS_PER_FRAME = (1000 / FRAMES_PER_SEC);

enum SolveMode
{
	UNSOLVED,
	SOLVING,
	SOLVED,
	FUTILE
} solveMode;

Timer* testTimer = NULL;
RicochetRobots::Board* gameBoard = NULL;
GUI::GUIManager* guiManager = NULL;
bool hasQuit = false;

int main()
{
	if (init())
		return 0;
	Timer fps;
	testTimer = new Timer();
	gameBoard = new RicochetRobots::Board();

	while (!hasQuit)
	{	

		if (solveMode == SOLVING)
		{
			//Don't draw updates, don't framecap; let the solver run at max speed, only handle input
			handleInput();
		}
		else
		{
			fps.start();
			
			switch (solveMode)
			{
				default:
				case UNSOLVED:
					//In this mode, various keypresses set up the board's initial state
					break;
				
				case SOLVED:
					//In this mode, various keypresses navigate the board's solution
					break;
					
				case FUTILE:
					//In this mode, no solution was found
					break;
			}
			
			handleInput();
			draw();

			uint32_t elapsed = fps.getTicks();
			if (elapsed < MS_PER_FRAME )
				SDL_Delay( MS_PER_FRAME - elapsed);

			fps.reset();
		}
	}
	
	SDL_Quit();
	
	return 0;
}

int init()
{
	if (SDLInit())
		return 1;
	if (OpenGLInit())
		return 1;
	if (GUIInit())
		return 1;
	return 0;
}

int SDLInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		//std::cout << "Error initializing SDL" << std::endl;
		return 1;
	}

	//SDL_putenv("SDL_VIDEO_CENTERED=center");
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 1); //Ask for a stencil buffer
	if (SDL_SetVideoMode(SCREENWIDTH, SCREENHEIGHT, 32, SDL_OPENGL | SDL_RESIZABLE ) == NULL)
	{
		//std::cout << "Error opening screen" << std::endl;
		return 1;
	}
	

	SDL_WM_SetCaption("Ricochet Robots Solver",NULL);
	return 0;
}

int OpenGLInit()
{
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho(0.0,SCREENWIDTH,SCREENHEIGHT,0.0,101.0,-101.0);
	glMatrixMode(GL_MODELVIEW);	
	glViewport(0,0,SCREENWIDTH,SCREENHEIGHT);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0); //Set color buffer clear value to white
	glClearStencil(0);  //Set stencil buffer clear value to 0

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		//std::cout << "Error initializing OpenGL" << std::endl;
		return 1;
	}
	
	return 0;
}

int GUIInit()
{
	if (guiManager)
		delete guiManager;

	guiManager = new GUI::GUIManager;
	guiManager->addButton("btnRandomize", 0, SCREENHEIGHT-32, 32, 32, onClickRandomize, drawRandomize);
	guiManager->addButton("btnSolve", 32, SCREENHEIGHT-32, 32, 32, onClickSolve, drawSolve);
	guiManager->addButton("btnStop", 64, SCREENHEIGHT-32, 32, 32, onClickStop, drawStop);
	guiManager->hideElement("btnStop");
	return 0;
}

void onClickRandomize()
{
	if (gameBoard)
		gameBoard->createBoard();
}

void onClickSolve()
{
	if (testTimer)
	{
		testTimer->start();	
		guiManager->hideElement("btnSolve");
		guiManager->hideElement("btnRandomize");
		guiManager->showElement("btnStop");
	}
}

void onClickStop()
{
	if (testTimer)
	{
		testTimer->stop();
		testTimer->reset();
		guiManager->hideElement("btnStop");
		guiManager->showElement("btnSolve");
		guiManager->showElement("btnRandomize");
	}
}

void drawRandomize(GLint xpos, GLint ypos, GLint w, GLint h)
{
	//Draw the 'Randomize' die
	//Black outline
	glColor3f(0.0f, 0.0f, 0.0f);
	RicochetRobots::Primitives::drawSquare(xpos, ypos, w, h);
	
	//White fill
	glColor3f(1.0f, 1.0f, 1.0f);
	RicochetRobots::Primitives::drawSquare(xpos+1, ypos+1, w-2, h-2);
	
	//Black dice dots
	glColor3f(0.0f, 0.0f, 0.0f);
	RicochetRobots::Primitives::drawCircle(xpos + (w/4  ),  ypos + (h/4  ),  3, 12);
	RicochetRobots::Primitives::drawCircle(xpos + (w*3/4),  ypos + (h/4  ),  3, 12);
	RicochetRobots::Primitives::drawCircle(xpos + (w/4  ),  ypos + (h/2  ),  3, 12);
	RicochetRobots::Primitives::drawCircle(xpos + (w*3/4),  ypos + (h/2  ),  3, 12);
	RicochetRobots::Primitives::drawCircle(xpos + (w/4  ),  ypos + (h*3/4),  3, 12);
	RicochetRobots::Primitives::drawCircle(xpos + (w*3/4),  ypos + (h*3/4),  3, 12);
}

void drawSolve(GLint xpos, GLint ypos, GLint w, GLint h)
{
	//Draw the 'Solve' arrow
	glColor3f(0.0f, 1.0f, 0.0f);
	RicochetRobots::Primitives::drawTriangle(xpos, ypos, xpos + w, ypos + (h/2), xpos, ypos + h);
}

void drawStop(GLint xpos, GLint ypos, GLint w, GLint h)
{
	//Draw the 'Stop' octagon
	glColor3f(1.0f, 0.0f, 0.0f);
	RicochetRobots::Primitives::drawOctagon(xpos, ypos, w, h);
}

void handleInput()
{
	SDL_Event m_eventInput;
	while (SDL_PollEvent(&m_eventInput))
	{
		switch (m_eventInput.type)
		{
			case SDL_VIDEORESIZE:
				SCREENWIDTH = m_eventInput.resize.w;
				SCREENHEIGHT = m_eventInput.resize.h;

				glMatrixMode( GL_PROJECTION );
				glLoadIdentity();
				glOrtho(0.0, SCREENWIDTH, SCREENHEIGHT, 0.0,-1.0,1.0);

				glMatrixMode(GL_MODELVIEW);
				glViewport(0,0,SCREENWIDTH, SCREENHEIGHT);
			break;			
		
			case SDL_QUIT:
				hasQuit = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (m_eventInput.button.button == SDL_BUTTON_LEFT)
					guiManager->handleMouse(m_eventInput.button.x, m_eventInput.button.y, true);
				break;
		}
		
	}
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	//Draws the current board
	gameBoard->draw();

	//Draws the gui
	guiManager->draw();
		
	//Draw the countdown clock
	glColor3f(0.0f, 1.0f, 0.0f);
	GLNumbers::drawTime( SCREENWIDTH - 144, SCREENHEIGHT - 32, 12, 28, testTimer->getTicks() );
	
	SDL_GL_SwapBuffers();
}
