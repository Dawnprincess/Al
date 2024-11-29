#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <string>
#include "../TestData.hpp"
#include "../TimeTracker.hpp"

using namespace std;

class Node {
public:
    int vertex, cost;

    Node(int v, int c) : vertex(v), cost(c) {}

    bool operator<(const Node &other) const {
        return cost > other.cost; // 小顶堆
    }
};

class Graph {
public:
    vector<vector<pair<int, int>>> adjList;

    Graph(int vertices) : adjList(vertices) {}

    void addEdge(int u, int v, int weight) {
        adjList[u].emplace_back(v, weight);
    }

    int shortestPath(int src, int dest) {
        priority_queue<Node> pq;
        vector<int> dist(adjList.size(), numeric_limits<int>::max());

        pq.emplace(src, 0);
        dist[src] = 0;

        while (!pq.empty()) {
            Node current = pq.top();
            pq.pop();

            int u = current.vertex;
            int cost = current.cost;

            if (u == dest) return cost;

            for (const auto &[v, weight] : adjList[u]) {
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.emplace(v, dist[v]);
                }
            }
        }

        return -1; // 无法到达目标节点
    }
};

void runAlgorithm(int vertices, int edges) {
    // 创建图
    Graph graph(vertices);

    // 使用TestData生成测试数据
    vector<vector<int>> testEdges = TestData::generateTwoDimensionalArray(edges, 2, 0, vertices - 1);
    vector<int> weights = TestData::generateOneDimensionalArray(edges, 1, 10);

    for (int i = 0; i < edges; ++i) {
        int u = testEdges[i][0];
        int v = testEdges[i][1];
        int weight = weights[i];
        graph.addEdge(u, v, weight);
    }

    // 从源节点0到目标节点vertices-1的最短路径
    graph.shortestPath(0, vertices - 1);
}

int main() {
    // 定义不同规模的测试用例
    vector<pair<int, int>> testCases = {
        {10, 15},   // 小规模
        {100, 500}, // 中规模
        {1000, 5000}, // 大规模
        {5000, 20000} // 超大规模
    };

    // 测试运行时间
    for (const auto &[vertices, edges] : testCases) {
        string functionName = "Test_" + to_string(vertices) + "_" + to_string(edges);
        cout << "正在测试图规模: 顶点数=" << vertices << " 边数=" << edges << endl;
        TimeTracker::measureTime(runAlgorithm, functionName, 1, vertices, edges);
        cout << "测试完成，结果已保存至 " << functionName << ".txt" << endl;
    }

    return 0;
}
