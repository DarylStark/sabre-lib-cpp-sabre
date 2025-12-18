#pragma once

#include "../simulator/simulator.hpp"

namespace sabre::Pilot
{
    class Presenter
    {
    protected:
        Simulator &_simulator;

    public:
        Presenter(Simulator &simulator);
        virtual void start() = 0;
    };
} // namespace sabre::Pilot