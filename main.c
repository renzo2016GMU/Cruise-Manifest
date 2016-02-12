#include <stdio.h>
#include <stdlib.h>
#include "StructsandNodes.h"
#define TRUE 1
#define FALSE 0

void mainMenu();
void passengerInfoMenu();
void printMenu();
//Main Menu
void readPassengerMainfest(LLNode *headOffShip);
void moveAllPassengersFromTo(LLNode *fromThisHeadList, LLNode *toThisHeadList, int changeLocat);
//Passenger Information Menu
void moveSinglePassengerFromTo(LLNode *fromThisHeadList, LLNode *toThisHeadList, int targetLocat);
void passengerMakePurchase(LLNode *currLocationHead, LLNode *notCurrLocationHead, int pLocation);
void synchronizePassengerLists(LLNode *headOffShip, LLNode *headOnShip);
//Print Menu
void printAccountSinglePassenger(LLNode *headOffShip, LLNode *headOnShip);
void printPassengerAccounts(LLNode *head); 
void removeAllNodePrintAverage(LLNode *headOffShip, LLNode *headOnShip);

int main()
{
	LLNode *headOnShip = malloc(sizeof (LLNode) );								// 4.C) Create two Linked List Dummy head Nodes
	if(headOnShip == NULL){											//Check memory allocation
		printf("Error memory allocation\n");
		exit(1);
	}
	LLNode *headOffShip = malloc(sizeof (LLNode) );
	if(headOnShip == NULL){											//Check memory allocation
		printf("Error memory allocation\n");
		exit(1);
	}
	headOnShip->Next = NULL;												//Set the Next pointers to NULL
	headOffShip->Next = NULL;

	char notDone = TRUE;
	int mainMenuChoice = 0;
	int passInfoMenuChoice = 0;
	int printMenuChoice = 0;
	char isNotDonePIMenu = TRUE;
	char isNotDonePMenu = TRUE;

	while(notDone)
	{
		mainMenu();
		printf("Enter a choice from the Main Menu: ");				//Prompt the user for input
		scanf("%d", &mainMenuChoice);
		getchar();
		printf("\n");	
		switch(mainMenuChoice)
		{
			case 1:													//Read Passenger Mainfest
				readPassengerMainfest(headOffShip);
				break;
			case 2:													//Embark all passengers
				moveAllPassengersFromTo(headOffShip, headOnShip, 1);
				break;
			case 3:													//Passenger Information
				isNotDonePIMenu = TRUE;
				while(isNotDonePIMenu)
				{
					passengerInfoMenu();
					printf("Enter a choice from the Passenger Information Menu: ");				//Prompt the user for input
					scanf("%d", &passInfoMenuChoice);
					getchar();
					printf("\n");
					switch(passInfoMenuChoice)		
					{	
						case 1:																	//Embark single Passenger
							moveSinglePassengerFromTo(headOffShip, headOnShip, 1);
							break;
						case 2:																	//Debark single Passenger
							moveSinglePassengerFromTo(headOnShip, headOffShip, 0);
							break;
						case 3:																	//Passenger OnBoard Purchase
							passengerMakePurchase(headOnShip, headOffShip, 1);
							break;
						case 4:																	//Passenger OffBoard Purchase						
							passengerMakePurchase(headOffShip, headOnShip, 0);
							break;
						case 5:																	//Synchronize Passenger Lists
							synchronizePassengerLists(headOffShip, headOnShip);
							break;
						case 6:																	//Do nothing return to Main Menu
							isNotDonePIMenu = FALSE;
							break;					
					}
				}
				break;
			case 4:													//Print Menu
				isNotDonePMenu = TRUE;
				while(isNotDonePMenu)
				{
					printMenu();
					printf("Enter a choice from the Print Menu: ");								//Prompt ther user for input
					scanf("%d", &printMenuChoice);
					getchar();
					printf("\n");
					switch(printMenuChoice)
					{
						case 1:																	//Print Account for Single Passenger
							printAccountSinglePassenger(headOffShip, headOnShip);								
							break;
						case 2:																	//Print All Passenger Accounts
							printPassengerAccounts(headOnShip);
							printPassengerAccounts(headOffShip);
							break;
						case 3:																	//Print Accounts for onShip Passengers
							printPassengerAccounts(headOnShip);
							break;
						case 4:																	//Print Accounts for offShip Passengers
							printPassengerAccounts(headOffShip);
							break;
						case 5:																	//Do nothing return to Main Menu
							isNotDonePMenu = FALSE;
							break;
					}		
				}
				break;
			case 5:													//Debark all passengers
				moveAllPassengersFromTo(headOnShip,headOffShip, 0);	
				break;
			case 6:													//Quit
				removeAllNodePrintAverage(headOffShip, headOnShip);	//Remove and free
				notDone = FALSE;
				break;
		}
	}
	return 0;
}

void mainMenu()				//Display Main Menu
{
	int i;
	for(i = 0; i < 28; i++)
		printf("_");
	printf("\n|%-27s|\n|%-27s|\n|%-27s|\n|%-27s|\n|%-27s|\n|%-27s|\n", "1. Read Passenger Manifest", "2. Embark all passengers", 
			"3. Passenger Information", "4. Print Menu", "5. Debark all passengers", "6. Quit");
	for(i = 0; i < 28; i++)
		printf("-");
	printf("\n");
}
void passengerInfoMenu()	//Display Passenger Information Menu
{
	int i;
	for(i = 0; i < 32; i++)
		printf("_");
	printf("\n|%-31s|\n|%-31s|\n|%-31s|\n|%-31s|\n|%-31s|\n|%-31s|\n", "1. Embark Passenger", "2. Debark Passenger", 
			"3. Passenger OnBoard Purchase", "4. Passenger OffBoard Purchase", "5. Synchronize Passenger Lists", "6. Return to Main Menu");
	for(i = 0; i < 32; i++)
		printf("-");
	printf("\n");
}
void printMenu()			//Display Print Menu
{
	int i;
	for(i = 0; i < 42; i++)
		printf("_");
	printf("\n|%-41s|\n|%-41s|\n|%-41s|\n|%-41s|\n|%-41s|\n", "1. Print Account for Single Passenger", "2. Print All Passenger Accounts", 
			"3. Print Accounts for onShip Passengers", "4. Print Accounts for offShip Passengers", "5. Return to Main Menu");
	for(i = 0; i < 42; i++)
		printf("-");
	printf("\n");
}

void readPassengerMainfest(LLNode *headOffShip)
{
	char fileName[200];
	FILE *file = NULL;

	printf("Enter a file name containing the \"Passenger Manifest\": ");	//Prompt the user for filename
	fgets(fileName, sizeof fileName, stdin);		
	sscanf(fileName, "%s", fileName);	

	file = fopen(fileName, "r");											//Open file in read mode
	if(file == NULL)																//Check file opened properly
		printf("\nFile cannot be found");									//Return to Main Menu if cannot be found
	else
	{
		while(!feof(file))													//Read info from the file
		{
			LLNode *temp = createLLNode(file);								//Create passenger
			if(temp != NULL)   												//feof read one more so check NULL
				insert(headOffShip, temp);									//add them to offShip list
		}
		fclose(file);														//Close file
	}
	printf("\n");
}
void moveAllPassengersFromTo(LLNode *fromThisHeadList, LLNode *toThisHeadList, int changeLocat)	//Move all passengers from the first list to the second list
{
	int ID = 0;
	LLNode *curr = fromThisHeadList;
	LLNode *moveThis = NULL;
	while(curr->Next != NULL)
	{
		ID = getPassengerID(curr->Next);										//Get the ID
		moveThis = deleteNode(fromThisHeadList, ID);							//Move this node from first argument list
		insert(toThisHeadList, moveThis);										//To second argument list
		if(getLocation(moveThis) == changeLocat)
		{	
			if(changeLocat)														//Message stating wrong passenger location
				printf( "Passenger[%s %s] location value indicates  already on the ship,\nmust have slipped off the ship without going through security\n", getFName(moveThis), getLName(moveThis) );
			else	
				printf( "Passenger[%s %s] location vaule indicates already off the ship,\nmust have gotten on the ship without going through security\n", getFName(moveThis), getLName(moveThis) );
		}
		else
			setLocation(moveThis, changeLocat);										//Change node location to second argument list
	}
}

