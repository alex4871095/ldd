cmd_/home/alex/work/symbols2/symbol2.mod := printf '%s\n'   symbol2.o | awk '!x[$$0]++ { print("/home/alex/work/symbols2/"$$0) }' > /home/alex/work/symbols2/symbol2.mod
