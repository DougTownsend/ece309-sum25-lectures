#include <memory>
#include <iostream>
#include <vector>
#include <initializer_list>

template <typename T>
class BST{
    private:
    class BTNode{
        public:
        T data;
        std::shared_ptr<BTNode> left;
        std::shared_ptr<BTNode> right;
        std::shared_ptr<BTNode> parent;
        int height;
        BTNode() : left(nullptr), right(nullptr), parent(nullptr), height(0) {}
        BTNode(T d) : left(nullptr), right(nullptr), data(d), parent(nullptr), height(0) {}
        void update_height(){
            if(right && !left) height = right->height + 1;
            else if (left && !right) height = left->height + 1;
            else if (left && right) height = std::max(left->height, right->height) + 1;
            else height = 0;
        }

        int balance_factor(){
            int lht = -1;
            int rht = -1;
            if(left) lht = left->height;
            if(right) rht = right->height;
            return lht - rht;
        }

        void replace(std::shared_ptr<BTNode> to_replace, std::shared_ptr<BTNode> replace_with){
            if(to_replace == left) left = replace_with;
            else right = replace_with;
        }
        
        void print(){
            std::cout << data;
            if(parent) std::cout << " p:" << parent->data;
            else std::cout << " root";
            if(left) std::cout << " l:" << left->data;
            if(right) std::cout << " r:" << right->data;
            std::cout << " h:" << height << " b:" << balance_factor() << "\n";
        }
    };
    std::shared_ptr<BTNode> root;

    void rotate_right(std::shared_ptr<BTNode> n){
        auto l = n->left;
        l->parent = n->parent;
        n->parent = l;
        if(!l->parent) root = l;
        else l->parent->replace(n, l);
        if(l->right) {
            n->left = l->right;
            n->left->parent = n;
        }
        else n->left = nullptr;
        l->right = n;
        n->update_height();
    }

    void rotate_left(std::shared_ptr<BTNode> n){
        auto r = n->right;
        r->parent = n->parent;
        n->parent = r;
        if(!r->parent) root = r;
        else r->parent->replace(n, r);
        if(r->left) {
            n->right = r->left;
            n->right->parent = n;
        }
        else n->right = nullptr;
        r->left = n;
        n->update_height();
    }

    void balance(std::shared_ptr<BTNode> n){
        if(n->balance_factor() == 2){
            if(n->left->balance_factor() == -1) rotate_left(n->left);
            rotate_right(n);
        }
        else if(n->balance_factor() == -2){
            if(n->right->balance_factor() == 1) rotate_right(n->right);
            rotate_left(n);
        }
    }

    std::shared_ptr<BTNode> remove_node(std::shared_ptr<BTNode> curr){
        //Case 1, Leaf node
        if(!curr->left && !curr->right){
            if(!curr->parent) root = nullptr;
            else if(curr->parent->left == curr){
                curr->parent->left = nullptr;
            } else {
                curr->parent->right = nullptr;
            } return curr->parent;
        }

        //Case 2, 1 Child
        else if(!curr->left != !curr->right) {
            auto tmp = curr->left;
            if (!tmp) tmp = curr->right;
            if(!curr->parent){
                root = tmp;
                tmp->parent = nullptr;
            } else if(curr->parent->left == curr){
                curr->parent->left = tmp;
            } else {
                curr->parent->right = tmp;
            } 
            tmp->parent = curr->parent;
            return curr->parent;
        }

        //Case 3, 2 children
        else {
            auto s = curr->right;
            auto s_parent = curr;
            while(s->left){
                s_parent = s;
                s = s->left;
            }
            remove_node(s);
            s->left = curr->left;
            s->right = curr->right;
            if(curr->left) curr->left->parent = s;
            if(curr->right) curr->right->parent = s;
            if(curr->parent && curr->parent->left == curr) curr->parent->left = s;
            else if (curr->parent) curr->parent->right = s;
            else root = s;
            if(s->left) s->left->parent = s;
            auto old_parent = s->parent;
            s->parent = curr->parent;
            s->update_height();
            return old_parent;
        }
        return nullptr;
    }

    public:
    class iterator{
        private:
        std::vector<std::shared_ptr<BTNode>> stack;
        std::shared_ptr<BTNode> curr;
        public:

        iterator(std::shared_ptr<BTNode> p, std::shared_ptr<BTNode> root){
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
                curr = stack.back();
                stack.pop_back();
                while(child != curr->left){
                    child = curr;
                    if(stack.empty()){
                        curr = nullptr;
                        break;
                    }
                    curr = stack.back();
                    stack.pop_back();
                }
            }
            return *this;
        }
    };

    BST() : root(nullptr) {}

    BST(std::initializer_list<T> l) : root(nullptr) {
        for(auto &i : l) insert(i);
    }

    ~BST(){
        while(root) remove(root->data);
    }

    BST(BST &other){
        for(auto &i : other) insert(i);
    }

    BST& operator= (BST& other){
        for(auto &i : other) insert(i);
        return *this;
    }

    iterator begin(){
        if (!root) return nullptr;
        auto n = root;
        while(n->left) n = n->left;
        return iterator(n, root);
    }

    iterator end(){
        return nullptr;
    }

    std::shared_ptr<BTNode> insert(T d){
        auto n = std::make_shared<BTNode>(d);
        if(!root){
            root = n;
        } else {
            auto curr = root;
            while(curr){
                if(d < curr->data){
                    if (!curr->left){
                        curr->left = n;
                        break;
                    }
                    curr = curr->left;
                } else {
                    if(!curr->right){
                        curr->right = n;
                        break;
                    }
                    curr = curr->right;
                }
            }
            n->parent = curr;
            while(curr){
                curr->update_height();
                balance(curr);
                curr = curr->parent;
            }
        }
        return n;
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
        auto curr = root;
        if(!root) return false;
        while(curr && curr->data != d){
            if(d < curr->data){
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
        if(!curr) return false;
        auto n = remove_node(curr);
        while(n){
            n->update_height();
            balance(n);
            n = n->parent;
        }
        return true;
    }

    void print(){
        print_helper(root);
    }

    void print_helper(std::shared_ptr<BTNode> n){
        if(!n) return;
        print_helper(n->left);
        n->print();
        print_helper(n->right);
    }
};