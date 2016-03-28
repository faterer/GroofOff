/*
 * ListDG.cpp
 *
 *  Created on: Mar 9, 2015
 *      Author: mawang
 */
#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

#define MAX 100

class ListDG
{
public:
	ListDG(char vexs[], int vlen, char edges[][2], int elen);
	~ListDG();
	void print();
	void depthFirstSearch();
	void breadthFirstSearch();
	void depthFirstSearch(int, int[]);
	int topologicalSort();
	void TopSort();

private:
	class ENode
	{
	public:
		int iVex;
		ENode *next;
	};

	class VNode
	{
	public:
		char data;
		ENode *first;
	};

	int vexNum;
	int edgNum;
	VNode vexs_[MAX];
	int getPosition(char);
	void linkLast(ENode *, ENode *);
};

ListDG::ListDG(char vexs[], int vlen, char edges[][2], int elen)
{
	char c1, c2;
	int i, p1, p2;
	ENode *node1;

	vexNum = vlen;
	edgNum = elen;

	for(i=0;i<vexNum;i++)
	{
		vexs_[i].data = vexs[i];
		vexs_[i].first = NULL;
	}

	for(i=0;i<edgNum;i++)
	{
		c1 = edges[i][0];
		c2 = edges[i][1];

		p1 = getPosition(c1);
		p2 = getPosition(c2);

		node1 = new ENode();
		node1->iVex = p2;
		if(vexs_[p1].first == NULL)
			vexs_[p1].first = node1;
		else
			linkLast(vexs_[p1].first, node1);
	}
}

int ListDG::getPosition(char ch)
{
	int i;
	for(i=0;i<vexNum;i++)
		if(vexs_[i].data ==ch)
			return i;

	return -1;
}

void ListDG::linkLast(ENode *list, ENode *node)
{
	ENode* p = list;
	while(p->next)
		p = p->next;
	p->next = node;
}

void ListDG::print()
{
	int i;
	ENode *node;

	cout << "List Graph:" << endl;
	for(i =0;i<vexNum;i++)
	{
		cout << i << "(" << vexs_[i].data << "):";
		node = vexs_[i].first;
		while(node)
		{
			cout << node->iVex << "(" << vexs_[node->iVex].data << ")";
			node = node->next;
		}
		cout << endl;
	}
}
void ListDG::depthFirstSearch(int i, int visited[])
{
	ENode *node;
	visited[i] = 1;
	cout << vexs_[i].data << " ";
	node = vexs_[i].first;
	while(node != NULL)
	{
		if(!visited[node->iVex])
			depthFirstSearch(node->iVex, visited);
		node = node->next;
	}
}

void ListDG::depthFirstSearch()
{
	int i;
	int *visited;

	visited = new int[vexNum];
	for(i=0;i<vexNum;i++)
		visited[i] = 0;

	cout << "== DFS: ";
	for(i=0;i<vexNum;i++)
	{
		if(!visited[i])
			depthFirstSearch(i, visited);
	}
	cout << endl;
	delete[] visited;
}

void ListDG::breadthFirstSearch()
{
	int head = 0;
	int rear = 0;
	int *queue;
	int *visited;
	int i,j,k;
	ENode *node;

	queue = new int[vexNum];
	visited = new int[vexNum];
	for(i=0;i<vexNum;++i)
		visited[i] = 0;

	cout << "== BFS: ";
	for(i=0;i<vexNum;i++)
	{
		if(!visited[i])
		{
			visited[i] = 1;
			cout << vexs_[i].data << " ";
			queue[rear++] = i;
		}

		while(head!=rear)
		{
			j = queue[head++];
			node = vexs_[j].first;
			while(node!=NULL)
			{
				k =  node->iVex;
				if(!visited[k])
				{
					visited[k] = 1;
					cout << vexs_[k].data << " ";
					queue[rear++]=k;
				}
				node = node->next;
			}
		}
	}
	cout << endl;
	delete[] visited;
	delete[] queue;
}

int ListDG::topologicalSort()
{
	int i,j;
	int index = 0;
	int head = 0;
	int rear = 0;
	int *queue;
	int *ins;
	char *tops;
	ENode *node;

	ins = new int[vexNum];
	queue = new int[vexNum];
	tops = new char[vexNum];
	memset(ins,0,sizeof(int)*vexNum);
	memset(queue,0,sizeof(int)*vexNum);
	memset(tops,0,sizeof(char)*vexNum);

	for(i=0;i<vexNum;i++)
	{
		node = vexs_[i].first;
		while(node != NULL)
		{
			ins[node->iVex]++;
			node = node->next;
		}
	}

	for(i=0;i<vexNum;i++)
		if(ins[i]==0)
			queue[rear++] = i;

	while(head != rear)
	{
		j = queue[head++];
		tops[index++] = vexs_[j].data;
		node = vexs_[j].first;

		while(node != NULL)
		{
			ins[node->iVex]--;
			if(ins[node->iVex] == 0)
				queue[rear++] = node->iVex;
			node = node->next;
		}
	}

	if(index != vexNum)
	{
		cout << "Graph has a cycle" << endl;
		delete queue;
		delete ins;
		delete tops;
		return -1;
	}

	cout << "== TopSort: ";
	for(i=0;i<vexNum;i++)
		cout << tops[i] << " ";
	cout << endl;
	delete queue;
	delete ins;
	delete tops;
	return 0;
}

void ListDG::TopSort()
{

}

int main()
{
	char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
	char edges[][2] = {{'A', 'C'},{'A', 'D'},{'A', 'F'},
					   {'B', 'C'},{'C', 'D'},{'E', 'G'},
					   {'F', 'G'}};

	int vlen = sizeof(vexs)/sizeof(vexs[0]);
	int elen = sizeof(edges)/sizeof(edges[0]);
	ListDG *pG = new ListDG(vexs, vlen, edges, elen);
	pG->print();
	pG->depthFirstSearch();
	pG->breadthFirstSearch();
	pG->topologicalSort();
	return 0;
}

