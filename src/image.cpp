#include "image.h"
#include <fstream>
#include <iostream>
#include <ncurses.h>

using namespace std;

Image::Image(string imagePath) : IDrawable(), m_width(0), m_height(0)
{
    fstream imageFile;

    try
    {
        imageFile.open(imagePath, ios::in);

        if (imageFile.is_open())
        {
            string line;
            while (getline(imageFile, line))
            {
                m_image.push_back(line);

                if (line.size() > m_width)
                {
                    m_width = line.size();
                }
            }
        }
        else
        {
            m_image.push_back(string("| | | - - - - this img. faild to load - - - - | | |"));
        }
    }
    catch (const fstream::failure& error)
    {
        cerr << error.what() << endl;
        m_image.push_back(string("| | | - - - - this img. faild to load - - - - | | |"));
    }

    m_height = m_image.size();
}

Image::~Image()
{
}

void Image::draw(const IGraphicsEngine* engine)
{
    int vertical_offset{0};

    for (const string& s : m_image)
    {
        engine->draw(s, m_vertical_position + vertical_offset, m_horizontal_position, Color::white, Color::black);
        vertical_offset++;
    }
}
