#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include "../TestData.hpp"
#include "../TimeTracker.hpp"

using namespace std;

class Graph {
public:
    vector<vector<pair<int, int>>> adjList;

    Graph(int vertices) : adjList(vertices) {}

    void addEdge(int u, int v, int weight) {
        adjList[u].emplace_back(v, weight);
    }

    int greedyShortestPath(int src, int dest) {
        int n = adjList.size();
        vector<int> dist(n, numeric_limits<int>::max());
        vector<bool> visited(n, false);

        dist[src] = 0;

        for (int i = 0; i < n; ++i) {
            // 找到当前未访问的节点中，距离源点最近的节点
            int u = -1;
            for (int j = 0; j < n; ++j) {
                if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                    u = j;
                }
            }

            if (u == -1 || dist[u] == numeric_limits<int>::max()) break;

            visited[u] = true;

            // 更新相邻节点的距离
            for (const auto &[v, weight] : adjList[u]) {
                if (!visited[v] && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }

        return dist[dest] == numeric_limits<int>::max() ? -1 : dist[dest];
    }
};

void runGreedyAlgorithm(int vertices, int edges) {
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
    graph.greedyShortestPath(0, vertices - 1);
}

int main() {
    // 定义不同规模的测试用例
    vector<pair<int, int>> testCases = {
        {10, 15},    // 小规模
        {100, 500},  // 中规模
        {1000, 5000}, // 大规模
        {5000, 20000} // 超大规模
    };

    // 测试运行时间
    for (const auto &[vertices, edges] : testCases) {
        string functionName = "Greedy_Test_" + to_string(vertices) + "_" + to_string(edges);
        cout << "正在测试图规模: 顶点数=" << vertices << " 边数=" << edges << endl;
        TimeTracker::measureTime(runGreedyAlgorithm, functionName, 1, vertices, edges);
        cout << "测试完成，结果已保存至 " << functionName << ".txt" << endl;
    }

    return 0;
}
