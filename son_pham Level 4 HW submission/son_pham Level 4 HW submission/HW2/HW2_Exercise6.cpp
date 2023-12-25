/*
* Advanced C++ and Modern Design
* Level 4
* Author: Son Pham
* Homework 2, Exercise 6: Modifying the Elements of a Container
*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include <string>
#include <vector>

namespace {
    class Point {
    public:
        Point(double x, double y) : x_(x), y_(y) {}

        double getX() const { return x_; }
        double getY() const { return y_; }

        double distanceTo(const Point& other) const {
            double dx = x_ - other.x_;
            double dy = y_ - other.y_;
            return std::sqrt(dx * dx + dy * dy);
        }

    private:
        double x_;
        double y_;
    };

    struct PointEquality {
        bool operator()(const Point& p1, const Point& p2) const {
            return p1.getX() == p2.getX() && p1.getY() == p2.getY();
        }
    };

    std::string trim(const std::string& str) {
        size_t start = str.find_first_not_of(" \t");
        size_t end = str.find_last_not_of(" \t");
        if (start == std::string::npos) {
            return "";
        }
        return str.substr(start, end - start + 1);
    }

    std::string trim_if(const std::string& str, bool (*predicate)(char)) {
        auto startIt = std::find_if_not(str.begin(), str.end(), predicate);
        auto endIt = std::find_if_not(str.rbegin(), str.rend(), predicate).base();
        return (startIt >= endIt) ? std::string() : std::string(startIt, endIt);
    }

    std::vector<std::string> split(const std::string& str, char separator) {
        std::vector<std::string> tokens;
        size_t start = 0;
        size_t end = str.find(separator);
        while (end != std::string::npos) {
            tokens.push_back(str.substr(start, end - start));
            start = end + 1;
            end = str.find(separator, start);
        }
        tokens.push_back(str.substr(start));
        return tokens;
    }

    std::string join(const std::vector<std::string>& strings,
        const std::string& separator) {
        std::string result;
        for (size_t i = 0; i < strings.size(); ++i) {
            result += strings[i];
            if (i < strings.size() - 1) {
                result += separator;
            }
        }
        return result;
    }

    bool is_digit(char c) { return std::isdigit(static_cast<unsigned char>(c)); }
} // namespace

int main26() {
    // a) Consider the set S1 = {a,b,c,d,e,k} and the set S2 = {a,e}. Remove those
    // elements from S1 that are not in S2. The output set is {b,c,d,k}.
    std::set<char> S1 = { 'a', 'b', 'c', 'd', 'e', 'k' };
    std::set<char> S2 = { 'a', 'e' };

    for (auto it = S1.begin(); it != S1.end();) {
        if (S2.find(*it) == S2.end()) {
            it = S1.erase(it);
        }
        else {
            ++it;
        }
    }

    for (char c : S1) {
        std::cout << c << " ";
    }

    // b) Create a class Point that models two-dimensional points. Provide
    // constructors, member functions to access the coordinates of a point and a
    // member function to compute the distance between two points. You also need
    // to define a binary predicate that tests two points for equality (they have
    // the same values for their x and y coordinates). Now create an array of
    // points (duplicates allowed). Transform this array to a set of points with
    // no duplicates. Finally, filter this set (that is, remove points) of those
    // points that are not within a distance from some predefined point.
    //
    // Class Point is defined in the anonymous namespace.
    std::vector<Point> points = { {1.0, 2.0}, {3.0, 4.0}, {1.0, 2.0}, {5.0, 6.0} };
    std::set<Point, PointEquality> pointSet(points.begin(), points.end());

    Point predefinedPoint(3.0, 4.0);
    double maxDistance = 2.5;

    for (auto it = pointSet.begin(); it != pointSet.end();) {
        if (predefinedPoint.distanceTo(*it) > maxDistance) {
            it = pointSet.erase(it);
        }
        else {
            ++it;
        }
    }

    for (const Point& p : pointSet) {
        std::cout << "(" << p.getX() << ", " << p.getY() << ") ";
    }

    // c) We wish to create some functions that process strings in some way (in
    // a sense, we are emulating a simple version of the Boost C++ String
    // Algorithm library). A string can be seen as a special kind of vector whose
    // elements are characters. Create functions to do the following (in all cases
    // the input is a string):
    // - Trim all leading and trailing blanks(space, tabs etc.) from the string.
    // - Trim all leading and trailing blanks based on a unary predicate, e.g. is
    // a
    //   digit, is a member of some set of characters (you could call the function
    //   trim_if()).
    // - Produce a vector of strings from a character-separated string.
    // - Join two strings.
    std::string input = "   Hello,   World!   ";
    std::cout << "Trimmed: " << trim(input) << std::endl;

    std::string input2 = "   123abc456   ";
    std::cout << "Trimmed digits: " << trim_if(input2, is_digit) << std::endl;

    std::string input3 = "apple,orange,banana";
    std::vector<std::string> tokens = split(input3, ',');
    for (const std::string& token : tokens) {
        std::cout << token << " ";
    }
    std::cout << std::endl;

    std::vector<std::string> words = { "Hello", "World" };
    std::string joined = join(words, ", ");
    std::cout << "Joined: " << joined << std::endl;

    return 0;
}