#include "hud/Hud.hpp"

#include "engine/Camera.hpp"
#include "engine/Window.hpp"
#include "engine/Renderer.hpp"
#include "engine/Camera.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

bool Hud::_wireframeMode = false;
int Hud::_resolution = 64;
Color Hud::_planetColor;
float Hud::_planetRadius = 1.0f;


void Hud::init(GLFWwindow* window)
{
    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
}

void Hud::draw(const std::shared_ptr<Camera>& camera, const Window& windowObject) const
{
    //New Frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Hints Pannel
    {
        ImGui::SetNextWindowPos(ImVec2(windowObject.Width() - 400, 0));
        ImGui::SetNextWindowSize(ImVec2(400, windowObject.Height()));
        ImGui::Begin("Procedural Planets Settings");
        {
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::Checkbox("Wireframe Mode", &_wireframeMode);
            ImGui::SliderInt("Resolution", &_resolution, 4, 128);
            ImGui::ColorEdit3("Planet Color", (float*)&_planetColor);
            ImGui::SliderFloat("Size", &_planetRadius, 0.2f, 4.0f);
        }
        ImGui::End();
    }

    // Render ImGUI
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
}

void Hud::free()
{
    //Shutdown ImGUI
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}



