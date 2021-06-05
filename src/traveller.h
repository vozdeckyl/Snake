#ifndef TRAVELLER_H
#define TRAVELLER_H

#include "IDrawable.h"

class Traveller : public IDrawable {
    public:
        Traveller(double verticalVelocity, double horizontalVelocity);
        ~Traveller();

        void draw(const IGraphicsEngine * engine) override;
        bool isVisible() override {return true;};

        void update() override;
        bool isUpdatable() override {return true;};

        void notify(int ch) override;
        bool isNotifiable() override {return true;};

    private:
        double m_verticalFractionPosition;
        double m_horizontalFractionPosition;
        double m_verticalVelocity;
        double m_horizontalVelocity;
};

#endif