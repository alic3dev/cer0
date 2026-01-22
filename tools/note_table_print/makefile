name=note_table_print

ifndef target_device_version
target_device_version=26.1
endif

target_platform=arm64-apple-macos${target_device_version}

directory_sdk=${shell xcrun --sdk macosx${target_device_version} --show-sdk-path}

directory_objects_base=objects
directory_output=../output

directory_objects=${directory_objects_base}/release

directory_cer0=../..
directory_cer0_include=${directory_cer0}/include
directory_cer0_library=${directory_cer0}/library/macos/release

directory_clic3=../../../clic3
directory_clic3_include=${directory_clic3}/include
directory_clic3_library=${directory_clic3}/library/macos/release

directory_math_c=../../../math_c
directory_math_c_include=${directory_math_c}/include

version_target_cer0=0
version_target_clic3=0

file_output_debug:=${directory_output}/${name}_debug
file_output_release=${directory_output}/${name}
file_output=${file_output_release}

file_library_cer0=${directory_cer0_library}/cer0.${version_target_cer0}.dylib
file_library_clic3=${directory_clic3_library}/clic3.${version_target_cer0}.dylib

ifeq (${debug}, 1)
	name:=${name}_debug
	directory_objects=${directory_objects_base}/debug
	directory_library:=${directory_library_debug}
	directory_cer0_library:=${directory_cer0_library}_debug
	file_library_cer0=${directory_cer0_library}/cer0_debug.${version_target_cer0}.dylib
	file_output=${file_output_debug}
endif

directory_include=include
directory_sources=sources

files_sources=${wildcard ${directory_sources}/*.c}
files_objects=${patsubst ${directory_sources}/%.c,${directory_objects}/%.o,${files_sources}}

cc=clang
c_flags_platform=-target ${target_platform} -isysroot ${directory_sdk}
c_flags=-I${directory_include} -I${directory_cer0_include} -I${directory_math_c_include} ${c_flags_platform}
c_flags_output=-framework CoreAudio

ifeq (${debug}, 1)
	c_flags:=${c_flags} -O0 -g -v -da -Q
else
	c_flags:=${c_flags} -O3
endif

${name}: ${file_output}

run: ${file_output}
	cd ${directory_output} && ./${file_output}

${file_output}: ${files_objects} ${file_library_cer0}
	mkdir -p ${directory_output}
	${cc} ${c_flags} ${c_flags_output} ${files_objects} ${file_library_cer0} -o ${file_output}
	-rm ${directory_output}/cer0.${version_target_cer0}.dylib
	-rm ${directory_output}/clic3.${version_target_clic3}.dylib
	ln -s ${file_library_cer0} ${directory_output}/cer0.${version_target_cer0}.dylib
	ln -s ${file_library_clic3} ${directory_output}/clic3.${version_target_clic3}.dylib

${directory_objects}/%.o: ${directory_sources}/%.c
	mkdir -p ${directory_objects}
	${cc} ${c_flags} -c $< -o $@

${file_library_cer0}:
	cd ${directory_cer0} && make

clean: clean_objects clean_output_debug clean_output_release

clean_objects:
	-rm -r ${directory_objects_base} 2> /dev/null

clean_output_debug:
	-rm ${file_output_debug} 2> /dev/null

clean_output_release:
	-rm ${file_output_release} 2> /dev/null
