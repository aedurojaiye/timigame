#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/********************************************************
*OLUWATIMILEHIN AKOGUN                                  *
*Title:                                                 *
*Date:                                                  *
*Github: functionOfFunction                             *
*Email: akoguntimi@gmail.com                            *
*License: Creative Commons Zero (CC0)                   *
*********************************************************/

struct node{
    int number;
    struct node* next;
} node;

int insert_in(int number, struct node** head);
void tranverse(struct node* head);


int main(int argc, char const *argv[])
{
    //declaration of the linked list
    struct node* head =  NULL;
    int operation = 0;

    do {
        printf("Enter an operation number\n");
        scanf("%d", &operation );
        switch (operation)
         {
            case 0:
                    printf("Exiting\n");
                    break;
            case 1: printf("Insert an Interger please\n");
                    int number;
                    scanf("%d", &number);
                    insert_in(number, &head);
                    break;
            case 2: printf("The list contains:\n");
                    tranverse(head);
                    break;

            default: printf("You have selected an invalid operation\n");


        }
    } while(operation != 0);
}

void tranverse(struct node* head)
{
    if (head == NULL)
    {
        return;
    }
    printf("%d\n",head->number);
    tranverse(head->next);
}

int insert_in(int number, struct node** head)
{

    if (*head == NULL) {
        struct node* temp = malloc(sizeof(struct node));
        if (temp == NULL)
        {
            return 1;
        }
        temp->number= number;
        temp->next= NULL;
        *head = temp;
        return 0;

    }
    struct node** next = &((*head)->next);
    return insert_in(number, next);
}
