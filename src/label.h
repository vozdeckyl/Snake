#ifndef LABEL_H
#define LABEL_H

#include <string>
#include "IDrawable.h"

class Label : public IDrawable {
    public:
        Label(std::string labelString);
        ~Label();

        void draw() override;
        bool isVisible() override {return true;};

        void update() override {};
        bool isUpdatable() override {return false;};

        void notify(int ch) override {};
        bool isNotifiable() override {return false;};

    private:
        std::string m_labelString;
};

#endif