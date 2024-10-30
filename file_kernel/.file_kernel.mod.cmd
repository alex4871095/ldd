cmd_/home/alex/work/file_kernel/file_kernel.mod := printf '%s\n'   start.o stop.o | awk '!x[$$0]++ { print("/home/alex/work/file_kernel/"$$0) }' > /home/alex/work/file_kernel/file_kernel.mod
