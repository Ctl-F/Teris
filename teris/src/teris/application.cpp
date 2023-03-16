#include "tpch.h"
#include "Application.h"

#include "events/event.h"
#include "events/application_event.h"

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace teris {
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::create());
		m_Window->set_event_callback(BIND_EVENT_FN(Application::on_event));
	}

	Application::~Application()
	{
	}


	void Application::on_event(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::on_window_close));

		for (auto layer = m_LayerStack.end(); layer != m_LayerStack.begin(); ) {
			(*--layer)->on_event(e);
			if (e.handled) {
				break;
			}
		}
	}
	

	void Application::run()
	{
		while (m_Running) {

			for (Layer* layer : m_LayerStack) {
				layer->on_update();
			}

			m_Window->on_update();
		};
	}

	void Application::push_layer(Layer* layer) {
		m_LayerStack.push_layer(layer);
	}

	void Application::push_overlay(Layer* layer) {
		m_LayerStack.push_overlay(layer);
	}
	
	
	bool Application::on_window_close(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}
}