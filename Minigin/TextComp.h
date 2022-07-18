#pragma once
#include "BaseComp.h"
#include "GameObject.h"
#include "Transform.h"

namespace dae
{
	class Texture2D;
	class Font;
	class TextComp : public BaseComp
	{
	public:
		explicit TextComp(dae::GameObject* gameObject, const std::string& text, const std::shared_ptr<Font>& font);
		virtual ~TextComp() override = default;
		TextComp(const TextComp& other) = delete;
		TextComp(TextComp&& other) = delete;
		TextComp& operator=(const TextComp& other) = delete;
		TextComp& operator=(TextComp&& other) = delete;

		void Initialize() override {};
		void Update() override;
		void Render() const override;

		void SetText(const std::string& text);
		std::string GetText() const { return m_Text; };

		void SetPos(float x, float y);

	private:
		bool m_NeedsUpdate = true;
		
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_Texture;
		Transform m_Transform;
	};
}
