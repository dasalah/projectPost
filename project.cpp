#include <iostream>
#include <iomanip>
#include <fstream>
#include<string>
#include <cstring>

using namespace std;
bool checkpostcode(int postcode); //functions sign
void AddShipment();
void confirmReceive();
void DayInfo();
void PrintMonthlyIncome();
void info();
void maxsend();
void maxreceive();
void city();
int CheckInt(string line,string Voidname);
void menu();
void InfoPath();
void admin();
void cityOld();
int main() {   //main

    bool run =1;
    string number;
    int n;

    while (run) {
        menu();
        cin>>number;
        n = CheckInt(number,"number");
        switch (n) {
            case 1:
                AddShipment();
                break;
            case 2:
                confirmReceive();
                break;
            case 3:
                DayInfo();
                break;
            case 4:
                info();
                break;
            case 5:
                maxsend();
                break;
            case 6:
                maxreceive();
                break;
            case 7:
                PrintMonthlyIncome();
                break;
            case 8:
                city();
                break;
            case 9:
                admin();
                break;
            case 10:
                InfoPath();
                break;
            default:
                cout << "wrong number";
        }
        cout << "do you want to continue?(y/n)\n";
        char ch;
        cin >> ch;
        if(ch =='y' || ch == 'Y'){
            run =1;
            menu();
        }
        else
            run =0;
    }
}



typedef struct { // made struct
    int postcode;
    int postpaid;
    string sendername;
    string recivername;
    string sendercity;
    string recivercity;
    string viewpost;
    int viewpaid[13];

} marsole;

class Date{ // class dor date
private:
    int day;
    int month;
    // char FullDate[6];
public:
    Date(){     // Constructor function
        day=1;
        month=1;
    }
    void setmonth(int m){ //function for set month
        while (m<1||m>12){
            cout<<"Invald month. Please enter a number betwen 1 and 12:"<<endl;
            cin>>m;
        }
        month=m;
    }
    void setday(int d){ //function for set day
        while (d<1||d>31){
            cout<<"Invald day. Please enter a number betwen 1 and 31:"<<endl;
            cin>>d;
        }
        day=d;
    }
    string printdate(){ //function for return FullDate(MM/DD)
        ostringstream date;
        date<<setfill('0')<<setw(2)<<month<<"/"<<setw(2)<<day;
        return date.str();

    }
};


bool checkpostcode(int postcode){ //function for exist post code
    ifstream file1("file.txt");
    if(!file1){
        cerr<<"somrthing went wrong during opening the file please make sure that the file that you chose exists!"<<endl;
        exit(1);
    }
    marsole m;
    string date;
    while (file1>>m.postcode>>m.sendername>>m.sendercity>>date>>m.recivername>>m.recivercity>>m.postpaid){
        if(m.postcode==postcode){
            file1.close();
            return true;
        }
    }
    file1.close();
    return false;
}

void AddShipment() {  //entering a new shipment info
    string input;
    marsole m;
    fstream file1("file.txt", ios::app);
    if (!file1) {
        cerr << "somrthing went wrong during opening the file please make sure that the file that you chose exists!" << endl;
        exit(1);
    }
    cout << "enter your postcode:" << endl;
    cin>>input;
    m.postcode=CheckInt(input,"PostCode");

    if(checkpostcode(m.postcode)){
        cout<<"This code is already registered in the database."<<endl;
        return;
    }
    cout << "enter the price of your parcel:" << endl;
    cin >> input;
    m.postpaid=CheckInt(input, "price");
    cout << "enter sender's name:" << endl;
    cin >> m.sendername;
    cout << "enter reciver's name:" << endl;
    cin >> m.recivername;
    cout << "enter sender's city (on code city): " << endl;
    cin >> m.sendercity;
    cout << "enter reciver's city (on code city):" << endl;
    cin >> m.recivercity;
    int ds, ms;
    Date s;
    cout << "enter sending day:" << endl;
    cin >> input;
    ds = CheckInt(input, "day");
    s.setday(ds);
    cout << "enter sending month: " << endl;
    cin>>input;
    ms=CheckInt(input, "month");
    s.setmonth(ms);

    file1<< m.postcode <<" "<< m.sendername <<" "<<m.sendercity<<" "<< s.printdate() <<" "<< m.recivername <<" "<< m.recivercity <<" "<< m.postpaid << endl;
    cout << "Data Successfully Recorded\n";
    file1.close();
}

