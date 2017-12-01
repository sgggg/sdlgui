#include "CalculatorGui.h"

using namespace std::string_literals;

CalculatorGui::CalculatorGui() :
	main_frame(nullptr, "Calculator"),
	calculation(&main_frame, "0"),
	gl(&main_frame),
	button_clear(&gl, "Clear"),
	button_negate(&gl, "+/-"),
	button_divide(&gl, "/"),
	button_num_7(&gl, "7"),
	button_num_8(&gl, "8"),
	button_num_9(&gl, "9"),
	button_multiply(&gl, "x"),
	button_num_4(&gl, "4"),
	button_num_5(&gl, "5"),
	button_num_6(&gl, "6"),
	button_plus(&gl, "+"),
	button_num_1(&gl, "1"),
	button_num_2(&gl, "2"),
	button_num_3(&gl, "3"),
	button_minus(&gl, "-"),
	button_num_0(&gl, "0"),
	button_decimal_point(&gl, "."),
	button_equals(&gl, "=")
{
}

void CalculatorGui::initialize(int guiWidth, int guiHeight)
{
	main_frame.setSize(guiWidth, guiHeight);

	calculation.setPosition(0, 0);
	const auto output_panel_height = 80;
	calculation.setSize(guiWidth, output_panel_height);
	calculation.setLabelAlignment(sgl::Alignment::Right);

	gl.setPosition(0, output_panel_height);
	gl.setSize(guiWidth, guiHeight - output_panel_height);

	button_clear.addEventCallback(sgl::EventType::ButtonPressed, [&](const auto& e) {
		doOperation('c');
	});
	gl.setGridPolicy(button_clear, 0, 0, 2, 1);
	button_negate.addEventCallback(sgl::EventType::ButtonPressed, [&](const auto& e) {
		doOperation('~');
	});
	gl.setGridPolicy(button_negate, 2, 0);
	button_divide.addEventCallback(sgl::EventType::ButtonPressed, [&](const auto& e) {
		doOperation('/');
	});
	gl.setGridPolicy(button_divide, 3, 0);
	button_num_7.addEventCallback(sgl::EventType::ButtonPressed, [&](const auto& e) {
		addDigit(7);
	});
	gl.setGridPolicy(button_num_7, 0, 1);
	button_num_8.addEventCallback(sgl::EventType::ButtonPressed, [&](const auto& e) {
		addDigit(8);
	});
	gl.setGridPolicy(button_num_8, 1, 1);
	button_num_9.addEventCallback(sgl::EventType::ButtonPressed, [&](const auto& e) {
		addDigit(9);
	});
	gl.setGridPolicy(button_num_9, 2, 1);
	button_multiply.addEventCallback(sgl::EventType::ButtonPressed, [&](const auto& e) {
		doOperation('x');
	});
	gl.setGridPolicy(button_multiply, 3, 1);
	button_num_4.addEventCallback(sgl::EventType::ButtonPressed, [&](const auto& e) {
		addDigit(4);
	});
	gl.setGridPolicy(button_num_4, 0, 2);
	button_num_5.addEventCallback(sgl::EventType::ButtonPressed, [&](const auto& e) {
		addDigit(5);
	});
	gl.setGridPolicy(button_num_5, 1, 2);
	button_num_6.addEventCallback(sgl::EventType::ButtonPressed, [&](const auto& e) {
		addDigit(6);
	});
	gl.setGridPolicy(button_num_6, 2, 2);
	button_plus.addEventCallback(sgl::EventType::ButtonPressed, [&](const auto& e) {
		doOperation('+');
	});
	gl.setGridPolicy(button_plus, 3, 2);
	button_num_1.addEventCallback(sgl::EventType::ButtonPressed, [&](const auto& e) {
		addDigit(1);
	});
	gl.setGridPolicy(button_num_1, 0, 3);
	button_num_2.addEventCallback(sgl::EventType::ButtonPressed, [&](const auto& e) {
		addDigit(2);
	});
	gl.setGridPolicy(button_num_2, 1, 3);
	button_num_3.addEventCallback(sgl::EventType::ButtonPressed, [&](const auto& e) {
		addDigit(3);
	});
	gl.setGridPolicy(button_num_3, 2, 3);
	button_minus.addEventCallback(sgl::EventType::ButtonPressed, [&](const auto& e) {
		doOperation('-');
	});
	gl.setGridPolicy(button_minus, 3, 3);
	button_num_0.addEventCallback(sgl::EventType::ButtonPressed, [&](const auto& e) {
		addDigit(0);
	});
	gl.setGridPolicy(button_num_0, 0, 4, 2, 1);
	button_decimal_point.addEventCallback(sgl::EventType::ButtonPressed, [&](const auto& e) {
		doOperation('p');
	});
	gl.setGridPolicy(button_decimal_point, 2, 4);
	button_equals.addEventCallback(sgl::EventType::ButtonPressed, [&](const auto& e) {
		doOperation('=');
	});
	gl.setGridPolicy(button_equals, 3, 4);
	gl.updateLayout();
	main_frame.setVisible(true);
}

