// SnakeConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <chrono>
#include <conio.h>

using namespace std;


bool gameOver = false;

const int W = 20, H = 20;
int headPos[2], foodPos[2];
int tailPosX[100], tailPosY[100], tailLenght, tailLenght2;
int wallPos[2];
unsigned t0, t1;
double timeG = 0;
int score = 0;
bool stop = true;

enum direction{Stop=0,Left,Right,Up,Down};

direction snakeDirection;

void init() {
	
	system("cls");
	
	headPos[0] = W / 2;
	headPos[1] = H / 2;
	stop = true;
	foodPos[0] = rand() % W;
	foodPos[1] = rand() % H;
	wallPos[0]= rand() % (W-4);
	wallPos[1] = rand() % (H-4);
	t0 = clock();
	snakeDirection = Stop;
	score = 0;

	tailLenght = 10; 
	tailLenght2 = 3;

	// Coloca los segmentos iniciales de la cola detrás de la cabeza
	for (int i = 0; i < tailLenght; ++i) {
		tailPosX[i] = headPos[0] ; // Posición X de la cola
		tailPosY[i] = headPos[1]; // Posición Y de la cola
	}

	
}

void generateRandomWall() {
	wallPos[0] = rand() % (W - 4);  // Ajusta el límite izquierdo para evitar desbordamiento
	wallPos[1] = rand() % (H - 4);   // Ajusta el límite inferior para evitar desbordamiento
}


void render() {
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
	system("cls");
	bool printWall = false;
	
	for (int i = 0; i < W + 2; i++)
	{
		cout << "#";
	}

	cout << endl;

	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{


			if (j == 0)
				cout << "#";

			
			if (j == headPos[0] && i == headPos[1]) {
				cout << "O";
				
			}
				
				
			else if (j == foodPos[0] && i == foodPos[1])
				cout << "*";
		

			else if (j == wallPos[0] && i == wallPos[1]) {
				cout << "9999";
				printWall = true;
				
			}
			if (j == W - 4 && printWall) {
				cout << "#";
				printWall = false;
			}
				
			else {
				bool printTail=false;
				
				for (int k = 0; k < tailLenght; k++)
				{
					if (tailPosX[k]==j && tailPosY[k]==i)
					{
						
						cout << "o";
						printTail = true;
					}
					
				
				}

				if (!printTail)
					cout << " ";
				
				

			}
			


			if (j == W - 1)
				cout << "#";
			
			
			if (j == wallPos[0] && i == wallPos[1]) {

				if (1 + rand() % (14)> 13 ){
					wallPos[0] = rand() % (W-4);
					wallPos[1] = rand() % (H-4);
				}

				if (score % 2==0)
				{
					//wallPos[0] = rand() % (W - 4);  // Ajusta el límite izquierdo
					//wallPos[1] = rand() % (H - 4);  // Ajusta el límite inferior
				}
				
				
					
	
			

			}
		
				
			
				
			

		}

		cout << endl;

	}
		for (int i = 0; i < H + 2; i++)
		{
			cout << "#";
		}
	
		cout << endl;
		cout << endl;
		
		
		
		
			// Code to execute
		t1 = clock();
		if (!stop)
		{
			timeG = (double(t1 - t0) / CLOCKS_PER_SEC);
		}
		
		cout << "Execution Time: " << timeG << endl;
		cout << "Score: " << score << endl;
		cout << "Snake Length: " << tailLenght << endl;
}

void input() {


	if (_kbhit())
	{
		switch (_getch())
		{
		
		case 'a':
			snakeDirection = Left;
			stop = false;
		break;

		case 'd':
			snakeDirection = Right;
			stop = false;
			break;
	
		case 'w':
			snakeDirection = Up;
			stop = false;
			break;
		case 's':
			snakeDirection = Down;
			stop = false;
			break;

		
		
		
		default:
			break;
		}
	}
	
}

void gameLogic() {


	int prevTailPosX = tailPosX[0];
	int prevTailPosY = tailPosY[0];

	int prevTailPosX2 = 0, prevTailPosY2 = 0;



	// Resto del código...

	for (int i = tailLenght - 1; i > 0; --i) {
		tailPosX[i] = tailPosX[i - 1];
		tailPosY[i] = tailPosY[i - 1];
	}

	tailPosX[0] = headPos[0];
	tailPosY[0] = headPos[1];


	switch (snakeDirection)
	{
	case Stop:
		break;
	case Left:
		headPos[0]--;
		break;
	case Right:
		headPos[0]++;
		break;
	case Up:
		headPos[1]--;
		Sleep(60);
		break;
	case Down:
		headPos[1]++;
		Sleep(60);
		break;

	}

	//check if there is collision with the walls
	if (headPos[0] >= W || headPos[0] < 0 || headPos[1] >= H || headPos[1] < 0)
	{
		gameOver = true;
	}

	//hit the wall
	for (int i = 1; i < 5; i++)
	{
		if (wallPos[0] + i-1 == headPos[0] && wallPos[1]  == headPos[1])
		{
			if (stop == false)
			{
				gameOver = true;
			}

		}

		for (int i = 0; i < tailLenght; i++)
		{
			if (tailPosX[i] == headPos[0] && tailPosY[i] == headPos[1])
			{
				if (stop == false)
				{
					gameOver = true;
				}


			}
		}



		if (headPos[0] == foodPos[0] && headPos[1] == foodPos[1])
		{
			score += 1;
			foodPos[0] = rand() % W;
			foodPos[1] = rand() % W;
			tailLenght++;
		}

	}
}


int main()
{
	srand(time(0));

	init();
	render();
	while (!gameOver)
	{

		render();
		input();
		gameLogic();
		Sleep(60);



	}
	
	char answer;
	cout << "Sorry :( you lose";
	cout << "time elapsed";
	cout << endl;
	cout << endl;

	cout << "Try again";
	cout << "Enter y: ";
	cin >> answer;

	if (answer == 'y')
	{
		gameOver = false;
		main();
	}


}



