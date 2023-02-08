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