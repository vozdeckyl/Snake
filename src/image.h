#ifndef IMAGE_H
#define IMAGE_H

#include "IDrawable.h"
#include <vector>
#include <string>

class Image : public IDrawable {
    public:
        Image(std::string imagePath);
        ~Image();

        void draw() override;
        bool isVisible() override {return true;}

        void update() override {};
        bool isUpdatable() override {return false;}

        void notify(int ch) override {};
        bool isNotifiable() override {return false;}

        int getWidth();
        int getHeight();

    private:
        std::vector<std::string> m_image;
        int m_width;
        int m_height;
};

#endif