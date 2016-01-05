#include "stdafx.h"
#include "Checkbox.h"

namespace sgl
{
	Checkbox::Checkbox()
		:Window()
	{
	}

	Checkbox::Checkbox(Window* parent, const std::string& label)
		:Window(parent, label)
	{
		parent->addChild(*this); 
	}

	bool Checkbox::isChecked()
	{
		return isChecked_;
	}

	void Checkbox::triggerClicked()
	{
		isChecked_ = !isChecked_;
		std::cout << "Checkbox is now " << ((isChecked_) ? "checked!" : "unchecked!") << std::endl;
	}

	void Checkbox::triggerDoubleClicked()
	{
		// do nothing
	}

	void Checkbox::triggerMouseEntered()
	{
		//std::cout << "Button " << label_ << ": mouse entered" << std::endl;
	}

	void Checkbox::triggerMouseLeft()
	{
		//std::cout << "Button " << label_ << ": mouse left" << std::endl;
	}

	void Checkbox::triggerMouseDown()
	{
		//std::cout << "Window " << label_ << ": mouse down" << std::endl;
	}

	void Checkbox::triggerMouseUp()
	{
		//std::cout << "Window " << label_ << ": mouse up" << std::endl;
	}

	void Checkbox::draw(SDL_Renderer* renderer)
	{
		if (isVisible_)
		{
			SDL_Rect outlineRect = { screenPosX_, screenPosY_, width_, height_ }; //draw gray outline
			SDL_SetRenderDrawColor(renderer, 0xC0, 0xC0, 0xC0, 0xFF);
			SDL_RenderDrawRect(renderer, &outlineRect);

			renderTextAtPos(renderer, label_, screenPosX_, screenPosY_, { 0,0,0 }, { 0xC0, 0xC0, 0xC0 });
			if (isActive_)
			{
				if (isChecked_)
				{
					// TODO draw checkbox in checked state
				}
				else
				{
					// TODO draw checkbox in unchecked state
				}
				// TODO draw checkbox label
			}
			else
			{
				// TODO draw checkbox in inactive state (grayed out)
			}
		}
	}

}