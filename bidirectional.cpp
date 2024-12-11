#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int vertexNumber;
    vector<pair<int, int>> children;

    Node(int vertexNumber)
    {
        this->vertexNumber = vertexNumber;
    }

    void add_child(int vNumber, int length)
    {
        children.push_back({vNumber, length});
    }
};

vector<int> dijkstraDist(vector<Node *> g, int s, vector<int> &path)
{
    int n = g.size();
    vector<int> dist(n, INT_MAX);
    vector<bool> visited(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    dist[s] = 0;
    pq.push({0, s});

    while (!pq.empty())
    {
        int current = pq.top().second;
        pq.pop();

        if (visited[current])
            continue;
        visited[current] = true;

        for (auto &child : g[current]->children)
        {
            int v = child.first, weight = child.second;
            if (!visited[v] && dist[current] + weight < dist[v])
            {
                dist[v] = dist[current] + weight;
                path[v] = current;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

void printPath(vector<int> path, int i, int s)
{
    if (i == -1)
    {
        cout << "Path not found!";
        return;
    }
    if (i != s)
        printPath(path, path[i], s);
    cout << i << " ";
}

vector<int> user(int n) {
    vector<int> points(n); // Create a vector to store delivery points
    for (int i = 0; i < n; i++) {
        cout << "Enter delivery point " << i + 1 << ": ";
        cin >> points[i];
    }
    return points; // Return the vector
}

void printShortestTime(vector<int> dist, vector<int> points)
{
    int overallTime = 0;
    for (int i = 0; i < points.size(); i++)
    {
        cout << "Shortest time for dilivery point " << points[i] << " is : " << dist[points[i]] <<" min" ;
        cout << "\n";
        if (overallTime < dist[points[i]])
        {
            overallTime = dist[points[i]];
        }
    }
    cout << "Maximum time for dilivery can get is : "<< overallTime <<  " min";
}

int main()
{
    vector<Node *> v;
    int n = 100, s = 0;

    for (int i = 0; i < n; i++)
    {
        v.push_back(new Node(i));
    }

    v[0]->add_child(1, 1);
    v[0]->add_child(2, 4);
    v[1]->add_child(2, 2);
    v[1]->add_child(3, 6);
    v[2]->add_child(3, 3);

        for (int i = 3; i < n; i++) {
        if (i + 1 < n) {
            v[i]->add_child(i + 1, i); // Connect to the next node with weight = current index
        }
        if (i + 2 < n) {
            v[i]->add_child(i + 2, i * 2); // Connect to the next-next node with weight = 2 * current index
        }
    }

    vector<int> path(n, -1);
    vector<int> dist = dijkstraDist(v, s, path);

    int m;
    cout << "Enter the number of dilivery points : ";
    cin >> m;

    vector<int> points = user(m);

    printShortestTime(dist, points);
    
    // Free memory
    for (auto node : v)
        delete node;

    return 0;
}