//Passenger Information Menu functions
void moveSinglePassengerFromTo(LLNode *fromThisHeadList, LLNode *toThisHeadList, int targetLocat)		//Passenger node is removed from the first list and added in the 
{																							//proper position to the second list
	int ID = 0;
	LLNode *moveThis = NULL;

	printf("Enter the passenger ID: ");											//Prompts for the passenger ID
	scanf("%d", &ID);
	getchar();
	printf("\n");	
	moveThis = deleteNode(fromThisHeadList, ID);								//Delete the node from first argument list (where we want to move the passenger from)
	if(moveThis == NULL)														//Not in fist list?
	{
		moveThis = searchID(toThisHeadList, ID);									//Maybe already in the second list(already moved)?
		if(moveThis == NULL)													//If passenger ID is not found in either list
			printf("Passenger ID is not found. Sorry\n");
		else																	//If found in second list
		{
			if(targetLocat)														//Already onShip
				printf("Passenger[ID: %d] already on the ship\n");
			else																//Already offShip
				printf("Passenger[ID: %d] already off the ship\n");
		}
	}
	else																		//Found it from the first list(ready to move it to second list)
	{
		insert(toThisHeadList, moveThis);										//Add passenger node in second list in the proper position 
		if(getLocation(moveThis) == targetLocat)								//If passenger Location is already the same as target Location
		{	
			if(targetLocat)														//Message stating wrong passenger location
				printf( "Passenger[%s %s] location value indicates  already on the ship,\nmust have slipped the ship without going through security\n", getFName(moveThis), getLName(moveThis) );
			else	
				printf( "Passenger[%s %s] location vaule indicates already off the ship,\nmust have gotten on the ship without going through security\n", getFName(moveThis), getLName(moveThis) );
		}
		else
			setLocation(moveThis, targetLocat);									//Change node location to second argument list
	}
}
void passengerMakePurchase(LLNode *currLocationHead, LLNode *notCurrLocationHead, int pLocation)
{
	int ID = 0;
	double amount = 0;
	LLNode *targetNode = NULL;

	printf("Enter the passenger ID: ");											//Prompts for the passenger ID
	scanf("%d", &ID);
	getchar();
	printf("\nEnter the amount of purchase: ");									//Prompts for the amount of purchase as a floating point value
	scanf("%lf", &amount);	
	getchar();
	printf("\n");
	targetNode = searchID(currLocationHead, ID);								//Search for passenger in current purchase location list
	if(targetNode == NULL)														//Not found in current purchase location list
	{
		targetNode = searchID(notCurrLocationHead, ID);							//Search for passenger in not current purchase location list
		if(targetNode == NULL)													//If passenger ID is not found in either list
			printf("Incorrect ID was entered\n");
		else																	//Found it in not current purchase location list
		{
			addToCurrentBal(targetNode, amount);								//The purchase amount is added to the current balance
			if(getLocation(targetNode) != pLocation)							//If is not the same location
			{//(Special Cases: <1> Wrong list, wrong location <2> Wrong list, correct location)
				if(pLocation)														//OnBoard purchase: print incorrect location message_passenger is off the ship
					printf("Passenger location is incorrent, Passenger is currently off the ship. Location will be set to on Ship.\n");
				else																//OffBoard purchase: print incorrect location message_passenger is on the ship
					printf("Passenger location is incorrent, Passenger is currently on the ship. Location will be set to off Ship.\n");
				setLocation(targetNode, pLocation);		//The passenger is not in current purchase location, so we set the passenger location to current purchase location.
			}
		}
	}
	else
	{																		//Found it in the current purchase location list
		addToCurrentBal(targetNode, amount);
		if(getLocation(targetNode) != pLocation)							//If is not the same location
		{//(Special Cases: <1> Corrent list, wrong location <2> Correct list, correct location)
			if(pLocation)														//OnBoard purchase: print incorrect location message_passenger is off the ship
				printf("Passenger location is incorrent, Passenger is currently off the ship. Location will be set to on Ship.\n");
			else																//OffBoard purchase: print incorrect location message_passenger is on the ship
				printf("Passenger location is incorrent, Passenger is currently on the ship. Location will be set to off Ship.\n");
			setLocation(targetNode, pLocation);		//The passenger is not in current purchase location, so we set the passenger location to current purchase location.
		}

	}
}
void synchronizePassengerLists(LLNode *headOffShip, LLNode *headOnShip)
{
	LLNode *currOffShip = headOffShip;
	LLNode *currOnShip = headOnShip;
	LLNode *moveThis;	

	while(currOnShip->Next != NULL)								//Traverse through the onShip list
	{
		if( getLocation(currOnShip->Next) != 1 )				//If any passenger in the onShip list with the location set to 0
		{
			moveThis = currOnShip->Next;
			currOnShip->Next = currOnShip->Next->Next;			//Bypass to move node from onShip list
			insert(headOffShip, moveThis);						//Move to the offShip list
		}
		else													//Else we move to next
			currOnShip = currOnShip->Next;							
	}
	while(currOffShip->Next != NULL)							//Traverse through the offShip list
	{
		if( getLocation(currOffShip->Next) != 0 )				//If any passenger in the offShip list with the location set to 1
		{
			moveThis = currOffShip->Next;
			currOffShip->Next = currOffShip->Next->Next;		//Bypass to move node from offShip list
			insert(headOnShip, moveThis);						//Move to the onShip list
		}
		else													//Else we move to next
			currOffShip = currOffShip->Next;
	}
}
//Print Menu
void printAccountSinglePassenger(LLNode *headOffShip, LLNode *headOnShip)
{
	int i = 0;
	int ID = 0;
	LLNode *targetNode = NULL;
	printf("Enter passenger ID: ");
	scanf("%d", &ID);
	getchar();
	printf("\n");
	targetNode = searchID(headOffShip, ID);										//Search offShip list
	if(targetNode == NULL)													//If not in offShip list we search onShip list
		targetNode = searchID(headOnShip, ID);
	if(targetNode == NULL)													//If passenger ID is not found in either list
		printf("The Passenger ID is not found! Sorry\n");					//Write message and return to Print Menu
	else
	{
		for(i = 0; i < 125; i++)
			printf("_");
		printf("\n|        ID         |          First Name          |               Last Name               |         Current Balance         |\n");
		for(i = 0; i < 125; i++)
			printf("-");

		printf("\n|%-19d|%-30s|%-39s|%-33lf|", getPassengerID(targetNode), getFName(targetNode), getLName(targetNode), getCurrBal(targetNode));
		printf("\n|%-19s|%-30s|%-39s|%-33s|\n"," "," "," "," ");
		for(i = 0; i < 125; i++)
			printf("-");
		printf("\n");

	}		
}

