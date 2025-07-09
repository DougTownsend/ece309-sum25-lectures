#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <list>
#include <stack>
#include <queue>
#include <initializer_list>
#include <algorithm>
#include <limits>

class Graph{
    protected:
    std::size_t num_verts;
    const bool directed;
    const bool weighted;

    class Edge{
        public:
        Edge(unsigned int n, int w) : next(n), weight(w) {}
        unsigned int next;
        int weight;
        bool operator<(const Edge rhs) const{
            return next < rhs.next;
        }
    };

    public:
    Graph(unsigned int n) : num_verts(n), directed(false), weighted(false) {};
    Graph(unsigned int n, bool dir, bool weight = false) : num_verts(n), directed(dir), weighted(weight) {};
    virtual void add_edge(unsigned int, unsigned int, int) = 0;
    virtual int is_edge(unsigned int, unsigned int) = 0;
    virtual std::vector<Edge> adj_list(unsigned int) = 0;

    void print_dot(const char *fname){
        std::ofstream out(fname);
        if(directed) out << "di";
        out << "graph{\n";
        if(!directed){
            for(unsigned int i = 0; i < num_verts; i++){
                for(unsigned int j = i+1; j < num_verts; j++){
                    if(is_edge(i,j)){ out << "\t" << i << " -- " << j;
                        if(weighted){
                            out << "[label=\"" << is_edge(i,j) << "\"]";
                        }
                        out << ";\n";
                    }
                }
            }
        } else {
            for(unsigned int i = 0; i < num_verts; i++){
                for(unsigned int j = 0; j < num_verts; j++){
                    if(is_edge(i,j)){
                        out << "\t" << i << " -> " << j;
                        if(weighted){
                            out << "[label=\"" << is_edge(i,j) << "\"]";
                        }
                        out << ";\n";
                    } 
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

    void dijkstra(unsigned int start){
        std::vector<Edge> shortest;
        for(unsigned int i = 0; i < num_verts; i++){
            if(i == start)
                shortest.push_back({i, 0});
            else
                shortest.push_back({i, std::numeric_limits<int>::max()});
        }
        std::set<unsigned int> visited;
        while(visited.size() < num_verts){
            Edge closest_node(0, std::numeric_limits<int>::max());
            for(unsigned int i = 0; i < num_verts; i++){
                if(visited.find(i) == visited.end()
                    && shortest[i].weight < closest_node.weight){
                        closest_node.weight = shortest[i].weight;
                        closest_node.next = i;
                    }
            }
            visited.insert(closest_node.next);
            auto adj = adj_list(closest_node.next);
            for(auto &i: adj){
                if(shortest[closest_node.next].weight + i.weight < 
                    shortest[i.next].weight){
                        shortest[i.next].weight = shortest[closest_node.next].weight + i.weight;
                        shortest[i.next].next = closest_node.next;
                    }
            }
        }
        for(unsigned int i = 0; i < num_verts; i++){
            unsigned int curr = i;
            std::cout << i  << "\n";
            std::list<unsigned int> path;
            while(shortest[curr].next != curr){
                path.push_front(curr);
                curr = shortest[curr].next;
            }
            path.push_front(start);
            for (auto p : path){
                std::cout << p << " ";
            }
            std::cout << "distance: " << shortest[i].weight <<"\n";
        }
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
    std::vector<std::set<Edge>> verts;

    public:
    SparseGraph(unsigned int n, bool dir = false, bool weight = false) : 
        Graph(n, dir, weight), verts(n){};

    void add_edge(unsigned int a, unsigned int b, int weight = 1){
        Edge e(b, weight);
        verts[a].insert(e);
        if(!directed)
            verts[b].insert(e);
    }

    int is_edge(unsigned int a, unsigned int b){
        for(auto &i : verts[a]){
            if(i.next == b) return i.weight;
        }
        return 0;
    }

    std::vector<Edge> adj_list(unsigned int node){
        std::vector<Edge> v;
        for(auto &n : verts[node]){
            v.push_back(n);
        }
        return v;
    }
};

class DenseGraph : public Graph{
    protected:
    std::vector<std::vector<int>> verts;

    public:
    DenseGraph(unsigned int n, bool dir = false, bool weight = false) : 
    Graph(n, dir, weight), verts(n) {
        for(auto &v : verts) v.resize(n);
    }

    void add_edge(unsigned int a, unsigned int b, int weight = 1){
        verts[a][b] = weight;
        if(!directed)
            verts[b][a] = weight;
    }

    int is_edge(unsigned int a, unsigned int b){
        return verts[a][b];
    }

    std::vector<Edge> adj_list(unsigned int node){
        std::vector<Edge> v;
        for(unsigned int i = 0; i < verts[node].size(); i++){
            if(verts[node][i]){
                Edge e(i, verts[node][i]);
                v.push_back(e);
            }
        }
        return v;
    }
};

int main(){
    SparseGraph s(6, true, true);
    s.add_edge(0,1, 1);
    s.add_edge(0,5, 6);
    s.add_edge(1,4,10);
    s.add_edge(1,5,2);
    s.add_edge(5,2,1);
    s.add_edge(5,3,3);
    s.add_edge(5,4,5);
    s.add_edge(3,2,6);
    s.add_edge(0,3,12);
    s.print_dot("test.dot");
    s.dijkstra(0);

    
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