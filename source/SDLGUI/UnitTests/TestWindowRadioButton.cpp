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
	TEST_CLASS(TestWindowRadioButton)
	{
	public:
		std::string radio1_label_;
		std::string radio2_label_;
		std::string radio3_label_;
		sgl::GuiManager manager_;
		sgl::Frame frame_;
		sgl::GroupBox group_box_;
		sgl::RadioButton radio1_;
		sgl::RadioButton radio2_;
		sgl::RadioButton radio3_;
		int last_checked_radio_{ 0 };
		int last_unchecked_radio_{0};

		TestWindowRadioButton() :
			radio1_label_("Option 1"),
			radio2_label_("Option 2"),
			radio3_label_("Option 3"),
			frame_(nullptr, "Frame"),
			group_box_(&frame_),
			radio1_(&group_box_, radio1_label_),
			radio2_(&group_box_, radio2_label_),
			radio3_(&group_box_, radio3_label_)
		{
			radio1_.setSize(200, 80);
			radio2_.setSize(200, 80);
			radio3_.setSize(200, 80);
			frame_.setVisible(true);
			radio1_.addEventCallback(sgl::EventType::Checked, [this](const auto&) {
				last_checked_radio_ = 1;
			});
			radio1_.addEventCallback(sgl::EventType::Unchecked, [this](const auto&) {
				last_unchecked_radio_ = 1;
			});
			radio2_.addEventCallback(sgl::EventType::Checked, [this](const auto&) {
				last_checked_radio_ = 2;
			});
			radio2_.addEventCallback(sgl::EventType::Unchecked, [this](const auto&) {
				last_unchecked_radio_ = 2;
			});
			radio3_.addEventCallback(sgl::EventType::Checked, [this](const auto&) {
				last_checked_radio_ = 3;
			});
			radio3_.addEventCallback(sgl::EventType::Unchecked, [this](const auto&) {
				last_unchecked_radio_ = 3;
			});
			manager_.registerWindow(frame_);
		}

		TEST_METHOD(CheckRadioButtonSetAndGetLabelText)
		{
			Assert::AreEqual(radio1_label_, radio1_.getLabel());

			radio1_label_ = "Option X"s;
			radio1_.setLabel(radio1_label_);

			Assert::AreEqual(radio1_label_, radio1_.getLabel());
		}

		TEST_METHOD(CheckRadioButtonSetCheckedAndUnchecked)
		{
			Assert::IsFalse(radio1_.isChecked());
			Assert::IsFalse(radio2_.isChecked());
			Assert::IsFalse(radio3_.isChecked());

			radio1_.setChecked(true);

			Assert::IsTrue(radio1_.isChecked());
			Assert::IsFalse(radio2_.isChecked());
			Assert::IsFalse(radio3_.isChecked());

			radio1_.setChecked(true);

			Assert::IsTrue(radio1_.isChecked());
			Assert::IsFalse(radio2_.isChecked());
			Assert::IsFalse(radio3_.isChecked());

			radio2_.setChecked(true);

			Assert::IsFalse(radio1_.isChecked());
			Assert::IsTrue(radio2_.isChecked());
			Assert::IsFalse(radio3_.isChecked());

			radio3_.setChecked(true);

			Assert::IsFalse(radio1_.isChecked());
			Assert::IsFalse(radio2_.isChecked());
			Assert::IsTrue(radio3_.isChecked());
		}

		TEST_METHOD(CheckRadioButtonCheckedUncheckedCallback)
		{
			Assert::AreEqual(0, last_checked_radio_);
			Assert::AreEqual(0, last_unchecked_radio_);

			localClickWindow(radio1_);

			Assert::AreEqual(1, last_checked_radio_);
			Assert::AreEqual(0, last_unchecked_radio_);

			localClickWindow(radio2_);

			Assert::AreEqual(2, last_checked_radio_);
			Assert::AreEqual(1, last_unchecked_radio_);

			localClickWindow(radio1_);

			Assert::AreEqual(1, last_checked_radio_);
			Assert::AreEqual(2, last_unchecked_radio_);
		}

		TEST_METHOD(CheckSetCheckedAndUncheckedWhenInactive)
		{
			radio1_.setActive(false);

			Assert::IsFalse(radio1_.isChecked());

			radio1_.setChecked(true);

			Assert::IsTrue(radio1_.isChecked());

			radio1_.setChecked(false);

			Assert::IsFalse(radio1_.isChecked());
		}

		TEST_METHOD(CheckSetCheckedAndUncheckedWhenNotVisible)
		{
			radio1_.setVisible(false);

			Assert::IsFalse(radio1_.isChecked());

			radio1_.setChecked(true);

			Assert::IsTrue(radio1_.isChecked());

			radio1_.setChecked(false);

			Assert::IsFalse(radio1_.isChecked());
		}

		TEST_METHOD(CheckSetCheckedAndNotUncheckedViaMouse)
		{
			Assert::IsFalse(radio1_.isChecked());

			localClickWindow(radio1_);

			Assert::IsTrue(radio1_.isChecked());

			localClickWindow(radio1_);

			Assert::IsTrue(radio1_.isChecked());
		}

		TEST_METHOD(CheckSetCheckedAndUncheckedViaMouseWhenInactive)
		{
			radio1_.setActive(false);

			Assert::IsFalse(radio1_.isChecked());

			localClickWindow(radio1_);

			Assert::IsFalse(radio1_.isChecked());
		}
	};
}
