
#include "stdafx.h"
#include "RadioButton.h"
#include "GuiManager.h"

namespace sgl
{
	RadioButton::RadioButton()
		:Window()
		,label_()
	{
	}

	RadioButton::RadioButton(Window* parent, const std::string& label)
		:Window(parent)
		,label_(label)
		,isChecked_(false)
	{
	}

	std::string RadioButton::getLabel() const
	{
		return label_;
	}

	void RadioButton::setLabel(const std::string& text)
	{
		label_ = text;
	}

	bool RadioButton::isChecked() const
	{
		return isChecked_;
	}

	void RadioButton::setChecked(bool isChecked)
	{
		isChecked_ = isChecked;
	}

	void RadioButton::draw(SDL_Renderer* renderer)
	{
		if (isVisible_)
		{
			auto boxSize = 12;
			auto labelOffset = 8 + boxSize;
			auto colorTheme = manager_->getStyleManager().getColorTheme();
			auto circleCenterX = screenPosX_ + boxSize / 2;
			auto circleCenterY = screenPosY_ + boxSize / 2;
			auto circleRadius = boxSize / 2;

			if (isActive_)
			{
				// draw circle
				if (containsMouse_)
				{
					drawFilledCircle(renderer, circleCenterX, circleCenterY, circleRadius, colorTheme.controlContainsMouse);
				}
				else
				{
					drawFilledCircle(renderer, circleCenterX, circleCenterY, circleRadius, colorTheme.controlBackgroundActive);
				}
				drawCircle(renderer, circleCenterX, circleCenterY, circleRadius, colorTheme.controlFrameActive);
				if (isChecked_)
				{
					drawFilledCircle(renderer, circleCenterX, circleCenterY, circleRadius - 2, colorTheme.controlFrameActive);
				}
				else
				{
					// draw in unchecked state -> no fill
				}
				// draw label next to check box
				renderTextAtPos(renderer, label_, screenPosX_ + labelOffset, screenPosY_ + circleRadius, PosAlign::Left, colorTheme.textActive, colorTheme.textBackground);
			}
			else
			{
				// TODO draw in inactive state (grayed out)
			}
		}
	}

	void RadioButton::triggerClicked()
	{
		isChecked_ = !isChecked_;
		/*auto evhandler = eventhandlers_.find(eventtype::button);
		if (evhandler != std::end(eventhandlers_))
		{
			event e;
			e.type = eventtype::button;
			evhandler->second(e);
		}*/
	}
}