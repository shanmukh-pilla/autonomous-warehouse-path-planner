#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

const int ROWS = 10;
const int COLS = 10;

struct Node {

    int x;
    int y;
    int g;
    int h;
    int f;

    Node* parent;

};

struct Compare {

    bool operator()(Node* a, Node* b) {

        return a->f > b->f;

    }

};

int heuristic(int x1, int y1, int x2, int y2) {

    return abs(x1 - x2) + abs(y1 - y2);

}

bool isValid(int x, int y) {

    return x >= 0 && y >= 0 &&
           x < ROWS && y < COLS;

}

void printGrid(
    vector<vector<char>>& grid
) {

    cout << endl;

    for (auto& row : grid) {

        for (char cell : row) {

            cout << cell << " ";

        }

        cout << endl;

    }

}

int main() {

    vector<vector<char>> grid(ROWS,
        vector<char>(COLS, '.'));

    // Obstacles
    grid[3][3] = '#';
    grid[3][4] = '#';
    grid[3][5] = '#';
    grid[5][6] = '#';
    grid[6][6] = '#';
    grid[7][6] = '#';

    int startX = 0;
    int startY = 0;

    int goalX = 9;
    int goalY = 9;

    grid[startX][startY] = 'S';
    grid[goalX][goalY] = 'E';

    priority_queue<
        Node*,
        vector<Node*>,
        Compare
    > openList;

    vector<vector<bool>> visited(
        ROWS,
        vector<bool>(COLS, false)
    );

    Node* start = new Node{
        startX,
        startY,
        0,
        heuristic(startX, startY, goalX, goalY),
        0,
        nullptr
    };

    start->f = start->g + start->h;

    openList.push(start);

    Node* goalNode = nullptr;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!openList.empty()) {

        Node* current = openList.top();
        openList.pop();

        int x = current->x;
        int y = current->y;

        if (visited[x][y])
            continue;

        visited[x][y] = true;

        if (x == goalX && y == goalY) {

            goalNode = current;
            break;

        }

        for (int i = 0; i < 4; i++) {

            int nx = x + dx[i];
            int ny = y + dy[i];

            if (
                isValid(nx, ny) &&
                !visited[nx][ny] &&
                grid[nx][ny] != '#'
            ) {

                int g = current->g + 1;

                int h = heuristic(
                    nx,
                    ny,
                    goalX,
                    goalY
                );

                Node* neighbor = new Node{
                    nx,
                    ny,
                    g,
                    h,
                    g + h,
                    current
                };

                openList.push(neighbor);

            }

        }

    }

    // Draw path
    Node* path = goalNode;

    while (
        path != nullptr &&
        !(path->x == startX &&
          path->y == startY)
    ) {

        if (
            grid[path->x][path->y] != 'E'
        ) {

            grid[path->x][path->y] = '*';

        }

        path = path->parent;

    }

    printGrid(grid);

    cout << endl;
    cout << "Autonomous path planning completed."
         << endl;

    return 0;
}