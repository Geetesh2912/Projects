/*
author: Geetesh Mandaogade
-----------------------------About this project-----------------------------
This code accepts a realtime input which has to be a unsolved sudoku and returns a solved completed sudoku.

-----------------------------What is a sudoku?-----------------------------
->  A sudoku is a logic-based, combinatorial number-placement puzzle. 

    In classic Sudoku, the objective is to fill a 9 × 9 grid with digits 
    so that each column, each row, and each of the nine 3 × 3 subgrids that 
    compose the grid (also called "boxes", "blocks", or "regions") contain 
    all of the digits from 1 to 9. 
    
    The puzzle setter has to provide a partially completed grid, which for a well-posed puzzle has a single solution.
*/

#include<iostream>
#include<vector>
using namespace std;

void displayBoard(int board[9][9])                                          //this function displays the sudoku board
{
    cout<<"    ---SUDOKU BOARD---   "<<endl;
    for (int i=0; i<9; i++)                                                 //normal nested for loops to traverse in 2D matrix
    {
        for (int j=0; j<9; j++)
        {
            cout<<board[i][j]<<"  ";                                         //print
        }
        cout<<endl;
        cout<<endl;
    }
    cout<<endl;
    cout<<endl;
}
 
bool isInsertValid(int board[9][9], int row, int col, int num)
{
    if (board[row][col]!=0)                                                 //if it's not 0 that means it is already filled
        return false;
    int boxCol= (col/3)*3;                                                  //gets us to the specific box number of sudoku to check
    int boxRow= (row/3)*3;

    for (int i=0; i<9; i++)
    {
        if (board[row][i]==num)                                             //if num is already in that row, cant insert
            return false;
        if (board[i][col]==num)                                             //if num is already in that col, cant insert
            return false;
        if (board[boxRow + i /3][boxCol + i % 3]==num)                       //if num is already in the box, cant insert
            return false;
    }
    return true;
}

vector<int> validDigits(int board[9][9], int row, int col)                  //gives all digits that can be placed in the board[row][col]
{
    vector<int> res={};
    for (int i=1; i<=9; i++)
    {
        if (isInsertValid(board, row, col, i)==1)                              //checks if i can be a valid digit at board[row][col]
            res.push_back(i);
    }
    return res;
}

void duplicateBoard(int board[9][9], int dupBoard[9][9])
{
    for (int i=0; i<9; i++)
    {
        for (int j=0; j<9; j++)
        {
            dupBoard[i][j]=board[i][j];
        }
    }
}

pair<int,int> nextEmpty(int board[9][9], int row, int col)
{
    pair<int,int> ans;
    int indexNext = 9 * 9 + 1;
	for (int i = row*9 + col + 1; i<9*9; i++) 
    {
		if (board[i/9][i%9] == 0) 
        {
			indexNext = i;
			break;
		}
	}
    int nRow= indexNext/9;
    int nCol= indexNext%9;
    ans.first=nRow;
    ans.second=nCol;
    return ans;
}


bool solver(int board[9][9], int row, int col)
{
    if (row>8)
        return true;

    if (board[row][col]!=0)                         //if this is non empty find next empty
    {
        pair<int,int> nxt= nextEmpty(board, row, col);
        int nextRow=nxt.first;
        int nextCol=nxt.second;
        //cout<<nextRow<<" "<<nextCol<<endl;
        return solver(board, nextRow, nextCol);
    }
    vector<int> validDigs= validDigits(board, row, col);
    if (validDigs.size()==0)                                                  //no digs valid to place in this position
        return false;
    
    for (int i=0; i<validDigs.size(); i++)
    {
        int n=validDigs[i];
        int dupBoard[9][9];
        duplicateBoard(board, dupBoard);
        dupBoard[row][col]=n;

        pair<int,int> nxt= nextEmpty(dupBoard, row, col);
        int nextRow=nxt.first;
        int nextCol=nxt.second;

        if (solver(dupBoard, nextRow, nextCol)==1)                          //dupBoard is the solved solution
        {
            duplicateBoard(dupBoard, board);                                //save modification in real board
            return true;                                                    //stop solver
        }
    }
    return false;
}

int main()
{
    cout<<endl;
    cout<<endl;
    cout<<"----------------------------------------------------------------"<<endl;
    cout<<"                Welcome to SUDOKU SOLVER program!"<<endl;
    cout<<"----------------------------------------------------------------"<<endl;
    cout<<endl;
    cout<<endl;
    int board[9][9] = {
		{0,0,0,2,6,0,7,0,1},
		{6,8,0,0,7,0,0,9,0},
		{1,9,0,0,0,4,5,0,0},
		{8,2,0,1,0,0,0,4,0},
		{0,0,4,6,0,2,9,0,0},
		{0,5,0,0,0,3,0,2,8},
		{0,0,9,3,0,0,0,7,4},
		{0,4,0,0,5,0,0,3,6},
		{7,0,3,0,1,8,0,0,0}
	};


    /*
    ----------------for real time input for sudoku problem from user---------------
    int n;
    cout<<"Enter number of already filled elements in the inomplete sudoku-> ";
    cin>>n;
    int board[9][9]={0};
    int i,j;
    
    while (n)
    {
        cout<<"Row number-> ";
        cin>>i;
        cout<<"Column number-> ";
        cin>>j;
        if (i>=1 and i<=9 and j>=1 and j<=9)
        {
            int number;
            cout<<"Enter Number at Row "<<i<<" Column "<<j<<"-> ";
            cin>>number;
            if (number<1 or number>9)
            {
                cout<<"Error- invalid digit: Note that the suoku contains all digits from 1 to 9, please re-enter a valid digit"<<endl;
            }
            else
            {
                board[i-1][j-1]=number;
                n--;
            }
        }
        else
        {
            cout<<"Error- invalid row or column: Note that sudoku is a 9x9 matrix, so please re-enter the value of row and column in the range from 1 to 9"<<endl;
        }
    }
    */
   cout<<"Below is the unsolved sudoku: "<<endl;
   cout<<endl;
    displayBoard(board);
    if(solver(board,0,0))
        cout<<"Hurray!! Sudoku Solved Successfully"<<endl;
    cout<<endl;
    displayBoard(board);
}

