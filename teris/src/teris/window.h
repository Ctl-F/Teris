#pragma once
#include "tpch.h"

#include "teris/core.h"
#include "teris/events/event.h"

namespace teris {

	struct WindowProperties {
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProperties(const std::string& title = "Teris Engine", unsigned int width = 1280, unsigned int height = 720) :
			title(title), width(width), height(height) {}
	};


	// window interface
	class TERIS_API Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		
		virtual ~Window() {}

		virtual void on_update() = 0;
		
		virtual unsigned int get_width() const = 0;
		virtual unsigned int get_height() const = 0;

		virtual void set_event_callback(const EventCallbackFn& callback) = 0;
		virtual void set_vsync(bool enabled) = 0;
		virtual bool is_vsync() const = 0;

		/*virtual void set_fullscreen(bool fullscreen, int monitor = 0) = 0;
		virtual bool is_fullscreen() const = 0;*/

		static Window* create(const WindowProperties& properties = WindowProperties());
	};
}