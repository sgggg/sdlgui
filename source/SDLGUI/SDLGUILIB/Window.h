#pragma once

#include "SDLGUILIB_API.h"
#include "Drawable.h"
#include "Utility.h"
#include "EventProcessor.h"
#include <vector>
#include <memory>
#include <string>

namespace sgl
{
	class SDLGUILIB_API Window : public Drawable, EventProcessor
	{
	public:
		Window();
		Window(Window* parentWindow, const std::string& label);
		virtual std::string getLabel() const;
		virtual void setLabel(const std::string& text);
		virtual void addChild(Window& childWindow);
		virtual Window* getParent() const;
		virtual void setSize(int width, int height);
		virtual void setSize(Size size);
		virtual Size getSize() const;
		virtual void setPosition(int x, int y);
		virtual Point getPosition() const;

		// inherited functions
		virtual void draw(SDL_Renderer* renderer) override;
		virtual bool isVisible() override;
		virtual void setVisible(bool isVisible) override;
		virtual bool handleEvent(const SDL_Event& e) override;

	protected:
		// helper functions
		bool isInsideWindowBounds(int x, int y) const;

		std::string label_;							///< label of this window
		int width_;									///< Width of this window in pixels
		int height_;								///< Height of this window in pixels
		int relativePosX_;							///< Position of this window along X axis relative to parent window
		int relativePosY_;							///< Position of this window along Y axis relative to parent window
		int screenPosX_;							///< Position of this window in screen (SDL window) coordinates
		int screenPosY_;							///< Position of this window in screen (SDL window) coordinates
		bool isVisible_;							///< If true, this window and none of the children will be drawn
		bool isActive_;								///< Ignores all received events if window is inactive.
		bool isClicked_;							///< `true` if there was a mouse down event inside this window but no mouse up event yet
		bool containsMouse_;						///< `true` if the mouse pointer is currently inside this window
		Window* parent_;							///< Non-owning pointer to parent window
		std::vector<Window*> children_;				///< Non-owning pointers to all children of this window

	private:
		Window& operator=(const Window&) = delete;
		Window(const Window&) = delete;
	};
}
