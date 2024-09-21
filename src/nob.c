#define NOB_IMPLEMENTATION
#include "nob.h"

#define ARRAY_AND_COUNT(...) (const char*[]){__VA_ARGS__}, sizeof(const char*[]){__VA_ARGS__}/sizeof(const char*)

bool cmd_append_and_run(Nob_Cmd *cmd, const char *args[], size_t count);

int main(int argc, char **argv) {
  NOB_GO_REBUILD_URSELF(argc, argv);
  nob_log(NOB_INFO, "Compiling UdreBMG...");

  Nob_Cmd cmd = {0};
  nob_cmd_append(&cmd, "gcc", "-Wall", "-Wextra", "-pedantic");

  if (nob_needs_rebuild("block.o", ARRAY_AND_COUNT("block.h", "block.c"))) {
    bool result = cmd_append_and_run(&cmd, ARRAY_AND_COUNT("-c", "block.h", "block.c"));
    if (!result) return 1;
  }

  if (nob_needs_rebuild("../bin/udrebmg", ARRAY_AND_COUNT("main.c", "block.o"))) {
    bool result = cmd_append_and_run(&cmd, ARRAY_AND_COUNT("-o", "../bin/udrebmg", "./main.c", "./block.o"));
    if (!result) return 1;
  }

  cmd.count = 0;
  nob_cmd_append(&cmd, "../bin/udrebmg");
  if (!nob_cmd_run_sync(cmd)) return 1;

  nob_log(NOB_INFO, "Compilation finished! :3");
  nob_cmd_free(cmd);
  return 0;
}

bool cmd_append_and_run(Nob_Cmd *cmd, const char *args[], size_t count) {
  Nob_Cmd cmd_cp = *cmd;

  nob_da_append_many(&cmd_cp, args, count);
  nob_cmd_append(&cmd_cp, "-I./include");
  nob_cmd_append(&cmd_cp, "-L./lib", "-l:libraylib.a", "-lm");

  cmd->capacity = cmd_cp.capacity;

  return nob_cmd_run_sync(cmd_cp);
}
