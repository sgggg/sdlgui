#include "stdafx.h"

#include <string>

#include "CppUnitTest.h"
#include "../SDLGUILIB/SGL.h"

using namespace std::string_literals;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(TestWindowTextLabel)
	{
	public:
		TEST_METHOD(CheckTextLabelLabel)
		{
			auto expected_text = "Label Text"s;
			sgl::TextLabel label(nullptr, expected_text);
			Assert::AreEqual(expected_text, label.getText());

			auto new_text = "New Text"s;
			label.setText(new_text);
			Assert::AreEqual(new_text, label.getText());
		}
	};
}
