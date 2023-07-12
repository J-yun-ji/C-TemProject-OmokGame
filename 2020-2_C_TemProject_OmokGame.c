#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h> // 표준 입출력 함수를 사용하기 위한 라이브러리.
#include <conio.h> // getch를 사용하기 위한 라이브러리.
#include <locale.h> // wchar_t를 사용하기 위한 라이브러리.
#include <windows.h> // 화면 초기화를 사용하기 위한 라이브러리. 

#define UP 72 // 방향키↑의 아스키 코드 값 72를 UP으로 정의. 
#define DOWN 80 // 방향키 ↓의 아스키 코드 값 80를 DOWN으로 정의.
#define LEFT 75 // 방향키 ←의 아스키 코드 값 75를 LEFT로 정의.
#define RIGHT 77 // 방향키 →의 아스키 코드 값 77를 RIGHT로 정의.
#define SPACE 32 // 스페이스의 아스키 코드 값 32를 SPACE로 정의.
#define WHITE L'○'// 백돌의 색상을 WHITE로 정의.
#define BLACK L'●' //  흑돌의 색상을 BLACK로 정의.
#define WHITE_WIN printf("Congratulations!\n******_백돌 승리_******") // 백돌 승리 출력문을 WHITE_WIN으로 정의.
#define BLACK_WIN printf("Congratulations!\n******_흑돌 승리_******") // 흑돌 승리 출력문을 BLACK_WIN으로 정의.

void gotoxy(int x, int y); // gotoxy 좌표 함수.
void Draw_OmokBoard(void);                              // 오목판을 만들고 출력하는 함수.
void Erase_Stone(int x, int y);                   // 오목알 지우고 바둑판 출력하는  함수.(오목판에 놓은 오목알은 고정)
int Winner_rule(int x, int y, wchar_t WB);                      // 오목 승패 판단 함수.
void Screen(void);                      // 콘솔 화면 "OMOKGAME"출력 함수.
char Again_GAME(vid);                       // 1번의 실행이 끝난 후, 다시 실행 여부를 물어 실행 or 종료하는 함수. 
int control(void);                          // 오목 게임 동작 함수. 
wchar_t board[19][19] = { 0, }; // 오목 판 (19X19)을 만드는 2차원 배열을 전역으로 선언.  

