#include <iostream>
#include <vector>
#include <conio.h>
#include <time.h>

#include "ConsoleGaming.h"

using namespace std;


HANDLE consoleHandle;

typedef vector<GameObject>::iterator randomAccess_iterator;
typedef vector<GameObject>::const_iterator const_iterator;

// Window constants
const int WindowWidth = 70;
const int WindowHeight = 30;
// Block variables
const char BlockSymbol = '-';
int blockSpeed = 1;

// Ball variables
int ballSpeed = 1;

// Platform variables
int platformSpeed = 1;
int platformLength = 5;

// Game variables
unsigned long sleepDuration = 200;

GameObject ball(WindowWidth / 2, WindowHeight / 2, '*');
vector<GameObject> blocks;
vector<GameObject> platform;

unsigned int blockSpawnInterval = 10;

int highestScore = 0;

void MainMenu();
void GameOver();

void CollisionDetection()
{
	for (randomAccess_iterator block = blocks.begin(); block != blocks.end(); ++block)
	{
		// Remove any block that is hit by the ball
		if (ball.Coordinates.X == block->Coordinates.X && ball.Coordinates.Y == block->Coordinates.Y && block->Color != 0x0)
		{
			block->Color = 0x0;
			if (ball.Coordinates.Y <= 0)
			{
				ballSpeed = -ballSpeed;
			}
			ballSpeed = -ballSpeed;
		}
		// Implement unit collision
	}
}
void Update()
{
	COORD direction = { 0, 0 };
	if (kbhit())
	{
		char key = getch();
		switch (key)
		{
		case 'a':
			direction.X = -platformSpeed;
			break;
		case 'd':
			direction.X = platformSpeed;
			break;
		case 'm': 
			MainMenu();
			break;
		};
	}
	if (((platform.end() - 1)->Coordinates.X >= WindowWidth - 1 && direction.X > 0) ||
		(platform.begin()->Coordinates.X <= 0 && direction.X < 0))
	{
		direction.X = 0;
	}
	for (randomAccess_iterator platformBody = platform.begin(); platformBody != platform.end(); ++platformBody)
	{
			platformBody->Coordinates.X += direction.X;
			platformBody->Coordinates.Y += direction.Y;
	}
	ball.Coordinates.Y += ballSpeed;

	// Loop trough all blocks
	CollisionDetection();
	if (ball.Coordinates.Y <= 0)
	{
		ballSpeed = -ballSpeed;
	}
	if (ball.Coordinates.Y == WindowHeight - 1 && ball.Coordinates.X >= platform.begin()->Coordinates.X && ball.Coordinates.X <= (platform.end()-1)->Coordinates.X)
	{
		ballSpeed = -ballSpeed;
		//GameOver();

	}
	

}

void Draw()
{
	ClearScreen(consoleHandle);

	for (const_iterator platformBody = platform.cbegin(); platformBody != platform.cend(); ++platformBody)
	{
		platformBody->Draw(consoleHandle);
	}

	for (const_iterator block = blocks.cbegin(); block != blocks.cend(); ++block)
	{
		block->Draw(consoleHandle);
	}

	ball.Draw(consoleHandle);

}


int main()
{
		consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

		srand(time(NULL));

		int platformY = WindowHeight - 1;
		int platformX = WindowWidth / 2 - platformLength / 2;
		char platformSymbol = '-';

		for (int i = 0; i < platformLength; i++)
		{
			platform.push_back(GameObject(platformX + i, platformY, platformSymbol));
		}


		// Generate blocks
		int blocksPerColumn = 3;
		for (int i = 0; i < WindowWidth - 1; i++)
		{
			for (int j = 0; j < blocksPerColumn; j++)
			{
				blocks.push_back(GameObject(i, j, BlockSymbol));
			}
		}
		MainMenu();
		return 0;
}
void MainMenu()
{
	int menuChoice;
	ClearScreen(consoleHandle);
	cout << "1 - New game" << endl;
	cout << "2 - How to play" << endl;
	cout << "3 - Highest score" << endl;
	cout << "0 - Exit" << endl;
	cin >> menuChoice;
	switch (menuChoice)
	{
	case 1:
		{
			while (true)
			{
				Update();
				Draw();
				Sleep(sleepDuration);
			}
			break;
		  }
	case 2:
		{
			ClearScreen(consoleHandle);
			//Instructions();
			cout << "Press m to return to the Main menu." << endl;
			while (true)
			{
				if (kbhit())
				{
					char key = getch();
					if (key == 'm')
						MainMenu();
				};
			}
			break;
		  }
	case 3:
		{
			ClearScreen(consoleHandle);
			cout << "Highest score: " << highestScore << endl;
			cout << "Press m to return to the Main menu." << endl;
			while (true)
			{
				if (kbhit())
				{
					char key1 = getch();
					if (key1 == 'm')
						MainMenu();
				};				
			}
			break;
		  }
	case 0:
		{
			ClearScreen(consoleHandle);
			exit(0);
			break;
		  }
	default:
		{
			MainMenu();
		   }
	}
}
