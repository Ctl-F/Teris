#include "tpch.h"
#include "ImGuiLayer.h"
#include "teris/core.h"

#include "teris/application.h"
// temporary
#include "GLFW/glfw3.h"
#include <glad/glad.h>

#include "imgui.h"
#include "teris/platform/OpenGL/imgui_impl_opengl3.h"

namespace teris {
	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
	{

	}
	ImGuiLayer::~ImGuiLayer()
	{

	}
	void ImGuiLayer::on_attach()
	{
		auto ctx = ImGui::CreateContext();
		ImGui::SetCurrentContext(ctx);

		ImGui_ImplOpenGL3_Init("#version 410");
		
		ImGuiIO& io = ImGui::GetIO(); (void)io;


		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		
		ImGui::StyleColorsDark();

		// temporary
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

	}
	void ImGuiLayer::on_detach()
	{
		
	}
	void ImGuiLayer::on_update()
	{
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::get();
		io.DisplaySize = ImVec2(app.get_window().get_width(), app.get_window().get_height());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0 / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	void ImGuiLayer::on_event(Event& event)
	{
		EventDispatcher dispatcher(event);

		dispatcher.dispatch<MouseMoveEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseMoveEvent));
		dispatcher.dispatch<MouseScrollEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseScrollEvent));
		dispatcher.dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.dispatch<KeyPressedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyPressEvent));
		dispatcher.dispatch<KeyReleasedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyReleaseEvent));
		dispatcher.dispatch<KeyTypedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
		dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FN(ImGuiLayer::OnWindowResizedEvent));
	}
	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[event.get_mouse_button()] = true;
		return false;
	}
	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[event.get_mouse_button()] = false;
		return false;
	}
	bool ImGuiLayer::OnMouseMoveEvent(MouseMoveEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(event.x(), event.y());
		return false;
	}
	bool ImGuiLayer::OnMouseScrollEvent(MouseScrollEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheel += event.y();
		io.MouseWheelH += event.x();
		return false;
	}
	bool ImGuiLayer::OnKeyPressEvent(KeyPressedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.KeysDown[event.get_key_code()] = true;

		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

		return false;
	}
	bool ImGuiLayer::OnKeyReleaseEvent(KeyReleasedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.KeysDown[event.get_key_code()] = false;

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& event) {
		ImGuiIO& io = ImGui::GetIO();

		int keycode = event.get_key_code();
		if (keycode > 0 && keycode < 0x10000) {
			io.AddInputCharacter((unsigned short)keycode);
		}

		return false;
	}

	bool ImGuiLayer::OnWindowResizedEvent(WindowResizeEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.DisplaySize = ImVec2(event.width(), event.height());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

		// TEMP
		glViewport(0, 0, event.width(), event.height());

		return false;
	}
}
