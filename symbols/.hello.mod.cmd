cmd_/home/alex/work/symbols/hello.mod := printf '%s\n'   start.o stop.o | awk '!x[$$0]++ { print("/home/alex/work/symbols/"$$0) }' > /home/alex/work/symbols/hello.mod
