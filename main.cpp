#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstdio>

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

void deleteNote(std::vector<Note> &notes){
    if (notes.empty()) {
        std::cout << "No available Notes" << std::endl;
        return;
    }

    for (int i = 0; i < notes.size(); i++) {
        std::cout << '[' << i + 1 << "] " << notes[i].Title << '\n';
    }

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
    }
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
    
    while (true) {
        std::cout << "[add]\t[open]\t[delete]\t[quit]\n";
        std::cout << "[act] ";
        std::getline(std::cin >> std::ws, act);

        if (act == "add") {
            addNote(notes);
        } else if (act == "open") {
            openNote(notes);
        } else if (act == "delete") {
            deleteNote(notes);
        } else if (act == "quit") {
            saveNotes(notes);
            exit(1);
        }
    }


    return 0;
}

