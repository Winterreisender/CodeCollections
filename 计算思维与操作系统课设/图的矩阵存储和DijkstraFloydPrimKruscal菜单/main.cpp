#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <tuple>
#include <stack>
#include <queue>
#include <list>

#define MAX_V 16 // 最大节点数,仅用于初始化数组,其他情况请用MatrixGraph.size
#define INF INT_MAX 

using namespace std;

class MatrixGraph {
	public:
		int edges[MAX_V][MAX_V] = {0}; //edge matrix 邻接矩阵
		char info[MAX_V] = {0}; // node data 节点数据
		int size = MAX_V;
		
		void show(bool show_info = true) const {
			
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++)
					if (edges[i][j] == INF)
						printf("INF ");
					else
						printf("%3d ", edges[i][j]);
				cout << endl;
			}
			
			if(!show_info)
				return;
			
			puts("");
			puts("各节点数据:");
			for(int i=0;i<size; i++)
				printf("%d: %c, ", i, info[i]);
			puts("");
		}
		
		int getWeight() const
		{
			int weight = 0;
			for(int i=0;i<size;i++)
			for(int j=0;j<size;j++)
				weight += edges[i][j];
			return weight;
		}
};

template <typename T>
void showMatrix(const T matrix[][MAX_V], const char* format, int rows, int cols) 
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
			if (matrix[i][j] == INF)
				printf("INF ");
			else
				printf(format, matrix[i][j]);
		cout << endl;
	}
}

MatrixGraph prim(const MatrixGraph g) {
	MatrixGraph tree; //最小生成树
	tree.size = g.size;
	bool isCandidate[MAX_V][MAX_V] = {false}; //是否为候选
	bool inTree[MAX_V] = {false}; //是否在已选节点集合U里 回环=两个inTree节点相连

	for (int _i = 0; _i < g.size; _i++) {
		int minX = 0, minY = 0; //选择的节点
		//showMatrix(isCandidate, "%d ");

		//找最小边
		for (int i = 0; i < g.size; i++)
		for (int j = 0; j < g.size; j++)
			if (isCandidate[i][j] && i != j && !inTree[j])
			if (g.edges[i][j] < g.edges[minX][minY] || g.edges[minX][minY] == 0)  //从所有节点中选出 是候选的 不是自己和自己的 不在已选集合U里的节点
			{ 
				minX = i;
				minY = j;
			}

		cout << "select (" << minX << "," << minY << ")" << endl;

		tree.edges[minX][minY] = g.edges[minX][minY];
		isCandidate[minX][minY] = false; // 选完后不是候选
		inTree[minY] = true;

		for (int i = 0; i < g.size; i++) //添加新的候选 minY 的邻居 add minY to isCandidate as next Candidate
			if (i != minY)
				isCandidate[minY][i] = true;
	}
	return tree;
}


MatrixGraph kruskal(const MatrixGraph g) {
	MatrixGraph tree; //最小生成树
	tree.size = g.size;
	int inTree[MAX_V] = {}; //是否在已选节点集合U_i里 两节点不在同一树时，不连通，连接后不成环
	for(int i=0;i< g.size;i++)
		inTree[i] = i;
	
	for (int _i = 0; _i < g.size - 1; _i++) {
		int minX = 0, minY = 0;

		//找最小边
		for (int i = 0; i < g.size; i++)
		for (int j = 0; j < g.size; j++)
			if (inTree[j] != inTree[i]) //两节点不在同一树时，不连通，不成环 (隐含i!=j)
			if (g.edges[i][j] < g.edges[minX][minY] || g.edges[minX][minY] == 0) { //从所有节点中选出 不是自己和自己的 不在已选集合U里的节点
				minX = i;
				minY = j;
			}

		cout << "select (" << minX << "," << minY << ")" << endl;
		tree.edges[minX][minY] = g.edges[minX][minY];

		// update inTree
		for (int i = 0; i < g.size; i++)
			if (inTree[i] == inTree[minY])
				inTree[i] = inTree[minX]; //X,Y同树
	}
	return tree;
}

