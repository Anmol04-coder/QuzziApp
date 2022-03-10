#include <string>
#include <bits/stdc++.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include "quiz.h"
#include "conio2.h"
#include <vector>
using namespace std;

void User::setUserDetails(string user_id,string pwd,string u_name)
{
    strcpy(this->userid,user_id.c_str());
    strcpy(this->pwd,pwd.c_str());
    strcpy(this->uname,u_name.c_str());
}


void Admin::create_admin(string userid, string password,string username)
{
    fstream fobj("Admin.bin",ios::binary|ios::in);
    if(fobj.fail())
    {
        fobj.open("Admin.bin",ios::out|ios::binary);
        Admin adminUser;
        adminUser.setUserDetails(userid,password,username);
        fobj.write((char *)&adminUser,sizeof(Admin));
        cout<<"File created!";
    }
    else
        cout<<"File already present";
    fobj.close();
}

int User::input()
{
    int i=0;
    clrscr();
    textcolor(GREEN);
        for(int i = 0; i < 85; i++)
            cout<<"*";
        gotoxy(37,2);
        textcolor(LIGHTRED);
        cout << "QUIZ APPLICATION\n";
        textcolor(GREEN);
        for(int i = 0; i < 85; i++)
            cout<<"*";
        gotoxy(61,4);
        textcolor(WHITE);
        cout << "press 0 to exist/Go Back\n\n\n\n";
        textcolor(YELLOW);
        for(int i = 0; i < 85; i++)
            cout << "*";
        gotoxy(1,18);
        textcolor(YELLOW);
        for(int i = 0; i < 85; i++)
            cout << "*";
        gotoxy(37,12);
        cout << "Enter UserId:";
        textcolor(WHITE);
        cin.getline(userid,20);
        if(strcmp(userid,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(41,25);
            printf("Login Cancelled");
            _getch();
            textcolor(YELLOW);
            return 0;
        }
        char ch;
        textcolor(YELLOW);
        gotoxy(37,13);
        cout << "Enter Password:";
        textcolor(WHITE);
        while(true)
        {
            ch = getch();
            if(ch==13)
                break;
            if(ch==8)
            {
                if(i==0)
                    continue;
                cout<<"\b \b";
                i--;
                continue;
            }
            cout << ch;
            delay(200);
            cout << "\b*";
            pwd[i]=ch;
            i++;
        }
        pwd[i]='\0';
        if(strcmp(pwd,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(41,25);
            printf("Login Cancelled");
            getch();
            textcolor(YELLOW);
            return 0;
        }

        return 1;


}

int User::checkUserExist(string usertype)
{
    if(strcmp(userid,"")==0||strcmp(pwd,"")==0)
    {
        gotoxy(41,25);
        textcolor(LIGHTRED);
        cout << "Both field are mandatory";
        getch();
        return 0;
    }
    ifstream fin;
    User *uptr;
    if(usertype=="admin")
    {
        fin.open("Admin.bin",ios::in|ios::binary);
        uptr=new Admin;
    }
    else if(usertype=="student")
    {
        fin.open("Student.bin",ios::in|ios::binary);
        uptr = new Student;
    }
    else
    {
        gotoxy(41,25);
        textcolor(LIGHTRED);
        cout << "wrong usertype passed!";
        getch();
        return 0;
    }
    bool useridfound=0,pwdFound=0;
    while(1)
    {
        fin.read((char *)uptr,sizeof(*uptr));
        if(fin.eof())
            break;
        if(strcasecmp(userid,uptr->userid)==0)
        {
            if(strcmp(pwd,uptr->pwd)==0)
            {
                 useridfound=pwdFound=1;
                break;
            }
            useridfound=1;
        }
    }
    bool result=0;
    if(useridfound==0)
    {
         gotoxy(25,18);
         textcolor(LIGHTRED);
         cout << "No such user exists!";
          getch();
    }
    else if(pwdFound==0)
    {
         gotoxy(25,18);
         textcolor(LIGHTRED);
         cout << " Invalid password!";
         getch();
    }
    else
    {
        result = 1;
        strcpy(uname,uptr->uname);
    }
    fin.close();
    return result;
}
string User::getName()
{
    string UNAME(uname);
    return UNAME;
}
string User::getUserID()
{
    string USERID;
    USERID = userid;
    return USERID;
}
void Admin::addQuestion()
{
    Question qObj;
    qObj.add();
    qObj.viewQuestion();
    clrscr();
}
void Question::add()
{
    fstream fobj("Question.bin",ios::app|ios::binary|ios::in);
    if(!fobj)
    {
        gotoxy(32,18);
        textcolor(LIGHTRED);
        cout<<"Sorry! File cannot be opened!";
        getch();
        return;
    }
    fobj.seekg(0,ios::end);
    if(fobj.tellg()==0)
        quesid=1;
    else
    {
        fobj.seekg(-1*sizeof(*this),ios::end);
        fobj.read((char *)this,sizeof(*this));
        cout<<"Last Question Id Is "<<quesid;
        quesid++;

    }
    cout<<endl<<"New Question Id Is "<<quesid;
    getch();
    char uchoice;
    do
    {
        clrscr();
        textcolor(WHITE);
        gotoxy(58,4);
        cout<<"Press 0 to Exit/Go Back";
        textcolor(LIGHTGREEN);
        gotoxy(1,1);
        for(int i=1;i<=85;i++)
            cout<<"*";
        gotoxy(1,3);
        for(int i=1;i<=85;i++)
            cout<<"*";
        gotoxy(32,2);
        textcolor(LIGHTRED);
        cout<<"QUIZ APP";
        textcolor(WHITE);
        gotoxy(25,5);
        cout<<"***** ADD QUESTION DETAILS *****";
        gotoxy(1,8);
        textcolor(YELLOW);
        string str;
        cout<<"Enter question:";
        cin.ignore();
        textcolor(WHITE);
        getline(cin,str,'*');
        if(strcmp(str.c_str(),"0")==0)
        {
            gotoxy(1,24);
            textcolor(LIGHTRED);
            cout<<"Closing add question"<<endl;
            getch();
            fobj.close();
            return;
        }
        strncpy(ques,str.c_str(),499);
        textcolor(LIGHTGREEN);
        cout<<endl<<"Carries Marks:";
        textcolor(YELLOW);
        cin>>tot_marks;
        textcolor(LIGHTGREEN);
        cout<<endl<<"OPTIONS"<<endl<<endl;
        textcolor(YELLOW);
        cout<<"(a)";
        cin.ignore();
        textcolor(WHITE);
        getline(cin,str);
        strncpy(op1,str.c_str(),99);
        textcolor(YELLOW);
        cout<<"(b)";
        textcolor(WHITE);
        getline(cin,str);
        strncpy(op2,str.c_str(),99);
        textcolor(YELLOW);
        cout<<"(c)";
        textcolor(WHITE);
        getline(cin,str);
        strncpy(op3,str.c_str(),99);
        textcolor(YELLOW);
        cout<<"(d)";
        textcolor(WHITE);
        getline(cin,str);
        strncpy(op4,str.c_str(),99);
        bool valid;
        do
        {
            gotoxy(1,19);
            textcolor(YELLOW);
            cout<<endl<<"Enter correct ans(a/b/c/d):  \b";
            textcolor(WHITE);
            cin>>ans;
            if(ans>='a' && ans<='d')
                valid=true;
            else
            {
                gotoxy(24,22);
                textcolor(LIGHTRED);
                cout<<"Invalid choice. Please try again";
                getch();
                valid=false;
            }

        }while(valid==false);
        fobj.write((char *)this,sizeof(*this));
        quesid++;
        gotoxy(24,22);
        printf("\t\t\t\t\t\t\t");
        gotoxy(34,22);
        textcolor(LIGHTGREEN);
        cout<<"QUESTION ADDED SUCCESSFULY!";
        getch();
        gotoxy(1,24);
        textcolor(LIGHTMAGENTA);
        cout<<endl<<"Do you want to add more questions (Y/N):";
        textcolor(WHITE);
        cin>>uchoice;
    }while(uchoice=='y'||uchoice=='Y');
    fobj.close();


}

void Admin::viewQuestion()
{
    Question qObj;
    qObj.viewQuestion();
    clrscr();
}

void Question::viewQuestion()
{
    ifstream fin("Question.bin",ios::in|ios::binary);
    if(!fin)
    {
        (1,10);
        textcolor(LIGHTRED);
        cout << "NO Question have been added yet!";
        getch();
        return;
    }
    fin.seekg(0,ios::end);
    if(fin.tellg()==0)
    {
        (1,10);
        textcolor(LIGHTRED);
        cout << "NO Question present in the file!";
        getch();
        return;
    }
    clrscr();
    fin.seekg(0);
    while(1)
    {
        textcolor(LIGHTGREEN);
        gotoxy(1,1);
        for(int i = 1; i < 85; i++)
            cout << "*";
        gotoxy(1,3);
        for(int i = 1; i < 85; i++)
            cout << "*";
        gotoxy(32,2);
        textcolor(LIGHTRED);
        cout << "Quiz App;";
        textcolor(WHITE);
        gotoxy(25,5);
        cout << "***SHOW QUESTION DETAILS***";
        gotoxy(1,7);
        textcolor(LIGHTGREEN);
        for(int i=1;i<85;i++)
            cout<<"*";
        gotoxy(1,9);
        fin.read((char*)this,sizeof(*this));
        if(fin.eof())
        {
            cout << endl;
            textcolor(LIGHTRED);
            gotoxy(35,10);
            cout << "No more Question present!";
            getch();
            break;
        }
        else
        {
            show();
            getch();
            clrscr();
        }
    }
    fin.close();
}

void Question::show()
{
    cout << endl;
    textcolor(YELLOW);
    cout << "Q." << quesid << "  ";
    cout << ques << endl;
    cout << "Carries Marks: " << tot_marks << endl;
    cout << "a. " << op1 << endl;
    cout << "b. " << op1 << endl;
    cout << "c. " << op1 << endl;
    cout << "d. " << op1 << endl;
    textcolor(LIGHTGREEN);
    cout << endl << "correct Option" << ans;
}

void Admin::removeQuestion()
{
    Question qObj;
    qObj.Remove();
    clrscr();
}

void Question::Remove()
{
        clrscr();
        textcolor(WHITE);
        gotoxy(58,4);
        cout<<"Press 0 to Exit/Go Back";
        textcolor(LIGHTGREEN);
        gotoxy(1,1);
        for(int i=1;i<=85;i++)
            cout<<"*";
        gotoxy(1,3);
        for(int i=1;i<=85;i++)
            cout<<"*";
        gotoxy(32,2);
        textcolor(LIGHTRED);
        cout<<"QUIZ APP";
        textcolor(WHITE);
        gotoxy(25,5);
        cout<<"***** REMOVE QUESTION DETAILS *****";
        ifstream fin("Question.bin",ios::in|ios::binary);
        if(!fin)
        {
            gotoxy(35,10);
            textcolor(LIGHTRED);
            cout<<"Sorry! File cannot be opened!";
            getch();
            return;
        }
        fin.seekg(0,ios::end);
        if(fin.tellg()==0)
        {
            gotoxy(35,10);
            textcolor(LIGHTRED);
            cout<<"No questions available for deletion!";
            getch();
            fin.close();
            return;
        }
        getch();
        gotoxy(1,8);
        textcolor(YELLOW);
        cout<<"Enter Question ID:";
        bool found=false,valid;
        int id;
        ofstream fout("temp.bin",ios::out|ios::binary);
        if(!fout)
        {
            gotoxy(35,10);
            textcolor(LIGHTRED);
            cout<<"Sorry! removal not possible!";
            getch();
            fin.close();
            return;
        }
        fin.seekg(0);
        do
        {
            valid=true;
            cin>>id;
            if(id==0)
            {
                fin.close();
                fout.close();
                remove("temp.bin");
                return;
            }
            if(id<0)
            {
                valid=false;
                gotoxy(1,24);
                textcolor(LIGHTRED);
                cout<<"\t\t\t\t\t\t\t\t\t\t\rInvalid Question ID";
                getch();
                gotoxy(19,8);
                cout<<"\t\t\t\t\t\t\t\t\t";
                gotoxy(19,8);
                textcolor(WHITE);
            }
            else
            {
                while(true)
                {
                    fin.read((char*)this,sizeof(*this));
                    if(fin.eof())
                        break;
                    if(this->quesid==id)
                    {
                        found=true;
                        continue;
                    }
                    else
                    {
                        fout.write((char*)this,sizeof(*this));
                    }
                }
                fout.close();
                fin.close();
                if(found)
                {
                    textcolor(WHITE);
                    gotoxy(1,24);
                    cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\rQuestion Removed Successfully!";
                    getch();
                    remove("Question.bin");
                    rename("temp.bin","Question.bin");
                }
                else
                {
                    textcolor(LIGHTRED);
                    gotoxy(1,24);
                    cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\rQuestion Id Not Found!";
                    getch();
                    remove("temp.bin");
                    getch();
                }
            }
        }while(valid==false);
}


void Admin::addStudent()
{
    Student studobj;
    studobj.add();
    clrscr();
}
void Student::add()
{
    char uchoice;
    int id;
    char stuid[10];
    string str;
    fstream fobj("Student.bin",ios::app|ios::in|ios::binary);
    fobj.seekg(0,ios::end);
    if(fobj.tellg()==0)
        id=1;
    else
    {
        fobj.seekg(-1*sizeof(*this),ios::end);
        fobj.read((char*)this,sizeof(*this));
        char* pos= strchr(userid,'-');
        if(pos!=NULL)
        {
            id=atoi(pos+1);
            id++;
        }

    }
    cout << "id is :" << id;
    getch();
    fobj.seekg(0,ios::end);
    do
    {
        clrscr();
        textcolor(WHITE);
        gotoxy(58,4);
        cout<<"Press 0 to EXIST/GO back";
        gotoxy(37,2);
        textcolor(LIGHTRED);
        cout << "Quizz App";
        textcolor(LIGHTGREEN);
        gotoxy(1,1);
        for(int i = 1; i <= 85; i++)
            cout << "~";
        gotoxy(1,3);
        for(int i = 1; i <= 85; i++)
            cout << "~";
        textcolor(WHITE);
        gotoxy(25,5);
        cout << "****ADD STUDENT DETAILS****";
        gotoxy(1,8);
        textcolor(YELLOW);
        cout << "Enter student name:";
        cin.ignore();
        textcolor(WHITE);
        getline(cin,str);
        strncpy(uname,str.c_str(),19);
        if(strcmp(uname,"0")==0)
        {
            gotoxy(1,24);
            textcolor(LIGHTRED);
            cout << "Cancelling Add Student..."<<endl;
            getch();
            fobj.close();
            return;
        }
        textcolor(YELLOW);
        cout << "Enter student pass:";
        textcolor(WHITE);
        getline(cin,str);
        strncpy(pwd,str.c_str(),19);
        if(strcmp(pwd,"0")==0)
        {
            gotoxy(1,24);
            textcolor(LIGHTRED);
            cout << "Cancelling Add Student..."<<endl;
            getch();
            fobj.close();
            return;
        }
        sprintf(stuid,"STU-%d",id);
        strcpy(userid,stuid);
        fobj.write((char*)this,sizeof(*this));
        gotoxy(30,15);
        textcolor(LIGHTGREEN);
        cout << "STUDENT ADDED SUCCESSFULLY! ";
        cout << endl << "STUDENT ID IS :"<< userid;
        getch();
        gotoxy(1,20);
        textcolor(MAGENTA);
        cout << "DO you want to add more student (Y\N) ?";
        cin>>uchoice;
        id++;
    }while(uchoice=='y'||uchoice=='Y');

}
void Admin::viewStudent()
{
    Student stuObj;
    stuObj.showStudentDetails();
    clrscr();
}
void Student::showStudentDetails()
{
    ifstream fin("Student.bin",ios::in|ios::binary);
    if(!fin)
    {
        (1,10);
        textcolor(LIGHTRED);
        cout << "NO Student have been added yet!";
        getch();
        return;
    }
    fin.seekg(0,ios::end);
    if(fin.tellg()==0)
    {
        (1,10);
        textcolor(LIGHTRED);
        cout << "NO Student present in the file!";
        getch();
        return;
    }
    clrscr();
    fin.seekg(0);
    while(1)
    {
        textcolor(LIGHTGREEN);
        gotoxy(1,1);
        for(int i = 1; i < 85; i++)
            cout << "*";
        gotoxy(1,3);
        for(int i = 1; i < 85; i++)
            cout << "*";
        gotoxy(32,2);
        textcolor(LIGHTRED);
        cout << "Quiz App;";
        textcolor(WHITE);
        gotoxy(25,5);
        cout << "***SHOW Student DETAILS***";
        gotoxy(1,7);
        textcolor(LIGHTGREEN);
        for(int i=1;i<85;i++)
            cout<<"*";
        gotoxy(1,9);
        fin.read((char*)this,sizeof(*this));
        if(fin.eof())
        {
            cout << endl;
            textcolor(LIGHTRED);
            gotoxy(35,10);
            cout << "No more Student present!";
            getch();
            break;
        }
        else
        {
            show();
            getch();
            clrscr();
        }
    }
    fin.close();
}
void User::show()
{
    cout << endl;
    textcolor(YELLOW);
    cout << "User ID: ";
    textcolor(GREEN);
    cout<< userid<< "  ";
    cout << endl;
    textcolor(YELLOW);
    cout << "Name: ";
    textcolor(GREEN);
    cout<< uname<< "  ";
}
void Admin::removeStudent()
{
    Student stuobj;
    stuobj.Remove();

}
void Student::Remove()
{
    clrscr();
        textcolor(WHITE);
        gotoxy(58,4);
        cout<<"Press 0 to Exit/Go Back";
        textcolor(LIGHTGREEN);
        gotoxy(1,1);
        for(int i=1;i<=85;i++)
            cout<<"*";
        gotoxy(1,3);
        for(int i=1;i<=85;i++)
            cout<<"*";
        gotoxy(32,2);
        textcolor(LIGHTRED);
        cout<<"QUIZ APP";
        textcolor(WHITE);
        gotoxy(25,5);
        cout<<"***** REMOVE STUDENT DETAILS *****";
        ifstream fin("Student.bin",ios::in|ios::binary);
        if(!fin)
        {
            gotoxy(35,10);
            textcolor(LIGHTRED);
            cout<<"Sorry! File cannot be opened!";
            getch();
            return;
        }
        fin.seekg(0,ios::end);
        if(fin.tellg()==0)
        {
            gotoxy(35,10);
            textcolor(LIGHTRED);
            cout<<"No student available for deletion!";
            getch();
            fin.close();
            return;
        }
        getch();
        gotoxy(1,8);
        textcolor(YELLOW);
        cout<<"Enter student ID:";
        bool found=false,valid;
        int id;
        ofstream fout("temp.bin",ios::out|ios::binary);
        if(!fout)
        {
            gotoxy(35,10);
            textcolor(LIGHTRED);
            cout<<"Sorry! removal not possible!";
            getch();
            fin.close();
            return;
        }
        fin.seekg(0);
        do
        {
            valid=true;
            cin>>id;
            if(id==0)
            {
                fin.close();
                fout.close();
                remove("temp.bin");
                return;
            }
            if(id<0)
            {
                valid=false;
                gotoxy(1,24);
                textcolor(LIGHTRED);
                cout<<"\t\t\t\t\t\t\t\t\t\t\rInvalid Question ID";
                getch();
                gotoxy(19,8);
                cout<<"\t\t\t\t\t\t\t\t\t";
                gotoxy(19,8);
                textcolor(WHITE);
            }
            else
            {
                while(true)
                {
                    fin.read((char*)this,sizeof(*this));
                    if(fin.eof())
                        break;
                    int i;
                    char* pos= strchr(userid,'-');
                    if(pos!=NULL)
                    {
                        i=atoi(pos+1);
                    }
                    if(i==id)
                    {
                        found=true;
                        continue;
                    }
                    else
                    {
                        fout.write((char*)this,sizeof(*this));
                    }
                }
                fout.close();
                fin.close();
                if(found)
                {
                    textcolor(WHITE);
                    gotoxy(1,24);
                    cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\rStudent Removed Successfully!";
                    getch();
                    remove("Student.bin");
                    rename("temp.bin","Student.bin");
                }
                else
                {
                    textcolor(LIGHTRED);
                    gotoxy(1,24);
                    cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\rQuestion Id Not Found!";
                    getch();
                    remove("temp.bin");
                    getch();
                }
            }
        }while(valid==false);
}

void Student::quiz()
{
    Question quesObj;
    quesObj.startQuiz(userid);
}
void Question::startQuiz( string id)
{
    ifstream fin("Question.bin",ios::in|ios::binary);
    if(fin.fail())
    {
        gotoxy(28,20);
        textcolor(LIGHTRED);
        cout << "No Question have been added Yet!";
        getch();
        return;
    }
    vector<Question>vecQues;
    while(1)
    {
        fin.read((char*)this,sizeof(*this));
        if(fin.eof())
            break;
        vecQues.push_back(*this);
    }
    fin.close();
    vector<int>vecRand;
    srand((unsigned int)time(NULL)); // generate random id w.r.t time
    int randno;
    while(1)
    {
        randno=rand()%vecQues.size();
        if(ispresent(vecRand,randno)==true)
            continue;
        vecRand.push_back(randno);
        if(vecRand.size()==vecQues.size())
            break;
    }
    int count = 0;
    User userObj;
    int local_marks = 0;
    int local_tot_marks = 0;
    string name = userObj.getName(id);
    for(int i = 0; i < vecQues.size();i++)
    {
        int index = vecRand.at(i);
        *this = vecQues.at(index);
        clrscr();
        gotoxy(37,2);
        textcolor(LIGHTRED);
        cout << "Quiz App";
        textcolor(YELLOW);
        gotoxy(1,4);
        for(int j = 1; j <=85; j++)
            cout<<"*";
        textcolor(WHITE);
        gotoxy(50,5);
        cout << name;
        gotoxy(10,5);
        cout << "Total Question:"<< vecQues.size()<<endl;
        gotoxy(1,6);
        textcolor(YELLOW);
        for(int j = 1; j <= 85; j++)
            cout << "*";
        textcolor(GREEN);
        gotoxy(1,8);
        count++;
        cout << count << ")";
        gotoxy(4,8);
        cout << this->ques << endl << endl;
        textcolor(LIGHTGRAY);
        cout << "a." << this->op1 << endl << endl;
        cout << "b." << this->op2 << endl << endl;
        cout << "c." << this->op3 << endl << endl;
        cout << "d." << this->op4 << endl << endl;
        bool valid;
        char uans;
        do
        {

            textcolor(YELLOW);
            cout<<"Enter your option(a/b/c/d):  \b";
            cin>>uans;
            if(uans>='a' && uans<='d')
                valid=true;
            else
            {
                valid=false;
                gotoxy(24,22);
                textcolor(LIGHTRED);
                cout<<"Invalid option entered. Try again";
                getch();
                gotoxy(24,22);
                cout<<"\t\t\t\t\t\t\t\t\t";
                gotoxy(1,18);
            }

        }while(valid==false);

        local_tot_marks+=this->tot_marks;
        if(uans==this->ans)
            local_marks+=this->tot_marks;
    }
    clrscr();
    gotoxy(37,2);
    textcolor(LIGHTRED);
    cout << "Quiz App";
    textcolor(YELLOW);
    gotoxy(1,4);
    for(int i = 1; i < 85; i++)
        cout << "*";
    gotoxy(32,10);
    textcolor(LIGHTRED);
    cout << "** Test Finished **";
    gotoxy(22,12);
    cout << "Press Any Key To Go Back To Main Menu";
    getch();
    StudentPerformance sp;
    sp.setMarksDetails(id,local_marks,local_tot_marks);

}
/** This member function will accept 2 arguments as parameters and only checks whether the 2nd argument is
present inside the 1st argument which is an object of class vector which is a collection of question ids
and as discussed above it will help us in creation of collection of random question id vector class object
 */

bool ispresent(vector<int> & v,int value)
{
    for(int i=0;i<v.size();i++)
    {
        if(v.at(i)==value)
            return true;
    }
    return false;
}
void StudentPerformance::setMarksDetails(string id, int marks, int tot_marks)
{
    strcpy(studid,id.c_str());
    this->marks=marks;
    this->tot_marks = tot_marks;
    saveMarksDetails();
}
void StudentPerformance::saveMarksDetails()
{
    ofstream fout("Performance.bin",ios::app|ios::binary);
    if(!fout)
    {
        gotoxy(1,26);
        textcolor(LIGHTRED);
        cout << "Error in creating/opening file";
        getch();
        return;
    }
    fout.write((char *)this,sizeof(*this));
    fout.close();
}
string User::getName(string id)
{
    ifstream fin("Student.bin",ios::in|ios::binary);
    User userObj;
    while(1)
    {
        fin.read((char*)this,sizeof(User));
        if(fin.eof())
        {
            cout << "No match records found";
            break;
        }
        int result = strcmp(this->getUserID().c_str(),id.c_str());
        if(result == 0)
        {
            fin.close();
            return this->uname;
        }
    }
    fin.close();
    return NULL;
}
void Student::viewPerformance()
{
    StudentPerformance studP;
    studP.viewDetails();
}

void StudentPerformance::viewDetails()
{
    ifstream fin("Performance.bin",ios::in|ios::binary);
    if(!fin)
    {
        (1,10);
        textcolor(LIGHTRED);
        cout << "Data is not present!";
        getch();
        return;
    }
    fin.seekg(0,ios::end);
    if(fin.tellg()==0)
    {
        (1,10);
        textcolor(LIGHTRED);
        cout << "No quiz is attend";
        getch();
        return;
    }
    clrscr();
    fin.seekg(0);
    while(1)
    {
        textcolor(LIGHTGREEN);
        gotoxy(1,1);
        for(int i = 1; i < 85; i++)
            cout << "*";
        gotoxy(1,3);
        for(int i = 1; i < 85; i++)
            cout << "*";
        gotoxy(32,2);
        textcolor(LIGHTRED);
        cout << "Quiz App;";
        textcolor(WHITE);
        gotoxy(25,5);
        cout << "***View Report Card***";
        gotoxy(1,7);
        textcolor(LIGHTGREEN);
        for(int i=1;i<85;i++)
            cout<<"*";
        gotoxy(1,9);
        fin.read((char*)this,sizeof(*this));
        if(fin.eof())
        {
            cout << endl;
            textcolor(LIGHTRED);
            gotoxy(35,10);
            cout << "No more data is present!";
            getch();
            break;
        }
        else
        {
            show();
            getch();
            clrscr();
        }
    }
    fin.close();
}

void StudentPerformance::show()
{
    cout << endl;
    User uObj;
    gotoxy(1,8);
    string name = uObj.getName();
    cout << "Name: " << name;
    gotoxy(1,10);
    textcolor(LIGHTGREEN);
    cout << "S.NO";
    gotoxy(30,10);
    cout << "Marks Obtain";
    gotoxy(60,10);
    cout << "Total Marks";
}
