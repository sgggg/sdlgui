#include "stdafx.h"

#include <string>

#include "CppUnitTest.h"
#include "../SDLGUILIB/SGL.h"
#include "UserInputGeneration.h"

using namespace std::string_literals;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(TestWindowFrame)
	{
	public:
		TEST_METHOD(CheckRootFrameConstruction)
		{
			sgl::Frame main_frame(nullptr, "Main Window");
			Assert::IsNull(main_frame.getParent());
		}

		TEST_METHOD(CheckFrameTitle)
		{
			auto expected_title = "Main Window"s;
			sgl::Frame main_frame(nullptr, expected_title);
			Assert::AreEqual(expected_title, main_frame.getTitle());

			auto new_title = "New Title"s;
			main_frame.setTitle(new_title);
			Assert::AreEqual(new_title, main_frame.getTitle());
		}

		TEST_METHOD(CheckFrameTitleBar)
		{
			sgl::Frame main_frame(nullptr, "Main Window");
			Assert::IsFalse(main_frame.hasTitleBar());
			main_frame.setTitleBar(true);
			Assert::IsTrue(main_frame.hasTitleBar());
			main_frame.setTitleBar(false);
			Assert::IsFalse(main_frame.hasTitleBar());
		}
	};
}
