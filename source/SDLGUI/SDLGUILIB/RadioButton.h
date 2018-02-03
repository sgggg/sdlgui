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
		void drawActiveState(SDL_Renderer * renderer, const sgl::Point &circle_center, const int &circle_radius, const int &label_offset);
		virtual void triggerClicked() override;
		void sendCheckedEvent();
		virtual void uncheckSiblingRadioButtons();
		bool hasChangedToChecked(bool was_checked);

		std::string label_;
		bool is_checked_;
	};
}
