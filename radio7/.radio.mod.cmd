cmd_/home/alex/work/radio7/radio.mod := printf '%s\n'   radio_main.o radio_or.o radio_read.o radio_write.o | awk '!x[$$0]++ { print("/home/alex/work/radio7/"$$0) }' > /home/alex/work/radio7/radio.mod
