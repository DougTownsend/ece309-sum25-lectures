#include <memory>
#include <iostream>
#include <vector>

template <typename T>
class BST{
    private:
    class BTNode{
        public:
        T data;
        std::shared_ptr<BTNode> left;
        std::shared_ptr<BTNode> right;
        BTNode() : left(nullptr), right(nullptr) {}
        BTNode(T d) : left(nullptr), right(nullptr), data(d) {}
    };
    std::shared_ptr<BTNode> root;

    bool remove_node(std::shared_ptr<BTNode> parent, std::shared_ptr<BTNode> curr){
        //Case 1, Leaf node
        if(!curr->left && !curr->right){
            if(parent->left == curr){
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            } return true;
        }

        //Case 2, 1 Child
        else if(!curr->left != !curr->right) {
            auto tmp = curr->left;
            if (!tmp) tmp = curr->right;
            if(parent->left == curr){
                parent->left = tmp;
            } else {
                parent->right = tmp;
            } return true;
        }

        //Case 3, 2 children
        else {
            auto s = curr->right;
            auto s_parent = curr;
            while(s->left){
                s_parent = s;
                s = s->left;
            }
            remove_node(s_parent, s);
            s->left = curr->left;
            s->right = curr->right;
            if(parent && parent->left == curr) parent->left = s;
            else if (parent) parent->right = s;
            else root = s;
            return true;
        }
        return false;
    }

    public:
    class iterator{
        private:
        std::vector<std::shared_ptr<BTNode>> stack;
        std::shared_ptr<BTNode> curr;
        public:

        iterator(std::shared_ptr<BTNode> p){
            auto n = root;
            while(p != n){
                stack.push_back(n);
                if(p->data < n->data){
                    n = n->left;
                } else {
                    n = n->right;
                }
            } 
            curr = n;
        }

        iterator& operator=(iterator& other){
            stack = other.stack;
            curr = other.curr;
            return *this;
        }

        iterator(std::nullptr_t){curr = nullptr;}

        const T& operator*(){
            return curr->data;
        }

    bool operator!=(iterator other){
            return other.curr != curr;
        }

        iterator& operator++(){
            if(curr->right){
                stack.push_back(curr);
                curr = curr->right;
                while(curr->left){
                    stack.push_back(curr);
                    curr = curr->left;
                }
            } else {
                auto child = curr;
                curr = stack.pop_back();
                while(child != curr->left){
                    child = curr;
                    curr = stack.pop_back();
                }
            }
            return *this;
        }
    };

    iterator begin(){
        if (!root) return nullptr;
        auto n = root;
        while(n->left) n = n->left;
        return n;
    }

    iterator end(){
        return nullptr;
    }

    void insert(T d){
        auto n = std::make_shared<BTNode>(d);
        if(!root){
            root = n;
        } else {
            auto curr = root;
            while(curr){
                if(d < curr->data){
                    if (!curr->left){
                        curr->left = n;
                        return;
                    }
                    curr = curr->left;
                } else {
                    if(!curr->right){
                        curr->right = n;
                        return;
                    }
                    curr = curr->right;
                }
            }
        }
    }

    bool search(T d){
        auto curr = root;
        while(curr){
            if (curr->data == d) return true;
            if(d < curr->data){
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
        return false;
    }

    bool remove(T d){
        std::shared_ptr<BTNode> parent = nullptr;
        auto curr = root;
        if(!root) return false;
        while(curr && curr->data != d){
            parent = curr;
            if(d < curr->data){
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
        if(!curr) return false;
        return remove_node(parent, curr);
    }

    void print(){
        print_helper(root);
    }

    void print_helper(std::shared_ptr<BTNode> n){
        if(!n) return;
        print_helper(n->left);
        std::cout << n->data << "\n";
        print_helper(n->right);
    }
};