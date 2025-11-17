#pragma once
#include <string>
#include <iostream>

// Representerer en sang (track) i biblioteket.
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
