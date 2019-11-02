#pragma once

#include <memory>
#include <chrono>
#include <list>

#include "StyleManager.h"
#include "InputHandler.h"
#include "IMessageBroker.h"
#include "RenderAssistant.h"
#include "EventProcessor.h"
#include "Common.h"

namespace sgl
{
	/**
	 * @brief Singleton GuiManager that manages all resources and handles events and input for 
	 * all windows.
	 */
	class SDLGUILIB_API GuiManager : public IMessageBroker
	{
	public:
		GuiManager();
		///< @todo check if we can undelete these
		GuiManager(const GuiManager&) = delete;
		GuiManager(GuiManager&&) = delete;
		GuiManager& operator=(const GuiManager&) = delete;
		GuiManager& operator=(GuiManager&&) = delete;
		~GuiManager();
		/**
		 * @brief Returns a reference to the input handler.
		 * @return Reference to the input handler.
		 */
		InputHandler& getInputHandler();
		/**
		 * @brief Returns a reference to the style manager.
		 * @return Reference to the style manager.
		 */
		StyleManager& getStyleManager();
		/**
		* @brief Returns a reference to the render assistant.
		* @return Reference to the render assistant.
		*/
		RenderAssistant& getRenderAssistant();
		/*
		 * @brief Returns a reference to the window stack.
		 * @return Reference to the window stack.
		 */
		std::list<Window*>& getWindowStack();
		/**
		 * @brief Draws the entire GUI to the given renderer.
		 * @param renderer `SDL_Renderer` the GUI elements will be drawn to.
		 */
		void drawGui(SDL_Renderer* renderer);
		/**
		 * @brief Register the given window to the manager.
		 * 
		 * Each window _must_ be registered after contruction to the GUI manager so
		 * it can be drawn and receive input, etc.
		 * @param window Reference to the new window instance to register.
		 * will receive upon registering to the GUI manager.
		 */
		void registerWindow(Window& window) override;
		/**
		 * @brief Unregisters the given window from the GUI manager.
		 * 
		 * Each window must be unregistered before it is destroyed. This should be done
		 * in a windows destructor. After this, the window will no longer receive 
		 * input or be drawn to the screen.
		 * @param window Pointer to the window to unregister.
		 */
		void unregisterWindow(Window* window);
		/** 
		 * @brief Sets focus to the given window.
		 * 
		 * Since only one window can have focus at a time, the GUI manager handles window
		 * focus for all windows. If a window should gain focus, it can call this function
		 * to gain focus from the manager, who also removes focus from the window that had
		 * focus before.
		 * @param window_with_focus The window that will receive focus.
		 */
		void setWindowFocus(Window* window_with_focus);
		/** 
		 * @brief Returns `true` if the given window has focus.
		 * 
		 * This function can be used by any window to find out if a given window has focus.
		 * @param window Pointer to the window to check for focus.
		 * @return Returns `true` if the window given in `window` currently has window focus,
		 * `false` otherwise.
		 */
		bool hasWindowFocus(const Window* window) const;
		/** 
		 * @brief Returns a new, unused window ID.
		 * @return A newly generated window ID, not used by any other window
		 */
		static WindowId getAvailableWindowId();
		/** 
		 * @brief Release the given window ID.
		 * 
		 * This should be called whenever a window ID is no longer used, e.g. because its window
		 * is destroyed or because it was assigned a new ID.
		 * @param id Window ID to release.
		 */
		void freeWindowId(WindowId id);
		/** 
		 * @brief Moves the given top-level window to the top of the window stack.
		 *
		 * The given window must be a top-level window, this means it can not have a parent.
		 * Moving a window to the top of the window stack, makes it the first window to receive 
		 * user input and the window that is drawn on top of all other top-level windows.
		 * @param window Pointer to the window to be moved to the top of the window stack.
		 */
		void stackOnTop(Window* window);
		/**
		 * @brief Recalculates the window stack from scratch.
		 *
		 * Usually this is only necessary if the child/parent relationships of windows change. In that case
		 * recalculating the windows stack ensures that a child window is always drawn on top of its parent.
		 */
		void updateWindowStack();
		/**
		* @brief Set the current application time.
		*
		* The application time is used for animations and timed events.
		* @param New application time in milliseconds.
		*/
		void setApplicationTime(std::chrono::milliseconds time);
		/**
		 * @brief Get the current application time previously set by `setApplicationTime()`.
		 *
		 * The application time is used for animations and timed events.
		 * @return Application time in milliseconds.
		 */
		std::chrono::milliseconds getApplicationTime() const;
		void dispatch(Event&& event);

	private:
		InputHandler input_handler_;					///< Manages input through `SDL_Event`s and passes it to the windows according to `window_stack_` order
		StyleManager style_manager_;					///< Manages window appearance
		RenderAssistant render_assistant_;				///< Provides utility for rendering GUI elements
		std::list<Window*> windows_;					///< Non-owning pointers to all Window instances
		std::list<Window*> window_stack_;				///< Non-owning pointers to all top-level windows. Input to windows and drawing of windows is done according to this list (first item drawn last)
		Window* window_with_focus_;						///< Points to the window with focus
		int64_t window_id_counter_;						///< TODO temporarily used to generate Window IDs
		std::chrono::milliseconds application_time_;	///< saves the current time the GUI uses for all things that need to be timed
	};
}
