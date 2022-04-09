#include <conio.h>
#include <iostream>
#include <fstream>
#include <limits.h>
#include <queue>
#include <string.h>
using namespace std;

#define V 8
int read_matrix(int matr[V][V]) {
	char line[2];
	ifstream in("l4-2.txt");
	printf("Розмiрнiсть матрицi: \n");
	if (in.is_open())
	{
		in.getline(line, 2);
		std::cout << line << std::endl;
		printf("Задана матриця: \n");
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				in >> matr[i][j];

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
				cout << matr[i][j] << "\t";
			cout << "\n";
		}

		in.close();
		printf("\n");
		return **matr;
	}
	else
	{
		cout << "Файл не знайдено.";
		return 0;
	}
}


bool search(int rGraph[V][V], int s, int t, int parent[])
{
	
	bool visit[V];
	memset(visit, 0, sizeof(visit));

	queue<int> q;
	q.push(s);
	visit[s] = true;
	parent[s] = -1;

	while (!q.empty()) {
		int u = q.front();
		q.pop();

		for (int v = 0; v < V; v++) {
			if (visit[v] == false && rGraph[u][v] > 0) {
				if (v == t) {
					parent[v] = u;
					return true;
				}
				q.push(v);
				parent[v] = u;
				visit[v] = true;
			}
		}
	}
	return false;
}

int Falkerson(int graph[V][V], int s, int t)
{
	int u, v;

	int rGraph[V]
		[V]; 
	for (u = 0; u < V; u++)
		for (v = 0; v < V; v++)
			rGraph[u][v] = graph[u][v];

	int parent[V]; 
	int max_f = 0; 
	cout << "Знайденi наскрiзнi потоки: ";
	while (search(rGraph, s, t, parent)) {
		int way_f = INT_MAX;
		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			way_f = min(way_f, rGraph[u][v]);
		}
		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			rGraph[u][v] -= way_f;
			rGraph[v][u] += way_f;
		}
		max_f += way_f;
		printf("%d ", way_f);
	}
	return max_f;
}

int main()
{
	setlocale(LC_ALL, "Ukrainian");
	int graph[V][V];
	read_matrix(graph);
	cout << "\nМаксимальний потiк = "
		<< Falkerson(graph, 0, 7);
	cout << "\n";
	system("pause");
}
