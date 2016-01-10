#pragma once

#include "SDLGUILIB_API.h"
#include "Drawable.h"
#include "Event.h"
#include "Utility.h"
#include "EventProcessor.h"
#include <list>
#include <memory>
#include <string>
#include <functional>
#include <map>

namespace sgl
{
	typedef int WindowId;
	class GuiManager;

	class SDLGUILIB_API Window : public Drawable, EventProcessor
	{
	public:
		Window();
		Window(Window* parentWindow);
		~Window();

		virtual WindowId GetId() const;
		virtual void addChild(Window& childWindow);
		virtual void removeChild(Window& childWindow);
		virtual void setParent(Window* newParent);
		virtual Window* getParent() const;
		virtual void setSize(int width, int height);
		virtual Size getSize() const;
		//virtual void setSizeFixed(bool isFixed);
		virtual void setPosition(int x, int y);
		virtual Point getPosition() const;
		//virtual void setPositionFixed(bool isFixed);
		virtual void setFocus();
		virtual bool hasFocus() const;
		virtual void setActive(bool isActive);
		virtual bool isActive() const;
		virtual void addEventCallback(EventType eventType, EventCallback handler);
		virtual void removeEventCallback(EventType eventType);

		// inherited functions
		virtual bool isVisible() override;
		virtual void setVisible(bool isVisible) override;
		virtual bool handleEvent(const SDL_Event& e) override;

	protected:
		// event generating functions
		virtual void triggerClicked();
		virtual void triggerDoubleClicked();
		virtual void triggerMouseEntered();
		virtual void triggerMouseLeft();
		virtual void triggerMouseDown();
		virtual void triggerMouseUp();
		virtual void triggerFocusGained();
		virtual void triggerFocusLost();
		virtual void triggerWindowResize();

		// helper functions
		bool isInsideWindowBounds(int x, int y) const;
		Window* getRootParent(Window* window);

		WindowId id_;										///< unique identifier for this window
		int width_;											///< Width of this window in pixels
		int height_;										///< Height of this window in pixels
		//bool isSizeFixed_;									///< If `true`, window can not be resized
		int relativePosX_;									///< Position of this window along X axis relative to parent window
		int relativePosY_;									///< Position of this window along Y axis relative to parent window
		int screenPosX_;									///< Position of this window in screen (SDL window) coordinates
		int screenPosY_;									///< Position of this window in screen (SDL window) coordinates
		//bool isPositionFixed_;								///< If `true`, window position can not be changed (ignored if parent is moved)
		bool isVisible_;									///< If true, this window and none of the children will be drawn
		bool isActive_;										///< Ignores all received events if window is inactive.
		bool isClicked_;									///< `true` if there was a mouse down event inside this window but no mouse up event yet
		bool hasFocus_;										///< `true` if this window is the one currently receiving keyboard input
		bool containsMouse_;								///< `true` if the mouse pointer is currently inside this window
		Window* parent_;									///< Non-owning pointer to parent window
		std::list<Window*> children_;						///< Non-owning pointers to all children of this window
		std::map<EventType, EventCallback> eventHandlers_;	///< List of registered event callback functions
		GuiManager* manager_;								///< Non-owning pointer to the global GUI manager

	private:
		Window& operator=(const Window&) = delete;
		Window(const Window&) = delete;
	};
}
