cmd_/home/alex/work/paramdemo4/paramdemo.mod := printf '%s\n'   paramdemo.o | awk '!x[$$0]++ { print("/home/alex/work/paramdemo4/"$$0) }' > /home/alex/work/paramdemo4/paramdemo.mod
