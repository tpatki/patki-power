Build:
----------------------------------------------------------------------
- add scripts directory to your PATH environment variable
- irs_build <new build dir> <irs base dir>
- cd <new build dir>/build
- irs_config (to see a list of predefined configs)
- irs_config <config>
- make depend
- make

Run:
----------------------------------------------------------------------
srun -N <nodes> -n <ranks> <new_build_dir>/codes_opt/irs <irs base dir>/decks/zrad3d -def NZONES_PER_DOM_SIDE=50 -def NDOMS=64 -k 0064MPI -child_io_off
example: srun -N 8 -n 64 ./irs ../../decks/zrad3d -def NZONES_PER_DOM_SIDE=50 -def NDOMS=64 -k 0064MPI -child_io_off
