#include "imgui_presenter.hpp"
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include <iostream>

namespace sabre::pilot
{
    ImGuiPresenter::ImGuiPresenter(Simulator &simulator) : Presenter(simulator)
    {
    }

    void ImGuiPresenter::_ui_handle_key_events()
    {
        if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl) &&
            ImGui::IsKeyPressed(ImGuiKey_Equal))
            _ui_zoom_in();
        if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl) &&
            ImGui::IsKeyPressed(ImGuiKey_Minus))
            _ui_zoom_out();
        if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl) &&
            ImGui::IsKeyPressed(ImGuiKey_0))
            _ui_set_scale_to_auto();
    }

    void ImGuiPresenter::_ui_main_menu()
    {
        if (ImGui::BeginMainMenuBar())
        {
            _ui_main_menu_file();
            _ui_main_menu_view();
            _ui_main_menu_debug();
            ImGui::EndMainMenuBar();
        }
    }

    void ImGuiPresenter::_ui_main_menu_file()
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit"))
                glfwSetWindowShouldClose(_window, GLFW_TRUE);
            ImGui::EndMenu();
        }
    }

    void ImGuiPresenter::_ui_main_menu_view()
    {
        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::BeginMenu("MCU"))
            {
                for (auto &mcu : _simulator.get_mcu_list())
                    if (ImGui::MenuItem(mcu.first.c_str(), nullptr,
                                        mcu.second.show))
                        mcu.second.show = !mcu.second.show;
                ImGui::EndMenu();
            }
            _ui_main_menu_view_scale();
            ImGui::EndMenu();
        }
    }

    void ImGuiPresenter::_ui_main_menu_view_scale()
    {
        if (ImGui::BeginMenu("Scale"))
        {
            if (ImGui::MenuItem("Auto", "Ctrl + 0", _auto_ui_scale))
                _ui_set_scale_to_auto();
            ImGui::Separator();
            if (ImGui::MenuItem("Zoom in", "Ctrl + =", false,
                                _ui_scale != 5.0f))
                _ui_zoom_in();
            if (ImGui::MenuItem("Zoom out", "Ctrl + -", false,
                                _ui_scale != 1.0f))
                _ui_zoom_out();
            ImGui::Separator();
            for (float scale = 1; scale <= 5; scale += 0.5f)
            {
                std::string label =
                    std::to_string(static_cast<int>(scale * 100)) + "%";
                if (ImGui::MenuItem(label.c_str(), nullptr,
                                    _ui_scale == scale && !_auto_ui_scale))
                    _ui_set_scale(scale);
            }
            ImGui::EndMenu();
        }
    }

    void ImGuiPresenter::_ui_main_menu_debug()
    {
        if (ImGui::BeginMenu("Debug"))
        {
            ImGui::MenuItem("ImGui Demo Window", nullptr, &_show_imgui_demo);
            ImGui::MenuItem("ImGui Metric Window", nullptr,
                            &_show_imgui_metrics);
            ImGui::EndMenu();
        }
    }

    void ImGuiPresenter::_ui_mcu(const std::string &name, SimulatorMCU &sim_mcu)
    {
        if (!sim_mcu.show)
            return;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::Begin(name.c_str(), &sim_mcu.show);

        // Calculate split
        float window_width = ImGui::GetContentRegionAvail().x;
        float window_height = ImGui::GetContentRegionAvail().y;
        float left_width = window_width * 0.7f;
        float right_width = window_width - left_width;

        // Remove spacing between children
        ImGuiStyle &style = ImGui::GetStyle();
        float old_item_spacing_x = style.ItemSpacing.x;
        float old_item_spacing_y = style.ItemSpacing.y;
        float old_window_padding_x = style.WindowPadding.x;
        float old_window_padding_y = style.WindowPadding.y;
        style.ItemSpacing.x = 0.0f;
        style.ItemSpacing.y = 0.0f;
        style.WindowPadding.x = 0.0f;
        style.WindowPadding.y = 0.0f;

        ImGui::BeginChild("LeftPane", ImVec2(left_width, window_height), true);
        for (const auto &[uart_number, uart_data] : sim_mcu.mcu->get_uart_map())
        {
            std::string header_output =
                "UART " + std::to_string(uart_number) + " output";
            if (ImGui::CollapsingHeader(header_output.c_str(),
                                        ImGuiTreeNodeFlags_DefaultOpen))
            {
                std::string child_id =
                    "UARTOutputChild" + std::to_string(uart_number);
                ImGui::BeginChild(child_id.c_str(), ImVec2(0, 250), true,
                                  ImGuiWindowFlags_HorizontalScrollbar);
                ImGui::TextUnformatted(uart_data.output_data.c_str());
                // Auto-scroll to bottom if already at bottom
                if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
                    ImGui::SetScrollHereY(1.0f);
                ImGui::EndChild();
            }

            std::string header_input =
                "UART " + std::to_string(uart_number) + " input :: buffer";
            if (ImGui::CollapsingHeader(header_input.c_str(),
                                        ImGuiTreeNodeFlags_DefaultOpen))
            {
                std::string child_id =
                    "UARTInputChild" + std::to_string(uart_number);
                ImGui::BeginChild(child_id.c_str(), ImVec2(0, 250), true,
                                  ImGuiWindowFlags_HorizontalScrollbar);
                ImGui::TextUnformatted(uart_data.input_buffer.c_str());
                // Auto-scroll to bottom if already at bottom
                if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
                    ImGui::SetScrollHereY(1.0f);
                ImGui::EndChild();
            }

            std::string header_input_consumed =
                "UART " + std::to_string(uart_number) + " input :: consumed";
            if (ImGui::CollapsingHeader(header_input_consumed.c_str(),
                                        ImGuiTreeNodeFlags_DefaultOpen))
            {
                std::string child_id =
                    "UARTInputConsumedChild" + std::to_string(uart_number);
                ImGui::BeginChild(child_id.c_str(), ImVec2(0, 250), true,
                                  ImGuiWindowFlags_HorizontalScrollbar);
                ImGui::TextUnformatted(uart_data.input_data_consumed.c_str());
                // Auto-scroll to bottom if already at bottom
                if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
                    ImGui::SetScrollHereY(1.0f);
                ImGui::EndChild();
            }
        }

        if (ImGui::CollapsingHeader("API logging",
                                    ImGuiTreeNodeFlags_DefaultOpen))
        {
        }
        ImGui::EndChild();

        ImGui::SameLine();

        // Right region (30%)
        ImGui::BeginChild("RightPane", ImVec2(right_width, window_height),
                          true);

        if (ImGui::CollapsingHeader("System", ImGuiTreeNodeFlags_DefaultOpen))
            ImGui::Text("Here comes the system information");

        if (ImGui::CollapsingHeader("Input GPIOs",
                                    ImGuiTreeNodeFlags_DefaultOpen))
            for (const auto &input_gpio :
                 sim_mcu.mcu->get_gpios(GPIOType::INPUT))
            {
                char label[32];
                snprintf(label, sizeof(label), "GPIO %d", input_gpio.number);
                if (ImGui::Selectable(label, false,
                                      ImGuiSelectableFlags_SpanAllColumns))
                {
                    sim_mcu.mcu->set_gpio_state(input_gpio.number,
                                                !input_gpio.state);
                }
                // Right mouse button DOWN handler
                if (ImGui::IsItemHovered() &&
                    ImGui::IsMouseClicked(ImGuiMouseButton_Right))
                {
                    sim_mcu.mcu->set_gpio_state(input_gpio.number,
                                                !input_gpio.state);
                }

                // Right mouse button UP handler
                if (ImGui::IsItemHovered() &&
                    ImGui::IsMouseReleased(ImGuiMouseButton_Right))
                {
                    sim_mcu.mcu->set_gpio_state(input_gpio.number,
                                                !input_gpio.state);
                }
                ImGui::SameLine(
                    ImGui::GetCursorPosX() + ImGui::GetContentRegionAvail().x -
                    ImGui::CalcTextSize(input_gpio.state ? "HIGH" : "LOW").x);
                if (input_gpio.state)
                {
                    ImGui::PushStyleColor(ImGuiCol_Text,
                                          IM_COL32(0, 200, 0, 255)); // Green
                    ImGui::Text("HIGH");
                    ImGui::PopStyleColor();
                }
                else
                {
                    ImGui::PushStyleColor(ImGuiCol_Text,
                                          IM_COL32(200, 0, 0, 255)); // Red
                    ImGui::Text("LOW");
                    ImGui::PopStyleColor();
                }
            }

        if (ImGui::CollapsingHeader("Output GPIOs",
                                    ImGuiTreeNodeFlags_DefaultOpen))
            for (const auto &output_gpio :
                 sim_mcu.mcu->get_gpios(GPIOType::OUTPUT))
            {
                ImGui::Text("GPIO %d", output_gpio.number);
                ImGui::SameLine(
                    ImGui::GetCursorPosX() + ImGui::GetContentRegionAvail().x -
                    ImGui::CalcTextSize(output_gpio.state ? "HIGH" : "LOW").x);
                ImGui::Text(output_gpio.state ? "HIGH" : "LOW");
            }
        ImGui::EndChild();

        // Restoring spacing
        style.ItemSpacing.x = old_item_spacing_x;
        style.ItemSpacing.y = old_item_spacing_y;
        style.WindowPadding.x = old_window_padding_x;
        style.WindowPadding.y = old_window_padding_y;

        ImGui::End();
        ImGui::PopStyleVar();
    }

    void ImGuiPresenter::_ui_create_window()
    {
        std::clog << "Creating GLFW window..." << std::endl;
        if (glfwInit() != GLFW_TRUE)
            return;
        _window = glfwCreateWindow(1024, 768, "Sabre Pilot", NULL, NULL);
        if (!_window)
        {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(_window);
    }

    void ImGuiPresenter::_ui_create_imgui_context()
    {
        std::clog << "Creating ImGui context..." << std::endl;

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplGlfw_InitForOpenGL(_window, true);
        ImGui_ImplOpenGL3_Init("#version 130");
    }

    void ImGuiPresenter::_ui_destroy_window()
    {
        std::clog << "Destroying GLFW window..." << std::endl;
        if (_window)
        {
            glfwDestroyWindow(_window);
            _window = nullptr;
        }
        glfwTerminate();
    }

    void ImGuiPresenter::_ui_imgui_demo_window()
    {
        if (!_show_imgui_demo)
            return;
        ImGui::ShowDemoWindow(&_show_imgui_demo);
    }

    void ImGuiPresenter::_ui_mcu_windows()
    {
        for (auto &mcu : _simulator.get_mcu_list())
            _ui_mcu(mcu.first, mcu.second);
    }

    void ImGuiPresenter::_ui_imgui_metrics_window()
    {
        if (!_show_imgui_metrics)
            return;
        ImGui::ShowMetricsWindow(&_show_imgui_metrics);
    }

    void ImGuiPresenter::_ui_loop()
    {
        std::clog << "Starting Loop..." << std::endl;
        ImGuiIO &io = ImGui::GetIO();
        while (!glfwWindowShouldClose(_window))
        {
            glfwPollEvents();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());

            _ui_handle_key_events();
            _ui_main_menu();
            _ui_mcu_windows();
            _ui_imgui_demo_window();
            _ui_imgui_metrics_window();

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(_window);
        }
    }

    void ImGuiPresenter::start()
    {
        std::clog << "Starting GUI..." << std::endl;

        _ui_create_window();
        _ui_create_imgui_context();
        _ui_set_scale_to_auto();
        _ui_loop();
        _ui_destroy_window();
    }

    void ImGuiPresenter::_ui_set_scale_to_auto()
    {
        if (!_window)
            return;
        float scale_x, scale_y;
        glfwGetWindowContentScale(_window, &scale_x, &scale_y);
        _ui_set_scale(scale_x);
        _auto_ui_scale = true;
    }

    void ImGuiPresenter::_ui_set_scale(float scale)
    {
        float current_scale = _ui_scale;
        _ui_scale = scale;
        ImGui::GetStyle().ScaleAllSizes(_ui_scale / current_scale);
        ImGuiIO &io = ImGui::GetIO();
        io.FontGlobalScale = _ui_scale;
        _auto_ui_scale = false;
    }

    void ImGuiPresenter::_ui_zoom_in()
    {
        if (_ui_scale < 5)
            _ui_set_scale(_ui_scale + 0.5f);
    }

    void ImGuiPresenter::_ui_zoom_out()
    {
        if (_ui_scale >= 1.5f)
            _ui_set_scale(_ui_scale - 0.5f);
    }
} // namespace sabre::pilot