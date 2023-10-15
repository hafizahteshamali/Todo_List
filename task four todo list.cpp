#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct TodoItem {
    int id;
    string task;
};

int ID = 0; // Initialize ID to 0

void banner();
void addTask();
void showTask();
int searchTask();
void deleteTask();

int main() {
    system("cls");

    while (true) {
        banner();
        cout << "\n\t1. Add Task";
        cout << "\n\t2. Show Task";
        cout << "\n\t3. Search Task";
        cout << "\n\t4. Delete Task";
        cout << "\n\t5. Exit";

        int choice;
        cout << "\n\tEnter any Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addTask();
                break;

            case 2:
                showTask();
                break;

            case 3:
                searchTask();
                break;

            case 4:
                deleteTask();
                break;

            case 5:
                cout << "Exiting program." << endl;
                return 0;

            default:
                break;
        }
    }
    return 0;
}

void banner() {
    cout << "_________________________________________" << endl;
    cout << "  \t    My TODO List" << endl;
    cout << "_________________________________________" << endl;
}

void addTask() {
    system("cls");
    banner();
    TodoItem todo;
    cout << "Enter new Task: " << endl;
    cin.ignore();
    getline(cin, todo.task);
    char save;
    cout << "Save? (y/n): ";
    cin >> save;

    if (save == 'y') {
        ID++;
        ofstream fout;
        fout.open("todo.txt", ios::app);
        fout << "\n" << ID;
        fout << "\n" << todo.task;
        fout.close();

        char more;
        cout << "Add more Task? (y/n): ";
        cin >> more;

        if (more == 'y') {
            addTask();
        } else {
            system("cls");
            cout << "Added Successfully!" << endl;
            return;
        }
    }

    system("cls");
}

void showTask() {
    system("cls");
    banner();
    TodoItem todo;
    ifstream fin;
    fin.open("todo.txt");
    cout << "Tasks:" << endl;

    while (!fin.eof()) {
        fin >> todo.id;
        fin.ignore();
        getline(fin, todo.task);

        if (!todo.task.empty()) {
            cout << "\t" << todo.id << ": " << todo.task << endl;
        }
    }
    fin.close();
    char exit;
    cout << "Exit? (y/n): ";
    cin >> exit;

    if (exit != 'y') {
        showTask();
    }
    system("cls");
}

int searchTask() {
    system("cls");
    banner();
    int id;
    cout << "Enter task id: ";
    cin >> id;
    TodoItem todo;
    ifstream fin("todo.txt");

    while (!fin.eof()) {
        fin >> todo.id;
        fin.ignore();
        getline(fin, todo.task);

        if (todo.id == id) {
            system("cls");
            cout << "\t" << todo.id << ": " << todo.task << endl;
            return id;
        }
    }
    system("cls");
    cout << "Not Found!" << endl;
    return 0;
}

void deleteTask() {
    system("cls");
    int id = searchTask();

    if (id != 0) {
        char del;
        cout << "\n\tDelete? (y/n): ";
        cin >> del;

        if (del == 'y') {
            TodoItem todo;
            ofstream tempFile;
            tempFile.open("temp.txt");
            ifstream fin;
            fin.open("todo.txt");
            int index = 1;

            while (!fin.eof()) {
                fin >> todo.id;
                fin.ignore();
                getline(fin, todo.task);

                if (todo.id != id) {
                    tempFile << "\n" << index;
                    tempFile << "\n" << todo.task;
                    index++;
                    ID--;
                }
            }

            fin.close();
            tempFile.close();
            remove("todo.txt");
            rename("temp.txt", "todo.txt");
            system("cls");
            cout << "\n\tDeleted Successfully!" << endl;
        } else {
            system("cls");
            cout << "Not Deleted!" << endl;
        }
    }
}

