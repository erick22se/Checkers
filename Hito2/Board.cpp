#include "Board.h"
#include "rlutil.h"
#include "Player.h"

Board::Board()
{
	fillBoard();
	fillDraughts();
}

void Board::fillDraughts()
{
	for (auto i = 0; i < 3; ++i) {
		int x = i;
		for (auto j = i % 2 == 0 ? 0 : 1; j < COLUMNS; j += 2) {
			Draught draught;
			draught.point.x = x;
			draught.point.y = j;
			draught.draughtType = DraughtType::NORMAL;
			draught.playerColor = PlayerColor::PLAYER_WHITE;
			whiteDraughts.insert(draught);
		}
	}
	for (auto i = 5; i < 8; ++i) {
		int x = i;
		for (auto j = i % 2 == 0 ? 0 : 1; j < COLUMNS; j += 2) {
			Draught draught;
			draught.point.x = x;
			draught.point.y = j;
			draught.draughtType = DraughtType::NORMAL;
			draught.playerColor = PlayerColor::PLAYER_RED;
			redDraughts.insert(draught);
		}
	}
}

void Board::fillBoard()
{
	board = {
		{ WHITE, EMPTY, WHITE, EMPTY, WHITE, EMPTY, WHITE, EMPTY },
		{ EMPTY, WHITE, EMPTY, WHITE, EMPTY, WHITE, EMPTY, WHITE },
		{ WHITE, EMPTY, WHITE, EMPTY, WHITE, EMPTY, WHITE, EMPTY },
		{ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
		{ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
		{ EMPTY, RED  , EMPTY, RED  , EMPTY, RED  , EMPTY, RED },
		{ RED  , EMPTY, RED  , EMPTY, RED  , EMPTY, RED  , EMPTY },
		{ EMPTY, RED  , EMPTY, RED  , EMPTY, RED  , EMPTY, RED }
	};
}

void Board::printBoard(){
	cout << "+";
	for (auto i = 0; i < ROWS; ++i)
		cout << "---+";
	cout << endl;
	for (auto i = 0; i < ROWS; ++i) {
		cout << "|";
		for (auto j = 0; j < COLUMNS; ++j) {
			switch (board[i][j]) {
			case EMPTY:
				cout << "   |";
				break;
			case WHITE:
				rlutil::setColor(15);
				cout << " " << NORMAL_PIECE << " |";
				break;
			case RED:
				rlutil::setColor(4);
				cout << " " << NORMAL_PIECE;
				rlutil::setColor(15);
				cout << " |";
				break;
			}
		}
		rlutil::setColor(15);
		cout << endl;
		cout << "+";
		for (auto j = 0; j < ROWS; ++j)
			cout << "---+";
		cout << endl;
	}
}

vector<Draught> Board::possibleMoves(PlayerColor color)
{
	return vector<Draught>();
}

bool Board::isSameColor(int x, int y, Draught draught)
{
	if (board[x][y] == RED && draught.playerColor == PlayerColor::PLAYER_RED)
		return true;
	else if (board[x][y] == WHITE && draught.playerColor == PlayerColor::PLAYER_WHITE)
		return true;
	else
		return false;
}

bool Board::isInLimits(int x, int y)
{
	if (x <= -1 || x >= ROWS || y <= -1 || y >= COLUMNS)
		return false;
	return true;
}

bool Board::isInLimits(Draught draught, Move move)
{
	int draughtX = draught.point.x;
	int draughtY = draught.point.y;
	switch (move) {
		case Move::DIAGONAL_TOP_LEFT: {
			int x = draughtX - 1;
			int y = draughtY - 1;
			return isInLimits(x, y) ? true : false;
		}
		case Move::DIAGONAL_TOP_RIGHT: {
			int x = draughtX - 1;
			int y = draughtY + 1;
			return isInLimits(x, y) ? true : false;
		}
		case Move::DIAGONAL_DOWN_LEFT: {
			int x = draughtX + 1;
			int y = draughtY - 1;
			return isInLimits(x, y) ? true : false;
		}
		case Move::DIAGONAL_DOWN_RIGHT: {
			int x = draughtX + 1;
			int y = draughtY + 1;
			return isInLimits(x, y) ? true : false;
		}
	}
}

void Board::updateBoard(int x, int y, PlayerColor color)
{
	color == PlayerColor::PLAYER_WHITE ? board[x][y] = WHITE : board[x][y] = RED;
}

void Board::updateBoard(int x, int y, int color)
{
	board[x][y] = color;
}

MoveStatus Board::move(Player &player, Draught&draught, Move move)
{
	int draughtX = draught.point.x;
	int draughtY = draught.point.y;

	switch (move) {
		case Move::DIAGONAL_TOP_LEFT: {
			if (isInLimits(draught, move)) {
				int x = draughtX - 1;
				int y = draughtY - 1;
				if (board[x][y] == EMPTY ) 
					return MoveStatus::MOVE_BLANK;
				else if (isSameColor(x, y, draught))
					return MoveStatus::MOVE_IMPOSSIBLE;
				else {
					int tempX = x - 1;
					int tempY = y - 1;
					if (isInLimits(tempX, tempY) && board[tempX][tempY] == EMPTY)
						return MoveStatus::MOVE_ENEMY;
				}
			}
			break;
		}

		case Move::DIAGONAL_TOP_RIGHT: {
			if (isInLimits(draught, move)) {
				int x = draughtX - 1;
				int y = draughtY + 1;
				if (board[x][y] == EMPTY) 
					return MoveStatus::MOVE_BLANK;
				else if (isSameColor(x, y, draught))
					return MoveStatus::MOVE_IMPOSSIBLE;
				else {
					int tempX = x - 1;
					int tempY = y + 1;
					if (isInLimits(tempX, tempY) && board[tempX][tempY] == EMPTY)
						return MoveStatus::MOVE_ENEMY;
				}
			}
			break;
		}

		case Move::DIAGONAL_DOWN_LEFT: {
			if (isInLimits(draught, move)) {
				int x = draughtX + 1;
				int y = draughtY - 1;
				if (board[x][y] == EMPTY) 
					return MoveStatus::MOVE_BLANK;				
				else if (isSameColor(x, y, draught))
					return MoveStatus::MOVE_IMPOSSIBLE;
				else {
					int tempX = x + 1;
					int tempY = y - 1;
					if (isInLimits(tempX, tempY) && board[tempX][tempY] == EMPTY)
						return MoveStatus::MOVE_ENEMY;
				}
			}
			break;
		}

		case Move::DIAGONAL_DOWN_RIGHT: {
			if (isInLimits(draught, move)) {
				int x = draughtX + 1;
				int y = draughtY + 1;
				if (board[x][y] == EMPTY) {
					return MoveStatus::MOVE_BLANK;
				}
				else if (isSameColor(x, y, draught))
					return MoveStatus::MOVE_IMPOSSIBLE;
				else {
					int tempX = x + 1;
					int tempY = y + 1;
					if (isInLimits(tempX, tempY) && board[tempX][tempY] == EMPTY)
						return MoveStatus::MOVE_ENEMY;
				}
			}
			break;
		}
	}
	return MoveStatus::MOVE_IMPOSSIBLE;
}
