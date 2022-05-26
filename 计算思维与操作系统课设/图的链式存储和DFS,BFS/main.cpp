#include <iostream>
#include <queue>
#include <stdio.h>
using namespace std;

#define MAX_V 5
#define INF 2147483647

class MatrixGraph
{
public:
	int edges[MAX_V][MAX_V] = {INF}; //edge matrix 邻接矩阵
	int data[MAX_V] = {0}; // node data 节点数据
};

typedef struct ListNode //Adjacency
{
	int id; // id = heads下标
	char info;
	ListNode* next;
} ListNode, *pListNode;
	

class List
{
public:
	char info;
	pListNode firstNode;
	
	List& insert(pListNode newNode) //方法链
	{
		newNode->next = firstNode;
		firstNode = newNode;
		return *this;	
	}
};

class ListGraph
{
public:
	List heads[MAX_V] = { List {'\0',NULL} }; // id = heads下标

	
	// 炫技了属于是
	List& operator[] (const unsigned int index)
	{
		return heads[index];
	}
	
	void show()
	{
		for(int i=0; i<MAX_V; i++)
		{
			auto& head = heads[i];
			
			cout << "vertex " << i << " info=" << head.info << " AdjacencyNodes= ";
			for(auto cur = head.firstNode; cur!=NULL; cur = cur->next)
				cout << "(" << cur->id << "," << cur->info << ")  ";
			cout << endl;
		}
	}

};

void DFS(ListGraph& g, int curID = 0, bool visited[MAX_V] = NULL) // P212
{
	// 第一次递归的时候初始化visited. 内存泄漏什么的不管了,用vector,list之类的就行
	if(visited == NULL)
		visited = new bool[MAX_V] {false};
	else
		for(int i=0;i<MAX_V;i++) cout<< visited[i] << " ";
	cout << endl;
	
	//访问curID
	visited[curID] = true;
	printf("(%d,%c)  ",curID, g[curID].info);
	
	// 找到第一个没被访问且非空的curID的邻接节点,进行DFS
	for(auto p = g[curID].firstNode; p != NULL; p=p->next)
		if(!visited[p->id])
		{
			DFS(g, p->id, visited);
		}	
}

void BFS(ListGraph& g, int initID = 0) // P212
{
	
	bool visited[MAX_V] = {false};
	std::queue<int> que; // id队列
	
	//visit curID
	visited[initID] = true;
	que.push(initID);
	printf("(%d,%c)  ",initID, g[initID].info);
	
	while(que.size() >= 0)
	{
		initID = que.front();
		que.pop();
		
		for(auto p=g[initID].firstNode; p!=NULL; p=p->next) 
			if(!visited[p->id]) // 所有未访问的initID邻居
			{
				que.push(p->id);
				visited[p->id] = true;
				printf("(%d,%c)  ",p->id, g[p->id].info);
			}
	}

}
int main()
{
	ListGraph graph = {
		.heads = { 
			{'a',NULL},
			{'b',NULL},
			{'c',NULL},
			{'d',NULL},
			{'e',NULL},
		}
	};
	
	auto createNode = [&graph](int id){ return new ListNode { .id=id,.info=graph[id].info }; };
	graph[0].insert(createNode(4)).insert(createNode(3)).insert(createNode(1)); // 头插，需要倒过来写
	graph[1].insert(createNode(3)).insert(createNode(2)).insert(createNode(0));
	graph[2].insert(createNode(4)).insert(createNode(3)).insert(createNode(1));
	graph[3].insert(createNode(4)).insert(createNode(2)).insert(createNode(1)).insert(createNode(0));
	graph[4].insert(createNode(3)).insert(createNode(2)).insert(createNode(0));
	graph.show();               
	
	DFS(graph, 2);
	BFS(graph, 2);

	return 0;
}