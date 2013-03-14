#include "GUI.hpp"

namespace GUI
{
	void GUIManager::addButton(std::string elemName, int xpos, int ypos, int w, int h, void (*onClick)(), void (*onDraw)(int xpos, int ypos, int w, int h) )
	{
		bool isDuplicate = false;
		for (std::list<GUIElement*>::iterator	iter  = m_elements.begin();
							iter != m_elements.end();
							++iter)
		{
			if ( (*iter)->getName().compare(elemName) == 0)
			{
				isDuplicate = true;
				break;
			}

		}

		if (!isDuplicate)
		{
			GUIButton* btn = new GUIButton(elemName, xpos, ypos, w, h, onClick, onDraw);
			m_elements.push_front(btn);
		}
	}

	void GUIManager::moveElement(std::string elemName, int xpos, int ypos)
	{
		for (std::list<GUIElement*>::iterator	iter  = m_elements.begin();
							iter != m_elements.end();
							++iter)
		{
			if ( (*iter)->getName().compare(elemName) == 0)
			{
				(*iter)->setXPos(xpos);
				(*iter)->setYpos(ypos);
			}
		}
	}	
	void GUIManager::sizeElement(std::string elemName, int w, int h)
	{
		for (std::list<GUIElement*>::iterator	iter  = m_elements.begin();
							iter != m_elements.end();
							++iter)
		{
			if ((*iter)->getName().compare(elemName) == 0)
			{
				(*iter)->setW(w);
				(*iter)->setH(h);
			}
		}
	}	
	void GUIManager::removeElement(std::string elemName)
	{
		for (std::list<GUIElement*>::iterator	iter  = m_elements.begin();
							iter != m_elements.end();
							++iter)
		{
			if ((*iter)->getName().compare(elemName) == 0)
			{
				delete *iter;
				m_elements.erase(iter);		
				break;
			}
		}
		
	}
	void GUIManager::handleMouse(int mousex, int mousey, bool mousedown)
	{
		for (std::list<GUIElement*>::iterator	iter  = m_elements.begin();
							iter != m_elements.end();
							++iter)
		{
			if ( (*iter)->getIsActive() )
				(*iter)->update(mousex, mousey, mousedown);
		}
	}
	
	void GUIManager::draw()
	{
		for (std::list<GUIElement*>::iterator	iter  = m_elements.begin();
							iter != m_elements.end();
							++iter)
		{
			if ( (*iter)->getIsActive() )
				(*iter)->draw();
		}
	}	

	void GUIManager::hideElement(std::string elemName)
	{
		for (std::list<GUIElement*>::iterator	iter  = m_elements.begin();
							iter != m_elements.end();
							++iter)
		{
			if ((*iter)->getName().compare(elemName) == 0)
			{
				(*iter)->hide();
				break;
			}
		}
	}
	void GUIManager::showElement(std::string elemName)
	{
		for (std::list<GUIElement*>::iterator	iter  = m_elements.begin();
							iter != m_elements.end();
							++iter)
		{
			if ((*iter)->getName().compare(elemName) == 0)
			{
				(*iter)->show();
				break;
			}
		}
	}




	GUIManager::~GUIManager()
	{	
		for (std::list<GUIElement*>::iterator	iter  = m_elements.begin();
							iter != m_elements.end();
							iter  = m_elements.erase(iter) )
			delete *iter;
	}
	
	GUIButton::GUIButton( std::string elemName, int xpos, int ypos, int w, int h, void (*onClick)(), void (*onDraw)(int xpos, int ypos, int w, int h) ) 
	{
		m_name = elemName;
	 	m_xpos = xpos;
		m_ypos = ypos;
		m_w = w;
		m_h = h;
		m_onClick = onClick;
		m_onDraw = onDraw;
		m_isActive = true;
	}
	void GUIButton::update(int mousex, int mousey, bool mousedown)
	{
		if ( testPoint(mousex, mousey) && mousedown)
			m_onClick();
	}
	void GUIButton::draw()
	{
		m_onDraw(m_xpos, m_ypos, m_w, m_h);
	}

}
