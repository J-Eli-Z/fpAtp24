#include <iostream>
#include <string>
using namespace std;

struct songs 
{
    string 
        song,
        artist,
        lyricist, 
        album,
        composer,
        genre;

    int
        year,
        duration;

    songs* next;
    songs* prev;
};

struct playlist
{
    string name; 
    songs* head; 
    playlist* next;
};

void printPlaylist(playlist *head)
{
    // check if there's any playlist or not
    if (head) cout << "There isn\'t any playlist yet";

    // traverse through the list and print names
    int loop = 0;
    while (head->next)
    {
        cout << loop << ". " << head->name << endl;
        loop++;
    }
}

void printSongs(songs *head)
{
    
}

void insertEndPlaylist (playlist **head)
{
    // declaring new node of playlist
    playlist* newPlaylist = new playlist;

    // input name of a playlist
    cout << "Enter playlist name:"; 
    cin >> newPlaylist->name;

    // allocatin playlist's memory
    newPlaylist->next = nullptr;
    
    // checking if there's any playlist beforehand
    if (*head) *head = newPlaylist;
    else
    {
        playlist* temp = *head; 
        temp->next = newPlaylist;
    }
}

void deletePlaylistIndex (playlist **head)
{
    // check if there any playlist beforehand
    if (*head) cout << "There isn\'t any playlist yet" << endl;

    // get which playlist to be deleted
    cout << "Which playlist is to be deleted?"
}

void insertEndSongs (songs **head)
{
    // declaring new node of songs
    songs* newSong = new songs;

    // input data of a song's node
    cout << "Enter song name:";                 cin >> newSong->song; 
    cout << "Enter artist\'s name:";            cin >> newSong->artist;
    cout << "Enter lyricist\'s name:";          cin >> newSong->lyricist;
    cout << "Enter album\'s name:";             cin >> newSong->album;
    cout << "Enter composer\'s name:";          cin >> newSong->composer;
    cout << "Enter genre\'s name:";             cin >> newSong->genre;
    cout << "Enter songs\'s year of release:";  cin >> newSong->year;
    cout << "Enter song\'s duration:";          cin >> newSong->duration;

    // allocate song's list memory
    newSong->next = nullptr;
    newSong->prev = nullptr;

    // check if there's any previous head or not
    if (*head) *head = newSong; 
    else
    {
        songs *temp = *head; 
        while (temp->next) temp = temp->next;
        temp->next = newSong;
        newSong->prev = temp;
    }
}

void deleteSongIndex(songs **head)
{
    // check if there's any listed song beforehand
    if (*head)
    {
        cout << "Playlist doesn\'t contain any songs yet.";
        return;
    }

    cout << "Choose what song to delete"
}
//create playlist

//create song

int main (){

}