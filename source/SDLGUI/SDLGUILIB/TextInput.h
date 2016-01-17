#pragma once

#include "Window.h"


namespace sgl
{
	class SDLGUILIB_API TextInput : public Window
	{
	public:
		TextInput();
		TextInput(Window* parent, const std::string& defaultText);
		virtual std::string getText() const;
		virtual void setText(const std::string& newText);

		// inherited functions
		virtual void draw(SDL_Renderer* renderer) override;
		virtual void triggerKeyDown(SDL_Keycode keycode) override;

	protected:
		std::string defaultText_;
		std::string currentText_;
	};
}
