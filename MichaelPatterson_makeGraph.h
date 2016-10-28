 /*
Author:Michael Patterson
*/
#pragma once

#include<stdlib.h>
#include<time.h> 
#include<iostream>
#include<utility>
#include "MichaelPatterson_listGraph.h"

bool isPrime(int num)
{
	int check = 0;
	for (int i = 2; i <= num / 2; i++)
	{
		if (num % i == 0)
		{
			check = 1;
			break;
		}
	}
	if (check == 0)
		return true;
	else
		return false;
}

// Prints the Multidimensional Array for Graph
void printGraph(int ** matGraph, int nodeAmt)
{
	//If prims algorithm returns a NULL
	if (matGraph == NULL)
	{
		std::cout << "This Graph is Either Empty or Disconnected" << std::endl;
		return;
	}
	//Prints the x-axis of the matrix
	for (int i = 0; i < nodeAmt; i++)
	{
		if (i == 0)
			std::cout << "   " << getTitle(i);
		else if (i == nodeAmt - 1)
			std::cout << "   " << getTitle(i) << std::endl;
		else
			std::cout << "   " << getTitle(i);
	}

	//Prints the remainder of the matrix
	for(int i = 0; i < nodeAmt; i++)
	{
		std::cout << getTitle(i) << ": ";
		for(int j = 0; j < nodeAmt; j++)
		{
			if(j!=(nodeAmt-1) && (matGraph[i][j] != INT_MAX && matGraph[i][j] != 0))
				std::cout << matGraph[i][j] << " , ";
			else if((matGraph[i][j] != INT_MAX && matGraph[i][j] != 0))
				std::cout << matGraph[i][j] << std::endl;
			else if (j != (nodeAmt - 1) && (matGraph[i][j] == INT_MAX || matGraph[i][j] == 0))
				std::cout << "X , ";
			else if(matGraph[i][j] == INT_MAX || matGraph[i][j] == 0)
				std::cout << "X" << std::endl;
		}
	}
}

// Makes and Returns Multidimensional Array Representation of Given Graph
std::pair<int**, ListGraph> makeGraph(int nodeAmt)
{
	int insert;
	ListGraph listGraph = ListGraph(nodeAmt);
	int ** matGraph = new int*[nodeAmt];	
	for (int i = 0; i < nodeAmt; i++)
		matGraph[i] = new int[nodeAmt];
	for(int i = 0; i < nodeAmt; i++)
	{	
		for(int j = i; j < nodeAmt; j++)
		{
			if (i == j)
			{
				matGraph[i][j] = 0;
				listGraph.addEdge(i, j, 0);
			}
			else
			{
				//insert an edge value from 1 to 10
				insert = rand() % 10 + 1;
				matGraph[i][j] = insert;
				matGraph[j][i] = insert;
				listGraph.addEdge(i, j, insert);
				listGraph.addEdge(j, i, insert);
			}
		}
	}
	return std::make_pair(matGraph, listGraph);
}

int** primMat(int** graph, int nodeAmt)
{
	int** primMat = new int*[nodeAmt];
	for (int i = 0; i < nodeAmt; i++)
	{
		primMat[i] = new int[nodeAmt];
	}
	for (int i = 0; i < nodeAmt; i++)
	{
		for (int j = 0; j < nodeAmt; j++)
		{
			if (i == j)
				primMat[i][j] = 0;
			else
				primMat[i][j] = INT_MAX;
		}
	}

	bool* used = new bool[nodeAmt];
	int min;

	for (int i = 0; i < nodeAmt; i++)
		used[i] = false;

	int test = rand() % nodeAmt;
	used[test] = true;

	int edges = 0;
	int src;
	int dest;

	while (edges < nodeAmt - 1)
	{
		min = INT_MAX;
		for (int i = 0; i < nodeAmt; i++)
		{
			if (used[i] == true) 
			{
				for (int j = 0; j < nodeAmt; j++)
				{
					if (used[j] == false) 
					{
						if (min > graph[i][j] && graph[i][j] != 0)
						{
							min = graph[i][j];
							src = i;
							dest = j;
						}
					}
				}
			}
		}
		used[dest] = true;
		primMat[src][dest] = graph[src][dest];
		primMat[dest][src] = graph[dest][src];
		edges++;
	}
	for (int i = 0; i < nodeAmt; i++)
	{
		if (used[i] == false)
		{
			return NULL;
		}
	}
	return primMat;
}