.PHONY:clean all rel
all:
	@cd ov9732; make
	#@for x in `find ./ -maxdepth 2 -mindepth 2 -name "Makefile" `; \
	#   do cd `dirname $$x`; if [ $$? ]; then make || exit 1; cd ../; fi; done

clean:
	@cd ov9732; make clean
	#@for x in `find ./ -maxdepth 2 -mindepth 2 -name "Makefile" `; \
	#   do cd `dirname $$x`; if [ $$? ]; then make clean; cd ../; fi; done

