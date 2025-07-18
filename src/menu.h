#ifndef MENU_H
#define MENU_H

#include "IDrawable.h"
#include <atomic>
#include <string>
#include <vector>

/*!
@brief Vertical menu drawn on the screen

Items can be selected using up and down keys. It inherits from the class IDrawable.

The class is drawable, notifiable(up/keys to change the menu selection), but not updatable.
*/
class Menu : public IDrawable
{
  public:
    /*!
    @brief Constructor
    @param entries Vector of strings defining the different menu items
    */
    Menu(std::vector<std::string> entries);

    /*!
    @brief Defualt constructor - creates an empty menu.
    */
    Menu();

    /*!
    @brief Copy constructor
    */
    Menu(const Menu& other);

    /*!
    @brief Destructor
    */
    ~Menu();

    void draw(const IGraphicsEngine* engine) override;
    bool isVisible() override
    {
        return true;
    }

    void update() override {};
    bool isUpdatable() override
    {
        return false;
    }

    void notify(int ch) override;
    bool isNotifiable() override
    {
        return true;
    }

    int getResult() override
    {
        return m_selector;
    }

    /*!
    @brief Adds an item into the menu.

    @param entryText item's text
    */
    void addEntry(std::string entryText);

    /*!
    @brief Moves the selector up
    */
    void moveSelectorUp();

    /*!
    @brief Moves the selector down
    */
    void moveSelectorDown();

    /*!
    @brief Returns the menu items as a vector of strings.
    */
    std::vector<std::string> getEntries() const;

  private:
    std::vector<std::string> m_entries;
    std::atomic<int> m_selector;
};

#endif
