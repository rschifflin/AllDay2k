#ifndef RS_PRIMITIVES
#define RS_PRIMITIVES

#include "SDL/SDL_opengl.h"
#include <math.h>

//SDL_OPENGL draw primitives
namespace RicochetRobots
{
	namespace Primitives
	{	
		inline void drawSquare(int x, int y, int w, int h)
		{
			glBegin(GL_QUADS);
				glVertex2i(x	, y    );
				glVertex2i(x + w, y    );
				glVertex2i(x + w, y + h);
				glVertex2i(x    , y + h);
			glEnd();

		}
		
		inline void drawCircle(int cx, int cy, int r, int nVertices)
		{
			float theta = (2.0f * 3.14159f) / float(nVertices); // 2PI / numVertices
			float tangent = tanf(theta); //Distance moved tangential to the circle
			float radiant = cosf(theta); //Distance moved toward the center of the circle

			float x = static_cast<float>(r);
			float y = 0.0;
			glBegin(GL_POLYGON);
				for (int i = 0; i < nVertices; i++)
				{
					glVertex2f(cx + x, cy + y);

					float tx = -y;
					float ty =  x;

					x += (tx * tangent); //Move tangent to circle
					y += (ty * tangent); //Move tangent to circle

					x *= radiant; //Move radially toward circle
					y *= radiant; //Move radially toward circle
				}
			glEnd();

		}

		inline void drawRing(int cx, int cy, int r, int nVertices, int thickness)
		{		
			glEnable(GL_STENCIL_TEST);
				//Write the inner circle to the stencil buffer
				glColorMask(0,0,0,0);
				glStencilFunc(GL_ALWAYS, 1, 1);
				glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
				drawCircle(cx, cy, r - thickness, nVertices);

				//Use the stencil buffer to block out the inner circle
				glColorMask(1,1,1,1);
				glStencilFunc(GL_NOTEQUAL, 1, 1);
				glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
				drawCircle(cx, cy, r, nVertices);	
			glDisable(GL_STENCIL_TEST);
		}
	

		inline void drawDiamond(int x, int y, int w, int h)
		{
			glBegin(GL_QUADS);
				glVertex2i(x + w/2 , y       );
				glVertex2i(x + w   , y + h/2 );
				glVertex2i(x + w/2 , y + h   );
				glVertex2i(x       , y + h/2 );
			glEnd();
		}

		inline void drawTriangle(int x, int y, int b, int h)
		{
			glBegin(GL_TRIANGLES);
				glVertex2i(x + b/2 , y	   );
				glVertex2i(x + b   , y + h );
				glVertex2i(x	   , y + h );
			glEnd();
		}
		
		inline void drawTriangle(int ax, int ay, int bx, int by, int cx, int cy)
		{
			glBegin(GL_TRIANGLES);
				glVertex2i(ax	, ay	);
				glVertex2i(bx	, by	);
				glVertex2i(cx	, cy	);
			glEnd();			
		}

		inline void drawForwardSlash(int x, int y, int w, int h)
		{
			glBegin(GL_QUADS);
				glVertex2i(x + (w * 3/4)	, y	);
				glVertex2i(x + w		, y	);
				glVertex2i(x + (w * 1/4)	, y + h	);
				glVertex2i(x			, y + h	);
			glEnd();
		}

		inline void drawBackwardSlash(int x, int y, int w, int h)
		{
			glBegin(GL_QUADS);
				glVertex2i(x			, y	);
				glVertex2i(x + (w * 1/4)	, y	);
				glVertex2i(x + w		, y + h	);
				glVertex2i(x + (w * 3/4)	, y + h	);
			glEnd();
		}
		
		inline void drawOctagon(int x, int y, int w, int h)
		{
			glBegin(GL_POLYGON);
				glVertex2i(x + static_cast<int>(w * 0.293)	, y					);
				glVertex2i(x + static_cast<int>(w * 0.707)	, y					);
				glVertex2i(x + w				, y + static_cast<int>(h * 0.293)	);
				glVertex2i(x + w				, y + static_cast<int>(h * 0.707)	);
				glVertex2i(x + static_cast<int>(w * 0.707)	, y + h					);
				glVertex2i(x + static_cast<int>(w * 0.293)	, y + h					);
				glVertex2i(x 					, y + static_cast<int>(h * 0.707)	);
				glVertex2i(x 					, y + static_cast<int>(h * 0.293)	);
			glEnd();
		}
		
	}
}

#endif //RS_PRIMITIVES
