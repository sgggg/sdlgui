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
		std::string defaultText_;			///< stores the text that is shown in the input box when it is empty
		std::string currentText_;			///< stores the text currently entered into the input box
		int cursorPosition_;				///< stores the index into currentText_ where the cursor is positioned.
		int selectionStart_;				///< stores the index into currentText_ where the selection starts if characters are selected.

		// helpers
		void drawCursor(SDL_Renderer* renderer, int relativeX);
		void removeCharacterRange(int leftIndex, int rightIndex);
		void addCharacterRange(int index, const std::string& characters);
		void addCharacter(int index, char character);
	};
}
