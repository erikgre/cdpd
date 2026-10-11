#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE 500

#include "cdpd.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define OPEN_FLAGS O_CREAT | O_WRONLY | O_TRUNC

void __attribute__((cold)) print_fail_open(void) {
  fprintf(stderr, "Failed to open histfile: %s/%s: %s\n", getenv("HOME"),
          HISTFILE, strerror(errno));
}

void __attribute__((cold)) print_not_dir(const char *restrict path) {
  fprintf(stderr, "here: %s: %s\n", strerror(ENOTDIR), path);
}

void __attribute__((cold)) print_failed_stat(const char *restrict path) {
  fprintf(stderr, "here: %s: %s\n", strerror(errno), path);
}

int main(int argc, char *argv[]) {
  int err = 0;
  if (argc > 2) {
    return EXIT_FAILURE;
  }
  int fd = open_histfile(OPEN_FLAGS);
  if (fd == -1) {
    err = errno;
    print_fail_open();
    return err;
  }

  FILE *file = fdopen(fd, "w");
  if (file == NULL) {
    err = errno;
    print_fail_open();
    close(fd);
    return err;
  }

  if (argc == 1) {
    char *pwd = getenv("PWD");
    fputs(pwd, file);
  } else {
    struct stat st;
    if (fstatat(AT_FDCWD, argv[1], &st, 0) != 0) {
      err = errno;
      print_failed_stat(argv[1]);
      goto end;
    }

    if (!S_ISDIR(st.st_mode)) {
      err = errno;
      print_not_dir(argv[1]);
      goto end;
    }

    char buf[MAX_PATH_LEN + 1];
    if (realpath(argv[1], buf) != NULL) {
      fputs(buf, file);
    }
  }

  err = errno;
end:
  fclose(file);
  return err;
}
