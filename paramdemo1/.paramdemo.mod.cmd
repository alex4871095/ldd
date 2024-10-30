cmd_/home/alex/work/paramdemo1/paramdemo.mod := printf '%s\n'   paramdemo.o | awk '!x[$$0]++ { print("/home/alex/work/paramdemo1/"$$0) }' > /home/alex/work/paramdemo1/paramdemo.mod
