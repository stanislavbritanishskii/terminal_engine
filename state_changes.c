#include "term.h"

void	change_echo(void)
{
	static	int amount_of_changes = 0;

	static struct termios initial_state;
	if (!amount_of_changes)
		tcgetattr(STDIN_FILENO, &initial_state);
	if (!amount_of_changes % 2)
		initial_state.c_lflag ^= ECHO;
	else
		initial_state.c_lflag ^= ECHO;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &initial_state);
}

void	change_raw(void)
{
	static	int amount_of_changes = 0;

	static struct termios initial_state;
	if (!amount_of_changes)
		tcgetattr(STDIN_FILENO, &initial_state);
	if (!amount_of_changes % 2)
		initial_state.c_lflag ^= ICANON;
	else
		initial_state.c_lflag ^= ICANON;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &initial_state);
}
