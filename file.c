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
#include "file.h"
#include"contact.h"
#include<stdlib.h>

void saveContactsToFile(struct AddressBook *addressBook)
{

    FILE* fb = fopen("contact.csv","w");
    fprintf(fb,"#%d\n",addressBook->contactCount);
    for(int i=0;i<addressBook->contactCount;i++)
    {
	    fprintf(fb,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fb);
  
}

void loadContactsFromFile(struct AddressBook *addressBook)
{

    FILE* fb = fopen("contact.csv","r");
    fscanf(fb,"#%d\n",&addressBook->contactCount);
    for(int i=0;i<addressBook->contactCount;i++)
    {
            fscanf(fb,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fb);

    
}
