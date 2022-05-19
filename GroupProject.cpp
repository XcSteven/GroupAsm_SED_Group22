#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using std::cout;
using std::cin;
using std::string;
using std::vector;

class Admin {
private:
    string name = "a";
    string pwd = "a";

public:
    Admin(){}
    bool login(string name, string pwd){
        if(this->name == name && this->pwd == pwd){
            return true;
        }
        else{
            return false;
        }
    }
};

class Member {
private:
    string username;
    string pwd;
    string full_name;
    string phone_num;
    double credit;

public:
    Member(){};
    Member(string username, string pwd, string full_name, string phone_num) {
        this->username = username;
        this->pwd = pwd;
        this->full_name = full_name;
        this->phone_num = phone_num;
        this->credit = 500;
    }
    Member(string username, string pwd, string full_name, string phone_num, double cre) {
        this->username = username;
        this->pwd = pwd;
        this->full_name = full_name;
        this->phone_num = phone_num;
        this->credit = cre;
    }

    // Getters
    string getMemberUsername() { return username; }
    string getMemberPassword() { return pwd; }
    string getMemberFullname() { return full_name; }
    string getMemberPhoneNumber() { return phone_num; }
    double getMemberCredit() { return credit; }
    
    // Setters
    void setMemberUsername(string usrn) { username = usrn; };
    void setMemberPassword(string pass) { pwd = pass; };
    void setMemberFullname(string fn) { full_name = fn; }
    void setMemberPhoneNumber(string pn) { phone_num = pn; }
    void setMemberCredit(double cre) { credit = cre; }

    friend class System;
};

class System {
public:
    vector<Member*> members;
    System(){};

    void addMember(Member* member){
        members.push_back(member);
    }

    void viewMembers(){
        cout << "---------------------------------\n" 
            <<"List of members: \n";
        for (auto mem: members) {
            cout << "Username: " << mem->username << "\n" 
            << "Password: " << mem->pwd << "\n" 
            << "Full name: " << mem->full_name << "\n" 
            << "Phone number: " << mem->phone_num << "\n" 
            << "Credit point: " << mem->credit << "\n"
            << "---------------------------------\n";
        }
    }

};

bool checkUsername(string username){   
    std::fstream myFile;
    myFile.open("account.txt", std::ios::in);
    string line;
    int count = 1;
    vector<string> a;
    while(getline(myFile, line, ',')){
        a.push_back(line);
    }
    for (int i = 0; i < a.size(); i++){
        if (count == 1){
            if (username == a[i]){
                return true;
            }
        }
        if (count == 5){ count = 0;}
        count++;
    }
    myFile.close();
    return false;
};

int main() {
    int key;
    int a;
    Admin admin;
    System appSys;
    string username;
    string pwd;
    string full_name;
    string phone_num;
    double cre;
    char name[100] = {0};

    //Read data from account.txt
    std::fstream myFile;
    string line;
    int count = 1;
    vector<string> arr;
    myFile.open("account.txt", std::ios::in);
    while(getline(myFile, line, ',')){
        arr.push_back(line);
    }
    myFile.close();

    for (int i = 0; i < arr.size(); i++){
        if (count == 1){
            username = arr[i];
        }
        if (count == 2){
            pwd = arr[i];
        }
        if (count == 3){
            full_name = arr[i];
        }
        if (count == 4){
            phone_num = arr[i];
        }
        if (count == 5){
            cre = std::stod(arr[i]);
        }
        if (count == 6){
            appSys.addMember(new Member(username,pwd,full_name,phone_num,cre));
            username = arr[i];
            count = 1;
        }
        count++;
    }
    appSys.addMember(new Member(username,pwd,full_name,phone_num,cre));

    while(true) {
        cout << "EEET2482/COSC2082 ASSIGNMENT \n"
        <<"VACATION HOUSE EXCHANGE APPLICATION \n"
        <<"\n"
        <<"Instructor: Mr. Linh Tran \n"
        <<"Group: Group 22 \n"
        <<"s3881388, Phan Quoc Thang \n"
        <<"s3877673, Bui Nguyen Ngoc Tuan \n"
        <<"s3891637, Tran Chi Toan \n"
        <<"\n"
        << "Use the app as 1.Guest    2.Member    3.Admin \n"
        <<  "Enter your choice: ";
        cin >> key;
        switch(key) {
            case 1:
                cout << "This is your menu: \n"
                << "1. View all available vacation houses \n"
                << "2. Register member \n"
                << "3. Exit \n"
                << "Enter your choice: ";
                cin >> a;
                if(a == 3) {
                    return 0;
                }
                if (a == 2) {
                    Member *newMem = new Member(username, pwd, name, phone_num);
                    cout << "-----Register account--------\n";

                    cout << "Please enter username: ";
                    cin >> username;
                    if (!checkUsername(username)){
                        newMem->setMemberUsername(username);

                        cout << "Please enter password: ";
                        cin >> pwd;
                        newMem->setMemberPassword(pwd);

                        cin.ignore();

                        cout << "Please enter your full name: ";
                        
                        getline(cin, full_name);
                        newMem->setMemberFullname(full_name);

                        cout << "Please enter your phone number: ";
                        cin >> phone_num;
                        newMem->setMemberPhoneNumber(phone_num);

                        //Store account into the system (if the registration is successful)
                        appSys.addMember(newMem);
                        std::ofstream myFile("account.txt", std::ios_base::app);
                        myFile << newMem->getMemberUsername() << "," << newMem->getMemberPassword() << "," 
                        << newMem->getMemberFullname() << "," << newMem->getMemberPhoneNumber() << newMem->getMemberCredit() << ",";
                        myFile.close();

                        //reward 500 points for registration
                        cout<<"Your are rewarded 500 credit points for registering your account!\n";
                        cout<<"\n";
                    } else {
                        cout << "Username has already taken.\n";
                    }
                    break;
                }

            case 2:
                cout << "Please enter your username: ";
                cin >> username;
                cout << "Please enter your password: ";
                cin >> pwd;
                //Check username and password
                for (Member *eachMem : appSys.members) {
                    if(eachMem->getMemberUsername() == username && eachMem->getMemberPassword() == pwd) {
                        cout << "Login successful" << "\n";
                        return 0;
                    }
                }
                cout << "Login failed" << "\n";
                break;
                
            case 3:
                cout << "Please enter your username: ";
                cin >> username;
                cout << "Please enter your password: ";
                cin >> pwd;
                
                //Check username and password
                if(admin.login(username, pwd)) {
                    cout << "Login successful" << "\n";

                    appSys.viewMembers();

                    return 0;
                }

                
        }
    }
}