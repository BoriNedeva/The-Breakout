#include <iostream>
#include <vector>
#include <conio.h>
#include <time.h>
#include <fstream>
#include <string>
#include <Windows.h>

#include "ConsoleGaming.h"

using namespace std;


HANDLE consoleHandle;

typedef vector<GameObject>::iterator randomAccess_iterator;
typedef vector<GameObject>::const_iterator const_iterator;

// Window constants
const int WindowWidth = 80;
const int WindowHeight = 20;
// Block variables
const char BlockSymbols[3] = { '-', '+', '=' };
char platformSymbol = '-';
int blockSpeed = 10;
int blocksPerColumn = 3;

// Ball variables
int ballSpeed;
int ballAngle;


// Platform variables
int platformSpeed;
int platformLength;

// Game variables
unsigned long sleepDuration = 170;

GameObject ball(WindowWidth / 2, WindowHeight / 2, 'o');
vector<GameObject> blocks;
vector<GameObject> platform;

unsigned int blockSpawnInterval = 10;//Y we need this?

// Gameplay variables
int highScore = 0;
int score = 0;
bool isNotGameOver = true;
int bonus = 0;
bool isAudio = true;

//Game functions
void MainMenu();
void GameOver();
void Settings();
void DefaultValues();
void NextLevel();
void Instructions();
char GenerateRandomBlock();
void CollisionDetection();

void Update()
{
	SetConsoleTextAttribute(consoleHandle, 0x4 | 0x2 | 0x1);
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
	for (randomAccess_iterator platformBody = platform.begin(); platformBody != platform.end(); ++platformBody)
	{
		platformBody->Coordinates.X += direction.X;
		platformBody->Coordinates.Y += direction.Y;
	}
	if ((platform.end() - 1)->Coordinates.X > WindowWidth)
	{
		int index = platformLength;
		for (randomAccess_iterator platformBody = platform.begin(); platformBody != platform.end(); ++platformBody, --index)
		{
			platformBody->Coordinates.X = WindowWidth - index - 1;
		}
	}
	else if (platform.begin()->Coordinates.X < 0)
	{
		int index = 0;
		for (randomAccess_iterator platformBody = platform.begin(); platformBody != platform.end(); ++platformBody, ++index)
		{
			platformBody->Coordinates.X = index;
		}
	}
	ball.Coordinates.Y += ballSpeed;
	ball.Coordinates.X += ballAngle*ballSpeed;

	// Loop trough all blocks
	CollisionDetection();

	if (ball.Coordinates.Y <= 0)
	{
		ballSpeed = -ballSpeed;
		ballAngle = -ballAngle;

	}
	if (ball.Coordinates.X <= 0)
	{
		ballAngle = -ballAngle;
	}
	if (ball.Coordinates.X >= WindowWidth - 3)
	{
		ballAngle = -ballAngle;
	}
	if (ball.Coordinates.Y == WindowHeight - 1 &&
		ball.Coordinates.X >= platform.begin()->Coordinates.X &&
		ball.Coordinates.X <= (platform.end() - 1)->Coordinates.X)
	{
		ballSpeed = -ballSpeed;
		if (ball.Coordinates.X == platform.begin()->Coordinates.X)
		{
			ballAngle = 2;
		}
		else if (ball.Coordinates.X == (platform.end() - 1)->Coordinates.X)
		{
			ballAngle = -2;
		}
		else if (ball.Coordinates.X == (platform.begin() + (platformLength / 4))->Coordinates.X)
		{
			ballAngle = 1;
		}
		else if (ball.Coordinates.X == (platform.end() - 1 - (platformLength / 4))->Coordinates.X)
		{
			ballAngle = -1;
		}
		else
		{
			ballAngle = -ballAngle;
		}

	}
	if (ball.Coordinates.Y >= WindowHeight || ball.Coordinates.Y == WindowHeight + 1 &&
		(ball.Coordinates.X < platform.begin()->Coordinates.X || ball.Coordinates.X >(platform.end() - 1)->Coordinates.X))
	{
		GameOver();

	}

	/*for (randomAccess_iterator block = blocks.begin(); block != blocks.end(); ++block)
	{
		block->Color = 0x0;
	} //test for next level */

	NextLevel();

	if ((blocks.end()-1)->Coordinates.Y == platform.begin()->Coordinates.Y)
	{
		GameOver();
	}

}
void Draw()
{
	ClearScreen(consoleHandle);
	if (bonus == 3)
	{
		platform.push_back(GameObject((platform.end() - 1)->Coordinates.X + 1, WindowHeight - 1, platformSymbol));
		(platform.end() - 1)->Color = 0x4 | 0x2;
		bonus = 0;
	}
	for (randomAccess_iterator platformBody = platform.begin(); platformBody != platform.end(); ++platformBody)
	{
		platformBody->Color = 0x2 | 0x4;
	}
	for (const_iterator platformBody = platform.cbegin(); platformBody != platform.cend(); ++platformBody)
	{
		platformBody->Draw(consoleHandle);
	}

	for (const_iterator block = blocks.cbegin(); block != blocks.cend(); ++block)
	{
		block->Draw(consoleHandle);
	}

	ball.Color = 0x2;
	ball.Draw(consoleHandle);

	
}


