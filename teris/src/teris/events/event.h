#pragma once

#include "../core.h"

namespace teris {
	
	// events are blocking right now
	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
	};

	enum EventCategory {
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput       = BIT(1),
		EventCategoryKeyboard    = BIT(2),
		EventCategoryMouse       = BIT(3),
		EventCategoryMouseButton = BIT(4),
	};

#define EVENT_CLASS_TYPE(type) static EventType get_static_type() { return EventType::##type; }\
						 virtual EventType get_event_type() const override { return get_static_type(); }\
						 virtual const char* get_name() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int get_category_flags() const override { return category; }

	class TERIS_API Event {
		friend class EventDispatcher;
	public:
		virtual EventType get_event_type() const = 0;
		virtual const char* get_name() const = 0;
		virtual int get_category_flags() const = 0;
		virtual std::string to_string() const { return get_name(); }

		inline bool is_category(EventCategory category) {
			return get_category_flags() & category;
		}

		bool handled = false;
	protected:
	};

	class EventDispatcher {
		template<typename event_ty> using EventFn = std::function<bool(event_ty&)>;
	public:
		EventDispatcher(Event& event) : m_Event(event) {

		}

		template<typename event_ty>
		bool dispatch(EventFn<event_ty> func) {
			if (m_Event.get_event_type() == event_ty::get_static_type()) {
				m_Event.handled = func(*(event_ty*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.to_string();
	}
}