void printPassengerAccounts(LLNode *head)			//Print passenger accounts from list
{
	int i = 0;
	LLNode *curr = head;
	for(i = 0; i < 125; i++)
		printf("_");
	printf("\n|        ID         |          First Name          |               Last Name               |         Current Balance         |\n");
	for(i = 0; i < 125; i++)
		printf("-");

	while(curr->Next != NULL)
	{
		printf("\n|%-19d|%-30s|%-39s|%-33lf|", getPassengerID(curr->Next), getFName(curr->Next), getLName(curr->Next), getCurrBal(curr->Next));
		curr = curr->Next;
	}
	printf("\n|%-19s|%-30s|%-39s|%-33s|\n"," "," "," "," ");
	for(i = 0; i < 125; i++)
		printf("-");
	printf("\n");
}

void removeAllNodePrintAverage(LLNode *headOffShip, LLNode *headOnShip)
{
	LLNode *deleteThis;
	int countNumPassengers = 0;
	double sum = 0;
	double average = 0;

	while(headOffShip->Next != NULL)										//Delete and free offShip list
	{
		deleteThis = headOffShip->Next;										//This is the node ready to delete from list
		headOffShip->Next = headOffShip->Next->Next;						//Bypass to remove from list
		sum = sum + getCurrBal(deleteThis);									//Add to sum
		countNumPassengers++;												//Increament number of passengers
		free(deleteThis);													//Free this node memory						
	}
	while(headOnShip->Next != NULL)											//Delete and free onShip list
	{
		deleteThis = headOnShip->Next;										//This is the node ready to delete from list
		headOnShip->Next = headOnShip->Next->Next;							//Bypass to remove from list
		sum = sum + getCurrBal(deleteThis);									//Add to sum
		countNumPassengers++;												//Increament number of passengers
		free(deleteThis);													//Free this node memory						
	}
	free(headOffShip);														//Free Dummy head Nodes
	free(headOnShip);
	
	if(countNumPassengers != 0)
		average = sum/countNumPassengers;
	printf("Total amount of money spent on the cruise: %lf\nAverage amount of money spent per passenger: %lf\n", sum, average);
	
}

