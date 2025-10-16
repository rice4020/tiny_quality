#pragma once

#include "Core.h"

#include "Window.h"
#include "tiny_quality/LayerStack.h"
#include "tiny_quality/Events/Event.h"
#include "tiny_quality/Events/ApplicationEvent.h"

#include "tiny_quality/ImGui/ImGuiLayer.h"

#include "tiny_quality/Renderer/Shader.h"
#include "tiny_quality/Renderer/Buffer.h"
#include "tiny_quality/Renderer/VertexArray.h"

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

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Runing = true;
		LayerStack m_LayerStack;
		
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_squareVA;
	private:
		static Application* s_Instance;
	};

	//To be defined in CLIENT
	Application* CreateApplication();
}
