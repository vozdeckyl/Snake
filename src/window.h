#ifndef WINDOW_H
#define WINDOW_H

#include "IGraphicsEngine.h"
#include "objectid.h"
#include <map>
#include <memory>
#include <mutex>

class IDrawable;
class Result;
using namespace std;

/*!
    @brief Represents the window onto which drawable objets are drawn.

    The class holds a list of all drawables and also has a point to the graphics engine which is used for drawing on the
   screen.
*/
class Window
{
  public:
    /*!
        @brief Contructor
        @param engine Graphics engine used for drawing objects on the screen
    */
    Window(IGraphicsEngine* engine);
    ~Window();

    /*!
        @brief Adds a drawable element to the screen, assigns it an ID and returs its ID
        @param element pointer to the drawable element to be added
        @param yPosition vertical position of the element
        @param xPosition horizontal position of the element
    */
    ObjectID addElement(IDrawable* element, int yPosition, int xPosition);

    /*!
        @brief Function that needs to be run to launch the screen. The function returns the %result of the window and
       when user exits.
    */
    Result run();

    /*!
        @brief Used to stop the window. Used mainly by the drawable objects.
    */
    void kill();

    /*!
        @brief If called before Run, the window is killed by pressing key Q.
    */
    void enableKillByKeyQ();

    /*!
        @brief Returns the width of the screen
    */
    int getWidth();

    /*!
        @brief Returns the height of the screen
    */
    int getHeight();

  private:
    /*!
        @brief This function is run on a separate thread. It iterates through the drawable objects and calls draw
       functions on them. It also takes care of the user input.
    */
    void graphicsLoop();

    /*!
        @brief This function is run on a separate thread. It iterates through the drawables, notifies them and sleeps
       for a short interval (1ms).
    */
    void updateLoop();

    /*!
        @brief Getter for m_exit
    */
    bool exit();

  private:
    map<ObjectID, unique_ptr<IDrawable>> m_elements;
    ObjectID m_nextObjectID;
    int m_numOfRows;
    int m_numOfColumns;
    mutex m_mutex_exit;
    bool m_exit;
    bool m_killByKeyQ;
    unique_ptr<IGraphicsEngine> m_engine;
};

#endif
