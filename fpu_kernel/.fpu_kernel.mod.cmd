cmd_/home/alex/work/fpu_kernel/fpu_kernel.mod := printf '%s\n'   fpu_kernel.o | awk '!x[$$0]++ { print("/home/alex/work/fpu_kernel/"$$0) }' > /home/alex/work/fpu_kernel/fpu_kernel.mod
