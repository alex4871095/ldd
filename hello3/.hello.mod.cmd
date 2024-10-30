cmd_/home/alex/work/hello3/hello.mod := printf '%s\n'   hello.o | awk '!x[$$0]++ { print("/home/alex/work/hello3/"$$0) }' > /home/alex/work/hello3/hello.mod
