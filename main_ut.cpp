
#include "RankTree.h"

int main()
{

    RankTree<int, int> tree;
    int a = 5;
    int b = 10;
    int c = 15;
    int d = 20;
    int f = 100;
    int g = 23;
    int k = 3;
    int h = 2;
    int hg = 1;
    tree.Insert(a, a);
    tree.Insert(b, b);
    tree.Insert(c, c);
    tree.Insert(d, d);
    tree.Insert(f, f);
    tree.Insert(g, g);
    tree.Insert(k, k);
    tree.Insert(h, h);
    tree.Insert(hg, hg);
    int *arr = new int[tree.getSize()];
    tree.BuildInOrderArray(arr);
    for (int i = 0; i < tree.getSize(); i++)
    {
        std::cout << arr[i] << " " << std::endl;
    }

    tree.Remove(f);
    tree.Remove(g);
    tree.Remove(b);
    tree.Remove(k);
    tree.Insert(k, k);
    tree.Insert(f, f);
    tree.Remove(h);
    int *arr1 = new int[tree.getSize()];
    tree.BuildInOrderArray(arr1);
    for (int i = 0; i < tree.getSize(); i++)
    {
        std::cout << arr1[i] << " " << std::endl;
    }
    return 0;

}