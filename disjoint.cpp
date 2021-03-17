#include <iostream>
#include <iterator>
#include <vector>
#include <unordered_map>

using namespace std;

class disjoint
{
private:
    vector<int> parent;
    vector<int> rank;//秩
public:
    disjoint(int size);
    ~disjoint();
    int find(int x){
        if (x == parent[x])
            return x;
        else{
            parent[x] = find(parent[x]);
            return parent[x];
        }
    };
    int unionSet(int x, int y){
        x = find(x);
        y = find(y);
        if (x == y)
            return 0;
        if (rank[x] > rank[y]){
            parent[y] = x;
        }
        else{
            parent[x] = y;
            if (rank[x] == rank[y])
                rank[y]++;
        }
    }
    vector<vector<int>> serialize(){
        unordered_map<int, vector<int>> buffer;
        for (int i = 0; i < parent.size(); i++){
            if (buffer.find(parent[i]) == buffer.end())
                buffer[parent[i]] = vector<int>();
            buffer[parent[i]].push_back(i);
        }
        vector<vector<int>> ans;
        for (auto i = buffer.begin(); i != buffer.end(); i++){
            ans.push_back(i->second);
        }
        return ans;
    }
};

disjoint::disjoint(int size)
{
    rank = vector<int>(size, 0);
    parent = vector<int>(size);
    for (int i = 0; i < size; i++){
        parent[i] = i;
    }
}



disjoint::~disjoint()
{
}

int main(){
    disjoint disjoint(10);
    disjoint.unionSet(5, 6);
    disjoint.unionSet(7, 8);
    disjoint.unionSet(1, 8);
    vector<vector<int>> ans = disjoint.serialize();
    for (int i = 0; i < ans.size(); i++){
        copy(ans[i].begin(), ans[i].end(), ostream_iterator<int>(cout, " "));
        cout << endl;
    }
}
