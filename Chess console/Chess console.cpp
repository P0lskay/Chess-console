#include "Chess_game.h"

ostream& Cell_prop::operator <<(ostream& os) const
{
	if (this->figure_color == White) //Если фигура белая, то она отобразится черным текстом на белом фоне
	{
		system("color F0");
	}
	else							 //Если фигура черная, то она отобразится белым текстом на черном фоне
	{
		system("color 0F");
	}

	cout << " ";
	switch (this->figure_type) //В зависимости от типа фигуры, выводим соответвующую ей букву
	{
	case K:
		cout << "K";
		break;
	case Q:
		cout << "Q";
		break;
	case N:
		cout << "N";
		break;
	case B:
		cout << "B";
		break;
	case R:
		cout << "R";
		break;
	case p:
		cout << "p";
		break;
	default:
		cout << " ";
		break;
	}

	cout << " ";
}

Chess_game::Chess_game()
{
	start_new_game();
	cout << "Игра началась, первыми ходят белые. Для совершения хода введите в одну строчку: 'e2 e4' - " << 
			"где e2 - координата, которой соответствует фигура, которая ходит, а e4 - координата клетки, куда данная фигура ходит.";
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
			chess_board[i][j] = Cell_prop(Ceil_Figure_color::none, Ceil_Figure_type::none);
		}
	}
	for (int i = 0; i < 8; i++)
	{
		chess_board[6][i] = Cell_prop(Ceil_Figure_color::Black, Ceil_Figure_type::p);
	}

	chess_board[7][0] = chess_board[0][7] = Cell_prop(Ceil_Figure_color::Black, Ceil_Figure_type::R);
	chess_board[7][1] = chess_board[0][6] = Cell_prop(Ceil_Figure_color::Black, Ceil_Figure_type::N);
	chess_board[7][2] = chess_board[0][5] = Cell_prop(Ceil_Figure_color::Black, Ceil_Figure_type::B);
	chess_board[7][3] = Cell_prop(Ceil_Figure_color::Black, Ceil_Figure_type::Q);
	chess_board[7][4] = Cell_prop(Ceil_Figure_color::Black, Ceil_Figure_type::K);
}