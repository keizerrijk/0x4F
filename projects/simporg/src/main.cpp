#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <string.h>
using namespace std;
namespace fs = std::filesystem;

//Object to store tasks in a simple format.
class task {
    public:
    bool completion_Status;
    string task_Desc;

    task( string line, bool comp_stat) {
        task_Desc = line;
        completion_Status = comp_stat;
    }
};

//Vector to store and edit tasks.
vector<task> orglist;

//Function to initialise the .org directory, and
//the file used to store tasks.
int check_Directory(string homefolder) {
    homefolder.append("/.org");

    if (fs::is_directory(homefolder)) {
        homefolder.append("/org.txt");
        if (fs::exists(homefolder)) {
            return 0;
        }
        else {
            cout << "ERROR Missing or deleted organisation file, creating";
            ofstream orgfile(homefolder);

            if(!orgfile) {
                cerr << "ERROR: Unable to create organisation file. Check permissions.\n";
                return 1;
            }
            else {
                cout << "Done!\n";
                return 0;
            }
        }
    }
    else {
        cout << "Organisation directory and file don't exist, creating them.\n";

        fs::create_directory(homefolder);
        if (fs::is_directory(homefolder)) {
            cout << "Directory creation successful.\n";
        }
        else {
            cerr << "ERROR: unable to create organisation directory. "
                 << "Perhaps you lack the correct permissions?\n";
            return 1;
        }

        homefolder.append("/org.txt");
        ofstream orgfile(homefolder);

        if(!orgfile) {
            cerr << "ERROR: Unable to create organisation file. Check permissions.\n";
            return 1;
        }
        else {
            cout << "Done!\n";
            return 0;
        }
    }
    return 1;
}

int load_Orgfile(string homefolder) {
    string line;

    ifstream orgfile(homefolder);

    while(!orgfile.eof()) {
        bool comp_stat;
        getline(orgfile, line);

        if(line.size()) {
            if (line.back() == '0') {
                comp_stat = true;
            } else {
                comp_stat = false;
            }

            line.pop_back();

            task task_Object(line, comp_stat);
            orglist.push_back(task_Object);
        }
    }
    return 0;
}

int orglist_Print() {
    int g = 1;
    int i = 0;
    int c = orglist.size();

    cout << "\nTasks ::/>\n";
    if (c > 0) {
        while(i < c) {
            cout << g << " " << orglist[i].task_Desc;
            if (orglist[i].completion_Status) {
                cout << "[X]\n";
            }
            else if(!orglist[i].completion_Status) {
                cout << "[ ]\n";
            }
            ++i;
            ++g;
        }
        cout << "\nTotal Number of task: " << orglist.size() << endl;
        return 0;
    }
    else {
        cout << "No tasks found.\n";
        return 0;
    }
}

void print_Help(void) {
    cout << "\nCommand list: \n"
         << "  h:   Prints a usage guide for the program.\n"
         << "  at:  Adds new task to the tasklist with user submitted parameters.\n"
         << "  rt:  Takes a number as an argument and removes the corresponding task.\n"
         << "  mt:  Modifies the descripton of a chosen task.\n"
         << "  ct:  Changes a chosen task's completion status to either complete or incomplete.\n"
         << "  pt:  Prints current tasklist and task ids.\n"
         << "  w:   Writes the current tasklist to the task file.\n"
         << "  wq:  Writes the current tasklist to drive and exits the program\n"
         << "  q:   Exits the program without saving.";

    cout << "\nTask guide: \n"
         << "  Each entry in the task file is printed on a newline \n"
         << "  with an integer value signifying their task id, and place in the task file.\n"
         << "  To modify a specific task use the task's id as a reference for the program to access\n"
         << "  the chosen task.\n";
}

int add_Task() {
    bool loop = true;
    string line;

    while(loop) {
        cout << "\nEnter a description for your task: ";
        cin.clear();
        cin.ignore();
        getline(cin,line);
        line.append(" ");

        if (line.length()) {

            bool comp_stat = false;

            task task_Object(line, comp_stat);
            orglist.push_back(task_Object);

            orglist_Print();

            cout << "Add another Task? y/n: ";
            cin >> line;

            if (line == "y") {
                ;
            }
            else if (line == "n") {
                cout << "(tasks are stored in memory until write command is given.)\n";
                break;
                return 0;
            }
        }
        else {
            cout << "ERROR: task has no text, try again.";
        }
    }
    return 0;
}

