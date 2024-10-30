cmd_/home/alex/work/symbols/my_alert.mod := printf '%s\n'   my_alert.o | awk '!x[$$0]++ { print("/home/alex/work/symbols/"$$0) }' > /home/alex/work/symbols/my_alert.mod
