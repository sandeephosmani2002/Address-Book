/*
NAME = SANDEEP HOSMANI
DATE = 10/10/25
DESCRIPTION = "ADDRESSBOOK"
              This program is about an address book system project. 
	      It can create contacts with validated Name, Phone, and Email. 
	      It can list all contacts sorted by name, phone or email. 
	      It can search contacts by any field. It can edit selected contact details. 
	      It can delete contacts which are selected. Save all changes to a file before exit. 
	      The program is implemented using strings, pointers, functions, structures, files and basics of C.
*/




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"



// ======================================================================
//  Function: listContacts()
//  Purpose: Displays all stored contacts in a formatted table.
// ======================================================================

void listContacts(struct AddressBook *addressBook) 
{

        // Loop through all saved contacts and print each record
	printf("+--------------------+--------------------+------------------------------+------------------------------+\n");

	printf("|%-20s|%-20s|%-30s|%-30s|\n","S.NO","NAME","PHONE","EMAIL");
	for(int i=0;i<addressBook->contactCount;i++)
	{
		printf("+--------------------+--------------------+------------------------------+------------------------------+\n");
		printf("|%-20d|%-20s|%-30s|%-30s|\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
	}

	printf("+--------------------+--------------------+------------------------------+------------------------------+\n");
}


// =========================================================================
// Function: initialize
// Purpose: Initialize the address book and load existing contacts from file
// =========================================================================

void initialize(struct AddressBook *addressBook)
{
	addressBook->contactCount = 0; // Start with zero contacts
	//populateAddressBook(addressBook);

	loadContactsFromFile(addressBook);// Load saved contacts
}

void saveAndExit(struct AddressBook *addressBook) {
	saveContactsToFile(addressBook); // Save contacts to file
	exit(EXIT_SUCCESS); // Exit the program
}


// =========================================================================
// Function: createContact
// Purpose: Add a new contact with proper validation and duplication checks
// =========================================================================

void createContact(struct AddressBook *addressBook)
{


	printf("Enter the name : ");
	scanf(" %[^\n]",addressBook->contacts[addressBook->contactCount].name);
	int j;
	char arr[30];


	do // Validate phone number
	{
		j = 0;
		int flag = 1;
		int valid = contactValidation(arr);
		if(valid == 1)  // Check if number already exists or not 
		{
			int val;
			for(int i = 0;i < addressBook->contactCount;i++)
			{
				val = (strcmp(addressBook->contacts[i].phone,arr));



				if(val == 0)
				{
					printf("The number is already exists:\n");
					flag = 0;
					j = 1;
					break;
				}
			}

		}
		if(flag == 1) // if contact is not present than save in structure
		{
			strcpy(addressBook->contacts[addressBook->contactCount].phone,arr);
			j = 0;
		}


        // Validate and add email 

	}while(j);


	int retry;
	char arr1[30];
	do
	{
		retry = 0;
		int flag = 1;
		int Evalid = emailValidation(arr1); // Validate email format
		if(Evalid == 1)
		{
			int val1;
			for(int k = 0;k < addressBook->contactCount;k++)
			{
				val1 = (strcmp(addressBook->contacts[k].email,arr1));



				if(val1 == 0)
				{
					printf("The email is already exists:\n");
					flag = 0;
					retry = 1;
					break;
				}
			}

		}
		else
		{
			retry = 1;
		}
		if(flag == 1)  // if email is not present the add to the structure
		{   
			strcpy(addressBook->contacts[addressBook->contactCount].email,arr1);

		}





	}while(retry);
	(addressBook->contactCount)++; // Increment contact count




}



// ======================================================================
// Function: searchContact
// Purpose: Search a contact by name, phone, or email using menu options
// ======================================================================

void searchContact(struct AddressBook *addressBook) 
{
	
	int index[addressBook->contactCount];
	int choice;
	do
	{

		printf("\nSearch Menu:\n");
		printf("1. Search By Name\n");
		printf("2. Search By Mobile\n");
		printf("3. Seatch By Email\n");
  		printf("4. Exit\n");
		printf("Enter the choice:");


		scanf("%d", &choice);

		switch (choice)
		{
			case 1:
				SearchName(addressBook);  // searching function for name 
				break;
			case 2:
				SearchMobile(addressBook,index); // searching function for mobile number
				break;
			case 3:
				SearchEmail(addressBook,index);  // searching function for email 
				break;
			case 4:
				break;

			default:
				printf("Invalid choice. Please try again.\n");
		}
	} while (choice != 4 ); 
}

// ======================================================================
// Function: editContact()
// Purpose: Edit existing contact details (name, phone, or email).
// ======================================================================

void editContact(struct AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
       
	int index[addressBook->contactCount];

        int Editchoice;
        do
        {

                printf("\nEdit Menu:\n");
                printf("1. Edit By Name\n");
                printf("2. Edit By Mobile\n");
                printf("3. Edit By Email\n");
                printf("4. Exit\n");
                printf("Enter the choice:");

                scanf("%d", &Editchoice);
		int matchCount = 0;

                switch(Editchoice)
                {
                         case 1:
                                matchCount = SearchNameEdit(addressBook,index);  // searching function for name and returning  the index count array
                                break;
				
                        case 2:
                                matchCount = SearchMobile(addressBook,index);// searching function for mobile number and returning  the index count array
                                break;
                        case 3:
                                matchCount = SearchEmail(addressBook,index);// searching function for email and returning  the index count array
                                break;
                        case 4:

                                return;
                        default:
                                printf("Invalid choice. Please try again.\n");
				break;

                }
		if(matchCount > 0)
		{
			int choice;
			printf("Enter the S.NO of the contact you to edit: ");
			scanf("%d",&choice);


			int foundIndex = -1;
			for(int i = 0; i < matchCount;i++)
			{
				if(index[i] == (choice-1))
				{
					foundIndex = index[i];
					break;
				}
			}

			if(foundIndex == -1)
			{
				printf("Invalid S.No selection.\n");
				continue;
			}

			int fieldChoice;
			printf("\nWhich field do you want to edit\n");
			printf("1. Name\n2. Phone\n3. Email\n");
			scanf("%d",&fieldChoice);


			switch(fieldChoice)
			{
				case 1:
					printf("Enter new name: ");
					scanf(" %[^\n]",addressBook->contacts[foundIndex].name);
					break;
				case 2:{
				       int i = 1;
				       while(i)
				       {
					char str[20];
				        printf("Enter new Phone number: ");
					scanf(" %[^\n]",str);
				        if(contactValidationEdit(str))
					{
						strcpy(addressBook->contacts[foundIndex].phone,str);
						i = 0;
					}
					else
					{
						printf("Invalid phone number: ");
					}
				       }
				        break;
				       }
				case 3:
				       {
					int i = 1;
					while(i)
					{
				         char str[20];
				        printf("Enter new email number: ");
					scanf(" %[^\n]",str);
					if(emailValidationEdit(str))
					{
					  i = 0;
					  strcpy(addressBook->contacts[foundIndex].email,str);

					}
					else
					{
						printf("Invalid email\n ");
						i = 1;
					}
					}
				        break;
				       }
				default:
				        printf("Invalid field choice.\n");
			}
		        printf("Contact updated successfully!\n");
		}	




        } while (Editchoice != 4);


}

// ======================================================================
// Function: deleteContact
// Purpose: Delete a contact by name, phone, or email
// Logic: Search → Confirm → Shift remaining contacts → Decrement count
// ======================================================================

void deleteContact(struct AddressBook *addressBook)
{
    int doption;

    do
    {
        printf("\nDELETE MENU:\n");
        printf("1. Delete by Name\n");
        printf("2. Delete by Phone\n");
        printf("3. Delete by Email\n");
        printf("4. Exit Delete Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &doption);

        int index[addressBook->contactCount];
        int matchCount = 0;

        switch (doption)
        {
            case 1:
                matchCount = SearchNameEdit(addressBook, index);
                break;
            case 2:
                matchCount = SearchMobile(addressBook, index);
                break;
            case 3:
                matchCount = SearchEmail(addressBook, index);
                break;
            case 4:
                printf("Exiting delete menu...\n");
                return;
            default:
                printf("Invalid choice!\n");
                continue;
        }

        if (matchCount > 0)
        {
            int choice;
            printf("Enter the S.NO of the contact you want to delete: ");
            scanf("%d", &choice);

            int foundIndex = -1;
            for (int i = 0; i < matchCount; i++)
            {
                if (index[i] == (choice - 1))
                {
                    foundIndex = index[i];
                    break;
                }
            }

            if (foundIndex == -1)
            {
                printf("Invalid selection.\n");
                continue;
            }

            int confirm;
            printf("Are you sure you want to delete this contact? (1 = Yes / 0 = No): ");
            scanf("%d", &confirm);

            if (confirm == 1) // Shift contacts to fill deleted position
            {
                for (int i = foundIndex; i < addressBook->contactCount - 1; i++)
                {
                    addressBook->contacts[i] = addressBook->contacts[i + 1];
                }
                addressBook->contactCount--;

                printf("Contact deleted successfully.\n");
            }
            else
            {
                printf("Deletion cancelled.\n");
            }
        }
    } while (doption != 4);
}


// ======================================================================
// Function: contactValidation()
// Purpose: Validates phone number (must be 10 digits, numeric only).
// ======================================================================

int contactValidation(char arr[])
{

	int j;
	do
	{
		j = 0;
		int flag = 1;
		printf("Enter the Mobile Number:");
		scanf(" %[^\n]",arr);
		int len = strlen(arr);
		if(len != 10)
		{
			flag = 0;
			j = 1;
		}
		for(int k = 0;k < 10;k++)
		{
			if(!(arr[k] >= '0' && arr[k] <= '9'))
			{
				flag = 0;
				j = 1;
				break;
			}
		}

		if(flag == 0)
		{
			printf("Invalid Mobile Number\n");

		}
		else
		{
			return 1;
		}

	}while(j);
	return 0;

}


// ======================================================================
// Function: emailValidation()
// Purpose: Validates email format (basic structure with @ and .com).
// ======================================================================

int emailValidation(char arr1[])
{
    while (1)
    {
        printf("Enter The Email: ");
        scanf(" %[^\n]", arr1);

        int lenEm = strlen(arr1);
        int atPos = -1;
        int hasLower = 0;
        int invalidChar = 0;
        
        // Validate structure of email
	
        for (int j = 0; j < lenEm; j++)
        {
            if (arr1[j] >= 'a' && arr1[j] <= 'z')
            {
                hasLower = 1;
            }
            else if (arr1[j] >= '0' && arr1[j] <= '9')
            {
                invalidChar = 1; 
                break;
            }
            else if (arr1[j] == '@')
            {
                if (atPos == -1) 
                    atPos = j;
                else
                {
                    invalidChar = 1; 
                    break;
                }
            }
            else if (!(arr1[j] == '.' || arr1[j] == '_'))
            {
                invalidChar = 1; 
                break;
            }
        }

  
        int endsWithCom = (lenEm > 4 && strcmp(arr1 + lenEm - 4, ".com") == 0);

        if (hasLower && atPos >= 3 && !invalidChar && endsWithCom)
        {
            return 1; 
        }
        else
        {
            printf("Invalid Email!\n");
        }
    }
}
 
// ========================================================================
// Function: SearchName()
// Purpose: searching the name and printing the name related information
// ========================================================================

void SearchName(struct AddressBook *addressBook)
{
    char str[50];
    printf("Enter the Name: ");
    scanf(" %[^\n]", str);

    int found = 0;   // flag to check if any match found
    int headerPrinted = 0;

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        char *value = strcasestr(addressBook->contacts[i].name, str); // case-insensitive match

        if (value != NULL)
        {
            if (!headerPrinted)
            {
                printf("+--------------------+--------------------+------------------------------+------------------------------+\n");
                printf("|%-20s|%-20s|%-30s|%-30s|\n", "S.NO", "NAME", "PHONE", "EMAIL");
                headerPrinted = 1;
            }

            printf("+--------------------+--------------------+------------------------------+------------------------------+\n");
            printf("|%-20d|%-20s|%-30s|%-30s|\n",
                   i + 1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);

            found = 1;
        }
    }

    if (found)
    {
        printf("+--------------------+--------------------+------------------------------+------------------------------+\n");
    }
    else
    {
        printf("Name Not Found\n");
    }
}

// =============================================================================
// Function: SearchMobile()
// Purpose: searching the phone number and printing the name related information
// =============================================================================

int SearchMobile(struct AddressBook *addressBook,int* index)
{
	char str1[20];
	printf("Enter the Mobile:");
	scanf(" %[^\n]",str1);
	int flag = 0;
	int j;
	int k = 0;
	for(j = 0;j < addressBook->contactCount;j++)
	{
		int value1 = strcmp(addressBook->contacts[j].phone,str1);
		if(value1 == 0)
		{
			flag = 1;
			index[k] = j;
			k++;
			break;

		}
	}
	if(flag == 1)
	{

		printf("+--------------------+--------------------+------------------------------+------------------------------+\n");
		printf("|%-20s|%-20s|%-30s|%-30s|\n","S.NO","NAME","PHONE","EMAIL");

		printf("+--------------------+--------------------+------------------------------+------------------------------+\n");
		printf("|%-20d|%-20s|%-30s|%-30s|\n",j+1,addressBook->contacts[j].name,addressBook->contacts[j].phone,addressBook->contacts[j].email);
		printf("+--------------------+--------------------+------------------------------+------------------------------+\n");
	}
	else
	{
		printf("Mobile Number Not Found\n");
	}
	return k;

}

// ========================================================================
// Function: SearchEmail()
// Purpose: searching the email and printing the name related information
// ========================================================================


int  SearchEmail(struct AddressBook *addressBook,int* index)
{
	char ptr[20];
	printf("Enter the Email:");
	scanf(" %[^\n]",ptr);
	int flag = 0;
	int j;
	int k = 0;
	for(j = 0;j < addressBook->contactCount;j++)
	{
		int value2 = strcmp(addressBook->contacts[j].email,ptr);
		if(value2 == 0)
		{
			flag = 1;
			index[k] = j;
			k++;
			break;

		}
	}
	if(flag == 1)
	{  

		printf("+--------------------+--------------------+------------------------------+------------------------------+\n");
		printf("|%-20s|%-20s|%-30s|%-30s|\n","S.NO","NAME","PHONE","EMAIL");

		printf("+--------------------+--------------------+------------------------------+------------------------------+\n");
		printf("|%-20d|%-20s|%-30s|%-30s|\n",j+1,addressBook->contacts[j].name,addressBook->contacts[j].phone,addressBook->contacts[j].email);
		printf("+--------------------+--------------------+------------------------------+------------------------------+\n");
	}
	else
	{
		printf("Email Not Found\n");
	}
	return k;


}
// =========================================================================================================
// Function: SearchNameEdit()
// Purpose: searching the name and printing the name related information and also returning the index address
// =========================================================================================================

int SearchNameEdit(struct AddressBook *addressBook, int *index)
{
    char str[20];
    printf("Enter the Name: ");
    scanf(" %[^\n]", str);

    int found = 0;          // To track if any match is found
    int j = 0;              // To store matching indices
    int headerPrinted = 0;  // To control header printing

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcasestr(addressBook->contacts[i].name, str) != NULL) // case-insensitive compare
        {
            // Print header only once
            if (!headerPrinted)
            {
                printf("+--------------------+--------------------+------------------------------+------------------------------+\n");
                printf("|%-20s|%-20s|%-30s|%-30s|\n", "S.NO", "NAME", "PHONE", "EMAIL");
                headerPrinted = 1;
            }

            printf("+--------------------+--------------------+------------------------------+------------------------------+\n");
            printf("|%-20d|%-20s|%-30s|%-30s|\n",
                   i + 1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);

            index[j++] = i;  // Save the index of this match
            found = 1;
        }
    }

    if (headerPrinted)
        printf("+--------------------+--------------------+------------------------------+------------------------------+\n");

    if (!found)
        printf("Name Not Found\n");

    return j;  // Return number of matches found
}

