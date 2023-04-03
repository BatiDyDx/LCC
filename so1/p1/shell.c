#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>

typedef struct _A_Cmd {
  char** toks;
  unsigned len;
  char* redir_path; // Path to redirect output of command, NULL if no redirection is specified;
} *AtomicCmd;

typedef struct _Cmd {
  AtomicCmd* atoms; // Atomic commands 
  unsigned char nprocs; // Number of processes (equal to length of atoms array)
} *Cmd;

#define ATOMS_SIZE 3
#define TOKS_SIZE 5

#define REDIR ">"
#define PIPE "|"
#define EXIT "exit"

#define IS_TOKEN(s, tok) (s != NULL && !strcmp(s, tok))

#define ABORT(msg) do {\
            fprintf(stderr, "[ERROR]: %s\n", msg);\
            exit(EXIT_FAILURE);\
          } while (0)

#define INFO(msg) do {\
            fprintf(stderr, "[INFO]: %s\n", msg);\
            exit(EXIT_SUCCESS);\
          } while (0)

// These macros do not check bounds on accessing the array
#define READ_END(filedes, i) filedes[2 * (i)]
#define WRITE_END(filedes, i) filedes[2 * (i) + 1]

void show_prompt() {
  printf("> ");
}

AtomicCmd create_atomcmd(char** toks, unsigned len) {
  AtomicCmd atom = malloc(sizeof(struct _A_Cmd));
  assert(atom != NULL);

  if (len >= 3 && IS_TOKEN(toks[len - 2], REDIR)) {
    toks[len - 2] = NULL;
    atom->redir_path = toks[len - 1];
    len -= 2; // Shorten the args list up to the last argumen before >
  } else {
    toks[len] = NULL;
    atom->redir_path = NULL;
  }
  atom->toks = toks;
  atom->len = len;

  return atom;
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

void add_atomic(Cmd cmd, AtomicCmd atom) {
  if (cmd->nprocs % ATOMS_SIZE == 0) {
    cmd->atoms = realloc(cmd->atoms, sizeof(AtomicCmd) * (cmd->nprocs + ATOMS_SIZE));
    assert(cmd->atoms != NULL);
  }
  cmd->atoms[cmd->nprocs++] = atom;
}

Cmd parse(char* input) {
  size_t toks_len = 1;
  AtomicCmd atom;
  Cmd cmd = malloc(sizeof(struct _Cmd));
  assert(cmd != NULL);

  cmd->nprocs = 0;
  cmd->atoms = malloc(sizeof(AtomicCmd) * ATOMS_SIZE);
  assert(cmd->atoms != NULL);

  char** toks = malloc(sizeof(char*) * (TOKS_SIZE + 1));
  char* tmp;
  char* delim = " \n\t";

  toks[0] = strtok(input, delim);
  while ((tmp = strtok(NULL, delim))) {
    if (toks_len % TOKS_SIZE == 0)
      toks = realloc(toks, sizeof(char*) * (toks_len + TOKS_SIZE + 1));
    toks[toks_len++] = tmp;
    if (IS_TOKEN(tmp, PIPE)) {
      atom = create_atomcmd(toks, toks_len - 1);
      add_atomic(cmd, atom);
      toks = malloc(sizeof(char*) * (TOKS_SIZE + 1));
      assert(toks != NULL);
      toks_len = 0;
    }
  }

  atom = create_atomcmd(toks, toks_len);
  add_atomic(cmd, atom);

  return cmd;
}

int cmd_is_exit(Cmd cmd) {
  // TODO Improve exit condition
  return cmd->nprocs > 0 && cmd->atoms[0]->len > 0 &&
         IS_TOKEN(cmd->atoms[0]->toks[0], EXIT);
}

void exec_atomic(AtomicCmd acmd) {
  if (acmd->len == 0)
    ABORT("Invalid command of length 0");
  if (acmd->redir_path != NULL) {
    close(STDOUT_FILENO);
    open(acmd->redir_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  }
  execvp(acmd->toks[0], acmd->toks);
  ABORT("Command not found");
}

void free_atomic(AtomicCmd ac) {
  free(ac->toks);
  free(ac);
}

void free_cmd(Cmd cmd) {
  for (int i = 0; i < cmd->nprocs; free_atomic(cmd->atoms[i++]));
  free(cmd);
}

int main() {
  printf("Welcome to BAtSH\n");
  while (1) {
    char* input = get_input();
    Cmd cmd = parse(input);

    if (cmd_is_exit(cmd))
      INFO("Exiting terminal");

    int npipes = cmd->nprocs - 1;

    int* filedes = malloc(sizeof(int) * 2 * (cmd->nprocs - 1));
    assert(filedes != NULL);

    for (int i = 0; i < npipes; i++) {
      if (pipe(filedes + i * 2) < 0)
        ABORT("Could not create pipe");
    }

    pid_t* pids = malloc(sizeof(pid_t) * cmd->nprocs);
    assert(pids != NULL);

    for (int i = 0; i < cmd->nprocs; i++) {
      pids[i] = fork();
      if (pids[i] < 0)
        ABORT("Could not create child process");
      else if (pids[i] == 0) {
        if (i != 0) {
          close(WRITE_END(filedes, i - 1));
          dup2(READ_END(filedes, i - 1), STDIN_FILENO);
        }
        if (i != cmd->nprocs - 1) {
          close(READ_END(filedes, i));
          dup2(WRITE_END(filedes, i), STDOUT_FILENO);
        }
        for (int j = 0; j < 2 * npipes; j++)
          close(filedes[j]);
        exec_atomic(cmd->atoms[i]);
      }
    }

    for (int j = 0; j < 2 * npipes; j++)
      close(filedes[j]);

    // TODO use static memory to avoid memory leaking
    free(input);
    free(filedes);

    for (int i = 0; i < cmd->nprocs; i++)
      waitpid(pids[i], NULL, 0);

    free_cmd(cmd);
    free(pids);
    // TODO check wait status of the commands
  }

  return 0;
}

