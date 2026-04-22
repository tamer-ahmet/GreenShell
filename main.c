/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerri- <mguerri-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:03:56 by atamer            #+#    #+#             */
/*   Updated: 2025/05/06 13:37:52 by mguerri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

volatile sig_atomic_t	g_exit_status = 0;

static void	create_command_array(t_data *data)
{
	int			index;
	t_command	*tmp;

	index = 0;
	tmp = data->commands_list;
	while (tmp)
	{
		data->commands_array[index].command_strings = tmp->command_strings;
		data->commands_array[index].tokens = tmp -> tokens;
		data->commands_array[index].tokens_size = tmp -> tokens_size;
		tmp = tmp->next;
		index++;
	}
}

static void	cntrl_d(t_data *data)
{
	int		i;
	char	*path;
	int		num;

	i = -1;
	printf("exit\n");
	while (data->envp[++i])
		if (ft_strncmp(data->envp[i], "SHLVL", 5) == 0)
			path = ft_envstr(data->envp[i], "=", ft_strlen(data->envp[i]));
	num = ft_atoi(path);
	num--;
	path = ft_itoa(num);
	assign_exported(data->envp, "SHLVL", path);
	free(path);
	if (num == data->level)
		exit(0);
	else
	{
		rl_clear_history();
		g_exit_status = 0;
	}
}

void	*greenshell(t_data *data)
{
	handle_signals();
	data->line = readline("GreenShell> ");
	handle_child();
	add_history(data->line);
	if (!data->line)
		cntrl_d(data);
	if (parser(data) == 0)
	{
		data->command_count = ft_lstsize(data->commands_list);
		data->commands_array = malloc(sizeof(t_command) *(data->command_count));
		if (!data->commands_array)
			return (NULL);
		create_command_array(data);
		if (data->command_count == 1)
			lone_command(data);
		else
			execute_pipes(data);
		ft_cleanup(data);
	}
	else
		free (data->line);
	return (NULL);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	data.envp = create_env(envp);
	data.set = create_env(envp);
	data.level = check_shell_level(&data);
	while (1)
	{
		greenshell(&data);
	}
	free_arr(data.envp);
	free_arr(data.set);
	(void)ac;
	(void)av;
	return (0);
}
