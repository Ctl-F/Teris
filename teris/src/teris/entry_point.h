#pragma once

#ifdef TS_PLATFORM_WINDOWS

extern teris::Application* teris::teris_main(const std::vector<std::string>& args);

int main(int argc, char** argv) {
	std::vector<std::string> s_args = std::vector<std::string>(argc);
	for (int i = 0; i < argc; i++) {
		s_args.push_back(std::string(argv[i]));
	}
	teris::Log::init();

	TS_CORE_INFO("Nao esquece do gelo!");
	TS_CORE_INFO("Initializing window with {0} args", s_args.size());

	auto app = teris::teris_main(s_args);
	app->run();
	delete app;

	TS_CORE_TRACE("Finished");
}

#endif
