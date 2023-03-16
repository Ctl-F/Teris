#pragma once

#include "teris/core.h"
#include "teris/layer.h"

#include "teris/events/all.h"

namespace teris {
	class TERIS_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void on_attach() override;
		void on_detach() override;
		void on_update() override;
		void on_event(Event& event) override;
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
		bool OnMouseMoveEvent(MouseMoveEvent& event);
		bool OnMouseScrollEvent(MouseScrollEvent& event);
		bool OnKeyPressEvent(KeyPressedEvent& event);
		bool OnKeyReleaseEvent(KeyReleasedEvent& event);
		bool OnKeyTypedEvent(KeyTypedEvent& event);
		bool OnWindowResizedEvent(WindowResizeEvent& event);

	private:
		float m_Time = 0.0;
	};
}