int contactValidationEdit(char arr[])
{

        int j;
        do
        {
                j=0;
                int flag = 1;
                //printf("Enter the New Number:");
                //scanf(" %[^\n]",arr);
                int len = strlen(arr);
                if(len != 10)
                {
                        flag = 0;
                        j=1;
                }
                for(int k = 0;k < 10;k++)
                {
                        if(!(arr[k] >= '0' && arr[k] <= '9'))
                        {
                                flag = 0;
                                j = 1;
                                break;
                        }
                }

                if(flag == 0)
                {
                        printf("Invalid Mobile Number\n");

                }
                else
                {
                        return 1;
                }

        }while(j);
	return 0;

}

int emailValidationEdit(char arr1[])
{
       // printf("Enter The New Email: ");
       // scanf(" %[^\n]", arr1);

        int lenEm = strlen(arr1);
        int atPos = -1;
        int hasLower = 0;
        int invalidChar = 0;

        // Validate structure of email

        for (int j = 0; j < lenEm; j++)
        {
            if (arr1[j] >= 'a' && arr1[j] <= 'z')
            {
                hasLower = 1;
            }
            else if (arr1[j] >= '0' && arr1[j] <= '9')
            {
                invalidChar = 1;
                break;
            }
            else if (arr1[j] == '@')
            {
                if (atPos == -1)
                    atPos = j;
                else
                {
                    invalidChar = 1;
                    break;
                }
            }
            else if (!(arr1[j] == '.' || arr1[j] == '_'))
            {
                invalidChar = 1;
                break;
            }
        }


        int endsWithCom = (lenEm > 4 && strcmp(arr1 + lenEm - 4, ".com") == 0);

        if (hasLower && atPos >= 3 && !invalidChar && endsWithCom)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    
}

