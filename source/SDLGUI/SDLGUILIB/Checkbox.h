#pragma once

#include "Window.h"

namespace sgl
{
	class SDLGUILIB_API Checkbox : public Window
	{
	public:
		Checkbox();
		Checkbox(Window* parent, const std::string& label);

		virtual std::string getLabel() const;
		virtual void setLabel(const std::string& text);
		virtual bool isChecked() const;
		virtual void setChecked(bool isChecked);

		// inherited functions
		virtual void draw(SDL_Renderer* renderer) override;

	protected:
		virtual void triggerClicked() override;
		virtual void triggerDoubleClicked() override;
		virtual void triggerMouseEntered() override;
		virtual void triggerMouseLeft() override;
		virtual void triggerMouseDown() override;
		virtual void triggerMouseUp() override;

		std::string label_;						///< label of the checkbox
		bool isChecked_;						///< `true` if the checkbox is checked
	};
}
