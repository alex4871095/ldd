cmd_/home/alex/work/radio7/Module.symvers :=  sed 's/ko$$/o/'  /home/alex/work/radio7/modules.order | scripts/mod/modpost -m      -o /home/alex/work/radio7/Module.symvers -e -i Module.symvers -T - 
