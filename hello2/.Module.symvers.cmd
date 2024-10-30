cmd_/home/alex/work/hello2/Module.symvers :=  sed 's/ko$$/o/'  /home/alex/work/hello2/modules.order | scripts/mod/modpost -m      -o /home/alex/work/hello2/Module.symvers -e -i Module.symvers -T - 
