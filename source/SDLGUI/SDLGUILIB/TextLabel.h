#pragma once

#include "Window.h"

namespace sgl
{
	enum class HAlignment
	{
		Center	= 0x01,
		Left	= 0x02,
		Right	= 0x03,
	};

	enum class VAlignment
	{
		Center	= 0x10,
		Top		= 0x20,
		Bottom	= 0x30,
	};
	typedef int Alignment;

	Alignment operator|(HAlignment h_align, VAlignment v_align)
	{
		return static_cast<Alignment>(static_cast<int>(h_align) | static_cast<int>(v_align));
	}

	class SDLGUILIB_API TextLabel : public Window
	{
	public:
		TextLabel();
		TextLabel(Window* parent, const std::string& text);
		virtual std::string getText() const;
		virtual void setText(const std::string& new_text);
		virtual void setTextAlignment(Alignment alignment);

		virtual void draw(SDL_Renderer* renderer) override;

	protected:
		std::string text_;
	};
}
