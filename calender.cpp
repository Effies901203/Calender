#define _CRT_SECURE_NO_WARNINGS_
#include<iostream>
using namespace std;
#include<stdio.h>
#include<ctime>
#include<stdlib.h>
#include<string.h>

class calender{
private:
    int year;
    int month;
    int date;
    char week[50];
    int week_num;
public:
    calender(){
        time_t now = time(0);
        t = localtime(&now);
        char tool[50];
        strftime(tool, sizeof(tool), "%Y", t);
        sscanf(tool, "%d", &year);
        
        strftime(tool, sizeof(tool), "%d", t);
        sscanf(tool, "%d", &date);
        strftime(week, sizeof(week), "%a", t);
        
        strftime(tool, sizeof(tool), "%m", t);
        sscanf(tool, "%d", &month);
        
        if (strcmp(week, "Mon")==0) week_num=1;
        if (strcmp(week, "Tue")==0) week_num=2;
        if (strcmp(week, "Wed")==0) week_num=3;
        if (strcmp(week, "Thur")==0) week_num=4;
        if (strcmp(week, "Fri")==0) week_num=5;
        if (strcmp(week, "Sat")==0) week_num=6;
        if (strcmp(week, "Sun")==0) week_num=7;
    };
    struct tm* t;
    void window(int[], int[]);
    void newtask(tm*);
    void recall();
    void save(int, int, char[], char[], char[]);
    void nextmonth(int*, int*, int*, int);
    void lastmonth(int*, int*, int*, int);
    void remember(int, char[]);
    char task1[7][50];
    char task2[7][50];
    char task3[7][50];
};
int main(){
    int will;
    FILE* f;
    calender what;
    cout<<"Have you ever used the app? (yes: 1 or no: 0) "; cin>>will;
    if (will==1){
        what.recall();
        what.newtask(what.t);
    }
    if (will==0){
        f=fopen("record.txt", "w");
        what.newtask(what.t);
    }
    return 0;
}
void calender::window(int mo[2], int da[7]){
    char week_sample[7][50];
    int date_sample[7], j, month_sample[7], year_sample[7];

    strcpy(week_sample[0],"Mon");
    strcpy(week_sample[1],"Tue");
    strcpy(week_sample[2],"Wed");
    strcpy(week_sample[3],"Thur");
    strcpy(week_sample[4],"Fri");
    strcpy(week_sample[5],"Sat");
    strcpy(week_sample[6],"Sun");
    for(int i=0;i<7;i++){
        month_sample[i]=month;
        year_sample[i]=year;
    }
    for(int i=0;i<7;i++)
    {
        if(strcmp(week,week_sample[i])==0){
            date_sample[i]=date;
            for(j=0;j<(7-i);j++){
                date_sample[i+j]=date+j;
                if(date+j>28 && month_sample[i+j]==2)
                    nextmonth(&year_sample[i+j], &month_sample[i+j], &date_sample[i+j], j);
                if(date+j>30 && (month_sample[i+j]==4 || month_sample[i+j]==6 || month_sample[i+j]==9 || month_sample[i+j]==11))
                    nextmonth(&year_sample[i+j], &month_sample[i+j], &date_sample[i+j], j);
                if(date+j>31 && (month_sample[i+j]==1 || month_sample[i+j]==3 || month_sample[i+j]==5 || month_sample[i+j]==7 || month_sample[i+j]==8 || month_sample[i+j]==10 || month_sample[i+j]==12))
                    nextmonth(&year_sample[i+j], &month_sample[i+j], &date_sample[i+j], j);
            }
            for(j=0;j<i+1;j++){
                date_sample[i-j]=date-j;
                if(date-j<1)
                    lastmonth(&year_sample[i-j], &month_sample[i-j], &date_sample[i-j], j);
            }
            break;
        }
    }
    for(int i=0;i<7;i++)
    {
        if(i==3)printf(" Thur.|");
        else printf(" %s. |",week_sample[i]);
        if(da[i]==date_sample[i])
            printf("・%s",task1[i]);
        printf("\n");
        printf("%2d/%-2d |",month_sample[i], date_sample[i]);
        if(da[i]==date_sample[i] && strcmp(task2[i],"none"))
            printf("・%s",task2[i]);
        printf("\n      |");
        if(da[i]==date_sample[i] && strcmp(task3[i],"none"))
            printf("・%s",task3[i]);
            printf("\n\n");
    };
}
void calender::recall(){
    FILE* f1;
    int m, d, i=0, da[7], mo[7];
    char t1[50], t2[50], t3[50];
    if((f1=fopen("record.txt", "r"))==NULL)
        printf("Cannot Find The File.");
    while((fscanf(f1,"%d %d %s %s %s", &m, &d, t1, t2, t3)==5))
    {
        i=week_num+d-date-1;
        da[i]=d;
        mo[i]=m;
        strcpy(task1[i], t1);
        strcpy(task2[i], t2);
        strcpy(task3[i], t3);
    };
    window(mo, da );
    fclose(f1);
}

