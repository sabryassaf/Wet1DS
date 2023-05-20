
#include "RankTree.h"

int main() {

	RankTree<int, int> tree;
	int a = 5;
	int b = 10;
	int c = 15;
	tree.Insert(a, a);
	tree.Insert(b, b);
	tree.Insert(c, c);
	tree.Remove(b);

	return 0;
}