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
<<<<<<< HEAD
const int WindowWidth = 80;
const int WindowHeight = 20;
// Block variables
const char BlockSymbols[3] = { '-', '+', '=' };
char platformSymbol = '-';
int blockSpeed = 10;
=======
const int WindowWidth = 70;
const int WindowHeight = 30;
// Block variables
const char BlockSymbols[3] = { '-', '+', '=' };
char platformSymbol = '-';
int blockSpeed = 1;
>>>>>>> 86c28a40f26ea1715b13b4a47bb777212447bbd3

// Ball variables
int ballSpeed = 1;

// Platform variables
int platformSpeed = 1;
int platformLength = 5;

// Game variables
<<<<<<< HEAD
unsigned long sleepDuration = 170;
=======
unsigned long sleepDuration = 200;
>>>>>>> 86c28a40f26ea1715b13b4a47bb777212447bbd3

GameObject ball(WindowWidth / 2, WindowHeight / 2, '*');
vector<GameObject> blocks;
vector<GameObject> platform;

<<<<<<< HEAD
unsigned int blockSpawnInterval = 10;//Y we need this?

// Gameplay variables
int highScore = 0;
int score = 0;
bool isNotGameOver = true;
int bonus = 0;
bool isAudio = true;

void MainMenu();
void GameOver();
void Settings();
void DefaultValues();
=======
unsigned int blockSpawnInterval = 10;

// Gameplay variables
int highestScore = 0;
int score = 0;
bool isNotGameOver = true;
int bonus = 0;

void MainMenu();
void GameOver();

>>>>>>> 86c28a40f26ea1715b13b4a47bb777212447bbd3
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
<<<<<<< HEAD
			if(isAudio)
			{
			cout << '\a';
			}

=======
			cout << '\a';
			
>>>>>>> 86c28a40f26ea1715b13b4a47bb777212447bbd3
			if (ball.Coordinates.Y <= 0)
			{
				ballSpeed = -ballSpeed;
			}
			ballSpeed = -ballSpeed;
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
<<<<<<< HEAD
=======
	if (((platform.end() - 1)->Coordinates.X >= WindowWidth - 1 && direction.X > 0) ||
		(platform.begin()->Coordinates.X <= 0 && direction.X < 0))
	{
		direction.X = 0;
	}
>>>>>>> 86c28a40f26ea1715b13b4a47bb777212447bbd3
	for (randomAccess_iterator platformBody = platform.begin(); platformBody != platform.end(); ++platformBody)
	{
			platformBody->Coordinates.X += direction.X;
			platformBody->Coordinates.Y += direction.Y;
	}
<<<<<<< HEAD
	if ((platform.end() - 1)->Coordinates.X > WindowWidth)
	{
		int index = platformLength;
		for (randomAccess_iterator platformBody = platform.begin(); platformBody != platform.end(); ++platformBody, --index)
		{
				platformBody->Coordinates.X = WindowWidth - index - 1;
		}
	}
	else if(platform.begin()->Coordinates.X < 0)
	{
		int index = 0;
		for (randomAccess_iterator platformBody = platform.begin(); platformBody != platform.end(); ++platformBody, ++index)
		{
				platformBody->Coordinates.X = index;
		}
	}
=======
>>>>>>> 86c28a40f26ea1715b13b4a47bb777212447bbd3
	ball.Coordinates.Y += ballSpeed;

	// Loop trough all blocks
	CollisionDetection();
<<<<<<< HEAD

=======
>>>>>>> 86c28a40f26ea1715b13b4a47bb777212447bbd3
	if (ball.Coordinates.Y <= 0)
	{
		ballSpeed = -ballSpeed;
	}
	if (ball.Coordinates.Y == WindowHeight - 1 && 
		ball.Coordinates.X >= platform.begin()->Coordinates.X && 
		ball.Coordinates.X <= (platform.end()-1)->Coordinates.X)
	{
		ballSpeed = -ballSpeed;

	}
