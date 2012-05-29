#ifndef MSR_OPT_H
#define MSR_OPT_H


//PATKI: These are static because we need to know in rapl_finalize if we are in the dry-run mode
//so we can write out an empty file.
static int dry_run_flag = 1;
static int read_only_flag = 0;
static int read_write_flag = 0;

void get_env_variables(struct rapl_state_s *s);
void set_power_bounds();
#endif //MSR_OPT_H
