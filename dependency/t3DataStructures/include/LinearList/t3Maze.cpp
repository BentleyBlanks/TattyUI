#include <LinearList/t3Maze.h>

#include <Common/t3Test.h>

class offsets
{
public:
    offsets():vert(0), horiz(0)
    {}
    
    offsets(int vert, int horiz):vert(vert), horiz(horiz)
    {}
    
    int vert;
    int horiz;
};

//enum t3MazeDirection
//{
//    N = 0,
//    NE,
//    E,
//    SE,
//    S,
//    SW,
//    W,
//    NW,
//    ALL_DIRECTION
//};

class compass
{
public:
    compass():row(0), col(0), direction(0)
    {}
    
    compass(int row, int col, int direction):row(row), col(col), direction(direction)
    {}
    
    friend std::ostream& operator<<(std::ostream& os, compass& c);

    int row;
    int col;
    int direction;
};

std::ostream& operator<<(std::ostream& os, compass& c)
{
    os << "row: " << c.row << ",col: " << c.col << ",dir: " << c.direction;
    return os;
}

void initMove(offsets* o)
{
    if(o)
    {
        o[0].vert = -1;
        o[0].horiz = 0;
        
        o[1].vert = -1;
        o[1].horiz = 1;
        
        o[2].vert = 0;
        o[2].horiz = 1;
        
        o[3].vert = 1;
        o[3].horiz = 1;
        
        o[4].vert = 1;
        o[4].horiz = 0;
        
        o[5].vert = 1;
        o[5].horiz = -1;
        
        o[6].vert = 0;
        o[6].horiz = -1;
        
        o[7].vert = -1;
        o[7].horiz = -1;
    }
}

t3Maze::t3Maze(int row, int col):m(NULL)//, std::ostream(NULL)
{
    m = new int*[row](); //开辟行
    for(int i = 0; i < row; i++)
        m[i] = new int[col](); //开辟列
    
    this->col = col;
    this->row = row;
    
    pCol = pRow = 0;
}

t3Maze::~t3Maze()
{
    for(int i = 0; i < row; i++)
        delete[] m[i];
    
    delete[] m;
}

void t3Maze::add(int value)
{
    m[pRow][pCol] = value;
    
    pCol++;
    if(pCol >= col)
    {
        pCol = 0;
        pRow++;
    }
}

void t3Maze::path(int exitRow, int exitCol)
{
    if(exitRow >= row || exitCol >= col || exitCol < 0 || exitRow < 0)
    {
        t3PrintError("迷宫出口数据有误");
        return;
    }
    
    offsets move[8];
    initMove(move);
   
    int **mark;
    // 标记是否来过此处
    mark = new int*[row](); //开辟行
    for(int i = 0; i < row; i++)
    {
        mark[i] = new int[col](); //开辟列
        for(int j=0; j<col; j++)
            mark[i][j] = 0;
    }
    
    bool found = false;
    int nextRow, nextCol;
    
    t3Stack<compass> stack;
    compass start(1, 1, 1);
    stack.push(start);
    
    // 还有退路可走 / 没有找到出口
    while(!stack.isEmpty() && !found)
    {
        // 寻找通路失败返回原路的标记
        
        compass now = stack.pop();
        
        while(now.direction < 8 && !found)
        {
            //stack.print();
            
            nextRow = now.row + move[now.direction].vert;
            nextCol = now.col + move[now.direction].horiz;
            
            if(nextRow == exitRow && nextCol == exitCol)
            {
                // 放入最后一个结点
                compass temp(now.row, now.col, ++now.direction);
                
                stack.push(temp);
                
                found = true;
            }
            // 没有来过 且 当前为通路
            else if(!mark[nextRow][nextCol] && !m[nextRow][nextCol])
            {
                // 放入当前走到的结点 dir代表可探测方向
                compass temp(now.row, now.col, ++now.direction);
                
                //t3Log("stack push row:%d col:%d", now.row, now.col);
                
                stack.push(temp);
                
                mark[nextRow][nextCol] = 1;
                now.row = nextRow;
                now.col = nextCol;
                now.direction = 0;
            }
            else
                now.direction++;
        }
    }
    
    if(found)
    {
        t3Log("t3Maze: 路径已找到为: \n");
        
        t3Log("[0] row: %d col: %d\n", exitRow, exitCol);
        
        int i=0;
        while(!stack.isEmpty())
        {
            compass temp = stack.pop();
            t3Log("[%d] row: %d col: %d\n", ++i, temp.row, temp.col);
        }
    }
    else
        t3Log("t3Maze: 当前迷宫没有路径可出");
}

void t3Maze::print()
{
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            t3Log("t3Maze[%d][%d]=%d", i, j, m[i][j]);
        }
        t3Log("\n");
    }
}

t3Maze& t3Maze::operator<<(int value)
{
    add(value);
    
    return *this;
}

t3Maze& t3Maze::operator,(int value)
{
    add(value);
    
    return *this;
}