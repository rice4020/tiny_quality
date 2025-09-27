#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "tiny_quality/Events/ApplicationEvent.h"

#include "Window.h"

namespace tiny_quality {

	class TINY_QUALITY_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Runing = true;
	};

	//To be defined in CLIENT
	Application* CreateApplication();
}
