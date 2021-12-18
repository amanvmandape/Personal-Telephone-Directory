// Your Personal Telephone Directory
// Creator: Armaan Mandape
// Dated: 19-dec-2021
// Time Required: 4:19 hrs
// Merry Christmas to all who are reading this

#include <stdio.h>
#include <strings.h>
#include <ctype.h>
#include<stdlib.h>


//Function Declarations
add_contact();
search_contact();
list_contacts();
admin_panel();
greet();
change_master();

//Variables
struct contact
{
    char fname[20];
    char lname[20];
    char mobnum[10];
};

char MASTER[20];
char code[20];

main()
{
    // Variables
    int choice = 0;
    int attempt = 0;

    //Preloading Routines
    get_pass();

    // UI
    do{
        system("cls");
        greet();
        printf("\n\n\n\n\n Please Enter the Master-Code to Continue: ");
        scanf("%s",code);

        if (!strcmp(code, MASTER))
        {
            do
            {
                system("cls");
                greet();

                printf("\n\n\n\n 1 Add a Contact");
                printf("\n 2 Find a Contact");
                printf("\n 3 List all the Contacts");
                printf("\n 4 Administrator Panel");
                printf("\n 5 Exit");
                printf("\n\n\n Please make a choice(1-5): ");
                scanf("%d",&choice);

                switch(choice)
                {

                case 1:
                    add_contact();
                    break;
                case 2:
                    search_contact();
                    break;
                case 3:
                    list_contacts();
                    break;
                case 4:
                    admin_panel();
                    break;
                case 5:
                    exit(1);
                default:
                    printf("\n Invalid Option... Kindly enter correct option... ");
                    system("pause");
                }
            }
            while(1);

        }
        else
        {
            attempt++;
            system("cls");
            printf("\n\n Incorrect Master-Code... ");
            system("pause");
        }
    }
    while(attempt<3);
}

add_contact()
{
    FILE *db;
    db = fopen("data", "a");
    struct contact new_contact;
    char choice;

    // Handling Opening Error
    if(db==NULL)
    {
        printf("\n Database Not Found");
        system("pause");
        exit(1);
    }

    // UI
    system("cls");
    greet();
    printf("\n\n\n\t\t\t******************************Add New Contacts*******************************");

    // Creating New Contact
    printf("\n\n\n Enter the First Name: ");
    scanf("%s", &new_contact.fname);
    printf(" Enter the Last Name: ");
    scanf("%s", &new_contact.lname);
    printf(" Enter the Mobile Number: ");
    scanf("%s", &new_contact.mobnum);

    printf("\n First Name: %s", new_contact.fname);
    printf("\n Last Name: %s", new_contact.lname);
    printf("\n Mobile Number: %s", new_contact.mobnum);

    printf("\n\n Is it Correct? (y/n): ");
    fflush(stdin);
    choice=getchar();

    if(toupper(choice)=='Y')
    {
        fwrite(&new_contact, sizeof(struct contact), 1, db);
        printf("\n Contact Added Successfully... ");
    }
    else
    {
        printf("\n Contact not added... ");
    }
    system("pause");

    // Handling Closing Errors
    if(fclose(db))
    {
        printf("Error Closing Database");
        system("pause");
    }
}

search_contact()
{
    FILE *db;
    struct contact search_contact;
    struct contact db_contact;
    int flag = 1;
    int condition1, condition2;


    db = fopen("data", "r");
    // Handling Opening Error
    if(db==NULL)
    {
        printf("\n Database Not Found");
        system("pause");
        exit(1);
    }

    // UI
    system("cls");
    greet();
    printf("\n\n\n\t\t\t******************************Search Contacts*******************************");

    // Creating New Contact
    printf("\n\n\n Enter the First Name of the contact: ");
    scanf("%s", &search_contact.fname);
    printf(" Enter the Last Name of the contact: ");
    scanf("%s", &search_contact.lname);


    while(fread(&db_contact, sizeof(struct contact), 1, db))
    {
        if(!strcmp(db_contact.fname, search_contact.fname)&&!strcmp(db_contact.lname, search_contact.lname))
        {
            printf("\n First Name: %s", db_contact.fname);
            printf("\n Last Name: %s", db_contact.lname);
            printf("\n Mobile Number: %s", db_contact.mobnum);
            flag = 0;
        }
    }

    if(flag)
    {
        printf("Contact not Found...");
    }
    printf("\n\n ");
    system("pause");

    // Handling Closing Errors
    if(fclose(db))
    {
        printf("Error Closing Database");
        system("pause");
    }
}

