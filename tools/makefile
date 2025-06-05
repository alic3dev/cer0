directory_output=output

directories_tools=${dir ${wildcard ./*/makefile}}

tools_make=${addprefix make/, ${directories_tools}}
tools_clean=${addprefix clean/, ${directories_tools}}

all: ${tools_make}
clean_all: ${tools_clean} clean
clean: clean_output

make/%: %
	cd $< && make

clean/%: %
	cd $< && make clean

clean_output:
	-rm -r ${directory_output}
