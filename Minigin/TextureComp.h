#pragma once
#include "BaseComp.h"
#include "MiniginPCH.h"

namespace dae
{
	class Texture2D;

	class TextureComp : public BaseComp
	{
	public:
		TextureComp() = delete;
		TextureComp(dae::GameObject* gameObject, const std::string& filename,int w,int h);
		void Render() const override;
		void SetTexture(const std::string& filename);
		bool m_isFlipped{};
	private:
		std::shared_ptr<Texture2D> m_Texture{};
		glm::vec2 m_Size{};
	};
}


