/*
Author: Michael Patterson
*/
#include "MichaelPatterson_makeGraph.h"

#include <iostream>
#include <chrono>

int getInt();

int main()
{
	std::cout << "How many vertices are there: ";
	srand(time(NULL));
	int nodeAmt = getInt();
	std::pair<int**, ListGraph> graph = makeGraph(nodeAmt);
	std::pair<int**, ListGraph> primGraph = std::make_pair(primMat(graph.first, nodeAmt), graph.second.PrimList());
	printGraph(graph.first, nodeAmt);
	std::cout << std::endl;
	graph.second.printGraph();
	std::cout << std::endl;
	printGraph(primGraph.first, nodeAmt);
	std::cout << std::endl;
	primGraph.second.printGraph();
	
	int x = 0;
	std::chrono::duration<double>total_list_time;
	std::chrono::duration<double>total_mat_time;
	do
	{
		std::pair<int**, ListGraph> graph = makeGraph(5);
		std::chrono::time_point<std::chrono::high_resolution_clock > matStart, matEnd, listStart, listEnd;

		matStart = std::chrono::high_resolution_clock::now();
		int** PrimMat = primMat(graph.first, 5);
		matEnd = std::chrono::high_resolution_clock ::now();
		total_mat_time = matEnd - matStart;

		listStart = std::chrono::high_resolution_clock::now();
		ListGraph PrimList = graph.second.PrimList();
		listEnd = std::chrono::high_resolution_clock::now();
		total_list_time = listEnd - listStart;
		x++;
	} while (x <= 1000);
	std::cout << "The average time for PRIM LIST is: " << total_list_time.count() / 1000 << std::endl;
	std::cout << "The average time for PRIM MATRIX is: " << total_mat_time.count() / 1000 << std::endl;
	return 0;
}

int getInt()
{
	int result;
	while (true)
	{
		try
		{
			if (std::cin >> result && result > 0) { break; }
			else if (!std::cin) { throw result; }
			else { throw result; }
		}
		catch (int)
		{
			std::cout << "Error=> Not a valid integer.\nPlease Enter another: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	return result;
}