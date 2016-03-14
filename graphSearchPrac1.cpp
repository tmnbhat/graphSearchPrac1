// graphSearchPrac1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int rear = -1;
int front = -1;

void insertNode(int(&queue)[200], int num)
{
	if (rear == (200 - 1))
		printf("Queue Overflow \n");
	else
	{
		if (front == -1)
			/*If queue is initially empty */
			front = 0;
		rear = rear + 1;
		queue[rear] = num;
	}
}

void deleteNode(int(&queue)[200])
{
	if (front == -1 || front > rear)
	{
		printf("Queue Underflow \n");
		return;
	}
	else
	{
		//printf("Element deleted from queue is : %d\n", queue[front]);
		front = front + 1;
	}
}

int BFS(int graph[][10], int(&nodeLayer)[20], int startNode, int reqNode) {
	rear = -1;
	front = -1;
	int queue[200] = { -1 };
	insertNode(queue, startNode);
	nodeLayer[startNode] = 0;			//nodeLayer represents the minimum number of steps it takes to reach a particular node from the initial node		
	while (!(front == -1 || front > rear)) {
		for (int i = 0; graph[queue[front]][i] != 0; i++) {
			int oldNode = queue[front];
			int newNode = graph[queue[front]][i] - 1;
			//cout << newNode << endl;
			if (nodeLayer[newNode] == -1) {
				insertNode(queue, newNode);
				nodeLayer[newNode] = nodeLayer[oldNode] + 1;
			}
			if ((newNode == reqNode) && (reqNode > 0)) {
				cout << "The required node " << reqNode + 1 << " was found in layer " << nodeLayer[newNode] << endl;
				return 0;
			}
		}
		deleteNode(queue);
	}
	if (reqNode > 0) {
		cout << "The required node " << reqNode + 1 << " was NOT found" << endl;
		return -1;
	}
	return 0;
}

int DFS(int graph[][10], int(&nodeSeen)[20], int currentNode, int reqNode) {
	nodeSeen[currentNode] = 1;
	if ((currentNode == reqNode) && (reqNode >= 0)) {
		cout << "The required node " << reqNode + 1 << " was found" << endl;
		return 0;
	}

	for (int i = 0; graph[currentNode][i] != 0; i++) {
		if (nodeSeen[graph[currentNode][i] - 1] != 1)
			DFS(graph, nodeSeen, graph[currentNode][i] - 1, reqNode);
	}
	return 0;
}

int dijkstra(int graphNeig[][5], int graphDist[][5], int(&nodeAnaly)[5], int(&nodePathL)[5], int startNode, int reqNode) {
	nodeAnaly[startNode] = 1;
	int numNodesSeen = 1;
	nodePathL[startNode] = 0;
	int nodeDistBuff = 1000;
	int nodeAnalyBuff = -1;
	int nodeAnalyPrevBuff = -1;
	while (numNodesSeen < 5) {
		for (int i = 0; i < 5; i++)
			if (nodeAnaly[i] == 1)
				for (int j = 0; graphNeig[i][j] != 0; j++)
					if ((nodeAnaly[graphNeig[i][j] - 1] != 1) && (graphDist[i][j] < nodeDistBuff)) {
						nodeDistBuff = graphDist[i][j];
						nodeAnalyBuff = graphNeig[i][j] - 1;
						nodeAnalyPrevBuff = i;
					}
		nodeAnaly[nodeAnalyBuff] = 1;
		nodePathL[nodeAnalyBuff] = nodePathL[nodeAnalyPrevBuff] + nodeDistBuff;
		if (nodeAnalyBuff == reqNode)
			return 0;
		nodeDistBuff = 1000;
		numNodesSeen++;
	}
	return 0;
}

int main()
{	//first idx of 'graph' is the node label(number). Second idx lists the neigbours of the node in a random order, the value contained representing the node label of the neighbour
	//NOTE: first idx has to start from 0 while the values contained in 'graph' start from 1, Ex: graph[0][#] != 1 (since a node is never its own neigbour)
	//above note is also true for nodeLayer
	//this had to be done because undeclared vaules get stored as 0 in a 2d array
	int graph[20][10] = { { 3 },{ 19 },{ 1,4 },{ 3,9 },{ 10 },{ 20,7,9 },{ 6,8 },{ 7 },{ 4,6 },{ 5,19 },{ 12 },{ 11 },{ 16 },{ 19 },{ 17 },{ 13,19 },{ 15,18 },{ 17 },{ 2,10,14,16 },{ 6 } };
	int dGraph[10][10] = { { 3,10,-9 },{ 6,-3,-8 },{ 2,-1,-8 },{ 5,6,-7 },{ 7,-10,-4 },{ 8,-2,-6 },{ 4,-5 },{ 2,3,-6 },{ 1,-10 },{ 9,5,-1 } };
	int nodeLayer[20] = { 0 };
	int graphDijNeig[5][5] = { { 2,4 },{ 3,4,1 },{ 4,2 },{ 1,2,3,5 },{ 2,4 } };
	int graphDijDist[5][5] = { { 2,5 },{ 6,2,2 },{ 3,6 },{ 5,2,3,1 },{ 4,1 } };
	int nodeAnaly[5] = { 0 };
	int nodePathL[5] = { 0 };
	memset(nodeAnaly, -1, sizeof(int) * 5);
	memset(nodeLayer, -1, sizeof(int) * 20);
	//DFS(graph, nodeLayer, 16, -1);
	dijkstra(graphDijNeig, graphDijDist, nodeAnaly, nodePathL, 0, -1);
	cout << nodePathL[2] << endl;
	/*cout << "The nodes connected to 17 are : ";
	for (int i = 0; i < 20; i++)
	if (nodeLayer[i] != -1)
	cout << i + 1 << endl;*/
	//cout << nodeLayer[12]<< endl;
	return 0;
}

