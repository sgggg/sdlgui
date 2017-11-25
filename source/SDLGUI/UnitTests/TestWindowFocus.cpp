#include "stdafx.h"

#include <string>

#include "CppUnitTest.h"
#include "../SDLGUILIB/SGL.h"
#include "UserInputGeneration.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(TestWindowFocus)
	{
	public:
		TEST_METHOD(CheckFirstWindowCreatedHasFocus)
		{
			sgl::Frame first_frame(nullptr, "First Frame");
			sgl::Frame second_frame(nullptr, "Second Frame");
			sgl::Frame third_frame(nullptr, "Third Frame");

			Assert::IsTrue(first_frame.hasFocus());
			Assert::IsFalse(second_frame.hasFocus());
			Assert::IsFalse(third_frame.hasFocus());
		}

		// TODO more tests 
	};
}