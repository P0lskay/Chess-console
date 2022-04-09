#pragma once
#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include <string_view>
#include <array>
#include <iostream>
#include <string>
#include <Windows.h>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <regex>

using namespace std;

enum class Ceil_Figure_color
	{
		Black,
		White,
		no
	};
enum class Ceil_Figure_type
	{
		K,		//King
		Q,		//Queen
		N,		//Knight
		B,		//Bishop
		R,		//Rook
		p,		//pawn
		none	//nobody
	};

struct Cell_prop
{
	Cell_prop(){}
	Cell_prop(Ceil_Figure_color color, Ceil_Figure_type type) : figure_color(color), figure_type(type){}
	Ceil_Figure_color figure_color = Ceil_Figure_color::no;
	Ceil_Figure_type figure_type = Ceil_Figure_type::none;

	friend ostream& operator << (ostream& os, Cell_prop obj);
};

class Chess_game
{
public:
	Chess_game();
	friend ostream& operator<<(ostream& os, Chess_game obj);
private:
	Cell_prop chess_board[8][8];
	bool is_move_white = true;

	//Постановка всех фигур на начальные позиции
	void start_new_game();
	
	//Метода отвечающий за начало игры и ходы игроков
	void make_move();

	//Преобразует строковые координаты в координаты, необходимые для обращения к ячейке chess_board
	pair<pair<int, int>, pair<int, int>> translate_move_coordinate(string& str_coordinate);

	//Проверяет координаты введенные пользователем на корректность
	bool check_str_coordinate(string_view str_coordinate) const;

	void move_figure(pair<int, int> start_move, pair<int, int> finish_move);

	//Проверяет, может ли фигура сделать ход
	bool mover_check(pair<int, int> start_move, pair<int, int> finish_move);

	//Проверяют, может ли конкретная фигура сделать данный ход 
	bool king_mover_check(pair<int, int> start_move, pair<int, int> finish_move);
	bool queen_mover_check(pair<int, int> start_move, pair<int, int> finish_move);
	bool bishop_mover_check(pair<int, int> start_move, pair<int, int> finish_move);
	bool knight_mover_check(pair<int, int> start_move, pair<int, int> finish_move);
	bool rook_mover_check(pair<int, int> start_move, pair<int, int> finish_move);
	bool pawn_mover_check(pair<int, int> start_move, pair<int, int> finish_move);
};

#endif // !CHESS_GAME_H