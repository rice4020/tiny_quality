#pragma once

#ifdef TQ_PLATFORM_WINDOWS

extern tiny_quality::Application* tiny_quality::CreateApplication();

int main(int argc, char** argv) {

	tiny_quality::Log::Init();
	TQ_CORE_WARN("Initialized Log!");
	int a = 5;
	TQ_INFO("Hello! Var={0}", a);

	auto app = tiny_quality::CreateApplication();
	app->Run();
	delete app;
}

#endif 


