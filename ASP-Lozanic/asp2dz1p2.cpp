//
// Created by akith on 10/21/2023.
//


namespace SkupSpace {
    struct Node {
        Node *left = nullptr;
        Node *right = nullptr;
        int info = 0;
    };

    class Skup {


    public:
        Node *root;

        Skup() {
            root = nullptr;
        }

        void init(int val){
            root = new Node;
            root->info = val;

        }
//        void add(Node *rootadd, Node *left, Node *right) {
//            this->root->left = left;
//            this->root = rootadd;
//            this->root->right = right;
//
//        }


    };


}