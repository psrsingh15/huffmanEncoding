#include <iostream>

using namespace std;


/* first stage od developing a program for hoffman encoding, 
   here a link list is created to store symbols and their probabilities */



struct link                    // 4 directional
{
	float prob;
	int index;
	link* next;
	link* previous;	
//	link* nextStage;                not using these at this stage so commenting them out
//	link* previousStage;
};





class symbolList
{
private:
 link* first;
 link* last;
 link* temp;
 link* after;
 bool flag;
 
 
public:
	symbolList()
	{
		first=NULL;
		last=NULL;
		flag= false;
	}

	void addSymbol(float p, int n )           //function to add a symbol
	{
          link* newlink= new link;
          newlink->prob=p;
          newlink->index=(n+1);
          
       
         
         if(flag)                                    
         {                                                        //executes if the list already exists
            last->next=newlink;                                          
         	newlink->previous=last;
         	last=newlink;
         	         	
         }
         else
         {                                                      // execute if the list doesn't exists
         	
         	flag=true;
         	first=newlink;
         	last=newlink;
         	
         }	
         

	}



    void display(){                                          // function to display all the symbols
    	link* current = first;
        cout<<"\tsymbol\tprobability\n-------------------------------------------\n";
        while(current!=NULL)
        {
        	cout<<"\t  x "<<current->index<<"     \t     "<<current->prob<<endl;
        	current=current->next;
        }
        cout<<"\a";
    }
 
 


	
};

            
int main()             //function main
{
	symbolList li;
	float prob;
	int length;
	cout<<" please enter the number of symbols \t";
	cin>>length;

	for (int i = 0; i < length; ++i)
	{
	
			cout<<"enter the probability of symbol  "<<(i+1)<<" \t";
		cin>>prob;
		li.addSymbol(prob,i);
	} 
	li.display();
	
	return 0;
}
