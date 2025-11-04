#pragma once

#include "Core.h"

#include "Window.h"
#include "tiny_quality/LayerStack.h"
#include "tiny_quality/Events/Event.h"
#include "tiny_quality/Events/ApplicationEvent.h"

#include "tiny_quality/Core/Timestep.h"

#include "tiny_quality/ImGui/ImGuiLayer.h"


namespace tiny_quality {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Runing = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	//To be defined in CLIENT
	Application* CreateApplication();
}
