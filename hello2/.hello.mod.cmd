cmd_/home/alex/work/hello2/hello.mod := printf '%s\n'   start.o stop.o | awk '!x[$$0]++ { print("/home/alex/work/hello2/"$$0) }' > /home/alex/work/hello2/hello.mod
