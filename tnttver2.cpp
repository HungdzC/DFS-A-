#include<bits/stdc++.h>
using namespace std;

struct Node {
    int x, y;   
    int g;      
    int h;      
    Node* parent;
    Node(int x, int y, int g, int h, Node* parent1 = nullptr) : x(x), y(y), g(g), h(h), parent(parent1) {}
    bool operator<(const Node& other) const { 
        return g + h > other.g + other.h; 
    }
};

inline int TinhhamHeuritic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

inline bool Kiemtra(int x, int y, int rows, int cols, vector<vector<int>>& grid, vector<vector<bool>>& visited) {
    return x >= 0 && y >= 0 && x < rows && y < cols && grid[x][y] == 0 && !visited[x][y];
}

void Vet(Node* dich) {
    vector<pair<int, int>> path;
    Node* current = dich;
    while(current !=nullptr) {
        path.emplace_back(current->x, current->y);
        current = current->parent;
    }
    reverse(path.begin(), path.end());
    cout<<"Duong di tim thay: ";
    for(auto [x, y] : path) {
        cout<< "(" <<x<< ", "<<y<< ") ";
    }
    cout<<endl;
}

bool TimkiemAs(vector<vector<int>>& grid, vector<vector<bool>>& visited, Node bd, Node dich, int maxNodes, stack<Node*>& dfsStack){
    priority_queue<Node> pq;
    pq.emplace(bd.x, bd.y, bd.g, bd.h, nullptr);

    int nodeCount= 0;
    int rows= grid.size(), cols= grid[0].size();
    vector<pair<int, int>> directions= {{0, 1},{1, 0},{0, -1}, {-1, 0}};

    while(!pq.empty() && nodeCount < maxNodes) {
        Node current = pq.top();
        pq.pop();
        nodeCount++;

        if(current.x == dich.x && current.y == dich.y) {
            Vet(&current);
            return true;
        }
        visited[current.x][current.y] = true;

        for(auto [dx, dy] : directions) {
            int nx = current.x + dx, ny = current.y + dy;

            if(Kiemtra(nx,ny,rows,cols,grid,visited)){
                int newG= current.g + 1;
                int newH= TinhhamHeuritic(nx, ny, dich.x, dich.y);
                pq.emplace(nx, ny, newG, newH, new Node(current.x, current.y, current.g, current.h, current.parent));

            if(nodeCount >= maxNodes) {
                    dfsStack.push(new Node(nx, ny, newG, 0, nullptr));
                }
            }
        }
    }
    return false;
}
bool TimkiemDFS(vector<vector<int>>& grid, vector<vector<bool>>& visited, Node dich, stack<Node*>& dfsStack) {
    int rows= grid.size(), cols= grid[0].size();
    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    while(!dfsStack.empty()){
        Node* current = dfsStack.top();
        dfsStack.pop();

        if(current->x == dich.x && current->y == dich.y) {
            Vet(current);
            return true;
        }
        visited[current->x][current->y]= true;

        for(auto [dx, dy] : directions) {
            int nx = current->x + dx, ny = current->y + dy;

            if(Kiemtra(nx, ny, rows, cols, grid, visited)) {
                dfsStack.push(new Node(nx, ny, current->g + 1, 0, current));
            }
        }
    }
    return false;
}

void KethopAsvaDFS(vector<vector<int>>& grid, Node bd, Node dich) {
    int rows= grid.size(), cols = grid[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    stack<Node*> dfsStack;

    int totalNodes = 0;
    for(const auto& row : grid) {
        for(int cell : row) {
            if(cell == 0) totalNodes++;
        }
    }
    int halfNodes = totalNodes / 2;

    if(TimkiemAs(grid, visited, bd, dich, halfNodes, dfsStack)) {
        cout << "Tim thay duong di" << endl;
        return;
    }

    else if(TimkiemDFS(grid, visited, dich, dfsStack)) {
        cout << "Tim thay duong di" << endl;
        return;
    }
    cout << "Ko tim thay duong di" << endl;
}

int main(){
    int rows, cols;
    cout << "Nhap so hang cua ban do: ";
    cin >> rows;
    cout<<"Nhap so cot cua ban do: ";
    cin >> cols;
    vector<vector<int>> grid(rows, vector<int>(cols));
    cout << "Nhap map: \n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> grid[i][j];
        }
    }
    int bdX, bdY, dichX, dichY;
    cout << "Nhap toa do bat dau: ";
    cin >> bdX;
    cin>>bdY;
    cout << "Nhap toa do dich: ";
    cin >> dichX;
    cin >> dichY;
    Node bd(bdX, bdY, 0, TinhhamHeuritic(bdX, bdY, dichX, dichY));
    Node dich(dichX, dichY, 0, 0);
    KethopAsvaDFS(grid, bd, dich);
    return 0;
}
