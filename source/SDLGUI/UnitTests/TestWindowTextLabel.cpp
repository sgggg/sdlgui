#include "stdafx.h"

#include <string>

#include "CppUnitTest.h"
#include "../SDLGUILIB/SGL.h"
#include "ExtendedAssert.h"

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
			Assert::AreEqual(expected_text, label.getLabel());

			auto new_text = "New Text"s;
			label.setLabel(new_text);
			Assert::AreEqual(new_text, label.getLabel());
		}

		TEST_METHOD(CheckTextLabelSetLabelAlignment)
		{
			sgl::TextLabel label(nullptr, "Label Text"s);
			auto expected_default_alignment = sgl::Alignment::Center;
			Assert::AreEqual(expected_default_alignment, label.getLabelAlignment());

			auto new_alignment = sgl::Alignment::TopRight;
			label.setLabelAlignment(new_alignment);
			Assert::AreEqual(new_alignment, label.getLabelAlignment());
		}
	};
}
