/*
* Advanced C++ and Modern Design
* Level 2
* Author: Son Pham
* Exercise 7, Exercise 3: Portable Error Conditions corresponding to POSIX Error Codes
*/

#include <system_error>


int main73() {
	// a) Create error condition instances based on the following POSIX error codes (use scoped enumerator std::errc ):
	std::error_condition io_error = std::make_error_condition(std::errc::io_error);
	std::error_condition network_unreachable = std::make_error_condition(std::errc::network_unreachable);
	std::error_condition no_such_file_or_directory = std::make_error_condition(std::errc::no_such_file_or_directory);
	std::error_condition not_a_socket = std::make_error_condition(std::errc::not_a_socket);
	std::error_condition permission_denied = std::make_error_condition(std::errc::permission_denied);

	// b) Create an std::error_condition object based on the value 128 and the generic error category.
	std::error_condition custom_error(128, std::generic_category());

	// c) Use std::make_error_condition (with std::io_errc as argument) to create an instance of std::error_condition.
	std::error_condition io_error_condition = std::make_error_condition(std::io_errc::stream);
	return 0;
}