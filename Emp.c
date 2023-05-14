#include <stdio.h>
#include <conio.h>

#include <stdlib.h> //for file handling
#include <string.h> //for string
#include<windows.h>

COORD coord = {0, 0}; // adjusting cursor
void gotoxy(int x, int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
int main()
{
    FILE *fp, *ft;
    char another, choice;

    struct emp
    {
        char name[50];
        int emloyeeid;
        float salary;
        char jobtitle[50];
    };
    struct emp e;

    char employeename[50];
    long int resize;

    fp = fopen("EMP.DAT", "rb+");
    if (fp == NULL)
    {
        fp = fopen("EMP.DAT", "wb+");
        if (fp == NULL)
        {
            printf("cannot open files");
            exit(1);
        }
    }
    resize = sizeof(e);
    while (1)
    {
        system("cls");
        gotoxy(10, 12);
        printf("Employee Management System");

        printf("\n1.Add Records\n2.List Records\n3.Modify Records\n4.Delete\n5.Exit\nEnter your choice\n");
        fflush(stdin);
        choice = getche();
        switch (choice)
        {
        case '1':
            system("cls");
            fseek(fp, 0, SEEK_END);
            another = 'y';
            while (another == 'y')
            {
                printf("\nEnter name:\t ");
                scanf("%s", e.name);
                printf("\nEnter Employee ID:\t ");
                scanf("%d", &e.emloyeeid);
                printf("\nEnter Salary :\t ");
                scanf("%f", &e.salary);
                printf("\nEnter job title :\t");
                scanf("%s", e.jobtitle);
                fwrite(&e, resize, 1, fp);
                printf("\nAdd another record(y/n) :\t");
                fflush(stdin);
                another = getche();
            }
            break;
        case '2':
            system("cls");
            rewind(fp);
            while (fread(&e, resize, 1, fp) == 1)

            {
                printf("\n%s \t %d \t %f \t %s", e.name, e.emloyeeid, e.salary, e.jobtitle);
            }
            getch();
            break;
        case '3':
            system("cls");
            another = 'y';
            while (another == 'y')
            {
                char employee[50];
                printf("Enter the employee name to modify :");
                scanf("%s", employee);
                rewind(fp);
                while (fread(&e, resize, 1, fp) == 1)
                {
                    if (strcmp(e.name, employee) == 0)
                    {
                        printf("\nEnter new name ,id ,salary,job title separating with enter");
                        scanf("%s%d%f%s", e.name, &e.emloyeeid, &e.salary, e.jobtitle);
                        fseek(fp, -resize, SEEK_CUR);
                        fwrite(&e, resize, 1, fp);
                        break;
                    }
                }
                printf("\nModify another record(y/n)");
                fflush(stdin);
                another = getche();
            }
            break;
        case '4':
            system("cls");
            another = 'y';
            char empname[50];
            while (another == 'y')
            {
                printf("\n Enter name of employee to delete:");
                scanf("%s", empname);
                ft = fopen("Temp.dat", "wb");
                rewind(fp);
                while (fread(&e, resize, 1, fp) == 1)
                {
                    if (strcmp(e.name, empname) == 0)
                    {
                        remove("EMP.DAT");
                        
                    }
                    else{
                            fwrite(&e, resize, 1, ft);
                    }
                }
                fclose(fp);
                fclose(ft);
                
                rename("Temp.dat", "EMP.DAT");
                fp = fopen("EMP.DAT", "rb+");
                printf("Delete another record(y/n)");
                fflush(stdin);
                another = getche();
            }
            break;
        case '5':
            fclose(fp);
            exit(0);
        }
    }
    return 0;
}