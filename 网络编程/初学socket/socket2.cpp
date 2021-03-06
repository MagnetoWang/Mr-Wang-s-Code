#include<iostream>
#include<queue>
#include<fstream>
#define MAXSize 100
const char *filename = "迷宫图.txt";
using namespace std;
typedef pair<int int> Position
typedef struct  coordinate
{
	int x;
	int y
}Coord;//根据这个程序，起点和终点设置全局变量较好
Coord Entrance,Exit;
queue<Position> pane;
//int direction[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
int dy[4]={-1,0,1,0};
int dx[4]={0,1,0,-1};
int Creat_Maze(int (*Maze)[MAXSize], int &line,int &row, int &EntranceL, int &EntranceR, int &ExitL, int &ExitR);//line是行，row是列
//int Search_Path(char (*Maze)[MAXSize], int line, int row, int EnL, int EnR, int ExL, int ExR);//广度优先搜素
int BFS()
int main()
{
	int line, row;
	int EntranceR, EntranceL, ExitR, ExitL;
	//cout<<"输入"
//	int queue;
	int maze[MAXSize][MAXSize] = { 0 };
	bool IsthatOk = Creat_Maze(maze, line, row, EntranceL, EntranceR, ExitL, ExitR);
	Entrance.x=EntranceL;
	Entrance.y=EntranceR;
	Exit.x=ExitL;
	Exit.y=ExitR;
	
	pane.push(EntranceL,EntranceR);
	//bool IsitFound = Search_Path(maze, line, row, EntranceL, EntranceR, ExitL, ExitR);
	int pause;
	cin >> pause;
	return 0;
}
int Creat_Maze(int (*Maze)[MAXSize],int &line, int &row, int &EntranceL, int &EntranceR, int &ExitL, int &ExitR)
{
	ifstream File_Maze;
	File_Maze.open(filename);
	int n;
	File_Maze >> line>>row;
	int i = 0;
	int j = 0;
	while (!File_Maze.eof()) //判断是否读到指针最后的位置
	{
		File_Maze >> Maze[i][j];
	//	File_Maze >> Maze[i][j];
		cout << Maze[i][j] << " ";
		j++;
		if (j == row)
		{
			i++;
			cout << endl;
			j = 0;
		}
		if (i == line)
		{
			File_Maze >> EntranceL >> EntranceR >> ExitL >> ExitR;
			break;
		}//逻辑顺序很重要，不过这次一下子就发现了

	}
	cout << line <<endl<< row<<endl << EntranceL<<endl << EntranceR<<endl << ExitL <<endl<< ExitR << endl;
	cout << "the end of creatmaze" << endl;
	
	return 1;
}
//int Search_Path(char (*Maze)[MAXSize], int line, int row, int EnL, int EnR, int ExL, int ExR)//广度优先搜素
int BFS(int (*Maze)[MAXSize],)
{

	for(int i=0;i<line;i++)
	{
		for (int j = 0; j < row; j++)
		{
			dist[i][j]=10000;//距离拉大
		}
	}
	dist[Entrance.x][Entrance.y]=0;
	while(pane.size())
	{
		Position Pane = pane.front();
		if(Pane.first==Exit.x&&Pane.second==Exit.y)
		{
			break;
		}
		/*for(int i=0;i<4;i++)
		{
			if(Maze[Entrance+dx[i]][Entrance+dy[i]]==1)
			{
				Pane.push(Entrance.x+dx[i],Entrance.y+dy[i]);
				dist[Entrance.x+dx[i]][Entrance.y+dy[i]]=dist[Entrance.x][Entrance.y]+1;
			}
		}*/
		for(int i=0;i<4;i++)
		{
			int nx=Entrance.x+dx[i];
			int ny=Entrance.y+dy[i]
			if(Maze[nx][ny]==1&&0<=nx&&nx<line&&0<=ny&&ny<row&&dist[nx][ny]==10000)
			{
				Pane.push([nx][ny]);
				dist[nx][ny]=dist[Entrance.x][Entrance.y]+1;


			}
		}
		
	}
	return dist[Exit.x][Exit.y];
	//queue<int,int> path;

}


