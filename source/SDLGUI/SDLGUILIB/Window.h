#pragma once

#include "SDLGUILIB_API.h"
#include "Drawable.h"
#include <vector>
#include <memory>
#include <string>

namespace sgl
{
	class SDLGUILIB_API Window : public Drawable
	{
	public:
		Window();
		virtual std::string getLabel() const;
		virtual void setLabel(const std::string& text);
		~Window();

	private:
		std::vector<std::unique_ptr<Window>> parents_;
		std::vector<std::unique_ptr<Window>> children_;
		std::string label_;

		Window& operator=(const Window&) = delete;
		Window(const Window&) = delete;
	};
}