void CalculatorGui::updateCalculationString()
{
	auto new_label = expression_stream.str();
	if (!(!new_label.empty() && number_being_entered_ == 0.0))
	{
		new_label += std::to_string(number_being_entered_);
	}
	calculation.setLabel(new_label);
}

void CalculatorGui::addDigit(int digit)
{
	if (nth_digit_after_decimal_point_ > 0)
	{
		number_being_entered_ = number_being_entered_ + (digit / std::pow(10.0, nth_digit_after_decimal_point_));
		++nth_digit_after_decimal_point_;
	}
	else
	{
		number_being_entered_ = (number_being_entered_ * 10.0) + digit;
	}
	updateCalculationString();
}

void CalculatorGui::doOperation(char operation)
{
	switch (operation)
	{
	case '+':
	case '-':
	case 'x':
	case '/':
		expression_stream << number_being_entered_ << operation;
		number_being_entered_ = 0.0;
		nth_digit_after_decimal_point_ = 0;
		break;
	case '~':
		number_being_entered_ *= -1.0;
		break;
	case '=':
	{
		expression_stream << number_being_entered_;
		auto result = parseAndCalculateResult(expression_stream.str());
		expression_stream << "=" << result;
		number_being_entered_ = 0.0;
		nth_digit_after_decimal_point_ = 0;
		break;
	}
	case 'c':
		expression_stream.str("");
		number_being_entered_ = 0.0;
		nth_digit_after_decimal_point_ = 0;
		break;
	case 'p':
		if (nth_digit_after_decimal_point_ == 0)
		{
			nth_digit_after_decimal_point_ = 1;
		}
		break;
	}
	updateCalculationString();
}


bool isDigit(char character)
{
	// TODO REGEX
	return character >= '0' && character <= '9';
}

bool isOperator(char character)
{
	// TODO REGEX
	return character == '-' || character == '+' || character == '/' || character == 'x';
}

double parseNumericLiteral(const std::string& expression, std::string::const_iterator& current_position)
{
	// TODO regex
	return 1.0;
}

double calculate(double lhs, char op, double rhs)
{
	switch (op)
	{
	case '+': return lhs + rhs;
	case '-': return lhs - rhs;
	case 'x': return lhs * rhs;
	case '/': return lhs / rhs;
	default: throw std::runtime_error("invalid operator");
	}
	throw std::runtime_error("invalid operator");
	return 0.0;
}

char parseOperator(const std::string& expression, std::string::const_iterator& current_position)
{
	auto op = *current_position;
	++current_position;
	return op;
}
double parseRecursive(const std::string& expression, std::string::const_iterator& current_position)
{
	if (current_position == expression.end())
	{
		return 0.0;
	}
	if (isDigit(*current_position))
	{
		auto literal_value = parseNumericLiteral(expression, current_position);
		if (isOperator(*current_position))
		{
			auto op = parseOperator(expression, current_position);
			auto right_literal_value = parseNumericLiteral(expression, current_position);
			return calculate(literal_value, op, right_literal_value);
		}
		else
		{
			return literal_value;
		}
	}
	throw std::runtime_error("invalid expression: expected numeric literal");
}



double CalculatorGui::parseAndCalculateResult(const std::string& expression)
{
	return parseRecursive(expression, expression.begin());
}
