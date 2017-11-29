#pragma once

#include "SDLGUILIB_API.h"
#include "SDL.h"

namespace sgl
{
	/**
	 * @brief Interface that must be implemented by all objects that can be drawn to
	 * an `SDL_Renderer`.
	 * @see SDL_Renderer
	 */
	class SDLGUILIB_API Drawable
	{
	public:
		/**
		 * @brief Draw this object to the given renderer.
		 * 
		 * This function should be implemented in a way that only if `is_visible()` returns
		 * `true`, this object is drawn to the passed renderer.
		 * @param renderer SDL renderer object this object will be drawn onto.
		 */
		virtual void draw(SDL_Renderer* renderer) = 0;
		/** 
		 * @brief Returns the visibility state of this object.
		 * 
		 * An invisible object should not be drawn when its `draw()` function is called.
		 */
		virtual bool isVisible() const = 0;
		/**
		 * @brief Set the visibility of this object.
		 * 
		 * @param is_visible If `true`, this object will be drawn to the renderer with the 
		 * next call to `draw()`. If `false`, drawing this object will have no effect.
		 */
		virtual void setVisible(bool is_visible) = 0;
		virtual ~Drawable() = default;
	};
}