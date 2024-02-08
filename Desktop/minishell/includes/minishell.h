/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <alfgarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:34:07 by alfgarci          #+#    #+#             */
/*   Updated: 2024/02/08 15:59:35 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <curses.h>
# include <fcntl.h>
# include <term.h>
# include <dirent.h>
# include "libft.h"
# include "messages.h"

# define PIPE 124
# define LESS 60
# define MORE 62
# define HERE 388
# define APPEND 488
# define OTHER 0
# define IN_CMD 2
# define STOP_HD 3
# define ERR_CMD 130

int	g_signal;

typedef struct s_token
{
	char			*world;
	int				type;
	int				num;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_command
{
	char				**args;
	int					is_builtin;
	char				*here_doc;
	t_token				*redirections;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct s_instance
{
	char		*prompt;
	char		**paths;
	char		**envp;
	char		*home;
	char		*pwd;
	char		*old_pwd;
	int			err_num;

	t_command	*cmd_list;
	t_token		*token_list;
	int			*pid;
	int			is_here;
	int			reset;

	int			num_pipes;
	t_token		*list_parser;
	t_token		*list_red_parser;
}	t_instance;

/*Minishell*/
void		minishell(t_instance *ins);
void		reset_minishell(t_instance *ins);

/*Setup*/
void		init_instance(t_instance *ins, char **envp);
void		init_pwd(t_instance *ins);
void		init_rest_instance(t_instance *ins);
void		init_envp(t_instance *ins);
char		**mini_envp(t_instance *ins);
void		init_home(t_instance *ins);

/*Lexer*/
char		**clean_prompt(t_instance *ins);
char		**split_prompt(char *str, int count);
int			count_words(char *str);
int			are_quotes_closed(const char *str);

void		tokenizer(t_instance *ins, char **arr_prompt);
t_token		*new_token(char *world, int type, int i);
void		token_add_back(t_token **token_list, t_token *new);
t_token		*delete_token(t_token **token_list);
void		delete_fisrt_token(t_token **token_list);
void		delete_i_token(t_token **token_list, int key);

/*Expander*/
void		expander(t_instance *ins, char **arr);
char		*expander_heredoc(t_instance *ins, char *line);
int			count_char_before(char *str);
char		*add_char_str(char *str, char c);
void		free_expander(char *front, char *back, char *key);

/*Parse Command*/
t_command	*new_command(char **args, t_token *red);
void		command_add_back(t_command **cmd_list, t_command *new_cmd);
t_command	*make_command_list(t_instance *ins);
void		parse_cmd(t_instance *ins);
void		new_redirection(t_instance *ins, t_token *token, int i);
void		search_redirections(t_instance *ins, int i);
void		count_pipes(t_instance *ins);
int			count_args(t_token *list_parser);
void		erase_quotes(t_command *cmd_list);

/*List Utils*/
void		free_tokens(t_token	**token_list);
void		free_cmds(t_command **cmd_list);

/*Utils*/
char		**arrdup(char **arr);
void		free_split(char **split);
char		*array_to_line(char **array);
char		**append_to_array(char **arr, char *new);
int			len_arr(char **arr);
char		**delete_str_in_arr(char **arr, int num);

char		*ft_strndup(const char *src, size_t n);
int			is_space(char c);
int			is_special_char(char c);
char		*strjoin_3(char	*s1, char *s2, char *s3);
int			is_str_indetical(char *str1, char *str2);

/*Error*/
void		minishell_error(char *str, t_instance *ins);
void		ctrl_d(t_instance *ins);
void		check_pipe_errors(t_instance *ins, t_token *token_list);
void		check_fist_tokken(t_instance *ins);
void		parse_error(t_instance *ins, t_token *token);
void		check_redirections_syntax_error(t_instance *ins, t_token *token);
int			exit_error(char *str);
int			end_minishell(t_instance *ins, int err_code);

/*Signals*/
void		sig_ctrlc(int sig);
void		sig_ctrl4(int sig);
void		init_signals(void);

/*Exexutor*/
void		executor(t_instance *ins);
t_command	*get_first_cmd(t_command *cmd_list);
void		run_cmd(t_command *cmd, t_instance *ins);
int			check_redirections(t_command *cmd);

void		dup_pipe(t_command *cmd, t_instance *ins, int end[2], int fd_in);
void		pipe_wait(t_instance *ins);

char		*check_heredoc_quotes(char *delimiter, int *quotes);
void		check_heredoc(t_instance *ins, t_command *cmd);
int			check_fd_heredoc(t_instance *ins, int end[2], t_command *cmd);
char		*generate_heredoc_filename(void);

/*Builtin*/
int			builtin(t_instance *ins, t_command *cmd);
int			cd(t_instance *ins, t_command *cmd);
int			pwd(t_instance *ins);
int			env(t_instance *ins, t_command *cmd);
int			unset(t_instance *ins, t_command *cmd);
int			my_echo(t_command *cmd);
void		my_exit(t_instance *ins, t_command *cmd);
int			export(t_instance *ins, t_command *cmd);

#endif
