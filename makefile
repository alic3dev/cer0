name=cer0

directory_clice=../clic3
directory_clice_include=${directory_clice}/include
directory_clice_library=${directory_clice}/library
directory_include=include
directory_library=library
directory_objects=objects
directory_sources=sources
directory_tools=tools

file_library=${directory_library}/${name}.o
file_library_clice=${directory_clice_library}/clic3.o

files_sources=${wildcard ${directory_sources}/*.c}
files_objects=${patsubst ${directory_sources}/%.c,${directory_objects}/%.o,${files_sources}}

cc=clang
c_flags=-O3 -I${directory_include} -I${directory_clice_include}

ld=ld
ld_flags=

strip=strip
strip_flags=-x

${name}: ${file_library}

all: ${name} tools

tools: ${file_library} .force
	cd ${directory_tools} && make all

${file_library}: ${files_objects} ${directory_library}
	${ld} ${ld_flags} -r ${files_objects} -o ${file_library}
	${strip} ${strip_flags} ${file_library}

${directory_objects}/%.o: ${directory_sources}/%.c ${directory_objects}
	${cc} ${c_flags} -c $< -o $@

${directory_library}:
	mkdir -p ${directory_library}

${directory_objects}:
	mkdir -p ${directory_objects}

clean_all: clean clean_tools

clean: clean_library clean_objects

clean_library:
	-rm -r ${directory_library} 2> /dev/null

clean_objects:
	-rm -r ${directory_objects} 2> /dev/null

clean_tools:
	cd ${directory_tools} && make clean_all

.force:
