#include "philosophers.h"

#define TRACKER_ADD 0
#define TRACKER_GET 1

t_alloc_list	**tracker(void *ptr, int option)
{
	static t_alloc_list	*alloc_lst;
	t_alloc_list		*new_node;

	if (option == TRACKER_GET)
		return (&alloc_lst);
	else if (option == TRACKER_ADD)
	{
		new_node = (t_alloc_list *)malloc(sizeof(t_alloc_list));
		if (!new_node)
		{
			free_memory();
			free(ptr);
			perror("philosophers: malloc");
			exit(1);
		}
		new_node->ptr = ptr;
		new_node->next = alloc_lst;
		alloc_lst = new_node;
	}
	return (NULL);
}

void	free_memory(void)
{
	t_alloc_list	*next;
	t_alloc_list	**alloc_lst;

	alloc_lst = tracker(NULL, TRACKER_GET);
	while (*alloc_lst)
	{
		next = (*alloc_lst)->next;
		free((*alloc_lst)->ptr);
		free((*alloc_lst));
		(*alloc_lst) = next;
	}
}

void	ft_free(void *ptr)
{
	t_alloc_list	*current;
	t_alloc_list	*previous;
	t_alloc_list	**alloc_lst;

	alloc_lst = tracker(NULL, TRACKER_GET);
	current = *alloc_lst;
	previous = NULL;
	while (current)
	{
		if (current->ptr == ptr)
		{
			if (previous)
				previous->next = current->next;
			else
				*alloc_lst = current->next;
			free(current->ptr);
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		free_memory();
		perror("philosophers: malloc");
		exit(1);
	}
	tracker(ptr, TRACKER_ADD);
	return (ptr);
}

void	free_all_resources(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->num_of_philo)
	{
		pthread_mutex_destroy(philo[i].left_fork);
		i++;
	}
	pthread_mutex_destroy(philo->write_lock);
	pthread_mutex_destroy(philo->data_lock);
	free_memory();
}
