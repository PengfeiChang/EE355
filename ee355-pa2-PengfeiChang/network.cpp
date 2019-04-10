
#include "network.h"
#include <limits>
#include "misc.h"
#include <fstream>
#include <dirent.h>
#include <string.h>
#include <stdio.h>

Network::Network(){
    head = NULL;
    tail = NULL;
    count = 0;
}


Network::Network(string fileName){
    // TODO: complete this method!
    // Implement it in one single line!
    // You may need to implement the load method before this!
    this -> loadDB(fileName);
}

Network::~Network(){
    // Copy from lab5 
    while(head != NULL)
    {
        Connection* copy = head;
        delete copy;
        head = head -> next;
    }
}


void Network::push_front(Connection* newEntry){
    // Adds a new Connection (newEntry) to the front of LL
    // TA completed me in lab5 and since then I've not been changed! 
    newEntry->prev = NULL;
    newEntry->next = head;

    if (head != NULL)
        head->prev = newEntry;
    else
        tail = newEntry;
    
    head = newEntry;
    count++;
}


void Network::push_back(Connection* newEntry){
    // Adds a new Connection (newEntry) to the back of LL
    // Copy from your lab5
    newEntry->next = NULL;
    newEntry -> prev = tail;

    if(head != NULL)
    {
        tail -> next = newEntry;
    }
    else 
        head = newEntry;

    tail = newEntry;
    count++;
}


Connection* Network::search(Connection* searchEntry){
    // Searches the Network for searchEntry
    // if found, returns a pointer to it, else returns NULL
    // Copy from lab5 
    Connection* pointer = head;

    while (pointer != NULL)
    {
        if(*pointer == *searchEntry)
        {
            return pointer;
        }
        else 
        {
            pointer = pointer->next;
        }
    }

    return NULL;
}


Connection* Network::search(string fname, string lname){
    // New == for Connection, only based on fname and lname
    // if found, returns a pointer to it, else returns NULL
    // TODO: Complete this method
    // Note: two ways to implement this, 1st making a new Connection with fname and lname and and using search(Connection*), 2nd using fname and lname directly. 

    //I am going to use fname and lname directly in my methods. 
    Connection* pointer = head;

    while(pointer != NULL)
    {
        if((pointer->f_name == fname) && (pointer->l_name == lname))
        {
            return pointer;
        }

        pointer = pointer -> next;
    }

    return NULL;
}

Connection* Network::search(string code){

    return NULL;
}


void Network::printDB(){
    // Leave me alone! I know how to print! 
    // Note: Notice that we don't need to update this even after adding to Connection attributes
    // This is a feature of OOP, classes are supposed to take care of themselves!
    cout << "Number of connections: " << count << endl;
    cout << "------------------------------" << endl;
    Connection* ptr = head;
    while(ptr != NULL){
        ptr->print_connection();
        cout << "------------------------------" << endl;
        ptr = ptr->next;
    }
}


void Network::saveDB(string filename){
    // Saves the netwrok in file <filename>
    // Note: The format of the output file is very abstract, just raw data
    // Look at studentDB.txt as a template
    // TODO: Update this method with new requirements
    // Note: notice the intentional flaw in this code, as compared to the note mentioned in printDB, now the one who is responsible for implementing Network should be aware of implementation of Connection, not good! You will fix this in PA2. 
    Connection* ptr = head;
    ofstream outFile;
    outFile.open(filename.c_str());

    while(ptr!= NULL)
    {
        ptr -> write_connection(outFile);
        ptr = ptr -> next;
    }

    outFile.close();
}


void Network::loadDB(string filename){
    // Loads the netwrok from file <filename>
    // The format of the input file is similar to saveDB
    // Look at network studentDB.txt as a template
    // Phone number can be with dashes or without them
    // TODO: Now you will notice you need to go back and make a new constructor to the Connection class,  
    // Connection::Connection(fname, lname, bdate, email, phone)
    // TODO: Update this method with new requirements 
    Connection* ptr = head;
    while(head != NULL){
        ptr = head->next;
        delete head;
        head = ptr;
        count--;
    }
    head = NULL;
    tail = NULL;
    ifstream infile;
    infile.open(filename.c_str());
    string buff, fname, lname, bdate, the_email, the_phone;

    vector < vector<string> >members;
    vector <string> temp;

    while(getline(infile, buff)){
        lname = buff.substr(0, buff.find(','));
        fname = buff.substr(buff.find(',')+2);
        getline(infile, bdate);
        getline(infile, the_email);
        getline(infile, the_phone);
        
        Connection* newEntry = new Connection(fname, lname, bdate, the_email, the_phone);
        this->push_back(newEntry);

        getline(infile, buff);
        temp.clear();
        while(buff.compare(0,5,"-----") != 0)
        {
            temp.push_back(buff);
            getline(infile,buff);
        }

        members.push_back(temp);

    }

    //build the connections of friends
    Connection* pointer = head;
    Connection* current = head;

    for(int i=0; i<members.size(); i++)
    {
        for(int j=0; j<members[i].size(); j++)
        {
            //cout << members[i][j]<<endl;
            Connection* pointer = head;
            while(pointer != NULL)
            {
                //cout<<"finding..."<<endl;
                //cout<<codeName(pointer -> f_name, pointer -> l_name)<<endl;
                if(codeName(pointer -> f_name, pointer -> l_name) == members[i][j])
                {
                    //cout<<"found!"<<endl;
                    current -> makeFriends(pointer);
                    break;
                }

                pointer = pointer -> next;
            }
        }

        current = current -> next;
    }
}


