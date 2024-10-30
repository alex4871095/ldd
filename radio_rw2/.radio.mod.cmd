cmd_/home/alex/work/radio_rw2/radio.mod := printf '%s\n'   radio_main.o | awk '!x[$$0]++ { print("/home/alex/work/radio_rw2/"$$0) }' > /home/alex/work/radio_rw2/radio.mod
