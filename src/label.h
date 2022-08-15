#ifndef LABEL_H
#define LABEL_H

#include "IDrawable.h"
#include <string>

/*!
@brief Simple text label drawn on the screen
*/
class Label : public IDrawable
{
  public:
    /*!
        @brief Constructor
        @param labelString text of the label
    */
    Label(std::string labelString);

    /*!
        @brief Constructor
        @param labelString text of the label
        @param fontColor text color
    */
    Label(std::string labelString, Color fontColor);

    /*!
        @brief Constructor
        @param labelString text of the label
        @param fontColor text color
        @param backgroundColor background color
    */
    Label(std::string labelString, Color fontColor, Color backgroundColor);

    ~Label();

    void draw(const IGraphicsEngine& engine) override;
    bool isVisible() override
    {
        return true;
    };

    void update() override{};
    bool isUpdatable() override
    {
        return false;
    };

    void notify(int ch) override{};
    bool isNotifiable() override
    {
        return false;
    };

  private:
    std::string m_labelString;
    Color m_fontColor;
    Color m_backgroundColor;
};

#endif
