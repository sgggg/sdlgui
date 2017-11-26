#pragma once

#include "Window.h"

namespace sgl
{
	class SDLGUILIB_API RadioButton : public Window
	{
	public:
		RadioButton();
		RadioButton(Window* parent, const std::string& label);

		virtual std::string getLabel() const;
		virtual void setLabel(const std::string& text);
		virtual bool isChecked() const;
		virtual void setChecked(bool is_checked);

		virtual void draw(SDL_Renderer* renderer) override;

	protected:
		virtual void triggerClicked() override;

		std::string label_;
		bool is_checked_;
	};
}
