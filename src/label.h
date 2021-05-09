#ifndef LABEL_H
#define LABEL_H

#include <string>
#include "IDrawable.h"

class Label : public IDrawable {
    public:
        Label(std::string labelString);
        Label(std::string labelString, int fontColor);
        Label(std::string labelString, int fontColor, int backgroundColor);
        ~Label();

        void draw() override;
        bool isVisible() override {return true;};

        void update() override {};
        bool isUpdatable() override {return false;};

        void notify(int ch) override {};
        bool isNotifiable() override {return false;};

    private:
        std::string m_labelString;
        int m_fontColor;
        int m_backgroundColor;
};

#endif