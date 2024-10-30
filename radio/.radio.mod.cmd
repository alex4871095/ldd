cmd_/home/alex/work/radio/radio.mod := printf '%s\n'   radio_main.o radio_or.o | awk '!x[$$0]++ { print("/home/alex/work/radio/"$$0) }' > /home/alex/work/radio/radio.mod
