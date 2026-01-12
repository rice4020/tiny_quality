#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}


void Sandbox2D::OnAttach() {
	TQ_PROFILE_FUNCTION();

	m_CheckerboardTexture = tiny_quality::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach() {
	TQ_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(tiny_quality::Timestep ts) {

	TQ_PROFILE_FUNCTION();
	//update
	m_CameraController.OnUpdate(ts);

	//render
	{
		TQ_PROFILE_SCOPE("Renderer Prep");
		tiny_quality::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		tiny_quality::RenderCommand::Clear();
	}

	{
		TQ_PROFILE_SCOPE("Renderer Draw");
		tiny_quality::Renderer2D::BeginScene(m_CameraController.GetCamera());
		tiny_quality::Renderer2D::DrowQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		tiny_quality::Renderer2D::DrowQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		tiny_quality::Renderer2D::DrowQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
		tiny_quality::Renderer2D::EndScene();
	}

}

void Sandbox2D::OnImGuiRender() {
	TQ_PROFILE_FUNCTION();
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(tiny_quality::Event& e) {
	m_CameraController.OnEvent(e);
}
