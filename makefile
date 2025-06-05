name=cer0

directory_include=include
directory_library=library
directory_objects=objects
directory_sources=sources
directory_tools=tools

file_library=${directory_library}/${name}.o

files_sources=${wildcard ${directory_sources}/*.c}
files_objects=${patsubst ${directory_sources}/%.c,${directory_objects}/%.o,${files_sources}}

cc=clang
c_flags=-O3 -I${directory_include}

ld=ld
ld_flags=

all: ${name} tools

tools: ${file_library} .force
	cd ${directory_tools} && make all

${name}: ${file_library}

${file_library}: ${files_objects} ${directory_library}
	${ld} ${ld_flags} -r ${files_objects} -o $@

${directory_objects}/%.o: ${directory_sources}/%.c ${directory_objects}
	${cc} ${c_flags} -c $< -o $@

${directory_library}:
	mkdir -p ${directory_library}

${directory_objects}:
	mkdir -p ${directory_objects}

clean_all: clean clean_tools

clean: clean_library clean_objects

clean_library:
	-rm -r ${directory_library}

clean_objects:
	-rm -r ${directory_objects} 

clean_tools:
	cd ${directory_tools} && make clean_all

.force:
