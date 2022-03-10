#include <iostream>
#include <string>
#include <cstring>
#include "conio2.h"
#include "quiz.h"
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int c,type,choice;

    textcolor(GREEN);
    for(int i = 0; i < 85; i++)
        cout<<"*";
    gotoxy(37,2);
    textcolor(LIGHTRED);
    cout << "QUIZ APPLICATION\n";
    for(int i = 0; i < 85; i++)
        cout<<"*";
    gotoxy(25,9);
    textcolor(YELLOW);
    cout << "WELCOME TO TECH TEST - QUIZ APPLICATION";
    textcolor(LIGHTGREEN);
    gotoxy(25,13);
    cout << "TEST YOUR SKILL! IMPROVE YOUR KNOWLEDGE!";
    textcolor(WHITE);
    gotoxy(1,25);
    cout << "Press any key to continue...";
    getch();
    Admin::create_admin("uadmin","abc","Sachin");
    do
    {
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
        cout << "1.Admin\n\n";
        gotoxy(37,13);
        cout << "2.Student\n\n";
        gotoxy(37,15);
        cout << "Select your role: ";
        cin>>type;
        cin.ignore();

        if(type == 0)
            break;

        if(type==1)
        {
            Admin u;
            do
            {
                c = u.input();
                if(c==0)
                    break;
                c=u.checkUserExist("admin");
                if(c==1)
                {
                    gotoxy(25,20);
                    textcolor(LIGHTGREEN);
                    cout << "Login Accepted!";
                    gotoxy(28,20);
                    cout << "welcome " << u.getName();
                    gotoxy(25,22);
                    textcolor(WHITE);
                    cout << "Press any key to contunue";
                    getch();
                    while(1)
                    {
                        clrscr();
                        textcolor(GREEN);
                        for(int i = 0; i < 85; i++)
                            cout<<"*";
                        gotoxy(37,2);
                        textcolor(LIGHTRED);
                        cout << "QUIZ APPLICATION\n";
                        for(int i = 0; i < 85; i++)
                            cout<<"*";

                        textcolor(LIGHTGREEN);
                        gotoxy(40,6);
                        cout << "Admin Menu\n";
                        textcolor(YELLOW);
                        for(int i = 0; i < 85; i++)
                            cout<<"*";

                        gotoxy(37,8);
                        cout << "1.Add Question";
                        gotoxy(37,9);
                        cout << "2.Add student";
                        gotoxy(37,10);
                        cout << "3.show Question";
                        gotoxy(37,11);
                        cout << "4.show Student";
                        gotoxy(37,12);
                        cout << "5.Remove Question";
                        gotoxy(37,13);
                        cout << "6.Remove student";
                        gotoxy(37,14);
                        cout << "7.EXIST";

                        gotoxy(37,16);
                        cout << "Enter your choice:";
                        textcolor(WHITE);
                        cin >> choice;
                        switch(choice)
                        {
                        case 1:
                            clrscr();
                            u.addQuestion();
                            break;

                        case 2:
                            clrscr();
                            u.addStudent();
                            break;
                         case 3:
                            clrscr();
                            u.viewQuestion();
                            break;
                         case 4:
                            clrscr();
                            u.viewStudent();
                            break;
                         case 5:
                            clrscr();
                            u.removeQuestion();
                            break;
                         case 6:
                            clrscr();
                            u.removeStudent();
                            break;
                        case 7:
                            clrscr();
                            break;
                        default:
                            cout << "Wrong choice. Try again";
                            getch();

                        }
                        if(choice==7)
                            break;
                    }
                }
            }while(c==0);

        }
        else if(type==2)
        {
            Student studObj;
            do
            {
                c = studObj.input();
                if(c==0)
                {
                    gotoxy(30,14);
                    textcolor(LIGHTRED);
                    cout << "Login Cancelled";
                    gotoxy(1,20);
                    textcolor(WHITE);
                    cout << "Press any key to contunue";
                    getch();
                   break;
                }
                c=studObj.checkUserExist("student");
                if(c==1)
                {
                    gotoxy(25,20);
                    textcolor(LIGHTGREEN);
                    cout << "Login Accepted!";
                    gotoxy(28,20);
                    cout << "welcome " << studObj.getName();
                    gotoxy(25,22);
                    textcolor(WHITE);
                    cout << "Press any key to contunue";
                    getch();
                    while(1)
                    {
                        clrscr();
                        textcolor(GREEN);
                        for(int i = 0; i < 85; i++)
                            cout<<"*";
                        gotoxy(37,2);
                        textcolor(LIGHTRED);
                        cout << "QUIZ APPLICATION\n";
                        for(int i = 0; i < 85; i++)
                            cout<<"*";

                        textcolor(LIGHTGREEN);
                        gotoxy(40,6);
                        cout << "Student Menu\n";
                        textcolor(YELLOW);
                        for(int i = 0; i < 85; i++)
                            cout<<"*";

                        gotoxy(37,8);
                        cout << "1.Start Quiz";
                        gotoxy(37,9);
                        cout << "2.View Performance";
                        gotoxy(37,11);

                        cout << "7.EXIST";

                        gotoxy(37,13);
                        cout << "Enter your choice:";
                        textcolor(WHITE);
                        cin >> choice;
                        switch(choice)
                        {
                        case 1:
                            clrscr();
                            studObj.quiz();
                            break;

                        case 2:
                            clrscr();
                            studObj.viewPerformance();
                            break;
                         case 3:
                            clrscr();
                            //u.viewQuestion();
                            break;
                        default:
                            cout << "Wrong choice. Try again";
                            getch();

                        }
                        if(choice==7)
                            break;
                    }
                }
            }while(c==0);
        }
        else
        {
            textcolor(LIGHTRED);
            gotoxy(30,14);
            cout<<"\t\t\t\t\t\t\t\t\t";
            gotoxy(30,14);
            cout<<"Invalid User Type";
            getch();
            textcolor(WHITE);
            clrscr();
        }



    }while(1);
    return 0;
}
