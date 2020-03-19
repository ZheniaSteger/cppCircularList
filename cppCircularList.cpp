//============================================================================
// Author		: Zhenia Steger
// College		: California State University San Marcos
// Purpose		: Demonstate circularly linked list
// ============================================================================

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// PROTOTYPE CLASSES / FUNCTIONS
class Node;
class CircularDLL;

// TYPE DEFINITION FOR NODE POINTER
typedef Node* NodePtr;

// ============================================================================
// NODE CLASS
class CircularDLL;

class Node
{
	friend class CircularDLL;
	private:
		int stId;
		string stName;
		string stEmail;
		int stAge;
		NodePtr next;
		NodePtr prev;
};

// ============================================================================
// CIRCULAR LINKED LIST CLASS
class CircularDLL
{
	private:
		NodePtr top;
		int numOfNodes;
		void destroy(NodePtr&);
	public:
	CircularDLL();
	CircularDLL(const CircularDLL& source);
	~CircularDLL();

	void insertDataFromFile();
	void print();
	bool search(int);
	void insertAfterFirst(int id, string name, string email, int age);
	void insertBeforeFirst(int id, string name, string email, int age);
	void insertAfterLast(int id, string name, string email, int age);
	void insertBeforeLast(int id, string name, string email, int age);
	void remove(int);
	void copy(NodePtr top1, NodePtr& top2);
};

// ============================================================================
// PURPOSE: Destroys the linked list
// PARAMETER: top node of linked list to be destroyed
void CircularDLL::destroy(NodePtr& top)
{
	if(top == NULL)
		return;

	NodePtr origTop = top;
	NodePtr prev;

	do
	{
		prev = top;
		top = top->next;
		delete prev;
	} while(origTop != top);
	top = NULL;
}

// ============================================================================
// DEFAULT CONSTRUCTOR
CircularDLL::CircularDLL()
{
	top = NULL;
}

// ============================================================================
// COPY CONSTRUCTOR
CircularDLL::CircularDLL(const CircularDLL& source)
{
	top = NULL;
	copy(source.top, top);
}

// ============================================================================
// DEFAULT DESTRUCTOR
CircularDLL::~CircularDLL()
{
	destroy(top);
}

// ============================================================================
// PURPOSE: Inserts data from a file into the linked list
void CircularDLL::insertDataFromFile()
{
	cout << "Opening file 'transaction.txt'" << endl;
	ifstream fin;
	fin.open("transaction.txt");
	if(!fin)	cout << "File does not exist." << endl;

	while(!fin.eof())
	{
		int id;
		string name;
		string email;
		int age;
		numOfNodes++;

		fin >> id >> name >> email >> age;
		insertAfterLast(id, name, email, age);
	}
	fin.close();
}

// ============================================================================
// PURPOSE: Calls the print function to output contents of each node
void CircularDLL::print()
{
	NodePtr curr;
	curr = top;
	do
	{
		cout << "-----------------------------------------" << endl;
		cout << "Students ID: " << curr->stId << endl;
		cout << "Students Name: " << curr->stName << endl;
		cout << "Students Email: " << curr->stEmail << endl;
		cout << "Students Age: " << curr->stAge << endl;
		cout << "-----------------------------------------" << endl;
		curr = curr->next;
	} while(curr != top);
	cout << endl;
}

// ============================================================================
// PURPOSE: Searches through student stId for the passsed parameter id 's'
bool CircularDLL::search(int s)
{
	if(top == NULL)
	{
		return false;
	}
	NodePtr curr;
	curr = top;
	curr = curr->next;
	while(curr != top)
	{
		if (curr->stId == s)
			return true;
		curr = curr->next;
	}
	return false;
}

// ============================================================================
// PURPOSE: Inserts data after the first node
void CircularDLL::insertAfterFirst(int id, string name, string email, int age)
{
	NodePtr newNode = new Node;
	newNode->stId = id;
	newNode->stName = name;
	newNode->stEmail = email;
	newNode->stAge = age;

	if(top == NULL)
	{
		top = newNode;
		newNode->next = top;
		newNode->prev = top;
		return;
	}

	newNode->prev = top;
	newNode->next = top->next;

	if(top->prev == top)
	{
		top->prev = newNode;
	}
	else
	{
		top->next->prev = newNode;
	}
	top->next = newNode;
}

