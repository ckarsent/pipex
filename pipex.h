/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:06:15 by ckarsent          #+#    #+#             */
/*   Updated: 2025/02/20 18:56:50 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "Libft/libft.h"
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_pipex
{
	char	*infile_name;
	char	*outfile_name;
	int		infile;
	int		outfile;
	char	*cmd1;
	char	*cmd2;
	int		status;
	pid_t	pid1;
	pid_t	pid2;
	int		infile_yes;
	int		outfile_yes;
}	t_pipex;

void	exec_cmd(char *cmd, char **envp);
int		main(int argc, char **argv, char **envp);

#endif
