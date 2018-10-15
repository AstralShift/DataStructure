/*
������ ���̻� �ּ��ޱ⿣ ���ƾ��.
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

// �̹� ������Ʈ�� ���Ǹ� ���� Vector2�� unsgiend int�� ����Ѵ�.
struct FillTarget
{
	struct Vector2 pos;
};

struct Map
{
	// ���� �ʿ� ���� ����������.
	// ���������Ϳ� mapHeight��ŭ �����͸� �Ҵ��ϰ�
	// �� mapHeight��ŭ�� �����Ϳ�  mapWidth��ŭ unsigned int(���������ͷ� ���� ����)�� �Ҵ��Ѵ�.
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
	char loopEnable; // ���� ���� ������ ���� true, false ���� ������ ����.
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
	// ���� ȭ���� �������ش�.
	present(gameManager);
	int startPointX, startPointY;
	char inputString[128];

	while (1)
	{
		printf("\n������ ��� ���� ��ġ�� �Է��ϼ���(0�� 0�� ���� ����)\n");
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
			printf("�߸� �Է� �Ͽ����ϴ�. �ٽ� �Է��Ͻʽÿ�.\n");
		}
	}
	// ��� ���� ��ȿ�� üũ.

	// ������ ��ġ�� ���� �����͸� ���ӸŴ����� �־���.
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
			printf("�÷��� �� ����� �����ּ���(1 - ��͹��, 2 - �ݺ����) : ");
			rewind(stdin);
			scanf("%c", &gameManager->choosePlay);
			if (FALSE == ((gameManager->choosePlay == '1') || (gameManager->choosePlay == '2')))
				printf("�߸� �Է��Ͽ����ϴ�. �ٽ� �Է����ּ���.\n");
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
		// �Է� ��Ʈ���� ����ش�. fflush�� visual studio�� �����Ϸ��� ���� �Ǵ� ������ �ְ� �ȵǴ� ������ ����. ǥ���� rewind
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

// �ش� �Լ��� �� �� �� �� ��ġ�� �̵��ϸ鼭 �Ǵ��Ѵ�.
// ��� ��ġ���� �̵��� �� �� �̹Ƿ� �¼������� �̵���θ� �������� ���� �ƴ�
// ��� ���⼺������ �̵��� �����ϸ� �� ��.
void recursiveFillTheMap(struct GameManager * gameManager)
{
	struct Vector2 targetPos = gameManager->fillTarget.pos;

	gameManager->map.pMapData[targetPos.y][targetPos.x] = '@';
	// ���� ȭ���� �������ش�.
	system("cls");
	present(gameManager);

#pragma region TOP
	// �� �ȿ� �ִ��� üũ.(�迭 �ε��� ��ȿ�� üũ)
	if (targetPos.y - 1 >= 0)
	{
		// ���� ������ ������? �׸��� ���� ������ -���� üũ
		if ( '-' == gameManager->map.pMapData[targetPos.y - 1][targetPos.x])
		{
			// �÷��̾��� ��ġ�� �Ű��ش�.
			gameManager->fillTarget.pos.x = targetPos.x;
			gameManager->fillTarget.pos.y = targetPos.y - 1;

			// Recursive
			recursiveFillTheMap(gameManager);
		}
	}
#pragma endregion

#pragma region LEFT
	// �� �ȿ� �ִ��� üũ.(�迭 �ε��� ��ȿ�� üũ)
	if (targetPos.x - 1 >= 0)
	{
		// ���� ������ ������? �׸��� ���� ������ -���� üũ
		if ('-' == gameManager->map.pMapData[targetPos.y][targetPos.x - 1])
		{
			// �÷��̾��� ��ġ�� �Ű��ش�.
			gameManager->fillTarget.pos.x = targetPos.x - 1;
			gameManager->fillTarget.pos.y = targetPos.y;

			// Recursive
			recursiveFillTheMap(gameManager);
		}
	}
#pragma endregion

#pragma region RIGHT
	// �� �ȿ� �ִ��� üũ.(�迭 �ε��� ��ȿ�� üũ)
	if (targetPos.x + 1 < gameManager->map.mapWidth)
	{
		// ���� ������ ������? �׸��� ���� ������ -���� üũ
		if ('-' == gameManager->map.pMapData[targetPos.y][targetPos.x + 1])
		{
			// �÷��̾��� ��ġ�� �Ű��ش�.
			gameManager->fillTarget.pos.x = targetPos.x + 1;
			gameManager->fillTarget.pos.y = targetPos.y;

			// Recursive
			recursiveFillTheMap(gameManager);
		}
	}
#pragma endregion

#pragma region BOTTOM
	// �� �ȿ� �ִ��� üũ.(�迭 �ε��� ��ȿ�� üũ)
	if (targetPos.y + 1 < gameManager->map.mapHeight)
	{
		// ���� ������ ������? �׸��� ���� ������ -���� üũ
		if ('-' == gameManager->map.pMapData[targetPos.y + 1][targetPos.x])
		{
			// �÷��̾��� ��ġ�� �Ű��ش�.

			gameManager->fillTarget.pos.x = targetPos.x;
			gameManager->fillTarget.pos.y = targetPos.y + 1;

			// Recursive
			recursiveFillTheMap(gameManager);
		}
	}
#pragma endregion


}

/*
 * �ݺ���Ŀ� ���ؼ��� ������ Ȱ���Ͽ���.
 * ������ Ư���� ���Լ���(LIFO)�̹Ƿ�
 * �� Ư���� �°� ����� ��İ� �ݴ�� ���ÿ� Ž�������� �־��ش�.
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
		// ���� ȭ���� �������ش�.
		present(gameManager);

#pragma region BOTTOM
		// �� �ȿ� �ִ��� üũ.(�迭 �ε��� ��ȿ�� üũ)
		if (targetPos.y + 1 < gameManager->map.mapHeight)
		{
			// ���� ������ ������? �׸��� ���� ������ -���� üũ
			if ('-' == gameManager->map.pMapData[targetPos.y + 1][targetPos.x])
			{
				// �÷��̾��� ��ġ�� �Ű��ش�.

				gameManager->fillTarget.pos.x = targetPos.x;
				gameManager->fillTarget.pos.y = targetPos.y + 1;

				// push
				gameManager->stack.push(&gameManager->stack, gameManager->fillTarget.pos);
			}
		}
#pragma endregion

#pragma region RIGHT
		// �� �ȿ� �ִ��� üũ.(�迭 �ε��� ��ȿ�� üũ)
		if (targetPos.x + 1 < gameManager->map.mapWidth)
		{
			// ���� ������ ������? �׸��� ���� ������ -���� üũ
			if ('-' == gameManager->map.pMapData[targetPos.y][targetPos.x + 1])
			{
				// �÷��̾��� ��ġ�� �Ű��ش�.
				gameManager->fillTarget.pos.x = targetPos.x + 1;
				gameManager->fillTarget.pos.y = targetPos.y;

				// push
				gameManager->stack.push(&gameManager->stack, gameManager->fillTarget.pos);
			}
		}
#pragma endregion

#pragma region LEFT
		// �� �ȿ� �ִ��� üũ.(�迭 �ε��� ��ȿ�� üũ)
		if (targetPos.x - 1 >= 0)
		{
			// ���� ������ ������? �׸��� ���� ������ -���� üũ
			if ('-' == gameManager->map.pMapData[targetPos.y][targetPos.x - 1])
			{
				// �÷��̾��� ��ġ�� �Ű��ش�.
				gameManager->fillTarget.pos.x = targetPos.x - 1;
				gameManager->fillTarget.pos.y = targetPos.y;

				// push
				gameManager->stack.push(&gameManager->stack, gameManager->fillTarget.pos);
			}
		}
#pragma endregion

#pragma region TOP
		// �� �ȿ� �ִ��� üũ.(�迭 �ε��� ��ȿ�� üũ)
		if (targetPos.y - 1 >= 0)
		{
			// ���� ������ ������? �׸��� ���� ������ -���� üũ
			if ('-' == gameManager->map.pMapData[targetPos.y - 1][targetPos.x])
			{
				// �÷��̾��� ��ġ�� �Ű��ش�.
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
	// �����͸� �о���� ������ ����.
	FILE* pFileOfMapData;

	// ����ڷκ��� �о���� ������ �Է¹޴´�.
	printf("Enter the name of data file : ");
	char inputFileName[FILENAME_MAX];
	scanf("%s", inputFileName);
	// ���������Ϳ� ������ ���Ͽ� ���� �ڵ��� ���� ���������͸� �Ѱ��ش�.
	pFileOfMapData = fopen(inputFileName, "rt");

	if (NULL == pFileOfMapData)
	{
		printf("�߸� �� ���� �̸��� �Է��Ͽ����ϴ�. �ٽ� �Է��Ͻʽÿ�.\n");
		return;
	}
	// ���� �����͸� ������ ����.
	char fileData;

	// �� �����͸� �������� ����.
	unsigned int mapWidth = 0;
	unsigned int mapHeight = 1;

	// ���� �ʺ���� üũ.
	while (1)
	{
		fscanf(pFileOfMapData, "%c", &fileData);
		if (fileData == '\n')
			break;
		mapWidth++;
	}

	// ���� �����͸� ���������� �ű��.
	rewind(pFileOfMapData);

	// ���� ���� ���� üũ.
	int n;
	while (EOF != fscanf(pFileOfMapData, "%c", &fileData))
	{
		if ('\n' == fileData)
			mapHeight++;
	}

	// ���� ���� �� �����͸� �о���� �޸� ������ �Ҵ��Ѵ�.
	gameManager->map.pMapData = (char**)malloc(sizeof(char*) * mapHeight);

	for (int index = 0; index < mapHeight; ++index)
	{
		gameManager->map.pMapData[index] = (char*)malloc(sizeof(char) * mapWidth);
	}


	// ������ �Ҵ��� �޸� ������ �ʵ����͸� �о�鿩 �����Ѵ�.
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
			printf("�߸� �Է� �Ͽ����ϴ�. �ٽ� �Է��Ͻʽÿ�.\n");
		}
	}
}
