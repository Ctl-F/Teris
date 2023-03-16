#include <teris.h>



class Sandbox : public teris::Application {
public:
	Sandbox() {
		push_overlay(new teris::ImGuiLayer());
	}
	~Sandbox() {

	}

};

teris::Application* teris::teris_main(const std::vector<std::string>& args) {
	return new Sandbox();
}