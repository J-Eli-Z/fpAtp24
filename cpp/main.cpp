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
    songs* songList = nullptr; 
    playlist* next;
};

// function to print out the amount of playlist there is --> Fika
void printPlaylist(playlist** head)
{
    // check if there's any playlist listed
    if (!*head)
    {
        cout << endl << "There isn\'t any playlist added yet.\n"; 
        return;
    }

    // listing out all of the playlist listed
    cout << endl << "List of playlists:\n";
    int index = 0;
    playlist *temp = *head;
    while (temp) 
    {
        cout << ++index << ". " << temp->name << endl;
        temp = temp->next;
    }

    cout << endl; 
}

/* 
*head = NULL; 

&head --> means &(*head) = **head --> memory address of a pointer variable 

dereference the memory address of a pointer variable

so memory address of the memory address of a pointer variable --> doesn't that mean i could just pass the inital value? like just head :v
*/

// function to print out the songs listed in a playlist --> added by Fika
void printSongs(playlist** head)
{
    // check if there's any playlist listed
    if (!*head)
    {
        cout << endl << "There isn\'t any playlist added yet.\n"; 
        return;
    }

    // asking which playlist is it
    printPlaylist(head);
    cout << "Choose a number: ";
    unsigned int num; cin >> num;  

    // find the indexed playlist name by traversing through the listed playlists
    int pos = 0; 
    playlist *temp = *head;
    while (temp && pos != (num - 1))
    {
        temp = temp->next; 
        pos++;
    }

    // check if the index is over the list's quantity
    if (!temp)
    {
        cout << "Number is bigger than the amount of listed playlist" << endl;
        return;
    }

    // check if there's any songs inside the playlist
    if (!temp->songList)
    {
        cout << "There isn\'t any songs added in this playlist yet.\n";
        return;
    }

    // print out the list of songs in playlist
    cout << endl << temp->name << ":" << endl;
    pos = 0;
    songs* now = temp->songList;
    while(now)
    {
        cout << ++pos << ". " << now->song << " by " << now->artist << endl;
        now = now->next;
    }

    cout << endl;
}

// function to insert a playlist to the end of the playlist
void insertEndPlaylist (playlist **head)
{
    // declaring new node of playlist
    playlist* newPlaylist = new playlist;

    // input name of a playlist
    cout << endl << "Enter playlist name:"; 
    cin >> newPlaylist->name;

    // allocating playlist's memory
    newPlaylist->next = nullptr;
    
    // checking if there's any playlist beforehand
    if (!*head)
    {
        *head = newPlaylist;
        return;
    } 
    
    // traversing to the end of the playlist's list
    playlist *temp = *head; 
    while (temp->next) temp = temp->next; 
    
    // insert the newPlaylist's memory into the next node of temp
    temp->next = newPlaylist;
}

// function to delete a playlist from the list by index
void deletePlaylistIndex (playlist **head)
{
    // check if there's any playlist listed
    if (!*head)
    {
        cout << "There isn\'t any playlist added yet.\n"; 
        return;
    }
    
    // get which playlist to be deleted
    printPlaylist(head);
    cout << "Choose a number: ";
    unsigned int num; cin >> num; 

    // traverse to the indexed list
    int pos = 0;
    playlist * temp = *head; 
    while (temp && pos != (num - 2))
    {
        temp = temp->next; 
        pos++;
    }

    // check if the index is over the list's quantity
    if (!temp || !temp->next)
    {
        cout << "Number is bigger than the amount of listed playlist" << endl;
        return; 
    }

    playlist * next = temp->next->next;
    delete temp->next;
    temp->next = next;
}

void insertEndSongs (playlist **head)
{
    // check if there's any playlist listed
    if (!*head)
    {
        cout << "There isn\'t any playlist added yet.\n"; 
        return;
    }
    
    // get which playlist to be inserted with a new song
    printPlaylist(head);
    cout << "Choose a number: "; 
    unsigned int num; cin >> num;

    // find the indexed playlist name by traversing through the listed playlists
    int pos = 0; 
    playlist *temp = *head;
    while (temp && pos != (num - 1))
    {
        temp = temp->next; 
        pos++;
    }
    
    // check if the index is over the list's quantity
    if (!temp)
    {
        cout << "Number is bigger than the amount of listed playlist" << endl;
        return;
    }

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
    if (!temp->songList) 
    {
        temp->songList = newSong; 
        return;
    }
    else
    {
        songs *sings = temp->songList; 
        // traverse 'till the end of the playlist
        while (sings->next) sings = sings->next;
        sings->next = newSong;
    }
}

void deleteSongIndex(playlist **head)
{
    // check if there's any playlist listed
    if (!*head)
    {
        cout << "There isn\'t any playlist added yet.\n"; 
        return;
    }
    
    // get the index of a song
    printSongs(head);
    cout << "Choose a number: "; 
    unsigned int num; cin >> num;

    // declaration of the now variable which is of songs struct6
    playlist *temp = *head;
    songs* now = temp->songList;

    // find the indexed song name by traversing through the listed playlists
    int pos = 0; 
    while (now && pos != (num - 2))
    {
        now = now->next; 
        pos++;
    }
    
    // check if the index is over the list's quantity
    if (!now)
    {
        cout << "Number is bigger than the amount of listed songs" << endl;
        return; 
    }

    // deleting the indexed song's memory
    songs *next = now->next->next;
    delete now->next;
    now->next = next;
}

int main (){
    playlist* head = nullptr; 
    int choose;
    
    do 
    {
        cout << "-----------------------" << endl;
        cout << ">-WELCOME TO SPOTIBRO-<" << endl;
        cout << "-----------------------" << endl;
        cout << "Choose what action you wanna do:" << endl;
        cout << "1. Add Playlist" << endl;
        cout << "2. Add Song in a Playlist" << endl;
        cout << "3. Delete Playlist" << endl;
        cout << "4. Delete Song in a Playlist" << endl;
        cout << "5. Print out all the Playlist" << endl;
        cout << "6. Print out all the songs in a Playlist" << endl;
        cin >> choose;
        switch (choose)
        {
            case 1:
                insertEndPlaylist(&head);
                break;

            case 2: 
                insertEndSongs(&head);
                break;
            
            case 3:
                deletePlaylistIndex(&head);
                break;
            
            case 4:
                deleteSongIndex(&head);
                break;
            
            case 5:
                printPlaylist(&head);
                break;
            
            case 6:
                printSongs(&head);
                break;
            
            default:
                cout << "Please choose again" << endl;
                break;
        }
    }
    while (choose != 9);
}
