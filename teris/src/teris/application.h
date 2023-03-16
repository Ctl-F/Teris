#pragma once

#include "core.h"
#include "window.h"
#include "teris/events/application_event.h"
#include <teris/layer_stack.h>

namespace teris {

	class TERIS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();

		void push_layer(Layer* layer);
		void push_overlay(Layer* layer);

		void on_event(Event& e);
		
		inline static Application& get() { return *s_Instance; }

		inline Window& get_window() { return *m_Window; }
	
	private:
		bool on_window_close(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

		static Application* s_Instance;
	};


	// define in client
	Application* teris_main(const std::vector<std::string>& args);
}

