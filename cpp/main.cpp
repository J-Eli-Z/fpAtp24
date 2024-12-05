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

// function to print out the amount of playlist there is --> Fika
void printPlaylist(playlist** head)
{
   if (!head)
   {
        cout << "There isn\'t any playlist added yet.\n";
        return;
    }   
    
    cout << "Playlist:\n";
    int index = 0;
    while (head) 
    {
        cout << index++ << ". " << head->name << endl;
        head = head->next;
    }

}

// function to print out the songs listed in a playlist --> added by Fika
void printSongs(playlist** head)
{
    cout << "Which playlist?" << endl; 

    
    if (!head){
        cout << "No songs listed in the playlist yet.";
        return;
    }

    cout<< "Lagu di playlist:\n";
    int index = 0;
    while(head){
        cout << index++ << ". "<<head->song<<"\n"
        <<" by " << head->artist
        <<" (" <<head->year<<")\n";
        head=head->next;
    }
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
    cout << "Which playlist is to be deleted?";
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

    cout << "Choose what song to delete";
}
//create playlist

void createPlaylist(songs **head){
    if(*head)
    {
        cout << "there's no song to add yet \n";
        return;
    }

    cout <<"Choose songs to add: \n";
}

//create song

int main (){

}
