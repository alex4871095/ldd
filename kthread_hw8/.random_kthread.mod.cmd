cmd_/home/alex/work/kthread_hw8/random_kthread.mod := printf '%s\n'   random_kthread.o | awk '!x[$$0]++ { print("/home/alex/work/kthread_hw8/"$$0) }' > /home/alex/work/kthread_hw8/random_kthread.mod
