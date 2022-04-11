﻿#include "Chess_game.h"

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
	//Запускаем цикл ходов, пока не произойдет break внутри цикла
	while (true)
	{
		cout << ((this->is_move_white) ? "Ход белых: " : "Ход черных: ");
		getline(cin, moves);
		try
		{
			if (moves == "END")
			{
				break;
			}
			else
			{
				pair_coordinates cordinate = translate_move_coordinate(moves);
			}
		}
		catch (exception& ex)
		{	//Если введена неверная команда или неверные кординаты, то выводим ошибку
			//и вновь даем игрокам возможность для ввода
			cerr << ex.what() << endl;
			continue;
		}
	}

}

pair<pair<int, int>, pair<int, int>> Chess_game::translate_move_coordinate(string& str_coordinate)
{
	pair<int, int> start_pos, finish_pos;
	if (check_str_coordinate(str_coordinate))
	{	//Удаляем все пробелы из строки, а затем вычисляем координаты клетки в массиве board_chess
		//static_cast<int>('a') = 97, а static_cast<int>('1') = 49, 
		//поэтому для получения координат вычитаем 97 и 49 соответсвенно
		str_coordinate.erase(remove(str_coordinate.begin(), str_coordinate.end(), ' '), str_coordinate.end());
		start_pos = { static_cast<int>(str_coordinate[0]) - 97, static_cast<int>(str_coordinate[1]) - 49 };
		finish_pos = { static_cast<int>(str_coordinate[2]) - 97, static_cast<int>(str_coordinate[3]) - 49 };
	}
	else
	{
		throw exception("Введены неправильные координаты или команда, пожалуйста, проверьте раскладку и попробуйте еще раз.");
	}
	return { start_pos, finish_pos };
}


bool Chess_game::check_str_coordinate(string_view str_coordinate) const
{
	static const regex r(R"(\s+[a-h][1-8]\s+[a-h][1-8]\s+)");
	return regex_match(str_coordinate.data(), r);
}

void Chess_game::move_figure(pair<int, int> start_move, pair<int, int> finish_move)
{
	if (is_move_white && chess_board[start_move.first][start_move.second].figure_color != Ceil_Figure_color::White ||
		!is_move_white && chess_board[start_move.first][start_move.second].figure_color != Ceil_Figure_color::Black)
	{	//Если на позиции, с которой фигура ходит, стоит фигура другого игрока или не стоит фигура вовсе, то бросаем исключение
		throw exception("На введенной позиции не стоит ваша фигура!");
	}

	if (chess_board[start_move.first][start_move.second].figure_color == chess_board[finish_move.first][finish_move.second].figure_color)
	{	//Если игрок пытается сходить на позицию, на которой стоит его фигура, то бросаем исключение
		throw exception("Вы не можете сходить фигурой туда, где уже стоит ваша фигура!");
	}

}

bool Chess_game::mover_check(pair<int, int> start_move, pair<int, int> finish_move)
{
	if (chess_board[start_move.first][start_move.second].figure_type == Ceil_Figure_type::B)
	{

	}
	else if (chess_board[start_move.first][start_move.second].figure_type == Ceil_Figure_type::R)
	{

	}
	else if (chess_board[start_move.first][start_move.second].figure_type == Ceil_Figure_type::N)
	{

	}
	else if (chess_board[start_move.first][start_move.second].figure_type == Ceil_Figure_type::Q)
	{

	}
	else if (chess_board[start_move.first][start_move.second].figure_type == Ceil_Figure_type::p)
	{

	}
	else if (chess_board[start_move.first][start_move.second].figure_type == Ceil_Figure_type::K)
	{

	}
}


bool Chess_game::pawn_mover_check(pair<int, int> start_move, pair<int, int> finish_move)
{
	//Случай, когда игрок ходит пешкой через 1 поле
	if (start_move.first == finish_move.first && abs(finish_move.second - start_move.second) == 2 && (start_move.second == 1 || start_move.second == 6)
		&& chess_board[finish_move.first][finish_move.second].figure_color == Ceil_Figure_color::no)
	{
		return true;
	}
	//Случай, когда игрок ходить пешкой на 1 поле вперед
	if (start_move.first == finish_move.first && abs(finish_move.second - start_move.second) == 1
		&& chess_board[finish_move.first][finish_move.second].figure_color == Ceil_Figure_color::no)
	{
		return true;
	}
	//Случай, когда игрок ест пешкой вражескую фигуру
	if (abs(finish_move.first - start_move.first) == 1 && abs(finish_move.second - start_move.second) == 1
		&& chess_board[finish_move.first][finish_move.second].figure_color == Ceil_Figure_color::Black)
	{
		return true;
	}
	
	return false;
}