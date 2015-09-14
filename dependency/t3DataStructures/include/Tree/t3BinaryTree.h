#ifndef T3_BINARYTREE_H
#define T3_BINARYTREE_H

#include <Common/t3Test.h>
#include <LinearList/t3Stack.h>
#include <Common/t3DataStructuresSettings.h>
#include <iostream>

class t3TreeNode
{
public:
    t3TreeNode(int data, t3TreeNode* leftChild,  t3TreeNode* rigthChild):data(data), leftChild(leftChild), rightChild(rigthChild){}
    
    t3TreeNode(int data):data(data), leftChild(NULL), rightChild(NULL){}
    
    t3TreeNode():data(0), leftChild(NULL), rightChild(NULL){}
    
    int data;
    t3TreeNode *leftChild, *rightChild;
};

// 原计划将树设定为模板 不过为练手 这里简单的用int直接代替data数据类型
template <typename T>
class t3BinaryTree
{
public:
    t3BinaryTree();
    
    bool create(int preorder[], int inorder[], int length);

    void preorder();
    
    void inorder();
    
    void postorder();
    
    void levelorder();
    
    t3BinaryTree<T>* copy();
    
    // 等价性
    bool equal(t3BinaryTree<T> *tree);
    
    T *tree;
    
private:
    // 所有递归方法都被重封装
    T* preorder(T* root);
    
    T* inorder(T* root);
    
    T* postorder(T* root);
    
    // 指定树拷贝
    T* copy(T *tree);
    
    bool equal(T *first, T *second);
    
    // offset为当前子树的相对序号
    T* buildInorderPreorder(int preorder[], int length, int offset, bool bRoot);
    
    int mapIndex[T3_BINARTTREE_MAPINDEX_LENGTH];
};

template <typename T>
t3BinaryTree<T>::t3BinaryTree()
{
    
}

template <typename T>
bool t3BinaryTree<T>::create(int preorder[], int inorder[], int length)
{
    if(!preorder || !inorder)
    {
        t3PrintError("前序/中序序列不能为空");
        return false;
    }
    
    //int length = sizeof(preorder) / sizeof(preorder[0]);
    for(int i=0; i<length; i++)
    {
        // --!此处极其可能造成大量空间浪费
        mapIndex[inorder[i]] = i;
    }
    
    buildInorderPreorder(preorder, length, 0, true);
    
    return true;
}

template <typename T>
// offset为当前子树在先序序列中的起始序号
T* t3BinaryTree<T>::buildInorderPreorder(int preorder[], int length, int offset, bool bRoot)
{
    if(length == 0)
        return NULL;
    int rootValue = preorder[0];
    // 当前子树根节点相对序号
    int i = mapIndex[rootValue] - offset;
    
    T* root = new T(rootValue);
    root->leftChild = buildInorderPreorder(preorder+1, i, offset, false);
    root->rightChild = buildInorderPreorder(preorder+i+1, length - i - 1, offset + i + 1, false);
    
    // 是否为根
    if(bRoot)
        tree = root;
    
    return root;
}

template <typename T>
void t3BinaryTree<T>::preorder()
{
    preorder(tree);
}

template <typename T>
void t3BinaryTree<T>::inorder()
{
    inorder(tree);
}

template <typename T>
void t3BinaryTree<T>::postorder()
{
    postorder(tree);
}

template <typename T>
void t3BinaryTree<T>::levelorder()
{
    t3Stack<t3TreeNode*> stack;
    
    if(!tree)
        return;
    
    stack.push(tree);
    while(true)
    {
        if(stack.isEmpty())
            break;
        
        t3TreeNode *node = stack.pop();
        t3Log("% d ", node->data);
        if(node->leftChild)
            stack.push(node->leftChild);
        if(node->rightChild)
            stack.push(node->rightChild);
    }
}

template <typename T>
t3BinaryTree<T>* t3BinaryTree<T>::copy()
{
    t3BinaryTree* temp = new t3BinaryTree();
    temp->tree = copy(tree);
    return temp;
}

// 指定树拷贝
template <typename T>
T* t3BinaryTree<T>::copy(T *root)
{
    if(!root)
        return NULL;
    
    T *temp = new T();
    
    temp->data = root->data;
    temp->leftChild = copy(root->leftChild);
    temp->rightChild = copy(root->rightChild);
    
    return temp;
}

// 等价性
template <typename T>
bool t3BinaryTree<T>::equal(t3BinaryTree *root)
{
    return equal(tree, root->tree);
}

template <typename T>
bool t3BinaryTree<T>::equal(T *first, T *second)
{
    // 两者皆空 / 非空那么数据域要相同 / 递归左右子树
    return ((!first && !second) || (first && second && first->data == second->data) ||
            equal(first->leftChild, second->leftChild) ||
            equal(first->rightChild, second->rightChild));
}

template <typename T>
T* t3BinaryTree<T>::preorder(T* root)
{
    if(!root)
        return NULL;
    
    t3Log(" %d ", root->data);
    preorder(root->leftChild);
    preorder(root->rightChild);
    
    return root;
}

template <typename T>
T* t3BinaryTree<T>::inorder(T* root)
{
    if(!root)
        return NULL;
    
    inorder(root->leftChild);
    t3Log(" %d ", root->data);
    inorder(root->rightChild);
    
    return root;
}

template <typename T>
T* t3BinaryTree<T>::postorder(T* root)
{
    if(!root)
        return NULL;
    
    postorder(root->leftChild);
    postorder(root->rightChild);
    t3Log(" %d ", root->data);
    
    return root;
}

#endif
