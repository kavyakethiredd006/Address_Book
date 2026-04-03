#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "contact.h"

void initialize(AddressBook *addressbook)
{
    addressbook->contactCount = 0;

    FILE *fr = fopen("contacts.txt", "r");
    if (fr == NULL)
    {
        printf("File not found\n");
        return;
    }
    printf("File found Successfully\n");

    int i = 0;
    while (1)
    {
    if (fscanf(fr, " %[^,] , %[^,] , %[^\n]",
               addressbook->contacts[i].name,
               addressbook->contacts[i].phone,
               addressbook->contacts[i].email) != 3)
    {
        break;  
    }

    addressbook->contactCount++;
    i++;
}
    fclose(fr);
}

void listContacts(AddressBook *addressbook)
{
    
    printf("  No      Name          Mobile         Email              \n");
    printf("----------------------------------------------------------\n");
   
    for (int i = 0; i < addressbook->contactCount; i++)
    {
        printf("%-2d  %-15s  %-12s  %-20s \n",i+1,
               addressbook->contacts[i].name,
               addressbook->contacts[i].phone,
               addressbook->contacts[i].email);
    }
}

void createContact(AddressBook *addressbook)
{
    if (addressbook->contactCount >= MAX_CONTACTS)
    {
        printf("Address book is full\n");
        return;
    }
    char temp_name[30];
    int name_chances = 0;

    while(name_chances < 3)
    {
        printf("Enter your name: ");
        scanf(" %[^\n]",temp_name);
        int flag = 1;
        if(temp_name[0] == ' ')
        {
            printf("Invalid Input...Try again");
            continue;
        }
    for(int i = 0;temp_name[i] != '\0';i++)
    {
        flag  = 1;
        if(!((temp_name[i] >= 'A' && temp_name[i] <= 'Z')||
        (temp_name[i] >= 'a' && temp_name[i] <= 'z')|| temp_name[i] == ' '))
        {
            flag = 0;
            break;
        }
        if(temp_name[i] == ' ' && temp_name[i + 1] == ' ')
        {
            flag = 0;
            break;
        }
    }
    if(flag == 1)
    {
        break;
    }
    else
    {
    printf("Invalid Input.... Try Again");
    name_chances++;
    }

}
if(name_chances == 3)
{
    return;
}
   char temp_phone[15];
   int phone_chances = 0;
   while(phone_chances < 3)
   {
    printf("Enter your number: ");
    getchar();
    scanf("%s",temp_phone);
    int flag = 1;
    if(strlen(temp_phone) != 10)
    {
        printf("Invalid Input... Try again");
        continue;
    }
    for(int i = 0;temp_phone[i] != '\0';i++)
    {
        flag = 1;
        if(!(temp_phone[i] >= '0' && temp_phone[i] <= '9'))
        {
            flag  = 0;
            break;
        }
    }
    if(flag == 1)
    {
        break;
    }
    else
    {
    printf("Invalid Input... Try again");
     phone_chances++;
    }

   }
   if(phone_chances == 3)
   {
    return;
   }

   char temp_email[30];
   int mail_chances = 0;
    while(mail_chances < 3)
    {
        printf("Enter your email: ");
        getchar();
        scanf("%[^\n]",temp_email);
        int flag = 1;
        for(int i = 0;temp_email[i] != '\0';i++)
        {
            flag  = 1;
            if(!((temp_email[i] >= 'a' && temp_email[i] <= 'z') ||
                  temp_email[i] == '@' || temp_email[i] == '.'))
            {
                flag = 0;
                break;
            }
        }
        if(strstr(temp_email,".com") == NULL)
        {
            flag = 0;
        }
        if(flag == 1)
        {
            break;
        }
        else
        {
        printf("Invalid Input... Try again");
        mail_chances++;
        }
   
    }
    if(mail_chances == 3)
    {
        return;
    }

    strcpy(addressbook->contacts[addressbook->contactCount].name, temp_name);
    strcpy(addressbook->contacts[addressbook->contactCount].phone, temp_phone);
    strcpy(addressbook->contacts[addressbook->contactCount].email, temp_email);

    addressbook->contactCount++;

    printf("Contact Saved...");

    
}

