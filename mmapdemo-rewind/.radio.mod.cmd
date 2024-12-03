cmd_/home/alex/work/mmeapdemo-rewind/radio.mod := printf '%s\n'   radio.o | awk '!x[$$0]++ { print("/home/alex/work/mmeapdemo-rewind/"$$0) }' > /home/alex/work/mmeapdemo-rewind/radio.mod
