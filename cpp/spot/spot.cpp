#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

struct Song {
    string title;
    string singer;
    string genre;
    string album;
    string year;
    Song* next;
};

struct Playlist {
    string name;
    Song* head;
    Playlist* next;
};

Song* createSong(const string& title, const string& singer, const string& genre, const string& album, const string& year) {
    Song* newSong = new Song;
    newSong->title = title;
    newSong->singer = singer;
    newSong->genre = genre;
    newSong->album = album;
    newSong->year = year;
    newSong->next = nullptr;
    return newSong;
}

void addSong(Song*& head, const string& title, const string& singer, const string& genre, const string& album, const string& year) {
    Song* newSong = createSong(title, singer, genre, album, year);
    if (!head) {
        head = newSong;
    } else {
        Song* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newSong;
    }
}

void removeSongByIndex(Song*& head, int index) {
    if (!head) {
        cout << "The playlist is empty.\n";
        return;
    }
    Song* temp = head;
    Song* prev = nullptr;

    int currentIndex = 0;
    while (temp && currentIndex != index) {
        prev = temp;
        temp = temp->next;
        currentIndex++;
    }

    if (!temp) {
        cout << "Invalid song selection.\n";
        return;
    }

    if (!prev) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }
    cout << "Removed song: " << temp->title << " by " << temp->singer << '\n';
    delete temp;
}

void saveToFile(Song* head, const string& playlistName) {
    string filename = playlistName + ".txt";
    ofstream file(filename);
    if (!file) {
        cout << "Error opening file for writing!\n";
        return;
    }
    while (head) {
        file << head->title << "," << head->singer << "," << head->genre << "," << head->album << "," << head->year << '\n';
        head = head->next;
    }
    file.close();
    cout << "Playlist saved to " << filename << '\n';
}

void loadFromFile(Playlist*& playlists, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file for reading!\n";
        return;
    }

    string name = filename.substr(0, filename.find('.'));
    Playlist* newPlaylist = new Playlist{name, nullptr, playlists};
    playlists = newPlaylist;

    string line, title, singer, genre, album, year;
    while (getline(file, line)) {
        size_t comma1 = line.find(',');
        size_t comma2 = line.find(',', comma1 + 1);
        size_t comma3 = line.find(',', comma2 + 1);
        size_t comma4 = line.find(',', comma3 + 1);

        if (comma1 != string::npos && comma2 != string::npos && comma3 != string::npos && comma4 != string::npos) {
            title = line.substr(0, comma1);
            singer = line.substr(comma1 + 1, comma2 - comma1 - 1);
            genre = line.substr(comma2 + 1, comma3 - comma2 - 1);
            album = line.substr(comma3 + 1, comma4 - comma3 - 1);
            year = line.substr(comma4 + 1);
            addSong(newPlaylist->head, title, singer, genre, album, year);
        }
    }
    file.close();
    cout << "Playlist \"" << name << "\" loaded from " << filename << '\n';
}

Playlist* selectPlaylist(Playlist* playlists) {
    if (!playlists) {
        cout << "No playlists available.\n";
        return nullptr;
    }
    cout << "Available playlists:\n";
    Playlist* current = playlists;
    int index = 1;
    vector<Playlist*> options;
    while (current) {
        cout << index << ". " << current->name << '\n';
        options.push_back(current);
        current = current->next;
        index++;
    }

    int choice;
    cout << "\n";
    cout << "Select a playlist: ";
    cin >> choice;
    if (choice < 1 || choice > options.size()) {
        cout << "Invalid selection.\n";
        return nullptr;
    }
    return options[choice - 1];
}

int displaySongsWithIndex(Song* head) {
    if (!head) {
        cout << "The playlist is empty.\n";
        return 0;
    }
    int index = 0;
    while (head) {
        cout << index + 1 << ". " << head->title << " by " << head->singer 
             << " (" << head->genre << ", " << head->album << ", " << head->year << ")\n";
        head = head->next;
        index++;
    }
    return index;
}

