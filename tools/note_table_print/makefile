name=note_table_print

directory_include=include
directory_objects=objects
directory_output=../output
directory_sources=sources

directory_cer0=../..
directory_cer0_include=${directory_cer0}/include
directory_cer0_library=${directory_cer0}/library

file_cer0_library=${directory_cer0_library}/cer0.o

file_output=${directory_output}/${name}

files_sources=${wildcard ${directory_sources}/*.c}
files_objects=${patsubst ${directory_sources}/%.c,${directory_objects}/%.o,${files_sources}}

cc=clang
c_flags=-O3 -I${directory_include} -I${directory_cer0_include}
c_flags_output=-framework CoreAudio 

${note_table_print}: ${file_output}

${file_output}: ${files_objects} ${file_cer0_library} ${directory_output}
	${cc} ${c_flags} ${c_flags_output} ${files_objects} ${file_cer0_library} -o ${file_output}

${directory_objects}/%.o: ${directory_sources}/%.c ${directory_objects}
	${cc} ${c_flags} -c $< -o $@

${file_cer0_library}:
	cd ${directory_cer0} && make

${directory_objects}:
	mkdir ${directory_objects}

${directory_output}:
	mkdir ${directory_output}

clean: clean_objects clean_output

clean_objects:
	-rm -r ${directory_objects}

clean_output:
	-rm ${file_output}
