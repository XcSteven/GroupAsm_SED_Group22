#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::string;
using std::vector;

class Acc {
private:
    string username;
    string pwd;
public:
    Acc(){};
    Acc(string username, string pwd) {
        this->username = username;
        this->pwd = pwd;
    }

    string getAccUsername() {
        return username;
    }

    string getAccPassword() {
        return pwd;
    }
    
    void setAccUserName(string usrn) {
        username = usrn;
    };
    void setAccPassword(string pass) {
        pwd = pass;
    };

    friend class System;
};

class System {
public:
    vector<Acc*> users;
    System(){};
};

int main(){
    int key;
    int a;
    System appSys;
    while(true){
        cout<<"EEET2482/COSC2082 ASSIGNMENT \n"
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
        switch (key){
            case 1:
                cout << "This is your menu: \n"
                << "1. View all available vacation houses \n"
                << "2. Register member \n"
                << "3. Exit \n"
                << "Enter your choice: ";
                cin >> a;
                if(a == 3){
                    return 0;
                }
                if (a == 2) {
                    string username;
                    string pwd;
                    Acc *newAcc = new Acc(username, pwd);
                    cout << "-----Register account--------\n";
                    cout << "Please enter username: ";
                    cin >> username;
                    newAcc->setAccUserName(username);
                    cout << "Please enter password: ";
                    cin >> pwd;
                    newAcc->setAccPassword(pwd);
                    //Store account into the system (if the registration is successful)
                    appSys.users.push_back(newAcc);
                    //Check:
                    cout << "All accounts in the system: \n";
                    for (Acc *eachUser: appSys.users) {
                        cout << "Name = " << eachUser->getAccUsername() << 
                                ", pwd = " << eachUser->getAccPassword();
                    }
                    return 0;
                }
        }
    }
}