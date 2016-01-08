
#include "stdafx.h"
#include "RadioButton.h"
#include "Gui.h"

namespace sgl
{
	RadioButton::RadioButton()
		:Window()
		, label_()
	{
	}

	RadioButton::RadioButton(Window* parent, const std::string& label)
		: Window(parent)
		, label_(label)
		, isChecked_(false)
	{
	}

	void RadioButton::setLabel(const std::string& text)
	{
		label_ = text;
	}

	void RadioButton::draw(SDL_Renderer* renderer)
	{
		if (isVisible_)
		{
			auto boxSize = 12;
			auto labelOffset = 8 + boxSize;
			auto colorTheme = guiRoot_->getStyleManager().getColorTheme();

			if (isActive_)
			{
				// draw box
				if (containsMouse_)
				{
					drawFilledRectangle(renderer, screenPosX_, screenPosY_, boxSize, boxSize, colorTheme.controlContainsMouse);
				}
				else
				{
					drawFilledRectangle(renderer, screenPosX_, screenPosY_, boxSize, boxSize, colorTheme.controlBackgroundActive);
				}
				drawRectangle(renderer, screenPosX_, screenPosY_, boxSize, boxSize, colorTheme.controlFrameActive);
				if (isChecked_)
				{
					// draw checkbox in checked state
					drawFilledRectangle(renderer, screenPosX_ + 2, screenPosY_ + 2, boxSize - 4, boxSize - 4, colorTheme.controlFrameActive);
				}
				else
				{
					// draw checkbox in unchecked state -> no fill
				}
				// draw label next to check box
				renderTextAtPos(renderer, label_, screenPosX_ + labelOffset, screenPosY_ + boxSize / 2, PosAlign::Left, colorTheme.textActive, colorTheme.textBackground);
			}
			else
			{
				// TODO draw checkbox in inactive state (grayed out)
			}
		}
	}

	void RadioButton::triggerClicked()
	{
		/*auto evhandler = eventhandlers_.find(eventtype::button);
		if (evhandler != std::end(eventhandlers_))
		{
			event e;
			e.type = eventtype::button;
			evhandler->second(e);
		}*/
	}

	void RadioButton::triggerDoubleClicked()
	{
		// do nothing
	}

	void RadioButton::triggerMouseEntered()
	{
		//std::cout << "RadioButton " << label_ << ": mouse entered" << std::endl;
	}

	void RadioButton::triggerMouseLeft()
	{
		//std::cout << "RadioButton " << label_ << ": mouse left" << std::endl;
	}

	void RadioButton::triggerMouseDown()
	{
		//std::cout << "Window " << label_ << ": mouse down" << std::endl;
	}

	void RadioButton::triggerMouseUp()
	{
		//std::cout << "Window " << label_ << ": mouse up" << std::endl;
	}
}