void sortPlaylist(Song*& head, int sortBy) {
    if (!head) return;

    vector<Song*> songVector;
    Song* temp = head;
    while (temp) {
        songVector.push_back(temp);
        temp = temp->next;
    }

    switch (sortBy) {
        case 1:
            sort(songVector.begin(), songVector.end(), [](Song* a, Song* b) { return a->title < b->title; });
            break;
        case 2:
            sort(songVector.begin(), songVector.end(), [](Song* a, Song* b) { return a->singer < b->singer; });
            break;
        case 3:
            sort(songVector.begin(), songVector.end(), [](Song* a, Song* b) { return a->genre < b->genre; });
            break;
        case 4:
            sort(songVector.begin(), songVector.end(), [](Song* a, Song* b) { return a->album < b->album; });
            break;
        case 5:
            sort(songVector.begin(), songVector.end(), [](Song* a, Song* b) { return a->year < b->year; });
            break;
        default:
            cout << "Invalid sort criterion.\n";
            return;
    }

    head = songVector[0];
    temp = head;
    for (size_t i = 1; i < songVector.size(); ++i) {
        temp->next = songVector[i];
        temp = temp->next;
    }
    temp->next = nullptr;
}


void saveProgramState(Playlist* playlists) {
    string filename = "spot.txt";
    ofstream file(filename);
    if (!file) {
        cout << "Error opening file for saving program state!\n";
        return;
    }

    Playlist* currentPlaylist = playlists;
    while (currentPlaylist) {
        file << currentPlaylist->name << '\n';
        Song* currentSong = currentPlaylist->head;
        while (currentSong) {
            file << currentSong->title << "," << currentSong->singer << "," 
                 << currentSong->genre << "," << currentSong->album << "," << currentSong->year << '\n';
            currentSong = currentSong->next;
        }
        file << '\n';
        currentPlaylist = currentPlaylist->next;
    }

    file.close();
    cout << "Program state saved to " << filename << '\n';
}

void loadProgramState(Playlist*& playlists) {
    string filename = "spot.txt";
    ifstream file(filename);
    if (!file) {
        cout << "No previous program state found, starting fresh.\n";
        return;
    }
    else {
        cout << "Previous program state found, loading...\n";
    }

    string line;
    Playlist* lastPlaylist = nullptr;

    while (getline(file, line)) {
        if (line.empty()) continue;

        if (line.find(',') == string::npos) {
            string playlistName = line;

            Playlist* newPlaylist = new Playlist{playlistName, nullptr, nullptr};

            if (!lastPlaylist) {
                playlists = newPlaylist;
            } else {
                lastPlaylist->next = newPlaylist;
            }

            lastPlaylist = newPlaylist;

            while (getline(file, line) && line.find(',') != string::npos) {
                size_t comma1 = line.find(',');
                size_t comma2 = line.find(',', comma1 + 1);
                size_t comma3 = line.find(',', comma2 + 1);
                size_t comma4 = line.find(',', comma3 + 1);

                string title = line.substr(0, comma1);
                string singer = line.substr(comma1 + 1, comma2 - comma1 - 1);
                string genre = line.substr(comma2 + 1, comma3 - comma2 - 1);
                string album = line.substr(comma3 + 1, comma4 - comma3 - 1);
                string year = line.substr(comma4 + 1);

                addSong(lastPlaylist->head, title, singer, genre, album, year);
            }
        }
    }
    file.close();
}

void displaySpotBanner() {
    cout << R"(
         ______                  
        / _____)             _   
       ( (____  ____   ___ _| |_ 
        \____ \|  _ \ / _ (_   _)
        _____) ) |_| | |_| || |_ 
       (______/|  __/ \___/  \__)
               |_|               

             Welcome to Spot!
    Our Personal Music Playlist Manager
    )" << endl;
}

