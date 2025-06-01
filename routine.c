#include "philosophers.h"


void	print_status(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->write_lock);
	if (!simulation_ended(philo))
		printf("%zu %d %s\n", get_time() - philo->data->begin, philo->id, msg);
	pthread_mutex_unlock(philo->write_lock);
}

void	eating(t_philo *philo)
{	
	if(philo->id % 2 == 0)
	{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	}
	else
	{
	ft_sleep(1, philo);
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	}
	print_status(philo, "is eating");
	pthread_mutex_lock(philo->data_lock);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->data_lock);
	ft_sleep(philo->data->time_to_eat, philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_sleep(philo->data->time_to_sleep, philo);
}

void	thinking(t_philo *philo)
{
	print_status(philo, "is thinking");
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_of_philo == 1)
	{
		print_status(philo, "has taken a fork");
		ft_sleep(philo->data->time_to_die, philo);
		return (NULL);
	}
	while (!simulation_ended(philo))
	{	
		eating(philo);
		if(simulation_ended(philo))
		break;
		sleeping(philo);
		if(simulation_ended(philo))
		break;
		thinking(philo);
	}
	return (NULL);
}
