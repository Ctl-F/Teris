#pragma once

#include <teris/core.h>
#include <teris/events/event.h>

namespace teris {
	
	class TERIS_API Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void on_attach() {};
		virtual void on_detach() {};
		virtual void on_update() {};
		virtual void on_event(Event& event) {};

		inline const std::string& get_name() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}