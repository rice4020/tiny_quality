#pragma once

#include "tiny_quality/Layer.h"

#include "tiny_quality/Events/ApplicationEvent.h"
#include "tiny_quality/Events/KeyEvent.h"
#include "tiny_quality/Events/MouseEvent.h"

namespace tiny_quality {

	class TINY_QUALITY_API ImGuiLayer : public Layer {
	private:
		float m_Time = 0.0f;
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	};

}