#include "imgui_presenter.hpp"
#include <iostream>

namespace sabre::pilot
{
    ImGuiPresenter::ImGuiPresenter(Simulator &simulator) : Presenter(simulator)
    {
    }

    void ImGuiPresenter::start()
    {
        std::cout << "ImGuiPresenter started!" << std::endl;
    }
} // namespace sabre::pilot