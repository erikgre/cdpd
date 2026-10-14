#include "cdpd.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPEN_FLAGS O_RDONLY | O_CREAT

int main(void) {
  int fd = open_histfile(OPEN_FLAGS);

  if (unlikely(fd == -1)) {
    return EXIT_FAILURE;
  }

  char old_pwd_buf[MAX_PATH_LEN];

  int bytes_read = read(fd, old_pwd_buf, MAX_PATH_LEN);

  if (unlikely(bytes_read == -1)) {
    return EXIT_FAILURE;
  }

  if (unlikely(bytes_read == 0)) {
    char *pwd = getenv("PWD");
    puts(pwd);
    return 0;
  }

  write(STDOUT_FILENO, old_pwd_buf, bytes_read);
  return 0;
}
