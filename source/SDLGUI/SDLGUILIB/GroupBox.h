#pragma once

#include "Window.h"

namespace sgl
{
	class SDLGUILIB_API GroupBox : public Window
	{
	public:
		GroupBox();
		GroupBox(Window* parent);
		virtual std::string getLabel() const;
		virtual void setLabel(const std::string& new_text);

		virtual void draw(SDL_Renderer* renderer) override;

	protected:
		std::string label_;
	};
}
