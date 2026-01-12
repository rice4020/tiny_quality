#pragma once

#ifdef TQ_PLATFORM_WINDOWS

extern tiny_quality::Application* tiny_quality::CreateApplication();

int main(int argc, char** argv) {

	TQ_PROFILE_BEGIN_SESSION("Startup", "tiny_quality-Startup.json");
	tiny_quality::Log::Init();
	TQ_PROFILE_END_SESSION();
	TQ_PROFILE_BEGIN_SESSION("Runtime", "tiny_quality-Runtime.json");
	auto app = tiny_quality::CreateApplication();
	app->Run();
	TQ_PROFILE_END_SESSION();
	TQ_PROFILE_BEGIN_SESSION("Shutdown", "tiny_quality-Shutdown.json");
	delete app;
	TQ_PROFILE_END_SESSION();
}

#endif 


