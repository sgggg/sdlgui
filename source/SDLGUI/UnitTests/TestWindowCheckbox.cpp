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
		TEST_METHOD(CheckSetAndGetLabelText)
		{
			auto label_text = "label text"s;
			sgl::Checkbox checkbox(nullptr, label_text);

			Assert::AreEqual(label_text, checkbox.getLabel());

			label_text = "new label text"s;
			checkbox.setLabel(label_text);

			Assert::AreEqual(label_text, checkbox.getLabel());
		}

		TEST_METHOD(CheckSetCheckedAndUnchecked)
		{
			sgl::Checkbox checkbox(nullptr, "label text"s);

			Assert::IsFalse(checkbox.isChecked());

			checkbox.setChecked(true);

			Assert::IsTrue(checkbox.isChecked());

			checkbox.setChecked(false);

			Assert::IsFalse(checkbox.isChecked());
		}

		TEST_METHOD(CheckSetCheckedAndUncheckedWhenInactive)
		{
			sgl::Checkbox checkbox(nullptr, "label text"s);
			checkbox.setActive(false);

			Assert::IsFalse(checkbox.isChecked());

			checkbox.setChecked(true);

			Assert::IsTrue(checkbox.isChecked());

			checkbox.setChecked(false);

			Assert::IsFalse(checkbox.isChecked());
		}

		TEST_METHOD(CheckSetCheckedAndUncheckedViaMouse)
		{
			sgl::Checkbox checkbox(nullptr, "label text"s);
			checkbox.setSize(200, 80);
			checkbox.setVisible(true);

			Assert::IsFalse(checkbox.isChecked());

			checkbox.handleEvent(leftMouseDown(100, 40));
			checkbox.handleEvent(leftMouseUp(101, 42));

			Assert::IsTrue(checkbox.isChecked());

			checkbox.handleEvent(leftMouseDown(100, 40));
			checkbox.handleEvent(leftMouseUp(101, 42));

			Assert::IsFalse(checkbox.isChecked());
		}

		TEST_METHOD(CheckSetCheckedAndUncheckedViaMouseWhenInactive)
		{
			sgl::Checkbox checkbox(nullptr, "label text"s);
			checkbox.setSize(200, 80);
			checkbox.setVisible(true);
			checkbox.setActive(false);

			Assert::IsFalse(checkbox.isChecked());

			checkbox.handleEvent(leftMouseDown(100, 40));
			checkbox.handleEvent(leftMouseUp(101, 42));

			Assert::IsFalse(checkbox.isChecked());

			checkbox.handleEvent(leftMouseDown(100, 40));
			checkbox.handleEvent(leftMouseUp(101, 42));

			Assert::IsFalse(checkbox.isChecked());
		}
	};
}
