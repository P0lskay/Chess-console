#include "Chess_game.h"
#include <Windows.h>
#include <iomanip>
#include <vector>

ostream& operator << (ostream& os, Cell_prop obj)
{
	
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (obj.figure_color == Ceil_Figure_color::White) //Если фигура белая, то она отобразится черным текстом на белом фоне
	{
		SetConsoleTextAttribute(hConsole, 240);
	}
	else							 //Если фигура черная, то она отобразится белым текстом на черном фоне 
	{
		SetConsoleTextAttribute(hConsole, 15);
	}
	os << " ";
	switch (obj.figure_type) //В зависимости от типа фигуры, выводим соответвующую ей букву
	{
	case Ceil_Figure_type::K:
		os << "K";
		break;
	case Ceil_Figure_type::Q:
		os << "Q";
		break;
	case Ceil_Figure_type::N:
		os << "N";
		break;
	case Ceil_Figure_type::B:
		os << "B";
		break;
	case Ceil_Figure_type::R:
		os << "R";
		break;
	case Ceil_Figure_type::p:
		os << "p";
		break;
	default:
		os << " ";
		break;
	}

	os << " ";
	SetConsoleTextAttribute(hConsole, 15);
	return os;
}

ostream& operator<<(ostream& os, Chess_game obj)
{
	vector<char> chess_letters = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
	for (auto& i : chess_letters)
	{
		os << setw(4) << i;
	}
	cout << '\n' << " ";
	for (int i = 0; i < sizeof(obj.chess_board) / sizeof(*(obj.chess_board)); i++)
		os << "____";
	cout << '\n';
	for (int i = 0; i < sizeof(obj.chess_board) / sizeof(*(obj.chess_board)); i++)
	{
		os << i + 1;
		for (int j = 0; j < sizeof(obj.chess_board[i]) / sizeof(*(obj.chess_board[i])); j++)
			os << "|" << obj.chess_board[i][j];
		os << "|" << '\n' << " ";
		for (int j = 0; j < sizeof(obj.chess_board[i]) / sizeof(*(obj.chess_board[i])); j++)
			os << "|" << "___";
		os << "|" << '\n';
	}
	return os;
}

Chess_game::Chess_game()
{
	start_new_game();
	cout << "Игра началась, первыми ходят белые. Для совершения хода введите в одну строчку: 'e2 e4' - " << 
			"где e2 - координата, которой соответствует фигура, которая ходит, а e4 - координата клетки, куда данная фигура ходит." << '\n';
}

void Chess_game::start_new_game()
{
	chess_board[0][0] = chess_board[0][7] = Cell_prop(Ceil_Figure_color::White, Ceil_Figure_type::R);
	chess_board[0][1] = chess_board[0][6] = Cell_prop(Ceil_Figure_color::White, Ceil_Figure_type::N);
	chess_board[0][2] = chess_board[0][5] = Cell_prop(Ceil_Figure_color::White, Ceil_Figure_type::B);
	chess_board[0][3] = Cell_prop(Ceil_Figure_color::White, Ceil_Figure_type::Q);
	chess_board[0][4] = Cell_prop(Ceil_Figure_color::White, Ceil_Figure_type::K);
	for (int i = 0; i < 8; i++)
	{
		chess_board[1][i] = Cell_prop(Ceil_Figure_color::White, Ceil_Figure_type::p);
	}
	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			chess_board[i][j] = Cell_prop(Ceil_Figure_color::no, Ceil_Figure_type::none);
		}
	}
	for (int i = 0; i < 8; i++)
	{
		chess_board[6][i] = Cell_prop(Ceil_Figure_color::Black, Ceil_Figure_type::p);
	}

	chess_board[7][0] = chess_board[7][7] = Cell_prop(Ceil_Figure_color::Black, Ceil_Figure_type::R);
	chess_board[7][1] = chess_board[7][6] = Cell_prop(Ceil_Figure_color::Black, Ceil_Figure_type::N);
	chess_board[7][2] = chess_board[7][5] = Cell_prop(Ceil_Figure_color::Black, Ceil_Figure_type::B);
	chess_board[7][3] = Cell_prop(Ceil_Figure_color::Black, Ceil_Figure_type::Q);
	chess_board[7][4] = Cell_prop(Ceil_Figure_color::Black, Ceil_Figure_type::K);
}

void Chess_game::make_move()
{
	using pair_coordinates = pair<pair<int, int>, pair<int, int>>;
	pair_coordinates cordinate = { {0, 0}, {0, 0} };

	string moves;
	cout << ((this->is_move_white) ? "Ход белых: " : "Ход черных: ");
	getline(cin, moves);
	try
	{
		if (moves == "RESTART")
		{
			//НАЧИНАЕМ ИГРУ ЗАНОВО
		}
		else if (moves == "END")
		{
			//ЗАКАНЧИВАЕМ ИГРУ 
		}
		else
		{
			pair_coordinates cordinate = translate_move_coordinate(moves);
		}
	}
	catch (exception& ex)
	{

	}

}

pair<pair<int, int>, pair<int, int>> translate_move_coordinate(string str_coordinate)
{
	pair<int, int> start_pos, finish_pos;

	for(auto& i : str_coordinate)
}