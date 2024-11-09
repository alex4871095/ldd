cmd_/home/alex/work/mem_kernel/mem_kernel.mod := printf '%s\n'   mem_kernel.o | awk '!x[$$0]++ { print("/home/alex/work/mem_kernel/"$$0) }' > /home/alex/work/mem_kernel/mem_kernel.mod
