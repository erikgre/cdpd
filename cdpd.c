#include "cdpd.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define MODE S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

int open_histfile(int flags) {
  char *home = getenv("HOME");
  char buf[MAX_PATH_LEN + 1];
  snprintf(buf, sizeof(buf), "%s/%s", home, HISTFILE);

  errno = 0;
  int fd = open(buf, flags, MODE);
  return fd;
}
