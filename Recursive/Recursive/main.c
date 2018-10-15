/*
솔직히 더이상 주석달기엔 지쳤어요.
*/
#include "global.h"
#include "stack.h"

// Game Logic
void createGameManager(struct GameManager* gameManager);

// GameManager function
void initialize(struct GameManager* gameManager);
void input(struct GameManager* gameManager);
void run(struct GameManager* gameManager);
void release(struct GameManager* gameManager);
void present(const struct GameManager* gameManager);
void recursiveFillTheMap(struct GameManager* gameManager);
void iterateFillTheMap(struct GameManager* gameManager);
void loadMapData(struct GameManager* gameManager);
unsigned char goAgain(struct GameManager* gameManager);

// 이번 프로젝트의 편의를 위해 Vector2를 unsgiend int로 사용한다.
struct FillTarget
{
	struct Vector2 pos;
};

struct Map
{
	// 게임 맵에 대한 더블포인터.
	// 더블포인터에 mapHeight만큼 포인터를 할당하고
	// 각 mapHeight만큼의 포인터에  mapWidth만큼 unsigned int(지형데이터로 쓰일 변수)를 할당한다.
	char** pMapData;
	unsigned int mapWidth;
	unsigned int mapHeight;
};

struct GameManager
{
#pragma region Validation Area
	struct Stack stack;
	struct Map map;
	struct FillTarget fillTarget;
	unsigned char choosePlay;
	char loopEnable; // 현재 게임 루프에 대한 true, false 값을 가지는 변수.
	unsigned int sleepTime;
#pragma endregion

#pragma region GameLogic Function
	void(*initialize)(struct GameManager* gameManager);
	void(*input)(struct GameManager* gameManager);
	// run
	void(*run)(struct GameManager* gameManager);
	// release
	void(*release)(struct GameManager* gameManager);
	void(*present)(const struct GameManager* gameManager);
#pragma endregion

#pragma region ThisProgram Function
	void(*recursiveFillTheMap)(struct GameManager* gameManager);
	void(*iterateFillTheMap)(struct GameManager* gameManager);
	void(*loadMapData)(struct GameManager* gameManager);
	unsigned char(*goAgain)(struct GameManager* gameManager);
#pragma endregion
}GameManager;

int main()
{
	struct GameManager gameManager;
	createGameManager(&gameManager);
	gameManager.initialize(&gameManager);
	gameManager.run(&gameManager);
	gameManager.release(&gameManager);

}

void createGameManager(struct GameManager* gameManager)
{
	gameManager->initialize = initialize;
}

// GameManager Function.
void initialize(struct GameManager* gameManager)
{
	srand((unsigned)time(NULL));

	gameManager->map.pMapData = NULL;
	gameManager->map.mapWidth = 0;
	gameManager->map.mapHeight = 0;
	gameManager->fillTarget.pos.x = 0;
	gameManager->fillTarget.pos.y = 0;
	gameManager->sleepTime = 0;
	gameManager->loopEnable = TRUE;
	gameManager->input = input;
	gameManager->run = run;
	gameManager->release = release;
	gameManager->present = present;
	gameManager->recursiveFillTheMap = recursiveFillTheMap;
	gameManager->iterateFillTheMap = iterateFillTheMap;
	gameManager->loadMapData = loadMapData;
	gameManager->loadMapData(gameManager);
	gameManager->goAgain = goAgain;

	createStack(&gameManager->stack);
	gameManager->stack.initialize(&gameManager->stack);
}

