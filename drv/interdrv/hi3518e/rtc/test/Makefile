ifeq ($(PARAM_FILE), )
    PARAM_FILE:=../../../../../mpp/Makefile.param
    include $(PARAM_FILE)
endif

default:
	$(CC) -Wall -O2 -I../ rtc_test.c -o rtc_test -static

clean:
	rm -rf rtc_test *.o
