cmd_/home/alex/work/fpu_kernel/fpu_mod.mod := printf '%s\n'   start.o stop.o fpu_kernel.o | awk '!x[$$0]++ { print("/home/alex/work/fpu_kernel/"$$0) }' > /home/alex/work/fpu_kernel/fpu_mod.mod
