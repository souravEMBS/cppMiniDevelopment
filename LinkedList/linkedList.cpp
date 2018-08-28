#include <iostream>

using namespace std;


struct node{
	int data;
	node *next;
};

bool isEmpty(node *head);
char menu();
void insertAsFirstElement(node *&head,node *&last,int number);
void insert(node *&head,node *&last,int number);
void remove(node *&head,node *&last);
void showlist(node *current);

int main(int argc, char const *argv[])
{
	/* code */
	node *head = NULL;
	node *last = NULL;
	char choice;
	int number;

	do{
		choice = menu();
		switch(choice)
		{
			case '1':
				cout  << "please enter a number: ";
				cin >> number;
				insert(head,last,number);
				break;
			case '2':
				remove(head,last);
				break;
			case '3':
				showlist(head);
				break;
			case '4':
				cout << "exit" << endl;
				break;
		}

	}while(choice != '4');
	
	return 0;
}


bool isEmpty(node *head)
{
	if(head == NULL)
		return true;
	else
		return false;
}


char menu(){

	char choice;
	cout << "Menu:" << endl;
	cout << "1.Add item. \n";
	cout << "2.Remove item. \n";
	cout << "3.Show list. \n";
	cout << "4.Exit. \n";

	cin >> choice;

	return choice;
}


void insertAsFirstElement(node *&head,node *&last,int number)
{
	node *temp = new node;
	temp->data = number;
	temp->next = NULL;
	head = temp;
	last = temp;
}


void insert(node *&head,node *&last,int number){
	if(isEmpty(head))
		insertAsFirstElement(head,last,number);
	else
	{
		node *temp =  new node;
		temp->data = number;
		temp->next = NULL;
		last->next = temp;
		last = temp;

	}


}
void remove(node *&head,node *&last){

	if(isEmpty(head))
		cout << "List is empty, nothing removed" << endl;
	else if(head == last)
	{
		delete head;
		head ==  NULL;
		last == NULL;
	}
	else
	{
		node *temp = head;
		head = head->next;
		delete temp;
	}

}
void showlist(node *current){
	if(isEmpty(current))
		cout << "List is empty, nothing to show" << endl;
	else
	{
		cout << "the list contains: \n";
		while(current != NULL)
		{
			cout<< current->data << endl;
			current =  current->next;
		}
	}

}