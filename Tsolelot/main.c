#include <stdio.h>
#include <stdlib.h>
#define  minBoardSize 25
#define  submarineTypes 5
#define  numOfSubmarines 19
#define  up 1
#define  right 2
#define  down 3
#define  left 4
#define submarine 1
#define hit -1
#define empty 0

#define false 0
#define true 1

int getBoardSize();
void fillBoard(int boardSize,int board[boardSize][boardSize]);
int isValidPlacement(int boardSize,int board[boardSize][boardSize],int x,int y,int x2,int y2);
int hasNeighbors(int boardSize,int board[boardSize][boardSize],int x,int y,int x2,int y2);
void placeSubmarine(int boardSize,int board[boardSize][boardSize],int x,int y,int x2,int y2);
void getEndCoordinates(int dir,int subSize,int x,int y, int * x2, int * y2);
void zeroBoard(int boardSize,int board[boardSize][boardSize]);
runGame(int boardSize,int board1[boardSize][boardSize],int board2[boardSize][boardSize]);
int checkHit(int boardSize,int board2[boardSize][boardSize],int x,int y);
int isDemolished(int boardSize,int board[boardSize][boardSize],int x,int y);
void swap(int * a,int * b);

void swap(int * a,int * b){
    *a = *a^*b;
    *b = *a^*b;
    *a = *a^*b;
}

int checkHit(int boardSize,int board[boardSize][boardSize],int x,int y){
if(x>=0&&x<boardSize&&y>=0&&y<boardSize)return board[x][y];
}

int isDemolished(int boardSize,int board[boardSize][boardSize],int x,int y){
    //check if submarine was demolished by searching an alive cell
    for(int i = x;i<boardSize&&board[i][y]!=empty;i++){
        if(board[i][y]==submarine)return 0;
    }
    for(int i = x;i>=0&&board[i][y]!=empty;i--){
        if(board[i][y]==submarine)return 0;
    }
    for(int i = y;i<boardSize&&board[x][i]!=empty;i++){
        if(board[x][i]==submarine)return 0;
    }
    for(int i = y;i>=0&&board[x][y]!=empty;i--){
        if(board[x][i]==submarine)return 0;
    }
    return 1;
}

void zeroBoard(int boardSize,int board[boardSize][boardSize]){
for(int i = 0;i<boardSize;i++)
for(int j = 0;j<boardSize;j++)board[i][j]=empty;
}

void getEndCoordinates(int dir,int subSize,int x,int y, int * x2, int * y2){
    *x2=x,*y2=y;
    if(dir==up)*x2 = x-subSize+1;
    else if(dir==right)*y2 = y+subSize-1;
    else if(dir==down)*x2 = x+subSize-1;
    else if(dir==left)*y2 = y-subSize+1;
    else {
        *x2=-1;
        *y2=-1;
    }
}

int getBoardSize(){
    int bs;
    printf("please insert the board size:\n");
    scanf("%d",&bs);
    while(bs<minBoardSize){
        printf("error! - (minimum 25).\n");
        scanf("%d",&bs);
    }
    return bs;
}

void fillBoard(int boardSize,int board[boardSize][boardSize]){
    int x,y;
    int dir;
    int x2,y2;
    printf("welcome to the submarine placement stage:\n");
    for(int size = 1; size<=submarineTypes; size++){
            for(int subNum = 1; subNum <=submarineTypes-size+1;subNum ++){
                printf("submarine size: %d - number: %d\n",size,subNum );
                printf("x coordinate: ");
                scanf("%d",&x);
                printf("y coordinate: ");
                scanf("%d",&y);
                printf("pick direction: (1-up, 2-right,3-down,4-left)");
                scanf("%d",&dir);
                getEndCoordinates(dir,size,x,y,&x2,&y2);
                while(!isValidPlacement(boardSize,board,x,y,x2,y2)){
                    printf("\nError! - Bad Placement\n");//אולי נוסיף סיבה של שגיאה
                    printf("x coordinate: ");
                    scanf("%d",&x);
                    printf("y coordinate: ");
                    scanf("%d",&y);
                    printf("pick direction: (1-up, 2-right,3-down,4-left)\n");
                    scanf("%d",&dir);
                    getEndCoordinates(dir,size,x,y,&x2,&y2);
                }
                placeSubmarine(boardSize,board,x,y,x2,y2);
            }
    }
}

int isValidPlacement(int boardSize,int board[boardSize][boardSize],int x,int y,int x2,int y2){
    if((x>=boardSize||y>=boardSize||x<0||y<0)||
        x2>=boardSize||y2>=boardSize||x2<0||y2<0)return 0;

    if(hasNeighbors(boardSize,board,x,y,x2,y2))return 0;
    printf("EE\n");
    return 1;
}

int hasNeighbors(int boardSize,int board[boardSize][boardSize],int x,int y,int x2,int y2){
    int tmp;
    printf("x:%d X y:%d\n",x,y);
    if(x>x2)swap(&x,&x2);
    if(y>y2)swap(&y,&y2);

    for(int i = x-1;i<=x2+1&&i<boardSize;i++){
        for(int j = y-1;j<=y2+1&&j<boardSize;j++){
            if(i>=0&&j>=0){
                printf("%d | ",(board)[i][j]);
                if((board)[i][j]==submarine)return 1;
               }
        }
        printf("\n");
    }
    return 0;
}

void placeSubmarine(int boardSize,int board[boardSize][boardSize],int x,int y,int x2,int y2){
    if(x>x2)swap(&x,&x2);
    if(y>y2)swap(&y,&y2);
    printf("(%d,%d)-(%d,%d)\n",x,y,x2,y2);

    for(int i = x;i<=x2;i++){
        for(int j = y;j<=y2;j++){
            printf("placed: (%d,%d)\n",x,y);
            (board)[i][j]=submarine;
        }
    }
}

runGame(int boardSize,int board1[boardSize][boardSize],int board2[boardSize][boardSize]){
    int p1Subs = numOfSubmarines,p2Subs = numOfSubmarines;
    int x,y;
    while(p1Subs>0&&p2Subs>0){
        printf("player 1 move: \n");
        printf("x: \n");
        scanf("%d",&x);
        printf("y: \n");
        scanf("%d",&y);
        if(checkHit(boardSize,board2,x,y)){
            board2[x][y]=hit;
            printf("***hit***\n");
            if(isDemolished(boardSize,board2,x,y)){
                printf("***killed***\n");
                p2Subs--;
            }
        }

        printf("player 2 move: \n");
        printf("x: \n");
        scanf("%d",&x);
        printf("y: \n");
        scanf("%d",&y);
        if(checkHit(boardSize,board1,x,y)){
            board1[x][y]=hit;
            printf("***hit***\n");
            if(isDemolished(boardSize,board1,x,y)){
                printf("***killed***\n");
                p1Subs--;
            }
        }
    }
    if(p1Subs<=0&&p2Subs<=0){
        printf("DRAW!\n");
    }else if(p1Subs<=0){
        printf("PLAYER 2 WON!!!\n");
    }else{
    printf("PLAYER 1 WON!!!\n");
    }
}

int main()
{
    int boardSize;
    boardSize = getBoardSize();
    int board1 [boardSize][boardSize];
    int board2 [boardSize][boardSize];
    printf("Player 1:\n");
    zeroBoard(boardSize,board1);
    fillBoard(boardSize,board1);

    printf("Player 2:\n");
    zeroBoard(boardSize,board2);
    fillBoard(boardSize,board2);

    runGame(boardSize,board1,board2);
    return 0;
}
