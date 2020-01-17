#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>
#include <iterator>
#include <sstream>
#include <stack>
#include <queue>
#include <algorithm> // for sorting

using namespace::std;



void printAdjList(vector<vector<int>> adjList, int N)
{
	cout << "adjList size: " << adjList.size() << endl;
	vector<int>::iterator iter;
	for (int i  = 0; i < N, i < adjList.size(); i++) {
		cout << "vertex " << i << ": ";
		for (iter = adjList.at(i).begin(); iter != adjList.at(i).end(); iter++) {
			if (iter != adjList.at(i).begin())
				cout << ", ";
			cout << *iter;
		}
		cout << endl;
	}
}

void bfs(int start, vector<vector<int>> graph, bool visited[])
{
	queue<int> q;
	q.push(start);
	visited[start] = true;
	while (!q.empty()) {
		int temp = q.front();
		q.pop();
		cout << " " << temp + 1;
		for (int i = 0; i < graph[temp].size(); i++) {
			if (visited[graph[temp][i]] == false) {
				q.push(graph[temp][i]);
				visited[graph[temp][i]] = true;
			}
		}
	}
	cout << endl;
}


void dfs(int start, vector<vector<int>> graph, bool visited[])
{
	stack<int> s;
	s.push(start);
	visited[start] = true;
	cout << " " << start + 1;

	while(!s.empty()) {
		int current = s.top();
		s.pop();
		for (int i = 0; i < graph[current].size(); i++) {
			int next = graph[current][i];

			if (visited[next] == false) {
				visited[next] = true;
				cout << " " << next + 1;
				s.push(current);
				s.push(next);
				break;
			}
		}
	}
	cout << endl;
}


vector<vector<int>> readInput(string fileName, int *N, int *M, int *V)
{
	vector<vector<int>> adjList;


	ifstream inFile(fileName);

	string firstLine;
	getline(inFile, firstLine);
	istringstream ss(firstLine);
	istream_iterator<int> intCursor(ss);

	*N = *intCursor;
	intCursor++;
	*M = *intCursor;
	intCursor++;
	*V = *intCursor - 1;
	intCursor++;

	cout << "N: " << *N << ", M: " << *M << ", V: " << *V << endl;

	//cur_line++;


	for (int i = 0; i < *N; i ++) {
		vector<int> row;
		adjList.push_back(row);
	}


	string buf;
	while (getline(inFile, buf)) {
		istringstream ss(buf);
		istream_iterator<int> intReader(ss);
		istream_iterator<int> intReaderEOF;

		while (true) {
			if (intReader != intReaderEOF) {
				int v = *intReader - 1;
				intReader++;
				int e = *intReader - 1;
				intReader++;
				cout << v << ", " << e << endl;
				adjList[v].push_back(e);
				adjList[e].push_back(v);
			} else {
				cout << endl;
				break;
			}
		}
	}

	for (int i = 0; i < *N; i++) {
		sort(adjList[i].begin(), adjList[i].end());
	}


	return adjList;
}

int main(void) 
{
	int N, M, V;
	vector <vector<int>> adjList = readInput("input", &N, &M, &V);
	cout << "N: " << N << ", M: " << M << ", V: " << V << endl;
	printAdjList(adjList, N);
	bool visited[N];
	dfs(V, adjList, visited);
	bool visited2[N];
	bfs(V, adjList, visited2);
	return 0;
}
