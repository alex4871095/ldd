cmd_/home/alex/work/radio_rw/radio.mod := printf '%s\n'   radio_main.o radio_or.o radio_rw.o | awk '!x[$$0]++ { print("/home/alex/work/radio_rw/"$$0) }' > /home/alex/work/radio_rw/radio.mod