void input(struct GameManager * gameManager)
{
	// 현재 화면을 갱신해준다.
	present(gameManager);
	int startPointX, startPointY;
	char inputString[128];

	while (1)
	{
		printf("\n시작할 행과 열의 위치를 입력하세요(0행 0열 부터 시작)\n");
		printf("Enter the row number : ");
		rewind(stdin);
		scanf("%d", &startPointY);

		printf("Enter the column number : ");
		rewind(stdin);
		scanf("%d", &startPointX);

		printf("Do you want to print out step by step ?");
		rewind(stdin);
		scanf("%s", inputString);

		if ((strcmp(inputString, "no") == 0) || (strcmp(inputString, "No") == 0))
		{
			gameManager->sleepTime = 0;
			break;
		}
		else if ((strcmp(inputString, "yes") == 0) || (strcmp(inputString, "Yes") == 0))
		{
			gameManager->sleepTime = 200;
			break;
		}
		else
		{
			printf("잘못 입력 하였습니다. 다시 입력하십시오.\n");
		}
	}
	// 행렬 범위 유효성 체크.

	// 시작할 위치에 대한 데이터를 게임매니저에 넣어줌.
	gameManager->fillTarget.pos.x = startPointX;
	gameManager->fillTarget.pos.y = startPointY;

	
}

void run(struct GameManager* gameManager)
{
	while (gameManager->loopEnable)
	{
		system("cls");
		gameManager->input(gameManager);

		while(1)
		{
			printf("플레이 할 방식을 정해주세요(1 - 재귀방식, 2 - 반복방식) : ");
			rewind(stdin);
			scanf("%c", &gameManager->choosePlay);
			if (FALSE == ((gameManager->choosePlay == '1') || (gameManager->choosePlay == '2')))
				printf("잘못 입력하였습니다. 다시 입력해주세요.\n");
			else
				break;
		}

		if ('1' == gameManager->choosePlay)
			recursiveFillTheMap(gameManager);
		else if ('2' == gameManager->choosePlay)
			gameManager->iterateFillTheMap(gameManager);

		if (FALSE == gameManager->goAgain(gameManager))
		{
			system("cls");
			printf("\nYour final result is\n\n");
			gameManager->present(gameManager);
			system("Pause");
			gameManager->loopEnable = FALSE;
		}
		// 입력 스트림을 비워준다. fflush는 visual studio의 컴파일러에 따라 되는 버전이 있고 안되는 버전이 있음. 표준이 rewind
		rewind(stdin);

	}
}

void release(struct GameManager* gameManager)
{
	free(gameManager->map.pMapData);
	gameManager->stack.release(&gameManager->stack);
}

void present(const struct GameManager* gameManager)
{
	//system("cls");
	for (int i = 0; i < gameManager->map.mapHeight; ++i)
	{
		for (int j = 0; j < gameManager->map.mapWidth; ++j)
		{
			printf("%c ", gameManager->map.pMapData[i][j]);
		}
		puts("\n");
	}
	_sleep(gameManager->sleepTime);
}

// 해당 함수는 상 하 좌 우 위치로 이동하면서 판단한다.
// 모든 위치로의 이동을 할 것 이므로 좌수법에서 이동경로만 가져오는 것이 아닌
// 모든 방향성으로의 이동을 강제하면 될 것.
void recursiveFillTheMap(struct GameManager * gameManager)
{
	struct Vector2 targetPos = gameManager->fillTarget.pos;

	gameManager->map.pMapData[targetPos.y][targetPos.x] = '@';
	// 현재 화면을 갱신해준다.
	system("cls");
	present(gameManager);

#pragma region TOP
	// 맵 안에 있는지 체크.(배열 인덱스 유효성 체크)
	if (targetPos.y - 1 >= 0)
	{
		// 위쪽 방향이 벽인지? 그리고 위쪽 방향이 -인지 체크
		if ( '-' == gameManager->map.pMapData[targetPos.y - 1][targetPos.x])
		{
			// 플레이어의 위치를 옮겨준다.
			gameManager->fillTarget.pos.x = targetPos.x;
			gameManager->fillTarget.pos.y = targetPos.y - 1;

			// Recursive
			recursiveFillTheMap(gameManager);
		}
	}
#pragma endregion

#pragma region LEFT
	// 맵 안에 있는지 체크.(배열 인덱스 유효성 체크)
	if (targetPos.x - 1 >= 0)
	{
		// 왼쪽 방향이 벽인지? 그리고 위쪽 방향이 -인지 체크
		if ('-' == gameManager->map.pMapData[targetPos.y][targetPos.x - 1])
		{
			// 플레이어의 위치로 옮겨준다.
			gameManager->fillTarget.pos.x = targetPos.x - 1;
			gameManager->fillTarget.pos.y = targetPos.y;

			// Recursive
			recursiveFillTheMap(gameManager);
		}
	}
#pragma endregion

#pragma region RIGHT
	// 맵 안에 있는지 체크.(배열 인덱스 유효성 체크)
	if (targetPos.x + 1 < gameManager->map.mapWidth)
	{
		// 우측 방향이 벽인지? 그리고 위쪽 방향이 -인지 체크
		if ('-' == gameManager->map.pMapData[targetPos.y][targetPos.x + 1])
		{
			// 플레이어의 위치로 옮겨준다.
			gameManager->fillTarget.pos.x = targetPos.x + 1;
			gameManager->fillTarget.pos.y = targetPos.y;

			// Recursive
			recursiveFillTheMap(gameManager);
		}
	}
#pragma endregion

#pragma region BOTTOM
	// 맵 안에 있는지 체크.(배열 인덱스 유효성 체크)
	if (targetPos.y + 1 < gameManager->map.mapHeight)
	{
		// 위쪽 방향이 벽인지? 그리고 위쪽 방향이 -인지 체크
		if ('-' == gameManager->map.pMapData[targetPos.y + 1][targetPos.x])
		{
			// 플레이어의 위치로 옮겨준다.

			gameManager->fillTarget.pos.x = targetPos.x;
			gameManager->fillTarget.pos.y = targetPos.y + 1;

			// Recursive
			recursiveFillTheMap(gameManager);
		}
	}
#pragma endregion


}

