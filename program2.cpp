// Richard Perez
// cpsc 335 Project 3 program 2

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

struct Node {
    int price;
    int city;
    int stops;
    Node(int a, int b, int c) {
        price = b;
        city = a;
        stops = c;
    }
};

int cheapRoute(int n, const std::vector<std::vector<int>>& routes, int src, int dst, int k) {
    // checking if route in  range
    if (dst >= n || dst < 0) {
        return -1;
    }    
    // building an adjcency list 
    std::vector<std::vector<std::pair<int, int>>> graph(n);
    for (const auto& route : routes) {
        graph[route[0]].emplace_back(route[1], route[2]);
    }
    std::queue<Node> q;
    q.emplace(src, 0, 0);
    // a 2d vector to track total min cost
    std::vector<std::vector<int>> min(n, std::vector<int>(k + 2, INT_MAX));
    min[src][0] = 0;

    while (!q.empty()) {
        Node current = q.front();
        q.pop();
        int cost = current.price;
        int location = current.city;
        int stops = current.stops;
        // if we got there then we are done
        if (stops > k) {
            continue;
        }
        // checking for no away routes continue to next 
        if (graph[location].empty()) {
            continue;
        }
        // checking the neighboring cities
        for (const auto& neighbor : graph[location]) {
            int next = neighbor.first;
            int price = neighbor.second;
            int current = cost + price;
            // if something cheaper is found with stops then change it
            if (current < min[next][stops + 1]) {
                min[next][stops + 1] = current;
                q.emplace(next, current, stops + 1);
            }
        }
    }
    int final = INT_MAX;
    for (int i = 0; i <= k + 1; ++i) {
        final = std::min(final, min[dst][i]);
    }
    if (final == INT_MAX) {
        return -1;
    } else return final;
}

int main() {
    // getting user input the call the function
    int numRoutes;
    std::cout << "Enter number of routes: ";
    std::cin >> numRoutes;
    std::vector<std::vector<int>> routes;
    int maxCity = 0;
    std::cout << "Enter routes: from, to, cost\n";
    for (int i = 0; i < numRoutes; ++i) {
        int from, to, cost;
        std::cin >> from >> to >> cost;
        routes.push_back({from, to, cost});
        maxCity = std::max(maxCity, std::max(from, to));
    }
    int src, dst, k;
    std::cout << "Enter src, dst, k\n";
    std::cin >> src >> dst >> k;
    int result = cheapRoute(maxCity + 1, routes, src, dst, k);
    std::cout << "Output:\n" << result << '\n';
    return 0;
}
