#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <climits>

using namespace std;

// Structure to represent a cell in the grid
struct Cell {
    int row, col;
    int f, g, h; // Values for A* algorithm
    bool obstacle;

    Cell(int row, int col) : row(row), col(col), f(INT_MAX), g(INT_MAX), h(INT_MAX), obstacle(false) {}
};

// Function to calculate the Manhattan distance heuristic between two cells
int calculateManhattanDistance(Cell* a, Cell* b) {
    return abs(a->row - b->row) + abs(a->col - b->col);
}

// A* algorithm function
void aStar(vector<vector<Cell*>>& grid, Cell* start, Cell* goal) {
    // Define priority queue for open set
    auto compare = [](Cell* a, Cell* b) { return a->f > b->f; };
    priority_queue<Cell*, vector<Cell*>, decltype(compare)> openSet(compare);

    // Initialize start node values
    start->g = 0;
    start->h = calculateManhattanDistance(start, goal);
    start->f = start->g + start->h;

    // Add start node to open set
    openSet.push(start);

    // Main loop
    while (!openSet.empty()) {
        // Get the cell with the lowest f value from the open set
        Cell* current = openSet.top();
        openSet.pop();

        // Check if current cell is the goal
        if (current == goal) {
            cout << "Path found!" << endl;
            return;
        }

        // Process neighbors
        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                // Skip diagonal neighbors and current cell
                if ((dr == 0 && dc == 0) || (dr != 0 && dc != 0)) continue;

                int newRow = current->row + dr;
                int newCol = current->col + dc;

                // Check if neighbor is within grid bounds
                if (newRow < 0 || newRow >= grid.size() || newCol < 0 || newCol >= grid[0].size()) continue;

                Cell* neighbor = grid[newRow][newCol];

                // Skip obstacles or cells already evaluated
                if (neighbor->obstacle) continue;

                // Calculate tentative g value for neighbor
                int tentativeG = current->g + 1; // Assuming uniform cost

                // If this is a better path to the neighbor, update its values and add it to the open set
                if (tentativeG < neighbor->g) {
                    neighbor->g = tentativeG;
                    neighbor->h = calculateManhattanDistance(neighbor, goal);
                    neighbor->f = neighbor->g + neighbor->h;
                    openSet.push(neighbor);
                }
            }
        }
    }

    // If open set becomes empty without reaching the goal, no path exists
    cout << "Path not found!" << endl;
}

// Function to print the grid
void printGrid(const vector<vector<Cell*>>& grid) {
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            if (cell->obstacle) cout << " #";
            else cout << " .";
        }
        cout << endl;
    }
}

int main() {
    // Define grid dimensions
    int rows = 5, cols = 5;

    // Create grid
    vector<vector<Cell*>> grid(rows, vector<Cell*>(cols, nullptr));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = new Cell(i, j);
        }
    }

    // Add obstacles
    grid[1][1]->obstacle = true;
    grid[1][2]->obstacle = true;
    grid[2][2]->obstacle = true;
    grid[3][2]->obstacle = true;

    // Set start and goal cells
    Cell* start = grid[0][0];
    Cell* goal = grid[rows - 1][cols - 1];

    // Print initial grid
    cout << "Initial Grid:" << endl;
    printGrid(grid);

    // Run A* algorithm
    aStar(grid, start, goal);

    return 0;
}
