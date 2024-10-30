cmd_/home/alex/work/paramdemo5/paramdemo.mod := printf '%s\n'   paramdemo.o | awk '!x[$$0]++ { print("/home/alex/work/paramdemo5/"$$0) }' > /home/alex/work/paramdemo5/paramdemo.mod
