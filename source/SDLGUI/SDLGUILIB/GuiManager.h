#pragma once

#include "StyleManager.h"
#include "InputHandler.h"
#include "RenderAssistant.h"
#include "EventProcessor.h"
#include <memory>
#include <list>

namespace sgl
{
	// global functions for GUI control
	void SDLGUILIB_API DrawGui(SDL_Renderer* renderer);
	bool SDLGUILIB_API HandleEvent(SDL_Event* e);
	void SDLGUILIB_API SetApplicationTime(int64_t absoluteTime);
	//void SDLGUILIB_API AdvanceApplicationTime(int64_t deltaTime);


	class Window;
	
	typedef int WindowId;	// TODO remove

	/**
	 * @brief Singleton GuiManager that manages all resources and handles events and input for 
	 * all windows.
	 */
	class GuiManager
	{
	public:
		/**
		 * @brief Returns a pointer to the global GUI manager object. If it 
		 * doesn't exist yet, it will be created.
		 * @return Pointer to the global GUI manager. Can not be `nullptr`.
		 */
		static GuiManager* GetInstance();
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
		 * @param window Pointer to the new window instance to register.
		 * @param[out] id Output parameter. The unique window ID the window 
		 * will receive upon registering to the GUI manager.
		 */
		void registerWindow(Window* window, WindowId& /* out */ id);
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
		 * @param windowWithFocus The window that will receive focus.
		 */
		void setWindowFocus(Window* windowWithFocus);
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
		WindowId getAvailableWindowId();
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
		void updateWindowStack();
		void setApplicationTime(int64_t time);
		int64_t getApplicationTime() const;

	private:
		GuiManager();
		GuiManager(const GuiManager&) = delete;
		GuiManager& operator=(const GuiManager&) = delete;

		static std::unique_ptr<GuiManager> instance;	///< Singleton instance of GuiManager
		InputHandler inputHandler_;						///< Manages input through `SDL_Event`s and passes it to the windows according to `windowStack_` order
		StyleManager styleManager_;						///< Manages window appearance
		RenderAssistant renderAssistant_;				///< Provides utility for rendering GUI elements
		std::list<Window*> windows_;					///< Non-owning pointers to all Window instances
		std::list<Window*> windowStack_;				///< Non-owning pointers to all top-level windows. Input to windows and drawing of windows is done according to this list (first item drawn last)
		Window* windowWithFocus_;						///< Points to the window with focus
		int64_t windowIdCounter_;						///< TODO temporarily used to generate Window IDs
		int64_t applicationTime_;						///< saves the current time the GUI uses for all things that need to be timed
	};
}
