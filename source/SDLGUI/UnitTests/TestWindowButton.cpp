#include "stdafx.h"

#include <string>

#include "CppUnitTest.h"
#include "../SDLGUILIB/SGL.h"
#include "UserInputGeneration.h"
#include "ExtendedAssert.h"

using namespace std::string_literals;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(TestWindowButton)
	{
	public:
		sgl::GuiManager manager_;
		std::string button_label_;
		sgl::Button button_;
		bool callback_button_was_pressed_ = false;
		bool callback_button_went_down_ = false;
		bool callback_button_went_up_ = false;
		sgl::EventType callback_received_event_type_ = sgl::EventType::Invalid;

		TestWindowButton()
			:manager_{}
			, button_(nullptr, button_label_)
			, button_label_{"Button Label"}
		{
			button_.setSize(200, 200);
			button_.setVisible(true);
			button_.addEventCallback(sgl::EventType::ButtonPressed, [this](const auto& e) {
				callback_button_was_pressed_ = true;
				callback_received_event_type_ = e.type_;
			});
			button_.addEventCallback(sgl::EventType::ButtonDown, [this](const auto& e) {
				callback_button_went_down_ = true;
				callback_received_event_type_ = e.type_;
			});
			button_.addEventCallback(sgl::EventType::ButtonUp, [this](const auto& e) {
				callback_button_went_up_ = true;
				callback_received_event_type_ = e.type_;
			});
			manager_.registerWindow(button_);
		}

		TEST_METHOD(CheckButtonLabel)
		{
			Assert::AreEqual(button_label_, button_.getLabel());

			const auto new_label = "New Button Label"s;
			button_.setLabel(new_label);

			Assert::AreEqual(new_label, button_.getLabel());
		}

		TEST_METHOD(CheckButtonSetLabelAlignment)
		{
			sgl::Button button(nullptr, "Label Text"s);
			manager_.registerWindow(button);
			auto expected_default_alignment = sgl::Alignment::Center;
			Assert::AreEqual(expected_default_alignment, button.getLabelAlignment());

			auto new_alignment = sgl::Alignment::TopRight;
			button.setLabelAlignment(new_alignment);
			Assert::AreEqual(new_alignment, button.getLabelAlignment());
		}

		TEST_METHOD(CheckButtonPressedCallback)
		{
			button_.handleEvent(leftMouseDown(1, 2));

			Assert::IsFalse(callback_button_was_pressed_);

			button_.handleEvent(leftMouseUp(4, 5));

			Assert::IsTrue(callback_button_was_pressed_);
		}

		TEST_METHOD(CheckButtonUpCallback)
		{
			Assert::IsFalse(callback_button_went_up_);

			button_.handleEvent(leftMouseUp(4, 5));

			Assert::IsFalse(callback_button_went_up_);
		}

		TEST_METHOD(CheckNoButtonEventsIfMouseNotOnButton)
		{
			button_.handleEvent(leftMouseDown(301, 302));

			Assert::IsFalse(callback_button_was_pressed_);
			Assert::IsFalse(callback_button_went_down_);
			Assert::IsFalse(callback_button_went_up_);

			button_.handleEvent(leftMouseUp(303, 304));

			Assert::IsFalse(callback_button_was_pressed_);
			Assert::IsFalse(callback_button_went_down_);
			Assert::IsFalse(callback_button_went_up_);
		}

		TEST_METHOD(CheckNoButtonEventsIfNotVisible)
		{
			button_.setVisible(false);

			button_.handleEvent(leftMouseDown(1, 2));

			Assert::IsFalse(callback_button_was_pressed_);
			Assert::IsFalse(callback_button_went_down_);
			Assert::IsFalse(callback_button_went_up_);

			button_.handleEvent(leftMouseUp(4, 5));

			Assert::IsFalse(callback_button_was_pressed_);
			Assert::IsFalse(callback_button_went_down_);
			Assert::IsFalse(callback_button_went_up_);
		}

		TEST_METHOD(CheckNoButtonEventsIfNotActive)
		{
			button_.setActive(false);

			button_.handleEvent(leftMouseDown(1, 2));

			Assert::IsFalse(callback_button_was_pressed_);
			Assert::IsFalse(callback_button_went_down_);
			Assert::IsFalse(callback_button_went_up_);

			button_.handleEvent(leftMouseUp(4, 5));

			Assert::IsFalse(callback_button_was_pressed_);
			Assert::IsFalse(callback_button_went_down_);
			Assert::IsFalse(callback_button_went_up_);
		}

		TEST_METHOD(CheckButtonEventsIfMouseLeavesAfterDown)
		{
			button_.handleEvent(leftMouseDown(1, 2));

			Assert::IsFalse(callback_button_was_pressed_);
			Assert::IsTrue(callback_button_went_down_);
			Assert::IsFalse(callback_button_went_up_);

			button_.handleEvent(leftMouseUp(400, 401));

			Assert::IsFalse(callback_button_was_pressed_);
			Assert::IsTrue(callback_button_went_down_);
			Assert::IsFalse(callback_button_went_up_);
		}

		TEST_METHOD(CheckButtonEventsIfMouseEntersAfterDown)
		{
			button_.handleEvent(leftMouseDown(400, 401));

			Assert::IsFalse(callback_button_was_pressed_);
			Assert::IsFalse(callback_button_went_down_);
			Assert::IsFalse(callback_button_went_up_);

			button_.handleEvent(leftMouseUp(4, 5));

			Assert::IsFalse(callback_button_was_pressed_);
			Assert::IsFalse(callback_button_went_down_);
			Assert::IsFalse(callback_button_went_up_);
		}
	};
}