void textcolor(int color_number) // 콘솔 글자색 변경 함수. 
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}
int main(void)
{
	setlocale(LC_ALL, ""); // wchar_t 자료형의 사용을 위해 setlocale 지정. 

	while (1)
	{
		Screen(); // 오목 게임 제목 출력 함수 호출.
		textcolor(224); // 회색 바탕 검은색 글씨. 
		Draw_OmokBoard(); // 오목판 출력 함수 호출. 
		control();
		if (Again_GAME() == 'y' || Again_GAME() == 'Y')
		{
			system("cls");
		}
		else
		{
			exit(0);
		}
	}

	return 0;
}
void gotoxy(int x, int y) // 좌표이동을 위한 함수.
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void Screen(void) // 시작화면에 OMOK GAME 글씨 출력하여 꾸미기.
{
	system("color Cf"); // 콘솔 배경화면을 핑크색으로 설정 
	system("mode con cols=105 lines=35 | title ---- LET'S PLAY OMOK GAME ----"); // 콘솔 창크기, 콘솔 제목 설정. 
	gotoxy(15, 2);
	printf("\n");
	printf("      ■■■    ■■   ■■    ■■■    ■    ■     ■■■        ■       ■■   ■■  ■■■■■\n");
	printf("    ■      ■  ■ ■ ■ ■  ■      ■  ■   ■    ■             ■■      ■ ■ ■ ■  ■ \n");
	printf("    ■      ■  ■  ■■ ■  ■      ■  ■ ■      ■            ■  ■     ■  ■■ ■  ■\n");
	printf("    ■      ■  ■   ■  ■  ■      ■  ■■       ■  ■■■   ■■■■    ■   ■  ■  ■■■■■\n");
	printf("    ■      ■  ■       ■  ■      ■  ■  ■     ■      ■  ■      ■   ■       ■  ■\n");
	printf("      ■■■    ■       ■    ■■■    ■    ■     ■■■   ■        ■  ■       ■  ■■■■■\n");
}
void Draw_OmokBoard(void) // 오목판을 만드는 함수. 
{
	Screen(); // 시작 화면 글씨를 출력하는 Screen 호출. 
	system("color Cf"); // 핑크 배경색. 
	textcolor(128); // 바둑판은 보기 편하게 그레이 색으로 결정. 
	int i, j; // for문을 돌리기 위한 i, j 선언. 

	board[0][0] = L'┌';
	board[0][18] = L'┐';
	board[18][0] = L'└';
	board[18][18] = L'┘';

	for (i = 1; i < 18; i++)
	{
		board[0][i] = L'┬';
		board[i][0] = L'├';
		board[i][18] = L'┤';
		board[18][i] = L'┴';

		for (j = 1; j < 18; j++)
		{
			board[i][j] = L'┼';
		}
	}
	for (i = 0; i <= 18; i++)
	{
		gotoxy(30, 12 + i); // 콘솔 시작화면인 가운데 좌표가 (0, 0) -> (30, 12) 

		for (j = 0; j <= 18; j++)
		{
			if ((board[i][j] == BLACK) || (board[i][j] == WHITE))
				wprintf(L'%c', board[i][j]); // 띄어쓰기 필요없음. 
			else
				wprintf(L"%c ", board[i][j]); // 오목판 기호는 2바이트를 차지하기 때문에 정사각형으로 출력하기 위해선 띄어쓰기가 필요함. 
		}
		printf("\n");
	}
}
int control(void) // 게임 컨트롤 하는 함수. 
{
	int key; // key는 방향키 아스키코드를 저장할 변수.
	int  x = 30, y = 12; // gotoxy(x, y)좌표의 원점을 (30, 12)부터 시작.  
	int a = y - 1;
	int b = (x - 30) / 2;
	wchar_t WB = BLACK; // 시작은 흑돌로. 

	while (1)                                     // 누군가 승리하기 전까지 계속 무한 반복.
	{
		if (_kbhit())                             // 키보드로부터 입력받으면 1반환. 
		{
			key = _getch();                       // getch로 방향키 or 스페이스바 입력받기.

			if (key == 224 || key == SPACE)       // 입력 받은 값이 2byte거나(224부터 2byte) 스페이스바일 때 
			{
				if (key == SPACE)                 // 입력받은 값이 스페이스이면 오목알 놓기.
				{
					if ((board[y - 12][(x - 30) / 2] == WHITE) || (board[y - 12][(x - 30) / 2] == BLACK)) // 오목알이 놓여져있다면 알림음으로 알림.                                                                            // 고정된 오목알을 또다시 고정시키려고 하는 경우
					{
						printf("\a");
						continue;
					}
					else if (WB == WHITE)         // 백돌 차례라면.
					{
						board[y - 12][(x - 30) / 2] = WHITE;
						Winner_rule(x, y, WB);
						if (Winner_rule(x, y, WB) == 1)     // 승패 판단 함수가 1을 반환한다면 종료.
						{
							break;
						}
						WB = BLACK;                         // 흑돌 차례로. 
					}
					else if (WB == BLACK)                   // 흑돌 차례라면.
					{
						board[y - 12][(x - 30) / 2] = BLACK;
						Winner_rule(x, y, WB);
						if (Winner_rule(x, y, WB) == 1)
						{
							break;
						}
						WB = WHITE;                        // 백돌 차례로. 
					}
					continue;                              // 스페이스를 입력받았으니, continue를 이용해 아래의 코드를 건너뛴다.
				}
				key = _getch();                            // 2바이트인 방향키의 남은 아스키코드 값을 다시 입력받는다. 
				switch (key)
				{
				case UP:                                   // 방향키가 UP이면 즉, 오목알을 위로 이동하면 다음을 실행.
					if (y == 12)                           // (30, 12)이 (0, 0)이니, 오목판의 가장 위쪽으로 이동한 좌표값 12로 지정.
						break;                             // 오목판의 가장자리이니 더 이상 위로 못가게 break 해준다. 
					Erase_Stone(x, y);                     // 오목을 둔 알은 고정하고 오목알 지우고 바둑판 출력하는 함수 호출. 
					y--;                                   // 다음 좌표는 위로 이동하니 y - 1.
					gotoxy(x, y);
					wprintf(L"%c", WB);
					break;

				case DOWN:                                 // 방향키가 DOWN이면 즉, 오목알을 아래로 이동하면 다음을 실행.
					if (y == 30)                           // 오목판의 가장 아래쪽으로 이동한 좌표값 30으로 지정. 
						break;
					Erase_Stone(x, y);                    // 오목알을 지우는 함수 호출.
					y++;                                  // 다음 좌표는 아래로 이동하니 y + 1
					gotoxy(x, y);
					wprintf(L"%c", WB);
					break;

				case LEFT:
					if (x == 30)
						break;
					Erase_Stone(x, y);
					x -= 2;
					gotoxy(x, y);                        // 다음 좌표는 왼쪽으로 이동하니 x - 2 -> - 2인 이유는 가로가 2바이트라서.
					wprintf(L"%c", WB);
					break;

				case RIGHT:
					if (x == 66)                         // 오목판의 가장 오른쪽으로 이동한 좌표값 66로 지정.
						break;
					Erase_Stone(x, y);
					x += 2;
					gotoxy(x, y);
					wprintf(L"%c", WB);
					break;
				}
			}
		}
	}
}
void Erase_Stone(int x, int y) // 고정된 오목알은 제외, 오목알 지우고 바둑판 출력하는  함수 
{
	int a = y - 12;
	int b = (x - 30) / 2;
	gotoxy(x, y);             // 현재 오목알이 위치한 곳으로 이동, 

	if (board[a][b] == WHITE || board[a][b] == BLACK) // 좌표값을 뺀 값이 배열에선 좌표위치. 
	{
		wprintf(L"%c", board[a][b]); // 만일 현재 board의 값이 오목알이면 띄어쓰기를 하지 않은 채로 출력.
	}
	else
	{
		wprintf(L"%c ", board[a][b]); // 만일 현재 board의 값이 오목판이면 띄어쓰기를 해준다. 
	}
}
int Winner_rule(int x, int y, wchar_t WB) // 오목 승패 판단 함수.
{
	int a = y - 12;
	int b = (x - 30) / 2;
	int i = 1, j = 1, k = 1, m = 1, n = 1;
	int count1 = 1, count2 = 1;

	for (i = 1; i < 5; i++)         // 연속적으로 놓인 5개의 오목알 검사.
	{
		if (board[a][b + j] == WB) // 놓인 오목알을 기준으로 오른쪽 검사. 가로 →
		{
			count1++;
			j++;
		}
		else if (board[a][b - k] == WB) // 왼쪽에 오목알이 놓였다면 왼쪽 검사. 가로 ←
		{
			count1++;
			k++;
		}
		else if (board[a + m][b] == WB) // 위쪽에 오목알이 놓였다면 검사. 위로 ↑
		{
			count2++;
			m++;
		}
		else if (board[a - n][b] == WB) // 아래쪽에 오목알이 놓였다면 검사. 아래 ↓
		{
			count2++;
			n++;
		}
	}
	if (count1 == 5 || count2 == 5)     // 5개의 알이 연속적으로 놓여있다면 승리자 출력.
	{
		gotoxy(1, 16);
		if (WB == BLACK)
		{
			BLACK_WIN;
		}
		else if (WB == WHITE)
		{
			WHITE_WIN;
		}
		return 1;
	}
	j = 1, k = 1, m = 1, n = 1, count1 = 1, count2 = 1;  // 다시 1로 초기화.
	for (i = 1; i < 5; i++)
	{
		if (board[a + j][b + j] == WB) // 대각선에 오목알이 놓였다면 검사. 오른쪽 하단 ↘
		{
			count1++;
			j++;
		}
		else if (board[a - k][b - k] == WB) // 대각선에 오목알이 놓였다면 검사. 왼쪽 상단 ↖
		{
			count1++;
			k++;
		}
		else if (board[a + m][b - m] == WB) // 대각선에 오목알이 놓였다면 검사. 왼쪽 하단 ↙
		{
			count2++;
			m++;
		}
		else if (board[a - n][b + n] == WB) // 대각선에 오목알이 놓였다면 검사. 오른쪽 상단 ↗
		{
			count2++;
			n++;
		}
	}
	if (count1 == 5 || count2 == 5)
	{
		gotoxy(1, 16);
		if (WB == BLACK)
		{
			BLACK_WIN;
		}
		else if (WB == WHITE)
		{
			WHITE_WIN;
		}
		return 1;
	}
}
char Again_GAME(void) // 해당 판의 게임이 종료된 후, 다시 게임을 할 것인지 묻고 실행 or 종료하는 함수.
{
	gotoxy(2, 20); // 글을 출력하기 좋은 위치로 좌표 이동. 
	textcolor(15); // 텍스트 컬러 설정. 
	printf("\n 게임을 다시 하시겠습니까?\n");
	printf("\n 다시 하기를 원한다면 -> Y(y)키를  \n 종료를 원한다면 아무키나 눌러주세요....\n");

	char ask = _getch(); // ask 변수에 입력받은 값 저장. 

	return ask;
}



