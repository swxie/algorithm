#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <deque>
#include <iterator>

using namespace std;

class graph
{
private:
    vector<vector<int>> node;
    int node_count;
public:
    //用于从输入中构建图
    int build(){
        cout << "首先输入节点个数，然后每行输入每个节点的邻接节点" << endl;
        cin >> node_count;
        string buffer;
        getline(cin, buffer);
        node.clear();
        int count = node_count;
        while (count > 0){
            node.push_back(vector<int>());
            getline(cin, buffer);
            istringstream is(buffer);
            int temp;
            while (is >> temp){
                node[node.size() - 1].push_back(temp);
            }
            count--;
        }
        return 0;
    }
    //进行转置
    void transpose(){
        vector<vector<int>> temp(node.size());
        for (int i = 0; i < node.size(); i++){
            for (int j = 0; j < node[i].size(); j++){
                temp[node[i][j]].push_back(i);
            }
        }
        node = move(temp);
    }
    //给定节点，输出它到每个节点的最短距离
    vector<int> minDist(int src){
        vector<int> ans(node_count, -1);
        if (src >= node_count)
            return ans;
        ans[src] = 0;
        vector<int> visited(node_count, 0);
        visited[src] = 1;
        deque<int> buffer;
        for (int i = 0; i < node[src].size(); i++){
            buffer.push_back(node[src][i]);
            ans[node[src][i]] = 1;
        }
        while (!buffer.empty()){
            int this_node = buffer.front();
            for (int i = 0; i < node[this_node].size(); i++){
                int next_node = node[this_node][i];
                if (visited[next_node] == 1)
                    continue;
                visited[next_node] = 1;
                ans[next_node] = ans[this_node] + 1;
                buffer.push_back(next_node);
            }
            buffer.pop_back();
        }
        return ans;
    }
    //拓扑排序
    vector<int> sort(){
        vector<int> ans;
        vector<int> stack;
        //统计入度
        vector<int> inCount(node_count, 0);
        vector<int> visited(node_count, 0);
        for (int i = 0; i < node.size(); i++){
            for (int j = 0; j < node[i].size(); j++){
                inCount[node[i][j]]++;
            }
        }
        for (int i = 0; i < inCount.size(); i++){
            if (inCount[i] == 0)
                subSort(i, stack, visited);
        }
        return stack;
    }
private:
    void subSort(int node_index, vector<int> &stack, vector<int> &visited){
        if (visited[node_index] == 1)
            return;
        visited[node_index] = 1;
        for (int i = 0; i < node[node_index].size(); i++){
            subSort(node[node_index][i], stack, visited);
        }
        stack.push_back(node_index);
    }

};

int main(){
    graph graph;
    graph.build();
    vector<int> ans = graph.sort();
    copy(ans.begin(), ans.end(), ostream_iterator<int>(cout));
    cout << endl;
    graph.transpose();
    ans = graph.sort();
    copy(ans.begin(), ans.end(), ostream_iterator<int>(cout));
    cout << endl;
}
