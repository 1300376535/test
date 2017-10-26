
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class Node
{
private:
public:
	int index;
	int pageNum;
	Node *next;
	string programName;
	
	Node(int a, int b, string p)
	{
		pageNum = a;
		next = nullptr;
		index = b;
		programName = p;
	}
	void print()
	{
		for (int i = 0; i < pageNum; i++)
		{
			cout << programName << " ";
		}
		cout << endl;
	}

};


class LinkedList
{
private:
public:
	Node *head;
	LinkedList()
	{
		head = nullptr;
	}
	LinkedList(int a, int b)
	{
		head = new Node(a, b, "free");
	}
	
	//the worst fit algorithm to find the index of the node being split
	int worstAlgorithm(int pages)
	{
		int max, index;
		Node * temp = head;
		while (temp->pageNum < pages && temp->next != nullptr)
		{
			temp = temp->next;
		}
		if(temp->pageNum >= pages)
		{
			max = temp->pageNum;
			index = temp->index;
			while (temp->next != nullptr)
			{
				if (temp->next->pageNum > max)
				{
					max = temp->next->pageNum;
					index = temp->next->index;
				}
				temp = temp->next;
			}
			return index;
		}
		else
			return 0;
	}
	
	//the best fit algorithm to find the index of the node being split
	int bestAlgorithm(int pages)
	{
		int min, index;
		Node * temp = head;
		while (temp->pageNum < pages && temp->next != nullptr)
		{
			temp = temp->next;
		}
		if (temp->pageNum >= pages)
		{
			min = temp->pageNum;
			index = temp->index;
			while (temp->next != nullptr)
			{
				if (temp->next->pageNum < min && temp->pageNum >= pages)
				{
					min = temp->next->pageNum;
					index = temp->next->index;
				}
				temp = temp->next;
			}
			return index;
		}
		else
		{
			return 0;
		}
	}
	
	//split part of the node out
	void split(int i, int pages)
	{
		Node * max = head;
		while (max->index != i)
		{
			max = max->next;
		}
		if (max->pageNum == pages)
		{
			Node * temp = head;
			if(temp == max)
			{
				head = max->next;
				delete max;
				return;
			}
			while(temp->next != max)
			{
				temp = temp->next;
			}
			temp->next = temp->next->next;
			delete max;
			return;
		}
		else
		{
			max->index = i + pages;
			max->pageNum = max->pageNum - pages;
			return;
		}
	}
	
	//add program to the used memory list
	void addProgram(int i, int pages, string name)
	{
		if (head == nullptr)
		{
			head = new Node(pages, i, name);
			return;
		}
		Node * temp = head;
		while (temp != nullptr)
		{
			if (temp->index > i)
			{
				if (temp == head)
				{
					head = new Node(pages, i, name);
					head->next = temp;
					return;
				}

				Node * temp2 = head;
				while (temp2->next != temp)
				{
					temp2 = temp2->next;
				}
				temp2->next = new Node(pages, i, name);
				temp2->next->next = temp;
				return;
			}
			temp = temp->next;
		}
		temp = head;
		while (temp->next != nullptr)
		{
			temp = temp->next;
		}
		temp->next = new Node(pages, i, name);
		return;
	}
	
	//kill a program in used memory list
	Node* kill(string name)
	{
		Node * temp = head;
		while (temp->programName.compare(name) != 0)
		{
			temp = temp->next;
		}
		if (head == temp)
		{
			head = temp->next;
			return temp;
		}
		Node * temp2 = head;
		while (temp2->next != temp)
		{
			temp2 = temp2->next;
		}
		temp2->next = temp->next;
		return temp;
	}
	
	//reclaim the memory of the program being killed
	void reclaim(Node * program)
	{
		if (head == nullptr)
		{
			head = program;
			program->next = nullptr;
			return;
		}
		Node * temp = head;
		while (temp->index < program->index)
		{
			temp = temp->next;
			if (temp == nullptr)
			{
				Node * temp2 = head;
				while (temp2->next != temp)
				{
					temp2 = temp2->next;
				}
				temp2->next = program;
				program->next = nullptr;
				if (temp2->index + temp2->pageNum == program->index)
				{
					temp2->next = nullptr;
					temp2->pageNum = temp2->pageNum + program->pageNum;
					delete program;
				}
				return;
			}
		}
		program->next = temp;
		Node * temp2 = head;
		while (temp2->next != temp)
		{
			if (temp2 == temp)
			{
				head = program;
				program->next = temp;
				if (program->index + program->pageNum == temp->index)
				{
					program->next = temp->next;
					program->pageNum = temp->pageNum + program->pageNum;
					delete temp;
					return;
				}
				return;
			}
			temp2 = temp2->next;
		}
		temp2->next = program;
		if (temp2->index + temp2->pageNum == program->index)
		{
			if (program->index + program->pageNum == temp->index)
			{
				temp2->next = temp->next;
				temp2->pageNum = temp2->pageNum + program->pageNum + temp->pageNum;
				delete program;
				delete temp;
				return;
			}
			temp2->next = temp;
			temp2->pageNum = temp2->pageNum + program->pageNum;
			delete program;
			return;
		}
		return;
	}
	
	//calculate the fragments in the memory
	int fragments()
	{
		int f = 0;
		Node * temp = head;
		while (temp != nullptr)
		{
			f++;
			temp = temp->next;
		}
		return f;
	}
};
