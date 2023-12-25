/*
* Advanced C++ and Modern Design
* Level 2
* Author: Son Pham
* Homework 4, Exercise 5: Custom Deleter
*/

#include <iostream>
#include <memory>

namespace {
    struct FileFinalizer {
        void operator()(FILE* file) const {
            if (file) {
                std::cout << "Closing file.\n";
                fclose(file);
            }
        }
    };

    void FunctionFinalizer(FILE* file) {
        if (file) {
            std::cout << "Closing file using free function.\n";
            fclose(file);
        }
    }


    class Point {
    public:
        Point() : x(0), y(0) {};
        void X(double new_x) {
            x = new_x;
        }
        void Y(double new_y) {
            y = new_y;
        }
        double x;
        double y;
    };

}

int main45() {
    // Prelude)
    auto deleter = [](Point* pt) -> void
    { std::cout << "Bye point!"; };

    using SmartPoint = std::shared_ptr<Point>;
    SmartPoint p1(new Point(), deleter);

	// a) The goal of this exercise is to open a file, write some data to the file an
	// then close it when we are finished writing. Under normal circumstances we are
	// able to close the file. However, if an exception occurs before the file can be
	// closed the file pointer will still be open and hence it cannot be accessed. 
    FILE* myFile = fopen("example.txt", "w");
    if (myFile == nullptr) {
        std::cerr << "Failed to open file.\n";
        return 1;
    }
    std::shared_ptr<FILE> mySharedFile(myFile, FileFinalizer());
    fprintf(mySharedFile.get(), "Hello, World!\n");

    // b) Create a free function and a stored lambda function that also play the role
    // of custom deleters for this problem.
    FILE* myFile2 = fopen("example2.txt", "w");
    std::shared_ptr<FILE> mySharedFile2(myFile2, FunctionFinalizer);
    fprintf(mySharedFile2.get(), "Hello, World!\n");


    FILE* myFile3 = fopen("example3.txt", "w");
    auto lambdaFinalizer = [](FILE* file) {
        if (file) {
            std::cout << "Closing file using lambda function.\n";
            fclose(file);
        }
    };
    std::shared_ptr<FILE> mySharedFile3(myFile3, lambdaFinalizer);
    fprintf(mySharedFile3.get(), "Hello, World!\n");

    // c) Test the code for three closer functions.
    // It was tested above. There will be three files example1.txt, example2.txt and example3.txt produced.
    // In the end, there will be the followings lines printed in the terminal:
    // Closing file using lambda function.
    // Closing file using free function.
    // Closing file.
    // This indicates the file being close. One interesting thing to note is that
    // the files are closed in the opposite order in which they are open, which indicates
    // that the stack frees the memory in a last in first out (LIFO) fashion.

    // d) Create a small loop in which records are added to the file; throw an exception 
    // at some stage in the loop, catch the exception and then open the file again. Does it work?
    auto lambdaFinalizer2 = [](FILE* file) {
        if (file) {
            std::cout << "Closing file for part d\n";
            fclose(file);
        }
    };
    try {
        FILE* myFile4 = fopen("example4.txt", "w");
        if (myFile4 == nullptr) {
            std::cerr << "Failed to open file.\n";
            return 1;
        }
        // Initialize with file closer
        std::shared_ptr<FILE> mySharedFile4(myFile4, lambdaFinalizer2);

        for (int i = 0; i < 5; ++i) {

            // Write some data to the file
            fprintf(mySharedFile4.get(), "Record %d\n", i);

            // Simulate an exception
            if (i == 2) {
                throw std::runtime_error("Exception occurred.");
            }

            // The file will be automatically closed when mySharedFile goes out of scope
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;

        // Open the file again if needed
        FILE* myFile4 = fopen("example4.txt", "a");
        if (myFile4 == nullptr) {
            std::cerr << "Failed to open file.\n";
            return 1;
        }

        std::shared_ptr<FILE> mySharedFile4(myFile4, FileFinalizer());
        fprintf(mySharedFile4.get(), "Recovered from exception\n");
    }
    // example_4.txt will show the following lines:
    // Record 0
    // Record 1
    // Record 2
    // Recovered from exception
    // Terminal will show:
    // Closing file for part d
    // Exception caught: Exception occured.
    // 
    // Here in this exercise, we break the record writing in loop i == 2.
    // There is a print of "Closing file for part d" which indicates that the
    // file did close successfully when the exception occur.
    // We then goes to the catch scope, which opens the file under append mode
    // The append mode still has the old record and "Recovered from exception"
    // which indicates that we successfully recover the writing.
    return 0;
}