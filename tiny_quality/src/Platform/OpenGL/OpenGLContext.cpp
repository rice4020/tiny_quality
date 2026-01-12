#include "tqpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace tiny_quality {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) 
		:m_WindowHandle(windowHandle)
	{
		TQ_CORE_ASSERT(m_WindowHandle, "Window Handle is null");

	}

	void OpenGLContext::Init() {
		TQ_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		TQ_CORE_ASSERT(status, "Failed to initialize Glad!");

		TQ_CORE_INFO("OpenGL info : ");
		TQ_CORE_INFO("  Vendor : {0}", (const char*)glGetString(GL_VENDOR));
		TQ_CORE_INFO("  Renderer : {0}", (const char*)glGetString(GL_RENDERER));
		TQ_CORE_INFO("  Version : {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers() {
		TQ_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}
}