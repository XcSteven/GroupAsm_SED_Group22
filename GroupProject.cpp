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

class House {
private:
    Member* owner;
    string city;
    string startDate;
    string endDate;
    double points;
    Member* occupier;
    double rating;
public:
    House(){}
    House(Member* owner, string city, string startDate, string endDate, double points, Member* occupier, double rating){
        this->owner = owner;
        this->city = city;
        this->startDate = startDate;
        this->endDate = endDate;
        this->points = points;
        this->occupier = occupier;
        this->rating = rating;
    }
    // Getters
    // string getCity() { return city; }
    // string getStartDate() { return startDate; }
    // string getEndDate() { return endDate; }
    // string getPoints() { return points; }
    
    // Setters
    // void setMemberUsername(string usrn) { username = usrn; };
    // void setMemberPassword(string pass) { pwd = pass; };
    // void setMemberFullname(string fn) { full_name = fn; }
    // void setMemberPhoneNumber(string pn) { phone_num = pn; }
    // void setMemberCredit(double cre) { credit = cre; }

friend class System;
};

class System {
public:
    vector<Member*> members;
    vector<House*> houses;
    System(){};

    void addMember(Member* member){
        members.push_back(member);
    }

    void addHouse(House* house){
        houses.push_back(house);
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
    void viewHouses(string username){
        cout << "---------------------------------\n" 
            <<"List of registered houses: \n";
        for (auto house: houses) {
            cout << "Host username: " << house->owner->getMemberUsername() << "\n"
            << "Location: " << house->city << "\n" 
            << "Points consuming per day: " << house->points << "\n" 
            << "Occupier: " << house->occupier << "\n";
            if (username == "Admin" || username != "Guest"){
                cout << "Start date: " << house->startDate << "\n" 
                << "End date: " << house->endDate << "\n" 
                << "Rating: " << house->rating << "\n";
            } cout << "---------------------------------\n";
        }
    }

    Member* searchMemByUsername(string username){
        for (auto mem: members) {
            if (mem->username == username){return mem;}
        }
    }

};

//Function to check username while Guest register
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

void denyRequest(string username, vector<string> requestArr){
    std::fstream myFile;
    string line;
    int count = 0;
    vector<int> deleteIndex;
    for (int i = 0; i < sizeof(requestArr); i++){
        if (count == 1 && requestArr[i] == username){
            deleteIndex.push_back(i-1);
            deleteIndex.push_back(i);
            count = 0;
        } else if (count == 1){ count = 0; } 
        else { count++; }
    }
    count = 0;
    for (int index: deleteIndex){
        index -= count;
        requestArr.erase(requestArr.begin() + index);
        count++;
    }
    myFile.open("request.txt", std::ios::out);
    for (string request: requestArr){
        myFile << request << ",";
    }
    myFile.close();
}

int main() {
    //key and a are user's choices
    int key;
    int a;
    
    Admin admin;
    System appSys;
    //For Member
    string username, pwd, full_name, phone_num;
    double cre;
    char name[100] = {0};
    bool loggedin = false;
    //For House
    string city, startDate, endDate;
    double points;
    //For request
    vector<string> requestArr, requestTemp;

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

    //Read data from house.txt
    arr.clear();
    string occupier;
    double rating;
    count = 1;
    vector<string> houseArr;
    myFile.open("house.txt", std::ios::in);
    while(getline(myFile, line, ',')){
        arr.push_back(line);
    }
    myFile.close();

    for (int i = 0; i < arr.size(); i++){
        if (count == 1){
            username = arr[i];
        }
        if (count == 2){
            city = arr[i];
        }
        if (count == 3){
            startDate = arr[i];
        }
        if (count == 4){
            endDate = arr[i];
        }
        if (count == 5){
            points = std::stod(arr[i]);
        }
        if (count == 6){
            occupier = arr[i];
        }
        if (count == 7){
            rating = std::stod(arr[i]);
        }
        if (count == 8){
            if(occupier == "0"){
                appSys.addHouse(new House(appSys.searchMemByUsername(username),city,startDate,endDate,points,NULL,rating));
            } else {
                appSys.addHouse(new House(appSys.searchMemByUsername(username),city,startDate,endDate,points,appSys.searchMemByUsername(occupier),rating));
            }
            username = arr[i];
            count = 1;
        }
        count++;
    }
    if(occupier == "0"){
        appSys.addHouse(new House(appSys.searchMemByUsername(username),city,startDate,endDate,points,NULL,rating));
    } else {
        appSys.addHouse(new House(appSys.searchMemByUsername(username),city,startDate,endDate,points,appSys.searchMemByUsername(occupier),rating));
    }

    //Read data from request.txt
    myFile.open("request.txt", std::ios::in);
    while(getline(myFile, line, ',')){
        requestArr.push_back(line);
    }
    myFile.close();


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
                username = "Guest";
                cout << "This is your menu: \n"
                << "1. View all available vacation houses \n"
                << "2. Register member \n"
                << "3. Exit \n"
                << "Enter your choice: ";
                cin >> a;
                if(a == 32) {
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
                if (a == 1){
                    appSys.viewHouses(username);
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
                        loggedin = true;
                    }
                }
                if (loggedin == false){
                    cout << "Login failed" << "\n";
                    break;
                } else {
                    while (a != 5){
                        cout << "Welcome " << username << ":\n"
                        << "1. See your information \n"
                        << "2. Register a house \n"
                        << "3. Search a house \n"
                        << "4. View requests \n"
                        << "5. Exit \n"
                        << "Enter your choice: ";
                        cin >> a;
                        if(a == 1){
                            cout << "-----------------------\n";
                            cout << "Full name: " << appSys.searchMemByUsername(username)->getMemberFullname() << "\n"
                            << "Phone number: " << appSys.searchMemByUsername(username)->getMemberPhoneNumber() << "\n";
                            cout << "-----------------------\n";
                        }
                        if(a == 2) {
                            cout << "Please enter the city your house: ";
                            cin >> city;
                            cout << "Please enter start Date (dd-mm): ";
                            cin >> startDate;
                            cout << "Please enter end Date (dd-mm): ";
                            cin >> endDate;
                            cout << "Please enter point consuming per day: ";
                            cin >> points;
                            House *newHouse = new House(appSys.searchMemByUsername(username), city, startDate, endDate, points, NULL, 0);
                            appSys.addHouse(newHouse);
                            //Write mewHouse to file
                            std::ofstream myFile("house.txt", std::ios_base::app);
                            myFile << username << "," << city << "," 
                            << startDate << "," << endDate << "," << points << "," << "0,0,";
                            myFile.close();
                            cout << "House registered.\n";
                        }
                        if(a == 3) {
                            appSys.viewHouses(username);
                            cout << "Enter owner username of the house you want to send request: ";
                            cin >> occupier;
                            std::ofstream myFile("request.txt", std::ios_base::app);
                            myFile << username << "," << occupier << ",";
                            myFile.close();
                        }
                        if(a == 4) {
                            count = 0;
                            for (int i = 0; i < requestArr.size(); i++){
                                if (count == 1 && requestArr[i] == username){
                                    requestTemp.push_back(requestArr[i-1]);
                                    count = 0;
                                    loggedin = false; //Just re-use this boolean variable to print out information
                                } else if(count == 1){ count = 0; } else { count++; }
                            }
                            cout << "----------------------\n" <<"Requests:\n";
                            if (loggedin){ cout << "You have no request.\n"; } else {
                                for (string request: requestTemp){
                                    cout << "User: " << request << "\n";
                                }
                            }
                            cout << "----------------------\n";
                            cout << "Type the username you want to Approve, or type \"DENY\" to deny all request: ";
                            cin >> occupier;
                            if (occupier == "DENY"){
                                denyRequest(username, requestArr);
                                cout << "All requests have been denied.";
                            }
                        }
                    } return 0;
                }
                
            case 3:
                cout << "Please enter your username: ";
                cin >> username;
                cout << "Please enter your password: ";
                cin >> pwd;
                
                //Check username and password
                if(admin.login(username, pwd)) {
                    cout << "Login successful" << "\n";

                    appSys.viewMembers();
                    appSys.viewHouses(username);

                    return 0;
                }

                
        }
    }
}