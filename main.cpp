#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::string;
using std::vector;

class Admin {
private:
    string name;
    string pwd;

public:
    Admin(string name, string pwd) {
        this->name = name;
        this->pwd = pwd;
    }
    bool login(string name, string pwd){
        if(this->name == name && this->pwd == pwd){
            return true;
        }
        else{
            return false;
        }
    }
};

class Mem {
private:
    string username;
    string pwd;
    string full_name;
    string phone_num;
    double credit;

public:
    Mem(){};
    Mem(string username, string pwd, string full_name, string phone_num, double credit) {
        this->username = username;
        this->pwd = pwd;
        this->full_name = full_name;
        this->phone_num = phone_num;
        this->credit = credit;
    }

    // Getters
    string getMemUsername() {
        return username;
    }

    string getMemPassword() {
        return pwd;
    }

    string getMemFullname() {
        return full_name;
    }

    string getMemPhoneNumber() {
        return phone_num;
    }

    double getMemCredit() {
        return credit;
    }
    
    // Setters
    void setMemUsername(string usrn) {
        username = usrn;
    };

    void setMemPassword(string pass) {
        pwd = pass;
    };

    void setMemFullname(string fn) {
        full_name = fn;
    }

    void setMemPhoneNumber(string pn) {
        phone_num = pn;
    }

    void setMemCredit(double cre) {
        credit = cre;
    }

    friend class System;
};

class System {
public:
    vector<Mem*> members;
    System(){};
};

int main() {
    int key;
    int a;
    Admin admin("admin", "123");
    System appSys;
    string username;
    string pwd;
    string phone_num;
    double cre;
    char name[100] = {0};

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
                    Mem *newMem = new Mem(username, pwd, name, phone_num, cre);
                    cout << "-----Register account--------\n";

                    cout << "Please enter username: ";
                    cin >> username;
                    newMem->setMemUsername(username);

                    cout << "Please enter password: ";
                    cin >> pwd;
                    newMem->setMemPassword(pwd);

                    cout << "Please enter your full name: ";
                    cin.getline(name, 100);
                    newMem->setMemFullname(name);

                    cout << "Please enter your phone number: ";
                    cin >> phone_num;
                    newMem->setMemPhoneNumber(phone_num);

                    newMem->setMemCredit(500);

                    //Store account into the system (if the registration is successful)
                    appSys.members.push_back(newMem);

                    //reward 500 points for registration
                    cout<<"Your are rewarded 500 credit points for registering your account!\n";
                    cout<<"\n";

                    //Check:
                    cout << "All accounts in the system: \n";
                    for (Mem *eachMem: appSys.members) {
                        cout << "Name = " << eachMem->getMemUsername() << 
                                ", Password = " << eachMem->getMemPassword() <<
                                ", Full Name = " << eachMem->getMemFullname() <<
                                ", Phone Number = " << eachMem->getMemPhoneNumber() <<
                                ", credit = " << eachMem->getMemCredit() << "\n";
                    }
                    break;
                }

            case 2:
                cout << "Please enter your username: ";
                cin >> username;
                cout << "Please enter your password: ";
                cin >> pwd;
                //Check username and password
                for (Mem *eachMem : appSys.members) {
                    if(eachMem->getMemUsername() == username && eachMem->getMemPassword() == pwd) {
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
                    return 0;
                }
        }
    }
}