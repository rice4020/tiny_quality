#include "tqpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace tiny_quality {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}
