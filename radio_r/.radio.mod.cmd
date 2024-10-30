cmd_/home/alex/work/radio_r/radio.mod := printf '%s\n'   radio_main.o radio_or.o radio_read.o | awk '!x[$$0]++ { print("/home/alex/work/radio_r/"$$0) }' > /home/alex/work/radio_r/radio.mod
