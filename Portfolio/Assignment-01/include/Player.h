#pragma once
#include <list>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <iostream>

#include "Track.h"

class Player {
private:
    std::list<Track> library;     // Doubly linked list (std::list)
    std::queue<Track> mainQueue;  // Main queue
    std::deque<Track> wishQueue;  // Wish queue (double ended)
    std::stack<Track> history;    // History stack

public:
    void AddToLibrary(const Track& track);
    void LoadToMainQueue();
    void PlayNextSong();
    void PlayPreviousSong();
    void ShowHistory() const;
    void ShowLibraryForward() const;
    void ShowLibraryBackward() const;
    void AddLibrarySongToMainQueue(int index);
    void AddLibrarySongToWishQueue(int index);

};
