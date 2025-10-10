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
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		TQ_CORE_ASSERT(status, "Failed to initialize Glad!");
	}

	void OpenGLContext::SwapBuffers() {


		glfwSwapBuffers(m_WindowHandle);
	}
}