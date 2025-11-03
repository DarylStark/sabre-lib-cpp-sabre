#pragma once

#include "../presenter.hpp"

namespace sabre::pilot
{
    class ImGuiPresenter : public Presenter
    {
    public:
        ImGuiPresenter(Simulator &simulator);
        void start() override;
    };
} // namespace sabre::pilot