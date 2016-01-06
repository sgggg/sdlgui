#include "stdafx.h"
#include "Checkbox.h"
#include "Gui.h"

namespace sgl
{
	Checkbox::Checkbox()
		:Window()
		,isChecked_(false)
	{
	}

	Checkbox::Checkbox(Window* parent, const std::string& label)
		:Window(parent, label)
		,isChecked_(false)
	{
	}

	bool Checkbox::isChecked() const
	{
		return isChecked_;
	}

	void Checkbox::setChecked(bool isChecked)
	{
		isChecked_ = isChecked;
	}

	void Checkbox::triggerClicked()
	{
		isChecked_ = !isChecked_;
		std::cout << "Checkbox is now " << ((isChecked_) ? "checked!" : "unchecked!") << std::endl;
	}

	void Checkbox::triggerDoubleClicked()
	{
	}

	void Checkbox::triggerMouseEntered()
	{
	}

	void Checkbox::triggerMouseLeft()
	{
	}

	void Checkbox::triggerMouseDown()
	{
	}

	void Checkbox::triggerMouseUp()
	{
	}

	void Checkbox::draw(SDL_Renderer* renderer)
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

}