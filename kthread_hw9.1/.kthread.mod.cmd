cmd_/home/alex/work/kthread_hw9.1/kthread.mod := printf '%s\n'   kthread.o | awk '!x[$$0]++ { print("/home/alex/work/kthread_hw9.1/"$$0) }' > /home/alex/work/kthread_hw9.1/kthread.mod
