#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Node of the doubly linked list: one song per node.
class Node {
public:
    string title;
    string artist;
    Node* prev;
    Node* next;

    Node(string songTitle, string artistName) {
        title = songTitle;
        artist = artistName;
        prev = nullptr;
        next = nullptr;
    }
};

class MusicPlaylist {
private:
    Node* head;       // Points to the first song.
    Node* current;    // Points to the currently selected/playing song.

public:
    MusicPlaylist() {
        head = nullptr;
        current = nullptr;
    }

    ~MusicPlaylist() {
        Node* q = head;
        while (q != nullptr) {
            Node* p = q;
            q = q->next;
            delete p;
        }
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    // Add a song at the end of the playlist.
    void addSong(const string& title, const string& artist) {
        Node* p = new Node(title, artist); // p points to the newly created node.

        if (head == nullptr) {
            head = p;
            current = p;
        } else {
            Node* q = head; // q traverses the list to its last node.
            while (q->next != nullptr) {
                q = q->next;
            }
            q->next = p;
            p->prev = q;
        }
        cout << "Song added: " << title << " - " << artist << "\n";
    }

    // Delete the first song whose title matches the input.
    void deleteSong(const string& title) {
        Node* q = head; // q searches for the song.
        while (q != nullptr && q->title != title) {
            q = q->next;
        }

        if (q == nullptr) {
            cout << "Song not found: " << title << "\n";
            return;
        }

        Node* p = q; // p points to the node that will be deleted.

        if (p->prev != nullptr) {
            p->prev->next = p->next;
        } else {
            head = p->next; // The first node is being deleted.
        }

        if (p->next != nullptr) {
            p->next->prev = p->prev;
        }

        if (current == p) {
            current = (p->next != nullptr) ? p->next : p->prev;
        }

        delete p;

        if (head == nullptr) {
            current = nullptr;
        }

        cout << "Song deleted: " << title << "\n";
    }

    // Display songs from head to tail using next pointers.
    void displayPlaylist() const {
        if (head == nullptr) {
            cout << "Playlist is empty.\n";
            return;
        }

        cout << "\nPlaylist (forward):\n";
        Node* q = head;
        int number = 1;
        while (q != nullptr) {
            cout << number++ << ". " << q->title << " - " << q->artist;
            if (q == current) cout << "  [CURRENT]";
            cout << "\n";
            q = q->next;
        }
    }

    // Find the last node, then traverse backward using prev pointers.
    void displayReverse() const {
        if (head == nullptr) {
            cout << "Playlist is empty.\n";
            return;
        }

        Node* q = head;
        while (q->next != nullptr) {
            q = q->next;
        }

        cout << "\nPlaylist (reverse):\n";
        int number = 1;
        while (q != nullptr) {
            cout << number++ << ". " << q->title << " - " << q->artist;
            if (q == current) cout << "  [CURRENT]";
            cout << "\n";
            q = q->prev;
        }
    }

    void playCurrent() const {
        if (current == nullptr) {
            cout << "Playlist is empty. Add a song first.\n";
            return;
        }
        cout << "Now playing: " << current->title << " - " << current->artist << "\n";
    }

    void playNext() {
        if (current == nullptr) {
            cout << "Playlist is empty. Add a song first.\n";
        } else if (current->next == nullptr) {
            cout << "Already at the last song. No next song.\n";
        } else {
            current = current->next;
            playCurrent();
        }
    }

    void playPrevious() {
        if (current == nullptr) {
            cout << "Playlist is empty. Add a song first.\n";
        } else if (current->prev == nullptr) {
            cout << "Already at the first song. No previous song.\n";
        } else {
            current = current->prev;
            playCurrent();
        }
    }

    void playCompletePlaylist() {
        if (head == nullptr) {
            cout << "Playlist is empty.\n";
            return;
        }

        Node* q = head;
        cout << "\nPlaying complete playlist:\n";
        while (q != nullptr) {
            cout << "Playing: " << q->title << " - " << q->artist << "\n";
            q = q->next;
        }
        current = head;
    }

    void repeatAll() {
        if (head == nullptr) {
            cout << "Playlist is empty.\n";
            return;
        }

        int repetitions;
        cout << "Enter number of repetitions: ";
        if (!(cin >> repetitions)) {
            cout << "Invalid input.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (repetitions <= 0) {
            cout << "Repetitions must be greater than zero.\n";
            return;
        }

        for (int i = 1; i <= repetitions; ++i) {
            cout << "\nRepetition " << i << ":\n";
            Node* q = head; // Restart from head for each repetition.
            while (q != nullptr) {
                cout << "Playing: " << q->title << " - " << q->artist << "\n";
                q = q->next;
            }
        }
        current = head;
    }

    void showCurrent() const {
        if (current == nullptr) {
            cout << "No current song. Playlist is empty.\n";
        } else {
            cout << "Current song: " << current->title << " - " << current->artist << "\n";
        }
    }
};

int main() {
    MusicPlaylist playlist;
    int choice;

    do {
        cout << "\n========== MUSIC PLAYLIST MANAGER ==========\n";
        cout << "1. Add Song\n";
        cout << "2. Delete Song\n";
        cout << "3. Display Playlist\n";
        cout << "4. Display Playlist in Reverse\n";
        cout << "5. Play Current Song\n";
        cout << "6. Play Next Song\n";
        cout << "7. Play Previous Song\n";
        cout << "8. Play Complete Playlist\n";
        cout << "9. Repeat All\n";
        cout << "10. Show Current Song\n";
        cout << "11. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number from 1 to 11.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string title, artist;

        switch (choice) {
        case 1:
            cout << "Enter song title: ";
            getline(cin, title);
            cout << "Enter artist name: ";
            getline(cin, artist);
            if (title.empty()) {
                cout << "Song title cannot be empty.\n";
            } else {
                playlist.addSong(title, artist);
            }
            break;

        case 2:
            cout << "Enter title of song to delete: ";
            getline(cin, title);
            playlist.deleteSong(title);
            break;

        case 3:
            playlist.displayPlaylist();
            break;

        case 4:
            playlist.displayReverse();
            break;

        case 5:
            playlist.playCurrent();
            break;

        case 6:
            playlist.playNext();
            break;

        case 7:
            playlist.playPrevious();
            break;

        case 8:
            playlist.playCompletePlaylist();
            break;

        case 9:
            playlist.repeatAll();
            break;

        case 10:
            playlist.showCurrent();
            break;

        case 11:
            cout << "Exiting Music Playlist Manager. Goodbye!\n";
            break;

        default:
            cout << "Invalid choice. Please select 1 to 11.\n";
        }
    } while (choice != 11);

    return 0;
}

//OUTPUT
PS C:\Users\poona\OneDrive\Desktop\sonu> g++ musicplayer.cpp -o musicplayer.exe
PS C:\Users\poona\OneDrive\Desktop\sonu> ./musicplayer

========== MUSIC PLAYLIST MANAGER ==========
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter your choice: 1
Enter song title: sau tarah ke
Enter artist name: jonita gandhi and amit mishra
Song added: sau tarah ke - jonita gandhi and amit mishra

========== MUSIC PLAYLIST MANAGER ==========
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter your choice: 1
Enter song title: humnava mere
Enter artist name: jubin nautiyal and rocky shiv
Song added: humnava mere - jubin nautiyal and rocky shiv

========== MUSIC PLAYLIST MANAGER ==========
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter your choice: 1
Enter song title: pata chalega
Enter artist name: imran khan
Song added: pata chalega - imran khan

========== MUSIC PLAYLIST MANAGER ==========
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter your choice: 2
Enter title of song to delete: pata chalega
Song deleted: pata chalega

========== MUSIC PLAYLIST MANAGER ==========
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter your choice: 3

Playlist (forward):
1. sau tarah ke - jonita gandhi and amit mishra  [CURRENT]
2. humnava mere - jubin nautiyal and rocky shiv

========== MUSIC PLAYLIST MANAGER ==========
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter your choice: 4

Playlist (reverse):
1. humnava mere - jubin nautiyal and rocky shiv
2. sau tarah ke - jonita gandhi and amit mishra  [CURRENT]

========== MUSIC PLAYLIST MANAGER ==========
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter your choice: 5
Now playing: sau tarah ke - jonita gandhi and amit mishra

========== MUSIC PLAYLIST MANAGER ==========
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter your choice: 6
Now playing: humnava mere - jubin nautiyal and rocky shiv

========== MUSIC PLAYLIST MANAGER ==========
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter your choice: 7
Now playing: sau tarah ke - jonita gandhi and amit mishra

========== MUSIC PLAYLIST MANAGER ==========
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter your choice: 8

Playing complete playlist:
Playing: sau tarah ke - jonita gandhi and amit mishra
Playing: humnava mere - jubin nautiyal and rocky shiv

========== MUSIC PLAYLIST MANAGER ==========
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter your choice: 9
Enter number of repetitions: 10

Repetition 1:
Playing: sau tarah ke - jonita gandhi and amit mishra
Playing: humnava mere - jubin nautiyal and rocky shiv

Repetition 2:
Playing: sau tarah ke - jonita gandhi and amit mishra
Playing: humnava mere - jubin nautiyal and rocky shiv

Repetition 3:
Playing: sau tarah ke - jonita gandhi and amit mishra
Playing: humnava mere - jubin nautiyal and rocky shiv

Repetition 4:
Playing: sau tarah ke - jonita gandhi and amit mishra
Playing: humnava mere - jubin nautiyal and rocky shiv

Repetition 5:
Playing: sau tarah ke - jonita gandhi and amit mishra
Playing: humnava mere - jubin nautiyal and rocky shiv

Repetition 6:
Playing: sau tarah ke - jonita gandhi and amit mishra
Playing: humnava mere - jubin nautiyal and rocky shiv

Repetition 7:
Playing: sau tarah ke - jonita gandhi and amit mishra
Playing: humnava mere - jubin nautiyal and rocky shiv

Repetition 8:
Playing: sau tarah ke - jonita gandhi and amit mishra
Playing: humnava mere - jubin nautiyal and rocky shiv

Repetition 9:
Playing: sau tarah ke - jonita gandhi and amit mishra
Playing: humnava mere - jubin nautiyal and rocky shiv

Repetition 10:
Playing: sau tarah ke - jonita gandhi and amit mishra
Playing: humnava mere - jubin nautiyal and rocky shiv

========== MUSIC PLAYLIST MANAGER ==========
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter your choice: 11
Exiting Music Playlist Manager. Goodbye!
PS C:\Users\poona\OneDrive\Desktop\sonu> 