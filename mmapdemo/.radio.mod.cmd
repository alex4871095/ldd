cmd_/home/alex/work/mmapdemo/radio.mod := printf '%s\n'   radio.o | awk '!x[$$0]++ { print("/home/alex/work/mmapdemo/"$$0) }' > /home/alex/work/mmapdemo/radio.mod
