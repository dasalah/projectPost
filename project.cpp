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
typedef struct {
    int smonth;
    int sday;
    int rmonth;
    int rday;
    char FullDate[6];
    string FullDateCheck[6];
} date;

void darj() {

    date d;
    marsole m;
    fstream marsolefile("file.txt", ios::in);
    if (!marsolefile) {
        cerr << "somrthing went wrong during opening the file please make sure that the file that you chose exists!" << endl;
        exit(1);
    }

    cout << "enter your postcode:" << endl;
    cin >> m.postcode;
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
    // get time
    for (int i = 0; i < 1; i++) {
        cout << "enter sending day:" << endl;
        cin >> d.sday;
        if (d.sday > 31 || d.sday < 0) { i--; cout << "Please enter the date correctly\n"; }

    }
    for (int i = 0; i < 1; i++) {
        cout << "enter sending month:" << endl;
        cin >> d.smonth;
        if (d.smonth > 12 || d.smonth < 0) { i--; cout << "Please enter the date correctly\n"; }
    }
  /*  for (int i = 0; i < 1; i++) {
        cout << "enter reciving day:" << endl;
        cin >> d.rday;
        if (d.rday > 31 || d.rday < 0) { i--; cout << "Please enter the date correctly\n"; };
    }
    for (int i = 0; i < 1; i++) {
        cout << "enter reciving month" << endl;
        cin >> d.rmonth;
        if (d.rmonth > 12 || d.rmonth < 0) { i--; cout << "Please enter the date correctly\n"; }
    }*/
    //file 1 ok


    marsolefile << m.postcode << setw(10) << m.sendername << setw(10) << d.smonth << '/' <<d.sday << setw(10) << m.recivername << setw(10) << m.recivercity << setw(10) << m.postpaid << endl;
    cout << "Data successfully recorded\n";
    marsolefile.close();


}


void tahvil() { //function 2  OK      #struct no made
    fstream get("get.txt", ios::app); //create file 2 ok
    if (!get) {
        cerr << "somrthing went wrong during opening the file please make sure that the file that you chose exists!" << endl;
        exit(1);
    }
    marsole reacive;
    date Reacive;
    int i;
    cout << "enter your postcode:" << endl;
    cin >> reacive.postcode;


    for (i = 0; i < 1; i++) {
        cout << "enter reciving day:" << endl;
        cin >> Reacive.rday;
        if (Reacive.rday > 31 || Reacive.rday < 0) { i--; cout << "Please enter the date correctly\n"; }
    }
    for (i = 0; i < 1; i++) {
        cout << "enter reciving month:" << endl;
        cin >> Reacive.rmonth;
        if (Reacive.rmonth > 12 || Reacive.rmonth < 0) { i--; cout << "Please enter the date correctly\n"; };
    }
    get << reacive.postcode << setw(10) << Reacive.rmonth << '/' << Reacive.rday << endl;
    cout << "Data successfully recorded." << endl;
    get.close();
}


void DayInfo() {
    marsole m;							// create struct
    date d;
    string line,lineCheck;
    string time,TimeCheck;
    fstream file("file.txt", ios::in); //open files
    fstream date("get.txt", ios::in);
    if (!file && date) {
        cerr << "somrthing went wrong during opening the file please make sure that the file that you chose exists!" << endl;
        exit(1);
    }
    cout << "enter your date  (MM/DD)" << endl;; //get data
    cin >> TimeCheck;

    while (!file.eof())
    {
        file >> m.postcode >> m.sendername >>m.sendercity >>time >> m.recivername >> m.recivercity >> m.postpaid;
        if (TimeCheck == time) {
            cout << m.postcode<<" " << m.sendername<<" " <<m.sendercity<<" " <<time <<" "<< m.recivername<<" " << m.recivercity <<" "<< m.postpaid<<" ";
            while(!date.eof())    {//check date reacive
                marsole m2;

                date>>m2.postcode>>d.FullDate;
                if(m2.postcode==m.postcode){
                    cout<<d.FullDate<<endl;
                }

            }
        }
    }

    file.close();
    date.close();

}


