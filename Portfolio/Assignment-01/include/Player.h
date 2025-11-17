#pragma once
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <iostream>

#include "Track.h"

// The Player class contains all logic:
//  library
//  main queue
//  wish queue
//  history stack
//  play next / previous
class Player {
private:
    std::list<Track> library;     // Main function of the program
    std::queue<Track> mainQueue;  // Main queue
    std::queue<Track> wishQueue;  // Wish queue
    std::stack<Track> history;    // History

public:
    // Add a song to the library
    void AddToLibrary(const Track& track);

    // After the library is filled, load it into the mainQueue
    void LoadToMainQueue();

    // Play the next song (WishQueue first, then MainQueue)
    void PlayNextSong();

    // Put the previous song (from the history) back into the WishQueue
    void PlayPreviousSong();

    // Display the play history
    void ShowHistory() const;
};
