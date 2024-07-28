#include<iostream>
#include<conio.h>
#include<windows.h>
#include<fstream>
#include<math.h>
#include<string>
#include<iomanip>

#define pi 3.1416 
#define BLACK 0
#define BROWN 6
#define WHITE 15
#define GREEN 2
#define RED 4
#define LBLUE 9
using namespace std;

enum Color { Green, Red };

#include<Windows.h>




struct Position
{
	int rpos;
	int cpos;
};

//Helpers
void SetClr(int tcl, int bcl)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (tcl + (bcl * 16)));
}
void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}


//Board
void DignalSec(int rs, int re, int cs, int ce, char sym, int clr)
{
	for (int r = rs, c = cs; r <= re && c >= ce; r++, c--)
	{
		SetClr(clr, BLACK);
		gotoRowCol(r, c);
		cout << sym;

	}
}
void Dignal(int rs, int re, int cs, int ce, char sym, int clr)
{
	for (int r = rs, c = cs; r <= re && c <= ce; r++, c++)
	{
		SetClr(clr, BLACK);
		gotoRowCol(r, c);
		cout << sym;

	}
}
void T2B(int c, int rs, int re, char sym, int clr)
{
	for (int r = rs; r <= re; r++)
	{
		SetClr(clr, BLACK);
		gotoRowCol(r, c);
		cout << sym;

	}
}
void L2R(int r, int cs, int ce, char sym, int clr)
{
	for (int c = cs; c <= ce; c++)
	{
		SetClr(clr, BLACK);
		gotoRowCol(r, c);
		cout << sym;

	}
}
void Board(int dim, int rows, int cols, int sh)
{
	char sym = -37;
	int shift = rows - 1;
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			if (j != dim - 1)
				L2R(i * rows + sh, j * cols + sh, ((j + 1) * (cols)) - 1 + sh, sym, 15);

			if (i != dim - 1)
			{
				int c = j * cols;
				T2B(c + sh, i * rows + sh, ((i + 1) * rows) - 1 + sh, sym, 15);
			}
			if (i != dim - 1 && j != dim - 1)
			{
				if ((i + j) % 2 == 0)
				{
					Dignal(i * rows + sh, ((i + 1) * rows) - 1 + sh, j * cols + sh, ((j + 1) * (cols)) - 1 + sh, sym, 15);
				}
				// if(i*rows+cols*(j+1) == dim * cols-cols)
				else
					DignalSec(i * rows + sh, ((i + 1) * rows) - 1 + sh, ((j + 1) * (cols)) + sh, j * cols + sh, sym, 15);
			}


		}

	}
	gotoRowCol(rows * dim - rows + sh, cols * dim - cols + sh);
	cout << sym;
}


//Beads
void Printdata(char** Board, int dim, int Bdim, int sh)
{
	int fixR = 0;
	int fixC = 0;
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			gotoRowCol((i)+fixR + sh, (j)+fixC + sh);
			if (Board[i][j] != '-')
				cout << Board[i][j];
			fixC += (Bdim - 1);

		}
		fixC = 0;
		fixR += (Bdim - 1);

	}
}
void Circle(int h, int k, float radius, char sym, int clr)
{

	for (int theta = 0; theta < 360; theta++)
	{
		SetClr(clr, BLACK);
		float rad = theta * pi / 180;
		float x = ceil(radius * cos(rad)) + k;
		float y = ceil(radius * sin(rad)) + h;
		gotoRowCol(y, x);
		cout << sym;
	}


}
void bead(int h, int k, int clr)
{

	Circle(h, k, 2.1, -37, clr);
	Circle(h, k, 1, -37, clr);
}
void beadRemove(int h, int k, int clr)
{

	Circle(h, k, 2.1, ' ', clr);
	Circle(h, k, 1, ' ', clr);
}
void printBeads(char** Board, int dim, int Bdim, int sh)
{
	int fixR = 0;
	int fixC = 0;
	int clr = 0;
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			//gotoRowCol(, );
			if (Board[i][j] == 'G')
			{
				clr = 2;
				bead((i)+fixR + sh, (j)+fixC + sh, clr);
			}
			if (Board[i][j] == 'R')
			{
				clr = 12;
				bead((i)+fixR + sh, (j)+fixC + sh, clr);
			}
			fixC += (Bdim - 1);

		}
		fixC = 0;
		fixR += (Bdim - 1);

	}
}
void RemoveBead(char** Board, int dim, int Bdim, int sh, Position P, int rows, int cols)
{
	int fixR = 0;
	int fixC = 0;
	int clr = 0;
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			//gotoRowCol(, );
			if (i == P.rpos && j == P.cpos)
			{
				clr = 15;
				beadRemove((i)+fixR + sh, (j)+fixC + sh, clr);
			}

			fixC += (Bdim - 1);

		}
		fixC = 0;
		fixR += (Bdim - 1);

	}
}



