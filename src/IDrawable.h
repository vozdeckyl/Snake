#ifndef IDRAWABLE_H
#define IDRAWABLE_H

#include "IGraphicsEngine.h"

class Window;

/*! 
@brief Interface for all drawable objects.

Any class that represents an graphical object on the sreen must inherit from this interface.
*/
class IDrawable {
    public:
        IDrawable();
        virtual ~IDrawable();

        /*!
            @brief Function that is called to draw the object
            @param engine Engine that is used to draw the object
        */
        virtual void draw(const IGraphicsEngine * engine) = 0;

        /*!
            @brief This function is called bin regular intervals to update the internal state of the object.
        */
        virtual void update() = 0;

        /*!
            @brief This function is called when a key is pressed.

            @param ch Character/key that was pressed.
        */
        virtual void notify(int ch) = 0;

        /*!
            @brief The draw() function is only called when this returns true.
        */
        virtual bool isVisible() = 0;

        /*!
            @brief The update() function is only called when this returns true.
        */
        virtual bool isUpdatable() = 0;

        /*!
            @brief The notify() function is only called when this returns true.
        */
        virtual bool isNotifiable() = 0;

        /*!
            @brief Sets the position of the drawable object.
            @param vertical vertical position of the top left corner
            @param horizontal horizontal position of the top left corner
        */
        void setPosition(int vertical, int horizontal);

        /*!
            @brief Returns the result of the object. For example for a menu it is the position of the selector. Objects without result return -1.
        */
        virtual int getResult();

        /*!
            @brief Sets the owner of the object.
            @param owner window that owns this object 
        */
        void setOwner(Window * owner);

    protected:
        Window * m_owner;
        int m_vertical_position;
        int m_horizontal_position;
};

#endif