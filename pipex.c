/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarsent <ckarsent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:04:45 by ckarsent          #+#    #+#             */
/*   Updated: 2025/02/22 18:35:28 by ckarsent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_struct(t_pipex *p, char **argv, int infile, int outfile)
{
	p->infile_name = argv[1];
	p->outfile_name = argv[4];
	p->infile = infile;
	p->outfile = outfile;
	p->cmd1 = argv[2];
	p->cmd2 = argv[3];
	p->infile_yes = 0;
	p->outfile_yes = 0;
	p->status = 0;
	if (access(p->infile_name, F_OK) == -1
		|| access(p->infile_name, R_OK) == -1)
		p->infile_yes = -1;
	if (access(p->outfile_name, F_OK) == -1
		|| access(p->outfile_name, W_OK) == -1)
		p->outfile_yes = -1;
}

void	first_process(t_pipex *p, int *fd, char **envp)
{
	pipe(fd);
	p->pid1 = fork();
	if (p->pid1 == 0 && p->infile_yes == 0)
	{
		dup2(p->infile, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		close(p->infile);
		exec_cmd(p->cmd1, envp);
	}
	else if (p->pid1 < 0)
	{
		close(fd[1]);
		close(p->outfile);
		close(p->infile);
		exit(1);
	}
	close(fd[1]);
}

void	second_process(t_pipex *p, int *fd, char **envp)
{
	p->pid2 = fork();
	if (p->pid2 == 0 && p->pid1 != 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(p->outfile, STDOUT_FILENO);
		close(fd[0]);
		close(p->outfile);
		exec_cmd(p->cmd2, envp);
	}
	else if (p->pid2 < 0)
	{
		close(fd[0]);
		close(fd[1]);
		close(p->outfile);
		exit(1);
	}
}

void	pipex(t_pipex *p, char **envp)
{
	int		fd[2];

	first_process(p, fd, envp);
	if (p->infile > 0)
		close(p->infile);
	second_process(p, fd, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(p->pid1, NULL, 0);
	waitpid(p->pid2, &p->status, 0);
	if (p->outfile_yes == -1)
		exit(1);
	exit(WEXITSTATUS(p->status));
}

int	main(int argc, char **argv, char **envp)
{
	int		infile;
	int		outfile;
	t_pipex	p;

	if (argc != 5 || !envp)
	{
		ft_putstr_fd("Error parse\n", 2);
		return (1);
	}
	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		perror("File error");
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		perror("File error");
	init_struct(&p, argv, infile, outfile);
	pipex(&p, envp);
	return (0);
}
