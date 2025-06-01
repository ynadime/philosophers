#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_alloc_list
{
	void				*ptr;
	struct s_alloc_list	*next;
}						t_alloc_list;

typedef struct s_data
{
	int					num_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					end_simulation;
	int					must_eat;
	size_t				begin;
}						t_data;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	pthread_mutex_t		*write_lock;
	pthread_mutex_t		*data_lock;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	int					meals_eaten;
	size_t				last_meal;
	t_data				*data;

}						t_philo;

int						init_data(t_data *data, char **av);
int						init_forks(pthread_mutex_t *forks, int num_of_forks);
int						init_mutexes(pthread_mutex_t *write_lock,
							pthread_mutex_t *data_lock, pthread_mutex_t *forks,
							int num_of_forks);
int						init_philo(t_philo *philo, t_data *data);
void					free_memory(void);
void					*ft_malloc(size_t size);
void					free_all_resources(t_philo *philo);
void					start_simulation(t_philo *philo);
int 					simulation_ended(t_philo *philo);
void					*routine(void *arg);
void					print_status(t_philo *philo, char *msg);
size_t					get_time(void);
void	ft_sleep(size_t ms, t_philo *philo);
int						ft_isdigit(int c);
int						ft_atoi(const char *str);

#endif