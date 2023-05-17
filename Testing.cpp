#include <iostream>
#include "AVLTreeS.h"

int main() {
    try {
        AVLTree<Movie> avlTree;

        // Creating movie objects
        Movie movie1(1, "Movie 1", 4.5, 1000);
        Movie movie2(2, "Movie 2", 3.8, 500);
        Movie movie3(3, "Movie 3", 4.2, 800);
        Movie movie4(4, "Movie 4", 4.7, 1200);

        // Inserting movies into the AVL tree
        avlTree.insert(&movie1);
        avlTree.insert(&movie2);
        avlTree.insert(&movie3);
        avlTree.insert(&movie4);

        // Searching for a movie by ID
        Movie* searchResult = avlTree.search(3);
        if (searchResult != nullptr) {
            std::cout << "Movie found: " << searchResult->getTitle() << std::endl;
        }
        else {
            std::cout << "Movie not found." << std::endl;
        }

        // Removing a movie by ID
        bool removeResult = avlTree.remove(2);
        if (removeResult) {
            std::cout << "Movie removed successfully." << std::endl;
        }
        else {
            std::cout << "Movie removal failed." << std::endl;
        }

        // Clearing the AVL tree
        avlTree.clear();
        std::cout << "AVL tree cleared." << std::endl;

    }
    catch (const AVL_Tree_Exceptions& ex) {
        std::cout << "Exception: " << ex.what() << std::endl;
    }

    return 0;
}
