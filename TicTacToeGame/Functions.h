#pragma once

#include "Defines.h"
#include <ranges>

static void NewGame() noexcept
{
	++g_GameNumber;
	g_IsGameOver = false;
	g_Turn       = Cell::X;
	g_UserInput  = INVALID_INPUT;
	b_choice	 = BOT_DEFAULT;

	for (auto& cell : g_Board)
	{
		cell = Cell::Empty;
	}
}

static Winner GetWinner() noexcept
{
	for (const auto i : std::ranges::views::iota(0, 8))
	{
		if (g_Board[win_patterns[i][0]] != Cell::Empty &&
			g_Board[win_patterns[i][0]] == g_Board[win_patterns[i][1]] &&
			g_Board[win_patterns[i][0]] == g_Board[win_patterns[i][2]]) 
		{
			g_IsGameOver = true;

			if (const auto winner{ g_Board[win_patterns[i][0]] }; winner == Cell::X)
			{
				return Winner::X;
			}
			else if (winner == Cell::O)
			{
				return Winner::O;
			}
		}
	}

	for (const auto cell : g_Board)
	{
		if (cell == Cell::Empty)
		{
			return Winner::None;
		}
	}

	g_IsGameOver = true;
	return Winner::Tie;
}

static void WinX() noexcept
{
	++g_WinX;
}

static void WinO() noexcept
{
	++g_WinO;
}

static void Tie() noexcept
{
	++g_Tie;
}


static void ChoiceStrategy() noexcept
{
	if (b_choice > FAILED_STRATEGY)
	{
		for (size_t idx = 0; idx < g_Board.size(); ++idx)
		{
			if (g_Board[idx] == Cell::Empty)
			{
				g_Board[idx] = Cell::O;
				return;
			}
		}
	}
	
	for (const auto el : win_patterns[b_choice])
	{
		if (g_Board[el] != Cell::Empty && g_Board[el] != Cell::O)
		{
			++b_choice;
			ChoiceStrategy();
			return;
		}
	}
}

static void BotCell() noexcept
{
	ChoiceStrategy();
	if (b_choice <= FAILED_STRATEGY)
	{
		for (const auto el: win_patterns[b_choice])
		{
			if (g_Board[el] == Cell::Empty)
			{
				g_Board[el] = Cell::O;
				break;
			}
		}
	}
}