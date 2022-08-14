#ifndef ALLEGROENGINE_H
#define ALLEGROENGINE_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include "IGraphicsEngine.h"

class AllegroEngine : public IGraphicsEngine
{
public:

    AllegroEngine(int h, int w)
    {
        m_width = w;
        m_height = h;
    }

    ~AllegroEngine()
    {
        if(!m_screenEnded)
        {
            endScreen();
        }
    }

    void init() override
    {
        if(!m_screenCreated)
        {
	    m_screenCreated = true;
	    al_init();
	    al_install_keyboard();
	    al_init_font_addon();
	    al_init_ttf_addon();
	    al_init_primitives_addon();

	    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	    m_display = al_create_display(m_height*10, m_width*10);
	    
	    if (!m_display)
	    {
		throw std::runtime_error("Unable to create display");
	    }
	    
	    al_set_window_title(m_display, "Shell Snake");
		
	    m_events = al_create_event_queue();
            al_register_event_source(m_events, al_get_display_event_source(m_display));
            al_register_event_source(m_events, al_get_keyboard_event_source());

            m_font = al_load_ttf_font("consola.ttf", 18, ALLEGRO_TTF_NO_KERNING);

	    al_set_target_backbuffer(m_display);
	    al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
	}

    }
    
    void prepareScreen() override
    {
        clearScreen();
    }

    void draw(std::string text, int y, int x, Color textColor, Color backgroundColor) const override
    {
        //al_set_target_backbuffer(m_display);
        //al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
        int n{0};
        
        for(const char & ch : text)
        {
            al_draw_filled_rectangle(10.0f*(x+n), 18.0f*y, 10.0f*(x+n+1), 18.0f*(y+1), get_al_color(backgroundColor));
            al_draw_text(m_font, get_al_color(textColor), 10.0f*(x+n), 18.0f*y, ALLEGRO_ALIGN_LEFT, &ch);
            n++;
        }
        //al_flip_display();
    }

    void refreshScreen() override
    {
        al_flip_display();
    }

    void clearScreen() override
    {
        al_clear_to_color(al_map_rgb(0, 0, 0));
    }

    void endScreen() override
    {
        al_destroy_display(m_display);
        al_destroy_event_queue(m_events);
        al_destroy_font(m_font);
        al_shutdown_primitives_addon();
        m_screenEnded = true;
    }

    int numberOfRows() override
    {
        return m_height;
    }

    int numberOfColumns() override
    {
        return m_width;
    }

    void wait(int timeMS) override
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeMS));
    }

    int input()
    {
        if(!al_is_event_queue_empty(m_events))
        {
            if(al_get_next_event(m_events, &m_event))
            {	
                if(m_event.type == ALLEGRO_EVENT_KEY_DOWN)
                {
                    int key = m_event.keyboard.keycode;

                    if(key == ALLEGRO_KEY_UP)
                    {
                        return 259;
                    }
                    else if (key == ALLEGRO_KEY_DOWN) 
                    {
                        return 258;
                    }
		    else if(key == ALLEGRO_KEY_LEFT)
		    {
			return 260;
		    }
		    else if(key == ALLEGRO_KEY_RIGHT)
		    {
			return 261;
		    }
                    else if (key == ALLEGRO_KEY_Q)
                    {
                        return 'q';
                    }
                    else if (key == ALLEGRO_KEY_ENTER)
                    {
                        return 10;
                    }
                    else
                    {
                        return key;
                    }
                }
            }
        }

        return -1;
    }


private:

    ALLEGRO_COLOR get_al_color(Color c) const
    {
        ALLEGRO_COLOR result;
        switch (c)
        {
            case Color::black:
                result = al_map_rgb(0,0,0);
                break;
            case Color::blue:
                result = al_map_rgb(0,0,255);
                break;
            case Color::green:
                result = al_map_rgb(0,255,0);
                break;
            case Color::cyan:
                result = al_map_rgb(0, 255, 255);
                break;
            case Color::red:
                result = al_map_rgb(255,0,0);
                break;
            case Color::magenta:
                result = al_map_rgb(255, 0, 255);
                break;
            case Color::white:
                result = al_map_rgb(255,255,255);
                break;
            case Color::yellow:
                result = al_map_rgb(255,255,0);
                break;
            default:
                throw std::runtime_error("Unimplemented color in AllegroEngine::get_al_color()");
                break;
        }
        return result;
    }

    private:
    int m_width = 500;
    int m_height = 500;

    ALLEGRO_DISPLAY * m_display;
    ALLEGRO_EVENT m_event;
    ALLEGRO_EVENT_QUEUE * m_events;
    ALLEGRO_FONT * m_font;

    bool m_screenEnded = false;
    bool m_screenCreated = false;
};

#endif