void calender::save(int m, int d, char task1[50], char task2[50], char task3[50]){
    FILE* f2;
    int i;
    if((f2=fopen("record.txt", "a+"))==NULL)
        printf("Cannot Write The File.");
    if((i=fscanf(f2,"%d %d", &m, &d))!=2)
        fprintf(f2,"%d %d %s %s %s", m, d, task1, task2, task3);
    if((i=fscanf(f2,"%d %d", &m, &d))==2)
        fprintf(f2,"%s %s %s",task1, task2, task3);
    fclose(f2);
    
}
void calender::newtask(tm* t){
    int task_month, task_date, will, m_will=1;
    while (m_will==1){
    cout<<"Would you like to add new task? (yes: 1 or no: 0) "; cin>>m_will;
    if (m_will==1)
    {   cout<<"task month: "; cin>>task_month;
        cout<<"task date: "; cin>>task_date;
        int i=week_num+task_date-date-1;
        int mo[7]; int da[7];
        mo[i]=task_month;
        da[i]=task_date;
        cout<<"task1: "; cin>>task1[i]; cout<<endl;
        cout<<"Would you like to add new task in the same day? (yes: 1 or no: 0) "; cin>>will;
        if (will==1)
        {   cout<<"task2: "; cin>>task2[i];
            cout<<"Would you like to add new task in the same day?(yes: 1 or no: 0) "<<endl<<"Remeber that don't arrange over 3 tasks!"; cin>>will;
            if (will==1)
            {
                cout<<"task3: "; cin>>task3[i];
            }
            else strcpy(task3[i],"none");
        }
        else {
            strcpy(task2[i],"none");
            strcpy(task3[i],"none");
        }
        save(task_month, task_date, task1[i], task2[i], task3[i] );
        recall();
    }
    }
}
void calender::lastmonth(int* y, int* m, int* d, int i){
        switch (*m){
            case 1:
                *y=*y-1;
                *m=12;
                *d=32-i;
                break;
            case 3:
                if(*y%4==0) *d=30-i;
                if(*y%4!=0) *d=29-i;
                *m=*m+1;
                break;
            case 5:
            case 7:
            case 10:
            case 12:
                *m=*m-1;
                *d=1;
                break;
            case 2:
            case 4:
            case 6:
            case 8:
            case 9:
            case 11:
                *m=*m-1;
                *d=32-i;
                break;
    }
}
void calender:: nextmonth(int* y, int* m, int* d, int i){
        switch (*m){
            case 12:
                *y=*y+1;
                *m=1;
                *d=1;
                break;
            case 2:
                if(*y%4==0 && *d>29) *d=1;
                if(*y%4!=0 && *d>28) *d=1;
                *m=3;
                break;
            default:
                *m=*m+1;
                *d=1;
                break;

        }
}
