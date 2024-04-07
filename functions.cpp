#include "node.h"
#include "link.cpp"
using namespace std;
long saved_memory = 0;


void remove_redundant(node* file, Linkedlist* Linkedlist)
{
    node* temp = Linkedlist->gethead();
    while (temp != nullptr)
    {
        if (Linkedlist->Find_redundant(file->size_file))
        {
            if (remove(file->File_Name->c_str()) != 0)
            {
                string description = "Error deleting a file: In the File " + (*file->URL_File) + "\nPlease check that the file.";
                //displayErrorMessage("Error deleting a file", &description);
                exit(0);
            }
            else
            {
                saved_memory += file->size_file;
            }
        }
    }
    return;
}





long new_date(node* file)
{
    int dd, mm, yyyy;
    long x;

    sscanf((*file->date_of_creation).c_str(), "%d-%d-%d", &dd, &mm, &yyyy);

    x = (yyyy * 10000) + (mm * 100) + dd;
    return x;
}





bool Old_by_Date(node* file, long date)
{

    if (new_date(file) < date)
    {
        return true;
    }
    else return false;
}




bool File_empty(node* file)
{

    if (file->size_file == 0) return true;

    return false;
}




bool File_Accessed(node* file, int acc)
{

    if (file->Accessed < acc) return true;

    return false;
}




bool IsValid(node* file, int acc, long date)
{
    if (Old_by_Date(file, date))return false;

    else
    {
        if (File_empty(file)) return false;

        else
        {
            if (File_Accessed(file, acc)) return false;

            else
            {
                return true;
            }
        }
    }
}






void File_seprate(const string& file_path, Linkedlist* valid, Linkedlist* delete_list, int min_acc, long min_date)
{

    int filenumber = 0;


    ifstream file(file_path);
    if (!file.is_open())
    {
        const string msg = "Failed to open file: " + file_path + "\n";
        string description = "File not found.";
        //displayErrorMessage(msg, &description);
        return;
    }

    string line;
    getline(file, line);


    while (getline(file, line))
    {

        filenumber++;
        stringstream ss(line);
        string name, access_count_str, date_created, size_str, URL;


        getline(ss, name, ',');
        getline(ss, access_count_str, ',');
        getline(ss, date_created, ',');
        getline(ss, size_str, ',');
        getline(ss, URL);

        int access_count;
        long size__;
        try {
            access_count = stoi(access_count_str);
            size__ = stol(size_str);
        }
        catch (const invalid_argument& e) {
            string description = "Invalid File name : In the File " + to_string(filenumber) + " From top.\nPlease check that the file name is as required.";
            //displayErrorMessage("Invalid File name", &description);
            valid->Empty_Linkedlist();
            delete_list->Empty_Linkedlist();
            break;
        }

        node* file_element = new node(name, access_count, date_created, size__, URL);
        if (!IsValid(file_element, min_acc, min_date)) {
            delete_list->Insertion(file_element);
        }
        else {
            valid->Insertion(file_element);
        }
    }

    file.close();
}






void File_empty(const string& file_path, Linkedlist* validfiles, Linkedlist* binfiles)
{

    int filenumber = 0;


    ifstream file(file_path);
    if (!file.is_open())
    {
        const string msg = "Failed to open file: " + file_path + "\n";
        string description = "File not found.";
       // displayErrorMessage(msg, &description);
        return;
    }

    string line;
    getline(file, line);


    while (getline(file, line))
    {

        filenumber++;
        stringstream ss(line);
        string name, access_count_str, date_created, size_str, URL;


        getline(ss, name, ',');
        getline(ss, access_count_str, ',');
        getline(ss, date_created, ',');
        getline(ss, size_str, ',');
        getline(ss, URL);

        int access_count;
        long size__;
        try {
            access_count = stoi(access_count_str);
            size__ = stol(size_str);
        }
        catch (const invalid_argument& e)
        {
            string description = "Invalid File name : In the File " + to_string(filenumber) + " From top.\nPlease check that the file name is as required.";
            //displayErrorMessage("Invalid File name", &description);
            validfiles->Empty_Linkedlist();
            binfiles->Empty_Linkedlist();
            break;
        }

        node* file_element = new node(name, access_count, date_created, size__, URL);
        if (File_empty(file_element)) {
            binfiles->Insertion(file_element);
        }
        else {
            validfiles->Insertion(file_element);
        }
    }

    file.close();
}