struct DijkstraResult {int distance[MAX_V];int path[MAX_V];};
auto dijkstra(const MatrixGraph g, int startID = 0) {
	
	int distance[MAX_V]; // 最短距离
	int path[MAX_V]; // 最短路径 "上一个节点"
	bool inU[MAX_V] = {false}; // 在不在集合U里(已找到)

	// 初始化distance 和 path
	for (int i = 0; i < g.size; i++) 
	{
		distance[i] = g.edges[startID][i];
		path[i] = (startID == INF) ? -1 : startID;
	}
	
	// 主体
	for (int _i = 0; _i < g.size; _i++) 
	{
		// 显示最短路径
		cout << "update distance:" ;
		showMatrix(&distance, "%3d ", 1, g.size);
		
		int minDisID = -1; // -1表示没有 , 这样去掉了原来的变量minDis
		//找出最小距离cost
		for (int i = 0; i < g.size; i++)
			if (!inU[i])
			if (distance[i] < distance[minDisID] || minDisID==-1)
			{
				minDisID = i;
			}
		// 把最小的放入U
		inU[minDisID] = true;

		for (int j = 0; j < g.size; j++)
			if (!inU[j])  
			if (g.edges[minDisID][j] < INF) //筛出不在U且非INF的
			if (distance[minDisID] + g.edges[minDisID][j] < distance[j]) //直接走vs间接走
			{
				distance[j] = distance[minDisID] + g.edges[minDisID][j];
				path[j] = minDisID;
			}
	}
	
	// 返回结果
	DijkstraResult result;
	for(int i=0;i< g.size;i++)
	{
		result.distance[i] = distance[i];
		result.path[i] = path[i];
	}
	return result;
	
}

struct FloydResult {int W[MAX_V][MAX_V];int R[MAX_V][MAX_V];};
auto floyd(const MatrixGraph g) 
{
	constexpr int NO_WAY = -1; // 这里由于书上以1作为下标开始,有点乱,以-1表示不可达到,0为第一个节点
	
	int W[MAX_V][MAX_V];
	int prevW[MAX_V][MAX_V];
	int R[MAX_V][MAX_V];

	
	for(int i=0;i< g.size;i++)
	for(int j=0;j< g.size;j++)
	{
		W[i][j] = g.edges[i][j];
		R[i][j] = (W[i][j] == INF || W[i][j] ==0)?NO_WAY:j; 
		prevW[i][j] = W[i][j];
	}
		
	// 以mid为中点更新W
	for(int mid = 0; mid < g.size; mid++)
	{
		for(int i = 0; i < g.size; i++)
		for(int j = 0; j < g.size; j++)
			if(prevW[i][mid]!=INF && prevW[mid][j] !=INF )
			if(prevW[i][mid]+prevW[mid][j] < prevW[i][j])
			{
				W[i][j] = prevW[i][mid]+prevW[mid][j];
				R[i][j] = mid;
			}

		for(int i=0;i< g.size;i++) 
		for(int j=0;j< g.size;j++)
			prevW[i][j] = W[i][j];	
	}
	
	
	FloydResult result;
	for(int i = 0; i < g.size; i++)
	for(int j = 0; j < g.size; j++)
	{
		result.W[i][j] = W[i][j];
		result.R[i][j] = R[i][j];
	}
	return result;
	
}

struct FloydPathResult {queue<int> path;int distance=INF;};
void getFloydPath(const int W[MAX_V][MAX_V], const int R[MAX_V][MAX_V], int from, const int to, struct FloydPathResult& result)
{
	// cout << "from " << from << " to " << to << endl; 
	if(from == to)
		return;
	result.path.push(R[from][to]);
	getFloydPath(W, R, R[from][to] , to, result);
}