/*
 * 반복방식에 대해서는 스택을 활용하였다.
 * 스택의 특성은 후입선출(LIFO)이므로
 * 그 특성에 맞게 재귀적 방식과 반대로 스택에 탐색방향을 넣어준다.
 */
void iterateFillTheMap(struct GameManager * gameManager)
{
	struct Vector2 startPos = gameManager->fillTarget.pos;

	gameManager->stack.push(&gameManager->stack, startPos);

	while (TRUE != gameManager->stack.empty(&gameManager->stack))
	{
		struct Vector2 targetPos = gameManager->stack.top(&gameManager->stack);
		gameManager->stack.pop(&gameManager->stack);

		gameManager->map.pMapData[targetPos.y][targetPos.x] = '@';
		system("cls");
		// 현재 화면을 갱신해준다.
		present(gameManager);

#pragma region BOTTOM
		// 맵 안에 있는지 체크.(배열 인덱스 유효성 체크)
		if (targetPos.y + 1 < gameManager->map.mapHeight)
		{
			// 위쪽 방향이 벽인지? 그리고 위쪽 방향이 -인지 체크
			if ('-' == gameManager->map.pMapData[targetPos.y + 1][targetPos.x])
			{
				// 플레이어의 위치로 옮겨준다.

				gameManager->fillTarget.pos.x = targetPos.x;
				gameManager->fillTarget.pos.y = targetPos.y + 1;

				// push
				gameManager->stack.push(&gameManager->stack, gameManager->fillTarget.pos);
			}
		}
#pragma endregion

#pragma region RIGHT
		// 맵 안에 있는지 체크.(배열 인덱스 유효성 체크)
		if (targetPos.x + 1 < gameManager->map.mapWidth)
		{
			// 우측 방향이 벽인지? 그리고 위쪽 방향이 -인지 체크
			if ('-' == gameManager->map.pMapData[targetPos.y][targetPos.x + 1])
			{
				// 플레이어의 위치로 옮겨준다.
				gameManager->fillTarget.pos.x = targetPos.x + 1;
				gameManager->fillTarget.pos.y = targetPos.y;

				// push
				gameManager->stack.push(&gameManager->stack, gameManager->fillTarget.pos);
			}
		}
#pragma endregion

#pragma region LEFT
		// 맵 안에 있는지 체크.(배열 인덱스 유효성 체크)
		if (targetPos.x - 1 >= 0)
		{
			// 왼쪽 방향이 벽인지? 그리고 위쪽 방향이 -인지 체크
			if ('-' == gameManager->map.pMapData[targetPos.y][targetPos.x - 1])
			{
				// 플레이어의 위치로 옮겨준다.
				gameManager->fillTarget.pos.x = targetPos.x - 1;
				gameManager->fillTarget.pos.y = targetPos.y;

				// push
				gameManager->stack.push(&gameManager->stack, gameManager->fillTarget.pos);
			}
		}
#pragma endregion

#pragma region TOP
		// 맵 안에 있는지 체크.(배열 인덱스 유효성 체크)
		if (targetPos.y - 1 >= 0)
		{
			// 위쪽 방향이 벽인지? 그리고 위쪽 방향이 -인지 체크
			if ('-' == gameManager->map.pMapData[targetPos.y - 1][targetPos.x])
			{
				// 플레이어의 위치를 옮겨준다.
				gameManager->fillTarget.pos.x = targetPos.x;
				gameManager->fillTarget.pos.y = targetPos.y - 1;

				// push
				gameManager->stack.push(&gameManager->stack, gameManager->fillTarget.pos);
			}
		}
#pragma endregion
	}
}

