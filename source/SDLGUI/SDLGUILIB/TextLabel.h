#pragma once

#include "Window.h"

namespace sgl
{
	/*enum class Alignment
	{
		HCenter	= 0x01,
		Left	= 0x02,
		Right	= 0x04,
		VCenter	= 0x10,
		Top		= 0x20,
		Bottom	= 0x40,
	};

	inline Alignment operator|(Alignment lhs, Alignment rhs)
	{
		return static_cast<Alignment>(static_cast<int>(lhs) | static_cast<int>(rhs));
	}*/

	class SDLGUILIB_API TextLabel : public Window
	{
	public:
		TextLabel();
		TextLabel(Window* parent, const std::string& text);
		virtual std::string getText() const;
		virtual void setText(const std::string& new_text);
		virtual Alignment getTextAlignment() const;
		virtual void setTextAlignment(Alignment alignment);

		virtual void draw(SDL_Renderer* renderer) override;

	protected:
		std::string text_;
		Alignment text_alignment_;
	};
}
