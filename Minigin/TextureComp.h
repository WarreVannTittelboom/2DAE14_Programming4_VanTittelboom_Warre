#pragma once
#include "BaseComp.h"
#include "MiniginPCH.h"

namespace dae
{
	class Texture2D;

	class TextureComp : public BaseComp
	{
	public:
		TextureComp(dae::GameObject* gameObject, const std::string& filename,int w,int h, bool isActive);
		void Initialize() override {  };
		void Render() const override;
		void SetTexture(const std::string& filename);
		bool m_FlipHorizontal{false};
		bool m_FlipVertical{false};
		bool m_IsActive{};
		int m_OffSetX{0};
		int m_OffSetY{0};
	private:
		std::shared_ptr<Texture2D> m_Texture{};
		glm::vec2 m_Size{};
	};
}


