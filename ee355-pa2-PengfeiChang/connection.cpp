
#include "connection.h"
#include "misc.h"

Connection::Connection(){
    // I'm already done! 
    set_connection();
}


Connection::~Connection(){
    // TODO: Complete me!
    delete birthdate;
    delete email;
    delete phone;
}


Connection::Connection(string fname, string lname, \
    string bdate, string email, string phone){
    // TODO: Complete this method!
    // phone and email strings are in full version
    string email_type;
    string phone_type;
    string email_addr;
    string phone_num;

    email_type = email.substr(1,email.find(')')-1);
    email_addr = email.substr(email.find(')')+2);

    phone_type = phone.substr(1,phone.find(')')-1);
    phone_num = phone.substr(phone.find(')')+2);

    this -> f_name = fname;
    this -> l_name = lname;
    this -> birthdate = new Date(bdate);
    this -> email = new Email(email_type, email_addr);
    this -> phone = new Phone(phone_type, phone_num);
}


Connection::Connection(string filename){
    // TODO: Complete this method!
    set_connection(filename);
}


void Connection::set_connection(){
    // prompts for the information of the user
    // first/last name can have spaces!
    // date format must be "M/D/YYYY"
    // We are sure user enters info in correct format.
    // TODO: complete this method!
    string temp;
    string type;

    cout << "First Name: ";
    // code here
    std::getline (std::cin,f_name);

	cout << "Last Name: ";
    // code here
    std::getline (std::cin,l_name);

    cout << "Birthdate (M/D/YYYY): ";
    // code here
    std::getline (std::cin,temp);
    birthdate = new Date(temp); 
    
    cout << "Type of email address: ";
    // code here
    std::getline (std::cin,type);
    cout << "Email address: ";
    // code here
    std::getline (std::cin,temp);
    email = new Email(type,temp);


    cout << "Type of phone number: ";
    // code here
    std::getline(std::cin,type);
    cout << "Phone number: ";
    // code here
    std::getline(std::cin,temp);
    // code here
    phone = new Phone(type,temp);
}


void Connection::set_connection(string filename){
    // TODO: Complete this method!
    // Look at connection_template files as examples.     
    // Phone number in files can have '-' or not.
    string buff;
    string type;
    string data;
    std::ifstream inFile(filename.c_str());
    std::getline(inFile, buff);
    l_name = buff.substr(0,buff.find(','));
    f_name = buff.substr(buff.find(',')+2);

    std::getline(inFile,buff);
    birthdate = new Date(buff);

    std::getline(inFile,buff);
    type = buff.substr(1,buff.find(')')-1);
    data = buff.substr(buff.find(')')+2);
    email = new Email(type,data);

    std::getline(inFile,buff);
    type = buff.substr(1,buff.find(')')-1);
    data = buff.substr(buff.find(')')+2);
    phone = new Phone(type,data);

}


bool Connection::operator==(const Connection& rhs){
    // TODO: Complete this method!
    // Note: Difference to Lab is that from now on the combination of fname-lname is unique for any connection
    if ( (f_name == rhs.f_name) && 
        (l_name == rhs.l_name))
        return true;
    else 
        return false;
}


bool Connection::operator!=(const Connection& rhs){ 
    // TODO: Complete this method!
    return !(*this == rhs);
}


void Connection::print_connection(){
    // Already implemented for you! Do not change!
	cout << l_name <<", " << f_name << endl;
	birthdate->print_date("Month D, YYYY");
    email->print();
    phone->print();
    for(int i=0; i< friends.size(); i++)
    {
        cout<<codeName(friends[i] -> f_name, friends[i] -> l_name)<<endl;
    }
}

void Connection::write_connection(std::ofstream& outFile){
    string first_name = this -> f_name;
    string last_name = this -> l_name;
    string birthday = this -> birthdate ->get_date();
    string the_email = this -> email -> get_contact();
    string the_phone = this -> phone -> get_contact();
    outFile<< last_name<<", "<<first_name<<"\n"<<birthday<<"\n"<<the_email<<"\n"<<the_phone<<"\n";
    for(int i=0; i<friends.size(); i++)
    {
        outFile << codeName(friends[i] -> f_name, friends[i] -> l_name) <<"\n";
    }
    outFile << "------------------\n";
}

void Connection::makeFriends(Connection* newFriend){
    this -> friends.push_back(newFriend);

}

