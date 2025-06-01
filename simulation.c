#include "philosophers.h"

int simulation_ended(t_philo *philo)
{
	int status;

	pthread_mutex_lock(philo->data_lock);
	status = philo->data->end_simulation;
	pthread_mutex_unlock(philo->data_lock);
	return status;
}

int	check_death(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->num_of_philo)
	{
		pthread_mutex_lock(philo->data_lock);
		if (get_time() - philo[i].last_meal >= (size_t)philo->data->time_to_die)
		{
			philo->data->end_simulation = 1;
			pthread_mutex_unlock(philo->data_lock);
			pthread_mutex_lock(philo->write_lock);
			printf("%zu %d has died\n", get_time() - philo->data->begin, philo[i].id);
			pthread_mutex_unlock(philo->write_lock);
			return (1);
		}
		pthread_mutex_unlock(philo->data_lock);
		i++;
	}
	return (0);
}

int	check_meals(t_philo *philo)
{
	int	i;

	if (philo->data->must_eat == -1)
		return (0);
	i = 0;
	while (i < philo->data->num_of_philo)
	{
		pthread_mutex_lock(philo->data_lock);
		if (philo[i].meals_eaten < philo->data->must_eat)
		{
			pthread_mutex_unlock(philo->data_lock);
			return (0);
		}
		pthread_mutex_unlock(philo->data_lock);
		i++;
	}
	pthread_mutex_lock(philo->data_lock);
	philo->data->end_simulation = 1;
	pthread_mutex_unlock(philo->data_lock);
	return (1);
}

void	start_simulation(t_philo *philo)
{
	int	i;

	philo->data->begin = get_time();
	i = 0;
	while (i < philo->data->num_of_philo)
	{
		philo[i].last_meal = philo->data->begin;
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]))
			return ;
		i++;
	}
	while (1)
	{
		if (check_death(philo) || check_meals(philo))
			break ;
		usleep(100);
	}
	i = 0;
	while (i < philo->data->num_of_philo)
		pthread_join(philo[i++].thread, NULL);
	free_all_resources(philo);
}
