#pragma once

#include "Window.h"
#include "InputHandler.h"
#include "StyleManager.h"

namespace sgl
{
	class SDLGUILIB_API Gui : public Window
	{
	public:
		Gui();

		// inherited functions
		virtual bool handleEvent(const SDL_Event& e) override;
		virtual void draw(SDL_Renderer* renderer) override;

		StyleManager& getStyleManager();

	private:
		InputHandler inputManager_;
		StyleManager styleManager_;
	};
}

