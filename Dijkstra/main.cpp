#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include <fstream>
#include <string>
#include <cfloat>
#include <cstring>

using namespace std;

#define V 16

//Keeps track of the minimum distance between nodes
int minDist(double dist[], bool sptSet[])
{
    double min = DBL_MAX;
    int min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    return min_index;
}

//Recursive function that prints the pathing between nodes
void getPath(int parent[], int j, int destination, string nameList[])
{
    if (parent[j] == -1)
        return;

    getPath(parent, parent[j], destination, nameList);

    cout << nameList[j] << endl;

    if (j != destination) {
        cout << nameList[j] << " to ";
    }
}

//prints the source node and part of the text for total distance
void print(double dist[], int n, int parent[], int destination, int source, string nameList[])
{
    for (int i = 1; i < V; i++)
    {
        if (i == destination) {
            cout << nameList[source] << " to ";
            getPath(parent, i, destination, nameList);
            cout << "Total distance: " << dist[i];
        }
    }
}

//The algortithm itself
void dijkstra(double graph[V][V], int source, int destination, string nameList[])
{
    double dist[V];
    bool vCheck[V];
    int parent[V];

    for (int i = 1; i < V; i++)
    {
        parent[source] = -1;
        dist[i] = DBL_MAX;
        vCheck[i] = false;
    }

    dist[source] = 0;

    for (int count = 1; count < V - 1; count++)
    {

        int u = minDist(dist, vCheck);


        vCheck[u] = true;

        for (int v = 1; v < V; v++)
            if (!vCheck[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v])
            {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
    }

    print(dist, V, parent, destination, source, nameList);
}

//Fills the matrix up with zeros
void blankGraph(double adj[V][V])
{
    int i = 0;
    int e = 0;

    while (i < V) {
        while (e < V) {
            adj[i][e] = 0;
            e++;
        }
        i++;
        e = 0;
    }
}

int main()
{
    double adj[V][V];
    ifstream file("Anchorage Nodes.txt");
    string totalNodes;
    string currentNode;
    string nodeEdges;
    string name;
    string neighborNode;
    string distance;
    string nNDistance;
    char arr[90];

    getline(file, totalNodes);

    blankGraph(adj);

    int i = 0;
    string nameList[V];

    //Receives Data from input in the given txt file format and turns it into an adjacency matrix
    while (i < stoi(totalNodes)) {
        getline(file, currentNode);
        getline(file, name);
        nameList[i + 1] = name;
        getline(file, nodeEdges);
        int j = 0;
        while (j < stoi(nodeEdges)) {
            getline(file, nNDistance);
            strcpy(arr, nNDistance.c_str());
            neighborNode = strtok(arr, " ");
            distance = strtok(NULL, " ");
            adj[stoi(currentNode)][stoi(neighborNode)] = stod(distance);
            j++;
        }
        i++;
    }

    char loop = 'y';

    //Skeleton for outputting dijkstra algorithm
    //Keeps loop running until user intputs n to stop the program
    while (loop == 'y') {
        cout << "Locations:" << endl;

        for (int i = 1; i < V; i++) {
            cout << i << " " << nameList[i] << endl;
        }

        cout << "Please enter source location number: ";
        int source;
        cin >> source;
        while (std::cin.fail() || source < 1 || source > 15) {
            std::cin.clear();
            cin.ignore(10000, '\n');
            cout << "Error: Invalid input" << endl << "Please enter a valid source location number : ";
            cin >> source;
        }

        cout << "Please enter destination location number: ";
        int destination;
        cin >> destination;
        while (std::cin.fail() || destination < 1 || destination > 15) {
            std::cin.clear();
            cin.ignore(10000, '\n');
            cout << "Error: Invalid input" << endl << "Please enter a valid destination location number : ";
            cin >> destination;
        }

        dijkstra(adj, source, destination, nameList);

        cout << endl << "Go again? y/n" << endl;
        cin >> loop;
        while (std::cin.fail() || (loop != 'y' && loop != 'n')) {
            std::cin.clear();
            cin.ignore(10000, '\n');
            cout << "Error: Invalid input" << endl << "Please enter \"y\" for yes or \"n\" for no : ";
            cin >> loop;
        }
    }

    return 0;
}