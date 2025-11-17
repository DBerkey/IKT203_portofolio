#pragma once
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <iostream>

#include "Track.h"

// Player-klassen inneholder all logikk:
//  bibliotek
//  main queue
//  wish queue
//  historikk stack
//  play next / previous
class Player {
private:
    std::list<Track> library;     // Hele sangbiblioteket
    std::queue<Track> mainQueue;  // Hovedkø
    std::queue<Track> wishQueue;  // Ønskekø
    std::stack<Track> history;    // Historikk

public:
    // Legg en sang inn i biblioteket
    void AddToLibrary(const Track& track);

    // Etter at biblioteket er fylt opp, last inn i mainQueue
    void LoadToMainQueue();

    // Spill neste sang (WishQueue først, så MainQueue)
    void PlayNextSong();

    // Legg forrige sang (fra historikk) tilbake i WishQueue
    void PlayPreviousSong();

    // Vis spillhistorikken
    void ShowHistory() const;
};