// ============================================================================
// PURPOSE: Inserts data before the first node
void CircularDLL::insertBeforeFirst(int id, string name, string email, int age)
{
	NodePtr newNode = new Node;
	newNode->stId = id;
	newNode->stName = name;
	newNode->stEmail = email;
	newNode->stAge = age;

	if(top == NULL)
	{
		top = newNode;
		return;
	}
	if(top->next == top)
	{
		newNode->prev = top;
		newNode->next = top;
		top->next = newNode;
		top->prev = newNode;
		top = newNode;
	}
	else
	{
		newNode->prev = top->prev;
		newNode->next = top->next;
		top->prev = newNode;
		top->next = newNode;
		top = newNode;
	}
}

// ============================================================================
// PURPOSE: Inserts data after the last node
void CircularDLL::insertAfterLast(int id, string name, string email, int age)
{
	NodePtr newNode = new Node;
	newNode->stId = id;
	newNode->stName = name;
	newNode->stEmail = email;
	newNode->stAge = age;

	if(top == NULL)
	{
		top = newNode;
		newNode->next = top;
		newNode->prev = top;
		return;
	}
	if(top->prev == top)
	{
		top->next = newNode;
		top->prev = newNode;
		newNode->next = top;
		newNode->prev = top;
	}
	else
	{
		newNode->prev = top->prev;
		top->prev->next = newNode;
		top->prev = newNode;
		newNode->next = top;
	}
}

// ============================================================================
// PURPOSE: Inserts data before the last node
void CircularDLL::insertBeforeLast(int id, string name, string email, int age)
{
	NodePtr newNode = new Node;
	newNode->stId = id;
	newNode->stName = name;
	newNode->stEmail = email;
	newNode->stAge = age;

	if(top == NULL)
	{
		top = newNode;
		return;
	}

	NodePtr prevNode = top->prev;
	newNode->next = prevNode;
	newNode->prev = prevNode->prev;
	prevNode->prev->next = newNode;
	if(top->prev == top)
	{
		top = newNode;
	}
	prevNode->prev = newNode;
}

// ============================================================================
// PURPOSE: Removes a node matching the stId to the passed parameter 's'
void CircularDLL::remove(int n)
{
	if(top == NULL)
	{
		return;
	}
	NodePtr curr = top;
	NodePtr prev = NULL;

	while(curr->stId != n && curr->next != top)
	{
		prev = curr;
		curr = curr->next;
	}
	if(!prev)
	{
		delete top;
		top = NULL;
	}
	else
	{
		prev->next = curr->next;
		curr->next->prev = prev;
	}
}

// ============================================================================
// PURPOSE: Copies one list to another
void CircularDLL::copy(NodePtr top1, NodePtr &top2)
{
	destroy(top2);
	NodePtr lcurr, rcurr;

	if(top1 != NULL)
	{
		top2 = new Node;

		top2->stId = top1->stId;
		top2->stName = top1->stName;
		top2->stEmail = top1->stEmail;
		top2->stAge = top1->stAge;

		lcurr = top1;
		rcurr = top2;

		while(lcurr->next != top1)
		{
			rcurr->next = new Node;
			rcurr->next->prev = rcurr;
			rcurr = rcurr->next;
			lcurr = lcurr->next;

			rcurr->stId = lcurr->stId;
			rcurr->stName = lcurr->stName;
			rcurr->stEmail = lcurr->stEmail;
			rcurr->stAge = lcurr->stAge;
		}

		rcurr->next = top2;
		top2->prev = rcurr;
	}
}

// ============================================================================
// PURPOSE: Main method runs the program
int main()
{
	CircularDLL list1;
	list1.insertDataFromFile();
	list1.print();
	list1.insertAfterFirst(54321, "Jim", "jim@csusm.edu", 25);
	list1.insertBeforeFirst(54123, "Joe", "joe@csusm.edu", 35);
	list1.insertAfterLast(63421, "Adam", "adam@csusm.edu", 20);
	list1.insertBeforeLast(66641, "Nancy", "nancy@csusm.edu", 27);
	list1.print();

	bool found = list1.search(12321);
	if(found)
		cout << "The record was found." << endl;
	else {
		cout << "The record was not found." << endl;
	}
	cout << "Removing 54321" << endl;
	list1.remove(54321);
	list1.print();

	CircularDLL list2(list1);
	list2.print();
	return 0;
}