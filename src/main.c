#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TASK_NAME_SIZE 100

void usage() {
  fprintf(stderr, "Usage: trakr [OPTIONS]\n");
  fprintf(stderr, "\nTODO\n");
}

int main(int argc, char **argv) {
  int incmd = 0;
  int outcmd = 0;
  int ch = 0;
  char task[TASK_NAME_SIZE] = {0};

  struct option longopts[] = {
    {"in", required_argument, NULL, 'i'},
    {"out", no_argument, NULL, 'o'},
    {0, 0, 0, 0},
  };

  if (argc == 1) {
    usage();
    exit(EXIT_FAILURE);
  }

  while ((ch = getopt_long(argc, argv, "+bf:", longopts, NULL)) != -1) {
    switch (ch) {
    case 'i':
      incmd = 1;
      strncpy(task, optarg, TASK_NAME_SIZE - 1);
      task[TASK_NAME_SIZE - 1] = '\0';
      break;
    case 'o':
      outcmd = 1;
      break;
    default:
      usage();
      exit(EXIT_FAILURE);
    }
  }
  argc -= optind;
  argv += optind;

  if ((incmd + outcmd) > 1) {
    fprintf(stderr, "'--in' and '--out' are mutually exclusive options\n");
    usage();
    exit(EXIT_FAILURE);
  }

  if (incmd) {
    fprintf(stderr, "Incmd\nTask: %s\n", task);
  } else if (outcmd) {
    fprintf(stderr, "Outcmd\n");
  }

  return EXIT_SUCCESS;
}
