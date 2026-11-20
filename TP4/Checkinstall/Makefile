all: hello_check stack_frame

hello_check: hello_check.c
	gcc hello_check.c -o hello_check

stack_frame: stack_frame.c
	gcc stack_frame.c -o stack_frame

install:
	mkdir -p /usr/local/bin
	cp hello_check /usr/local/bin/
	cp stack_frame /usr/local/bin/

clean:
	rm -f hello_check stack_frame
