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

	class SDLGUILIB_API Window : public Drawable, public EventProcessor
	{
	public:
		Window();
		Window(Window* parentWindow);
		~Window();

		virtual WindowId GetId() const;
		virtual void addChild(Window& child_window);
		virtual void removeChild(Window& child_window);
		virtual void setParent(Window* new_parent);
		virtual Window* getParent() const;
		virtual void setSize(int width, int height);
		virtual Size getSize() const;
		virtual void setPosition(int x, int y);
		virtual Point getPosition() const;
		virtual void setFocus();
		virtual bool hasFocus() const;
		virtual void setActive(bool is_active);
		virtual bool isActive() const;
		virtual void addEventCallback(EventType event_type, EventCallback handler);
		virtual void removeEventCallback(EventType event_type);

		// inherited functions
		virtual bool isVisible() override;
		virtual void setVisible(bool is_visible) override;
		virtual bool handleEvent(const SDL_Event& e) override;

	protected:
		bool handleEventByChildren(const SDL_Event& e);
		bool handleMouseButtonDown(const SDL_Event& e);
		bool handleMouseButtonUp(const SDL_Event& e);
		bool handleMouseMotion(const SDL_Event& e);
		bool handleKeyDown(const SDL_Event& e);

		friend GuiManager;
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
		virtual void triggerKeyDown(SDL_Keysym key);

		// helper functions
		bool isInsideWindowBounds(int x, int y) const;
		Window* getRootParent(Window* window);

		WindowId id_;										///< unique identifier for this window
		int width_;											///< Width of this window in pixels
		int height_;										///< Height of this window in pixels
		int relative_pos_x_;								///< Position of this window along X axis relative to parent window
		int relative_pos_y_;								///< Position of this window along Y axis relative to parent window
		int screen_pos_x_;									///< Position of this window in screen (SDL window) coordinates
		int screen_pos_y_;									///< Position of this window in screen (SDL window) coordinates
		bool is_visible_;									///< If true, this window and none of the children will be drawn
		bool is_active_;									///< Ignores all received events if window is inactive.
		bool is_clicked_;									///< `true` if there was a mouse down event inside this window but no mouse up event yet
		bool contains_mouse_;								///< `true` if the mouse pointer is currently inside this window
		Window* parent_;									///< Non-owning pointer to parent window
		std::list<Window*> children_;						///< Non-owning pointers to all children of this window
		std::map<EventType, EventCallback> event_handlers_;	///< List of registered event callback functions
		GuiManager* manager_;								///< Non-owning pointer to the global GUI manager

	private:
		Window& operator=(const Window&) = delete;
		Window(const Window&) = delete;
	};
}
