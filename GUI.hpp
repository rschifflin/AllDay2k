/*
	GUI.hpp
	This program provides various objects in the GUI namespace useful for manipulating a graphic interface

	GUIManager
		Object that holds all the GUI elements. Takes input from user, searches its GUI elements and fires the appropriate events.

	Button
		Button objects are rectangles that allow functions to be 'hooked in' to mouse press events.
		Button objects take a function pointer to a MousePress event, and a function pointer to a Draw event.

*/
#ifndef RS_GUI
#define RS_GUI

#include <list>
#include <string>

namespace GUI
{
	class GUIElement
	{
	protected:
		int m_xpos;
		int m_ypos;
		int m_w;
		int m_h;
		std::string m_name;
		bool m_isActive;

	public:
		std::string getName() const {return m_name;}
		int getXPos() const {return m_xpos;}
		int getYPos() const {return m_ypos;}
		int getW() const {return m_w;}
		int getH() const {return m_h;}
		bool getIsActive() const {return m_isActive;}
		void setXPos(int xpos) {m_xpos = xpos;}
		void setYpos(int ypos) {m_ypos = ypos;}
		void setW(int w) {m_w = w;}
		void setH(int h) {m_h = h;}
		void hide() { m_isActive = false; }
		void show() { m_isActive = true; }		

		bool testPoint(int px, int py) {return (px >= m_xpos && px < m_xpos + m_w && py >= m_ypos && py < m_ypos + m_h); }
		
		virtual void update(int mousex, int mousey, bool mousedown) = 0;
		virtual void draw() = 0;
		virtual ~GUIElement(){}
	};

	class GUIManager
	{
		std::list<GUIElement*> m_elements;	
	public:	
		void addButton(std::string elemName, int xpos, int ypos, int w, int h, void (*onClick)(), void (*onDraw)(int xpos, int ypos, int w, int h) );
		void moveElement(std::string elemName, int xpos, int ypos);
		void sizeElement(std::string elemName, int w, int h);
		void removeElement(std::string elemName);
		void hideElement(std::string elemName);
		void showElement(std::string elemName);
		void handleMouse(int mousex, int mousey, bool mousedown);
		void draw();
		~GUIManager();
	};

	class GUIButton: public GUIElement
	{
		void (*m_onClick)();
		void (*m_onDraw)(int xpos, int ypos, int w, int h);
		
	public:
		GUIButton(std::string elemName, int xpos, int ypos, int w, int h, void (*onClick)(), void (*onDraw)(int xpos, int ypos, int w, int h) ); 
		void update(int mousex, int mousey, bool mousedown);
		void draw();
	};
}
#endif //RS_GUI

