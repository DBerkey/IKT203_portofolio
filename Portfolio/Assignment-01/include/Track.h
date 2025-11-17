#pragma once
#include <string>
#include <iostream>


// Represents a song track in the library.

class Track {
public:
    std::string artist;
    std::string title;
    std::string year;
    std::string genre;
    std::string source;

    Track() = default;

    Track(const std::string& a,
          const std::string& t,
          const std::string& y,
          const std::string& g,
          const std::string& s);

    void Print() const;
};
