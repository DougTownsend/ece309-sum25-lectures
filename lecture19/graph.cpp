#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <list>
#include <stack>
#include <queue>
#include <initializer_list>

class Graph{
    protected:
    std::size_t num_verts;

    public:
    Graph(unsigned int n) : num_verts(n) {};
    virtual void add_edge(unsigned int, unsigned int) = 0;
    virtual bool is_edge(unsigned int, unsigned int) = 0;
    virtual std::vector<unsigned int> adj_list(unsigned int) = 0;

    void print_dot(const char *fname){
        std::ofstream out(fname);
        out << "graph{\n";
        for(unsigned int i = 0; i < num_verts; i++){
            for(unsigned int j = i+1; j < num_verts; j++){
                if(is_edge(i,j)) out << "\t" << i << " -- " << j << ";\n";
            }
        }
        out << "}\n";
    }
    
    bool is_path(std::vector<unsigned int> p){
        for(unsigned int i = 1; i < p.size(); i++){
            if(!is_edge(p[i], p[i-1])) return false;
        }
        return true;
    }

    template <typename T>
    void bfs(unsigned int start, T& visit){
        std::queue<unsigned int> front;
        std::set<unsigned int> disc;
        disc.insert(start);
        front.push(start);
        while(!front.empty()){
            unsigned int n = front.front();
            front.pop();
            visit(n);
            auto adj = adj_list(n);
            for(auto i : adj){
                if(disc.find(i) == disc.end()){
                    disc.insert(i);
                    front.push(i);
                }
            }
        }
    }

    template <typename T>
    void dfs(unsigned int start, T& visit){
        std::stack<unsigned int> front;
        std::set<unsigned int> disc;
        disc.insert(start);
        front.push(start);
        //visit(start);
        while(!front.empty()){
            auto n = front.top();
            auto adj = adj_list(n);
            bool found = false;
            for(auto i : adj){
                if(disc.find(i) == disc.end()){
                    front.push(i);
                    //visit(i);
                    disc.insert(i);
                    found = true;
                    break;
                }
            }
            if(!found){
                visit(front.top());
                front.pop();
            }
        }
    }

    void shortest_path(unsigned int start, unsigned int end){
        std::queue<unsigned int> front;
        std::set<unsigned int> disc;
        std::vector<unsigned int> preds(num_verts);
        disc.insert(start);
        front.push(start);
        while(!front.empty()){
            unsigned int n = front.front();
            front.pop();
            auto adj = adj_list(n);
            for(auto i : adj){
                if(disc.find(i) == disc.end()){
                    preds[i] = n;
                    disc.insert(i);
                    front.push(i);
                }
            }
        }
        std::list<unsigned int> path;
        auto curr = end;
        while(curr != start){
            path.push_front(curr);
            curr = preds[curr];
        }
        path.push_front(curr);
        for(auto i : path) std::cout << i << " ";
    }
};

class Visit{
    public:
    void operator() (unsigned int a){
        std::cout << a << " ";
    }
};

class SparseGraph : public Graph{
    protected:
    std::vector<std::set<unsigned int>> verts;

    public:
    SparseGraph(unsigned int n) : Graph(n), verts(n) {};

    void add_edge(unsigned int a, unsigned int b){
        verts[a].insert(b);
        verts[b].insert(a);
    }

    bool is_edge(unsigned int a, unsigned int b){
        if(verts[a].find(b) != verts[a].end()) return true;
        return false;
    }

    std::vector<unsigned int> adj_list(unsigned int node){
        std::vector<unsigned int> v;
        for(auto &n : verts[node]){
            v.push_back(n);
        }
        return v;
    }
};

class DenseGraph : public Graph{
    protected:
    std::vector<std::vector<bool>> verts;

    public:
    DenseGraph(unsigned int n) : Graph(n), verts(n) {
        for(auto &v : verts) v.resize(n);
    }

    void add_edge(unsigned int a, unsigned int b){
        verts[a][b] = true;
        verts[b][a] = true;
    }

    bool is_edge(unsigned int a, unsigned int b){
        return verts[a][b];
    }

    std::vector<unsigned int> adj_list(unsigned int node){
        std::vector<unsigned int> v;
        for(unsigned int i = 0; i < verts[node].size(); i++){
            if(verts[node][i]) v.push_back(i);
        }
        return v;
    }
};

int main(){
    SparseGraph s(7);
    s.add_edge(0,1);
    s.add_edge(0,3);
    s.add_edge(1,4);
    s.add_edge(4,2);
    s.add_edge(4,5);
    s.add_edge(5,2);
    s.add_edge(5,6);
    s.add_edge(3,4);
    Visit v;
    //s.shortest_path(0,  5);
    s.dfs(4, v);
    s.print_dot("test.dot");

    
    DenseGraph d(7);
    d.add_edge(0,1);
    d.add_edge(0,3);
    d.add_edge(1,4);
    d.add_edge(4,2);
    d.add_edge(4,5);
    d.add_edge(5,2);
    d.add_edge(5,6);
    d.add_edge(3,4);
    d.print_dot("test.dot");
    //d.shortest_path(0,5);
    return 0;
}