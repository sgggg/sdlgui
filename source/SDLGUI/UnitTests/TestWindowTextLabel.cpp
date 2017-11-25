#include "stdafx.h"

#include <string>

#include "CppUnitTest.h"
#include "../SDLGUILIB/SGL.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(TestWindowTextLabel)
	{
	public:
		TEST_METHOD(CheckTextLabelLabel)
		{
			auto expected_text = std::string("Label Text");
			sgl::TextLabel label(nullptr, expected_text);
			Assert::AreEqual(expected_text, label.getText());

			auto new_text= std::string("New Text");
			label.setText(new_text);
			Assert::AreEqual(new_text, label.getText());
		}
	};
}
