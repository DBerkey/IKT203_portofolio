#include "Player.h"


//  Library Functions

// Add a track to the main library (doubly-linked list)
void Player::AddToLibrary(const Track& track) {
    library.push_back(track);
}

// Load the entire library into the Main Queue
void Player::LoadToMainQueue() {
    for (const auto& t : library) {
        mainQueue.push(t);
    }
}



//  Playback Logic — PLAY NEXT SONG


void Player::PlayNextSong() {

    // 1. WISH QUEUE ALWAYS PLAYS FIRST (one song only)
    if (!wishQueue.empty()) {

        Track t = wishQueue.front();
        wishQueue.pop_front();

        std::cout << "\n Playing from WishQueue: ";
        t.Print();

        history.push(t);
        return;   // Only ONE song each call
    }

    // 2. If WishQueue empty ... play from MainQueue
    if (!mainQueue.empty()) {

        Track t = mainQueue.front();
        mainQueue.pop();

        std::cout << "\n Playing from MainQueue: ";
        t.Print();

        history.push(t);
        return;
    }

    // 3. Both queues empty
    std::cout << "\n No more songs to play.\n";
}



//  PLAY PREVIOUS SONG (History → front of WishQueue)

void Player::PlayPreviousSong() {

    if (history.empty()) {
        std::cout << "\n No songs in history.\n";
        return;
    }

    Track last = history.top();
    history.pop();

    // Must go at FRONT of WishQueue
    wishQueue.push_front(last);

    // Log into history again
    history.push(last);

    std::cout << "\n Previous song added to FRONT of WishQueue: ";
    last.Print();
}




//  HISTORY VIEW

void Player::ShowHistory() const {

    if (history.empty()) {
        std::cout << "\n History is empty.\n";
        return;
    }

    std::cout << "\n  Play History:\n";

    std::stack<Track> temp = history;

    while (!temp.empty()) {
        temp.top().Print();
        temp.pop();
    }
}




//  LIBRARY VIEW (Forward / Backward)

void Player::ShowLibraryForward() const {

    std::cout << "\n Library (forward):\n";

    for (const auto& t : library)
        t.Print();
}

void Player::ShowLibraryBackward() const {

    std::cout << "\n Library (backward):\n";

    for (auto it = library.rbegin(); it != library.rend(); ++it)
        it->Print();
}



//  Add specific library song to queues

void Player::AddLibrarySongToMainQueue(int index) {

    if (index < 1 || index > library.size()) {
        std::cout << "Invalid index.\n";
        return;
    }

    auto it = library.begin();
    std::advance(it, index - 1);

    mainQueue.push(*it);

    std::cout << "Added to Main Queue: ";
    it->Print();
}


void Player::AddLibrarySongToWishQueue(int index) {

    if (index < 1 || index > library.size()) {
        std::cout << "Invalid index.\n";
        return;
    }

    auto it = library.begin();
    std::advance(it, index - 1);

    wishQueue.push_back(*it);

    std::cout << "Added to Wish Queue: ";
    it->Print();
}
