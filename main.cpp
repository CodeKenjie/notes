#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>

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
    std::string title, content;
    std::string date = cdate.str();
    std::cout << "Title: ";
    std::getline(std::cin >> std::ws, title);

    std::cout << ":";
    std::getline(std::cin >> std::ws, content);

    Note new_note(id, date, title, content);
    
    notes.push_back(new_note);
    notes.shrink_to_fit();
}

void openNote(std::vector<Note> &notes) {
    int index;

    if (notes.empty()) {
        std::cout << "No notes Available!" << std::endl;
        return;
    }

    std::cout << "[index]" << '\n';
    for(int i = 0; i < notes.size(); ++i){
        std::cout << '[' << i + 1 << "] " << notes[i].Title << std::endl;
    }

    std::cout << "[capacity]: " << notes.capacity() << '\n';
    std::cout << "[size]: " << notes.size() << '\n';
    std::cout << "[index]: ";
    std::cin >> index;

    if (index >= 0 && index <= notes.size()) {
            std::cout << "ID: " << notes[index-1].Id << '\n' << "Date: " << notes[index-1].Date << '\n' << "Title: " << notes[index-1].Title << '\n' << notes[index-1].Content << std::endl;
    } else if (index <= 0 && index >= notes.size()) {
        return;
    }
}

int main() {
    std::string act;
    std::vector<Note> notes;
    
    while (true) {
        std::cout << "[add]\t[open]\n";
        std::cout << "[act] ";
        std::getline(std::cin >> std::ws, act);

        if (act == "add") {
            addNote(notes);
        } else if (act == "open") {
            openNote(notes);
        }
    }


    return 0;
}

