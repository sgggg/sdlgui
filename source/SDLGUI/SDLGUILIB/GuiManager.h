#pragma once

#include "StyleManager.h"
#include "InputHandler.h"
#include "EventProcessor.h"
#include <memory>
#include <list>

namespace sgl
{
	// global functions for GUI control
	void SDLGUILIB_API DrawGui(SDL_Renderer* renderer);
	bool SDLGUILIB_API HandleEvent(SDL_Event* e);


	class Window;
	
	typedef int WindowId;	// TODO remove

	/**
	 * @brief Singleton GuiManager that manages all resources and handles events and input for 
	 * all windows.
	 */
	class GuiManager
	{
	public:
		static GuiManager* GetInstance();

		InputHandler& getInputHandler();
		StyleManager& getStyleManager();
		std::list<Window*>& getWindows();
		void drawGui(SDL_Renderer* renderer);

		void registerWindow(Window* window, WindowId& /* out */ id);
		void unregisterWindow(Window* window);
		void setWindowFocus(Window* windowWithFocus);
		bool hasWindowFocus(const Window* window) const;
		WindowId getAvailableWindowId();

	private:
		GuiManager();
		GuiManager(const GuiManager&) = delete;
		GuiManager& operator=(const GuiManager&) = delete;

		static std::unique_ptr<GuiManager> instance;	///< Singleton instance of GuiManager
		InputHandler inputHandler_;						///< Manager for SDL_Event input
		StyleManager styleManager_;						///< Manages window appearance
		std::list<Window*> windows_;					///< Non-owning pointers to all Window instances
		std::list<Window*> windowStack_;				///< order in which windows are stacked on the screen (first on top) for drawing and input processing
		int64_t windowIdCounter_;						///< TODO temporarily used to generate Window IDs
	};
}
