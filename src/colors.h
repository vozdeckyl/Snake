#ifndef COLORS_H
#define COLORS_H

/*!
    @brief Static class for setting colours
*/
class Colors
{
  public:
    /*!
        @brief This function must be called before the class can be used
    */
    static void generateColors();

    /*!
        @brief Select a color
    */
    static void activateColor(int fontColor, int backgroundColor);

    /*!
        @brief Deactiavte the selected color - i.e. activate the default white font and black background
    */
    static void deactivateColor();
};

#endif