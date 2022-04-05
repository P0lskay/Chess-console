#pragma once
#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include <array>
#include <iostream>

using namespace std;

enum Ceil_Figure_color
	{
		Black,
		White,
		none
	};
enum Ceil_Figure_type
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
	Ceil_Figure_color figure_color = Ceil_Figure_color::none;
	Ceil_Figure_type figure_type = Ceil_Figure_type::none;

	ostream& operator << (ostream& os) const;
};

class Chess_game
{
public:
	Chess_game();
	~Chess_game();

private:
	Cell_prop chess_board[8][8];
	bool is_move_white = true;

	void start_new_game();
	
	template<class T>
	void move_figure(Cell_prop& figure);

	void mover_is_check();
};


#endif // !CHESS_GAME_H