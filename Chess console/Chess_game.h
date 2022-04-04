#pragma once
#include <array>

using namespace std;

struct Cell_prop
{
	enum Ceil_Figure_color
	{
		black,
		white,
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

	Ceil_Figure_color figure_color = Ceil_Figure_color::none;
	Ceil_Figure_type figure_type = Ceil_Figure_type::none;
};

class Chess_game
{
public:
	Chess_game();
	~Chess_game();

private:
	Cell_prop chess_board[8][8];
};

