// graphSearchPrac1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int rear = -1;
int front = -1;

void insertNode(int (&queue)[200], int num)
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

void deleteNode(int (&queue)[200])
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

int BFS(int graph[][10], int (&nodeLayer)[20],int startNode) {
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
		}
		deleteNode(queue);
	}
	return 0;					
}

int main()
{	//first idx of 'graph' is the node label(number). Second idx lists the neigbours of the node in a random order, the value contained representing the node label of the neighbour
	//NOTE: first idx has to start from 0 while the values contained in 'graph' start from 1, Ex: graph[0][#] != 1 (since a node is never its own neigbour)
	//above note is also true for nodeLayer
	//this had to be done because undeclared vaules get stored as 0 in a 2d array
	int graph[20][10] = { {3},{19},{1,4},{3,9},{10},{20,7,9},{6,8},{7},{4,6},{5,19,20},{12},{11},{16},{19},{17},{13,19},{15,18},{17},{2,10,14,16},{6} };
	int nodeLayer[20] = { 0 };
	memset(nodeLayer, -1, sizeof(int) * 20);
	BFS(graph, nodeLayer, 18);
	/*cout << "The nodes connected to 1 are : ";
	for (int i = 0; i < 20; i++)
		if (nodeLayer[i] != 0)
			cout << i;*/
	cout << nodeLayer[12]<< endl;
	return 0;
}

