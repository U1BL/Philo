
#include "pipex.h"

int redirect_output_to_file(char *command, char *filename, char *joined_str) 
{
    pid_t pid;
    int status;
    int fd;
    
    pid = fork();
    if (pid == 0)     // Child process
    {
        fd = open(filename, O_WRONLY | O_CREAT, 0777);
        if (fd < 0) {
            ft_printf("Error: Creating/Opening the file failed\n");
            exit(1);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);

        char *envp[] = { NULL };
        char **args = ft_split(command, ' ');
        if (execve(joined_str, args, envp) < 0) {
            ft_printf("Error: Executing the command failed\n");
            exit(1);
        }
    } 
    
    else if (pid < 0)   // Fork failed
    {
        ft_printf("Forking the process failed\n");
        return 1;
    } 
    
    else 
    {
        // Parent process
        wait(&status);
    }
    return 0;
}

int main(int argc, char *argv[], char *env[])
{
    (void)env;
    int i = 0;
    char **str;
    char *s = NULL;
    char *a;
    int j = 1;
    char *joinedstr;

    // check_leaks();
    if(argc == 5)
    {
        int fd = open(argv[1], O_RDONLY);
        if (fd == -1)
        {
           perror("Error while opening the file");
           exit(1);
        }
        dup2(fd, STDIN_FILENO);
    }
    
    else
    {
        ft_printf("You Have Entered Few Arguments Than Expected\n");
        exit(1);
    }

        while (env[i]) 
        {
            if((strncmp("PATH=", env[i], 5) == 0)){
                s = strdup((env[i] + 5));
                // ft_printf("s = %s\n", s);
            }
            i++;
        }
        if(!s)
        {
           ft_printf("ERROR WHILE FINDING THE PATH\n");
            exit(3);
        }
        check_leaks();
        str = ft_split(s, ':');
        i = 0;
        a = malloc(ft_strlen(argv[2]) + 2);
        a[0] = '/';
        i = 0;
        while(argv[2][i] && argv[2][i] != ' ')
            a[j++] = argv[2][i++];
        a[j] = '\0';
        i = 0;
        while (str[i]) {
            joinedstr = ft_strjoin(str[i], a);
            // ft_printf("%s\n", joinedstr);
            if (access(joinedstr, F_OK) == 0){
            {
                // char *args[] = { argv[2] , NULL}; 
                // if (execvp(joinedstr, args) < 0) {
                //     ft_printf("Error: Executing the command failed\n");
                //     exit(1);
                // }
                redirect_output_to_file(argv[2], argv[4], joinedstr);
                 check_leaks();
                // execute_command(joinedstr);
                return (0);
            }
            }
            i++;
        }
        // check_leaks();
        if (str[i] == NULL) 
        {
         ft_printf("the command %s doesn't exist\n", argv[2]); 
        }
        check_leaks();
        free(a);
        free(joinedstr);
    // check_leaks();
    check_leaks();
    return (0);
}