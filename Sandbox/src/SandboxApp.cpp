#include <tiny_quality.h>

class ExampleLayer : public tiny_quality::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		TQ_INFO("ExampleLayer::Update");
	}

	void OnEvent(tiny_quality::Event& event) override
	{
		TQ_TRACE("{0}", event);
	}

};

class Sandbox : public tiny_quality::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}
	
	~Sandbox() {

	}
};

tiny_quality::Application* tiny_quality::CreateApplication() {
	return new Sandbox();
}