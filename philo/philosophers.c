/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynadime <ynadime@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:49:48 by ynadime           #+#    #+#             */
/*   Updated: 2025/06/03 14:49:49 by ynadime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac != 5 && ac != 6)
		return (write(2, "Invalid Arguments\n", 18));
	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (write(2, "Invalid Arguments\n", 18));
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;

	if (check_args(ac, av))
		return (1);
	data = (t_data *)ft_malloc(sizeof(t_data));
	if (init_data(data, av))
		return (free_memory(), 1);
	philo = (t_philo *)ft_malloc(sizeof(t_philo) * data->num_of_philo);
	if (init_philo(philo, data))
		return (free_memory(), 1);
	start_simulation(philo);
}
