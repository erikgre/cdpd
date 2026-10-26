#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE 200809L

#include "cdpd.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define OPEN_FLAGS O_CREAT | O_WRONLY | O_TRUNC

void __attribute__((cold)) print_invalid_args(void) {
  fputs("here: To many arguments\n", stderr);
}

void __attribute__((cold)) print_fail_open(void) {
  fprintf(stderr, "here: Failed to open histfile: %s/%s: %s\n", getenv("HOME"),
          HISTFILE, strerror(errno));
}

void __attribute__((cold)) print_failure(const char *restrict path) {
  fprintf(stderr, "here: %s: %s\n", strerror(errno), path);
}

int write_histfile(const char *restrict str) {
  const int fd = open_histfile(OPEN_FLAGS);
  if (fd == -1) {
    return EOF;
  }
  FILE *file = fdopen(fd, "w");
  if (file == NULL) {
    return EOF;
  }

  return fputs(str, file);
}

int main(int argc, char *argv[]) {
  if (argc > 2) {
    print_invalid_args();
    return EXIT_FAILURE;
  }

  char *path;

  if (argc == 1) {
    path = getenv("PWD");
  } else if (memcmp(argv[1], "-", 2) == 0) {
    char *oldpwd = getenv("OLDPWD");
    if (oldpwd == NULL) {
      oldpwd = getenv("PWD");
    }
    puts(oldpwd);

    path = oldpwd;
  } else {
    char buf[MAX_PATH_LEN + 1];

    if (realpath(argv[1], buf) == NULL) {
      print_failure(argv[1]);
      return EXIT_FAILURE;
    }

    struct stat st;

    if (stat(buf, &st) != 0) {
      print_failure(argv[1]);
      return EXIT_FAILURE;
    }

    if (!S_ISDIR(st.st_mode)) {
      errno = ENOTDIR;
      print_failure(argv[1]);
      return EXIT_FAILURE;
    }

    path = buf;
  }

  if (write_histfile(path) == EOF) {
    print_fail_open();
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
