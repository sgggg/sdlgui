#pragma once

#include "Window.h"


namespace sgl
{
	class SDLGUILIB_API TextInput : public Window
	{
	public:
		TextInput();
		TextInput(Window* parent, const std::string& defaultText);

		// inherited functions
		virtual void draw(SDL_Renderer* renderer) override;

	protected:
		//virtual void triggerClicked();
		//virtual void triggerDoubleClicked();
		//virtual void triggerMouseEntered();
		//virtual void triggerMouseLeft();
		//virtual void triggerMouseDown();
		//virtual void triggerMouseUp();*/
	};
}