void rate() {
    marsole m;
    date d;
    string line;
    for (int i = 0; i < 13; i++) {
        m.viewpaid[i] = 0;
    }

    fstream rate("file.txt", ios::in);
    if (!rate.is_open()) {
        cerr << "somrthing went wrong during opening the file please make sure that the file that you chose exists!" << endl;
        exit(1);
    }
    while (!rate.eof())
    {
        rate >> m.postcode >> m.sendername >> m.sendercity >> d.FullDate >> m.recivername >> m.recivercity >> m.postpaid;
        if (d.FullDate[0] == '0' && d.FullDate[1] == '1') {
            m.viewpaid[1] += m.postpaid;
        }
        if (d.FullDate[0] == '0' && d.FullDate[1] == '2') {
            m.viewpaid[2] += m.postpaid;

        }
        if (d.FullDate[0] == '0' && d.FullDate[1] == '3') {
            m.viewpaid[3] += m.postpaid;

        }
        if (d.FullDate[0] == '0' && d.FullDate[1] == '4') {
            m.viewpaid[4] += m.postpaid;

        }
        if (d.FullDate[0] == '0' && d.FullDate[1] == '5') {
            m.viewpaid[5] += m.postpaid;

        }
        if (d.FullDate[0] == '0' && d.FullDate[1] == '6') {
            m.viewpaid[6] += m.postpaid;

        }
        if (d.FullDate[0] == '0' && d.FullDate[1] == '7') {
            m.viewpaid[7] += m.postpaid;

        }
        if (d.FullDate[0] == '0' && d.FullDate[1] == '8') {
            m.viewpaid[8] += m.postpaid;

        }
        if (d.FullDate[0] == '0' && d.FullDate[1] == '9') {
            m.viewpaid[9] += m.postpaid;

        }
        if (d.FullDate[0] == '1' && d.FullDate[1] == '0') {
            m.viewpaid[10] += m.postpaid;

        }
        if (d.FullDate[0] == '1' && d.FullDate[1] == '1') {
            m.viewpaid[11] += m.postpaid;

        }
        if (d.FullDate[0] == '1' && d.FullDate[1] == '2') {
            m.viewpaid[12] += m.postpaid;

        }

    }
    system("color f");
    cout<<"The monthly income of the post office is as follows"<<endl;
    cout<<"farvardin: "<<setw(10)<<m.viewpaid[1]<<endl<<"ordibehesht:"<<setw(10)<<m.viewpaid[2]<<endl<<"khordad:"<<setw(10)<<m.viewpaid[3]<<endl
    <<"tir:"<<setw(10)<< m.viewpaid[4]<<endl<<"mordad:"<<setw(10)<<m.viewpaid[5]<<endl<<"shahrivar:"<<setw(10)<<m.viewpaid[6]<<endl
    <<"mehr:"<<setw(10)<<m.viewpaid[7]<<endl<<"aban:"<<setw(10)<<m.viewpaid[8]<<endl<<"azar:"<<setw(10)<<m.viewpaid[9]<<endl
    <<"dey:"<<setw(10)<<m.viewpaid[10]<<endl<<"bahman:"<<setw(10)<<m.viewpaid[11]<<endl<<"esfand:"<<setw(10)<<m.viewpaid[12]<<endl;
}



void info() {
    marsole m;
    date d;
    int code;
    string line, time;
    cout << "enter your post code:";
    cin >> code;
    fstream data("file.txt", ios::in);
    fstream DataDate("get.txt", ios::in);
    if (!data.is_open()) {
        cerr << "somrthing went wrong during opening the file please make sure that the file that you chose exists!" << endl;
        exit(1);
    }

    while (!data.eof())
    {
        data >> m.postcode >> m.sendername >>m.sendercity >>time >> m.recivername >> m.recivercity >> m.postpaid;
        if (m.postcode == code) {
            cout <<"post code:" <<m.postcode<<endl<<"Sender Name:"<< m.sendername<<endl<<"Sender City"<<m.sendercity<<endl<<"Send Time: "<<time<<endl<<"Reciver Name: "<< m.recivername<<endl<<"Reciver City: "<< m.recivercity <<endl<<"Postal Fare"<< m.postpaid;
            while(!DataDate.eof())    {//check date reacive
                marsole m2;

                DataDate>>m2.postcode>>d.FullDate;
                if(m2.postcode==m.postcode){
                    cout<<endl<<"Date Recive: "<<d.FullDate<<endl;
                    break;
                }
                else{
                    cout<<endl<<"Received date not found.";
                }

            }
        }
        else{
            cout<<"PostCode is NOT FOUND!";
            break;
        }
    }

    data.close();
    DataDate.close();
}

/*
void maxsend(){
    marsole m,ma;
    string date,date2, maxsender;
    int maxcount=1;
    fstream readfile("file.txt",ios::in);
    if(!readfile){
        cerr<<"somthing went wrong during opening thr file please make sure the file the you chose exists!"<<endl;
        exit(07);
    }
    while(!readfile.eof()){
        readfile>>m.postcode>>m.sendername>>m.sendercity>>date>>m.recivername>>m.recivercity;
        int sendcount=1;
       readfile.seekg(0,ios::beg);
        while(!readfile.eof()){

            readfile>>ma.postcode>>ma.sendername>>m.sendercity>>date2>>ma.recivername>>ma.recivercity;
            if(ma.sendername==m.sendername){
                sendcount++;
            }

        }
        if(sendcount>maxcount){
            maxcount=sendcount;
            maxsender+ma.sendername;
        }
    }
    cout<<maxsender<<" sent the most post with"<<maxcount<<"sending";
}
*/
int main() {

    while (1) {
        int n;
        system("color 2");
        system("cls");
        cout
            << "1- register a new shipment       \n"
            << "2- indert receipt time         \n"
            << "3- View Daily Posts         \n"
            << "4-View Package Information     \n"
            << "5- max sender                 \n"
            << "6-                   \n"
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
         //       maxsend();
                break;
            case 7:
                rate();
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
