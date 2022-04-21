#ifndef IMAGE_H
#define IMAGE_H

#include "IDrawable.h"
#include <string>
#include <vector>

/*!
@brief Character based image

The image is loaded from a text file whose path is submitted to the constructor.
*/
class Image : public IDrawable
{
  public:
    /*!
        @brief Contructor.
        @param imagePath path to the textfile with the image
    */
    Image(std::string imagePath);
    ~Image();

    void draw(const IGraphicsEngine* engine) override;
    bool isVisible() override
    {
        return true;
    }

    void update() override{};
    bool isUpdatable() override
    {
        return false;
    }

    void notify(int ch) override{};
    bool isNotifiable() override
    {
        return false;
    }

    /*!
        @brief Returns the width of the image.
    */
    int getWidth();

    /*!
        @brief Returns the height of the image.
    */
    int getHeight();

  private:
    std::vector<std::string> m_image;
    int m_width;
    int m_height;
};

#endif