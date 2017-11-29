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
	class BasicWindow : public sgl::Window
	{
	public:
		BasicWindow(sgl::Window* parent) :
			Window(parent)
		{
		}

		virtual void draw(SDL_Renderer*) override
		{
		}
	};
	TEST_CLASS(TestWindowWindow)
	{
	public:
		TEST_METHOD(CheckWindowSetParent)
		{
			BasicWindow window1(nullptr);
			BasicWindow window2(nullptr);

			Assert::IsNull(window1.getParent());
			Assert::IsNull(window2.getParent());

			window1.setParent(&window1);
			
			Assert::IsNull(window1.getParent());
			Assert::IsNull(window2.getParent());

			window2.setParent(&window1);

			Assert::IsNull(window1.getParent());
			Assert::IsTrue(&window1 == window2.getParent());

			window1.setParent(nullptr);
			window2.setParent(nullptr);

			Assert::IsNull(window1.getParent());
			Assert::IsNull(window2.getParent());

			window1.setParent(&window2);

			Assert::IsNull(window2.getParent());
			Assert::IsTrue(&window2 == window1.getParent());
		}

		TEST_METHOD(CheckUniqueId)
		{
			BasicWindow window1(nullptr);
			BasicWindow window2(nullptr);
			BasicWindow window3(nullptr);

			Assert::AreNotEqual(sgl::Window::kInvalidId, window1.getId());
			Assert::AreNotEqual(sgl::Window::kInvalidId, window2.getId());
			Assert::AreNotEqual(sgl::Window::kInvalidId, window3.getId());
			Assert::AreNotEqual(window1.getId(), window2.getId());
			Assert::AreNotEqual(window1.getId(), window3.getId());
			Assert::AreNotEqual(window2.getId(), window3.getId());
		}

		TEST_METHOD(CheckWindowSetPosition)
		{
			BasicWindow window(nullptr);

			Assert::AreEqual(sgl::Point{0, 0}, window.getPosition());

			sgl::Point new_position = {52, 87};
			window.setPosition(new_position);

			Assert::AreEqual(new_position, window.getPosition());
		}

		TEST_METHOD(CheckWindowSetSize)
		{
			BasicWindow window(nullptr);

			Assert::AreEqual(sgl::Size{0, 0}, window.getSize());

			sgl::Size new_size = {52, 87};
			window.setSize(new_size);

			Assert::AreEqual(new_size, window.getSize());
		}

	};
}
