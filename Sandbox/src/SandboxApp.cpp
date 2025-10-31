#include <tiny_quality.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public tiny_quality::Layer
{
private:
	tiny_quality::Ref<tiny_quality::Shader> m_Shader;
	tiny_quality::Ref<tiny_quality::VertexArray> m_VertexArray;

	tiny_quality::Ref<tiny_quality::Shader> m_FlatColorShader, m_TextureShader;
	tiny_quality::Ref<tiny_quality::VertexArray> m_squareVA;

	tiny_quality::Ref<tiny_quality::Texture2D> m_Texture, m_ChernoLogoTexture;

	tiny_quality::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
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

		tiny_quality::Ref<tiny_quality::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(tiny_quality::VertexBuffer::Create(vertices, sizeof(vertices)));

		tiny_quality::BufferLayout layout = {
			{ tiny_quality::ShaderDataType::Float3, "a_Position"},
			{ tiny_quality::ShaderDataType::Float4, "a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0,1,2 };
		tiny_quality::Ref<tiny_quality::IndexBuffer> indexBuffer;
		indexBuffer.reset(tiny_quality::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_squareVA.reset(tiny_quality::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		tiny_quality::Ref<tiny_quality::VertexBuffer> squareVB;
		squareVB.reset(tiny_quality::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ tiny_quality::ShaderDataType::Float3, "a_Position" },
			{ tiny_quality::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_squareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		tiny_quality::Ref<tiny_quality::IndexBuffer> squareIB;
		squareIB.reset(tiny_quality::IndexBuffer::Create(squareIndices, sizeof(squareIndices)));
		m_squareVA->SetIndexBuffer(squareIB);


		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main() {
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

		m_Shader.reset(tiny_quality::Shader::Create(vertexSrc, fragmentSrc));

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main() {
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			
			uniform vec3 u_Color;

			void main() {
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader.reset(tiny_quality::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));

		m_TextureShader.reset(tiny_quality::Shader::Create("assets/shaders/Texture.glsl"));

		m_Texture = tiny_quality::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoLogoTexture = tiny_quality::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<tiny_quality::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<tiny_quality::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
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

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<tiny_quality::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<tiny_quality::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for(int y = 0; y<20; y++) {
			for (int x = 0; x < 20; x++) {
				glm::vec3 pos(x * 0.11f, y * 0.11f , 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				tiny_quality::Renderer::Submit(m_FlatColorShader, m_squareVA, transform);
			}
		}

		//m_Texture->Bind();
		//tiny_quality::Renderer::Submit(m_TextureShader, m_squareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		//m_ChernoLogoTexture->Bind();
		//tiny_quality::Renderer::Submit(m_TextureShader, m_squareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// triangle
		//tiny_quality::Renderer::Submit(m_Shader, m_VertexArray);

		tiny_quality::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
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