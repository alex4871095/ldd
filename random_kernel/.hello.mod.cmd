cmd_/home/alex/work/random_kernel/hello.mod := printf '%s\n'   start.o stop.o | awk '!x[$$0]++ { print("/home/alex/work/random_kernel/"$$0) }' > /home/alex/work/random_kernel/hello.mod
