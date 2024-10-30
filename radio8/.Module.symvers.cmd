cmd_/home/alex/work/radio8/Module.symvers :=  sed 's/ko$$/o/'  /home/alex/work/radio8/modules.order | scripts/mod/modpost -m      -o /home/alex/work/radio8/Module.symvers -e -i Module.symvers -T - 
