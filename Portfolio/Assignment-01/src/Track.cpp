#include "Track.h"

Track::Track(const std::string& a,
             const std::string& t,
             const std::string& y,
             const std::string& g,
             const std::string& s)
    : artist(a), title(t), year(y), genre(g), source(s) {}

void Track::Print() const {
    std::cout << title << " - " << artist
              << " (" << year << ", " << genre << ")\n";
}