void searchContact(AddressBook *addressBook) 
{
    int option;
    int flag=0;
    int match=0;
    char name[50], phone[20], email[100];
    printf("1. search by name \n2. search by ph no\n3.search by email id\n");
    printf("Enter the option : ");
    scanf("%d",&option);
    getchar();
    switch(option)
    {

    case 1 :
    {
    printf("Enter the name : ");
    scanf("%[^\n]",name);
    for(int i = 0;i < addressBook->contactCount;i++)
    {
        if(strstr(addressBook->contacts[i].name,name))
        {
            printf("%s %s %s\n",addressBook->contacts[i].name,
                                addressBook->contacts[i].phone,
                               addressBook->contacts[i].email);
        }
    }
    break;
    }

        case 2:
        {
            printf("Enter phone number to search: ");
            scanf("%s", phone);

            for (int i = 0; i < addressBook->contactCount; i++) 
            {
                if (strstr(addressBook->contacts[i].phone,phone)) 
                {
                    printf("\nContact found:\n");
                    printf("Name : %s\n", addressBook->contacts[i].name);
                    printf("Phone: %s\n", addressBook->contacts[i].phone);
                    printf("Email: %s\n", addressBook->contacts[i].email);
                }
            }
            break;
        }

        case 3:
        {
            printf("Enter email to search: ");
            scanf("%s", email);

            for (int i = 0; i < addressBook->contactCount; i++) 
            {
                if (strstr(addressBook->contacts[i].email,email)) 
                {
                    printf("\nContact found:\n");
                    printf("Name : %s\n", addressBook->contacts[i].name);
                    printf("Phone: %s\n", addressBook->contacts[i].phone);
                    printf("Email: %s\n", addressBook->contacts[i].email);
                }
            }
            break;
        }

        default:
            printf("Invalid option. Please enter 1 or 2.\n");
    }
}


void editContact(AddressBook *addressBook)
 {
    char search_name[30];
    char phone[15];
    char email[30];
    int index = -1;

    
    for (int j = 0; j < 3; j++) 
    {
        printf("Enter name to edit: ");
        scanf(" %[^\n]", search_name);

        
        for (int i = 0; i < addressBook->contactCount; i++) 
        {
            if (strcmp(addressBook->contacts[i].name, search_name) == 0) 
            {
                index = i;
                printf("Contact found successfully:\n");
                printf("%-20s %-20s %s\n",addressBook->contacts[i].name,
                                         addressBook->contacts[i].phone,
                                         addressBook->contacts[i].email);
                break;
            }
        }

        if (index != -1)
        {
        break;  
        }
        else 
        {
        printf("Sorry, name not found. Please try again.\n");
        }
    }

    if (index == -1) 
     {
        printf("Attempts exceeded. Contact not found!\n");
        return;
     }

   
    printf("Enter new name: ");
    scanf(" %[^\n]", search_name);
    strcpy(addressBook->contacts[index].name, search_name);

    printf("Enter new phone number: ");
    scanf(" %[^\n]", phone);
    if(strlen(phone) == 10) 
     {
        strcpy(addressBook->contacts[index].phone, phone);
     }
     else 
     {
        printf("Invalid phone number. Keeping old value.\n");
     }

    printf("Enter new email: ");
    scanf(" %[^\n]", email);
    if (strstr(email, "@") && strstr(email, ".com"))
     {
        strcpy(addressBook->contacts[index].email, email);
     } 
    else 
     {
        printf("Invalid email. Keeping old value.\n");
     }

    printf("Contact details updated successfully!\n");
 }

void deleteContact(AddressBook *addressBook)
 {
    char search_name[30];
    int index = -1;

    printf("Enter name to delete: ");
    scanf(" %[^\n]", search_name);

    
    for (int i = 0; i < addressBook->contactCount; i++)
     {
        if (strcmp(addressBook->contacts[i].name, search_name) == 0)
         {
            index = i;
            break;
        }
    }

    if (index == -1) 
    {
        printf("Contact not found!\n");
        return;
    }

    
    for (int i = index; i < addressBook->contactCount - 1; i++) 
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    addressBook->contactCount--;  
    printf("Contact deleted successfully!\n");
}
void saveContactsToFile (AddressBook *addressBook)
{
    FILE *fp = fopen("contacts.txt","w");
    if(fp == NULL)
    {
        printf("sorry");
        return;
    }
    for(int i=0;i<addressBook->contactCount;i++)

    {
        fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,
                               addressBook->contacts[i].phone,
                               addressBook->contacts[i].email);
    }
    fclose(fp);

    printf("All your contacts saved to contacts.txt fill successfully....\n");
}


