#include <tiny_quality.h>


class Sandbox : public tiny_quality::Application {
public:
	Sandbox() {

	}
	
	~Sandbox() {

	}
};

tiny_quality::Application* tiny_quality::CreateApplication() {
	return new Sandbox();
}