#include "Track.h"

// Represents a single track (song) in the music library.
Track::Track(const std::string& a,
             const std::string& t,
             const std::string& y,
             const std::string& g,
             const std::string& s)
    : artist(a), title(t), year(y), genre(g), source(s) {}

// Print track information to the console.
void Track::Print() const {
    std::cout << title << " - " << artist
              << " (" << year << ", " << genre << ")\n";
}
