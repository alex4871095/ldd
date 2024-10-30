cmd_/home/alex/work/symbols2/arr_sum.mod := printf '%s\n'   arr_sum.o | awk '!x[$$0]++ { print("/home/alex/work/symbols2/"$$0) }' > /home/alex/work/symbols2/arr_sum.mod
