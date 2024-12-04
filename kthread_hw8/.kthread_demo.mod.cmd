cmd_/home/alex/work/kthread_hw8/kthread_demo.mod := printf '%s\n'   kthread_demo.o | awk '!x[$$0]++ { print("/home/alex/work/kthread_hw8/"$$0) }' > /home/alex/work/kthread_hw8/kthread_demo.mod
