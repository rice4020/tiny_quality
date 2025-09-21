#pragma once

#ifdef TQ_PLATFORM_WINDOWS

extern tiny_quality::Application* tiny_quality::CreateApplication();

int main(int argc, char** argv) {
	auto app = tiny_quality::CreateApplication();
	app->Run();
	delete app;
}

#endif 


