#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
    int left;
    int right;
};

vector<Node> tree;
vector<int> depth;

void calculateDepth(int n) {
    depth.assign(n + 1, 0);
    queue<int> q;
    
    // Root is node 1
    depth[1] = 1;
    q.push(1);
    
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        
        if (tree[current].left != -1) {
            depth[tree[current].left] = depth[current] + 1;
            q.push(tree[current].left);
        }
        
        if (tree[current].right != -1) {
            depth[tree[current].right] = depth[current] + 1;
            q.push(tree[current].right);
        }
    }
}

void swapAtDepth(int current, int k, int currentDepth) {
    if (current == -1) return;
    
    // If current depth is a multiple of k, swap children
    if (currentDepth % k == 0) {
        swap(tree[current].left, tree[current].right);
    }
    
    // Recursively process children
    swapAtDepth(tree[current].left, k, currentDepth + 1);
    swapAtDepth(tree[current].right, k, currentDepth + 1);
}

void inorderTraversal(int current, vector<int>& result) {
    if (current == -1) return;
    
    inorderTraversal(tree[current].left, result);
    result.push_back(current);
    inorderTraversal(tree[current].right, result);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    tree.resize(n + 1);
    
    for (int i = 1; i <= n; i++) {
        cin >> tree[i].left >> tree[i].right;
    }
    
    int t;
    cin >> t;
    
    vector<int> queries(t);
    for (int i = 0; i < t; i++) {
        cin >> queries[i];
    }
    
    // Process each query
    for (int k : queries) {
        swapAtDepth(1, k, 1);
        
        vector<int> result;
        inorderTraversal(1, result);
        
        // Output inorder traversal
        for (int i = 0; i < result.size(); i++) {
            if (i > 0) cout << " ";
            cout << result[i];
        }
        cout << "\n";
    }
    
    return 0;
}