cmd_/home/alex/work/time_kernel/time_kernel.mod := printf '%s\n'   start.o stop.o | awk '!x[$$0]++ { print("/home/alex/work/time_kernel/"$$0) }' > /home/alex/work/time_kernel/time_kernel.mod
