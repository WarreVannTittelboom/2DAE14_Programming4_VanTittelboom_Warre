#include "MiniginPCH.h"
#include "TextureComp.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Timer.h"

dae::TextureComp::TextureComp(dae::GameObject* gameObject, const std::string& filename, int w,int h, bool isActive = true) 
	: BaseComp(gameObject)
	,m_IsActive(isActive)
{
	SetTexture(filename);
	m_Size.x = (float)w;
	m_Size.y = (float)h;
}
void dae::TextureComp::Render() const
{
	if(m_IsActive)
	{
	auto pos = glm::ivec2{ m_pGameObject->GetWorldPosition().x, m_pGameObject->GetWorldPosition().y };
	dae::Renderer::GetInstance().RenderTexture(*m_Texture, SDL_Rect{ 0,0,(int)m_Size.x,(int)m_Size.y }, { pos.x, -pos.y,(int)m_Size.x,(int)m_Size.y }, m_FlipHorizontal, m_FlipVertical);
	}
}

void dae::TextureComp::SetTexture(const std::string& filename)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}
