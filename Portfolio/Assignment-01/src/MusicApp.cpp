#include <iostream>
#include <string>
#include "MusicApp.h"
#include "Player.h"
#include "Track.h"
#include "SharedLib.h"

// Global Player instance
static Player gPlayer;

// Callback used by SharedLib when reading songs
static bool SongReadCallback(
    const int aIndex,
    const int aTotalCount,
    const std::string& aArtist,
    const std::string& aTitle,
    const std::string& aYear,
    const std::string& aGenre,
    const std::string& aSource)
{
    // Create track and add it to the player's library
    Track t(aArtist, aTitle, aYear, aGenre, aSource);
    gPlayer.AddToLibrary(t);

    // Optional debug log
    std::cout << "Loaded song " << (aIndex + 1) << "/" << aTotalCount
              << ": " << aTitle << " - " << aArtist << "\n";

    return true;
}

// Menu displayed to the user
static void ShowMenu() {
    std::cout << "\n==== Console Music Player ====\n";
    std::cout << "1. Play next song\n";
    std::cout << "2. Play previous song\n";
    std::cout << "3. Show play history\n";
    std::cout << "4. Exit\n";
    std::cout << "Choice: ";
}

void MusicApp::start()
{

    std::string filename = "../DATA/songs.txt";

    // Read all songs from file
    ReadSongsFromFile(filename, SongReadCallback);

    // Load the library into the main play queue
    gPlayer.LoadToMainQueue();

    int choice = 0;

    do {
        ShowMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                gPlayer.PlayNextSong();
                break;

            case 2:
                gPlayer.PlayPreviousSong();
                break;

            case 3:
                gPlayer.ShowHistory();
                break;

            case 4:
                std::cout << "Exiting...\n";
                break;

            default:
                std::cout << "Invalid choice.\n";
        }

    } while (choice != 4);
}
