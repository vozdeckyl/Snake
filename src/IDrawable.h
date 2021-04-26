#ifndef IDRAWABLE_H
#define IDRAWABLE_H

class IDrawable {
    public:
        IDrawable() : m_vertical_position(0), m_horizontal_position(0) {};
        virtual ~IDrawable() {};
        virtual void draw() = 0;
        virtual void update() = 0;
        virtual void notify(int ch) = 0;

        virtual bool isVisible() = 0;
        virtual bool isUpdatable() = 0;
        virtual bool isNotifiable() = 0;

        virtual void setPosition(unsigned int vertical, unsigned int horizontal)
        {
            m_vertical_position=vertical;
            m_horizontal_position=horizontal;
        }

        virtual int getResult() {return -1;}

    protected:
        unsigned int m_vertical_position;
        unsigned int m_horizontal_position;
};

#endif