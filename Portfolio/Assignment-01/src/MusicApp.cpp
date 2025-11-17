#include <iostream>
#include <string>
#include "MusicApp.h"
#include "Player.h"
#include "Track.h"
#include "SharedLib.h"

// Global Player
static Player gPlayer;

// Callback for SharedLib
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

    std::cout << "Lest sang " << (aIndex + 1) << "/" << aTotalCount
              << ": " << aTitle << " - " << aArtist << "\n";

    return true;
}

// Meny
static void ShowMenu() {
    std::cout << "\n==== Console Music Player ====\n";
    std::cout << "1. Spill neste sang\n";
    std::cout << "2. Spill forrige sang\n";
    std::cout << "3. Vis historikk\n";
    std::cout << "4. Avslutt\n";
    std::cout << "Valg: ";
}

void MusicApp::start()
{
    std::string filename = "C:\\Users\\safwa\\IKT203_portofolio\\DATA\\songs.txt";

    ReadSongsFromFile(filename, SongReadCallback);

    gPlayer.LoadToMainQueue();

    int valg = 0;

    do {
        ShowMenu();
        std::cin >> valg;

        switch (valg) {
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
                std::cout << "Avslutter..\n";
                break;
            default:
                std::cout << "Ugyldig valg.\n";
        }

    } while (valg != 4);
}
