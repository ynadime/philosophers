/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynadime <ynadime@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:49:57 by ynadime           #+#    #+#             */
/*   Updated: 2025/06/03 14:55:16 by ynadime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_data(t_data *data, char **av)
{
	data->num_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->end_simulation = 0;
	if (av[5])
		data->must_eat = ft_atoi(av[5]);
	else
		data->must_eat = -1;
	if (!data->num_of_philo || !data->time_to_die || !data->time_to_eat
		|| !data->time_to_sleep || !data->must_eat)
		return (write(2, "Invalid Arguments\n", 18));
	return (0);
}

int	init_forks(pthread_mutex_t *forks, int num_of_forks)
{
	int	i;
	int	j;

	i = 0;
	while (i < num_of_forks)
	{
		if (pthread_mutex_init(&forks[i], NULL))
		{
			j = 0;
			while (j < i)
			{
				pthread_mutex_destroy(&forks[j]);
				j++;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_mutexes(pthread_mutex_t *write_lock, pthread_mutex_t *data_lock,
		pthread_mutex_t *forks, int num_of_forks)
{
	int	i;
	int	j;

	if (pthread_mutex_init(write_lock, NULL))
		return (1);
	else if (pthread_mutex_init(data_lock, NULL))
		return (pthread_mutex_destroy(write_lock), 1);
	i = 0;
	while (i < num_of_forks)
	{
		if (pthread_mutex_init(&forks[i], NULL))
		{
			j = 0;
			while (j < i)
			{
				pthread_mutex_destroy(&forks[j]);
				j++;
			}
			return (pthread_mutex_destroy(write_lock),
				pthread_mutex_destroy(data_lock), 1);
		}
		i++;
	}
	return (0);
}

int	init_philo(t_philo *philo, t_data *data)
{
	int				i;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*data_lock;
	pthread_mutex_t	*forks;

	write_lock = ft_malloc(sizeof(pthread_mutex_t));
	data_lock = ft_malloc(sizeof(pthread_mutex_t));
	forks = ft_malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	if (init_mutexes(write_lock, data_lock, forks, data->num_of_philo))
		return (1);
	i = 0;
	while (i < data->num_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].write_lock = write_lock;
		philo[i].data_lock = data_lock;
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[(i + 1) % data->num_of_philo];
		philo[i].data = data;
		philo[i].meals_eaten = 0;
		i++;
	}
	return (0);
}
