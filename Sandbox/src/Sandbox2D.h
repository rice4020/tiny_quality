#pragma once

#include "tiny_quality.h"

class Sandbox2D : public tiny_quality::Layer {
private:
	tiny_quality::OrthographicCameraController m_CameraController;

	tiny_quality::Ref<tiny_quality::VertexArray> m_SquareVA;
	tiny_quality::Ref<tiny_quality::Shader> m_FlatColorShader;

	tiny_quality::Ref<tiny_quality::Texture2D> m_CheckerboardTexture;

	struct ProfileResult {
		const char* Name;
		float Time;
	};

	std::vector<ProfileResult> m_ProfileResults;
	
	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(tiny_quality::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(tiny_quality::Event& e) override;
};