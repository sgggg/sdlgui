#include "stdafx.h"

#include <string>

#include "CppUnitTest.h"
#include "../SDLGUILIB/SGL.h"
#include "UserInputGeneration.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	class KeyEventWindow : public sgl::Window
	{
	public:
		SDL_Keysym last_received_key_down_{};

		KeyEventWindow(Window* parent)
			:Window(parent)
		{
		}

		virtual void triggerKeyDown(SDL_Keysym key_symbol) override
		{
			last_received_key_down_ = key_symbol;
		}

		virtual void draw(SDL_Renderer*) override
		{
			// must be overriden
		}
	};

	TEST_CLASS(TestWindowFocus)
	{
	public:
		TEST_METHOD(CheckFirstWindowCreatedHasFocus)
		{
			sgl::Frame first_frame(nullptr, "First Frame");
			sgl::Frame second_frame(nullptr, "Second Frame");
			sgl::Frame third_frame(nullptr, "Third Frame");

			Assert::IsTrue(first_frame.hasFocus());
			Assert::IsFalse(second_frame.hasFocus());
			Assert::IsFalse(third_frame.hasFocus());
		}

		TEST_METHOD(CheckSwitchingFocusBetweenRootFrames)
		{
			sgl::Frame left_frame(nullptr, "Left Frame");
			left_frame.setSize(100, 100);
			left_frame.setPosition(0, 0);
			left_frame.setVisible(true);
			sgl::Frame right_frame(nullptr, "Right Frame");
			right_frame.setSize(100, 100);
			right_frame.setPosition(100, 0);
			right_frame.setVisible(true);

			clickScreenPosition(150, 50);

			Assert::IsFalse(left_frame.hasFocus());
			Assert::IsTrue(right_frame.hasFocus());

			clickScreenPosition(50, 50);

			Assert::IsTrue(left_frame.hasFocus());
			Assert::IsFalse(right_frame.hasFocus());

			clickScreenPosition(150, 50);

			Assert::IsFalse(left_frame.hasFocus());
			Assert::IsTrue(right_frame.hasFocus());
		}

		TEST_METHOD(CheckSwitchingFocusBetweenChildWindows)
		{
			sgl::Frame left_frame(nullptr, "Left Frame");
			left_frame.setSize(100, 100);
			left_frame.setPosition(0, 0);
			left_frame.setVisible(true);
			// TODO create some children of left_frame
			// click around on the frame and check which child has focus

			Assert::Fail(L"Not Implemented");
		}

		TEST_METHOD(CheckWindowWithFocusGetsKeyboardEvents)
		{
			KeyEventWindow window(nullptr);

			Assert::Fail(L"Not Implemented");
		}

		// TODO more tests 
	};
}