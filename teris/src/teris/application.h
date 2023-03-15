#pragma once

#include "core.h"

namespace teris {

	class TERIS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
	};


	// define in client
	Application* teris_main(const std::vector<std::string>& args);
}

