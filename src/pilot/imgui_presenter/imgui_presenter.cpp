#include "imgui_presenter.hpp"
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include <iostream>

namespace sabre::impl::pilot
{
    ImGuiPresenter::ImGuiPresenter(Simulator &simulator) : Presenter(simulator)
    {
    }

    void ImGuiPresenter::_handle_key_events()
    {
        if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl) &&
            ImGui::IsKeyPressed(ImGuiKey_Equal))
            _zoom_in();
        if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl) &&
            ImGui::IsKeyPressed(ImGuiKey_Minus))
            _zoom_out();
        if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl) &&
            ImGui::IsKeyPressed(ImGuiKey_0))
            _set_scale_to_auto();
    }

    void ImGuiPresenter::_main_menu()
    {
        if (ImGui::BeginMainMenuBar())
        {
            _main_menu_file();
            _main_menu_view();
            _main_menu_debug();
            ImGui::EndMainMenuBar();
        }
    }

    void ImGuiPresenter::_main_menu_file()
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit"))
                glfwSetWindowShouldClose(_window, GLFW_TRUE);
            ImGui::EndMenu();
        }
    }

    void ImGuiPresenter::_main_menu_view()
    {
        if (ImGui::BeginMenu("View"))
        {
            _main_menu_view_device_list();
            _main_menu_view_scale();
            _main_menu_view_theme();
            ImGui::EndMenu();
        }
    }

    void ImGuiPresenter::_main_menu_view_device_list()
    {
        if (ImGui::BeginMenu("Device"))
        {
            for (auto &device : _simulator.get_device_list())
                if (ImGui::MenuItem(device.first.c_str(), nullptr,
                                    _device_visibility[device.first]))
                    _device_visibility[device.first] =
                        !_device_visibility[device.first];
            ImGui::EndMenu();
        }
    }

    void ImGuiPresenter::_main_menu_view_scale()
    {
        if (ImGui::BeginMenu("Scale"))
        {
            if (ImGui::MenuItem("Auto", "Ctrl + 0", _auto_scale))
                _set_scale_to_auto();
            ImGui::Separator();
            if (ImGui::MenuItem("Zoom in", "Ctrl + =", false, _scale != 5.0f))
                _zoom_in();
            if (ImGui::MenuItem("Zoom out", "Ctrl + -", false, _scale != 1.0f))
                _zoom_out();
            ImGui::Separator();
            for (float scale = 1; scale <= 5; scale += 0.5f)
            {
                std::string label =
                    std::to_string(static_cast<int>(scale * 100)) + "%";
                if (ImGui::MenuItem(label.c_str(), nullptr,
                                    _scale == scale && !_auto_scale))
                    _set_scale(scale);
            }
            ImGui::EndMenu();
        }
    }

    void ImGuiPresenter::_main_menu_view_theme()
    {
        if (ImGui::BeginMenu("Theme"))
        {
            if (ImGui::MenuItem("Light", nullptr,
                                _current_theme == ImGuiTheme::LIGHT))
                _current_theme = ImGuiTheme::LIGHT;
            if (ImGui::MenuItem("Dark", nullptr,
                                _current_theme == ImGuiTheme::DARK))
                _current_theme = ImGuiTheme::DARK;
            if (ImGui::MenuItem("Classic", nullptr,
                                _current_theme == ImGuiTheme::CLASSIC))
                _current_theme = ImGuiTheme::CLASSIC;
            ImGui::EndMenu();
        }
    }

    void ImGuiPresenter::_main_menu_debug()
    {
        if (ImGui::BeginMenu("Debug"))
        {
            ImGui::MenuItem("ImGui Demo Window", nullptr, &_show_imgui_demo);
            ImGui::MenuItem("ImGui Metric Window", nullptr,
                            &_show_imgui_metrics);
            ImGui::EndMenu();
        }
    }

    void ImGuiPresenter::_device(const std::string &name,
                                 SimulatorDevice &sim_device)
    {
        if (_device_visibility.find(name) == _device_visibility.end())
            _device_visibility[name] = true;

        if (!_device_visibility[name])
            return;

        sim_device.device->accept(_imgui_visitor, name);
        return;
    }

    void ImGuiPresenter::_create_window()
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

    void ImGuiPresenter::_create_imgui_context()
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

    void ImGuiPresenter::_destroy_window()
    {
        std::clog << "Destroying GLFW window..." << std::endl;
        if (_window)
        {
            glfwDestroyWindow(_window);
            _window = nullptr;
        }
        glfwTerminate();
    }

    void ImGuiPresenter::_imgui_demo_window()
    {
        if (!_show_imgui_demo)
            return;
        ImGui::ShowDemoWindow(&_show_imgui_demo);
    }

    void ImGuiPresenter::_device_windows()
    {
        for (auto &device : _simulator.get_device_list())
            _device(device.first, device.second);
    }

    void ImGuiPresenter::_imgui_metrics_window()
    {
        if (!_show_imgui_metrics)
            return;
        ImGui::ShowMetricsWindow(&_show_imgui_metrics);
    }

    void ImGuiPresenter::_loop()
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

            if (_current_theme == ImGuiTheme::DARK)
                ImGui::StyleColorsDark();
            else if (_current_theme == ImGuiTheme::LIGHT)
                ImGui::StyleColorsLight();
            else if (_current_theme == ImGuiTheme::CLASSIC)
                ImGui::StyleColorsClassic();

            _handle_key_events();
            _main_menu();
            _device_windows();
            _imgui_demo_window();
            _imgui_metrics_window();

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(_window);
        }
    }

    void ImGuiPresenter::start()
    {
        std::clog << "Starting GUI..." << std::endl;

        _create_window();
        _create_imgui_context();
        _set_scale_to_auto();
        _loop();
        _destroy_window();
    }

    void ImGuiPresenter::_set_scale_to_auto()
    {
        if (!_window)
            return;
        float scale_x, scale_y;
        glfwGetWindowContentScale(_window, &scale_x, &scale_y);
        _set_scale(scale_x);
        _auto_scale = true;
    }

    void ImGuiPresenter::_set_scale(float scale)
    {
        float current_scale = _scale;
        _scale = scale;
        ImGui::GetStyle().ScaleAllSizes(_scale / current_scale);
        ImGuiIO &io = ImGui::GetIO();
        io.FontGlobalScale = _scale;
        _auto_scale = false;
    }

    void ImGuiPresenter::_zoom_in()
    {
        if (_scale < 5)
            _set_scale(_scale + 0.5f);
    }

    void ImGuiPresenter::_zoom_out()
    {
        if (_scale >= 1.5f)
            _set_scale(_scale - 0.5f);
    }
} // namespace sabre::impl::pilot