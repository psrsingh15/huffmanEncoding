// ConsoleApplication2.cpp : Defines the entry point for the console application.  
#include"stdafx.h"             // remove if you aren't using microsoft visual studio 
#include<iostream> 
#include<process.h> 
#include<string.h> 
 
 
using namespace std; 
 
// defines a node of list

struct Node          
{ 
	float prob; 
	short index; 
	string code; 
	Node* next; 
	Node* prev; 
	Node* frontLink; 
	Node* backLink1; 
	Node* backLink2; 
};                
  //*********************** class to maintain symbols  
class symbolList 
{ 
public: 
    void addSymbol(float probab, short dex); 
	void displayList(); 
	void sortList(short n); 
	bool validateList(); 
	void huffmanEncoding(); 
	symbolList(); 
	~symbolList(); 
 
 
private: 
	Node *first, *last, *current, *current1, *current2, *current3, *current5, *after, *temp, *temp1; 
	bool flag; 
	short count; 
	float sum,sumLast; 
	symbolList *nextStage, *prevstage, *current4 ;
	void swapNodes(); 
	void createNextStage();
	void addSymbolInStage(Node*,float); 
	void sumOfLast(); 
	void insertSum(float,Node*,Node*); 
	void findCode();
	void backtrace(Node*);
	void displayCodeList();
}; 
 
symbolList* laststage;
 
//************************************************************************constructor of symbolList 
 
symbolList::symbolList() 
{ 
	first = NULL; 
	last = NULL; 
	nextStage = NULL; 
	prevstage = NULL;
	laststage = this;
	flag = false; 
	count = 0; 
 
} 
 
 
//************************************************************************destructor of symbolList 
 
symbolList::~symbolList() 
{ 
	cout << "\n*******************end*********************"; 
} 
 
 
//***********************************************************************function to insert a symbol in a list 
 
void symbolList::addSymbol(float probab, short dex) 
{ 
	Node* newNode = new Node; 
	newNode->prob = probab; 
	newNode->index = dex; 
	newNode->next = NULL; 
	newNode->prev = NULL; 
	newNode->code = "";
	newNode->backLink1 = NULL; 
	newNode->backLink2 = NULL; 
	newNode->frontLink = NULL; 
 
	if (flag) 
	{    
		newNode->prev = last; 
		last->next = newNode; 
		newNode->prev = last; 
		last = newNode; 
	} 
	else 
	{ 
		flag = true; 
		first = newNode; 
		last = newNode; 
 
	} 
	count++; 
} 
 
//***********************************************************************a function to check wheteher the probabilties aer valid 
 
bool symbolList::validateList() 
{ 
	sum = 0; 
	current = first; 
	while (current) 
	{ 
		sum += current->prob; 
		current = current->next; 
	} 
 
	if (sum == 1) return true; 
	else return false; 
} 
 
 
//***********************************************************************a function to display the list 
void symbolList::displayList() 
{ 
	current1 = first; 
	while (current1 != NULL) 
	{ 
		cout << "\n probability of symbol x" << current1->index << " is " << current1->prob << "\t";
		current1 = current1->next; 
	} 
 
} 
 
 
//***********************************************************************function to sort the list 
void symbolList::sortList(short n) 
{ 
	 
	for (short x = 0; x < n; x++) 
	{ 
		current = first; 
		for (short y = 0; y < n; y++) 
		{ 	 
			if (current->next!= NULL) 
			{ 
				after = current->next; 
				if (current->prob < after->prob) 
				{				 
					swapNodes();					 
					current = after;	 
				}	 
				current = current->next; 
								 
			} 
			else break; 
		} 
	} 
} 
 
//***********************************************************************function to swap the two adjacent nodes 
void symbolList::swapNodes() 
{ 
       	if (current == first) first = after; 
    	if (after == last) last = current; 
		if (current->prev != NULL)  (current->prev)->next = after;  //1 
		if (after->prev)  after->prev->next = current;       //2 
		if (after->next) after->next->prev = current;        //4	 
		temp = current->prev;                         //5 
	    temp1 = after->next;                     //6 
	    after->prev = temp;               //7 
		current->prev = after;                              //8 
		current->next = temp1;               //9 
		after->next = current;              //10 
} 
 
//***********************************************************************create next stageList, add symbols in list 
void symbolList::addSymbolInStage(Node* prevlink, float probb) 
{ 
	Node* tempNode = new Node; 
	 
	tempNode->prob = probb; 
	tempNode->next = NULL; 
	tempNode->prev = NULL; 
	tempNode->code = "";
	
	tempNode->backLink1 = prevlink;
	tempNode->backLink2 = NULL;
	tempNode->frontLink = NULL; 
	prevlink->frontLink = tempNode; 
 
	if (flag) 
	{ 
		tempNode->prev = last; 
		last->next = tempNode; 
		tempNode->prev = last; 
		last = tempNode; 
	} 
	else 
	{ 
		flag = true; 
		first = tempNode; 
		last = tempNode; 
 
	} 
	count++; 
} 
 
