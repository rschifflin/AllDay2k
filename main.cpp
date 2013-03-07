//Simple 2D 'Snake' game using the component model
#include "sdl.h"
#include "sdl_opengl.h"
#include "IL/il.h"
#include "IL/ilu.h"

//#include "SimpleEngine.h"
#include "Board.h"

int init();
int SDLInit();
int OpenGLInit();
int DevILInit();

void handleInput();
void draw();

int SCREENWIDTH = 512;
int SCREENHEIGHT = 512;

RicochetRobots::Board* gameBoard = new RicochetRobots::Board();
bool hasQuit = false;

int main(int argc, char** argv)
{
	if (init())
		return 0;

	while (!hasQuit)
	{
		handleInput();
		draw();
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
	if (DevILInit())
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

	SDL_putenv("SDL_VIDEO_CENTERED=center");
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

	//GLubyte colorFade4[3] = {193, 203, 217};
	glClearColor((GLclampf)1, (GLclampf)1, (GLclampf)1, 1.0);
	//glEnable( GL_TEXTURE_2D );
	//glEnable( GL_BLEND );
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		//std::cout << "Error initializing OpenGL" << std::endl;
		return 1;
	}
	
	return 0;
}

int DevILInit()
{
	ilInit();
	ilClearColor(0xFF,0xFF,0xFF,0x00);
	ILenum ilError = ilGetError();
	if (ilError != IL_NO_ERROR)
	{
		//std::cout << "Error initializing DevIL" << std::endl;
		return 1;
	}

	return 0;
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
		}
	}
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gameBoard->draw();

	SDL_GL_SwapBuffers();
}