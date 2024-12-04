#pragma once

#include <vector>

enum class Cell
{
	Empty = 0,
	X,
	O,
};

enum class Winner
{
	None = 0,
	X,
	O,
	Tie,
};

enum class TypeGame
{
	Player = 0,
	Bot
};

static auto g_TypeGame{ TypeGame::Bot };

constexpr auto INVALID_INPUT{ -1 };

constexpr auto ROWS{ 3 };
constexpr auto COLUMNS{ 3 };
constexpr auto BOARD_SIZE{ ROWS * COLUMNS };

static auto g_IsGameOver{ false };
static std::vector g_Board{ BOARD_SIZE, Cell::Empty };

static auto g_GameNumber{ 1 };
static auto g_WinX{ 0 };
static auto g_WinO{ 0 };
static auto g_Tie{ 0 };

static auto g_UserInput{ 0 };
static auto g_Turn{ Cell::X };

constexpr static int win_patterns[8][3]
{
	{ 0, 1, 2 },
	{ 3, 4, 5 },
	{ 6, 7, 8 },
	{ 0, 3, 6 },
	{ 1, 4, 7 },
	{ 2, 5, 8 },
	{ 0, 4, 8 },
	{ 2, 4, 6 } 
};
constexpr auto BOT_DEFAULT{ 0 };

constexpr auto FAILED_STRATEGY{ 7 };
static int	   b_choice{ BOT_DEFAULT };