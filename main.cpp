#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstdlib>

void ClearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

class Note{
public:
    int Id;
    std::string Date;
    std::string Title;
    std::string Content;

    Note(int id, std::string date, std::string title, std::string content) : Id(id), Date(date), Title(title), Content(content) {}
};

int lastID = 1;

void addNote(std::vector<Note> &notes) {

    std::time_t now = std::time(nullptr);
    std::tm *localtime = std::localtime(&now);
    std::ostringstream cdate;
    cdate << std::put_time(localtime, "%Y-%m-%d %I:%M %p");

    int id = lastID++;
    std::string title, content, note;
    std::string date = cdate.str();

    std::cout << "[Add Note: (:w)- Save Note (:q)- Dont Save]:" << std::endl;
    std::cout << "Title: ";
    std::getline(std::cin >> std::ws, title);

    while (true) {
        std::getline(std::cin >> std::ws, content);
        if (content == ":w") {
            break;
        } else if (content == ":q") {
            return;
        }
        note += content + "\n";
    }

    Note new_note(id, date, title, note);
    
    notes.push_back(new_note);
    notes.shrink_to_fit();
    ClearScreen();
}

void NoteList(std::vector<Note> &notes){
    
    std::cout << "[Notes List]:" << std::endl;
    for(int i = 0; i < notes.size(); ++i){
        std::cout << '[' << i + 1 << "] " << notes[i].Title  << std::endl;
    }

}

void openNote(std::vector<Note> &notes) {
    int index;

    if (notes.empty()) {
        std::cout << "[Open Note]:" << std::endl;
        std::cout << "No notes Available!" << std::endl;
        return;
    }

    NoteList(notes);

    std::cout << "[index]: ";
    std::cin >> index;
    index -= 1;

    ClearScreen();
    if (index >= 0 && index <= notes.size()) {
            std::cout << "Date: " << notes[index].Date << '\n' << "Title: " << notes[index].Title << "\n\n" << notes[index].Content << '\n';
    } else if (index <= 0 && index >= notes.size()) {
        return;
    } else {
        return;
    }
}

void editNote(std::vector<Note> &notes) {
    if (notes.empty()) {
        std::cout << "[Edit Note]:" << std::endl;
        std::cout << "No notes Available!" << std::endl;
        return;
    }

    std::time_t now = std::time(nullptr);
    std::tm *localtime = std::localtime(&now);
    std::ostringstream cdate;
    cdate << std::put_time(localtime, "%Y-%m-%d %I:%M %p");

    std::string etitle;
    std::string econtent, enote;
    std::string edate = cdate.str();
    int index;

    NoteList(notes);

    std::cout << "[index]: ";
    std::cin >> index;
    index -= 1;
    
    ClearScreen();
    if (index >= 0 && index <= notes.size()) {
        notes[index].Date = edate;
        std::cout << "[Previews Note]:" << std::endl;
        std::cout << "Title: " << notes[index].Title << "\n: "<< notes[index].Content << '\n';

        std::cout << "[Edit Note: (:w)-SAVE Edit (:q)- Cancel Edit]:" << std::endl;
        std::cout << "New Title: ";
        std::getline(std::cin >> std::ws, notes[index].Title);
        while (true) {
            std::getline(std::cin >> std::ws, econtent);
            if (econtent == ":w") {
                break;
            } else if (econtent == ":q") {
                return;
            }
            enote += econtent + "\n";
        }
        notes[index].Content = enote;
    } else if (index <= 0 && index >= notes.size()) {
        return;
    } else {
        return;
    }
    ClearScreen();
}

void deleteNote(std::vector<Note> &notes){
    if (notes.empty()) {
        std::cout << "[Delete Note]:" << std::endl;
        std::cout << "No available Notes" << std::endl;
        return;
    }

    NoteList(notes);

    int index;
    
    std::cout << "[index] ";
    std::cin >> index;
    
    index -= 1;

    if (index >= 0 && index <= notes.size()) {
        notes.erase(notes.begin() + index);
        notes.shrink_to_fit();
    } else if (index <= 0 && index >= notes.size()) {
        std::cout << "Invalid index";
        return;
    } else {
        return;
    }
    ClearScreen();
}

void saveNotes(std::vector<Note> &notes) {
    if (notes.empty()) {
        return;
    }

    std::fstream Date;
    std::fstream Title;
    std::fstream Content;
    std::string date;
    std::string title;
    std::string content;

    Date.open("dates.txt", std::ios::out);
    for (int i = 0; i < notes.size(); i++) {
        Date << notes[i].Date << "|";
    }
    Date.close();
    
    Title.open("titles.txt", std::ios::out);
    for (int i = 0; i < notes.size(); i++) {
        Title << notes[i].Title << "|";
    }
    Title.close();
    
    Content.open("contents.txt", std::ios::out);
    for (int i = 0; i < notes.size(); i++) {
        Content << notes[i].Content << "|";
    }
    Content.close();
}

void loadNotes(std::vector<Note> &notes) {
    std::fstream Dates;
    std::fstream Titles;
    std::fstream Contents;
    int id = lastID++;
    std::string date;
    std::string title;
    std::string content;

    Dates.open("dates.txt", std::ios::in);
    Titles.open("titles.txt", std::ios::in);
    Contents.open("contents.txt", std::ios::in);
    
    while(std::getline(Dates, date, '|'), std::getline(Titles, title, '|'), std::getline(Contents, content, '|')) {
        Note LoadNotes(id, date, title, content);
        notes.push_back(LoadNotes);
        notes.shrink_to_fit();
    }

    Dates.close();
    Titles.close();
    Contents.close();
    remove("dates.txt");
    remove("titles.txt");
    remove("contents.txt");
}

int main() {
    std::string act;
    std::vector<Note> notes;

    loadNotes(notes);
    ClearScreen();
    
    std::cout << "\t=====================\n";
    std::cout << "\t==      NOTES      ==\n";
    std::cout << "\t=====================\n";
    
    while (true) {
        std::cout << "[add]-[open]-[edit]-[delete]\n";
        std::cout << "Save 'n Quit(:wq) Quit(:q)\n";
        std::cout << "[Command]";
        std::getline(std::cin >> std::ws, act);

        if (act == "add") {
            ClearScreen();
            addNote(notes);
        } else if (act == "open") {
            ClearScreen();
            openNote(notes);
        } else if (act == "edit"){
            ClearScreen();
            editNote(notes);
        } else if (act == "delete") {
            ClearScreen();
            deleteNote(notes);
        } else if (act == ":wq") {
            saveNotes(notes);
            exit(1);
        } else if (act == ":q") {
            exit(1);
        }
    }


    return 0;
}

