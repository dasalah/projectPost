#include <iostream>
#include <iomanip>
#include <fstream>
#include<string>

using namespace std;


typedef struct {
    int postcode;
    int postpaid;
    string sendername;
    string recivername;
    string sendercity;
    string recivercity;
    string viewpost;
    int viewpaid[13];

} marsole;

class Date{
private:
    int day;
    int month;
    char FullDate[6];
public:
    Date(){
        day=1;
        month=1;
    }
    void setmonth(int m){
        while (m<1||m>12){
            cout<<"Invald month. Please enter a number betwen 1 and 12:"<<endl;
            cin>>m;
        }
        month=m;
    }
    void setday(int d){
        while (d<1||d>31){
            cout<<"Invald day. Please enter a number betwen 1 and 31:"<<endl;
            cin>>d;
        }
        day=d;
    }
    string printdate(){
        ostringstream date;
        date<<setfill('0')<<setw(2)<<month<<"/"<<setw(2)<<day;
        return date.str();

    }
};

//for function number 1 and 2
bool checkpostcode(int postcode){
    ifstream file1("file1.txt");
    if(!file1){
        cerr<<"Erorr"<<endl;
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

//entering a new parcel
void darj() {

    marsole m;
    fstream file1("file.txt", ios::app);
    if (!file1) {
        cerr << "somrthing went wrong during opening the file please make sure that the file that you chose exists!" << endl;
        exit(1);
    }
    cout << "enter your postcode:" << endl;
    cin>>m.postcode;
    while(checkpostcode(m.postcode)){
        cout<<"Invalid postcode. Please enter a valid postcode:"<<endl;
        cin>>m.postcode;
    }
    cout << "enter the price of your parcel:" << endl;
    cin >> m.postpaid;
    cout << "enter sender's name:" << endl;
    cin >> m.sendername;
    cout << "enter reciver's name:" << endl;
    cin >> m.recivername;
    cout << "enter sender's city:" << endl;
    cin >> m.sendercity;
    cout << "enter reciver's city:" << endl;
    cin >> m.recivercity;
    int ds, ms;
    Date s;
    cout << "enter sending day:" << endl;
    cin >> ds;
    s.setday(ds);
    cout << "enter sending month: " << endl;
    cin >> ms;
    s.setmonth(ms);

    file1<< m.postcode <<" "<< m.sendername <<" "<< s.printdate() <<" "<< m.recivername <<" "<< m.recivercity <<" "<< m.postpaid << endl;
    cout << "Data successfully recorded\n";
    file1.close();
}

//entering delivery of a parcel
void tahvil() {
    fstream file2("get.txt", ios::app);
    if (!file2) {
        cerr << "somrthing went wrong during opening the file. please make sure that the file that you chose exists!" << endl;
        exit(1);
    }
    marsole recive;
    Date Recive;
    int dr, mr;
    cout <<"enter your postcode:"<< endl;
    cin >> recive.postcode;
    while(!checkpostcode(recive.postcode)){
        cout<<"Invalid postcode. Please enter a valid postcode:"<<endl;
        cin>>recive.postcode;
    }
    cout<<"enter reciving day:"<<endl;
    cin>>dr;
    Recive.setday(dr);
    cout<< "enter reciving month:" <<endl;
    cin>>mr;
    Recive.setmonth(mr);
    file2<<recive.postcode<<" "<<Recive.printdate()<<endl;
    cout << "Data successfully recorded." << endl;
    file2.close();
}

//info of certain date
void DayInfo() {
    marsole m;
    Date d;
    int day, month;
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
    cin>>day;
    d.setday(day);
    cout<<"enter intended month:"<<endl;
    cin>>month;
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
        system("color c");
        cout<<"No shipments have been sent on your intended date\n";

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
    Date d;
    int code;
    string line, time, FullDate;
    cout << "enter your post code:";
    cin >> code;
    fstream file1("file.txt", ios::in);
    fstream file2("get.txt", ios::in);
    if (!file1.is_open()) {
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
                    cout << endl << "Date Recive: " << FullDate << endl;
                    break;
                }
                else {
                    cout << endl << "Received date not found.";
                }

            }
        }
        else {
            cout << "PostCode is NOT FOUND!";
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
    int maxcount = 1;
    fstream file1("file.txt", ios::in);
    if (!file1) {
        cerr << "somthing went wrong during opening thr file please make sure the file the you chose exists!" << endl;
        exit(07);
    }
    while (!file1.eof()) {
        file1 >> m.postcode >> m.sendername >> m.sendercity >> date >> m.recivername >> m.recivercity >> ma.postpaid;
        int sendcount = 1;
        file1.seekg(0, ios::beg);
        while (!file1.eof()) {

            file1 >> ma.postcode >> ma.sendername >> m.sendercity >> date2 >> ma.recivername >> ma.recivercity >> ma.postpaid;
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
    string date, date2, maxreceiver;
    int maxcount = 1;
    fstream file1("file1.txt", ios::in);
    if (!file1) {
        cerr << "somthing went wrong during opening thr file please make sure the file the you chose exists!" << endl;
        exit(07);
    }
    while (!file1.eof()) {
        file1 >> m.postcode >> m.sendername >> m.sendercity >> date >> m.recivername >> m.recivercity >> ma.postpaid;
        int receivecount = 1;
        file1.seekg(0, ios::beg);
        while (!file1.eof()) {

            file1 >> ma.postcode >> ma.sendername >> m.sendercity >> date2 >> ma.recivername >> ma.recivercity >> ma.postpaid;
            if (ma.recivername == m.recivername) {
                receivecount++;
            }

        }
        if (receivecount > maxcount) {
            maxcount = receivecount;
            maxreceiver = ma.recivername;
        }
    }
    cout<< "The person who has received the most shipments is " <<maxreceiver<< ", with "<<maxcount<<" shipments."<<endl;
}


//city exchanges
void city() {

    marsole m, t;

    string date, date2, f1, f2;

    int counter;

    ifstream file1("file1.txt");

    if (!file1) {

        cerr << "somthing went wrong during opening thr file please make sure the file the you chose exists!" << endl;

        exit(1);

    }
    while (!file1.eof()) {

        int count=0;

        bool citypair = false;

        file1 >> m.postcode >> m.sendername >> m.sendercity >> date >> m.recivername >> m.recivercity >> m.postpaid;

        ifstream file1_2("file.txt");

        while (!file1_2.eof()) {

            file1_2 >> t.postcode >> t.sendername >> t.sendercity >> date2 >> t.recivername >> t.recivercity>> t.postpaid;

            if ((m.recivercity == t.recivercity) && (m.sendercity == t.sendercity) && (m.recivercity != m.sendercity)) {

                count++;

                citypair = true;

            }

        }

        file1_2.close();

        if (citypair) {

            cout << m.sendercity << setw(6) << m.recivercity << setw(6) << count << setw(4) << endl;

        }

        file1.close();

    }
}
int main() {

    while (1) {
        int n;
        system("color f");
        system("cls");
        cout
                << "1-register a new shipment       \n"
                << "2-indert receipt time         \n"
                << "3-View Daily Posts         \n"
                << "4-View Package Information     \n"
                << "5-max sender                 \n"
                << "6-max reciver                  \n"
                << "7-Monthly income           \n"
                << "8-Number of intercity shipments  \n\n"
                << "Please enter your request number:\n";

        cin >> n;

        while (1) {
            switch (n) {
                case 1:
                    darj();
                    break;
                case 2:
                    tahvil();
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
                case 0:
                    continue;
                default: cout << "wrong number";
            }
            cout << "do you want to continue?(y/n)\n";
            char ch;
            cin >> ch;
            if (ch == 'n' || ch == 'N') break;
            else {
                break;
            }
        }
    }

}
