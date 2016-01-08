#pragma once

#include "Window.h"

namespace sgl
{
	class SDLGUILIB_API RadioButton : public Window
	{
	public:
		RadioButton();
		RadioButton(Window* parent, const std::string& label);
		virtual void setLabel(const std::string& text);

		// inherited functions
		virtual void draw(SDL_Renderer* renderer) override;

		virtual void triggerClicked() override;
		virtual void triggerDoubleClicked() override;
		virtual void triggerMouseEntered() override;
		virtual void triggerMouseLeft() override;
		virtual void triggerMouseDown() override;
		virtual void triggerMouseUp() override;

	protected:
		std::string label_;
		bool isChecked_;
	};
}
