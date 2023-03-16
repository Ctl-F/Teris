#include "tpch.h"
#include "WindowWin32.h"

#include "teris/events/event.h"
#include "teris/events/application_event.h"
#include "teris/events/key_event.h"
#include "teris/events/mouse_event.h"
#include "glad/glad.h"

namespace teris {
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int err, const char* description) {
		TS_CORE_ERROR("GLFW Error({0}) {1}", err, description);
	}

	Window* Window::create(const WindowProperties& props) {
		return new WindowWin32(props);
	}

	WindowWin32::WindowWin32(const WindowProperties& props) {
		init(props);
	}

	WindowWin32::~WindowWin32() {
		shutdown();
	}

	void WindowWin32::init(const WindowProperties& props) {
		m_Data.title = props.title;
		m_Data.width = props.width;
		m_Data.height = props.height;

		TS_CORE_INFO("Creating Win32 Window {0} ({1}, {2})", props.title, props.width, props.height);

		if (!s_GLFWInitialized) {
			int success = glfwInit();
			TS_CORE_ASSERT(success, "Could not initialize GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.width, (int)props.height, m_Data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		TS_CORE_ASSERT(status, "Failed to initialize Glad!");

		glfwSetWindowUserPointer(m_Window, &m_Data);
		set_vsync(true);

		// initialize callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;
			
			WindowResizeEvent event(width, height);
			data.event_callback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.event_callback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			
			switch (action) {
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, 0);
				data.event_callback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				data.event_callback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event(key, 1);
				data.event_callback(event);
				break;
			}
			}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keycode);
			data.event_callback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
			case GLFW_PRESS: {
				MouseButtonPressedEvent event(button);
				data.event_callback(event);
				break;
			}
			case GLFW_RELEASE: {
				MouseButtonReleasedEvent event(button);
				data.event_callback(event);
				break;
			}
			}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoff, double yoff) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrollEvent event((float)xoff, (float)yoff);
			data.event_callback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMoveEvent event((float)x, (float)y);
			data.event_callback(event);
			});
	}

	void WindowWin32::shutdown() {
		if (m_Window != nullptr) {
			glfwDestroyWindow(m_Window);
			m_Window = nullptr;
		}
	}

	void WindowWin32::on_update() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowWin32::set_vsync(bool enable) {
		glfwSwapInterval(enable);
		m_Data.is_vsync = enable;
	}

	bool WindowWin32::is_vsync() const {
		return m_Data.is_vsync;
	}


}
