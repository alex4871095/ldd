cmd_/home/alex/work/paramdemo3/paramdemo.mod := printf '%s\n'   paramdemo.o | awk '!x[$$0]++ { print("/home/alex/work/paramdemo3/"$$0) }' > /home/alex/work/paramdemo3/paramdemo.mod
