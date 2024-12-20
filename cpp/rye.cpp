#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

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

string playlistdir = "playlist/"; //folder to save playlist files

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
    getline(cin, newPlaylist->name);

    // allocating playlist's memory
    newPlaylist->next = nullptr;
    
    // checking if there's any playlist beforehand
    if (!*head)
    {
        *head = newPlaylist;
        ofstream file(playlistdir + newPlaylist->name + ".txt", ios::app); //making new file for playlist
        return;
    } 
    
    // traversing to the end of the playlist's list
    playlist *temp = *head; 
    while (temp->next) temp = temp->next; 
    
    // insert the newPlaylist's memory into the next node of temp
    temp->next = newPlaylist;
    ofstream file(playlistdir + newPlaylist->name + ".txt", ios::app); //same
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

void WriteFile(const string& playlistdir, const string& filename, const songs* newSong){
    ofstream file(playlistdir + filename + ".txt", ios::app); //open file according to selected playlist
    if (file.is_open()) {
        file << "Song Name: " << newSong->song << "\n";
        file << "Artist: " << newSong->artist << "\n";
        file << "Lyricist: " << newSong->lyricist << "\n";
        file << "Album: " << newSong->album << "\n";
        file << "Composer: " << newSong->composer << "\n";
        file << "Genre: " << newSong->genre << "\n";
        file << "Year: " << newSong->year << "\n";
        file << "Duration: " << newSong->duration << "\n";
        file << "-------------------------\n";
        file.close();
        cout << "Song succesfully added and saved to playlist!\n";
    } else {
        cout << "Unable to open file for saving song data.\n";
    }
}

void LoadFile(playlist** head) {
    //check if the directory exist or not if it is not then it will create directory
    if (!std::filesystem::exists(playlistdir)) {
        std::filesystem::create_directory(playlistdir);
    }

    for (const auto& entry : std::filesystem::directory_iterator(playlistdir)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            playlist* newPlaylist = new playlist;
            newPlaylist->name = entry.path().stem().string(); //get the filename without .txt
            newPlaylist->songList = nullptr;
            newPlaylist->next = nullptr;

            // check for duplicate playlists
            playlist* temp = *head;
            while (temp) {
                if (temp->name == newPlaylist->name) {
                    delete newPlaylist; // avoid duplicate playlists
                    newPlaylist = nullptr;
                    break;
                }
                temp = temp->next;
            }
            if (!newPlaylist) continue;

            // insert new playlist at the head
            newPlaylist->next = *head;
            *head = newPlaylist;

            // load songs from file
            ifstream file(entry.path());
            if (file.is_open()) {
                string line;
                songs* lastSong = nullptr;

                while (getline(file, line)) {
                    if (line.find("Song Name:") == 0) {
                        songs* newSong = new songs;
                        newSong->song = line.substr(11); // find the song name after song name:

                        //load songs data
                        getline(file, line); newSong->artist = line.substr(8); 
                        getline(file, line); newSong->lyricist = line.substr(10);
                        getline(file, line); newSong->album = line.substr(7);
                        getline(file, line); newSong->composer = line.substr(9);
                        getline(file, line); newSong->genre = line.substr(7);

                        try {
                            getline(file, line); newSong->year = stoi(line.substr(6));
                            getline(file, line); newSong->duration = stoi(line.substr(10));
                        } catch (const std::exception& e) {
                            cout << "Error parsing song attributes in file: " << entry.path() << "\n";
                            delete newSong; 
                            continue;
                        }

                        // insert songs into playlist
                        newSong->next = nullptr;
                        newSong->prev = lastSong;
                        if (!newPlaylist->songList) {
                            newPlaylist->songList = newSong;
                        } else {
                            lastSong->next = newSong;
                        }
                        lastSong = newSong;
                    }
                }
                file.close();
            } else {
                cout << "Error opening file " << entry.path() << "\n";
            }
        }
    }
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
    cin.ignore();

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

    string filename = temp->name; //set filename to open file according to current playlist

   // declaring new node of songs
   songs* newSong = new songs;


    // input data of a song's node
    cout << "Enter song name:";                 getline(cin, newSong->song); 
    cout << "Enter artist\'s name:";            getline (cin, newSong->artist);
    cout << "Enter lyricist\'s name:";          getline(cin, newSong->lyricist);
    cout << "Enter album\'s name:";             getline (cin, newSong->album);
    cout << "Enter composer\'s name:";          getline(cin, newSong->composer);
    cout << "Enter genre\'s name:";             getline(cin, newSong->genre);

    cout << "Enter songs\'s year of release:";  while(!(cin >> newSong->year)) {
        cout << "Invalid input. Please enter an integer: ";
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }; 
    
    cout << "Enter song\'s duration:";          while(!(cin >> newSong->duration)){
        cout << "Invalid input. Please enter an integer: ";
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }; 

    // allocate song's list memory
    newSong->next = nullptr;
    newSong->prev = nullptr;

    // check if there's any previous head or not
    if (!temp->songList) 
    {
        temp->songList = newSong; 
        WriteFile(playlistdir ,filename, newSong);
        return;
    }
    else
    {
        songs *sings = temp->songList; 
        // traverse 'till the end of the playlist
        while (sings->next) sings = sings->next;
        sings->next = newSong;
        WriteFile(playlistdir, filename, newSong);
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
    LoadFile(&head);
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
        cin.ignore();
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
