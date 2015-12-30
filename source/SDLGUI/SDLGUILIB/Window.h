#pragma once

#include "SDLGUILIB_API.h"
#include "Drawable.h"
#include "Utility.h"
#include <vector>
#include <memory>
#include <string>

namespace sgl
{
	class SDLGUILIB_API Window : public Drawable
	{
	public:
		Window();
		Window(Window* parentWindow, const std::string& label);
		virtual std::string getLabel() const;
		virtual void setLabel(const std::string& text);
		virtual void addChild(Window* childWindow);
		virtual Window* getParent() const;
		virtual void setSize(int width, int height);
		virtual void setSize(Size size);
		virtual Point getSize() const;

		// inherited methods
		virtual void draw() override;
		virtual void setCanvas(SDL_Window& canvas) override;
		virtual bool isVisible() override;
		virtual void setVisible(bool isVisible) override;

	private:
		std::string label_;							///< label of this window
		int width_;									///< Width of this window in pixels
		int height_;								///< Height of this window in pixels
		int posX_;									///< Position of this window along X axis relative to parent
		int posY_;									///< Position of this window along Y axis relative to parent
		bool isVisible_;							///< If true, window any none of the children will be drawn
		bool isActive_;
		Window* parent_;							///< Non-owning pointer to parent window
		std::vector<Window*> children_;				///< owning pointers to all children of this window
		SDL_Window* canvas_;						///< The SDL surface the window will be drawn onto

		Window& operator=(const Window&) = delete;
		Window(const Window&) = delete;
	};
}
