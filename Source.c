#pragma warning(disable:4996)


#include <stdio.h>
#include <stdlib.h>

struct Date {
    int dd;
    int mm;
    int yy;
};
struct Date date;

struct Remainder {
    int dd;
    int mm;
    char note[50];
};
struct Remainder R;

void gotoxy(int x, int y)//This function allows you to print text in any place of screen.//
{
   
}



//Alogrithm for calculating the first day of the week

int get_1st_weekday(int year) {

    int d;
    d = (((year - 1) * 365) + ((year - 1) / 4) - ((year - 1) / 100) + ((year) / 400) + 1) % 7;
    return d;
}



// ---------Main Function for the calendar---------
int main()
{
    system("Color 2F");
    int year, month, day, daysInMonth, weekDay = 0, startingDay;
    char ch = 'a';
    printf("\nEnter the year:");
    scanf_s("%d", &year);

    char* months[] = { "January","February","March","April","May","June","July","August","September","October","November","December" };
    int monthDay[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };



    //---------Checking the Leap Year---------
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        monthDay[1] = 29;

    startingDay = get_1st_weekday(year);

    for (month = 0; month < 12; month++) {

        daysInMonth = monthDay[month];
        printf("\n\n---------------%s-------------------\n", months[month]);
        printf("\n  Sun  Mon  Tue  Wed  Thurs  Fri  Sat\n");


   //This line will print spaces after the day where month ends
        for (weekDay = 0; weekDay < startingDay; weekDay++)
            printf("     ");

        for (day = 1; day <= daysInMonth; day++) {
            printf("%5d", day);

            if (++weekDay > 6) {
                printf("\n");
                weekDay = 0;
            }
            startingDay = weekDay;
        }


    }


    //This is to add notes in the calendar

    //------This function will create a file and ask user to add the event which user want to save---------
    void making_Note(); {
        FILE* fp;
        fp = fopen("my_notes", "ab+");
        system("cls");
        gotoxy(5, 7);
        printf("Enter the date you wish to enter Notes for(DD MM): ");
        scanf_s("%d%d", &R.dd, &R.mm);
        gotoxy(5, 8);
        printf("Enter your Note(Only 50 Characters): ");
        fflush(stdin);
        scanf("%[^\n]", R.note);

        if (fwrite(&R, sizeof(R), 1, fp)) {
            gotoxy(5, 12);
            puts("Your note has been saved");
            fclose(fp);
        }
        else {
            gotoxy(5, 12);
            puts("\aPlease try to save again notes!!\a");
        }
        gotoxy(5, 15);
        printf("Press Any Key to return");
        getch();
        fclose(fp);
        
    }
    



    //----------------This is to show the all saved notes in the calendar-----------------------------

   void showing_notes(int mm);
    {
        FILE* fp;
        int i = 0, fileisFound = 0;
        system("cls");
        fp = fopen("my_notes", "rb");
        if (fp == NULL) {
            printf("Error in Opening the File");
        }
        while (fread(&R, sizeof(R), 1, fp) == 1) {
            if (R.mm == monthDay) {
                gotoxy(10, 5 + i);
                printf("Note %d Day = %d: %s", i + 1, R.dd, R.note);
                fileisFound = 1;
                i++;
            }
        }
        if (fileisFound == 0) {
            gotoxy(10, 5);
            printf("You do not have any saved notes for this month");
        }
        gotoxy(10, 7 + i);
        printf("Please press any button to go back to main page");
        getch();


    }

   
}