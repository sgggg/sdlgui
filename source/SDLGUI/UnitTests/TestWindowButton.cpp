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
		std::string button_label_;
		sgl::Button button_;
		bool callback_button_was_pressed_ = false;
		sgl::EventType callback_received_event_type_ = sgl::EventType::Invalid;

		TestWindowButton()
			:button_label_("Button Label")
			,button_(nullptr, button_label_)
		{
			button_.setSize(300, 80);
			button_.setVisible(true);
			button_.addEventCallback(sgl::EventType::ButtonPressed, [this](const auto& e) {
				callback_button_was_pressed_ = true;
				callback_received_event_type_ = e.type_;
			});
		}

		TEST_METHOD(CheckButtonLabel)
		{
			Assert::AreEqual(button_label_, button_.getLabel());

			auto new_label = "New Button Label"s;
			button_.setLabel(new_label);

			Assert::AreEqual(new_label, button_.getLabel());
		}

		TEST_METHOD(CheckButtonPressedCallback)
		{
			button_.handleEvent(leftMouseDown(1, 2));

			Assert::IsFalse(callback_button_was_pressed_);
			Assert::AreEqual(sgl::EventType::Invalid, callback_received_event_type_);

			button_.handleEvent(leftMouseUp(4, 5));

			Assert::IsTrue(callback_button_was_pressed_);
			Assert::AreEqual(sgl::EventType::ButtonPressed, callback_received_event_type_);
		}

		TEST_METHOD(CheckButtonNotPressedIfMouseNotOnButton)
		{
			button_.handleEvent(leftMouseDown(301, 302));

			Assert::IsFalse(callback_button_was_pressed_);

			button_.handleEvent(leftMouseUp(303, 304));

			Assert::IsFalse(callback_button_was_pressed_);
		}

		TEST_METHOD(CheckButtonNotPressedIfNotVisible)
		{
			button_.setVisible(false);

			button_.handleEvent(leftMouseDown(1, 2));

			Assert::IsFalse(callback_button_was_pressed_);

			button_.handleEvent(leftMouseUp(4, 5));

			Assert::IsFalse(callback_button_was_pressed_);
		}

		TEST_METHOD(CheckButtonNotPressedIfNotActive)
		{
			button_.setActive(false);

			button_.handleEvent(leftMouseDown(1, 2));

			Assert::IsFalse(callback_button_was_pressed_);

			button_.handleEvent(leftMouseUp(4, 5));

			Assert::IsFalse(callback_button_was_pressed_);
		}

		TEST_METHOD(CheckButtonNotPressedIfMouseLeavesAfterDown)
		{
			button_.handleEvent(leftMouseDown(401, 402));

			Assert::IsFalse(callback_button_was_pressed_);

			button_.handleEvent(leftMouseUp(4, 5));

			Assert::IsFalse(callback_button_was_pressed_);
		}

		TEST_METHOD(CheckButtonNotPressedIfMouseEntersAfterDown)
		{
			button_.handleEvent(leftMouseDown(1, 2));

			Assert::IsFalse(callback_button_was_pressed_);

			button_.handleEvent(leftMouseUp(404, 405));

			Assert::IsFalse(callback_button_was_pressed_);
		}
	};
}
