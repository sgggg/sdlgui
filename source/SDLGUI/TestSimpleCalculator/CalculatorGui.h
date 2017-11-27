#pragma once

#include <string>
#include <sstream>

#include "SGL.h"

class CalculatorGui
{
public:
	CalculatorGui();

	void initialize(int guiWidth, int guiHeight);

private:
	void updateCalculationString();
	void addDigit(int digit);
	void doOperation(char operation);
	double parseAndCalculateResult(const std::string& expression);

	sgl::Frame main_frame;
	sgl::TextLabel calculation;
	sgl::GridLayout gl;
	sgl::Button button_clear;
	sgl::Button button_negate;
	sgl::Button button_divide;
	sgl::Button button_num_7;
	sgl::Button button_num_8;
	sgl::Button button_num_9;
	sgl::Button button_multiply;
	sgl::Button button_num_4;
	sgl::Button button_num_5;
	sgl::Button button_num_6;
	sgl::Button button_plus;
	sgl::Button button_num_1;
	sgl::Button button_num_2;
	sgl::Button button_num_3;
	sgl::Button button_minus;
	sgl::Button button_num_0;
	sgl::Button button_decimal_point;
	sgl::Button button_equals;

	std::stringstream expression_stream;
	double number_being_entered_ = 0.0;
	int nth_digit_after_decimal_point_ = 0;
};