void loadMapData(struct GameManager* gameManager)
{
	// 데이터를 읽어들일 파일을 연다.
	FILE* pFileOfMapData;

	// 사용자로부터 읽어들일 파일을 입력받는다.
	printf("Enter the name of data file : ");
	char inputFileName[FILENAME_MAX];
	scanf("%s", inputFileName);
	// 파일포인터에 오픈한 파일에 대한 핸들을 가진 파일포인터를 넘겨준다.
	pFileOfMapData = fopen(inputFileName, "rt");

	if (NULL == pFileOfMapData)
	{
		printf("잘못 된 파일 이름을 입력하였습니다. 다시 입력하십시오.\n");
		return;
	}
	// 파일 데이터를 가져올 변수.
	char fileData;

	// 맵 데이터를 갖고있을 변수.
	unsigned int mapWidth = 0;
	unsigned int mapHeight = 1;

	// 맵의 너비길이 체크.
	while (1)
	{
		fscanf(pFileOfMapData, "%c", &fileData);
		if (fileData == '\n')
			break;
		mapWidth++;
	}

	// 파일 포인터를 시작점으로 옮긴다.
	rewind(pFileOfMapData);

	// 맵의 높이 길이 체크.
	int n;
	while (EOF != fscanf(pFileOfMapData, "%c", &fileData))
	{
		if ('\n' == fileData)
			mapHeight++;
	}

	// 게임 내에 맵 데이터를 읽어들일 메모리 공간을 할당한다.
	gameManager->map.pMapData = (char**)malloc(sizeof(char*) * mapHeight);

	for (int index = 0; index < mapHeight; ++index)
	{
		gameManager->map.pMapData[index] = (char*)malloc(sizeof(char) * mapWidth);
	}


	// 위에서 할당한 메모리 공간에 맵데이터를 읽어들여 저장한다.
	rewind(pFileOfMapData);
	int EndOfFile;
	for (int i = 0; i < mapHeight; ++i)
	{
		for (int j = 0; j < mapWidth; ++j)
		{
			EndOfFile = fscanf(pFileOfMapData, "%c", &fileData);
			gameManager->map.pMapData[i][j] = fileData;
		}

		if (EndOfFile != EOF)
			fseek(pFileOfMapData, 2L, SEEK_CUR);
	}

	fclose(pFileOfMapData);

	gameManager->map.mapWidth = mapWidth;
	gameManager->map.mapHeight = mapHeight;
}

unsigned char goAgain(struct GameManager * gameManager)
{
	while (1)
	{
		printf("Go Again?");
		char inputString[128];
		rewind(stdin);
		scanf("%s", inputString);

		if ((strcmp(inputString, "no") == 0) || (strcmp(inputString, "No") == 0))
		{
			gameManager->sleepTime = 0;
			return FALSE;
		}
		else if ((strcmp(inputString, "yes") == 0) || (strcmp(inputString, "Yes") == 0))
		{
			gameManager->sleepTime = 200;
			return TRUE;
		}
		else
		{
			printf("잘못 입력 하였습니다. 다시 입력하십시오.\n");
		}
	}
}
