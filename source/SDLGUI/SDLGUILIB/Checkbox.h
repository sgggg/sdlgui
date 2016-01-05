#pragma once

#include "Window.h"

namespace sgl
{
	class SDLGUILIB_API Checkbox : public Window
	{
	public:
		Checkbox();
		Checkbox(Window* parent, const std::string& label);

		virtual bool isChecked() const;
		virtual void setChecked(bool isChecked);

		// inherited functions
		virtual void draw(SDL_Renderer* renderer) override;

	protected:
		virtual void triggerClicked();
		virtual void triggerDoubleClicked();
		virtual void triggerMouseEntered();
		virtual void triggerMouseLeft();
		virtual void triggerMouseDown();
		virtual void triggerMouseUp();

		bool isChecked_;						///< `true` if the checkbox is checked
	};
}
