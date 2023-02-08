#include "term.h"



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

t_settings *init_settings(void)
{
	t_settings *res;

	res = malloc(sizeof(t_settings));
	res->pressed = malloc(sizeof(int));
	res->pressed[0] = 0;
	res->pressed_lock = malloc(sizeof(pthread_mutex_t));
	res->scene_size = get_screen_size();
	res->initial_scene = make_scene(res->scene_size[0] - 1, res->scene_size[1] - 1);
	res->actual_scene = copy_scene(res->initial_scene, res->scene_size[0] - 1, res->scene_size[1] - 1);
	pthread_mutex_init(res->pressed_lock, NULL);
	res->value = 0;
	res->pressed_thread = create_thread();
	return (res);
}

void	clear_settings(t_settings *settings)
{
	pthread_mutex_lock(settings->pressed_lock);
	settings->pressed[0] = -1;
	pthread_mutex_unlock(settings->pressed_lock);
	pthread_join(*settings->pressed_thread, NULL);
	free(settings->pressed);
	pthread_mutex_destroy(settings->pressed_lock);
	free(settings->pressed_lock);
	free(settings->pressed_thread);
	free(settings->scene_size);
	free_scene(settings->initial_scene);
	free_scene(settings->actual_scene);
	free(settings);

}


// void	check_leaks()
// {
// 	system("leaks a.out");
// }

int equal_size(int *s1, int *s2)
{
	if (s1[0] == s2[0] && s1[1] == s2[1])
		return (1);
	return (0);
}

t_object *make_stone()
{
	t_object *res;

	res = create_object("objects/ball.txt");
	res->total_clicks_till_move = 1;
	res->clicks_till_move = 10;
	res->x = 30;
	res->y = 30;
	res->x_dir = 3;
	res->y_dir = 1;
	return (res);
}

void	bouncy_move(t_object *object, t_settings *settings)
{
	t_scene *scene = settings->actual_scene;
	if (!object->clicks_till_move)
	{
		remove_object_from_scene(object, scene, settings->initial_scene);
		object->x += object->x_dir;
		if (object->x + object->x_size >= scene->x)
		{
			object->x_dir *=-1;
			object->x = scene->x - object->x_size - 1;
		}
		if (object->x<= 0)
		{
			object->x_dir *=-1;
			object->x = 1;
		}
		object->y += object->y_dir;
		if (object->y + object->y_size >= scene->y)
		{
			object->y_dir *=-1;
			object->y = scene->y - object->y_size - 1;
		}
		if (object->y <= 0)
		{
			object->y_dir *=-1;
			object->y = 1;
		}
		add_object_to_scene(object, scene);
		object->clicks_till_move = object->total_clicks_till_move;
	}
	add_object_to_scene(object, scene);
	object->clicks_till_move--;
}


int main (int argc, char **argv)
{
	int	*mid_value;
	int c = 0;
	t_settings *settings;
	t_object *object;
	t_object *ball, *ball1, *ball2, *ball3;
	char **scene;

	settings = init_settings();
	object = create_object("objects/object.txt");
	ball = make_stone();
	ball1 = make_stone();
	ball1->x_dir *= -1;
	ball2 = make_stone();
	ball2->y_dir *= -3;
	ball3 = make_stone();
	ball3->y_dir *= -2;
	ball3->x_dir *= -1;
	change_echo();
	change_raw();
	// atexit(check_leaks);
	run_pressed_thread(settings);
	while (c != '!')
	{
		c = get_pressed(settings);
		mid_value = get_screen_size();
		if (!equal_size(settings->scene_size, mid_value))
		{
			free(settings->scene_size);
			settings->scene_size = mid_value;
			free_scene(settings->initial_scene);
			free_scene(settings->actual_scene);
			settings->initial_scene = make_scene(mid_value[0] - 1, mid_value[1] - 1);
			settings->actual_scene = copy_scene(settings->initial_scene, settings->scene_size[0] - 1, settings->scene_size[1] - 1);
		}
		else
			free(mid_value);
		remove_object_from_scene(object, settings->actual_scene, settings->initial_scene);
		if (c == 'w')
			object->y--;
		if (c == 's')
			object->y++;
		if (c == 'a')
			object->x -= 2;
		if (c == 'd')
			object->x += 2;
		bouncy_move(ball, settings);
		bouncy_move(ball1, settings);
		bouncy_move(ball2, settings);
		bouncy_move(ball3, settings);
		add_object_to_scene(object, settings->actual_scene);
		draw_scene(settings->actual_scene);
		printf("press WASD to move\n");
		usleep(30000);
	}
	free_object(object);
	clear_settings(settings);
	printf("\n");
	change_raw();
	change_echo();
}