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
		printf("Element deleted from queue is : %d\n", queue[front]);
		front = front + 1;
	}
}

int BFSrecur(int graph[][10], int nodeProp[][2],int node, int cluster, int layer) {
	if (nodeProp[node][0] == 0) {
		for (int i = 0; graph[node - 1][i] != 0; i++) {
			nodeProp[node][0] = layer;
			nodeProp[node][1] = cluster;
		}
		BFSrecur(graph, nodeProp, graph[node - 1][0], cluster, layer + 1);
	}
	else
		return 0;
	for (int i = 1; graph[node - 1][i] != 0; i++)
	return 0;					//potentially redundent
}

int main()
{	//first idx of graph is the node label. Second idx lists the neigbours of the node in a random order, the value contained representing the node label of the neighbour
	//note that first idx has to start from 0 while the values contained in 'graph' start from 1, i.e graph[0][#] != 1 (since a node is never its own neigbour)
	//above note is lso true for nodeProp
	//this had to be done because undeclared vaules get stored as 0 in a 2d array
	int graph[20][10] = { {3},{19},{1,4},{3,9},{10},{20,7,9},{6,8},{7},{4,6},{5,19,20},{12},{11},{16},{19},{17},{13,19},{15,18},{17},{2,10,14,16},{6} };
	int nodeProp[20][2] = { 0 };
	int layer = 1, cluster = 1;	//cluster(value in nodeProp[#][1]) represents collection of nodes that are interconnected, i.e nodes with different 'cluster' are NOT connected
							//layer(value in nodeProp[#][0]) represents the number of steps it takes to reach a particular node from the initial node (valid only for cluster 1)				
	int queue[200] = { -1 };
	queue[0] = 1;
	do {
		for (int i = 0; graph[queue[front]][i] != 0; i++) {
			int newNode = graph[queue[front]][i];
			if (nodeProp[newNode][0] == 0) {
				insertNode(queue, newNode);
				nodeProp[newNode][0] = layer;
				nodeProp[newNode][1] = cluster;
			}
		}
		deleteNode(queue);
	} while(front != rear)
	/*for (int nodeidx = 0; nodeidx < 20; nodeidx++) {
		if (nodeLabel[cluster][layer] != 0)
			continue;
		for (int neigNodeidx = 0; graph[neigNodeidx] != 0; neigNodeidx++) {
			if (nodeLabel[cluster][layer] == 0) {
				nodeLabel[neigNodeidx][0] = cluster;
				nodeLabel[neigNodeidx][1] = layer;
			}
		}
		cluster++;
	}*/
    return 0;
}

