cmd_/home/alex/work/radio1/Module.symvers :=  sed 's/ko$$/o/'  /home/alex/work/radio1/modules.order | scripts/mod/modpost -m      -o /home/alex/work/radio1/Module.symvers -e -i Module.symvers -T - 
