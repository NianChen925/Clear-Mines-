//
//  main.c
//  Clear Mines扫雷
//
//  Created by orange on 15/12/17.
//  Copyright © 2015年 orange. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void openZero(int x,int y);     //打开为0周边的格子的函数
int flag[9][9]={0};             //该位置是否可以显示的标记数组
int map[9][9]={0};              //存原始雷图的数组
int findFlag[9][9]={0};         //记录该位置是否被查找过的数组
int mines=0;                    //记录雷的数量

int main(int argc, const char * argv[]) {
    // insert code here...
    //扫雷游戏
    //设置扫雷图
    //生成随机雷
    srand((unsigned)time(0));
    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            if(rand()%10==6)
            {
                map[i][j]=-1;
                mines++;        //计算雷的数量
            }
        }
    }
    //完善地图
    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            if(i==0&&i==j)printf("  1 2 3 4 5 6 7 8 9\n");
            if(j==0)printf("%d ",i+1);
            printf("* ");
            //对地图除雷外的其它位置进行雷数提醒计算
            if(map[i][j]==-1)continue;
            if(i>0&&j>0&&map[i-1][j-1]==-1) map[i][j]++;
            if(i>0&&map[i-1][j]==-1) map[i][j]++;
            if(i>0&&j<8&&map[i-1][j+1]==-1) map[i][j]++;
            if(j>0&&map[i][j-1]==-1) map[i][j]++;
            if(j<8&&map[i][j+1]==-1) map[i][j]++;
            if(i<8&&j>0&&map[i+1][j-1]==-1) map[i][j]++;
            if(i<8&&map[i+1][j]==-1) map[i][j]++;
            if(i<8&&j<8&&map[i+1][j+1]==-1) map[i][j]++;
            
        }
        printf("\n");
    }
    //显示真实地图
//    for (int i=0; i<9; i++) {
//        for (int j=0; j<9; j++) {
//            if(i==0&&i==j)printf("   1  2  3  4  5  6  7  8  9\n");
//            if(j==0)printf("%d ",i+1);
//            printf("%2d ",map[i][j]);
//        }
//        printf("\n");
//    }
    //开始游戏
    printf("开始扫雷游戏！\n请输入您要猜的位置（例如1.1.1，第三位是雷标记，1为是，0为不是）:");
    int x=0,y=0;
    int mark=0;
    while(scanf("%d.%d.%d",&x,&y,&mark)){
        int count=0;        //count 为统计已经显示的位置的数目
        int boom=0;         //boom 为统计已揭示雷的数目
        x-=1;               //x y是从1开始的 转换成c中从0开始的数
        y-=1;
        //对已经点击的位置跳过显示 计算环节 节省资源
        if(flag[x][y]==1&&map[x][y]!=-1){
            printf("请输入您要猜的位置（例如1.1.1，第三位是雷标记，1为是，0为不是）:");
            continue;
        }
        if (flag[x][y]==2&&mark==0)flag[x][y]=1;        //此判断是 标记为雷的位置重置为普通位置
        if (map[x][y]!=-1)flag[x][y]=1;                 //为点击后非雷的位置 做显示操作
        if (mark==1) flag[x][y]=2;                      //标记雷操作
        if(map[x][y]==-1&&flag[x][y]!=2){               //游戏结束判断
            printf("Game Over!\n");
            break;
        }
        openZero(x, y);
        //显示当前雷图
        for (int i=0; i<9; i++) {
            for (int j=0; j<9; j++) {
                if(i==0&&i==j)printf("  1 2 3 4 5 6 7 8 9\n");
                if(j==0)printf("%d ",i+1);
                if(flag[i][j]==1)printf("%d ",map[i][j]);
                else if(flag[i][j]==2)printf("# ");
                else printf("* ");
                if(flag[i][j]!=0)count++;       //计算已显示的位置数目
                if(flag[i][j]==2)boom++;        //计算已标记的雷数
            }
            printf("\n");
        }
        //游戏通关判定
        if (count==81&&boom==mines) {
            printf("恭喜扫雷通关！\n");
            break;
        }
        printf("请输入您要猜的位置（例如1.1.1，第三位是雷标记#，1为是，0为不是）:");
    }
    return 0;
}

void openZero(int x,int y){
    //为为0的位置打开周围格子
    if (map[x][y]==0) {
        flag[x][y]=1;       //显示操作
        findFlag[x][y]=1;   //已搜索操作
        //对格子进行边界判定 并剪枝 继续递归打开点击后周边所有的0格
        if(x>0&&y>0) {flag[x-1][y-1]=1; if(x>0&&y>0&&findFlag[x-1][y-1]==0)openZero(x-1, y-1); }
        if(x>0) {flag[x-1][y]=1;if(x>0&&findFlag[x-1][y]==0)openZero(x-1, y);}
        if(x>0&&y<8) { flag[x-1][y+1]=1; if(x>0&&y<8&&findFlag[x-1][y+1]==0)openZero(x-1, y+1);}
        if(y>0) { flag[x][y-1]=1; if(y>0&&findFlag[x][y-1]==0)openZero(x, y-1);}
        if(y<8) { flag[x][y+1]=1; if(y<8&&findFlag[x][y+1]==0)openZero(x, y+1);}
        if(x<8&&y>0) { flag[x+1][y-1]=1; if(x<8&&y>0&&findFlag[x+1][y-1]==0)openZero(x+1, y-1);}
        if(x<8) { flag[x+1][y]=1; if(x<8&&findFlag[x+1][y]==0)openZero(x+1, y);}
        if(x<8&&y<8) { flag[x+1][y+1]=1;if(x<8&&y<8&&findFlag[x+1][y+1]==0) openZero(x+1, y+1);}
    }
}

/* 第一次通关
1 2 3 4 5 6 7 8 9
1 1 1 2 # 2 1 2 # #
2 2 # 3 2 3 # 2 2 2
3 2 # 3 2 # 2 1 0 0
4 2 2 3 # 2 1 0 0 0
5 1 # 3 2 2 0 0 0 0
6 1 1 2 # 1 0 0 0 0
7 0 1 2 2 1 1 1 1 0
8 2 3 # 1 0 1 # 1 0
9 # # 2 1 0 1 1 1 0
 1  2  3  4  5  6  7  8  9
 1  1  1  2 -1  2  1  2 -1 -1
 2  2 -1  3  2  3 -1  2  2  2
 3  2 -1  3  2 -1  2  1  0  0
 4  2  2  3 -1  2  1  0  0  0
 5  1 -1  3  2  2  0  0  0  0
 6  1  1  2 -1  1  0  0  0  0
 7  0  1  2  2  1  1  1  1  0
 8  2  3 -1  1  0  1 -1  1  0
 9 -1 -1  2  1  0  1  1  1  0
 */