<<<<<<< HEAD
	if (ball.Coordinates.Y>=WindowHeight||ball.Coordinates.Y == WindowHeight + 1 && 
=======
	if (ball.Coordinates.Y == WindowHeight + 1 && 
>>>>>>> 86c28a40f26ea1715b13b4a47bb777212447bbd3
		(ball.Coordinates.X < platform.begin()->Coordinates.X || ball.Coordinates.X > (platform.end() - 1)->Coordinates.X))
	{
		GameOver();
	
	}
	

}

void Draw()
{
	ClearScreen(consoleHandle);
	if (bonus == 1)
	{
		platform.push_back(GameObject((platform.end()-1)->Coordinates.X + 1, WindowHeight - 1, platformSymbol));
		bonus = 0;
	}
		
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
<<<<<<< HEAD
	DefaultValues();
	MainMenu();
	return 0;
=======
		consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

		srand(time(NULL));

		int platformY = WindowHeight - 1;
		int platformX = WindowWidth / 2 - platformLength / 2;

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
				blocks.push_back(GameObject(i, j, GenerateRandomBlock()));
			}
		}
		MainMenu();
		return 0;
>>>>>>> 86c28a40f26ea1715b13b4a47bb777212447bbd3
}
void MainMenu()
{
	isNotGameOver = true;
	int menuChoice;
	ClearScreen(consoleHandle);
	cout << "1 - New game" << endl;
	cout << "2 - How to play" << endl;
	cout << "3 - Highest score" << endl;
	cout << "4 - Settings" << endl;
	cout << "0 - Exit" << endl;
	cin >> menuChoice;
	switch (menuChoice)
	{
	case 1:
		{
<<<<<<< HEAD
			DefaultValues();
=======
>>>>>>> 86c28a40f26ea1715b13b4a47bb777212447bbd3
			while (true)
			{
				Update();
				if (isNotGameOver)
				{
					Draw();
				}
				else
				{
<<<<<<< HEAD
					GameOver();
=======
					
>>>>>>> 86c28a40f26ea1715b13b4a47bb777212447bbd3
				}
				Sleep(sleepDuration);
			}
			break;
		  }
	case 2:
		{
			ClearScreen(consoleHandle);
			//Instructions();
<<<<<<< HEAD
			cout << "Press 'm' to return to the Main menu." << endl;
=======
			cout << "Press m to return to the Main menu." << endl;
>>>>>>> 86c28a40f26ea1715b13b4a47bb777212447bbd3
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
<<<<<<< HEAD
			cout << "Highest score: " << highScore << endl;
			cout << "Press 'm' to return to the Main menu." << endl;
=======
			cout << "Highest score: " << highestScore << endl;
			cout << "Press m to return to the Main menu." << endl;
>>>>>>> 86c28a40f26ea1715b13b4a47bb777212447bbd3
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
<<<<<<< HEAD
	case 4:
		{
			Settings();
			break;
		}
=======
>>>>>>> 86c28a40f26ea1715b13b4a47bb777212447bbd3
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
<<<<<<< HEAD
	cout << "Press 'm' to return to the Main menu." << endl;
	if (score > highScore)
		highScore = score;


=======
	cout << "Press m to return to the Main menu." << endl;
>>>>>>> 86c28a40f26ea1715b13b4a47bb777212447bbd3
	if (kbhit())
	{
		char key = getch();
		if (key == 'm')
		{
			MainMenu();
		}
	}
<<<<<<< HEAD
}

void Settings()
{
	ClearScreen(consoleHandle);
	if(isAudio)
	{
		cout << "Press '0' to turn off the audio."<< endl;
	}
	else
	{
		cout << "Press '1' to turn on the audio."<< endl;
	}
	cout << "Press 'm' to return to the main menu.";

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
	platformSpeed = 5;
	platformLength = 5;
	ballSpeed = 1;
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
	/// Generate blocks
	int blocksPerColumn = 3;
	for (int i = 0; i < WindowWidth - 1; i++)
	{
		for (int j = 0; j < blocksPerColumn; j++)
		{
			blocks.push_back(GameObject(i, j, GenerateRandomBlock()));
		}
	}
}
=======
	
}
>>>>>>> 86c28a40f26ea1715b13b4a47bb777212447bbd3

