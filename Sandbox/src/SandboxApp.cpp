#include <tiny_quality.h>

#include "imgui/imgui.h"

class ExampleLayer : public tiny_quality::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (tiny_quality::Input::IsKeyPressed(TQ_KEY_TAB))
			TQ_TRACE("Tab key is pressed! (poll)!");
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(tiny_quality::Event& event) override
	{
		if (event.GetEventType() == tiny_quality::EventType::KeyPressed) {
			tiny_quality::KeyPressedEvent& e = (tiny_quality::KeyPressedEvent&)event;
			if(e.GetKeyCode() == TQ_KEY_TAB)
				TQ_TRACE("Tab key is pressed! (event)!");
			TQ_TRACE("{0}", (char)e.GetKeyCode());
		}
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