//Main Flow
void init(const char* fName, char**& board, int& dim, int& turn, string pNames[], int count[])
{

	ifstream rdr(fName);
	if (!rdr)
		cout << "Loading fail....", exit(1);
	rdr >> turn >> count[Green] >> count[Red] >> dim;
	board = new char* [dim];

	for (int i = 0; i < dim; i++)
	{
		board[i] = new char[dim] {};
	}

	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			rdr >> board[i][j];
		}
	}


	for (int i = 0; i < 2; i++)
	{
		cout << "Player " << i + 1 << " Name:";
		cin >> pNames[i];
	}
	if (fName == "New.txt")
	{
		srand(69);
		turn = rand() % 2;
	}


}
void initComp(const char* fName, char**& board, int& dim, int& turn, string pNames[], int count[])
{

	ifstream rdr(fName);
	if (!rdr)
		cout << "Loading fail....", exit(1);
	rdr >>turn >> count[Green] >> count[Red] >> dim;

	board = new char* [dim];

	for (int i = 0; i < dim; i++)
	{
		board[i] = new char[dim] {};
	}

	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			rdr >> board[i][j];
		}
	}

	pNames[0] = "Computer";

	for (int i = 1; i < 2; i++)
	{
		cout << "Player's Name:";
		cin >> pNames[i];
	}
	if (fName == "New.txt")
	{
		srand(69);
		turn = rand() % 2;
	}


}
void TurnAndScoreMessage(string Names[], int turn, int Boxdim, int count[])
{
	SetClr(15, BLACK);
	gotoRowCol(2 * Boxdim, 5 * Boxdim);
	cout << "Score(" << Names[Green] << ")    Score(" << Names[Red] << ")";
	gotoRowCol(2 * Boxdim + 2, 5 * Boxdim);
	cout << "       " << setw(2) << setfill('0') << count[Green] << "                " << setw(2) << count[Red] << endl;
	gotoRowCol(2 * Boxdim + 4, 5 * Boxdim);
	cout << "                                                        ";
	gotoRowCol(2 * Boxdim + 4, 5 * Boxdim);
	if (turn == Green)
		cout << Names[turn] << "'s turn (Green Bead)" << endl << endl;
	else
		cout << Names[turn] << "'s turn (Red Bead)" << endl << endl;




}
void selectPosition(Position& P, int dim, int divide)
{
	int y, x;

	getRowColbyLeftClick(y, x);
	P.rpos = y / divide;
	P.cpos = x / divide;


}
bool isRedPiece(char sym)
{
	return sym == 'R';
}
bool isGreenPiece(char sym)
{
	return sym == 'G';
}
bool isMyPiece(char sym, int turn)
{
	if (turn == Red)
		return isRedPiece(sym);
	return isGreenPiece(sym);

}
bool validRange(int dim, Position P)
{
	if (P.rpos<0 || P.rpos>=dim || P.cpos<0 || P.cpos>=dim)
		return false;
	return true;
}
bool isValidSource(char** Board, int dim, int turn, Position source)
{
	if (Board[source.rpos][source.cpos] == '-')
		return false;

	if (validRange(dim, source) == 0)
		return false;
	return isMyPiece(Board[source.rpos][source.cpos], turn);
}
bool isValidDestination(char** Board, int dim, int turn, Position dest)
{
	if (validRange(dim, dest) == 0)
		return false;
	//return !(isMyPiece(Board[source.rpos][source.cpos], turn));
	return(Board[dest.rpos][dest.cpos] == '-');

}
void updadteBoard(char** Board, Position source, Position destination)
{
	char temp = Board[source.rpos][source.cpos];
	Board[destination.rpos][destination.cpos] = temp;
	Board[source.rpos][source.cpos] = '-';

}
void KillBead(char** Board, Position remove)
{

	Board[remove.rpos][remove.cpos] = '-';

}
void TurnChnage(int& Turn)
{

	Turn = (Turn + 1) % 2;
}
void WinMessage(int Boxdim, int turn, string Names[])
{
	TurnChnage(turn);
	SetClr(WHITE, BLACK);
	gotoRowCol(2 * Boxdim + 6, 5 * Boxdim);
	cout << "GAME OVER";
	gotoRowCol(2 * Boxdim + 8, 5 * Boxdim);
	cout << Names[turn] << " Wins";
}

