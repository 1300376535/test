
#include <iostream>
#include <string>
#include <cstring>

#include "pa2.h"

using namespace std;


int main(int a, char** algorithm )
{
	bool worst;
	
	if(strcmp(algorithm[1],"worst") == 0)
	{
		worst = true;
		cout<<"Using worst fit algorithm"<<endl;
	}
	else
	{
		worst = false;
		cout<<"Using best fit algorithm"<<endl;
	}
	
	LinkedList *free = new LinkedList(32, 1);
	LinkedList *used = new LinkedList();

	cout << "1. Add program\n2. Kill program\n3. Fragmentation\n4. Print memory\n5. Exit\n";

	int input = 0;
	while (input != 5)
	{
		cout << "choice - ";
		cin >> input;
		//add program
		if (input == 1)
		{
			cout << "Program name - ";
			string programName = "";
			cin >> programName;
			int pageNum = 0;
			cout << "Program size (KB) - ";
			cin >> pageNum;
			if (pageNum % 4 == 0)
				pageNum = pageNum / 4;
			else
				pageNum = pageNum / 4 + 1;
			int index;
			
			//determine the index of the program
			if (worst)
			{
				index = free->worstAlgorithm(pageNum);
			}
			else
			{
				index = free->bestAlgorithm(pageNum);
			}
			//add the program to the useding memory list
			free->split(index, pageNum);
			used->addProgram(index, pageNum, programName);
			cout << "Program " << programName << " added successfully: " << pageNum << " page(s) used." << endl;
			
		}
		//kill program
		if (input == 2)
		{
			cout << "Program name - ";
			string programName = "";
			cin >> programName;
			//kill the program
			Node *program = used->kill(programName);
			int pageNum = program->pageNum;
			//reclaim the memory
			free->reclaim(program);
			cout << "Program " << programName << " successfully killed, " << pageNum << " page(s) reclaimed." << endl;
		}
		//print out fragments
		if (input == 3)
		{
			int f = free->fragments();
			cout << "There are " << f << " fragment(s)." << endl;

		}
		//print out memories
		if (input == 4)
		{
			int nodes = 0;
			Node * temp = free->head;
			while (temp != nullptr)
			{
				nodes++;
				temp->programName = "free";
				temp = temp->next;
			}
			
			Node *freelist = free->head;
			Node *usedlist = used->head;

			temp = used->head;
			while (temp != nullptr)
			{
				nodes++;
				temp = temp->next;
			}
			for (int i = 0; i < nodes; i++)
			{
				if (i == 0)
				{
					if (freelist == nullptr)
					{
						for (int i = 0; i < nodes; i++)
						{
							usedlist->print();
							usedlist = usedlist->next;
						}
						break;
					}
					else if (usedlist == nullptr)
					{
						for (int i = 0; i < nodes; i++)
						{
							freelist->print();
							freelist = freelist->next;
						}
						break;
					}
					else if (freelist->index == 1)
					{
						freelist->print();
						temp = freelist;
					}
					else if (usedlist->index == 1)
					{
						usedlist->print();
						temp = usedlist;
					}
					continue;
				}
				
				if (temp == freelist)
				{
					freelist = freelist->next;
					usedlist->print();
					temp = usedlist;
				}
				else
				{
					if (usedlist->next ==nullptr)
					{
						freelist->print();
						break;
					}
					if (usedlist->index + usedlist->pageNum == usedlist->next->index)
					{
						usedlist = usedlist->next;
						usedlist->print();
						temp = usedlist;
					}
					else
					{
						usedlist = usedlist->next;
						freelist->print();
						temp = freelist;
					}
				}
			}
		}

	}
	return 0;
}

