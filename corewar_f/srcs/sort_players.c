/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 15:17:23 by bcherkas          #+#    #+#             */
/*   Updated: 2018/07/07 16:22:58 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	swap(int *a, int *b)
{
	int		c;

	c = *a;
	*a = *b;
	*b = c;
}

void	sort_linked_arrs(int *fds, int *nums, int max)
{
	int		i;
	int		j;

	i = max;
	j = 0;
	while (i > 1)
	{
		while (j < i - 1)
		{
			if ((nums[j] > nums[j + 1] && nums[j + 1] > -1)
					|| (nums[j] == -1 && nums[j + 1] != -1))
			{
				swap(nums + j, nums + j + 1);
				swap(fds + j, fds + j + 1);
			}
			j++;
		}
		j = 0;
		i--;
	}
}
