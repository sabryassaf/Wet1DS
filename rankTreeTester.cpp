/*
 * A Rank/AVL Tree Tester to test your tree implementation
 *
 * Please Read the instructions in the README file before you start

 * You may add any additional functions you need.
 *
 * I would suggest first beginning with a simple tree and then moving on to a more complex one.
 *
 * G O O D  L U C K !
 */

#include <iostream>
#include <vector>
#include <ostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <memory>
#include <assert.h>
#include "RankTree.h"

/*
 * is_tree_valid - checks if the tree is valid, meaning that the tree is balanced and the rank is correct
 * @param root - the root of the tree
 * @return true if the tree is valid, false otherwise
 * Should use to make sure your tree is valid after every insertion and deletion
 * If your Node class doesn't use a parent pointer, remove lines 66-84
 * If your tree isn't a Rank Tree, remove lines 56-60
 * if assert happens, put breaking points in "return false" to see where the error is
 */

template<class Key, class Value>
bool is_tree_valid(AVLNode<Key, Value> *root) {
    if (!root) {
        return true;
    }
    // Checks the height of every node is valid
    if (root->getHeight() != 1 + std::max(getHeight(root->getLeftChild()), getHeight(root->getRightChild()))) {
        std::cout << "Height is not valid" << std::endl;
        return false;
    }
    if (!root->getLeftChild() && !root->getRightChild() && root->getHeight() != 0) {
        std::cout << "Leaf Height is not valid" << std::endl;
        return false;
    }
    //checks the Tree is a Binary Search Tree
    if (root->getLeftChild() && root->getLeftChild()->getKey() >= root->getKey()) {
        std::cout << "Left son is not smaller than root" << std::endl;
        return false;
    }
    if (root->getRightChild() && root->getRightChild()->getKey() <= root->getKey()) {
        std::cout << "Right son is not bigger than root" << std::endl;
        return false;
    }
    //checks that the rank of every node is valid
//    if (root->weight != 1 + getWeight(root->left_son) + getWeight(root->right_son)) {
//        std::cout << "Rank is not valid" << std::endl;
//        return false;
//    }
    //checks that the Balance Factor of every node is valid
    if (std::abs(root->getBalanceFactor()) > 1) {
        std::cout << "Balance Factor is not valid" << std::endl;
        return false;
    }
    //checks that the parent pointer is valid
    if (root->getParent()) {
        if (root->getParent()->getLeftChild() != root && root->getParent()->getRightChild() != root) {
            std::cout << "Parent pointer is not valid" << std::endl;
            return false;
        }
    }
    if (root->getLeftChild()) {
        if (root->getLeftChild()->getParent() != root) {
            std::cout << "Parent's Left Son pointer is not valid" << std::endl;
            return false;
        }
    }
    if (root->getRightChild()) {
        if (root->getRightChild()->getParent() != root) {
            std::cout << "Parent's Right Son pointer is not valid" << std::endl;
            return false;
        }
    }
    return is_tree_valid(root->getLeftChild()) && is_tree_valid(root->getRightChild());
}

template<class Key, class Value>
int getHeight(AVLNode<Key, Value> *root) {
    if (!root) {
        return -1;
    }
    return root->getHeight();
}


template<class Key, class Value>
int BalanceFactor(AVLNode<Key, Value> *node) {
    if (node == nullptr) {
        return 0;
    }
    int Rheight = -1;
    int Lheight = -1;
    if (node->getRightChild() != nullptr) {
        Rheight = node->getRightChild()->getHeight();
    }
    if (node->getLeftChild() != nullptr) {
        Lheight = node->getLeftChild()->getHeight();
    }
    return Lheight - Rheight;
}

template<class Key, class Value>
int getWeight(AVLNode<Key, Value> *root) {
    if (!root) {
        return 0;
    }
    return root->weight;
}


// A function to print the tree
void print2DHelper(AVLNode<int,int> *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += 10;

    // Process right_son child first
    print2DHelper(root->getRightChild(), space);

    // Print current node after space
    std::cout<<std::endl;
    for (int i = 10; i < space; i++)
        std::cout<<" ";
    std::cout<<root->getData()<<"\n";

    // Process left_son child
    print2DHelper(root->getLeftChild(), space);
}

// Wrapper over print2DHelper()
void print2D(AVLNode<int,int> *root)
{
    // Pass initial space count as 0
    print2DHelper(root, 0);
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
}
int main(){
    RankTree<int,int> tree;
    std::vector<int> vector;
    int size = 0;
    int count = 0;
    //determines the size of the tree - change i to test different sizes
    for (int i = 1; i < 200; i++) {
        vector.push_back(i);
        size = i;
    }

    //randomizes the vector, and k is the number of trees to randomize - change k to test different numbers of trees
    for (int k = 1; k < 3; ++k) {
        count = k;
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle (vector.begin(), vector.end(), std::default_random_engine(seed));
        std::cout<<"\n     Creating The Tree \n"<<std::endl;
        for (std::vector<int>::iterator it = vector.begin() ; it != vector.end(); it++){
            tree.Insert(*it,*it);
            assert(is_tree_valid(tree.getRoot()));
            if(is_tree_valid(tree.getRoot())){}
            print2D(tree.getRoot());
        }
        std::cout<<"    Deleting The Tree \n"<<std::endl;
        shuffle (vector.begin(), vector.end(), std::default_random_engine(seed));
        for (std::vector<int>::iterator it = vector.begin() ; it != vector.end(); ++it){
            tree.Remove(*it);
            assert(is_tree_valid(tree.getRoot()));
            print2D(tree.getRoot());

        }
        if(k != 1){
            std::cout<<"A New Tree begins \n"<<std::endl;
        }
        tree.DeleteTree(tree.getRoot());
        tree.setRoot(nullptr);
    }
    std::cout<<" S U C C E S S"<<std::endl;
    std::cout << '\n';
    if(size < 100 && count < 6){
        std::cout << "Great! Now try a Larger Tree and more Trees " << std::endl;
        std::cout << '\n';
    }
    else if(size < 100){
        std::cout << "Great! Now try a Larger Tree " << std::endl;
        std::cout << '\n';
    }
    else if(count < 6){
        std::cout << "Great! Now try more Trees " << std::endl;
        std::cout << '\n';
    }
    else{
        std::cout << "    Great! " << std::endl;
        std::cout << '\n';
    }

    return 0;
}


