#include "cdpd.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPEN_FLAGS O_RDONLY | O_CREAT

int main(void) {
  int fd = open_histfile(OPEN_FLAGS);

  if (unlikely(fd == -1)) {
    return errno;
  }

  char old_pwd_buf[MAX_PATH_LEN + 1] = {0};

  int bytes_read = read(fd, &old_pwd_buf, MAX_PATH_LEN);

  if (unlikely(bytes_read == -1)) {
    return errno;
  }

  char *old_pwd = old_pwd_buf;

  if (unlikely(bytes_read == 0)) {
    old_pwd = getenv("PWD");
  }

  puts(old_pwd);
  return 0;
}
