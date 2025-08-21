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
    system("reset");
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

    std::cout << "[Add Note] (:w)-Save Note (:q)-Dont Save:" << std::endl;
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
    std::string act;
    if (notes.empty()) {
        std::cout << "[Notes List]:" << std::endl;
        std::cout << " No notes Available!\n\n";
        std::cout << "[Command]\n";
        std::getline(std::cin >> std::ws, act);
        if (act == ":q") {
            return;
        } else {
            return;
        }
    }

    NoteList(notes);

    std::cout << "[index]: ";
    std::cin >> index;
    index -= 1;

    ClearScreen();
    if (index >= 0 && index <= notes.size()) {
        std::cout << "[(:q)- Quit]\n";
        std::cout << "Date: " << notes[index].Date << '\n' << "Title: " << notes[index].Title << "\n" << notes[index].Content << '\n';
        std::cout << "[Command]\n";
        std::getline(std::cin >> std::ws, act);
        if (act == ":q") {
            return;
        }
    } else {
        return;
    }
}

void renameNote(std::vector<Note> &notes) {
    std::string act;
    if (notes.empty()) {
        std::cout << "[Notes List]:" << std::endl;
        std::cout << " No notes Available!\n\n";
        std::cout << "[Command]\n";
        std::getline(std::cin >> std::ws, act);
        if (act == ":q") {
            return;
        } else {
            return;
        }
    }

    std::time_t now = std::time(nullptr);
    std::tm *localtime = std::localtime(&now);
    std::ostringstream cdate;
    cdate << std::put_time(localtime, "%Y-%m-%d %I:%M %p");
    std::string edate = cdate.str();
    std::string etitle;
    int index;

    NoteList(notes);

    std::cout << "[index]: ";
    std::cin >> index;
    index -= 1;

    ClearScreen();
    if (index >= 0 && index <= notes.size()) {
        notes[index].Date = edate;
        std::cout << "[Previews Title]:" << std::endl;
        std::cout << "Title: " << notes[index].Title << '\n'; 
        std::cout << "[Rename]:" << std::endl;
        std::cout << "New Title: ";
        std::getline(std::cin >> std::ws, notes[index].Title);
    } else {
        return;
    }

}

void editNote(std::vector<Note> &notes) {
    std::string act;
    if (notes.empty()) {
        std::cout << "[Notes List]:" << std::endl;
        std::cout << " No notes Available!\n\n";
        std::cout << "[Command]\n";
        std::getline(std::cin >> std::ws, act);
        if (act == ":q") {
            return;
        } else {
            return;
        }
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

        std::cout << "[Edit Note] (:w)-Save Edit (:q)- Cancel Edit:" << std::endl;
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
    } else {
        return;
    }
    ClearScreen();
}

void appendNote(std::vector<Note> &notes) {
    std::string act;
    if (notes.empty()) {
        std::cout << "[Notes List]:" << std::endl;
        std::cout << " No notes Available!\n\n";
        std::cout << "[Command]\n";
        std::getline(std::cin >> std::ws, act);
        if (act == ":q") {
            return;
        } else {
            return;
        }
    }
    
    int index; 
    std::string AppContent, Addlines;

    NoteList(notes);

    std::cout << "[index]: ";
    std::cin >> index;
    index -= 1;

    ClearScreen();
    if (index >= 0 && index <= notes.size()) {
        std::cout << "[Appen Note] (:w)-Save Edit (:q)- Cancel Edit:" << std::endl;
        std::cout << "Title: " << notes[index].Title << '\n';
        std::cout << notes[index].Content;
        while (true){
            std::getline(std::cin >> std::ws, AppContent);
            if (AppContent == ":w") {
                break;
            } else if (AppContent == ":q") {
                return;
            }
            Addlines += AppContent + "\n";
        }
        notes[index].Content += Addlines;
    } else {
        return;
    }
}

void deleteNote(std::vector<Note> &notes){
    std::string act;
    if (notes.empty()) {
        std::cout << "[Notes List]:" << std::endl;
        std::cout << " No notes Available!\n\n";
        std::cout << "[Command]\n";
        std::getline(std::cin >> std::ws, act);
        if (act == ":q") {
            return;
        } else {
            return;
        }
    }

    NoteList(notes);

    int index;
    
    std::cout << "[index] ";
    std::cin >> index;
    
    index -= 1;

    if (index >= 0 && index <= notes.size()) {
        notes.erase(notes.begin() + index);
        notes.shrink_to_fit();
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

    Date.open(".notes//dates.txt", std::ios::out);
    for (int i = 0; i < notes.size(); i++) {
        Date << notes[i].Date << "|";
    }
    Date.close();
    
    Title.open(".notes//titles.txt", std::ios::out);
    for (int i = 0; i < notes.size(); i++) {
        Title << notes[i].Title << "|";
    }
    Title.close();
    
    Content.open(".notes//contents.txt", std::ios::out);
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

    Dates.open(".notes//dates.txt", std::ios::in);
    Titles.open(".notes//titles.txt", std::ios::in);
    Contents.open(".notes//contents.txt", std::ios::in);
    
    while(std::getline(Dates, date, '|'), std::getline(Titles, title, '|'), std::getline(Contents, content, '|')) {
        Note LoadNotes(id, date, title, content);
        notes.push_back(LoadNotes);
        notes.shrink_to_fit();
    }

    Dates.close();
    Titles.close();
    Contents.close();
    remove(".notes//dates.txt");
    remove(".notes//titles.txt");
    remove(".notes//contents.txt");
}

int main() {
    std::string act;
    std::vector<Note> notes;

    loadNotes(notes);
    ClearScreen();
    
    while (true) {
        ClearScreen();
        std::cout << "================================\n";
        std::cout << "=======      Notes      ========\n";
        std::cout << "================================\n";
        std::cout << "[:add]-[:open]-[:edit]-[:delete]\n";
        std::cout << "-----[:rename]----[:append]-----\n";
        std::cout << "== Save 'n Quit(:wq) Quit(:q) ==\n";
        std::cout << "[Command]_______________________\n";
        std::getline(std::cin >> std::ws, act);

        if (act == ":add" || act == ":ad" || act == ":a") {
            ClearScreen();
            addNote(notes);
        } else if (act == ":open" || act == ":op" || act == ":o") {
            ClearScreen();
            openNote(notes);
        } else if (act == ":edit" || act == ":ed" || act == ":e"){
            ClearScreen();
            editNote(notes);
        } else if (act == ":rename" || act == ":re" || act == ":r") {
            ClearScreen();
            renameNote(notes);
        } else if (act == ":append" || act == ":app" || act == ":ap") {
            ClearScreen();
            appendNote(notes);
        } else if (act == ":delete" || act == ":del" || act == ":de" || act == ":d") {
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

