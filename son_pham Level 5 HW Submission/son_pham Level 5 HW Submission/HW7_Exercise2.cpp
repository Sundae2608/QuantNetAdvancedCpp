/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 7, Exercise 2: Boost Bimap
*/

#include <iostream>
#include <boost/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

namespace bimaps = boost::bimaps;

namespace {
    // Alias for Boost UUID
    using UUID = boost::uuids::uuid;

    // Define tags for improved readability
    struct IpAddress {};
    struct DomainName {};
}

int main72() {
    using BimapType = bimaps::bimap<
        bimaps::tagged<UUID, IpAddress>,
        bimaps::tagged<std::string, DomainName>
    >;

    BimapType dns;

    // Create some instances of DNS
    UUID ip1 = boost::uuids::random_generator()();
    UUID ip2 = boost::uuids::random_generator()();
    UUID ip3 = boost::uuids::random_generator()();

    dns.insert({ ip1, "example.com" });
    dns.insert({ ip2, "example.net" });
    dns.insert({ ip3, "example.org" });

    // Find a domain name for a given IP address
    UUID searchIp = ip2; // Change this to the IP you want to search
    BimapType::left_iterator leftIter = dns.left.find(searchIp);
    if (leftIter != dns.left.end()) {
        std::cout << "Domain name for IP " << searchIp << ": " << leftIter->second << std::endl;
    }
    else {
        std::cout << "No domain name found for the given IP." << std::endl;
    }

    // Find an IP address for a given domain name
    std::string searchDomain = "example.org"; // Change this to the domain you want to search
    BimapType::right_iterator rightIter = dns.right.find(searchDomain);
    if (rightIter != dns.right.end()) {
        std::cout << "IP address for domain " << searchDomain << ": " << rightIter->second << std::endl;
    }
    else {
        std::cout << "No IP address found for the given domain." << std::endl;
    }

    // Print the contents of the DNS 'database'
    std::cout << "DNS Database:" << std::endl;
    for (const auto& entry : dns) {
        std::cout << "IP: " << entry.left << ", Domain: " << entry.right << std::endl;
    }

    return 0;
}