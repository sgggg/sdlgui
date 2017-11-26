#include <iostream>
#include <thread>

#include "SDL.h"
#include "SDL_ttf.h"
#include "SGL.h"

#include "Calculator.h"

int CalculatorApp::run()
{
	const auto return_code = initializeSdl();
	if (return_code != 0)
	{
		SDL_Quit();
		return return_code;
	}

	auto sdl_window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, kScreenWidth_, kScreenHeight_, SDL_WINDOW_SHOWN);
	if (sdl_window == nullptr)
	{
		std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return -1;
	}

	sgl::Frame main_frame(nullptr, "Calculator");
	main_frame.setSize(kScreenWidth_, kScreenHeight_);

	sgl::TextLabel calculation(&main_frame, "0");
	calculation.setPosition(0, 0);
	const auto output_panel_width = 50;
	calculation.setSize(kScreenWidth_, output_panel_width);

	//add window with grid layout
	sgl::GridLayout gl(&main_frame);
	gl.setPosition(0, 50);
	gl.setSize(kScreenWidth_, kScreenHeight_ - output_panel_width);
	sgl::Button button_clear(&gl, "Clear");
	gl.setGridPolicy(button_clear, 0, 0, 2, 1);
	sgl::Button button_negate(&gl, "+/-");
	gl.setGridPolicy(button_negate, 2, 0);
	sgl::Button button_divide(&gl, "/");
	gl.setGridPolicy(button_divide, 3, 0);
	sgl::Button button_num_7(&gl, "7");
	gl.setGridPolicy(button_num_7, 0, 1);
	sgl::Button button_num_8(&gl, "8");
	gl.setGridPolicy(button_num_8, 1, 1);
	sgl::Button button_num_9(&gl, "9");
	gl.setGridPolicy(button_num_9, 2, 1);
	sgl::Button button_multiply(&gl, "x");
	gl.setGridPolicy(button_multiply, 3, 1);
	sgl::Button button_num_4(&gl, "4");
	gl.setGridPolicy(button_num_4, 0, 2);
	sgl::Button button_num_5(&gl, "5");
	gl.setGridPolicy(button_num_5, 1, 2);
	sgl::Button button_num_6(&gl, "6");
	gl.setGridPolicy(button_num_6, 2, 2);
	sgl::Button button_plus(&gl, "+");
	gl.setGridPolicy(button_plus, 3, 2);
	sgl::Button button_num_1(&gl, "1");
	gl.setGridPolicy(button_num_1, 0, 3);
	sgl::Button button_num_2(&gl, "2");
	gl.setGridPolicy(button_num_2, 1, 3);
	sgl::Button button_num_3(&gl, "3");
	gl.setGridPolicy(button_num_3, 2, 3);
	sgl::Button button_minus(&gl, "-");
	gl.setGridPolicy(button_minus, 3, 3);
	sgl::Button button_num_0(&gl, "0");
	gl.setGridPolicy(button_num_0, 0, 4, 2, 1);
	sgl::Button button_decimal_point(&gl, ".");
	gl.setGridPolicy(button_decimal_point, 2, 4);
	sgl::Button button_equals(&gl, "=");
	gl.setGridPolicy(button_equals, 3, 4);
	gl.updateLayout();
	main_frame.setVisible(true);

	auto renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);

	runUpdateLoop(renderer);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(sdl_window);
	SDL_Quit();
	return 0;
}

void CalculatorApp::doOperation(Operation operation)
{
}

int CalculatorApp::initializeSdl()
{

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	if (TTF_Init() < 0)
	{
		std::cerr << "SDL_ttf could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	return 0;
}

void CalculatorApp::runUpdateLoop(SDL_Renderer* renderer)
{
	auto running = true;
	SDL_Event e;
	std::chrono::system_clock clock;
	const auto maxFps = 30;
	const auto frame_time = std::chrono::microseconds(1'000'000) / maxFps; // e.g. a frame has 1/60 s for 60 fps
	while (running)
	{
		// begin new frame
		auto frame_start = clock.now();

		// 1. advance state of application to the current time
		sgl::SetApplicationTime(std::chrono::duration_cast<std::chrono::milliseconds>(clock.now().time_since_epoch()));

		// 2. handle all input
		while (0 != SDL_PollEvent(&e))
		{
			sgl::HandleEvent(&e);

			if (e.type == SDL_QUIT)
			{
				running = false;
			}
		}

		// 3. draw updated state
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		sgl::DrawGui(renderer);
		SDL_RenderPresent(renderer);

		// 4. wait until frame time is over
		auto elapsed = clock.now() - frame_start;
		auto time_left_in_frame = frame_time - elapsed;
		std::this_thread::sleep_for(time_left_in_frame);
	}
}
