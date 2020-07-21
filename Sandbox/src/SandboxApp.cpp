#include <Reyes.h>

#include <Reyes/Transform.h>
#include <Reyes/Camera.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui/imgui.h>
#include <memory>

#include <Platform/OpenGL/OpenGLShader.h>
#include <Reyes/Text.h>

struct GlyphInfo
{
	glm::vec3 positions[4];
	glm::vec2 texCoords[4];
	glm::vec2 offset;
};

class ExampleLayer : public Reyes::Layer
{
public:
	ExampleLayer()
	{
		using namespace Reyes::RenderAPI;

		m_Texture = Texture2D::Create("assets/textures/redup.png", true, true);

		m_VertexArray = VertexArray::Create();

		auto texWidth = (float)m_Texture->GetWidth();
		auto texHeight = (float)m_Texture->GetHeight();
		float vertices[5 * 4] = {
			-texWidth / 2.f,
			-texHeight / 2.f,
			0.f,
			0.f,
			0.f,
			texWidth / 2.f,
			-texHeight / 2.f,
			0.f,
			1.f,
			0.f,
			texWidth / 2.f,
			texHeight / 2.f,
			0.f,
			1.f,
			1.f,
			-texWidth / 2.f,
			texHeight / 2.f,
			0.f,
			0.f,
			1.f,
		};
		BufferLayout layout = {
			{ShaderDataType::Float3, "i_Position"},
			{ShaderDataType::Float2, "i_TexCoord"},
		};
		m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices), layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		unsigned int indices[6] = {0, 1, 2, 0, 2, 3};
		m_IndexBuffer = IndexBuffer::Create(indices, sizeof(indices));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_Shader = Shader::Create("assets/shaders/Sprite.glsl");

		m_Transform = std::make_shared<Reyes::Transform>("Squar", glm::vec3(), glm::vec3(), glm::vec3(16, 16, 1));

		m_Camera = std::make_shared<Reyes::OrthographicCamera>("Camera");

		m_Shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->SetUniform("u_Texture", 0);

		m_Atlas = AtlasTexture::Create("assets/fonts/Courier.ttf", 50);

		m_TextShader = Shader::Create("assets/shaders/Text.glsl");
		m_TextShader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(m_TextShader)->SetUniform("u_Texture", 0);

		m_TextTransform = std::make_shared<Transform>("Text");
		m_Text = std::make_unique<Text>(m_TextTransform, "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Erat velit scelerisque in dictum non consectetur a erat. Magna etiam tempor orci eu lobortis elementum. Molestie ac feugiat sed lectus. Lectus urna duis convallis convallis tellus id interdum velit. Feugiat in ante metus dictum at tempor commodo ullamcorper a. Sed adipiscing diam donec adipiscing tristique risus nec feugiat. Mauris a diam maecenas sed enim ut sem viverra. Vitae tortor condimentum lacinia quis. Pretium aenean pharetra magna ac placerat vestibulum. Lobortis elementum nibh tellus molestie nunc non. Elit ut aliquam purus sit amet luctus venenatis. Sed lectus vestibulum mattis ullamcorper velit sed ullamcorper. Ac orci phasellus egestas tellus rutrum. Proin fermentum leo vel orci. Ullamcorper morbi tincidunt ornare massa eget egestas purus. Aliquam id diam maecenas ultricies mi eget mauris.", m_Atlas, Reyes::Application::Get().GetWindow().GetSize().x);
	}

	~ExampleLayer() override = default;

	void OnImGuiRender() override
	{
	}

	void OnEvent(Reyes::Event &event) override
	{
		Reyes::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Reyes::WindowResizeEvent>(REY_BIND_EVENT_FN(ExampleLayer::OnWindowResize));
	}
	
	bool OnWindowResize(Reyes::WindowResizeEvent &event)
	{
		m_Text->Resize(event.GetSize().x);

		return false;
	}

	void OnUpdate(float deltaSeconds) override
	{
		if (Reyes::Input::IsKeyDown(REY_KEY_W))
			m_Camera->Translate({0, 200 * deltaSeconds, 0});
		if (Reyes::Input::IsKeyDown(REY_KEY_S))
			m_Camera->Translate({0, -200 * deltaSeconds, 0});
		if (Reyes::Input::IsKeyDown(REY_KEY_D))
			m_Camera->Translate({200 * deltaSeconds, 0, 0});
		if (Reyes::Input::IsKeyDown(REY_KEY_A))
			m_Camera->Translate({-200 * deltaSeconds, 0, 0});
		if (Reyes::Input::IsKeyDown(REY_KEY_LEFT))
			m_Camera->Rotate(45 * deltaSeconds);
		if (Reyes::Input::IsKeyDown(REY_KEY_RIGHT))
			m_Camera->Rotate(-45 * deltaSeconds);

		Reyes::Renderer::Clear();
		Reyes::Renderer::BeginScene(m_Camera);

		// m_Texture->Bind();
		// Reyes::Renderer::Submit(m_VertexArray, m_Transform, m_Shader);

		Reyes::Renderer::EndScene();

		Reyes::Renderer::BeginUI(m_Camera);

		m_Text->GetFontAtlas()->Bind();
		Reyes::Renderer::Submit(m_Text->GetVertexArray(), m_Text->GetTransform(), m_TextShader);

		Reyes::Renderer::EndUI();
	}

private:
	Reyes::Ref<Reyes::RenderAPI::Shader> m_Shader;
	Reyes::Ref<Reyes::RenderAPI::VertexArray> m_VertexArray;
	Reyes::Ref<Reyes::RenderAPI::VertexBuffer> m_VertexBuffer;
	Reyes::Ref<Reyes::RenderAPI::IndexBuffer> m_IndexBuffer;
	Reyes::Ref<Reyes::RenderAPI::Transform> m_Transform;
	Reyes::Ref<Reyes::RenderAPI::Texture2D> m_Texture;
	Reyes::Ref<Reyes::RenderAPI::AtlasTexture> m_Atlas;

	Reyes::Ref<Reyes::RenderAPI::Shader> m_TextShader;
	Reyes::Ref<Reyes::Transform> m_TextTransform;
	Reyes::Scope<Reyes::Text> m_Text;

	Reyes::Ref<Reyes::Camera> m_Camera;

	glm::vec4 m_Color{0.f, 0.f, 1.f, 1.f};
};

class Sandbox : public Reyes::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer);
	}
	~Sandbox() override = default;

	void Render() override {}
};

Reyes::Application *Reyes::CreateApplication()
{
	return new Sandbox;
}