void File_Date(const string& file_path, Linkedlist* validfiles, Linkedlist* binfiles, long date)
{

    int filenumber = 0;


    ifstream file(file_path);
    if (!file.is_open())
    {
        const string msg = "Failed to open file: " + file_path + "\n";
        string description = "File not found.";
       // displayErrorMessage(msg, &description);
        return;
    }

    string line;
    getline(file, line);


    while (getline(file, line))
    {

        filenumber++;
        stringstream ss(line);
        string name, access_count_str, date_created, size_str, URL;


        getline(ss, name, ',');
        getline(ss, access_count_str, ',');
        getline(ss, date_created, ',');
        getline(ss, size_str, ',');
        getline(ss, URL);

        int access_count;
        long size__;
        try
        {
            access_count = stoi(access_count_str);
            size__ = stol(size_str);
        }
        catch (const invalid_argument& e) {
            string description = "Invalid File name : In the File " + to_string(filenumber) + " From top.\nPlease check that the file name is as required.";
            //displayErrorMessage("Invalid File name", &description);
            validfiles->Empty_Linkedlist();
            binfiles->Empty_Linkedlist();
            break;
        }

        node* file_element = new node(name, access_count, date_created, size__, URL);
        if (Old_by_Date(file_element, date)) {
            binfiles->Insertion(file_element);
        }
        else {
            validfiles->Insertion(file_element);
        }
    }

    file.close();
}




void File_Accessed(const string& file_path, Linkedlist* validfiles, Linkedlist* binfiles, int min_acc) {

    int filenumber = 0;


    ifstream file(file_path);
    if (!file.is_open()) {
        const string msg = "Failed to open file: " + file_path + "\n";
        string description = "File not found.";
       // displayErrorMessage(msg, &description);
        return;
    }

    string line;
    getline(file, line);


    while (getline(file, line)) {

        filenumber++;
        stringstream ss(line);
        string name, access_count_str, date_created, size_str, URL;


        getline(ss, name, ',');
        getline(ss, access_count_str, ',');
        getline(ss, date_created, ',');
        getline(ss, size_str, ',');
        getline(ss, URL);

        int access_count;
        long size__;
        try {
            access_count = stoi(access_count_str);
            size__ = stol(size_str);
        }
        catch (const invalid_argument& e) {
            string description = "Invalid File name : In the File " + to_string(filenumber) + " From top.\nPlease check that the file name is as required.";
            //displayErrorMessage("Invalid File name", &description);
            validfiles->Empty_Linkedlist();
            binfiles->Empty_Linkedlist();
            break;
        }

        node* file_element = new node(name, access_count, date_created, size__, URL);
        if (File_Accessed(file_element, min_acc)) {
            binfiles->Insertion(file_element);
        }
        else {
            validfiles->Insertion(file_element);
        }
    }

    file.close();
}




int get_saved_memory() {
    return saved_memory;
}




void Checking(string file_name, Linkedlist* bin, Linkedlist* valid) {
    if (bin->search(file_name)) {
        valid->Insertion(bin->Remove_Node(file_name));
    }
}


void remove_list(Linkedlist* bin) {
    node* temp = bin->gethead();
    while (temp != nullptr) {
        saved_memory += temp->size_file;
        string element = "sample\\" + *temp->File_Name;
        cout << element;
        remove(element.c_str());
        temp = temp->next;
    }
}



/* void displayErrorMessage(const string& message, const string description) {

    cout << "\n\n\033[31m";
    cout << message;
    cout << *description << "\n";
    cout << "\033[0m";
}*/