// Richard Perez
// CPSC 335 project 3, problem 1

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

int burningTrees(std::vector<std::vector<int>>& forest) {
    int a = forest.size();
    int b = forest[0].size();
    int days = 0;    
    std::vector<int> directions = {-1, 0, 1, 0, -1, 0};
    std::queue<std::pair<int, int>> q;
    int healthyTrees = 0;

    // making the queue with all initially burned trees (2s)
    // and count the total number of healthy trees (1s)
    for (int i = 0; i < a; ++i) {
        for (int j = 0; j < b; ++j) {
            if (forest[i][j] == 2) {
                q.push({i, j});
            } else if (forest[i][j] == 1) {
                healthyTrees++;
            }
        }
    }
    // can't burn healthy trees without a dead tree already so check 
    if (q.empty()) {
        if (healthyTrees == 0) {
            return 0;
        } else return -1;
    }
    // with a Bread First Search I can the spread the fire
    while (!q.empty() && healthyTrees > 0) {
        int size = q.size();
        days++;
        // burning the healthy trees
        for (int i = 0; i < size; ++i) {
            std::pair<int, int> front = q.front();
            q.pop();
            for (int d = 0; d < 4; ++d) {
                int x = front.first + directions[d];
                int y = front.second + directions[d + 1];
                if (x >= 0 && y >= 0 && x < a && y < b && forest[x][y] == 1) {
                    forest[x][y] = 2;
                    healthyTrees--;
                    q.push({x, y});
                }
            }
        }
    }
    // checking if there are still healthy trees
    if (healthyTrees == 0) {
        return days;
    } else return -1;
}
int main() {
    int m, n;
    // getting the matrix 
    std::cout << "Enter the number of rows: ";
    std::cin >> m;
    std::cout << "Enter the number of columns: ";
    std::cin >> n;
    std::cout << "Enter the forest grid (0 for empty, 1 for healthy tree, 2 for burned tree): \n";
    std::vector<std::vector<int>> forest(m, std::vector<int>(n));    
    
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> forest[i][j];
        }
    }
    // sending it to the function
    int result = burningTrees(forest);
    std::cout << "Minimum days to burn all trees: " << result << "\n";

    return 0;
}