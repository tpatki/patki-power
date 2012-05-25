#ifndef RESTORE_DEFAULTS_H
#define RESTORE_DEFAULTS_H

#include <stdint.h>
#include <sys/types.h>  // off_t

#define NUM_PACKAGES 2
#define NUM_CORES_PER_PACKAGE 8

#define IA32_PERF_CTL		0x199 // setting bit 32 high DISABLES turbo mode.
#define MSR_PKG_POWER_LIMIT	0x610   // Section 14.7.3 "Package RAPL Domain"
#define MSR_PP0_POWER_LIMIT	0x638   // Section 14.7.4 "PP0/PP1 RAPL Domains"
#define MSR_DRAM_POWER_LIMIT	0x618  

void init_msr();
void finalize_msr();
void read_msr_single_core(int cpu, int core, off_t msr, uint64_t *val);
void write_msr_single_core(int cpu, int core, off_t msr, uint64_t val);
void write_msr_all_cores_v(int cpu, off_t msr, uint64_t *val);
void write_msr(int cpu, off_t msr, uint64_t val);
void enable_turbo(int package);
void disable_turbo( int package );
void restore_defaults();


#endif //RESTORE_DEFAULTS_H
