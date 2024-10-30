cmd_/home/alex/work/radio_c/radio.mod := printf '%s\n'   radio_main.o radio_or.o | awk '!x[$$0]++ { print("/home/alex/work/radio_c/"$$0) }' > /home/alex/work/radio_c/radio.mod
