cmd_/home/alex/work/procdemo/procdemo.mod := printf '%s\n'   proc_main.o proc_or.o proc_rw.o | awk '!x[$$0]++ { print("/home/alex/work/procdemo/"$$0) }' > /home/alex/work/procdemo/procdemo.mod
