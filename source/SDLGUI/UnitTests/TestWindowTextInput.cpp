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
	TEST_CLASS(TestWindowTextInput)
	{
	public:
		TEST_METHOD(CheckSetAndGetDefaultText)
		{
			auto default_text = "default text"s;
			sgl::TextInput text_input(nullptr, default_text);

			Assert::AreEqual(""s, text_input.getText());
			Assert::AreEqual(default_text, text_input.getDefaultText());

			default_text = "new default text"s;
			text_input.setDefaultText(default_text);

			Assert::AreEqual(""s, text_input.getText());
			Assert::AreEqual(default_text, text_input.getDefaultText());
		}

		TEST_METHOD(CheckSetAndGetText)
		{
			auto default_text = "default text"s;
			sgl::TextInput text_input(nullptr, default_text);

			Assert::AreEqual(""s, text_input.getText());
			Assert::AreEqual(default_text, text_input.getDefaultText());

			auto text = "normal text"s;
			text_input.setText(text);

			Assert::AreEqual(text, text_input.getText());
			Assert::AreEqual(default_text, text_input.getDefaultText());

			text = "more text"s;
			text_input.setText(text);

			Assert::AreEqual(text, text_input.getText());
			Assert::AreEqual(default_text, text_input.getDefaultText());
		}

		TEST_METHOD(CheckEnterText)
		{
			auto default_text = "default text"s;
			sgl::TextInput text_input(nullptr, default_text);
			text_input.setVisible(true);

			Assert::AreEqual(""s, text_input.getText());
			Assert::AreEqual(default_text, text_input.getDefaultText());

			auto typed_text = "Blue Elephants"s;
			typeText(text_input, typed_text);

			Assert::AreEqual(typed_text, text_input.getText());
			Assert::AreEqual(default_text, text_input.getDefaultText());

			auto more_typed_text = " and Red Spiders"s;
			typeText(text_input, more_typed_text);

			Assert::AreEqual(typed_text + more_typed_text, text_input.getText());
			Assert::AreEqual(default_text, text_input.getDefaultText());
		}

		TEST_METHOD(CheckEnterTextAtCursor)
		{
			auto default_text = "default text"s;
			sgl::TextInput text_input(nullptr, default_text);
			text_input.setVisible(true);

			Assert::AreEqual(""s, text_input.getText());

			Assert::Fail(L"Not Implemented");
		}

		TEST_METHOD(CheckRemoveTextWithBackspaceAtCursor)
		{
			auto default_text = "default text"s;
			sgl::TextInput text_input(nullptr, default_text);
			text_input.setVisible(true);

			Assert::AreEqual(""s, text_input.getText());

			Assert::Fail(L"Not Implemented");
		}

		TEST_METHOD(CheckRemoveTextWithDeleteAtCursor)
		{
			auto default_text = "default text"s;
			sgl::TextInput text_input(nullptr, default_text);
			text_input.setVisible(true);

			Assert::AreEqual(""s, text_input.getText());

			Assert::Fail(L"Not Implemented");
		}

		TEST_METHOD(CheckEnterAndRemoveTextAtCursor)
		{
			auto default_text = "default text"s;
			sgl::TextInput text_input(nullptr, default_text);
			text_input.setVisible(true);

			Assert::AreEqual(""s, text_input.getText());

			Assert::Fail(L"Not Implemented");
		}
	};
}