//************************************************************************creating new stages 
void symbolList::createNextStage() 
{ 
	if (count > 2) 
	{ 
		symbolList* newStage = new symbolList; 
		laststage = newStage;
		current2 = first; 
		for(int i=1;i<=count-2;i++) 
		{ 
			newStage->addSymbolInStage(current2,current2->prob); 
			current2 = current2->next; 
		}
		nextStage = newStage; 
		newStage->prevstage = this;  
		sumOfLast();                      //find sum and insert
		cout << "\n next stage";
		newStage->displayList();
		nextStage = newStage; 
		laststage = newStage;
		if(nextStage) nextStage->createNextStage(); 
	} 
 
} 
 
//***********************************************************************calculate sum of last two probs and insert in it's place in stage 
void  symbolList::sumOfLast() 
{ 
	sumLast = (last->prob) + (last->prev->prob);  
	nextStage->insertSum(sumLast, last, last->prev); 
} 
 
//**********************************************************************insert sum 
void symbolList::insertSum(/*symbolList* beforeStage,*/ float toInsert,Node *n1, Node *n2) 
{    
	Node* tempNode=new Node; 
	bool done=false; 
	tempNode->prob=toInsert; 
	tempNode->backLink1 = n2; 
	tempNode->backLink2 = n1; 
	tempNode->next = NULL; 
	tempNode->prev = NULL;
	n1->frontLink = tempNode;
	n2->frontLink = tempNode;
	current3 = first; 
	Node* current3trail = first->prev; 
	while (current3 != NULL && (!done)) 
	{ 
		if (toInsert >= current3->prob) 
		{ 
			tempNode->next = current3; 
			tempNode->prev = current3trail; 
		    if(current3trail)	current3trail->next = tempNode; 
			current3->prev = tempNode; 
			done = true; 
			if (current3 == first) first = tempNode; 
			if (current3 == last) last = tempNode; 
		} 
		else 
		{ 
			current3trail = current3; 
			current3 = current3->next; 
		} 
	} 
	if (!done) { 
		tempNode->prev = last; 
		last->next = tempNode; 
		last = tempNode; 
		displayList(); 
	}  
	count++;
} 
 
//************************************************function to find code
void symbolList::findCode()
{
	current4 = laststage;
	current5 = laststage->first;
	current5->code = "0";
	backtrace(current5);
	current5 = current5->next;
	current5->code = "1";
	backtrace(current5);
	 
}

void symbolList::backtrace(Node* link)
{
	Node* anothertemp;
	if ((link->backLink1 !=NULL) && (link->backLink2 != NULL))
	{
		anothertemp = link->backLink1;
		anothertemp->code = link->code + "0";
		if(anothertemp->backLink1) backtrace(anothertemp);
		anothertemp = link->backLink2;
		anothertemp->code = link->code + "1";
		if(anothertemp->backLink1) backtrace(anothertemp);
	}
	else if(link->backLink1)
	{
		anothertemp = link->backLink1;
		anothertemp->code = link->code;
		if (anothertemp->backLink1) backtrace(anothertemp);
		
	}
}

//************************************************display code with symbols
void symbolList::displayCodeList()
{
	current1 = first;
	while (current1 != NULL)
	{
		string a = current1->code;
		cout << "\n the code for symbol x" << current1->index << " is ";

		for (int i = 0; a[i] != '\0'; i++)
			cout << a[i];

		current1 = current1->next;
	}

}



//**********************************************************************huffman encoding 
void symbolList::huffmanEncoding()
{
	cout << "\n................................Encoding message symbols using Huffman Coding................................";
	cout << "\n------------------------------------------------creating stages----------------------------------------------";
	createNextStage();
	findCode();
	cout << "\n--------------------------------------------------encoded list-----------------------------------------------";
	displayCodeList();
}
 
//**********************************************************************function main 
int main() 
{ 
	float probability; 
	short nos,i; 
	symbolList list; 
	cout << "\n enter the number of symbols \t"; 
	cin >> nos; 
 
	for (i = 0; i < nos; i++) 
	{ 
		cout << "enter the probability of x" << (i + 1)<<"\t"; 
		cin >> probability; 
		list.addSymbol(probability, (i + 1)); 
	} 
 
	if (list.validateList()) 
	{ 
		cout << "\n**************************sum of probabilities is equal to 1, data validated********************************"; 
	} 
	else 
	{ 
	    cout << "\n********************sum of probabilities is not equal to 1, data  not validated*****************************"; 
		cout << "\n***********************************************EXITING******************************************************\n";
		exit(EXIT_SUCCESS); 
	} 
 
	list.displayList(); 
	list.sortList(nos); 
	cout << "\nsorted list \n"; 
	list.displayList(); 
	list.huffmanEncoding(); 

	return 0; 
}