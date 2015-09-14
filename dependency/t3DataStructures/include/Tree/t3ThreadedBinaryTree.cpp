#include <Tree/t3ThreadedBinaryTree.h>
t3ThreadTreeNode *previous;

t3ThreadedBinaryTree::t3ThreadedBinaryTree()
{
    
}

void t3ThreadedBinaryTree::inThreading()
{
    previous = NULL;
    inThreading(tree);
}

void t3ThreadedBinaryTree::inThreading(t3ThreadTreeNode *current)
{
    if(current)
    {
        inThreading(current->leftChild);
    
        // 空 / false
        if(!current->leftChild && !current->leftThread)
        {
            current->leftThread = true;
            current->leftChild = previous;
        }
        
        // 空 / 空 / false
        if(previous && !previous->rightChild && !previous->rightThread)
        {
            previous->rightThread = true;
            previous->rightChild = current;
        }
        
        previous = current;
        
        inThreading(current->rightChild);
    }
}

void t3ThreadedBinaryTree::inorder()
{
    if(!tree)
        return;
    
    t3ThreadTreeNode *h;
    h = tree;
    // 找到根的最左端
    while(!h->leftThread)
        h = h->leftChild;
    
    t3Log(" %d ", h->data);
    
    // 直到找到最后一个后继结点
    while(h->rightChild)
    {
        if(h->rightThread)
            h = h->rightChild;
        else
        {
            h = h->rightChild;
            
            // 找到该节点的最左端结点
            while(!h->leftThread)
                h = h->leftChild;
        }
        t3Log(" %d ", h->data);
    }
}

t3ThreadTreeNode* t3ThreadedBinaryTree::inSuccessor(t3ThreadTreeNode *root)
{
    if(!root)
    {
        t3PrintError("空指针没有后继结点");
        return NULL;
    }
    
    t3ThreadTreeNode *temp = root->rightChild;
    if(!root->rightThread)
        // 找到其最左端结点 即root的后继结点
        while(!temp->leftThread)
            temp = temp->leftChild;
    
    return temp;
}

void t3ThreadedBinaryTree::insertRight(t3ThreadTreeNode *parent, t3ThreadTreeNode *child)
{
    if(!parent || !child)
    {
        t3PrintError("插入二叉线索树中的子节点或父节点不能为空");
        return;
    }
    
    child->leftThread = true;
    child->leftChild = parent;
    child->rightChild = parent->rightChild;
    child->rightThread = parent->rightThread;
    
    parent->rightThread = false;
    parent->rightChild = child;
    
    // 看原父节点右边有无子节点
    if(!child->rightThread)
    {
        t3ThreadTreeNode *temp;
        // 找到后继
        temp = inSuccessor(child);
        temp->leftChild = child;
    }
}