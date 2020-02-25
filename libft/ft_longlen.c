/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_longlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 15:54:36 by sadawi            #+#    #+#             */
/*   Updated: 2019/12/09 15:54:58 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_longlen(long int nbr)
{
	int i;

	i = 0;
	if (nbr < 0)
		i++;
	while (nbr || i == 0)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}