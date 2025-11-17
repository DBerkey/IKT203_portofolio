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
    Track t(aArtist, aTitle, aYear, aGenre, aSource);
    gPlayer.AddToLibrary(t);

    std::cout << "Loaded song " << (aIndex + 1) << "/" << aTotalCount
              << ": " << aTitle << " - " << aArtist << "\n";

    return true;
}

// ===== FULL MUSIC PLAYER MENU =====
static void ShowMenu() {
    std::cout << "\n==== Console Music Player ====\n";
    std::cout << "1. Play next song\n";
    std::cout << "2. Play previous song\n";
    std::cout << "3. Show play history\n";
    std::cout << "4. Show library (forward)\n";
    std::cout << "5. Show library (backward)\n";
    std::cout << "6. Add song from library to Main Queue\n";
    std::cout << "7. Add song from library to Wish Queue\n";
    std::cout << "8. Load entire library into Main Queue\n";
    std::cout << "9. Exit\n";
    std::cout << "Choice: ";
}

void MusicApp::start()
{
    std::string filename ="DATA/song.txt";

<<<<<<< HEAD
    std::string filename = "DATA/songs.txt";

    // Read all songs from file
=======
    // Load songs from file into library
>>>>>>> dd9a693 (Updated Assignment-01 with final working version3)
    ReadSongsFromFile(filename, SongReadCallback);

    // Initially load library into MainQueue
    gPlayer.LoadToMainQueue();

    int choice = 0;

    do {
        ShowMenu();
        std::cin >> choice;
        // INVALID INPUT CHECK
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Please enter a NUMBER between 1 and 9.\n";
            choice = -1;
            continue;
        }

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

            case 4: // forward
                gPlayer.ShowLibraryForward();
                break;

            case 5: // backward
                gPlayer.ShowLibraryBackward();
                break;

            case 6: { // Add library song to MainQueue
                int index;
                std::cout << "Enter song index (starting from 1): ";
                std::cin >> index;
                gPlayer.AddLibrarySongToMainQueue(index);
                break;
            }

            case 7: { // Add library song to WishQueue
                int index;
                std::cout << "Enter song index (starting from 1): ";
                std::cin >> index;
                gPlayer.AddLibrarySongToWishQueue(index);
                break;
            }

            case 8:
                gPlayer.LoadToMainQueue();
                std::cout << "Library loaded into Main Queue.\n";
                break;

            case 9:
                std::cout << "Exiting...\n";
                break;

            default:
                std::cout << "Invalid choice.\n";
        }

    } while (choice != 9);
}