bool Network::remove(string fname, string lname){
    // We modified the definition of == for Connection in Connection definition itself, 
    // So we should not be worried about changes we made in Connection to modify this method!
    // Copy from lab5
    Connection* ptr = search(fname, lname);

    //newentry -> print_connection();
    if(ptr == NULL)
        return false;

    else 
    {
        //check to see if it's the only node in the LL
        if((ptr -> prev == NULL) && (ptr -> next == NULL))
        {
            delete head;
        }

        else
        {
            //check to see if it's the first node
            if(ptr -> prev == NULL)
            {
                ptr -> next -> prev = NULL;
                head = ptr -> next;
                delete ptr;
            }

            //check to see if it's the last node
            else if(ptr -> next == NULL)
            {
                ptr -> prev -> next = NULL;
                delete ptr;
            }

            //if it's in the middle
            else 
            {
                ptr -> next -> prev = ptr -> prev;
                ptr -> prev -> next = ptr -> next;
                delete ptr;

            }
        }

        count--;

        return true;

    }
}


void Network::sendEmail(string addr, string subject, string content, string attachment=""){
    // Sending a command looks like:
    // echo "content" | mailx -s "subject" -a "attachment" addr;
    // TODO: Search how you can run a unix command in C++
    // TODO: You need to add double quotation character (") to both sides of strings for this command. Adding other characters (like ? in code below) should be easy, but double quotation says: I'm a character but not a typical character! 
    // string new_str = '?' + old_str + '?'
    // TODO: Complete this method
    attachment = "\"" + attachment + "";
    content = "\"" + content + "\"";
    subject = "\"" + subject + "\"";
    string cmd;
    cmd = "echo " + content + " | mailx -s " + subject + " -a" + attachment + addr;
    cout << cmd << endl;
    system(cmd.c_str());
}


