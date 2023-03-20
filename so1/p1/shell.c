#include <sys/fcntl.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>

typedef struct {
  char** args;      // Array of strings representing commands, arguments, pipes, redirections, etc
  unsigned len;     // Length of args array
  char* redir_path; // Path to redirect output of command, NULL if no redirection is specified
  unsigned* pipes;  // Positions in args where there is a pipe. Parse replaces this strings by a NULL pointer
  char npipes;      // Number of pipes in command, equivalent to length of pipes array
} Cmd;

#define CMD_IS_EXIT(cmd) (cmd.args[0] && strcmp(cmd.args[0], EXIT_CMD) == 0)
#define TOKEN_IS_PIPE(tok) (tok != NULL && !strcmp(tok, "|"))
#define TOKEN_IS_REDIR(tok) (tok != NULL && !strcmp(tok, ">"))
#define ABORT(msg) {fprintf(stderr, "[ERROR]: %s\n", msg); exit(EXIT_FAILURE);}

// This macros do not check bounds on accessing the array
#define READ_END(filedes, i) filedes[2 * (i)]
#define WRITE_END(filedes, i) filedes[2 * (i) + 1]

const char* const EXIT_CMD = "exit";

void show_prompt() {
  printf("> ");
}

char* get_input() {
  char c;
  int i = 0;
  size_t size = 10;
  char* input = malloc(sizeof(char) * (size + 1));
  assert(input != NULL);
  show_prompt();
  while ((c = getchar()) != '\n') {
    if (i == size) {
      input = realloc(input, size *= 2);
      assert(input != NULL);
    }
    input[i++] = c;
  }
  input[i] = 0;
  return input;
}

Cmd parse(char* input) {
  size_t size_args = 10, size_pipes = 9;
  char** args = malloc(sizeof(char*) * (size_args + 1));
  unsigned npipes = 0, *pipes = malloc(sizeof(unsigned) * size_pipes);
  char* tmp;
  char* delim = " \n\t";

  args[0] = strtok(input, delim);
  int i;
  for (i = 1; (tmp = strtok(NULL, delim)); ++i) {
    if (i == size_args) {
      size_args += 10;
      args = realloc(args, sizeof(char*) * (size_args + 1));
    }
    args[i] = tmp;
    if (TOKEN_IS_PIPE(tmp)) {
      if (npipes == size_pipes) {
        size_pipes += 2;
        pipes = realloc(pipes, sizeof(unsigned) * size_pipes);
        assert(pipes != NULL);
      }
      pipes[npipes++] = i;
      args[i] = NULL; // Replace the "|" by a NULL, this lets us treat the args array as multiple
                      // commands by saving the positions of the pipes
    }
  }
  args[i] = NULL;

  int len = i;
  char* redir_path = NULL;
  if (i >= 3 && TOKEN_IS_REDIR(args[i-2])) {
    redir_path = args[i-1];
    args[i-2] = NULL; // Shorten the args list up to the last argumen before >
    len = i - 2;
  }
  Cmd cmd = { args, len, redir_path, pipes, npipes };

  return cmd;
}

void handle_cmd(char** cmd, char* redir_path) {
  if (redir_path != NULL) {
    close(STDOUT_FILENO);
    open(redir_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  }
  execvp(cmd[0], cmd);
  ABORT("Command not found");
}

char** ith_process_cmd(Cmd cmd, unsigned i) {
  if (i == 0) return cmd.args;
  int last_pipe = cmd.pipes[i - 1];
  return cmd.args + last_pipe + 1;
}

int main() {
  printf("Welcome to BAtSH\n");
  while (1) {
    char* input = get_input();
    Cmd cmd = parse(input);

    if (CMD_IS_EXIT(cmd))
      break;
    int* filedes = malloc(sizeof(int) * 2 * cmd.npipes);
    assert(filedes != NULL);

    for (int i = 0; i < cmd.npipes; i++)
      pipe(filedes + i * 2);

    int nprocs = cmd.npipes + 1;
    pid_t* pids = malloc(sizeof(pid_t) * nprocs);
    assert(pids != NULL);

    // printf("npipes: %d, len: %d, positions: ", cmd.npipes, cmd.len);
    // for (int i = 0; i < cmd.npipes; i++)
    //   printf("%u ", cmd.pipes[i]);
    // putchar('\n');
    // for (int i = 0, j = 0; j < cmd.npipes + 1; i++) {
    //   printf("%s, ", cmd.args[i] == NULL ? "NULL" : cmd.args[i]);
    //   if (cmd.args[i] == NULL) j++;
    // }
    //
    // fflush(stdout);
    for (int i = 0; i < nprocs; i++) {
      char* redir_path = NULL;
      pids[i] = fork();
      if (pids[i] < 0) {
        ABORT("Could not create child process");
      } else if (pids[i] == 0) {
        if (i != 0) {
          close(WRITE_END(filedes, i - 1));
          dup2(READ_END(filedes, i - 1), STDIN_FILENO);
        }
        if (i != nprocs - 1) {
          close(READ_END(filedes, i));
          dup2(WRITE_END(filedes, i), STDOUT_FILENO);
        }
        for (int j = 0; j < 2 * cmd.npipes; j++)
          close(filedes[j]);
        if (i == nprocs - 1) // If this is the last process of the pipe, check if output is redirected
          redir_path = cmd.redir_path;
        handle_cmd(ith_process_cmd(cmd, i), redir_path);
      }
    }

    for (int j = 0; j < 2 * cmd.npipes; j++)
      close(filedes[j]);

    // TODO use static memory to avoid memory leaking
    free(input);
    free(cmd.args);
    free(filedes);

    int status;
    for (int i = 0; i < nprocs; i++)
      waitpid(pids[i], &status, 0);
    free(pids);
    // TODO check wait status of the commands
  }

  return 0;
}

