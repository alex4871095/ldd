cmd_/home/alex/work/hello1/hello.mod := printf '%s\n'   hello.o | awk '!x[$$0]++ { print("/home/alex/work/hello1/"$$0) }' > /home/alex/work/hello1/hello.mod