//Legalities
bool isHorizontal(Position Sc, Position Dc)
{
	return(Sc.rpos == Dc.rpos);

}
bool isVertical(Position Sc, Position Dc)
{
	return(Sc.cpos == Dc.cpos);
}
bool NotSamePos(Position p1, Position p2)
{
	return (p1.rpos != p2.rpos || p1.cpos != p2.cpos);
}
bool isVerticalJump(char** B, Position S, Position D, Position& R, int dim, int turn)
{
	TurnChnage(turn);
	if (isVertical(S, D))
	{
		if (S.rpos > D.rpos)
		{

			R.rpos = S.rpos - 1, R.cpos = S.cpos;
			if (validRange(dim, R))
				return((isMyPiece(B[R.rpos][R.cpos], turn)) && B[D.rpos][D.cpos] == '-' && NotSamePos(R, D));

		}
		else
		{

			R.rpos = S.rpos + 1, R.cpos = S.cpos;
			if (validRange(dim, R))
				return((isMyPiece(B[R.rpos][R.cpos], turn)) && B[D.rpos][D.cpos] == '-' && NotSamePos(R, D));
		}

	}
	return false;
}
bool isHorizentalJump(char** B, Position S, Position D, Position& R, int dim, int turn)
{

	TurnChnage(turn);
	if (isHorizontal(S, D))
	{
		//Left
		if (D.cpos < S.cpos)
		{

			R.rpos = S.rpos, R.cpos = S.cpos - 1;
			if (validRange(dim, R))
				return((isMyPiece(B[R.rpos][R.cpos], turn)) && B[D.rpos][D.cpos] == '-' && NotSamePos(R, D));

		}
		//Right
		else
		{
			R.rpos = S.rpos, R.cpos = S.cpos + 1;
			if (validRange(dim, R))
				return((isMyPiece(B[R.rpos][R.cpos], turn)) && B[D.rpos][D.cpos] == '-' && NotSamePos(R, D));
		}
	}
	return false;
}
bool isDignolMain(Position Sc, Position Dc)
{
	return ((Sc.rpos - Dc.rpos) == (Sc.cpos - Dc.cpos));
}
bool isDignolSec(Position Sc, Position Dc)
{
	return (abs(Sc.rpos - Dc.rpos) == abs(Sc.cpos - Dc.cpos) && (Sc.rpos - Dc.rpos) != (Sc.cpos - Dc.cpos));
}
bool isDignalJump(char** B, Position S, Position D, Position& R, int dim, int turn)
{
	TurnChnage(turn);
	if ((S.rpos + S.cpos) % 2 == 0)
	{
		if (isDignolMain(S, D))
		{
			if (D.rpos < S.rpos && D.cpos < S.cpos)
			{
				R.rpos = S.rpos - 1, R.cpos = S.cpos - 1;
				if (validRange(dim, R))
					return((isMyPiece(B[R.rpos][R.cpos], turn)) && B[D.rpos][D.cpos] == '-' && NotSamePos(R, D));

			}
			else
			{
				R.rpos = S.rpos + 1, R.cpos = S.cpos + 1;
				if (validRange(dim, R))
					return((isMyPiece(B[R.rpos][R.cpos], turn)) && B[D.rpos][D.cpos] == '-' && NotSamePos(R, D));
			}
		}
		if (isDignolSec(S, D))
		{
			if (D.rpos > S.rpos && D.cpos < S.cpos)
			{

				R.rpos = S.rpos + 1, R.cpos = S.cpos - 1;
				if (validRange(dim, R))
					return((isMyPiece(B[R.rpos][R.cpos], turn)) && B[D.rpos][D.cpos] == '-' && NotSamePos(R, D));

			}
			else
			{
				R.rpos = S.rpos - 1, R.cpos = S.cpos + 1;
				if (validRange(dim, R))
					return((isMyPiece(B[R.rpos][R.cpos], turn)) && B[D.rpos][D.cpos] == '-' && NotSamePos(R, D));
			}
		}
	}
	return false;
}
bool isLegalMove(char** B, Position S, Position D, Position& R, int dim, int turn)
{
	int temp = abs(D.rpos - S.rpos);
	int temp1 = abs(D.cpos - S.cpos);
	// jumps
	if (isVerticalJump(B, S, D, R, dim, turn))
		return true;
	if (isHorizentalJump(B, S, D, R, dim, turn))
		return true;
	if (isDignalJump(B, S, D, R, dim, turn))
		return true;
	R.rpos = -1, R.cpos = -1;
	//veritcal Move
	if (temp == 1 && isVertical(S, D))
	{
		return true;
	}
	if (temp1 == 1 && isHorizontal(S, D))
	{
		return true;
	}
	//Dignal Move
	if ((abs(S.rpos - D.rpos) == 1) && (abs(S.cpos - D.cpos) == 1) && (S.rpos + S.cpos) % 2 == 0)
	{
		return true;
	}

	return false;


}
bool isKill(char** B, Position S, Position D, Position& R, int dim, int turn)
{
	int temp = abs(D.rpos - S.rpos);
	int temp1 = abs(D.cpos - S.cpos);
	// jumps
	if (isVerticalJump(B, S, D, R, dim, turn))
		return true;
	if (isHorizentalJump(B, S, D, R, dim, turn))
		return true;
	if (isDignalJump(B, S, D, R, dim, turn))
		return true;
	R.rpos = -1, R.cpos = -1;
	return false;


}

