#pragma once

struct Play;
class Board;
class Player;

using namespace std;

class MoveAlgorithm
{
public:
	MoveAlgorithm() = default;
	virtual ~MoveAlgorithm() = 0;
	virtual Play moveDraught(Board board, Player player) = 0;
};

