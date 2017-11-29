#pragma once

#include "Window.h"

namespace sgl
{
	class SDLGUILIB_API TextLabel : public Window
	{
	public:
		TextLabel();
		TextLabel(Window* parent, const std::string& text);
		virtual std::string getText() const;
		virtual void setText(const std::string& new_text);

		virtual void draw(SDL_Renderer* renderer) override;

	protected:
		std::string text_;
	};
}
