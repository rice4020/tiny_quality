#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}


void Sandbox2D::OnAttach() {
	m_SquareVA = tiny_quality::VertexArray::Create();

	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f, 
		 0.5f, -0.5f, 0.0f, 
		 0.5f,  0.5f, 0.0f, 
		-0.5f,  0.5f, 0.0f
	};

	tiny_quality::Ref<tiny_quality::VertexBuffer> squareVB;
	squareVB.reset(tiny_quality::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

	squareVB->SetLayout({
		{ tiny_quality::ShaderDataType::Float3, "a_Position" }
	});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	tiny_quality::Ref<tiny_quality::IndexBuffer> squareIB;
	squareIB.reset(tiny_quality::IndexBuffer::Create(squareIndices, sizeof(squareIndices)));
	m_SquareVA->SetIndexBuffer(squareIB);

	m_FlatColorShader = tiny_quality::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach() {

}

void Sandbox2D::OnUpdate(tiny_quality::Timestep ts) {
	//update
	m_CameraController.OnUpdate(ts);

	//render
	tiny_quality::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	tiny_quality::RenderCommand::Clear();

	tiny_quality::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<tiny_quality::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<tiny_quality::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	tiny_quality::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	tiny_quality::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(tiny_quality::Event& e) {
	m_CameraController.OnEvent(e);
}
