#include <SparseMatrix/t3SparseMatrixADT.h>
#include <Common/t3Test.h>

// 创建一个最大能容纳maxRow x maxCol 非零元素个数count的稀疏矩阵 本质上是一维矩阵
void t3SparseMatrixADT::create(int maxRow, int maxCol, int itemCount)
{
    if(itemCount < 0)
    {
        t3PrintErrorArg("itemCount", itemCount, "非零元素个数不能小于0");
        
        count = 0;
        
        return;
    }
    
    // 额外一行用于存放头结点
    m = new term[itemCount+1]();
    
    // 头结点保存矩阵信息
    m[0].row = maxRow;
    m[0].col = maxCol;
    m[0].value = itemCount;
    
    count = 1;
}

t3SparseMatrixADT* t3SparseMatrixADT::transpose()
{
    if(m == NULL)
    {
        t3PrintError("矩阵未经过初始化 或 初始哈失败");
        return NULL;
    }
    
    t3SparseMatrixADT *t = new t3SparseMatrixADT();
    t->create(m[0].col, m[0].row, m[0].value);
    
    int num = m[0].value;
    if(num > 0)
    {
        // 遍历所有可能的列
        for(int i=0; i<m[0].col; i++)
        {
            // 在源矩阵中找到所有与当前列相同的元素
            for(int j=1; j<m[0].value+1; j++)
            {
                if(m[j].col == i)
                    t->add(m[j].col, m[j].row, m[j].value);
            }
        }
    }
    
    return t;
}

t3SparseMatrixADT* t3SparseMatrixADT::transposeFast()
{
    if(m == NULL)
    {
        t3PrintError("矩阵未经过初始化 或 初始哈失败");
        return NULL;
    }
    
    int num = m[0].value, numCol = m[0].col;
    
    // 每一列上元素个数 / 转置矩阵可被赋值的起始位置
    int *rowTerms = new int[numCol], *startingPos = new int[numCol];
    
    t3SparseMatrixADT *t = NULL;
    
    if(num > 0)
    {
        t = new t3SparseMatrixADT();
        t->create(numCol, m[0].row, m[0].value);
        
        // 初始化并计算每列上元素个数
        for(int i=0; i<numCol; i++)
            rowTerms[i] = 0;
        for(int i=0; i<num; i++)
            rowTerms[m[i].col]++;
        
        // 初始化startingPos
        startingPos[0] = 1;
        for(int i=1; i<numCol; i++)
            startingPos[i] = startingPos[i-1] + rowTerms[i-1];
        
        // 真转置
        for(int i=1; i<num+1; i++)
        {
            //暂时存储起始位置
            int j = startingPos[m[i].col]++;
            
//            for(int g=0; g<numCol; g++)
//                printf("%d ", startingPos[g]);
//            printf("\n");
            
            t->m[j].col = m[i].row;
            t->m[j].row = m[i].col;
            t->m[j].value = m[i].value;
            
//            printf("j=%d\n", j);
//            printf("%d  %d  %d", m[i].row, m[i].col, m[i].value);
//            printf("\n");
//            t->count++;
            
//            t->print();
        }
    }
    
    return t;
}

void t3SparseMatrixADT::add(int row, int col, int value)
{
    if(m == NULL || row > m[0].row || col > m[0].col || count >= m[0].row * m[0].col + 1)
    {
        t3PrintError("矩阵长度溢出 或 指定行列数有误 或 初始化失败");
        return;
    }
    
    m[count].row = row;
    m[count].col = col;
    m[count].value = value;
    
    count++;
}

// 在矩阵中添加一项<row, col, value>的拷贝
void t3SparseMatrixADT::add(term& t)
{
    if(m == NULL || t.row > m[0].row || t.col > m[0].col || count >= m[0].row * m[0].col + 1)
    {
        t3PrintError("矩阵长度溢出 或 指定行列数有误 或 初始化失败");
        return;
    }
        
    m[count].row = t.row;
    m[count].col = t.col;
    m[count].value = t.value;
    
    count++;
}

void t3SparseMatrixADT::print()
{
    t3Log("------------------------------------------\n");
    t3Log("        行        列        值\n");
    
    for(int i=0; i<m[0].value; i++)
    {
        t3Log("m[%d]    %d    %d    %d\n", i, m[i].row, m[i].col, m[i].value);
    }
}

void t3SparseMatrixADT::operator+(t3SparseMatrixADT& m)
{
    
}

void t3SparseMatrixADT::operator*(t3SparseMatrixADT& m)
{
    // 并没有写
}