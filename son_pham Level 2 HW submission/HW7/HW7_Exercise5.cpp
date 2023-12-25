/*
* Advanced C++ and Modern Design
* Level 2
* Author: Son Pham
* Exercise 7, Exercise 5: Catching Exceptions
*/

#include <iostream>
#include <fstream>
#include <system_error>

int main75() {
	std::ifstream file(std::string("DOESNOTEXIST.txt"));
	try
	{
		// Set the exception mask of the file stream
		// In this case 1) logical error on I/O operation or
		// 2) read/write error on I/O operation
		file.exceptions(file.failbit | file.badbit);
	}
	catch (const std::ios_base::failure& e)
	{
		// a) In the catch block use e.code() with std::io_errc::stream.
		if (e.code() == std::make_error_code(std::io_errc::stream))
		{
			// b) If the comparison in a) is true, then:
			// Create an error code instance ec1 with e.code() as argument.
			// Create an error condition ec2 instance with ec1 as argument.
			// Print the properties value, messageand error category of ec2.
			std::error_code ec1 = e.code();
			std::error_condition ec2(ec1.value(), ec1.category());

			std::cout << "Value: " << ec2.value() << std::endl;
			std::cout << "Message: " << ec2.message() << std::endl;
			std::cout << "Category: " << ec2.category().name() << std::endl;
		}
	}
	catch (...)
	{
		std::cout << "catch all\n";
	}
	return 0;
}