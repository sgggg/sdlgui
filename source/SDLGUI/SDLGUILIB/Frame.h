#pragma once

#include "Window.h"

namespace sgl
{
	class SDLGUILIB_API Frame : public Window
	{
	public:
		Frame();
		Frame(Window* parent, const std::string& title);
		virtual void setTitleBarVisible(bool isTitleBarVisible);
		virtual bool hasTitleBar() const;

		virtual void draw(SDL_Renderer* renderer) override;

	protected:
		std::string title_;
		bool hasTitleBar_;							///< If true, this frame has a title bar containing its title at the top
	};
}
