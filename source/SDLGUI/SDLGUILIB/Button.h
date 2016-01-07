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

		// inherited functions
		virtual void draw(SDL_Renderer* renderer) override;

	protected:
		virtual void triggerClicked() override;
		virtual void triggerDoubleClicked() override;
		virtual void triggerMouseEntered() override;
		virtual void triggerMouseLeft() override;
		virtual void triggerMouseDown() override;
		virtual void triggerMouseUp() override;

		std::string label_;
	};
}