list_contacts()
{
    FILE *db;
    db = fopen("data", "r");
    struct contact current_contact;

    // Handling Opening Error
    if(db==NULL)
    {
        printf("\n Database Not Found");
        system("pause");
        exit(1);
    }

    // UI
    system("cls");
    greet();
    printf("\n\n\n\t\t\t******************************Contacts List*******************************\n\n");

    while(fread(&current_contact, sizeof(struct contact), 1, db))
    {
        printf("\n\t\t Name: %s\t\tSurname: %s\t\tContact Number: %s",current_contact.fname, current_contact.lname, current_contact.mobnum);
    }
    printf("\n\n ");
    system("pause");

    if(fclose(db))
    {
        printf("Error Closing Database");
        system("pause");
    }
}

admin_panel()
{
    int choice;


    system("cls");
    greet();
    printf("\n\n\n\t\t\t******************************Admin Panel*******************************");
    printf("\n\n\n\n\n Please Enter the Master-Code to Continue: ");
   scanf("%s",code);

    if (!strcmp(code, MASTER))
    {
        system("cls");
        greet();
        printf("\n\n\n\t\t\t******************************Administrator Panel*******************************");
        printf("\n\n\n 1 Change Master-Password");
        printf("\n 2 Clear Database");
        printf("\n 3 Export Contacts");
        printf("\n 4 Exit Administrator Panel");
        printf("\n\n\n Please make a choice(1-4): ");
        fflush(stdin);
        scanf("%d",&choice);

        switch(choice)
        {

        case 1:
            change_master();
            break;
        case 2:
            clear_db();
            break;
        case 3:

            break;
        case 4:
            break;
        default:
            printf("\n Invalid Option... ");
            system("pause");
        }

    }

    else
    {
        system("cls");
        printf("\n\n Incorrect Master-Code... Access Denied... Program is Closing... ");
        system("pause");
        exit(1);
    }

}


greet()
{
    printf("   ******************************************************************************************************************");
    printf("\n\n\t \t \t \t\tWELCOME TO YOUR PERSONAL TELEPHONE DIRECTORY");
    printf("\n\n   ******************************************************************************************************************");
}


change_master()
{
    FILE *fpass;

    system("cls");
    greet();
    printf("\n\n\n\t\t\t******************************Change Master Code*******************************");
    printf("\n\n\n Please Enter the Master-Code to Continue: ");
    scanf("%s",code);

    if (!strcmp(code, MASTER))
    {

        fpass=fopen("pass", "w");

        printf("\n\n Enter a New Password: ");
        scanf("%s", MASTER);

        fwrite(MASTER, sizeof(MASTER), 1, fpass);

        fclose(fpass);

        printf("\n Password Successfully Changed... ");
        system("pause");
    }

    else
    {
        system("cls");
        printf("\n\n Incorrect Master-Code... Access Denied... Program is Closing... ");
        system("pause");
        exit(1);
    }


}

clear_db()
{
    FILE *db;

    system("cls");
    greet();
    printf("\n\n\n\t\t\t******************************Clear Database*******************************");
    printf("\n\n\n Please Enter the Master-Code to Clear Database: ");
    scanf("%s",code);

    if (!strcmp(code, MASTER))
    {
        db = fopen("data", "w");
        system("cls");
        greet();
        printf("\n\n\n\t\t\t******************************Clear Database*******************************");
        printf("\n\n\n Your Database has been Cleared Successfully... ");
        system("pause");
    }
    else
    {
        system("cls");
        printf("\n\n Incorrect Master-Code... Access Denied... Program is Closing... ");
        system("pause");
        exit(1);
    }

}

get_pass()
{
    FILE *fpass;

    fpass=fopen("pass", "r");

    fread(MASTER, sizeof(MASTER), 1, fpass);

    fclose(fpass);
}