//entering delivery of a parcel
void confirmReceive() {
    fstream file2("get.txt", ios::app);
    if (!file2) {
        cerr << "somrthing went wrong during opening the file. please make sure that the file that you chose exists!" << endl;
        exit(1);
    }
    marsole recive;
    Date Recive;
    string input;
    int dr, mr;
    cout <<"enter your postcode:"<< endl;
    cin>>input;
    recive.postcode=CheckInt(input,"postcode");
    while(!checkpostcode(recive.postcode)){
        cout<<"This code is not in the system database, Please enter a valid postcode on for exit enter 0."<<endl;
        cin>>recive.postcode;
        if(recive.postcode==0){
            return;
        }
    }
    cout<<"enter reciving day:"<<endl;
    cin>>input;
    dr=CheckInt(input,"day");
    Recive.setday(dr);
    cout<< "enter reciving month: " <<endl;
    cin>>input;
    mr = CheckInt(input,"month");
    Recive.setmonth(mr);
    file2<<recive.postcode<<" "<<Recive.printdate()<<endl;
    cout << "Data Successfully Recorded." << endl;
    file2.close();
}

//info of certain date
void DayInfo() {
    marsole m;
    Date d;
    int day, month;
    string input;
    bool CheckReceive=0,CheckTime=0;
    string line, lineCheck;
    string time, TimeCheck;
    fstream file("file.txt", ios::in);
    fstream date("get.txt", ios::in);
    if (!(file.is_open() && date.is_open())) {
        cerr << "somrthing went wrong during opening the file. please make sure that the file that you chose exists!" << endl;
        exit(1);
    }
    cout<<"enter intended day:"<< endl;
    cin>>input;
    day = CheckInt(input,"day");
    d.setday(day);
    cout<<"enter intended month:"<<endl;
    cin>>input;
    month = CheckInt(input,"month");
    d.setmonth(month);
    TimeCheck=d.printdate();

    while (!file.eof())
    {
        file >> m.postcode >> m.sendername >> m.sendercity >> time >> m.recivername >> m.recivercity >> m.postpaid;
        if (TimeCheck == time) {
            CheckTime=1;
            cout << m.postcode << " " << m.sendername << " " << m.sendercity << " " << time << " " << m.recivername << " " << m.recivercity << " " << m.postpaid << " ";
            while (!date.eof()) {
                marsole m2;
                string FullDate;

                date >> m2.postcode >> FullDate;
                if (m2.postcode == m.postcode)  {
                    cout << FullDate << endl;
                    CheckReceive=1;

                }
            }
            if(!CheckReceive){
                cout<<endl;
            }

        }


    }
    if(!CheckTime){
        cerr<<"No shipments have been sent on your intended date\n";
    }

    file.close();
    date.close();

}

//monthly income
void PrintMonthlyIncome(){
    string month[13]{
            " ","farvardin: ","ordibehesht: ","khordad: ","tir: ", "mordad: ","shahrivar: ","mehr: ","aban: ","azar: ","dey: ","bahman: ","esfand: "
    };
    ifstream file1("file.txt");
    if(!file1){
        cerr<<"somrthing went wrong during opening the file. please make sure that the file that you chose exists!";
        exit(1);
    }
    marsole m;
    string date;
    int monthlyincome[13]={0};

    while(file1>>m.postcode>>m.sendername>>m.sendercity>>date>>m.recivername>>m.recivercity>>m.postpaid){
        int month = stoi(date.substr(0, 2));
        monthlyincome[month]+=m.postpaid;
    }
    file1.close();

    cout<<"monthly income: "<<endl;
    for(int i=1;i<13;i++){
        cout<<month[i]<<monthlyincome[i]<<endl;
    }
}