int remove_Task() {
    bool loop = true;
    int task_ID;
    int task_Count = orglist.size();
    string usrInput;

    if (task_Count > 0) {
        while(loop) {
            task_Count = orglist.size();
            if (task_Count > 0) {
                orglist_Print();
                cout << "Enter the id of the task to remove: ";
                cin >> task_ID;

                if(!cin) {
                    cerr << "ERROR: Please enter a number. \n";
                }
                else {
                    if (task_ID > task_Count) {
                        cerr << "ERROR: Inputted number was greater than size of tasklist.\n";
                    }
                    else if (task_ID <= 0) {
                        cerr << "ERROR: Inputted number was invalid (lower than minimum value)";
                    }
                    else {
                        task_ID--;
                        orglist.erase(orglist.begin()+task_ID);
                        cout << "Task successfully deleted.\n";

                        cout << "Would you like to remove another task y/n?: ";
                        cin >> usrInput;

                        if (usrInput == "y") {
                            ;
                        }
                        else if (usrInput == "n") {
                            cout << "(tasks changes stored in memory until write command is given.)\n";
                            break;
                            return 0;
                        }
                    }
                }
            }
            else {
                cout << "No tasks left to remove.\n";
                return 0;
            }
        }
    }
    else {
        cout << "ERROR: No tasks found. How can you remove what isn't there?\n";
        return 0;
    }
    return 0;
}

int write_to_Disk(string write_Directory) {
    ofstream orgfile;

    int i = 0;
    int orgsize = orglist.size();

    orgfile.open(write_Directory);

    if(orgsize == 0) {
        cerr << "\nERROR: orglist is empty. Nothing to save";
        return 1;
    }
    else {
        cout << "\nSaving!";
        while(i < orgsize) {
            orgfile << orglist[i].task_Desc;

            if(orglist[i].completion_Status) {
                orgfile << "0\n";
                ++i;
            } else {
                orgfile << "1\n";
                ++i;
            }
        }
        cout << "\nSaving Successful!\n";
        return 0;
    }
}

int change_Task() {
    int task_ID;
    int task_Count = orglist.size();
    bool loop;
    string usrInput;

    if (task_Count > 0) {
        while(loop) {
            task_Count = orglist.size();
            if (task_Count > 0) {
                orglist_Print();
                cout << "Enter the ID of the task you want to complete: ";
                cin >> task_ID;

                if (!cin) {
                    cerr << "ERROR: Input was not a number\n";
                }
                else {
                    if (task_ID > task_Count) {
                        cerr << "ERROR: Inputted task ID did not match any known task\n";
                    }
                    else if (task_ID <= 0) {
                        cerr << "ERROR: Task ID cannot be zero or lower.\n";
                    }
                    else {
                        task_ID--;
                        if (orglist[task_ID].completion_Status) {
                            orglist[task_ID].completion_Status = false;
                        }
                        else if (!orglist[task_ID].completion_Status) {
                            orglist[task_ID].completion_Status = true;
                        }
                        cout << "Do you want to modify another task?\n";
                        cin >> usrInput;

                        if (usrInput == "y") {
                            ;
                        }
                        else if (usrInput == "n") {
                            cout << "(tasks changes stored in memory until write command is given.)\n";
                            break;
                            return 0;
                        }
                    }
                }
            }
        }
    }
    else {
        cerr << "\nERROR: No tasks to modify.\n";
        return 1;
    }
    return 0;
}

int command_Parser(string homefolder) {
    string usrInput;
    bool loop = true;

    while(loop) {
        cout << "\nEnter a command λ::> ";
        cin >> usrInput;
        if (usrInput.length()) {
            if (usrInput == "h") {
                print_Help();
            }
            else if (usrInput == "at") {
                add_Task();
            }
            else if (usrInput == "rt") {
                remove_Task();
            }
            else if (usrInput == "q") {
                cout << "\nExiting program.\n";
                return 0;
            }
            else if (usrInput == "w") {
                write_to_Disk(homefolder);
            }
            else if (usrInput == "wq") {
                write_to_Disk(homefolder);
                cout << "Exiting program.\n";
                return 0;
            }
            else if (usrInput == "pt") {
                orglist_Print();
            }
            else if  (usrInput == "ct") {
                change_Task();
            }
            else {
                cout << "Command not recognised, try again.";
            }
        }
        else {
            cout << "ERROR: No command entered, please try again.\n";
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    string homefolder = getenv("HOME");

    if (check_Directory(homefolder) == 1) {
        cerr << "ERROR: Function check_directory(homefolder) "
             << "returned error, goodbye ;(.\n";
        return 1;
    }

    homefolder.append("/.org/org.txt");

    if (argc > 1) {
        if (strcmp(argv[1], "-pt") == 0) {
            load_Orgfile(homefolder);
            orglist_Print();
            cout << endl;
            return 0;
        } 
    }
    else {
        cout << "Simple Organisation Utility."
             << " Beta 1.9\n" << "(For help enter h)\n";

        load_Orgfile(homefolder);
        orglist_Print();

        command_Parser(homefolder);

        return 0;
    }
}
