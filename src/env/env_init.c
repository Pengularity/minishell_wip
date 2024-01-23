/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:57:14 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/23 14:18:10 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/exec.h"

t_env	*init_env(void)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->first = NULL;
	env->last = NULL;
	env->len = 0;
	return (env);
}

t_env_element	*init_env_element(void)
{
	t_env_element	*element;

	element = malloc(sizeof(t_env_element));
	if (!element)
		return (NULL);
	element->key = NULL;
	element->value = NULL;
	element->next = NULL;
	element->prev = NULL;
	return (element);
}

