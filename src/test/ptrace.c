/* -*- Mode: C; tab-width: 8; c-basic-offset: 2; indent-tabs-mode: nil; -*- */

#include "rrutil.h"

int main(int argc, char* argv[]) {
  pid_t child;
  int status;

  if (0 == (child = fork())) {
    sleep(1000000);
    return 77;
  }

  test_assert(0 == ptrace(PTRACE_ATTACH, child, NULL, NULL));
  test_assert(child == waitpid(child, &status, 0));
  test_assert(status == ((SIGSTOP << 8) | 0x7f));

  test_assert(0 == kill(child, SIGKILL));

  atomic_puts("EXIT-SUCCESS");
  return 0;
}
