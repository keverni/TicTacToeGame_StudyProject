#include <iostream>
#include <string>
#include "Functions.h"

void Input() noexcept
{
	if (g_TypeGame == TypeGame::Bot)
	{
		std::cout << "Turn: X" << " [1-9]> ";
	}
	else
	{
		std::cout << "Turn: " << ((g_Turn == Cell::X) ? "X" : "O") << " [1-9]> " ;
	}
	
	std::string input;
	std::getline(std::cin, input);

	try
	{
		g_UserInput = std::stoi(input);
		if (g_UserInput < 1 || g_UserInput > 9)
		{
			throw std::invalid_argument("");
		}

		--g_UserInput;
	}
	catch(const std::exception&)
	{
		g_UserInput = INVALID_INPUT;
	}
}

void Logic() noexcept
{
	if (g_TypeGame == TypeGame::Bot)
	{
		if (g_UserInput >= 0  && g_Turn == Cell::X)
		{
			if (g_Board[g_UserInput] == Cell::Empty)
			{
				g_Board[g_UserInput] = Cell::X;
				g_Turn = Cell::O;
			}
		}
		else if (g_Turn == Cell::O)
		{
			BotCell();
			g_Turn = Cell::X;
		}
	}
	else
	{
		if (g_UserInput >= 0)
		{
			if (g_Board[g_UserInput] == Cell::Empty)
			{
				if (g_Turn == Cell::X)
				{
					g_Board[g_UserInput] = Cell::X;
					g_Turn = Cell::O;
				}
				else if (g_Turn == Cell::O)
				{
					g_Board[g_UserInput] = Cell::O;
					g_Turn = Cell::X;
				}
			}
		}
	}

	if (const auto winner{ GetWinner() }; winner == Winner::X)
	{
		WinX();
	}
	else if (winner == Winner::O)
	{
		WinO();
	}
	else if (winner == Winner::Tie)
	{
		Tie();
	}
	
}

void Draw() noexcept
{
	auto clear_screen = []() noexcept
	{
		system("cls");
	};

	auto draw_line = []() noexcept
	{
		std::cout << ("---------------------------------") << std::endl;
	};

	clear_screen();
	std::cout << "Game #" << g_GameNumber << "\nWin X: " << g_WinX << " | Win O: " << g_WinO << " | Tie: " << g_Tie << std::endl;
	draw_line();

	for (const auto c : std::ranges::views::iota(0, COLUMNS))
	{
		std::cout << ("|\t");
		for (const auto r : std::ranges::views::iota(0, ROWS))
		{
			if (const auto cell{ g_Board[(c * COLUMNS + r)] }; cell == Cell::Empty)
			{
				std::cout << " \t";
			}
			else if (cell == Cell::X)
			{
				std::cout << "X\t";
			}
			else if (cell == Cell::O)
			{
				std::cout << "O\t";
			}
		}

		std::cout << ("|") << std::endl;
	}
	draw_line();
}

int wmain(int argc, wchar_t* argv[]) noexcept
{
	
	for (;;)
	{
		system("cls");
		int GameType = 0;
		std::cout << "Enter game type(0 - Player vs Player, 1 - Player vs Bot): ";
		std::cin >> GameType;
		g_TypeGame = static_cast<TypeGame>(GameType);
		if (g_TypeGame == TypeGame::Bot)
		{
			while (!g_IsGameOver)
			{
				Draw();
				if (g_Turn == Cell::X)
				{
					Input();
				}
				Logic();
			}
		}
		else if (g_TypeGame == TypeGame::Player)
		{
			while (!g_IsGameOver)
			{
				Draw();
				Input();
				Logic();
			}
		}
		else
		{
			continue;
		}

		Draw();

		char input;
		std::cout << "\nDo you want play again (y/n)? > ";
		std::cin >> input;

		if (input == 'y')
		{
			NewGame();
		}
		else
		{
			break;
		}
	}

	return 0;
}
