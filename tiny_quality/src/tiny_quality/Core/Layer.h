#pragma once

#include "tiny_quality/Core/Core.h"
#include "tiny_quality/Core/Timestep.h"
#include "tiny_quality/Events/Event.h"


namespace tiny_quality {

	class TINY_QUALITY_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}