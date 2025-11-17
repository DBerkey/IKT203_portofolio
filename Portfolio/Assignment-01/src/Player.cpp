#include "Player.h"

// Legger sang i biblioteket
void Player::AddToLibrary(const Track& track) {
    library.push_back(track);
}

//  HerFyller MainQueue med alle sanger fra biblioteket
void Player::LoadToMainQueue() {
    for (const auto& t : library) {
        mainQueue.push(t);
    }
}

// Spiller neste sang:
// 1. Hvis WishQueue har noe.... spill fra den først
// 2. Hvis tom ... spill fra MainQueue
void Player::PlayNextSong() {
    if (!wishQueue.empty()) {
        Track t = wishQueue.front();
        wishQueue.pop();

        std::cout << "\n Spiller fra WishQueue: ";
        t.Print();

        history.push(t);
    }
    else if (!mainQueue.empty()) {
        Track t = mainQueue.front();
        mainQueue.pop();

        std::cout << "\n Spiller fra MainQueue: ";
        t.Print();

        history.push(t);
    }
    else {
        std::cout << "\n Ingen flere sanger å spille.\n";
    }
}

// Legger forrige sang tilbake i WishQueue (spilles neste gang)
void Player::PlayPreviousSong() {
    if (history.empty()) {
        std::cout << "\n Ingen sanger i historikken.\n";
        return;
    }

    Track last = history.top();
    history.pop();

    wishQueue.push(last);

    std::cout << "\n Forrige sang ble lagt i WishQueue: ";
    last.Print();
}

// Viser spillhistorikk (sist spilt øverst)
void Player::ShowHistory() const {
    if (history.empty()) {
        std::cout << "\n Historikken er tom.\n";
        return;
    }

    std::cout << "\n  Spillhistorikk:\n";

    // Lager kopi for å ikke ødelegge ekte stack
    std::stack<Track> temp = history;

    while (!temp.empty()) {
        temp.top().Print();
        temp.pop();
    }
}
