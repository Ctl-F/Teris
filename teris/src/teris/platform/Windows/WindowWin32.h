#pragma once

#include <teris/core.h>
#include <teris/window.h>

#include <GLFW/glfw3.h>

namespace teris {

	class WindowWin32 : public Window
	{
	public:
		WindowWin32(const WindowProperties& props);
		virtual ~WindowWin32();

		void on_update() override;

		inline unsigned int get_width() const override { return m_Data.width; }
		inline unsigned int get_height() const override { return m_Data.height; }

		inline void set_event_callback(const EventCallbackFn& callback) override { m_Data.event_callback = callback; }
		void set_vsync(bool enabled) override;
		bool is_vsync() const override;

		/*void set_fullscreen(bool enabled, int monitor = 0) override;
		bool is_fullscreen() const override;*/

	private:
		virtual void init(const WindowProperties& props);
		virtual void shutdown();

	private:
		GLFWwindow* m_Window;

		struct WindowData {
			std::string title;
			unsigned int width, height;
			bool is_fullscreen, is_vsync;
			EventCallbackFn event_callback;
		};

		WindowData m_Data;
	};
}

