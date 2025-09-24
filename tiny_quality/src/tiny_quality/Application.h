#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace tiny_quality {

	class TINY_QUALITY_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//To be defined in CLIENT
	Application* CreateApplication();
}
