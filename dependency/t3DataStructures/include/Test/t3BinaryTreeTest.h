#include <Tree/t3BinaryTree.h>
#include <Tree/t3ThreadedBinaryTree.h>

#include <Common/t3Test.h>
#include <iostream>
#include <string>

//#define T3_BINARYTREE_TEST
#define T3_THREADEDBINARYTREE_TEST

int main(int argc, char* argv[])
{
    int preorder[] = {7, 10, 4, 3, 1, 2, 8, 11};
    int inorder[] = {4, 10, 3, 1, 7, 11, 8, 2};
    int length = sizeof(preorder) / sizeof(preorder[0]);
    
#ifdef T3_BINARYTREE_TEST
    t3BinaryTree<t3TreeNode> tree;
    
    tree.create(preorder, inorder, length);
    
    t3Log("---------------------preorder---------------------\n");
    tree.preorder();
    
    t3Log("---------------------inorder---------------------\n");
    tree.inorder();
    
    t3Log("---------------------postorder---------------------\n");
    tree.postorder();
    
    t3Log("---------------------levelorder---------------------\n");
    tree.levelorder();
    
    t3BinaryTree<t3TreeNode> *root;
    root = tree.copy();
    root->inorder();
    
    t3Log("---------------------inorder---------------------\n");
    root->inorder();
    if(tree.equal(root))
        t3Log("equal() -> ==\n");
    else
        t3Log("equal() -> !=\n");
#endif
    
#ifdef T3_THREADEDBINARYTREE_TEST
    
    t3ThreadedBinaryTree tree;
    tree.create(preorder, inorder, length);
    tree.inThreading();
    t3Log("---------------------inorder---------------------\n");
    tree.inorder();
    t3ThreadTreeNode node(5);
    tree.insertRight(tree.tree, &node);
    t3Log("---------------------insert inorder---------------------\n");
    tree.inorder();
#endif
    getchar();

    return 0;
}