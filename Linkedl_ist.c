#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StructsandNodes.h"


LLNode * createLLNode(FILE *file)			//  Create a Linked List node, and return a pointer to this new node
{	
	int ID;
	char firstName[25];
	char lastName[35];
	LLNode *newNode = NULL;

	if(fscanf(file, "%d", &ID) != EOF)					//Reading in ID from file
	{
		fscanf(file, "%s", &firstName);
		fscanf(file, "%s", &lastName);

		newNode = malloc(sizeof(LLNode));	//Memory allocation to create a node
		if(newNode == NULL){						//Check memory allocation
			printf("Error memory allocation\n");
			exit(1);
		}

		(newNode->pInfo).ID = ID;							//Initialize the Passenger struct
		strcpy( (newNode->pInfo).firstName ,  firstName );
		strcpy( (newNode->pInfo).lastName , lastName );	

		newNode->Next = NULL;								//Set the Next pointer to NULL
		(newNode->pInfo).currentBal = 0.00;					//Set balance to 0;
		(newNode->pInfo).passengerLocation = 0;				//Set location to 0 since they have not boarded the ship yet
	}
	return newNode;
}

int getPassengerID(LLNode *node){				// 4.F) Take a pointer node as parameter and return the Passenger ID
	return (node->pInfo).ID;
}
char * getFName(LLNode *node){
	return (node->pInfo).firstName;
}
char * getLName(LLNode *node){
	return (node->pInfo).lastName;
}
double getCurrBal(LLNode *node){
	return (node->pInfo).currentBal;
}
int getLocation(LLNode *node){
	return (node->pInfo).passengerLocation;
}
void setLocation(LLNode *node, int location){
	(node->pInfo).passengerLocation = location;
}

void addToCurrentBal(LLNode *node, double amount){
	(node->pInfo).currentBal = ( (node->pInfo).currentBal ) + amount;
}
LLNode * searchID(LLNode *head, int ID)			// 4.G) Search ID return the target Node pointer. Not found return NULL pointer
{
	LLNode *curr = head;
	while( ((curr->Next) != NULL) && (getPassengerID(curr->Next) != ID) ) //continue until Next is NULL OR Target
	{
		curr = curr->Next;
	}
	return curr->Next;			//return target or NULL
}	

void insert(LLNode *head, LLNode *newNode)		// 4.H) Insert new node to the list
{
	LLNode *curr = head;						//continue until Next is NULL OR newID less than NextID
	while( (curr->Next != NULL) && (getPassengerID(newNode) > getPassengerID(curr->Next) ) )
		curr = curr->Next;	
	newNode->Next = curr->Next;		//Change new Node first
	curr->Next = newNode;			//Then change current
}

LLNode * deleteNode(LLNode *head, int ID)			//4.I) Remove a node. Retrun pointer to the removed node. Not found return NULL
{
	LLNode *curr = head;
	while(curr->Next != NULL && getPassengerID(curr->Next) != ID) //continue until Next is NULL OR Target
		curr = curr->Next;
	LLNode *deletedNode = curr->Next;				//Need this to return deleted node;
	if(curr->Next != NULL)
		curr->Next = curr->Next->Next;		//Bypass
	return deletedNode;								//This will return removed node or NULL if not found
}
