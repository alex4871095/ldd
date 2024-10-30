cmd_/home/alex/work/symbols3/symbol3.mod := printf '%s\n'   symbol3.o | awk '!x[$$0]++ { print("/home/alex/work/symbols3/"$$0) }' > /home/alex/work/symbols3/symbol3.mod
