#include "term.h"



char **read_image(char *path)
{
	char **res;
	int	i;
	res = NULL;
	char *one_line;
	char *other_line;
	int fd = open(path, O_RDONLY);

	i = 0;
	one_line = get_next_line(fd);
	res = add_string_to_string_arr(strtok(one_line, "\n"), res, i);
	while (one_line)
	{
		i++;
		free(one_line);
		one_line = get_next_line(fd);
		res = add_string_to_string_arr(strtok(one_line, "\n"), res, i);
	}
	close (fd);
	return (res);
}

t_object *create_object(char *path)
{
	t_object *res;
	int i;

	res = malloc(sizeof(t_object));
	res->x = 0;
	res->y = 0;
	if (path)
		res->image = read_image(path);
	else
		res->image = NULL;
	res->y_size = 0;
	res->x_size = 0;
	if (res->image)
	{
	while(res->image[res->y_size])
	{
		i = 0;
		while (res->image[res->y_size][i])
			i++;
		if (i > res->x_size)
			res->x_size = i;
		res->y_size++;
	}
	}
	return (res);
}

void free_object(t_object *object)
{

	int	i;

	i = 0;
	if (object->image)
	{
		while(object->image[i])
		{
			free(object->image[i]);
			i++;
		}
		free(object->image);
	}
	free(object);
}