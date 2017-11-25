#pragma once

#include "Window.h"

namespace sgl
{
	class SDLGUILIB_API Frame : public Window
	{
	public:
		Frame(Window* parent, const std::string& title);
		virtual void setTitleBar(bool is_title_bar_visible);
		virtual bool hasTitleBar() const;
		virtual void setTitle(const std::string& title);
		virtual std::string getTitle() const;

		virtual void draw(SDL_Renderer* renderer) override;

	protected:
		std::string title_;
		bool has_title_bar_;							///< If true, this frame has a title bar containing its title at the top
	};
}
