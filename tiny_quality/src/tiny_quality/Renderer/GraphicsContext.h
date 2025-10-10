#pragma once

namespace tiny_quality {

	class GraphicsContext {
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
		
	};
}