namespace MenuActions
{
	void usePrim(MatrixGraph& graph)
	{
		cout << "Prim:" << endl;
		auto tree = prim(graph);
		tree.show(false);
		cout << "Weight=" << tree.getWeight() << endl;
	}
	void useKruskal(MatrixGraph& graph)
	{
		cout << "Kruskal:" << endl;
		auto tree = kruskal(graph);
		tree.show(false);
		cout << "Weight=" << tree.getWeight() << endl;
	}
	void useDijkstra(MatrixGraph& graph)
	{
		auto dijkstraResult = dijkstra(graph);
		cout << "Dijkstra:" << endl;
		puts("distance:");
		showMatrix(&dijkstraResult.distance, "%3d ", 1, graph.size);
		puts("path array:");
		showMatrix(&dijkstraResult.path, "%3d ",1, graph.size);
		puts("path:");
		for(int i=0;i< graph.size;i++)
		{
			cout << i << ": ";
			stack<int> s;
			s.push(dijkstraResult.path[i]);
			
			int j = i;
			while(dijkstraResult.path[j] != 0)
			{
				j = dijkstraResult.path[j];
				s.push(dijkstraResult.path[j]);
			}
			while(s.size()>0){
				printf("%2d ",s.top());
				s.pop();
			}	
			
			cout << endl;
		}	
	}
	void useFloyd(MatrixGraph& graph)
	{

		auto floydResult = floyd(graph);
		puts("W:");
		showMatrix(floydResult.W,"%3d ",graph.size,graph.size);
		puts("R:");
		showMatrix(floydResult.R,"%3d ",graph.size,graph.size);
		
		queue<int> path;
		struct FloydPathResult t {.path=path,.distance=INF};
		
		int from;
		int to;
		cout << "from where?" << endl;
		cin >> from;
		cout << "to where?" << endl;
		cin >> to;
		
		 
		getFloydPath(floydResult.W, floydResult.R, from, to, t);
		
		cout << "Path is: " ;
		cout << from ;
		while(t.path.size() > 0)
		{
			cout  << " -> " << t.path.front();
			t.path.pop();
		}	
		cout << endl;
	}
		
}


int main()
{
	//P232 图8.26 Dijkstra示例
	MatrixGraph graph_232 = {
		.edges = {
		    {0,   6,    12, INF, INF, INF},
		    {INF, 0,     9,   3, INF, INF},
		    {INF, INF,   0, INF, 5  , INF},
		    {INF, INF,   4,   0, 13 , 15 },
		    {INF, INF, INF, INF, 0  , 4  },
		    {INF, INF, INF, INF, INF, 0  }
		},
		.info = {'a', 'b', 'c', 'd', 'e', 'f'},
		.size = 6
	};
	//P238 A_{-1} Floyd示例
	MatrixGraph graph_238 = {
		.edges = {
			{0,     5,   INF, 7},
			{INF,   0,   4,   2},
			{3,     3,   0,   2},
			{INF, INF,   1,   0}
		},
		.info = {'a', 'b', 'c', 'd'},
		.size = 4
	};
	
	// P226 下方Prim和Kruskal示例(无向)
		MatrixGraph graph_226 = {
			.edges = { 
				{  0,  6,  1,   5,  INF, INF},
				{  6,  0,  5, INF,    3, INF},
				{  1,  5,  0,   5,    6,   4},
				{  5,INF,  5,   0,  INF,   2},
				{INF,  3,  6, INF,    0,   6},
				{INF,INF,  4,   2,    6,   0}
			},
			.info = {'a', 'b', 'c', 'd', 'e', 'f'},
			.size = 6
		};
	
	MatrixGraph* pGraph;
	pGraph = &graph_232;
	
	string names[16] = {
		"0. 选择图",
		"1. 显示邻接矩阵",
		"2. Prim 最小生成树",
		"3. Kruskal 最小生成树",
		"4. Dijkstra 最短路径",
		"5. Floyd 最短路径",
		"6. 退出"
	};
	
	while(true)
	{
		system("cls");
		cout << "------------菜单----------------" << endl;
		for(int i=0;i<7;i++)
			cout << names[i] <<endl;
		cout << "--------------------------------" << endl;
		
		cout << endl << endl;
		
		cout << "输入:";
		int input;
		cin >> input;
		
		system("cls");
		switch (input) {
			case 1:
				pGraph->show();
				break;
			case 2:
				MenuActions::usePrim(*pGraph);
				break;
			case 3:
				MenuActions::useKruskal(*pGraph);
				break;
			case 4:
				MenuActions::useDijkstra(*pGraph);
				break;
			case 5:
				MenuActions::useFloyd(*pGraph);
				break;
			case 0:
				MatrixGraph* atlas[3];
				atlas[0] = &graph_232;
				atlas[1] = &graph_238;
				atlas[2] = &graph_226;
				
				cout << "选哪张图?" << endl;
				cout << "0. 教材P232 图8.26 Dijkstra示例" << endl;
				cout << "1. 教材P238 A_-1 Floyd示例" << endl;
				cout << "2. 教材P226 下方 Prim和Kruskal示例" << endl;
				int chosen;
				cout << "输入:";
				cin >> chosen;
				
				pGraph = atlas[chosen];
				cout << "已换为: " << endl;
				pGraph->show();
				break;
			case 6:
				exit(0);
				break;
			default:
				cout << "输入有误" << endl;
				break;
		}
		system("pause");
	}
	
	return 0;	
}
