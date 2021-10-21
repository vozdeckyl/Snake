#ifndef MOCKSCREEN_H
#define MOCKSCREEN_H

#include <vector>
#include "IGraphicsEngine.h"

class mockScreen : public IGraphicsEngine {
public:
    mockScreen(int height, int width) :
	m_isInitialized(false),
	m_isScreenPrepared(false),
	m_height(height),
	m_width(width),
	m_refreshed(false),
	m_screenEnded(false),
	m_waitForMS(0)
    {
	m_screen = new char[height*width];
	for(int i = 0; i<m_height*m_height; i++)
	{
	    m_screen[i] = ' ';
	}
    }

    ~mockScreen()
    {
	delete[] m_screen;
    }

    void init() override
    {
	m_isInitialized = true;
    }

    void prepareScreen() override
    {
	m_isScreenPrepared = true;
    }

    void draw(std::string text, int y, int x, Color textColor, Color backgroundColor) const override
    {
	char * textString = const_cast<char*>(text.c_str());
	int length = text.size();
	
	for(int i=0; i<length; i++)
	{
	    drawChar(textString[i],y,x+i);
	}
    }

    void drawChar(char ch, int y, int x) const
    {
	m_screen[y*m_height+x] = ch;
    }
        
    void refreshScreen() override
    {
	m_refreshed = true;
    }
        
    void clearScreen() override
    {
	for(int i = 0; i<m_height*m_height; i++)
	{
	    m_screen[i] = ' ';
	}
    }
    
    void endScreen()
    {
	m_screenEnded = true;
    }

    int numberOfRows()
    {
	return m_height;
    }
    
    int numberOfColumns()
    {
	return m_width;
    }
    
    void wait(int timeMS)
    {
	m_waitForMS = timeMS;
    }

    int input()
    {
	if(m_buffer.size() == 0)
	{
	    return -1;
	}
	else
	{
	    char output = *(m_buffer.end()); 
	    m_buffer.pop_back();
	    return (int) output;            
	}
    }

    void addToBuffer(char ch)
    {
	m_buffer.emplace_back(ch);
    }
    
    bool testScreen(char ch, int y, int x)
    {
	return ch == m_screen[y*m_height+x];
    }
    
private:
    bool m_isInitialized;
    bool m_isScreenPrepared;
    char * m_screen;
    int m_height;
    int m_width;
    bool m_refreshed;
    bool m_screenEnded;
    int m_waitForMS;
    std::vector<char> m_buffer;
};

#endif
