#include "tqpch.h"
#include "Application.h"

#include "tiny_quality/Events/ApplicationEvent.h"
#include "tiny_quality/Log.h"

namespace tiny_quality {

	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::Run() {

		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			TQ_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			TQ_TRACE(e);
		}

		while (true);
	}

}