﻿#include "Chess_game.h"

using pair_coordinates = pair<pair<int, int>, pair<int, int>>;

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
	white_king_coordinate = { 0, 4 };
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
	black_king_coodinate = { 7, 4 };

	make_move();
}

void Chess_game::make_move()
{
	pair_coordinates cordinate = { {0, 0}, {0, 0} };

	string moves;
	//Запускаем цикл ходов, пока не произойдет break внутри цикла
	while (true)
	{
		cout << *this;
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
				move_figure(cordinate.first, cordinate.second);
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

pair_coordinates Chess_game::translate_move_coordinate(string& str_coordinate)
{
	pair<int, int> start_pos, finish_pos;
	if (check_str_coordinate(str_coordinate))
	{	//Удаляем все пробелы из строки, а затем вычисляем координаты клетки в массиве board_chess
		//static_cast<int>('a') = 97, а static_cast<int>('1') = 49, 
		//поэтому для получения координат вычитаем 97 и 49 соответсвенно
		str_coordinate.erase(remove(str_coordinate.begin(), str_coordinate.end(), ' '), str_coordinate.end());
		start_pos = { static_cast<int>(str_coordinate[1]) - 49, static_cast<int>(str_coordinate[0]) - 97 };
		finish_pos = { static_cast<int>(str_coordinate[3]) - 49, static_cast<int>(str_coordinate[2]) - 97 };
	}
	else
	{
		throw exception("Введены неправильные координаты или команда, пожалуйста, проверьте раскладку и попробуйте еще раз.");
	}

	if (start_pos == finish_pos)
	{
		throw exception("Фигура не может остаться на месте");
	}
	return { start_pos, finish_pos };
}


bool Chess_game::check_str_coordinate(string_view str_coordinate) const
{
	static const regex r(R"(\s*[a-h][1-8]\s+[a-h][1-8]\s*)");
	return regex_match(str_coordinate.data(), r);
}


bool Chess_game :: check_int_coordinate(int start_coordinate, int finish_coordinate) const
{
	if (start_coordinate >= 0 && start_coordinate <= 7 && finish_coordinate >= 0 && finish_coordinate <= 7)
		return true;
	return false;

}

void Chess_game::move_figure(pair<int, int> start_move, pair<int, int> finish_move)
{
	if (chess_board[start_move.first][start_move.second].figure_color != (is_move_white ? Ceil_Figure_color::White : Ceil_Figure_color::Black))
	{	//Если на позиции, с которой фигура ходит, стоит фигура другого игрока или не стоит фигура вовсе, то бросаем исключение
		throw exception("На введенной позиции не стоит ваша фигура!");
	}

	if (chess_board[start_move.first][start_move.second].figure_color == chess_board[finish_move.first][finish_move.second].figure_color)
	{	//Если игрок пытается сходить на позицию, на которой стоит его фигура, то бросаем исключение
		throw exception("Вы не можете сходить фигурой туда, где уже стоит ваша фигура!");
	}

	if (!mover_check(start_move, finish_move))
	{
		throw exception("Данная фигура не может так ходить!");
	}

	if (!check_of_check(start_move, finish_move))
	{
		throw exception("После данного хода вашему королю будет шах!");
	}

	//Если ни одно из исключений не сработало, то перемещаем фигуру и обновляем координаты короля

	chess_board[finish_move.first][finish_move.second] = chess_board[start_move.first][start_move.second];
	chess_board[start_move.first][start_move.second] = { Ceil_Figure_color::no, Ceil_Figure_type::none };
	if (chess_board[finish_move.first][finish_move.second].figure_type == Ceil_Figure_type::K)
	{
		(is_move_white ? white_king_coordinate : black_king_coodinate) = finish_move;
	}
	is_move_white = !is_move_white;

	//После хода проверяем, не произошло ли мата.
	if (!check_of_check_mate())
	{
		throw exception("ШАХ И МАТ!");
	}
}

bool Chess_game::mover_check(pair<int, int> start_move, pair<int, int> finish_move)
{
	if (chess_board[start_move.first][start_move.second].figure_type == Ceil_Figure_type::B)
	{
		return bishop_mover_check(start_move, finish_move);
	}
	else if (chess_board[start_move.first][start_move.second].figure_type == Ceil_Figure_type::R)
	{
		return rook_mover_check(start_move, finish_move);
	}
	else if (chess_board[start_move.first][start_move.second].figure_type == Ceil_Figure_type::N)
	{
		return knight_mover_check(start_move, finish_move);
	}
	else if (chess_board[start_move.first][start_move.second].figure_type == Ceil_Figure_type::Q)
	{
		return queen_mover_check(start_move, finish_move);
	}
	else if (chess_board[start_move.first][start_move.second].figure_type == Ceil_Figure_type::p)
	{
		return pawn_mover_check(start_move, finish_move);
	}
	else if (chess_board[start_move.first][start_move.second].figure_type == Ceil_Figure_type::K)
	{
		return king_mover_check(start_move, finish_move);
	}
	return false;
}


bool Chess_game::pawn_mover_check(pair<int, int> start_move, pair<int, int> finish_move)
{
	//Случай, когда игрок ходит пешкой через 1 поле
	if (start_move.second == finish_move.second && abs(finish_move.first - start_move.first) == 2 && (start_move.first == 1 || start_move.first == 6) && 
		(is_move_white && finish_move.first > start_move.first || !is_move_white && finish_move.first < start_move.first) && 
		chess_board[finish_move.first][finish_move.second].figure_color == Ceil_Figure_color::no)
	{
		return true;
	}
	//Случай, когда игрок ходить пешкой на 1 поле вперед
	if (start_move.second == finish_move.second && abs(finish_move.first - start_move.first) == 1 && 
		(is_move_white && finish_move.first > start_move.first || !is_move_white && finish_move.first < start_move.first) &&
		chess_board[finish_move.first][finish_move.second].figure_color == Ceil_Figure_color::no)
	{
		return true;
	}
	//Случай, когда игрок ест пешкой вражескую фигуру
	if (abs(finish_move.first - start_move.first) == 1 && abs(finish_move.second - start_move.second) == 1 &&
		(is_move_white && finish_move.first > start_move.first || !is_move_white && finish_move.first < start_move.first) && 
		chess_board[finish_move.first][finish_move.second].figure_color == (is_move_white ? Ceil_Figure_color::Black : Ceil_Figure_color::White))
	{
		return true;
	}

	return false;
}

bool Chess_game::knight_mover_check(pair<int, int> start_move, pair<int, int> finish_move)
{
	if ((abs(finish_move.first - start_move.first) == 2 && abs(finish_move.second - start_move.second) == 1 ||
		abs(finish_move.first - start_move.first) == 1 && abs(finish_move.second - start_move.second) == 2) &&
		chess_board[finish_move.first][finish_move.second].figure_color != (is_move_white ? Ceil_Figure_color::White : Ceil_Figure_color::Black))
	{
		return true;
	}
	return false;
}

bool Chess_game::rook_mover_check(pair<int, int> start_move, pair<int, int> finish_move)
{	//У ладьи обязательно после хода одна из координат должна остаться прежней, поэтому
	//проверяем каждую и итерируемся по другой, проверяя, нет ли на пути ладьи фигур
	if (start_move.first == finish_move.first)
	{
		for (int i = start_move.second + ((start_move.second < finish_move.second) ? 1 : (-1)); i != finish_move.second; i += (start_move.second < finish_move.second) ? 1 : (-1))
		{
			if (chess_board[start_move.first][i].figure_type != Ceil_Figure_type::none)
			{
				return false;
			}
		}
		if (chess_board[finish_move.first][finish_move.second].figure_color == (is_move_white ? Ceil_Figure_color::White : Ceil_Figure_color::Black))
		{
			return false;
		}
	}
	else if (start_move.second == finish_move.second)
	{
		for (int i = start_move.first + ((start_move.first < finish_move.first) ? 1 : (-1)); i != finish_move.first; i += (start_move.first < finish_move.first) ? 1 : (-1))
		{
			if (chess_board[i][start_move.second].figure_type != Ceil_Figure_type::none)
			{
				return false;
			}
		}
		if (chess_board[finish_move.first][finish_move.second].figure_color == (is_move_white ? Ceil_Figure_color::White : Ceil_Figure_color::Black))
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	return true;
}

bool Chess_game::bishop_mover_check(pair<int, int> start_move, pair<int, int> finish_move)
{	//для передвижения по диагонали слону обязательно нужно передвинуться на одинковое количество клеток по вертикали и горизонтали 
	if (abs(start_move.first - finish_move.first) == abs(start_move.second - finish_move.second))
	{
		for (int i = start_move.first + ((start_move.first < finish_move.first) ? 1 : (-1)), j = start_move.second + ((start_move.second < finish_move.second) ? 1 : (-1)); 
			i != finish_move.first; 
			i += (start_move.first < finish_move.first) ? 1 : (-1), j += (start_move.second < finish_move.second) ? 1 : (-1))
		{
			if (chess_board[i][j].figure_type != Ceil_Figure_type::none &&
				i != finish_move.first && j != finish_move.second)
			{
				return false;
			}
		}
		if (chess_board[finish_move.first][finish_move.second].figure_color == (is_move_white ? Ceil_Figure_color::White : Ceil_Figure_color::Black))
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	return true;
}

bool Chess_game::queen_mover_check(pair<int, int> start_move, pair<int, int> finish_move)
{	//Королева может хрдить либо также как слон, либо как ладья,
	//Поэтому стоит использовать уже написанные методы
	if (start_move.first == finish_move.first || start_move.second == finish_move.second)
	{
		return rook_mover_check(start_move, finish_move);
	}
	else if (abs(start_move.first - finish_move.first) == abs(start_move.second - finish_move.second))
	{
		return bishop_mover_check(start_move, finish_move);
	}
	return false;
}


bool Chess_game::king_mover_check(pair<int, int> start_move, pair<int, int> finish_move)
{	//Король должен просто переместиться максимум на 1 клетку в любую (или каждую) из сторон,
	//где нет союзника (проверка на наличие вражеского короля рядом или шаха будет в другой функции
	if (abs(start_move.first - finish_move.first) <= 1 && abs(start_move.second - finish_move.second) <= 1 &&
		chess_board[finish_move.first][finish_move.second].figure_color != (is_move_white ? Ceil_Figure_color::White : Ceil_Figure_color::Black))
	{
		return true;
	}
	return false;
}


bool Chess_game::check_of_check(pair<int, int> king_coordinate)
{
	is_move_white = !is_move_white;
	for (int i = 0; i < (sizeof(chess_board) / sizeof(*(chess_board))); i++)
	{
		for (int j = 0; j < sizeof(chess_board[i]) / sizeof(*(chess_board[i])); j++)
		{
			if (chess_board[i][j].figure_color == (is_move_white ? Ceil_Figure_color::White : Ceil_Figure_color::Black))
			{
				if (mover_check({ i, j }, king_coordinate))
				{
					is_move_white = !is_move_white;
					return false;
				}
			}
		}
	}
	is_move_white = !is_move_white;
	return true;
}

bool Chess_game::check_of_check(pair<int, int> start_move, pair<int, int> finish_move)
{
	//Временно перемещаем фигуру на ту клетку, на которой она должна стоять и меняем очередность хода
	//НЕ ЗАБЫТЬ ВЕРНУТЬ ЕЕ ОБРАТНО!!!!!
	Cell_prop copy_ceil = { chess_board[finish_move.first][finish_move.second].figure_color, chess_board[finish_move.first][finish_move.second].figure_type };
	chess_board[finish_move.first][finish_move.second] = chess_board[start_move.first][start_move.second];
	
	chess_board[start_move.first][start_move.second] = { Ceil_Figure_color::no, Ceil_Figure_type::none };
	is_move_white = !is_move_white;

	//Проверяем ходит ли сейчас король
	pair<int, int> frendly_king_coordinate;
	if (chess_board[finish_move.first][finish_move.second].figure_type == Ceil_Figure_type::K)
	{
		frendly_king_coordinate = { finish_move.first, finish_move.second };
	}
	else
	{	//Не забываем про то, что мы поменяли очередность хода
		frendly_king_coordinate = (!is_move_white ? white_king_coordinate : black_king_coodinate);
	}

	for (int i = 0; i < (sizeof(chess_board) / sizeof(*(chess_board))); i++)
	{
		for (int j = 0; j < sizeof(chess_board[i]) / sizeof(*(chess_board[i])); j++)
		{
			if (chess_board[i][j].figure_color == (is_move_white ? Ceil_Figure_color::White : Ceil_Figure_color::Black))
			{
				if (mover_check({ i, j }, frendly_king_coordinate))
				{
					//Перед возвратом функции нужно вернуть фигуру обратно
					chess_board[start_move.first][start_move.second] = chess_board[finish_move.first][finish_move.second];
					chess_board[finish_move.first][finish_move.second] = copy_ceil;
					is_move_white = !is_move_white;
					return false;
				}
			}
		}
	}

	//Перед возвратом функции нужно вернуть фигуру обратно
	chess_board[start_move.first][start_move.second] = chess_board[finish_move.first][finish_move.second];
	chess_board[finish_move.first][finish_move.second] = copy_ceil;
	is_move_white = !is_move_white;
	return true;
}


bool Chess_game::check_of_check_mate()
{// Алгоритм:
 //1) координаты короля = (получаем координаты для проверяемого короля) - done
 //2) Проверка 8 клеток вокруг короля, есть ли на них шах. - done
 //3) Создаем френдли фигуру - done
 //4) Проверяем, будет ли шах при перемещении ее на различнчые клетки - done
 //5) Если шаха нет, то добавляем координаты клетки в вектор - done
 //6) Удаляем френдли фигуру, если мы ее создали -done
 //7) Для всех остальных френди фигур проверяем, способны ли они переместиться на одну из тех координат и будет ли шах после перемещения -done
 //8) Если ни одна фигура не подойдет, то это мат -done 

	pair<int, int> king_coordinate = (is_move_white ? white_king_coordinate : black_king_coodinate);
	vector<pair<int, int>> ceils_for_check;
	//Проверка на угрозу шаха королю впринципе
	if (check_of_check(king_coordinate))
	{
		return true;
	}

	//Проверка 8 клеток вокруг короля на возможность уйти от шаха
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (check_int_coordinate(king_coordinate.first + i, king_coordinate.second + j))
			{
				if (mover_check(king_coordinate, { king_coordinate.first + i, king_coordinate.second + j }) && check_of_check(king_coordinate, { king_coordinate.first + i, king_coordinate.second + j }))
				{
					return true;
				}
			}
		}
	}

	//Создаем френдли фигуру на поле 
	pair<int, int> frendly_figure = { -1, -1 };																								//Переменная для запоминания старого значения клетки
	for (int i = 0; i < (sizeof(chess_board) / sizeof(*(chess_board))); i++)
	{
		for (int j = 0; j < sizeof(chess_board[i]) / sizeof(*(chess_board[i])); j++)
		{
			if (chess_board[i][j].figure_color == Ceil_Figure_color::no )
			{
				frendly_figure = { i, j };
				//Создаем временную френди фигуру на найденом поле
				chess_board[i][j] = { (is_move_white ? Ceil_Figure_color::White : Ceil_Figure_color::Black), Ceil_Figure_type::Q };
				break;
			}
		}
		//Если мы нашли и клетку для френли фигуры, то выходим из цикла
		if (frendly_figure.first > -1)
			break;
	}

	//Обходим все поле и добавляем все клетки при перемещении на которые шаха нет
	for (int i = 0; i < (sizeof(chess_board) / sizeof(*(chess_board))); i++)
	{
		for (int j = 0; j < sizeof(chess_board[i]) / sizeof(*(chess_board[i])); j++)
		{
			if (check_of_check(frendly_figure, {i, j}))
			{
				ceils_for_check.push_back({ i, j });
			}
		}
	}

	//Нужно проверить, не произойдет ли переполнения массива при попытке вернуть созданную френди клетку к исходному значению
	if (frendly_figure.first >= 0 && frendly_figure.first <= 7 && frendly_figure.second <= 7 && frendly_figure.second >= 0)
		chess_board[frendly_figure.first][frendly_figure.second] = { Ceil_Figure_color::no, Ceil_Figure_type::none };
	else
		throw exception("Ошибка при расчете шах и мата");

	//Ищем все союзные фигуры и пробуем передвинуть их на клетки "отменяющие" шах
	for (int i = 0; i < (sizeof(chess_board) / sizeof(*(chess_board))); i++)
	{
		for (int j = 0; j < sizeof(chess_board[i]) / sizeof(*(chess_board[i])); j++)
		{
			if (chess_board[i][j].figure_color == (is_move_white ? Ceil_Figure_color::White : Ceil_Figure_color::Black))
			{
				for (auto& k : ceils_for_check)
				{
					if (mover_check({ i, j }, k) && check_of_check({ i, j }, k))
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}