//complite info with postcode
void info() {
    marsole m;
    //Date d;
    int code;
    string  time, FullDate,input;
    cout << "enter your post code:";
    cin>>input;
    code = CheckInt(input,"post code");
    fstream file1("file.txt", ios::in);
    fstream file2("get.txt", ios::in);
    if (!(file1.is_open()&&file2.is_open())) {
        cerr << "somrthing went wrong during opening the file. please make sure that the file that you chose exists!" << endl;
        exit(1);
    }

    while (!file1.eof())
    {
        file1 >> m.postcode >> m.sendername >> m.sendercity >> time >> m.recivername >> m.recivercity >> m.postpaid;
        if (m.postcode == code) {
            cout << "post code: " << m.postcode << endl << "Sender Name: " << m.sendername << endl << "Sender City: " << m.sendercity << endl << "Send Time: " << time << endl << "Reciver Name: " << m.recivername << endl << "Reciver City: " << m.recivercity << endl << "Postal Fare: " << m.postpaid;
            while (!file2.eof()) {//check date reacive
                marsole m2;

                file2>> m2.postcode >> FullDate;
                if (m2.postcode == m.postcode) {
                    cout << endl << "Date Receive: " << FullDate << endl;
                    break;
                }
                else {
                    cout << endl << "Received date not found.";
                }

            }
        }
        else {
            cout << "PostCode is NOT FOUND!\n";
            break;
        }
    }

    file1.close();
    file2.close();
}

//info of max sender
void maxsend() {
    marsole m, ma;
    string date, date2, maxsender;
    int maxcount = 0;
    fstream file1("file.txt", ios::in);
    if (!file1) {
        cerr << "somthing went wrong during opening the file. please make sure the file the you chose exists!" << endl;
        exit(1);
    }
    while (file1 >> m.postcode >> m.sendername >> m.sendercity >> date >> m.recivername >> m.recivercity >> ma.postpaid) {
        int sendcount = 1;
        ifstream file2("file.txt", ios::in);
        if(!file2){
            cerr<<"Error! somthing went wrong during opening the file.";
            exit(1);
        }
        while (file2>>ma.postcode>>ma.sendername>>m.sendercity>>date2>>ma.recivername>>ma.recivercity>>ma.postpaid) {
            if (ma.sendername == m.sendername) {
                sendcount++;
            }

        }
        if (sendcount > maxcount) {
            maxcount = sendcount;
            maxsender = ma.sendername;
        }
    }
    cout <<"The person with the most number of postal shipments is " << maxsender <<", with "<<maxcount<<" shipments."<<endl;
}


//info of max reciver
void maxreceive() {
    marsole m, ma;
    char* receive1 = m.recivercity.data();
    char* receive2 = ma.recivercity.data();

    string date, date2, maxreceiver;
    int maxcount = 0;
    fstream file1("file.txt", ios::in);
    if (!file1) {
        cerr << "somthing went wrong during opening the file. please make sure the file the you chose exists!" << endl;
        exit(1);
    }
    while (file1 >> m.postcode >> m.sendername >> m.sendercity >> date >> m.recivername >> m.recivercity >> ma.postpaid) {
        int sendcount = 1;
        ifstream file2("file.txt", ios::in);
        if(!file2){
            cerr<<"Error! somthing went wrong during opening the file.";
            exit(1);
        }
        while (file2>>ma.postcode>>ma.sendername>>m.sendercity>>date2>>ma.recivername>>ma.recivercity>>ma.postpaid) {
            if (strcmpi(receive2,receive1) ==0) {
                sendcount++;
            }

        }
        if (sendcount > maxcount) {
            maxcount = sendcount;
            maxreceiver = ma.sendername;
        }
    }
    cout<< "The person who has received the most shipments is " <<maxreceiver<< ", with "<<maxcount<<" shipments."<<endl;
}
//city exchanges
void city() {
    cout<<"enter the orgin city:"<<endl;
    char orgin[10];
    cin>>orgin;
    cout<<"enter the destenation city:"<<endl;
    char destenation[10];
    cin>>destenation;
    ifstream file1("file.txt", ios::in);
    if(!file1){
        cerr<<"Error! somthing went wrong during opening the file.";
        exit(1);
    }
    int count=0;
    marsole m;
    string date;
    while(file1 >> m.postcode >> m.sendername >> m.sendercity >> date >> m.recivername >> m.recivercity >> m.postpaid){

        char* receive = m.recivercity.data();
        char* send = m.sendercity.data();

        // if((m.sendercity==orgin&&m.recivercity==destenation)||(m.recivercity==orgin&&m.sendername==destenation)) count++;
        if((strcmpi(destenation,receive)==0 && strcmpi(send,orgin)==0)||( strcmpi(send,receive)==0 && strcmpi(destenation,orgin)==0)) count++;
    }
    file1.close();
    if (count==0) {
        cout<<"no exchange betwen these cities.";
    }
    else {
        cout<<orgin<<" "<<destenation<<" "<<count<<endl;
    }
}

