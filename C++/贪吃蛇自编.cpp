#include <iostream>
#include <cstdio.h>
#include <queue>
#include <time.h>
#include <conio.h>
#include <windows.h>
#define MAXSIZE 100;
#define pair<int,int> Spostion;
enum directions
{
	UP,DOWN,LEFT,RIGHT
};
using namespace std;
char SnakeMap[MAXSIZE][MAXSIZE]='-'; //全局变量，注意操作
class Fence
{
public:
	Fence();
	bool get_Length_Width(int length,int width);
	int build_wall()；
	int game_screen();
	int produce_food();
	~Fence();
private:
	int Length;
	int Width;
	int food_x;
	int food_y;

}
class Fence :: bool get_Length_Width(int length,int width)
{
	Length=length;
	Width = width;
	return true;
}
int build_wall()
{
	int i=0;
	int j=0;
	for(j=0;j<Width;)
	{
		SnakeMap[i][j]='#';
		j++;
		if(j==Width)
		{
			j=0;
			i=Length-1;
		}

	}
	j=0;
	for(i=0;i<Length;)
	{
		SnakeMap[i][j]='#';
		i++;
		if(i==Length)
		{
			i=0;
			j=Width-1;
		}
	}
	return 0;
}
class Fence::int game_screen()
{
	for (int i = 0; i < Length; ++i)
	{
		for(int j=0;j<Width;j++)
		{
			cout<<SnakeMap[i][j];
		}
		cout<<endl;
	}
}
class Fence::int produce_food()
{
	srand((unsigned)time(NULL));
	int food_x=rand()%Width;
	int food_y=rand();%Length;
	SnakeMap[food_x][food_y]='O';
}
class Snake
{
public:
	Snake();
	int direction();
	int change_move();
	~Snake();
private:
	int SLength;
	queue <Spostion> Greedy_Snake;
	
};
class Snake::Snake()
{
	
}
int main()