int main()
{
	DefaultValues();
	MainMenu();
	return 0;
}
void MainMenu()
{
	isNotGameOver = true;
	char menuChoice;
	ClearScreen(consoleHandle);
	cout << "1 - New game" << endl;
	cout << "2 - How to play" << endl;
	cout << "3 - Highest score" << endl;
	cout << "4 - Settings" << endl;
	cout << "0 - Exit" << endl;
	cin >> menuChoice;
	int menuChoiceNumber = menuChoice - '0';
	switch (menuChoiceNumber)
	{
	case 1:
	{
			  DefaultValues();
			  while (true)
			  {
				  Update();
				  if (isNotGameOver)
				  {
					  Draw();
				  }
				  else
				  {
					  GameOver();
				  }
				  Sleep(sleepDuration);
			  }
			  break;
	}
	case 2:
	{
			  ClearScreen(consoleHandle);
			  Instructions();
			  cout << "Press 'M' to return to the Main menu." << endl;
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
			  cout << "Highest score: " << highScore << endl << endl;
			  cout << "Press 'M' to return to the Main menu." << endl;
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
	case 4:
	{
			  Settings();
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

void GameOver()
{
	Sleep(1000);
	isNotGameOver = false;
	ClearScreen(consoleHandle);
	cout << "GAME OVER!!!" << endl << endl;
	cout << "Press 'M' to return to the Main menu." << endl;
	if (score > highScore)
		highScore = score;


	if (kbhit())
	{
		char key = getch();
		if (key == 'm')
		{
			MainMenu();
		}
	}
}

void Settings()
{
	ClearScreen(consoleHandle);
	if (isAudio)
	{
		cout << "Press '0' to turn off the audio." << endl;
	}
	else
	{
		cout << "Press '1' to turn on the audio." << endl;
	}
	cout << endl << "Press 'M' to return to the main menu.";

	while (!kbhit())
	{
		char key = getch();
		if (key == 'm')
		{
			MainMenu();
		}
		else if (key == '0')
		{
			isAudio = false;
			Settings();
		}
		else if (key == '1')
		{
			isAudio = true;
			Settings();
		}
	}
}
void DefaultValues()
{
	score = 0;
	ball.Coordinates.X = WindowWidth / 2;
	ball.Coordinates.Y = WindowHeight / 2;
	platformSpeed = 2;
	platformLength = 5;
	ballSpeed = 1;
	ballAngle = 0;
	bonus = 0;

	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	srand(time(NULL));

	platform.clear();

	int platformY = WindowHeight - 1;
	int platformX = WindowWidth / 2 - platformLength / 2;

	for (int i = 0; i < platformLength; i++)
	{
		platform.push_back(GameObject(platformX + i, platformY, platformSymbol));
	}
	
	blocks.clear();
	// Generate blocks
	blocksPerColumn = 3;
	for (int i = 0; i < WindowWidth - 1; i++)
	{
		for (int j = 0; j < blocksPerColumn; j++)
		{
			blocks.push_back(GameObject(i, j, GenerateRandomBlock()));
		}
	}
}

void NextLevel()
{
	bool areAllBlocksDestroyed = true;
	for (const_iterator block = blocks.begin(); block != blocks.end(); ++block)
	{
		if (block->Color != 0x0)
		{
			areAllBlocksDestroyed = false;
		}
		if (areAllBlocksDestroyed == false) break;
	}
	if (areAllBlocksDestroyed)
	{
		blocks.clear();
		// Generate blocks
		blocksPerColumn++;
		for (int i = 0; i < WindowWidth - 1; i++)
		{
			for (int j = 0; j < blocksPerColumn; j++)
			{
				blocks.push_back(GameObject(i, j, GenerateRandomBlock()));
			}
		}
	}
}

void Instructions()
{
	string line;
	ifstream myFile("Instructions.txt");
	while (getline(myFile, line))
	{
		cout << line << endl << endl;
	}
}

char GenerateRandomBlock()
{
	int length = sizeof(BlockSymbols);
	return BlockSymbols[rand() % length];
}
void CollisionDetection()
{
	for (randomAccess_iterator block = blocks.begin(); block != blocks.end(); ++block)
	{
		// Remove any block that is hit by the ball
		if (ball.Coordinates.X == block->Coordinates.X && ball.Coordinates.Y == block->Coordinates.Y && block->Color != 0x0)
		{
			if (isAudio)
			{
				cout << '\a';
			}

			if (ball.Coordinates.Y <= 0)
			{
				ballSpeed = -ballSpeed;
				ballAngle = -ballAngle;
			}
			ballSpeed = -ballSpeed;
			ballAngle = -ballAngle;
			switch (block->Symbol)
			{
			case '-':{
						 block->Color = 0x0;
						 ++score;
			}break;
			case '=':{
						 block->Symbol = '-';
			}break;
			case '+':{
						 block->Color = 0x0;
						 ++score;
						 ++bonus;
			}break;
			}
		}
		// Implement unit collision
	}
}