#include "Player.h"

// Adds a track to the library
void Player::AddToLibrary(const Track& track) {
    library.push_back(track);
}

// Fills the main queue with all tracks from the library
void Player::LoadToMainQueue() {
    for (const auto& t : library) {
        mainQueue.push(t);
    }
}

// Plays the next song:
// 1. If WishQueue is not empty .. play from WishQueue
// 2. Otherwise .. play from MainQueue
void Player::PlayNextSong() {
    if (!wishQueue.empty()) {
        Track t = wishQueue.front();
        wishQueue.pop();

        std::cout << "\n Playing from WishQueue: ";
        t.Print();

        history.push(t);
    }
    else if (!mainQueue.empty()) {
        Track t = mainQueue.front();
        mainQueue.pop();

        std::cout << "\n Playing from MainQueue: ";
        t.Print();

        history.push(t);
    }
    else {
        std::cout << "\n No more songs to play.\n";
    }
}

// Moves the previously played song back to the WishQueue
void Player::PlayPreviousSong() {
    if (history.empty()) {
        std::cout << "\n No songs in history.\n";
        return;
    }

    Track last = history.top();
    history.pop();

    wishQueue.push(last);

    std::cout << "\n Previous song added to WishQueue: ";
    last.Print();
}

// Displays play history (last played on top)
void Player::ShowHistory() const {
    if (history.empty()) {
        std::cout << "\n History is empty.\n";
        return;
    }

    std::cout << "\n  Play History:\n";

    // Create a copy so we don’t modify the real stack
    std::stack<Track> temp = history;

    while (!temp.empty()) {
        temp.top().Print();
        temp.pop();
    }
}
