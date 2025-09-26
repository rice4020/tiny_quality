#include "tqpch.h"
#include "Application.h"

#include "tiny_quality/Events/ApplicationEvent.h"
#include "tiny_quality/Log.h"

#include <GLFW/glfw3.h>

namespace tiny_quality {

	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {

	}

	void Application::Run() {
		
		while (m_Runing) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

}