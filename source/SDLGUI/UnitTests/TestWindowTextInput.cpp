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
			sgl::TextInput text_input(nullptr, "default text"s);
			text_input.setVisible(true);

			Assert::AreEqual(""s, text_input.getText());

			auto typed_blue = "Blue "s;
			auto typed_elephants = "Elephants"s;
			auto expected_text = typed_blue + typed_elephants;
			typeText(text_input, expected_text);

			Assert::AreEqual(expected_text, text_input.getText());

			moveCursorLeft(text_input, expected_text.size());
			auto typed_i_like = "I Like "s;
			expected_text = typed_i_like + typed_blue + typed_elephants;
			typeText(text_input, typed_i_like);

			Assert::AreEqual(expected_text, text_input.getText());

			moveCursorRight(text_input, typed_blue.size());
			auto typed_and_green = "and Green "s;
			expected_text = typed_i_like + typed_blue + typed_and_green + typed_elephants;
			typeText(text_input, typed_and_green);

			Assert::AreEqual(expected_text, text_input.getText());
		}

		TEST_METHOD(CheckRemoveTextWithBackspaceAtCursor)
		{
			sgl::TextInput text_input(nullptr, "default text"s);
			text_input.setVisible(true);

			auto expected_text = "AbCdEf"s;
			typeText(text_input, expected_text);

			Assert::AreEqual(expected_text, text_input.getText());

			moveCursorLeft(text_input, 3);
			typeBackspace(text_input, 2);

			Assert::AreEqual("AdEf"s, text_input.getText());

			moveCursorRight(text_input, 3);
			typeBackspace(text_input, 2);

			Assert::AreEqual("Ad"s, text_input.getText());

			moveCursorLeft(text_input, 2);
			typeBackspace(text_input, 4);

			Assert::AreEqual("Ad"s, text_input.getText());
		}

		TEST_METHOD(CheckRemoveTextWithDeleteAtCursor)
		{
			sgl::TextInput text_input(nullptr, "default text"s);
			text_input.setVisible(true);

			auto typed_text = "AbCdEf"s;
			typeText(text_input, typed_text);

			Assert::AreEqual(typed_text, text_input.getText());

			moveCursorLeft(text_input, 5);
			typeDelete(text_input, 2);

			Assert::AreEqual("AdEf"s, text_input.getText());

			moveCursorRight(text_input, 2);
			typeDelete(text_input, 5);

			Assert::AreEqual("AdE"s, text_input.getText());
		}
		
		TEST_METHOD(CheckEnterAndRemoveTextAtCursor)
		{
			sgl::TextInput text_input(nullptr, "default text"s);
			text_input.setVisible(true);

			auto typed_text = "AbCdEf"s;
			typeText(text_input, typed_text);

			Assert::AreEqual(typed_text, text_input.getText());

			moveCursorLeft(text_input, 3);
			typeText(text_input, "...");
			typeBackspace(text_input, 2);

			Assert::AreEqual("AbC.dEf"s, text_input.getText());

			moveCursorRight(text_input, 2);
			typeDelete(text_input, 3);
			typeText(text_input, "//");

			Assert::AreEqual("AbC.dE//"s, text_input.getText());
		}
	};
}
