#ifndef LABEL_H
#define LABEL_H

#include <string>
#include "IDrawable.h"

class Label : public IDrawable {
    public:
        Label(std::string labelString);
        Label(std::string labelString, Color fontColor);
        Label(std::string labelString, Color fontColor, Color backgroundColor);
        ~Label();

        void draw(const IGraphicsEngine * engine) override;
        bool isVisible() override {return true;};

        void update() override {};
        bool isUpdatable() override {return false;};

        void notify(int ch) override {};
        bool isNotifiable() override {return false;};

    private:
        std::string m_labelString;
        Color m_fontColor;
        Color m_backgroundColor;
};

#endif