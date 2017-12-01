#pragma once

#include "Window.h"

namespace sgl
{
	class SDLGUILIB_API TextLabel : public Window
	{
	public:
		TextLabel();
		TextLabel(Window* parent, const std::string& text);
		virtual std::string getLabel() const;
		virtual void setLabel(const std::string& new_text);
		virtual Alignment getLabelAlignment() const;
		virtual void setLabelAlignment(Alignment alignment);

		virtual void draw(SDL_Renderer* renderer) override;

	protected:
		std::string label_;
		Alignment label_alignment_;
	};
}