int main() {
    Playlist* playlists = nullptr;
    string choice, title, singer, genre, album, year, filename;

    displaySpotBanner();
    cout << "\n";
    loadProgramState(playlists);

    while (true) {
        cout << "\n1. Create Playlist\n2. Add Song\n3. Remove Song\n4. Display Playlist\n";
        cout << "5. Save Playlist\n6. Load Playlist\n7. Sort Playlist\n8. Exit\nChoose an option: ";
        cin >> choice;

        if (choice == "1") {
            cout << "\n";
            cout << "Enter playlist name: ";
            string playlistName;
            cin >> playlistName;
            Playlist* newPlaylist = new Playlist{playlistName, nullptr, playlists};
            playlists = newPlaylist;
            cout << "\n";
            cout << "Playlist created.\n";

        } else if (choice == "2") {
            cout << "\n";
            Playlist* selectedPlaylist = selectPlaylist(playlists);
            if (!selectedPlaylist) continue;

            cout << "\n" << "Enter song title: ";
            cin.ignore();
            getline(cin, title);
            cout << "\n" << "Enter singer's name: ";
            getline(cin, singer);
            cout << "\n" << "Enter genre: ";
            getline(cin, genre);
            cout << "\n" << "Enter album: ";
            getline(cin, album);
            cout << "\n" << "Enter year: ";
            getline(cin, year);

            addSong(selectedPlaylist->head, title, singer, genre, album, year);
            cout << "Song added: " << title << " by " << singer << '\n';
        } else if (choice == "3") {
            cout << "\n";
            Playlist* selectedPlaylist = selectPlaylist(playlists);
            if (!selectedPlaylist) continue;

            cout << "\n" << "Song lists: \n";
            int songCount = displaySongsWithIndex(selectedPlaylist->head);
            if (songCount == 0) continue;

            int songIndex;
            cout << "Select a song to remove: ";
            cin >> songIndex;
            if (songIndex < 1 || songIndex > songCount) {
                cout << "Invalid selection.\n";
                continue;
            }
            removeSongByIndex(selectedPlaylist->head, songIndex - 1);

        } else if (choice == "4") {
            cout << '\n';
            Playlist* selectedPlaylist = selectPlaylist(playlists);
            if (!selectedPlaylist) continue;
            cout << '\n';
            cout << "Songs in the " << selectedPlaylist->name << ": \n";
            cout << '\n';
            cout << "Song name by singer (genre, album, year)\n";
            displaySongsWithIndex(selectedPlaylist->head);

        } else if (choice == "5") {
            cout << "\n";
            Playlist* selectedPlaylist = selectPlaylist(playlists);
            if (!selectedPlaylist) continue;

            saveToFile(selectedPlaylist->head, selectedPlaylist->name);

        } else if (choice == "6") {
            cout << "\n";
            cout << "Enter file to load: ";
            cin >> filename;
            loadFromFile(playlists, filename);

        } else if (choice == "7") {
            Playlist* selectedPlaylist = selectPlaylist(playlists);
            cout << '\n';
            if (!selectedPlaylist) continue;

            cout << "Sort by:\n";
            cout << "1. Title\n";
            cout << "2. Singer\n";
            cout << "3. Genre\n";
            cout << "4. Album\n";
            cout << "5. Year\n";
            cout << "Choose what to sort: ";
            cin >> choice;

            sortPlaylist(selectedPlaylist->head, stoi(choice));
            cout << "Playlist sorted.\n";
            displaySongsWithIndex(selectedPlaylist->head);
        } else if (choice == "8") {
            cout << "\n";
            cout << "Saving program state and exiting...\n";
            saveProgramState(playlists);
            cout << "\n";	
            cout << "Goodbye!\n";
            cout << "\n";	
            break;

        } else {
            cout << "Invalid option. Please try again.\n";
        }
    }
    return 0;
}