typedef struct _passengerInfo			// Create the struct for the Passenger Information
{
	int ID;
	char firstName[25];
	char lastName[35];
	double currentBal;
	char passengerLocation;
}passengerInfo;

typedef struct _LLNode					// Create a Linked List struct
{
	passengerInfo pInfo;
	struct _LLNode *Next;
}LLNode;

LLNode * createLLNode(FILE *file);				// 4.E)
int getPassengerID(LLNode *node);				// 4.F)
LLNode * searchID(LLNode *head, int ID);		// 4.G)
void insert(LLNode *head, LLNode *newNode);		// 4.H)
LLNode * deleteNode(LLNode *head, int ID);      // 4.I)


char * getFName(LLNode *node);
char * getLName(LLNode *node);
double getCurrBal(LLNode *node);
int getLocation(LLNode *node);

void setLocation(LLNode *node, int location);
void addToCurrentBal(LLNode *node, double amount);
