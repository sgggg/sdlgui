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
			sgl::GuiManager gui_manager;
			sgl::Frame first_frame(nullptr, "First Frame");
			sgl::Frame second_frame(nullptr, "Second Frame");
			sgl::Frame third_frame(nullptr, "Third Frame");
			gui_manager.registerWindow(first_frame);
			gui_manager.registerWindow(second_frame);
			gui_manager.registerWindow(third_frame);

			Assert::IsTrue(first_frame.hasFocus());
			Assert::IsFalse(second_frame.hasFocus());
			Assert::IsFalse(third_frame.hasFocus());
		}

		TEST_METHOD(CheckSwitchingFocusBetweenRootFrames)
		{
			sgl::GuiManager gui_manager;
			sgl::Frame left_frame(nullptr, "Left Frame");
			left_frame.setSize(100, 100);
			left_frame.setPosition(0, 0);
			left_frame.setVisible(true);
			sgl::Frame right_frame(nullptr, "Right Frame");
			right_frame.setSize(100, 100);
			right_frame.setPosition(100, 0);
			right_frame.setVisible(true);

			gui_manager.registerWindow(left_frame);
			gui_manager.registerWindow(right_frame);

			globalClickScreenPosition(gui_manager.getInputHandler(), 150, 50);

			Assert::IsFalse(left_frame.hasFocus());
			Assert::IsTrue(right_frame.hasFocus());

			globalClickScreenPosition(gui_manager.getInputHandler(), 50, 50);

			Assert::IsTrue(left_frame.hasFocus());
			Assert::IsFalse(right_frame.hasFocus());

			globalClickScreenPosition(gui_manager.getInputHandler(), 150, 50);

			Assert::IsFalse(left_frame.hasFocus());
			Assert::IsTrue(right_frame.hasFocus());
		}

		TEST_METHOD(CheckSwitchingFocusBetweenChildWindows)
		{
			sgl::GuiManager gui_manager;
			sgl::Frame frame(nullptr, "Left Frame");
			frame.setSize(300, 300);
			frame.setPosition(0, 0);
			frame.setVisible(true);
			sgl::Button left_button(&frame, "Left Button");
			left_button.setSize(100, 100);
			left_button.setPosition(0, 0);
			left_button.setVisible(true);
			sgl::Button center_button(&frame, "Center Button");
			center_button.setSize(100, 100);
			center_button.setPosition(100, 0);
			center_button.setVisible(true);
			sgl::Button right_button(&frame, "Right Button");
			right_button.setSize(100, 100);
			right_button.setPosition(200, 0);
			right_button.setVisible(true);

			gui_manager.registerWindow(frame);

			globalClickWindow(gui_manager.getInputHandler(), frame);

			Assert::IsTrue(frame.hasFocus());
			Assert::IsFalse(left_button.hasFocus());
			Assert::IsFalse(center_button.hasFocus());
			Assert::IsFalse(right_button.hasFocus());

			globalClickWindow(gui_manager.getInputHandler(), left_button);

			Assert::IsFalse(frame.hasFocus());
			Assert::IsTrue(left_button.hasFocus());
			Assert::IsFalse(center_button.hasFocus());
			Assert::IsFalse(right_button.hasFocus());

			globalClickWindow(gui_manager.getInputHandler(), center_button);

			Assert::IsFalse(frame.hasFocus());
			Assert::IsFalse(left_button.hasFocus());
			Assert::IsTrue(center_button.hasFocus());
			Assert::IsFalse(right_button.hasFocus());

			globalClickWindow(gui_manager.getInputHandler(), right_button);

			Assert::IsFalse(frame.hasFocus());
			Assert::IsFalse(left_button.hasFocus());
			Assert::IsFalse(center_button.hasFocus());
			Assert::IsTrue(right_button.hasFocus());

			globalClickWindow(gui_manager.getInputHandler(), frame);

			Assert::IsTrue(frame.hasFocus());
			Assert::IsFalse(left_button.hasFocus());
			Assert::IsFalse(center_button.hasFocus());
			Assert::IsFalse(right_button.hasFocus());
		}

		TEST_METHOD(CheckWindowWithFocusGetsKeyboardEvents)
		{
			sgl::GuiManager gui_manager;
			sgl::Frame frame(nullptr, "Left Frame");
			frame.setSize(300, 300);
			frame.setPosition(0, 0);
			frame.setVisible(true);
			KeyEventWindow left_event_window(&frame);
			left_event_window.setSize(100, 100);
			left_event_window.setPosition(0, 0);
			left_event_window.setVisible(true);
			KeyEventWindow right_event_window(&frame);
			right_event_window.setSize(100, 100);
			right_event_window.setPosition(100, 0);
			right_event_window.setVisible(true);

			gui_manager.registerWindow(frame);

			globalClickWindow(gui_manager.getInputHandler(), left_event_window);
			auto first_key_press = pressCharacterKey('A');
			gui_manager.getInputHandler().handleEvent(first_key_press);

			Assert::AreEqual(first_key_press.key.keysym.sym, left_event_window.last_received_key_down_.sym);
			Assert::AreEqual(0, right_event_window.last_received_key_down_.sym);

			globalClickWindow(gui_manager.getInputHandler(), right_event_window);
			auto second_key_press = pressCharacterKey('B');
			gui_manager.getInputHandler().handleEvent(second_key_press);

			Assert::AreEqual(first_key_press.key.keysym.sym, left_event_window.last_received_key_down_.sym);
			Assert::AreEqual(second_key_press.key.keysym.sym, right_event_window.last_received_key_down_.sym);

			globalClickWindow(gui_manager.getInputHandler(), left_event_window);
			auto third_key_press = pressCharacterKey('C');
			gui_manager.getInputHandler().handleEvent(third_key_press);

			Assert::AreEqual(third_key_press.key.keysym.sym, left_event_window.last_received_key_down_.sym);
			Assert::AreEqual(second_key_press.key.keysym.sym, right_event_window.last_received_key_down_.sym);
		}
	};
}