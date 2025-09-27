#pragma once

#include "Core.h"

#include "Window.h"
#include "tiny_quality/LayerStack.h"
#include "tiny_quality/Events/Event.h"
#include "tiny_quality/Events/ApplicationEvent.h"


namespace tiny_quality {

	class TINY_QUALITY_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Runing = true;
		LayerStack m_LayerStack;
	};

	//To be defined in CLIENT
	Application* CreateApplication();
}
