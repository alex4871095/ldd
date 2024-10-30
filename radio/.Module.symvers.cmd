cmd_/home/alex/work/radio/Module.symvers :=  sed 's/ko$$/o/'  /home/alex/work/radio/modules.order | scripts/mod/modpost -m      -o /home/alex/work/radio/Module.symvers -e -i Module.symvers -T - 
