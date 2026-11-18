#ifdef __linux__
#include <linux/limits.h>
#else
#define PATH_MAX 4096
#endif

#define MAX_PATH_LEN PATH_MAX

#define HISTFILE ".prevwd"

#define unlikely(x) __builtin_expect(!!(x), 0)

int open_histfile(int flags);
