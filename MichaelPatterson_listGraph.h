/*
Author:Michael Patterson
*/
#pragma once
#include <list>
#include <iostream>
#include <utility>

//Returns label of vertex
char getTitle(int lab)
{
	char title;
	switch (lab)
	{
	case 0: title = 'A'; break;
	case 1: title = 'B'; break;
	case 2: title = 'C'; break;
	case 3: title = 'D'; break;
	case 4: title = 'E'; break;
	case 5: title = 'F'; break;
	case 6: title = 'G'; break;
	case 7: title = 'H'; break;
	case 8: title = 'I'; break;
	case 9: title = 'J'; break;
	case 10: title = 'K'; break;
	case 11: title = 'L'; break;
	case 12: title = 'M'; break;
	case 13: title = 'N'; break;
	case 14: title = 'O'; break;
	case 15: title = 'P'; break;
	case 16: title = 'Q'; break;
	case 17: title = 'P'; break;
	case 18: title = 'R'; break;
	case 19: title = 'S'; break;
	case 20: title = 'T'; break;
	case 21: title = 'U'; break;
	case 22: title = 'V'; break;
	case 23: title = 'W'; break;
	case 24: title = 'Y'; break;
	case 25: title = 'Z'; break;
	}
	return title;
}

class ListGraph
{
	private:
		int vertAmt;
		std::list<std::pair<int, int>>* gArr;
	public:
		ListGraph(int);
		//Destructor somehow messes with prim algo assuming that it has to do with iterators calling the destructor when finished
		//~ListGraph();
		void addEdge(int, int, int);
		void printGraph();
		ListGraph PrimList();
};

ListGraph::ListGraph(int amt)
{
	vertAmt = amt;
	gArr = new std::list<std::pair<int, int>>[vertAmt];
}
 
/*ListGraph::~ListGraph()
{
	delete[] gArr;
}*/

void ListGraph::addEdge(int src, int dest, int weight)
{
	gArr[src].push_back(std::make_pair(dest, weight));
	return;
}

void ListGraph::printGraph()
{
	if (vertAmt == 0)
	{
		std::cout << "This Graph is Either Empty or Disconnected" << std::endl;
		return;
	}
	for (int i = 0; i < vertAmt; i++)
	{
		std::cout << getTitle(i);
		for (std::list<std::pair<int, int>>::iterator it = gArr[i].begin(); it != gArr[i].end(); ++it)
		{
			if (it->second != 0)
				std::cout << " -> " << getTitle(it->first) << ", " << it->second;
		}
		std::cout << std::endl;
	}
	return;
}

ListGraph ListGraph::PrimList()
{
	ListGraph primList = ListGraph(vertAmt);
	bool* used = new bool[vertAmt];
	int min;

	for (int i = 0; i < vertAmt; i++)
		used[i] = false;

	int test = rand() % vertAmt;
	used[test] = true;

	int edges = 0;
	int x;
	int y;
	int val;
	while (edges < vertAmt - 1)
	{
		min = INT_MAX;
		for (int i = 0; i < vertAmt; i++)
		{
			for (std::list<std::pair<int, int>>::iterator it = gArr[i].begin(); it != gArr[i].end(); ++it)
			{
				if (used[i] == true)
				{
					for (std::list<std::pair<int, int>>::iterator it2 = gArr[i].begin(); it2 != gArr[i].end(); ++it2)
					{
						if (used[it2->first] == false)
						{
							if (min > it2->second && it2->second != 0)
							{
								min = it2->second;
								x = i;
								y = it2->first;
							}
						}
					}
					val = min;
				}
			}
		}
		used[y] = true;
		primList.addEdge(x, y, min);
		primList.addEdge(y, x, min);
		edges++;
	}
	for (int i = 0; i < vertAmt; i++)
	{
		if (used[i] == false)
		{
			return ListGraph(0);
		}
	}
	delete[] used;
	return primList;
}

