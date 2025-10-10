#pragma once

#include "tiny_quality/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace tiny_quality {

	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};
}