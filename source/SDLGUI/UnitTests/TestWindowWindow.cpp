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

		TEST_METHOD(GivenWindowWithParent_WhenParentIsDestroyed_ThenParentIsRemoved)
		{
			TestableWindow window1(nullptr);
			{
				TestableWindow window2(nullptr);

				window1.setParent(&window2);
			}

			Assert::IsNull(window1.getParent());
		}

		TEST_METHOD(GivenWindowWithParent_WhenOtherParentIsSet_ThenOldParentIsReplaced)
		{
			TestableWindow old_parent(nullptr);
			TestableWindow window(&old_parent);
			TestableWindow new_parent(nullptr);
			
			window.setParent(&new_parent);

			Assert::AreEqual<void*>(&new_parent, window.getParent());
			Assert::AreEqual(std::size_t{ 0 }, old_parent.getChildren().size());
		}

		TEST_METHOD(GivenWindowWithoutChildren_WhenSetItselfAsChild_ThenHasNoChildren)
		{
			TestableWindow window1(nullptr);

			window1.addChild(window1);

			Assert::AreEqual(std::size_t{ 0 }, window1.getChildren().size());
		}

		TEST_METHOD(GivenWindowWithoutChildren_WhenAddChildren_ThenWindowHasChildren)
		{
			TestableWindow window1(nullptr);
			TestableWindow child1(nullptr);
			TestableWindow child2(nullptr);

			window1.addChild(child1);
			window1.addChild(child2);

			Assert::AreEqual(std::size_t{ 2 }, window1.getChildren().size());
			Assert::AreEqual<void*>(&child1, window1.getChildren()[0]);
			Assert::AreEqual<void*>(&child2, window1.getChildren()[1]);
		}

		TEST_METHOD(GivenWindowWithChild_WhenChildIsAddedToOtherWindow_ThenOtherWindowHasChildOnly)
		{
			TestableWindow window1(nullptr);
			TestableWindow window2(nullptr);
			TestableWindow child1(nullptr);
			window1.addChild(child1);
			
			window2.addChild(child1);

			Assert::AreEqual(std::size_t{ 0 }, window1.getChildren().size());
			Assert::AreEqual(std::size_t{ 1 }, window2.getChildren().size());
			Assert::AreEqual<void*>(&child1, window2.getChildren()[0]);
		}

		TEST_METHOD(GivenWindowWithChild_WhenChildIsRemoved_ThenWindowHasNoChildren)
		{
			TestableWindow window1(nullptr);
			TestableWindow child1(nullptr);
			window1.addChild(child1);

			window1.removeChild(child1);

			Assert::AreEqual(std::size_t{ 0 }, window1.getChildren().size());
		}

		TEST_METHOD(GivenWindowWithoutChild_WhenChildIsRemoved_ThenNoop)
		{
			TestableWindow window1(nullptr);
			TestableWindow child1(nullptr);

			window1.removeChild(child1);

			Assert::AreEqual(std::size_t{ 0 }, window1.getChildren().size());
		}

		TEST_METHOD(GivenWindowWithChild_WhenChildIsDestroyed_ThenWindowHasNoChildren)
		{
			TestableWindow parent(nullptr);
			{
				TestableWindow child(nullptr);
				parent.addChild(child);

			}

			Assert::AreEqual(std::size_t{ 0 }, parent.getChildren().size());
		}

		TEST_METHOD(GivenWindow_WhenChildIsAdded_ThenChildHasParent)
		{
			TestableWindow parent(nullptr);
			TestableWindow child(nullptr);
			
			parent.addChild(child);

			Assert::AreEqual<void*>(&parent, child.getParent());
		}

		TEST_METHOD(GivenWindow_WhenParentIsSet_ThenWindowIsChildOfParent)
		{
			TestableWindow parent(nullptr);
			TestableWindow child(nullptr);

			child.setParent(&parent);

			Assert::AreEqual<void*>(&child, parent.getChildren()[0]);
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

		TEST_METHOD(GivenWindow_WhenIsActive_ThenTrueByDefault)
		{
			TestableWindow window(nullptr);

			Assert::IsTrue(window.isActive());
		}

		TEST_METHOD(GivenActiveWindow_WhenSetInactive_ThenInactive)
		{
			TestableWindow window(nullptr);

			window.setActive(false);

			Assert::IsFalse(window.isActive());
		}

		TEST_METHOD(GivenInactiveWindow_WhenSetActive_ThenActive)
		{
			TestableWindow window(nullptr);
			window.setActive(false);
			
			window.setActive(true);

			Assert::IsTrue(window.isActive());
		}

		// TODO handleEvent tests
		// TODO callback tests
	};
}
