#pragma once

#include "Window.h"

namespace sgl
{
	class SDLGUILIB_API Button : public Window
	{
	public:
		Button();
		Button(Window* parent, const std::string& label);
		virtual std::string getLabel() const;
		virtual void setLabel(const std::string& text);

		virtual void draw(SDL_Renderer* renderer) override;

	protected:
		virtual void triggerClicked() override;
		virtual void triggerMouseDown() override;
		virtual void triggerMouseUp() override;

		std::string label_;
	};
}
