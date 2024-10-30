cmd_/home/alex/work/radio1/radio.mod := printf '%s\n'   radio_main.o radio_or.o | awk '!x[$$0]++ { print("/home/alex/work/radio1/"$$0) }' > /home/alex/work/radio1/radio.mod
