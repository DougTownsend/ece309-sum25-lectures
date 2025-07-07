#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <initializer_list>

class Graph{
    protected:
    std::size_t num_verts;

    public:
    Graph(unsigned int n) : num_verts(n) {};
    virtual void add_edge(unsigned int, unsigned int) = 0;
    virtual bool is_edge(unsigned int, unsigned int) = 0;

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
    //s.print_dot("test.dot");
    
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

    std::cout << s.is_path({1,0,3,4,5}) << "\n";
    return 0;
}