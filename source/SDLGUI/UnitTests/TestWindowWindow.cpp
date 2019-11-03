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
	class TestableWindow : public sgl::Window
	{
	public:
		TestableWindow(sgl::Window* parent) :
			Window(parent)
		{
		}

		virtual void draw(SDL_Renderer*) override
		{
		}
	};

	class MockGuiManager : public sgl::GuiManager 
	{};

	TEST_CLASS(TestWindowWindow)
	{
	public:
		TEST_METHOD(GivenWindow_WhenGetManager_ThenNullByDefault)
		{
			TestableWindow window1(nullptr);

			Assert::IsNull(window1.getManager());
		}

		TEST_METHOD(GivenWindow_WhenSetManager_ThenHasManager)
		{
			MockGuiManager manager;
			TestableWindow window1{ nullptr };

			window1.setManager(&manager);

			Assert::AreEqual<const void*>(&manager, window1.getManager());
		}

		TEST_METHOD(GivenWindowWithManager_WhenRemoveManager_ThenManagerNull)
		{
			MockGuiManager manager;
			TestableWindow window1{ nullptr };
			window1.setManager(&manager);

			window1.setManager(nullptr);

			Assert::IsNull(window1.getManager());
		}

		TEST_METHOD(GivenWindowWithoutParent_WhenGetParent_ThenNull)
		{
			TestableWindow window1(nullptr);

			Assert::IsNull(window1.getParent());
		}

		TEST_METHOD(GivenWindowWithParent_WhenGetParent_ThenReturnParent)
		{
			TestableWindow window1(nullptr);
			TestableWindow window2(&window1);

			Assert::AreEqual<const void*>(&window1, window2.getParent());
		}

		TEST_METHOD(GivenWindowWithoutParent_WhenSetItselfAsParent_ThenHasNoParent)
		{
			TestableWindow window1(nullptr);

			window1.setParent(&window1);

			Assert::IsNull(window1.getParent());
		}

		TEST_METHOD(GivenWindowWithoutParent_WhenSetParent_ThenWindowIsSetAsParent)
		{
			TestableWindow window1(nullptr);
			TestableWindow window2(nullptr);

			window2.setParent(&window1);

			Assert::AreEqual<const void*>(&window1, window2.getParent());
		}

		TEST_METHOD(GivenWindowWithParent_WhenParentRemoved_ThenHasNoParent)
		{
			TestableWindow window1(nullptr);
			TestableWindow window2(&window1);

			window2.setParent(nullptr);

			Assert::IsNull(window2.getParent());
		}

		TEST_METHOD(GivenWindow_WhenGetId_ThenHasValidId)
		{
			TestableWindow window1(nullptr);

			Assert::AreNotEqual(sgl::kInvalidWindowId, window1.getId());
		}

		TEST_METHOD(GivenMultipleWindows_WhenGetId_ThenAllHaveUniqueIds)
		{
			TestableWindow window1(nullptr);
			TestableWindow window2(nullptr);
			TestableWindow window3(nullptr);

			Assert::AreNotEqual(window1.getId(), window2.getId());
			Assert::AreNotEqual(window1.getId(), window3.getId());
			Assert::AreNotEqual(window2.getId(), window3.getId());
		}

		TEST_METHOD(GivenWindow_WhenGetPosition_ThenReturnDefaultPosition)
		{
			TestableWindow window(nullptr);

			Assert::AreEqual(sgl::Point{ 0, 0 }, window.getPosition());
		}

		TEST_METHOD(GivenWindow_WhenSetPosition_ThenWindowAtNewPosition)
		{
			TestableWindow window(nullptr);

			sgl::Point new_position = {52, 87};
			window.setPosition(new_position);

			Assert::AreEqual(new_position, window.getPosition());
		}

		TEST_METHOD(GivenWindow_WhenSetPositionXAndY_ThenWindowAtNewPosition)
		{
			TestableWindow window(nullptr);

			window.setPosition(52, 87);

			sgl::Point new_position = { 52, 87 };
			Assert::AreEqual(new_position, window.getPosition());
		}

		TEST_METHOD(GivenWindow_WhenGetSize_ThenReturnDefaultSize)
		{
			TestableWindow window(nullptr);

			Assert::AreEqual(sgl::Size{ 0, 0 }, window.getSize());
		}

		TEST_METHOD(GivenWindow_WhenSetSize_ThenWindowOfNewSize)
		{
			TestableWindow window(nullptr);

			sgl::Size new_size = {52, 87};
			window.setSize(new_size);

			Assert::AreEqual(new_size, window.getSize());
		}

		TEST_METHOD(GivenWindow_WhenSetWidthAndHeight_ThenWindowOfNewSize)
		{
			TestableWindow window(nullptr);

			window.setSize(52, 87);

			sgl::Size expected_size = { 52, 87 };
			Assert::AreEqual(expected_size, window.getSize());
		}

		TEST_METHOD(GivenWindow_WhenGetVisible_ThenFalseByDefault)
		{
			TestableWindow window(nullptr);

			Assert::IsFalse(window.isVisible());
		}

		TEST_METHOD(GivenVisibleWindow_WhenSetInvisible_ThenInivisble)
		{
			TestableWindow window(nullptr);
			window.setVisible(true);

			window.setVisible(false);

			Assert::IsFalse(window.isVisible());
		}

		TEST_METHOD(GivenInvisibleWindow_WhenSetVisible_ThenVisible)
		{
			TestableWindow window(nullptr);

			window.setVisible(true);

			Assert::IsTrue(window.isVisible());
		}

		// TODO remaining tests

	};
}
