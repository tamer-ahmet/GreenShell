/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerri- <mguerri-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:04:17 by atamer            #+#    #+#             */
/*   Updated: 2025/05/05 14:26:38 by mguerri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <string.h>
# include <limits.h>
# include <errno.h>

extern volatile sig_atomic_t	g_exit_status;
typedef struct s_command		t_command;

typedef enum s_token_type
{
	WORD = 1,
	OUTRED,
	INRED,
	APPEND,
	HEREDOC,
	PIPE
}	t_token_type;

typedef struct s_lexer
{
	char	*input;
	int		pos;
	char	current_char;
}	t_lexer;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_stringbuilder
{
	char	*str;
	size_t	len;
	size_t	cap;
}	t_stringbuilder;

typedef struct s_command
{
	int					fd[2];
	struct s_command	*prev;
	struct s_command	*next;
	int					*tokens;
	int					tokens_size;
	char				**command_strings;
}	t_command;

typedef struct s_data
{
	char		*second;
	char		*line;
	char		**envp;
	char		**set;
	int			level;
	int			command_count;
	int			heredoc_count;
	int			stdin_backup;
	int			stdout_backup;
	t_command	*commands_list;
	t_command	*commands_array;
}	t_data;

typedef enum s_build_in
{
	NO_BUILD_IN,
	ENV,
	EXPORT,
	UNSET,
	ASSIGN,
	SHELL,
	EXIT,
	ECHO,
	CD,
	PWD
}	t_build_in;

typedef struct s_store
{
	t_command	curr_cmd;
	char		**line_arr;
	char		**path_arr;
	char		**command_arr;
	char		**var_arr;
	char		**exec_arr;
	char		*command;
	char		*path;
	char		*temp;
	int			len;
	int			index;
	int			count;
	int			flag;
	int			num;
	int			id;
}	t_store;

	//	UTILS

// free.c
void			*free_arr(char **arr);
void			sb_free(t_stringbuilder *sb);
void			free_parsing(t_lexer *lexer, t_token *tokens, char *str);
void			free_commands_list(t_command *commands_list);
void			ft_cleanup(t_data *data);
//	ft_split.c 5/5
char			**ft_split(char const *s, char c);
//	ft_strtrim.c 3/5
char			*ft_strtrim(char *s1, char *set);
//	is_it.c 4/5
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isvarchar(char c);
int				ft_isalldigits(char *str);
//	len.c 3/5
int				ft_strlen(char *str);
int				ft_varlen(char *line);
int				arr_len(char **arr);
//	list.c 1/5
int				ft_lstsize(t_command *lst);
//	numbers.c 4/5
int				ft_atoi(const char *nptr);
char			*ft_itoa(int n);
//	string_parse.c 5/5
int				str_contains(char *str, char c);
int				ft_strncmp(const char *s1, const char *s2, int n);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strchr(const char *str, int c);
char			*ft_strcat(char *dest, const char *src);
//	strings.c 5/5
void			*ft_memcpy(void *dst, void *src, size_t n);
char			*ft_strdup(char *str);
char			*ft_strndup(char *str, int n);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strcpy(char *dst, const char *src);

	//	PARSING

// parser.c 3/5
int				parser(t_data *data);
// stringbuilding.c
t_stringbuilder	*sb_new(void);
void			sb_append(t_stringbuilder *sb, char *s);
void			sb_append_char(t_stringbuilder *sb, char c);
char			*sb_build(t_stringbuilder *sb);
// lexer.c 3/5
t_lexer			*init_lexer(char *input);
void			lexer_advance(t_lexer *lexer);
void			lexer_skip_whitespace(t_lexer *lexer);
// tokens.c
void			append_token(t_token **head, t_token *new);
t_token			*token_collect(t_lexer *lexer);
t_token			*lexer_tokenize(t_lexer *lexer);
// word.c 1/5
char			*lexer_collect_word(t_lexer *lexer);
// quotes_helper.c
void			init_makestring_vars(t_lexer *lxr, char *q_char, int *start);
void			quotes_append_and_free(char **result, char *temp);
// quotes.c 5/5
char			*append_str(char *str, char *suffix);
char			*make_string(t_lexer *lexer);
// data_prepare.c 5/5
int				*int_array_maker(t_token *head);
char			**char_array_maker(t_token *tokens);
void			append_command(t_command **head, t_command *new);
t_command		*create_command(t_token *tokens);

	//	BUILD_INS
//	cd_utils.c
int				update_pwd_vars(t_data *data, char *oldpwd);
char			*get_env_value(t_data *data, char *key);
//	cd.c
void			update_env(t_data *data, char *key, char *value);
int				execute_cd(t_data *data, char **command_strings);
//	echo.c
void			execute_echo(char **command_strings);
//	env.c 5/5
char			**create_env(char **envp);
int				check_env(char **envp, char *var);
int				check_export(char **envp, char *var);
void			print_env(char **envp);
void			print_export(char **envp);
//	exit.c
int				check_shell_level(t_data *data);
int				check_exit(t_data *data);
void			execute_shell(t_data *data);
//	export.c 
char			**ft_export(char **envp, char *str);
void			execute_export(t_data *data, char **command_strings);
// export_utils.c
int				contains_concat(char *str);
char			*cut_concat_name(char *str);
char			*cut_concat_value(char *str);
void			*concat_values(char **arr, char *name, char *value);
//	pwd.c
int				execute_pwd(void);
//	unset.c
char			**ft_unset(char **envp, char *var);
int				check_unset(char *var, char *str);
void			execute_unset(t_data *data, char **command_strings);

	// ERROR_MANAGING

// error.c
int				syntax_error(void);
int				cd_too_many_args(int flag, char **command_strings);

	// EXECUTION

//	assign.c 3/5
void			*assign_exported(char **envp, char *var, char *value);
void			*execute_assign(t_data *data, char **command_strings);
//	build_in.c
int				is_built_in(char *line);
void			exec_pipe_build_in(t_data *data, int index, int command_id);

//	command.c
char			*find_command(char **path_arr, char **command_arr);
//	heredoc.c
int				check_heredoc(t_data *data, int count);
int				search_heredoc(t_data *data);
//	heredoc_utils.c
void			handle_heredoc_signal(int signum);
void			change_tokens(t_command curr_cmd,
					int token_index, char *index_str, char *file_name);
void			heredoc_exit(void);

//	lone.c 
void			lone_command(t_data *data);
void			*exec_inredirection(t_store *store);
void			*exec_outredirection(t_store *store);
void			*exec_append(t_store *store);
void			*lone_fork(t_data *data);
/*	path.c	*/
char			*ft_envstr(char *big, char *little, size_t len);
char			**create_path(char **envp);
/*	pipes.c  */
void			*execute_pipes(t_data *data);
void			*execute_order(t_data *data, int index, int len);
//	redirect.c 
void			*exec_inredirection(t_store *store);
void			*exec_outredirection(t_store *store);
void			*exec_append(t_store *store);
void			*create_exec_array(t_store *store);
// output.c
void			is_directory(char *cmd);
void			command_not_found(t_store *store);
int				check_directory(char *path);
void			check_echo(t_store *store);
void			*invalid_export(char **var_arr);

// wait.c
void			close_and_wait(t_data *data, int id);
void			clean_data(t_data *data);
void			clean_temp(t_data *data);

	//	SIGNALS

// signals.c
void			handle_child(void);
void			child_sigint(int signum);
void			handle_signals(void);
void			handle_sigint(int signum);

#endif
