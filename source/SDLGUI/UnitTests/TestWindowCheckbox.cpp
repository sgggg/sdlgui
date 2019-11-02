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
	TEST_CLASS(TestWindowCheckbox)
	{
	public:
		std::string checkbox_label_;
		sgl::GuiManager manager_;
		sgl::Checkbox checkbox_;
		bool callback_was_checked_ = false;
		bool callback_was_unchecked_ = false;

		TestWindowCheckbox()
			:checkbox_label_{ "Label Text" }
			, checkbox_{nullptr, checkbox_label_}
		{
			checkbox_.setSize(200, 80);
			checkbox_.setVisible(true);
			checkbox_.addEventCallback(sgl::EventType::Checked, [this](const auto& e) {
				callback_was_checked_ = true;
			});
			checkbox_.addEventCallback(sgl::EventType::Unchecked, [this](const auto& e) {
				callback_was_unchecked_ = true;
			});
			manager_.registerWindow(checkbox_);
		}

		TEST_METHOD(CheckSetAndGetLabelText)
		{
			Assert::AreEqual(checkbox_label_, checkbox_.getLabel());

			checkbox_label_ = "new label text"s;
			checkbox_.setLabel(checkbox_label_);

			Assert::AreEqual(checkbox_label_, checkbox_.getLabel());
		}

		TEST_METHOD(CheckSetCheckedAndUnchecked)
		{
			Assert::IsFalse(checkbox_.isChecked());

			checkbox_.setChecked(true);

			Assert::IsTrue(checkbox_.isChecked());

			checkbox_.setChecked(false);

			Assert::IsFalse(checkbox_.isChecked());
		}
		
		TEST_METHOD(CheckCheckboxCheckedUncheckedCallback)
		{
			Assert::IsFalse(callback_was_checked_);
			Assert::IsFalse(callback_was_unchecked_);

			localClickWindow(checkbox_);

			Assert::IsTrue(callback_was_checked_);
			Assert::IsFalse(callback_was_unchecked_);

			localClickWindow(checkbox_);

			Assert::IsTrue(callback_was_checked_);
			Assert::IsTrue(callback_was_unchecked_);

		}

		TEST_METHOD(CheckSetCheckedAndUncheckedWhenInactive)
		{
			checkbox_.setActive(false);

			Assert::IsFalse(checkbox_.isChecked());

			checkbox_.setChecked(true);

			Assert::IsTrue(checkbox_.isChecked());

			checkbox_.setChecked(false);

			Assert::IsFalse(checkbox_.isChecked());
		}

		TEST_METHOD(CheckSetCheckedAndUncheckedWhenNotVisible)
		{
			checkbox_.setVisible(false);

			Assert::IsFalse(checkbox_.isChecked());

			checkbox_.setChecked(true);

			Assert::IsTrue(checkbox_.isChecked());

			checkbox_.setChecked(false);

			Assert::IsFalse(checkbox_.isChecked());
		}

		TEST_METHOD(CheckSetCheckedAndUncheckedViaMouse)
		{
			Assert::IsFalse(checkbox_.isChecked());

			localClickWindow(checkbox_);

			Assert::IsTrue(checkbox_.isChecked());

			localClickWindow(checkbox_);

			Assert::IsFalse(checkbox_.isChecked());
		}

		TEST_METHOD(CheckSetCheckedAndUncheckedViaMouseWhenInactive)
		{
			checkbox_.setActive(false);

			Assert::IsFalse(checkbox_.isChecked());

			localClickWindow(checkbox_);

			Assert::IsFalse(checkbox_.isChecked());

			localClickWindow(checkbox_);

			Assert::IsFalse(checkbox_.isChecked());
		}
	};
}
