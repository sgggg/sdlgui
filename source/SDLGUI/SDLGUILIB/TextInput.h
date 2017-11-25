#pragma once

#include "Window.h"


namespace sgl
{
	class SDLGUILIB_API TextInput : public Window
	{
	public:
		TextInput();
		TextInput(Window* parent, const std::string& default_text);
		virtual std::string getText() const;
		virtual void setText(const std::string& new_text);

		// inherited functions
		virtual void draw(SDL_Renderer* renderer) override;
		virtual void triggerKeyDown(SDL_Keysym key) override;

	protected:
		std::string default_text_;			///< stores the text that is shown in the input box when it is empty
		std::string current_text_;			///< stores the text currently entered into the input box
		int cursor_position_;				///< stores the index into current_text_ where the cursor is positioned.
		int selection_start_;				///< stores the index into current_text_ where the selection starts if characters are selected.

		// helpers
		void drawCursor(SDL_Renderer* renderer, int relative_x);
		void removeCharacterRange(int left_index, int right_index);
		void addCharacterRange(int index, const std::string& characters);
		void addCharacter(int index, char character);
	};
}
