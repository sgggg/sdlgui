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

	protected:
		//virtual void triggerClicked() override;
		//virtual void triggerDoubleClicked() override;
		//virtual void triggerMouseEntered() override;
		//virtual void triggerMouseLeft() override;
		//virtual void triggerMouseDown() override;
		//virtual void triggerMouseUp() override;

		std::string defaultText_;
		std::string currentText_;
	};
}
