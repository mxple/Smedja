#include "ImGuiLayer.h"
#include "Smedja/Application.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

namespace Smedja {

ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {
    SD_CORE_INFO("ImGuiLayer constructed");
}

ImGuiLayer::~ImGuiLayer() {}

void ImGuiLayer::onAttach() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    ImGui_ImplOpenGL3_Init();
    // Set ImGui Style
    ImGui::StyleColorsDark();
}

void ImGuiLayer::onDetach() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiLayer::onUpdate() {
    ImGuiIO &io = ImGui::GetIO();
    Application &app = Application::get();
    io.DisplaySize = ImVec2((float)app.getWindow().getWidth(),
                            (float)app.getWindow().getHeight());

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    static bool show = true;
    ImGui::ShowDemoWindow(&show);
    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::onEvent(Event &e) {}

} // namespace Smedja