//Load Game
void Load(const char* fName, char** B, int dim, int count[],int turn)
{
	ofstream wrt(fName);
	wrt << turn << endl;
	wrt << count[Green] << " " << count[Red] << endl;
	wrt << dim << endl;
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			wrt << B[i][j];
		}
		wrt << endl;
	}
}

bool isKill(char** B, int dim, Position S, Position& D, Position& R, int turn)
{
	if (isVerticalJump(B, S, D, R, dim, turn))
		return true;
	if (isHorizentalJump(B, S, D, R, dim, turn))
		return true;
	if (isDignalJump(B, S, D, R, dim, turn))
		return true;

}

int  ComputerMove(char** B, int dim, Position &S, Position& D, Position& R, int turn)
{

	//kiling Inteligence
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			S.rpos = i, S.cpos = j;
			if(isValidSource(B,dim,turn,S))
			{
				for (int k = 0; k < dim; k++)
				{
					for (int l = 0; l < dim; l++)
					{
						D.rpos = k, D.cpos = l;
						if (isKill(B, S, D, R, dim, turn) && isValidDestination(B, dim, turn, D))
							return 0;
					}
				}


			}
		}
	}
	R.rpos = -1, R.cpos = -1;
	//Simple Move
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			S.rpos = i, S.cpos = j;
			if (isValidSource(B, dim, turn, S))
			{
				for (int k = 0; k < dim; k++)
				{
					for (int l = 0; l < dim; l++)
					{
						D.rpos = k, D.cpos = l;
						if (isLegalMove(B, S, D, R, dim, turn) && isValidDestination(B, dim, turn, D))
						{
							R.rpos = -1, R.cpos = -1;
							return 0;
						}
					}
				}


			}
		}
	}
	
	//TurnChnage(turn);

	//for (int i = 0; i < dim; i++)
	//{
	//	for (int j = 0; j < dim; j++)
	//	{
	//		S.rpos = i, S.cpos = j;
	//		for (int k = 0; k < dim; k++)
	//		{
	//			for (int l = 0; l < dim; l++)
	//			{
	//				S.rpos = k, S.cpos = k;
	//				if (isKill(B, dim, S, D, R, turn))
	//					return 0;
	//			}


	//		}
	//	}
	//}

	//R.rpos = -1, R.cpos = -1;
	//TurnChnage(turn);
	//do
	//{
	//	D.rpos = rand() % dim;
	//	D.cpos = rand() % dim;
	//} while (isValidDestination(B, dim, turn, D));

}


void Menu()
{
	cout << "1.New Game" << endl;
	cout << "2.Load Game" << endl;
	cout << "0.Exit" << endl;
}
void GameMenu()
{
	cout << "1.Human Vs Human" << endl;
	cout << "2.Computer Vs Human" << endl;
	cout << "0.Exit" << endl;
}

