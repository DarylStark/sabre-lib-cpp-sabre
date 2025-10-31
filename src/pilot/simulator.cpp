#include "simulator.hpp"
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include <iostream>
#include <sstream>

namespace sabre::pilot
{
    void Simulator::add_mcu(const std::string &name, const MCUConfig &config,
                            sabre::AppUniquePtr &&app)
    {
        SimulatorMCU mcu{.mcu = std::make_unique<MCU>(config, std::move(app))};
        if (_mcus.find(name) != _mcus.end())
        {
            // TODO: Custom exception
            throw std::runtime_error("MCU with name '" + name +
                                     "' already exists");
        }
        _mcus[name] = std::move(mcu);
    }

    void Simulator::_start_mcu(SimulatorMCU &sim_mcu)
    {
        if (sim_mcu.thread == nullptr)
        {
            std::cout << "Starting MCU in new thread..." << std::endl;
            sim_mcu.thread = std::make_unique<std::jthread>(
                &Simulator::_thread_mcu_start, this, std::ref(sim_mcu.mcu));
            sim_mcu.thread->detach();
        }
    }

    void Simulator::start_mcu(const std::string &name)
    {
        auto it = _mcus.find(name);
        if (it == _mcus.end())
        {
            // TODO: Custom exception
            throw std::runtime_error("MCU with name '" + name + "' not found");
        }
        _start_mcu(it->second);
    }

    void Simulator::_thread_mcu_start(std::unique_ptr<MCU> &mcu)
    {
        while (true)
            mcu->start();
    }

    void Simulator::_start_all_mcus()
    {
        for (auto &sim_mcu : _mcus)
            _start_mcu(sim_mcu.second);
    }

    void Simulator::start()
    {
        start_gui();
    }

    void Simulator::_ui_handle_key_events()
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

    void Simulator::_ui_setup_menubar()
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Exit"))
                    glfwSetWindowShouldClose(_window, GLFW_TRUE);
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("View"))
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
                    if (ImGui::MenuItem("100%", nullptr,
                                        _ui_scale == 1.0f && !_auto_ui_scale))
                        _ui_set_scale(1.0f);
                    if (ImGui::MenuItem("150%", nullptr,
                                        _ui_scale == 1.5f && !_auto_ui_scale))
                        _ui_set_scale(1.5f);
                    if (ImGui::MenuItem("200%", nullptr,
                                        _ui_scale == 2.0f && !_auto_ui_scale))
                        _ui_set_scale(2.0f);
                    if (ImGui::MenuItem("250%", nullptr,
                                        _ui_scale == 2.5f && !_auto_ui_scale))
                        _ui_set_scale(2.5f);
                    if (ImGui::MenuItem("300%", nullptr,
                                        _ui_scale == 3.0f && !_auto_ui_scale))
                        _ui_set_scale(3.0f);
                    if (ImGui::MenuItem("350%", nullptr,
                                        _ui_scale == 3.5f && !_auto_ui_scale))
                        _ui_set_scale(3.5f);
                    if (ImGui::MenuItem("400%", nullptr,
                                        _ui_scale == 4.0f && !_auto_ui_scale))
                        _ui_set_scale(4.0f);
                    if (ImGui::MenuItem("450%", nullptr,
                                        _ui_scale == 4.5f && !_auto_ui_scale))
                        _ui_set_scale(4.5f);
                    if (ImGui::MenuItem("500%", nullptr,
                                        _ui_scale == 5.0f && !_auto_ui_scale))
                        _ui_set_scale(5.0f);
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("MCU"))
                {
                    for (auto &mcu : _mcus)
                        if (ImGui::MenuItem(mcu.first.c_str(), nullptr,
                                            mcu.second.show))
                            mcu.second.show = !mcu.second.show;
                    ImGui::EndMenu();
                }
                if (ImGui::MenuItem("Debug window", nullptr, _show_debug))
                    _show_debug = !_show_debug;
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

    void Simulator::_ui_mcu(const std::string &name, SimulatorMCU &sim_mcu)
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
            std::stringstream header;
            header << "UART " << uart_number << " output";
            if (ImGui::CollapsingHeader(header.str().c_str(),
                                        ImGuiTreeNodeFlags_DefaultOpen))
            {
                std::string child_id =
                    "UARTOutputChild" + std::to_string(uart_number);
                ImGui::BeginChild(child_id.c_str(), ImVec2(0, 250), true,
                                  ImGuiWindowFlags_HorizontalScrollbar);
                ImGui::TextUnformatted(uart_data.c_str());
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

    void Simulator::start_gui()
    {
        std::cout << "Starting GUI..." << std::endl;
        const auto retval = glfwInit();
        if (retval != GLFW_TRUE)
            return;
        _window = glfwCreateWindow(1024, 768, "Sabre Pilot", NULL, NULL);
        if (!_window)
        {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(_window);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplGlfw_InitForOpenGL(_window, true);
        ImGui_ImplOpenGL3_Init("#version 130");

        _ui_set_scale_to_auto();

        while (!glfwWindowShouldClose(_window))
        {
            glfwPollEvents();

            io.FontGlobalScale = _ui_scale;

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());

            _ui_handle_key_events();
            _ui_setup_menubar();

            for (auto &mcu : _mcus)
                _ui_mcu(mcu.first, mcu.second);

            if (_show_debug)
            {
                ImGui::Begin("Debug", &_show_debug);
                ImGui::Text("Frame rate: %.1f", io.Framerate);
                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(_window);
        }

        glfwDestroyWindow(_window);
        glfwTerminate();
    }

    void Simulator::_ui_set_scale_to_auto()
    {
        if (!_window)
            return;
        float scale_x, scale_y;
        glfwGetWindowContentScale(_window, &scale_x, &scale_y);
        _ui_set_scale(scale_x);
        _auto_ui_scale = true;
    }

    void Simulator::_ui_set_scale(float scale)
    {
        float current_scale = _ui_scale;
        _ui_scale = scale;
        ImGui::GetStyle().ScaleAllSizes(_ui_scale / current_scale);
        _auto_ui_scale = false;
    }

    void Simulator::_ui_zoom_in()
    {
        if (_ui_scale < 5)
            _ui_set_scale(_ui_scale + 0.5f);
    }

    void Simulator::_ui_zoom_out()
    {
        if (_ui_scale >= 1.5f)
            _ui_set_scale(_ui_scale - 0.5f);
    }
} // namespace sabre::pilot