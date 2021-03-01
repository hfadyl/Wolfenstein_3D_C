/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfadyl <hfadyl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:21:40 by hfadyl            #+#    #+#             */
/*   Updated: 2020/11/21 14:23:20 by hfadyl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_puterror(char *error)
{
	char *e;

	e = "\033[1;31m Error\n >> \033[0;31m";
	write(1, e, ft_strlen(e));
	write(1, error, ft_strlen(error));
	write(1, "\n", 1);
	return (quit());
}

int	quit(void)
{
	exit(1);
	return (-1);
}