int Computer()
{

	char** B = nullptr;
	int dim = 0;
	int boxdim = 15;
	int shift = 10;
	int turn = 0;
	int count[2];
	string Names[2] = {};
	Position Sc, Dc, Rc, P;
	Rc.rpos = -1, Rc.cpos = -1;
	cout << "Enter Your Choice" << endl;
	Menu();
	int choice = -1;
	cin >> choice;
	switch (choice)
	{
	case 0:
		cout << "Exit", exit(1);
	case 1:
		initComp("New.txt", B, dim, turn, Names, count);
		break;
	case 2:
		initComp("Load.txt", B, dim, turn, Names, count);
		break;
	default:
		break;
	}
	system("cls");
	Board(dim, boxdim, boxdim, shift);
	Printdata(B, dim, boxdim, shift);
	printBeads(B, dim, boxdim, shift);


	while (true)
	{
		TurnAndScoreMessage(Names, turn, boxdim, count);
		if (count[Green] == 12 || count[Red] == 12)
			break;
		if (turn == 0)
		{
			ComputerMove(B, dim, Sc, Dc, Rc, turn);
		}
		else {
			do {

				do
				{
					do
					{
						selectPosition(Sc, dim, boxdim);


					} while (isValidSource(B, dim, turn, Sc) == 0);

					selectPosition(Dc, dim, boxdim);

				} while (isValidDestination(B, dim, turn, Dc) == 0);

			} while (isLegalMove(B, Sc, Dc, Rc, dim, turn) == 0);
		}
		updadteBoard(B, Sc, Dc);
		if (Rc.rpos != -1 && Rc.cpos != -1)
		{
			KillBead(B, Rc);
			RemoveBead(B, dim, boxdim, shift, Rc, boxdim, boxdim);
			Rc.rpos = -1, Rc.cpos = -1;
			if (turn == Green)
				count[Green]++;
			else
				count[Red]++;


		}
		RemoveBead(B, dim, boxdim, shift, Sc, boxdim, boxdim);
		Board(dim, boxdim, boxdim, shift);
		printBeads(B, dim, boxdim, shift);
		Load("Load.txt", B, dim, count,turn);
		TurnChnage(turn);


	}


	WinMessage(boxdim, turn, Names);

	_getch();
	return 0;

}

int Human()
{

	char** B = nullptr;
	int dim = 0;
	int boxdim = 15;
	int shift = 10;
	int turn = 0;
	int count[2];
	string Names[2] = {};
	Position Sc, Dc, Rc, P;
	Rc.rpos = -1, Rc.cpos = -1;
	cout << "Enter Your Choice" << endl;
	Menu();
	int choice = -1;
	cin >> choice;
	switch (choice)
	{
	case 0:
		cout << "Exit", exit(1);
	case 1:
		init("New.txt", B, dim, turn, Names, count);
		break;
	case 2:
		init("Load.txt", B, dim, turn, Names, count);
		break;
	default:
		break;
	}
	system("cls");
	Board(dim, boxdim, boxdim, shift);
	Printdata(B, dim, boxdim, shift);
	printBeads(B, dim, boxdim, shift);


	while (true)
	{
		TurnAndScoreMessage(Names, turn, boxdim, count);
		if (count[Green] == 12 || count[Red] == 12)
			break;
		do {
			do
			{
				do
				{
					selectPosition(Sc, dim, boxdim);


				} while (isValidSource(B, dim, turn, Sc) == 0);

				selectPosition(Dc, dim, boxdim);

			} while (isValidDestination(B, dim, turn, Dc) == 0);
		} while (isLegalMove(B, Sc, Dc, Rc, dim, turn) == 0);
		updadteBoard(B, Sc, Dc);
		if (Rc.rpos != -1 && Rc.cpos != -1)
		{
			KillBead(B, Rc);
			RemoveBead(B, dim, boxdim, shift, Rc, boxdim, boxdim);
			Rc.rpos = -1, Rc.cpos = -1;
			if (turn == Green)
				count[Green]++;
			else
				count[Red]++;


		}
		RemoveBead(B, dim, boxdim, shift, Sc, boxdim, boxdim);
		Board(dim, boxdim, boxdim, shift);
		printBeads(B, dim, boxdim, shift);
		Load("Load.txt", B, dim, count,turn);
		TurnChnage(turn);


	}


	WinMessage(boxdim, turn, Names);

	_getch();
	return 0;

}

int main()
{
	int choice = -1;

	GameMenu();
	cout << "\n_____________________\n";
	cout << "\n\nChoice" << endl;
	cin >> choice;
	switch (choice)
	{
	case 0:
		break;
	case 1:
		Human();
		break;
	case 2:
		Computer();
		break;
	default:
		cout << "Invalid Input";
		break;
	}
}

