void Network::showMenu(){
    // TODO: Complete this method!
    // All the prompts are given to you, 
    // You should add code before, between and after prompts!

    int opt;
    while(1){
        cout << "\033[2J\033[1;1H";
        printMe("banner"); // from misc library

        cout << "Select from below: \n";
        cout << "1. Save network database \n";
        cout << "2. Load network database \n";
        cout << "3. Add a new connection \n";
        cout << "4. Remove a connection \n";
        cout << "5. Search \n";
        cout << "6. Send an email \n";
        cout << "7. Send an iMessage \n";
        cout << "8. Print database \n";
        cout << "9. Connect \n";
        cout << "\nSelect an option ... ";
        
        if (cin >> opt) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Wrong option! " << endl;
            return;
        }
        
        // You may need these variables! Add more if you want!
        string fname, lname, fileName, bdate;
        cout << "\033[2J\033[1;1H";

        if (opt==1){
            // TODO: Complete me!
            cout << "Saving network database \n";
            cout << "Enter the name of the save file: ";
            std::getline (std::cin, fileName);
            saveDB(fileName);
            cout << "Network saved in " << fileName << endl;
        }
        else if (opt==2){
            // TODO: Complete me!
            cout << "Loading network database \n";
            // TODO: print all the files in this same directory that have ".db" format
            // Take a look into sample_files.cpp 
            DIR *dir;
            struct dirent *ent;
            char targetFolderAddr[] = "./";
            string db_file[10];
            string fileName;
            int i = 0;
            bool flag = false;

            if ((dir = opendir ("./")) != NULL) {
                /* Note: You may ask "what is dir here in this code"? 
                * You have two options (as an engineer): 
                * 1. Spend a lot of time reading about dirent.h, exploring stackoverflow pages and make test cases, you will learn something, but does it worth the time? Specially when you may forget about it till the next time you actually need to know about it. 
                * 2. Just use it to solve your problem, maybe a small test to understand its potentiallity. So next time when you design something you know this functionality exists. Of course, each option has its advantages and disadvatanges. 
                * And remember, you have a deadline for this PA!
                */ 
                while ((ent = readdir (dir)) != NULL) {
                    if(strstr(ent->d_name, ".db") != NULL){
                        db_file[i] = ent -> d_name;
                        i++;
                        cout << ent->d_name << endl;
                    }
                }
                closedir (dir);
            } 
            else {
                /* could not open directory */
                perror ("No directory!");
                break;
            }
            cout << "Enter the name of the load file: "; 
            // If file with name FILENAME does not exist: 
            cin >> fileName;
            for(int j =0; j<i; j++)
            {
                if(fileName == db_file[j])
                {
                    flag = true;
                    break;
                }
            }

            if(flag == false){
                cout << "File FILENAME does not exist!" << endl;
            }

            else if(flag == true){
                loadDB(fileName);
                // If file is loaded successfully, also print the count of connections in it: 
                cout << "Network loaded from " << fileName << " with " << count << " connections \n";
            }
            
        }
        else if (opt == 3){
            // TODO: Complete me!
            // TODO: use push_front, and not push_back 
            // Add a new Connection ONLY if it does not exists!
            cout << "Adding a new connection \n";
            Connection* newEntry = new Connection();
            this->push_front(newEntry);

        }
        else if (opt == 4){
            // TODO: Complete me!
            string fname;
            string lname;

            cout << "Removing a connection \n";
            cout << "First name: ";
            std::getline (std::cin, fname);
            cout << "Last name: ";
            std::getline (std::cin, lname);
            // if found, cout << "Remove Successful! \n";
            // if not found: cout << "Connection not found! \n";

            if(remove(fname,lname))
            {
                cout<<"Remove Successful! \n";
            }

            else 
                cout << "Connection not found! \n";

        }
        else if (opt==5){
            // TODO: Complete me!
            string fname;
            string lname;
            cout << "Searching: \n";
            cout << "First Name: ";
            std::getline (std::cin, fname);
            cout << "Last Name: ";
            std::getline (std::cin, lname);
            // if found: print connection
            // if not, cout << "Not found! \n";
            Connection* ptr = search(fname, lname);

            if(ptr != NULL)
            {
                ptr -> print_connection();
            }

            else 
                cout << "Not found! \n";

        }
        else if (opt==6){
            // Note: Completed!
            string fname;
            string lname;
            cout << "Sending email to: \n";
            cout << "First Name: ";
            std::getline (std::cin, fname);
            cout << "Last Name: ";
            std::getline (std::cin, lname);
            Connection* ptr = search(fname, lname);
            if (ptr){
                string subject, content, attachment;
                cout << "Sending email to: \n";
                ptr->print_connection();
                cout << "Subject: ";
                std::getline (std::cin, subject);
                cout << "Content: ";
                std::getline (std::cin, content);
                cout << "Attachment: ";
                std::getline (std::cin, attachment);
                string addr = ptr->email->get_contact("1");
                sendEmail(addr, subject, content, attachment);
            }
            else 
                cout << "Contact not found! \n";
        }
        else if (opt==7){
            cout << "Option currently not available\n";
        }
        else if (opt==8){
            // TODO: Complete me!
            cout << "Network Database: \n";
            printDB();
        }
        else if (opt==9){
            string firstName1;
            string firstName2;
            string lastName1;
            string lastName2;
            cout << "Make friends: \n";
            cout << "Connection 1 \n";
            cout << "First Name: ";
            std::getline(std::cin, firstName1);
            cout << "Last Name: ";
            std::getline(std::cin, lastName1);
            cout<<endl;

            Connection* ptr1 = search(firstName1,lastName1);
            if(ptr1 == NULL)
            {
                cout << "Connection not found \n";
                //continue;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "\n\nPress Enter key to go back to main menu ... ";
                string temp;
                std::getline (std::cin, temp);
                cout << "\033[2J\033[1;1H";
                continue;
            }

            cout << "Connection 2 \n";
            cout << "First Name: ";
            std::getline(std::cin, firstName2);
            cout << "Last Name: ";
            std::getline(std::cin, lastName2);
            cout<<endl;

            Connection* ptr2 = search(firstName2,lastName2);
            if(ptr2 == NULL)
            {
                cout << "Connection not found \n";
                //continue;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "\n\nPress Enter key to go back to main menu ... ";
                string temp;
                std::getline (std::cin, temp);
                cout << "\033[2J\033[1;1H";
                continue;

            }

            ptr1 -> makeFriends(ptr2);

            if(ptr1 != ptr2)
                ptr2 -> makeFriends(ptr1);

        }
        else
            cout << "Nothing matched!\n";
        
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\n\nPress Enter key to go back to main menu ... ";
        string temp;
        std::getline (std::cin, temp);
        cout << "\033[2J\033[1;1H";
    }
}


