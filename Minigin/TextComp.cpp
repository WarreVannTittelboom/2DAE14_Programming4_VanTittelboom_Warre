#include "MiniginPCH.h"
#include "TextComp.h"
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

dae::TextComp::TextComp(dae::GameObject* gameObject, const std::string& text, const std::shared_ptr<Font>& font)
	: BaseComp(gameObject),
	m_Text(text),
	m_Font(font),
	m_Texture(nullptr),
	m_NeedsUpdate(true)
{ }

void dae::TextComp::Update()
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 };
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_Texture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void dae::TextComp::Render() const
{
	if (m_Texture != nullptr)
	{
		const glm::ivec3& pos = m_Transform.GetLocalPosition();

		Renderer::GetInstance().RenderTexture(*m_Texture, static_cast<int>(pos.x), static_cast<int>(pos.y));
	}
}


void dae::TextComp::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComp::SetPos(const float x, const float y)
{
	m_Transform.SetPosition(x, y, 0.f);
}


