#include <sys/fcntl.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>

typedef struct {
  char*** args;
  unsigned len;
  char* redir_path;
  char npipes;
} Cmd;

// FIXME Could fail
#define CMD_IS_EXIT(cmd) (strcmp(cmd.args[0][0], EXIT_CMD) == 0)

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
  size_t size = 10;
  char** args = malloc(sizeof(char*) * (size + 1));
  char* tmp;
  char* delim = " \n\t";

  args[0] = strtok(input, delim);
  int i = 1;
  while ((tmp = strtok(NULL, delim))) {
    if (i == size) {
      size += 10;
      args = realloc(args, sizeof(char*) * (size + 1));
    }
    args[i++] = tmp;
  }
  args[i] = NULL;

  int len = i;
  char* redir_path = NULL;
  if (i >= 3 && strcmp(args[i-2], ">") == 0) {
    redir_path = args[i-1];
    args[i-2] = NULL; // Shorten the args list up to the last argumen before >
    len = i - 2;
  }
  Cmd cmd = { args, len, redir_path };

  return cmd;
}

void handle_cmd(Cmd cmd) {
  if (cmd.redir_path != NULL) {
    close(STDOUT_FILENO);
    open(cmd.redir_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  }
  execvp(cmd.args[0], cmd.args);
  exit(EXIT_FAILURE);
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

    for (int i = 0; i < nprocs; i++) {
      pids[i] = fork();
      if (pids[i] == 0) {
        int input_side = filedes[2 * (i - 1)];
        int output_side = filedes[2 * (i - 1) + 1];
        if (i != 0) {
          close(output_side);
          dup2(input_side, STDIN_FILENO);
        } else if (i != nprocs - 1) {
          close(input_side);
          dup2(output_side, STDOUT_FILENO);
        }
        handle_cmd(cmd, redir);
      }
    }

    // TODO use static memory to avoid memory leaking
    if (pid == 0) {
      handle_cmd(cmd);
    } else {
      free(input);
      free(cmd.args);
      wait(NULL);
    }
  }

  return 0;
}

