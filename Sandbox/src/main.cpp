#include <teris.h>


class Sandbox : public teris::Application {
public:
	Sandbox() {

	}
	~Sandbox() {

	}

};

teris::Application* teris::teris_main(const std::vector<std::string>& args) {
	return new Sandbox();
}