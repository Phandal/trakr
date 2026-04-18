#ifndef TRAKR_H
#define TRAKR_H

#define TRAKR_TIME_LENGTH 6

#define TRAKR_TASK_LENGTH 512

// Note the extra 7 is for ' | ' twice  and the ending '\0'
#define TRAKR_SESSION_LENGTH (TRAKR_TIME_LENGTH + TRAKR_TIME_LENGTH + TRAKR_TASK_LENGTH + 7)

#define TRAKR_DIR "~/.trakr"

void trakr_log(const char *, ...);

#endif // TRAKR_H
