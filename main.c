/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:16:16 by tlize             #+#    #+#             */
/*   Updated: 2025/08/11 21:42:45 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char **argv)
{
    t_data data;

    if (argc !=5 && argc != 6)
    {
        printf("Mauvais nombre d'arguments\n");
        return (1);
    }
	if (init_data(&data, argc, argv))
    {
        printf("Erreur d'initialisation\n");
        return (1);
    }
	return (0);
}