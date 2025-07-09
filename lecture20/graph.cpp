#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <list>
#include <stack>
#include <queue>
#include <initializer_list>
#include <algorithm>

class Graph{
    protected:
    std::size_t num_verts;
    const bool directed;

    public:
    Graph(unsigned int n) : num_verts(n), directed(false) {};
    Graph(unsigned int n, bool dir) : num_verts(n), directed(dir) {};
    virtual void add_edge(unsigned int, unsigned int) = 0;
    virtual bool is_edge(unsigned int, unsigned int) = 0;
    virtual std::vector<unsigned int> adj_list(unsigned int) = 0;

    void print_dot(const char *fname){
        std::ofstream out(fname);
        if(directed) out << "di";
        out << "graph{\n";
        if(!directed){
            for(unsigned int i = 0; i < num_verts; i++){
                for(unsigned int j = i+1; j < num_verts; j++){
                    if(is_edge(i,j)) out << "\t" << i << " -- " << j << ";\n";
                }
            }
        } else {
            for(unsigned int i = 0; i < num_verts; i++){
                for(unsigned int j = 0; j < num_verts; j++){
                    if(is_edge(i,j)) out << "\t" << i << " -> " << j << ";\n";
                }
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
        visit(start);
        while(!front.empty()){
            auto n = front.top();
            auto adj = adj_list(n);
            bool found = false;
            for(auto i : adj){
                if(disc.find(i) == disc.end()){
                    front.push(i);
                    visit(i);
                    disc.insert(i);
                    found = true;
                    break;
                }
            }
            if(!found){
                //visit(front.top());
                front.pop();
            }
        }
    }

    bool cycle_detect(unsigned int start){
        std::vector<unsigned int> front;
        std::set<unsigned int> disc;
        disc.insert(start);
        front.push_back(start);
        while(!front.empty()){
            auto n = front.back();
            auto adj = adj_list(n);
            bool found = false;
            for(auto i : adj){
                auto it = std::find(front.begin(), front.end(), i);
                if(it != front.end()){
                    while(it != front.end()){
                        std::cout << *it << ", ";
                        ++it;
                    }
                    std::cout << i << "\n";
                    return true;
                }
                if(disc.find(i) == disc.end()){
                    front.push_back(i);
                    disc.insert(i);
                    found = true;
                    break;
                }
            }
            if(!found){
                front.pop_back();
            }
        }
        return false;
    }
    
    template <typename T>
    std::set<unsigned int> dfs_recurse(unsigned int node, T& visit, std::set<unsigned int> disc = std::set<unsigned int>()){
        disc.insert(node);
        visit(node);
        auto adj = adj_list(node);
        for(auto i : adj){
            if(disc.find(i) == disc.end()){
                disc = dfs_recurse(i, visit, disc);
            }
        }
        return disc;
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
    SparseGraph(unsigned int n, bool dir = false) : Graph(n, dir), verts(n){};

    void add_edge(unsigned int a, unsigned int b){
        verts[a].insert(b);
        if(!directed)
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
    DenseGraph(unsigned int n, bool dir = false) : Graph(n, dir), verts(n) {
        for(auto &v : verts) v.resize(n);
    }

    void add_edge(unsigned int a, unsigned int b){
        verts[a][b] = true;
        if(!directed)
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
    SparseGraph s(7, true);
    s.add_edge(0,1);
    s.add_edge(0,3);
    s.add_edge(1,4);
    s.add_edge(4,2);
    s.add_edge(4,5);
    s.add_edge(5,2);
    s.add_edge(5,6);
    s.add_edge(3,4);
    //s.add_edge(6,3);
    Visit v;
    //s.shortest_path(0,  5);
    //std::cout << "\nnon-recursive\n";
    //s.dfs(4, v);
    //std::cout << "\nrecursive\n";
    //s.dfs_recurse(4, v);
    bool cycle = s.cycle_detect(0);
    std::cout << cycle << "\n";
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
    //d.print_dot("test.dot");
    //d.shortest_path(0,5);
    return 0;
}