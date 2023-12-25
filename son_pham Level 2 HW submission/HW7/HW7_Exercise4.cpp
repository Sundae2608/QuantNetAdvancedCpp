/*
* Advanced C++ and Modern Design
* Level 2
* Author: Son Pham
* Exercise 7, Exercise 4: Error Code Fundamentals
*/

#include <iostream>
#include <system_error>
#include <tuple>

namespace {
	// b) Create a function that returns the following information pertaining to instances of std::error_code:
	// Its error code (an integer).
	// Its message(a string).
	// The name of its category(a string).
	std::tuple<std::string, int, std::string> getErrorInfo(const std::error_code& error)
	{
		return std::make_tuple(error.message(), error.value(), error.category().name());
	}
}

int main74() {
	// a) Create a default error code and an error code with a platform-dependent error code value and an error category.
	std::error_code default_error_code;  // Default error code
	std::error_code platform_error_code(42, std::generic_category());  // Platform-dependent error code with value 42 and generic error category

	// b) Call the function that returns errorInfo
	auto [message, value, category] = getErrorInfo(platform_error_code);
	std::cout << "Message: " << message << std::endl;     // Message: illegal byte sequence
	std::cout << "Error Code: " << value << std::endl;    // Error Code: 42
	std::cout << "Category: " << category << std::endl;   // Category: generic

	// c) Test equality/inequality of instances of std::error_code and std::error_condition using operators == and !=.
	std::error_code error_code1(42, std::generic_category());
	std::error_code error_code2(42, std::generic_category());
	std::error_code error_code3(43, std::generic_category());
	std::cout << std::boolalpha;
	std::cout << "Error code 1 == Error code 2: " << (error_code1 == error_code2) << std::endl;
	std::cout << "Error code 1 == Error code 2: " << (error_code1 == error_code3) << std::endl;

	std::error_condition error_condition1 = std::make_error_condition(std::errc::permission_denied);
	std::error_condition error_condition2 = std::make_error_condition(std::errc::permission_denied);
	std::error_condition error_condition3 = std::make_error_condition(std::errc::no_such_file_or_directory);

	std::cout << "Error condition 1 == Error condition 2: " << (error_code1 == error_code2) << std::endl;
	std::cout << "Error condition 1 == Error condition 3: " << (error_code1 == error_code3) << std::endl;
	return 0;
}