#include "term.h"


void	*thread(void	*input)
{
	t_settings *settings;

	int c;
	settings = (t_settings *) input;

	while (1)
	{
		c = getchar();
		pthread_mutex_lock(settings->pressed_lock);
		if (settings->pressed[0] == -1)
		{
			pthread_mutex_unlock(settings->pressed_lock);
			return (NULL);
		}
		settings->pressed[0] = c;
		pthread_mutex_unlock(settings->pressed_lock);
		usleep(100);
	}
}

int	get_pressed(t_settings *settings)
{
	int	res;

	pthread_mutex_lock(settings->pressed_lock);
	res = settings->pressed[0];
	settings->pressed[0] = 0;
	pthread_mutex_unlock(settings->pressed_lock);
	return (res);
}

pthread_t	*create_thread(void)
{
	pthread_t	*res;

	res = malloc(sizeof(pthread_t));
	return (res);
}

void	run_pressed_thread(t_settings *settings)
{
	pthread_create(settings->pressed_thread, NULL, thread, settings);
}
