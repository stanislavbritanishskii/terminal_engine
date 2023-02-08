#include "term.h"


char *str_copy(char *str, int n)
{
	char	*res;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	if (n < 0)
	{
		while (str[i++])
			;
		res = malloc(sizeof(char) * i);
		i = -1;
		while (str[++i])
			res[i] = str[i];
		res[i] = '\0';
	}
	else
	{
		res = malloc(sizeof(char) * (n + 1));
		i = -1;
		while (str[++i] && i < n)
			res[i] = str[i];
		res[i] = '\0';
	}
	return (res);
}


char	**add_string_to_string_arr(char *str, char **arr, int n)
{
	char **res;
	int	i;

	i = 0;
	res = malloc(sizeof(char *) * (n + 2));
	if (arr)
	{
		while (i < n)
		{
			res[i] = arr[i];
			i++;
		}
	}
	res[i] = str_copy(str, -1);
	res[i + 1] = NULL;
	free(arr);
	return (res);
}

int	*get_screen_size()
{
	int	*res;

	res = malloc(sizeof(int) * 2);
	struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	res[0] = w.ws_row;
	res[1] = w.ws_col;
	return (res);
}


int equal_size(int *s1, int *s2)
{
	if (s1[0] == s2[0] && s1[1] == s2[1])
		return (1);
	return (0);
}
