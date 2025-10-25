#include <tiny_quality.h>

#include "imgui/imgui.h"

class ExampleLayer : public tiny_quality::Layer
{
private:
	std::shared_ptr<tiny_quality::Shader> m_Shader;
	std::shared_ptr<tiny_quality::VertexArray> m_VertexArray;

	std::shared_ptr<tiny_quality::Shader> m_BlueShader;
	std::shared_ptr<tiny_quality::VertexArray> m_squareVA;

	tiny_quality::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(tiny_quality::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<tiny_quality::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(tiny_quality::VertexBuffer::Create(vertices, sizeof(vertices)));

		tiny_quality::BufferLayout layout = {
			{ tiny_quality::ShaderDataType::Float3, "a_Position"},
			{ tiny_quality::ShaderDataType::Float4, "a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0,1,2 };
		std::shared_ptr<tiny_quality::IndexBuffer> indexBuffer;
		indexBuffer.reset(tiny_quality::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_squareVA.reset(tiny_quality::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<tiny_quality::VertexBuffer> squareVB;
		squareVB.reset(tiny_quality::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ tiny_quality::ShaderDataType::Float3, "a_Position" }
			});
		m_squareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<tiny_quality::IndexBuffer> squareIB;
		squareIB.reset(tiny_quality::IndexBuffer::Create(squareIndices, sizeof(squareIndices)));
		m_squareVA->SetIndexBuffer(squareIB);


		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main() {
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main() {
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new tiny_quality::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			out vec3 v_Position;

			void main() {
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main() {
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new tiny_quality::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate(tiny_quality::Timestep ts) override
	{

		if (tiny_quality::Input::IsKeyPressed(TQ_KEY_LEFT)) {
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		}
		else if (tiny_quality::Input::IsKeyPressed(TQ_KEY_RIGHT)) {
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		}
		if (tiny_quality::Input::IsKeyPressed(TQ_KEY_UP)) {
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		}
		else if (tiny_quality::Input::IsKeyPressed(TQ_KEY_DOWN)) {
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		}

		if (tiny_quality::Input::IsKeyPressed(TQ_KEY_A)) {
			m_CameraRotation += m_CameraRotationSpeed * ts;
		}
		if (tiny_quality::Input::IsKeyPressed(TQ_KEY_D)) {
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		}

		tiny_quality::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		tiny_quality::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		tiny_quality::Renderer::BeginScene(m_Camera);

		tiny_quality::Renderer::Submit(m_BlueShader, m_squareVA);
		tiny_quality::Renderer::Submit(m_Shader, m_VertexArray);

		tiny_quality::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {

	}

	void OnEvent(tiny_quality::Event& event) override
	{
	}
};

class Sandbox : public tiny_quality::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}
	
	~Sandbox() {

	}
};

tiny_quality::Application* tiny_quality::CreateApplication() {
	return new Sandbox();
}