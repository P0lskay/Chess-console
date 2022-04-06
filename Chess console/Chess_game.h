#pragma once
#ifndef CHESS_GAME_H
#define CHESS_GAME_H


#include <array>
#include <iostream>
#include <string>

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


	void start_new_game();
	

	void move_figure(Cell_prop& figure);

	void mover_is_check();
};

#endif // !CHESS_GAME_H