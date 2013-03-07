#ifndef RS_PRIMITIVES
#define RS_PRIMITIVES

#include "sdl_opengl.h"
#include <math.h>
//SDL_OPENGL draw primitives
namespace RicochetRobots
{
	namespace Primitives
	{
		void drawSquare(int x, int y, int w, int h)
		{
			glBegin(GL_QUADS);
				glVertex2i(x	, y    );
				glVertex2i(x + w, y    );
				glVertex2i(x + w, y + h);
				glVertex2i(x    , y + h);
			glEnd();

		}
		
		void drawCircle(int cx, int cy, int r, int nVertices)
		{
			float theta = (2.0f * 3.14159f) / float(nVertices); // 2PI / numVertices
			float tangent = tan(theta); //Distance moved tangential to the circle
			float radiant = cosf(theta); //Distance moved toward the center of the circle

			float x = (float)r;
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

		void drawDiamond(int x, int y, int w, int h)
		{
			glBegin(GL_QUADS);
				glVertex2i(x + w/2 , y       );
				glVertex2i(x + w   , y + h/2 );
				glVertex2i(x + w/2 , y + h   );
				glVertex2i(x       , y + h/2 );
			glEnd();
		}

		void drawTriangle(int x, int y, int b, int h)
		{
			glBegin(GL_TRIANGLES);
				glVertex2i(x + b/2	, y		);
				glVertex2i(x + b	, y + h	);
				glVertex2i(x		, y + h	);
			glEnd();
		}

		void drawForwardSlash(int x, int y, int w, int h)
		{
			glBegin(GL_QUADS);
				glVertex2i(x + (int)(w * 0.75)	, y		);
				glVertex2i(x + w				, y		);
				glVertex2i(x + (int)(w * 0.25)	, y + h	);
				glVertex2i(x					, y + h	);
			glEnd();
		}

		void drawBackwardSlash(int x, int y, int w, int h)
		{
			glBegin(GL_QUADS);
				glVertex2i(x					, y		);
				glVertex2i(x + (int)(w * 0.25)	, y		);
				glVertex2i(x + w				, y + h	);
				glVertex2i(x + (int)(w * 0.75)	, y + h	);
			glEnd();
		}
	}
}

#endif //RS_PRIMITIVES