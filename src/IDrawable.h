#ifndef IDRAWABLE_H
#define IDRAWABLE_H

class Window;

class IDrawable {
    public:
        IDrawable();
        virtual ~IDrawable();
        virtual void draw() = 0;
        virtual void update() = 0;
        virtual void notify(int ch) = 0;

        virtual bool isVisible() = 0;
        virtual bool isUpdatable() = 0;
        virtual bool isNotifiable() = 0;

        void setPosition(unsigned int vertical, unsigned int horizontal);

        virtual int getResult();

        void setOwner(Window * owner);

    protected:
        Window * m_owner;
        unsigned int m_vertical_position;
        unsigned int m_horizontal_position;
};

#endif