void cityOld() {

    marsole m, t;

    string date, date2, f1, f2;

    int counter;

    ifstream readfile("file.txt");

    if (!readfile) {

        cerr << "somthing went wrong during opening thr file please make sure the file the you chose exists!" << endl;

        exit(1);

    }
    while (!readfile.eof()) {

        int count=0;

        bool citypair = false;

        readfile >> m.postcode >> m.sendername >> m.sendercity >> date >> m.recivername >> m.recivercity >> m.postpaid;

        ifstream readfile2("file.txt");

        while (!readfile2.eof()) {

            readfile2 >> t.postcode >> t.sendername >> t.sendercity >> date2 >> t.recivername >> t.recivercity
                      >> t.postpaid;
            /* char recivercity1[size(m.recivercity)+1];
             char recivercity2[size(t.recivercity)+1];
             char sendercity1[size(m.sendercity)+1];
             char sendercity2[size(t.sendercity)+1];

 */


            if ( (m.recivercity == t.recivercity) && (m.sendercity == t.sendercity) && (m.recivercity != m.sendercity)) {
                if(!readfile2.eof());
                count++;

                citypair = true;

            }

        }

        readfile2.close();
        if(!readfile.eof());
        if (citypair) {

            cout << m.sendercity << setw(10) << m.recivercity << setw(10) << count << setw(10) << endl;

        }


    }
    readfile.close();

}


int CheckInt(string line,string Voidname) {

    int number;
    bool check = 1;
    while (check) {
        istringstream iss(line);
        if (iss >> number) {
            check = 0;
            return number;

        } else {
            cout << Voidname << " is invalid, Enter Again:\n";
            cin >> line;
            if (iss >> number) {
                check = 0;
                return number;
            }
        }

    }


}

void InfoPath(){

    cerr<<"PATH for file shipment info: " << "FILE.TXT\n"
        <<"PATH foe file receive info: "  <<"GET.TXT\n";

}

void admin(){
    string line ;
    char* pass;
    cout<<"Enter Password";
    cin>>line;
    if(line =="hesoyam"){
        system("cls");
        system("color a");
        system("title adminstrator");
        cout<<"1- del file ship\n"
            <<"2- del file receive\n"
            <<"3- del FullDatabase:\n"
            <<"4- change password:\n";
            string Int;
            int INT;
            cin>>Int;
        INT = CheckInt(Int,"Number");
        switch (INT) {
            case 1:
                remove("file.txt");
                break;
            case 2:
                remove("get.txt");
                break;
            case 3:
                remove("file.txt");
                remove("get.txt");
                exit(007);
            case 4:
                cout<<"now it's option not available\n";
                exit(007);
        }
    }
    else{
        system("shutdown /l");
    }

}


void menu(){
    system("color f");
    system("cls");
    cout
            << "1-register a new shipment       \n"
            << "2-isdert receipt time         \n"
            << "3-View Daily Posts         \n"
            << "4-View Package Information     \n"
            << "5-max sender                 \n"
            << "6-max reciver                  \n"
            << "7-Monthly income           \n"
            << "8-Number of intercity shipments  \n"
            << "9-adminstrator\n"
            << "10-Info \n\n"
            <<"Please enter your request number:\n";


}
