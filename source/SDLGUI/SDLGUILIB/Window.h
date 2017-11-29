#pragma once

#include <list>
#include <string>
#include <map>
#include <cstdint>
#include <assert.h>

#include "SDLGUILIB_API.h"
#include "Drawable.h"
#include "Event.h"
#include "Utility.h"
#include "EventProcessor.h"

namespace sgl
{
	typedef std::int64_t WindowId;
	class GuiManager;

	class SDLGUILIB_API Window : public Drawable, public EventProcessor
	{
	public:
		static const WindowId kInvalidId = WindowId(-1);

		Window();
		Window(Window* parentWindow);
		~Window();

		virtual WindowId getId() const;
		virtual void addChild(Window& child_window);
		virtual void removeChild(Window& child_window);
		virtual void setParent(Window* new_parent);
		virtual Window* getParent() const;
		virtual void setSize(int width, int height);
		virtual void setSize(Size new_size);
		virtual Size getSize() const;
		virtual void setPosition(int x, int y);
		virtual void setPosition(Point new_position);
		virtual Point getPosition() const;
		virtual void setFocus();
		virtual bool hasFocus() const;
		virtual void setActive(bool is_active);
		virtual bool isActive() const;
		virtual void addEventCallback(EventType event_type, EventCallback handler);
		virtual void removeEventCallback(EventType event_type);

		virtual bool isVisible() const override;
		virtual void setVisible(bool is_visible) override;
		virtual bool handleEvent(const SDL_Event& e) override;

	protected:
		bool canHandleEvent() const;
		bool handleEventByChildren(const SDL_Event& e);
		bool handleMouseButtonDown(const SDL_Event& e);
		bool handleMouseButtonUp(const SDL_Event& e);
		bool handleMouseMotion(const SDL_Event& e);
		bool handleKeyDown(const SDL_Event& e);
		bool isInsideWindowBounds(int x, int y) const;
		Window* getRootParent(Window* window);

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

		WindowId id_;										///< unique identifier for this window
		Size size_;											///< Size of this window in pixels
		Point relative_pos_;								///< Position of this window relative to parent window
		Point screen_pos_;									///< Position of this window in screen (SDL window) coordinates
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
