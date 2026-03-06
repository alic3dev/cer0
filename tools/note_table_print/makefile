name=note_table_print

target_os=macos

ifeq (${debug}, 1)
target_build=debug
suffix_library_target_build=_${target_build}
else
target_build=release
suffix_library_target_build=
endif

suffix_library_target=${suffix_library_target_os}${suffix_library_target_build}
path_target:=${target_os}/${target_build}

name:=${name}${suffix_library_target}

ifndef target_device_version
target_device_version=26.1
endif

target_platform=arm64-apple-macos${target_device_version}

directory_sdk=${shell xcrun --sdk macosx${target_device_version} --show-sdk-path}

directory_objects_base=objects
directory_output=../output

directory_objects=${directory_objects_base}/${target_build}

directory_cer0=../..
directory_cer0_include=${directory_cer0}/include
directory_cer0_library=${directory_cer0}/library/${path_target}

directory_clic3=../../../clic3
directory_clic3_include=${directory_clic3}/include
directory_clic3_library=${directory_clic3}/library/${path_target}

directory_math_c=../../../math_c
directory_math_c_include=${directory_math_c}/include

version_target_cer0=0
version_target_clic3=0

file_output=${directory_output}/${name}

file_library_cer0=${directory_cer0_library}/cer0${suffix_library_target}.${version_target_cer0}.dylib
file_library_clic3=${directory_clic3_library}/clic3${suffix_library_target}.${version_target_cer0}.dylib

file_output_symbolic_link_cer0=${directory_output}/cer0${suffix_library_target}.${version_target_cer0}.dylib
file_output_symbolic_link_clic3=${directory_output}/clic3${suffix_library_target}.${version_target_clic3}.dylib

directory_include=include
directory_sources=sources

files_sources=${wildcard ${directory_sources}/*.c}
files_objects=${patsubst ${directory_sources}/%.c,${directory_objects}/%.o,${files_sources}}

cc=clang
c_flags_platform=-target ${target_platform} -isysroot ${directory_sdk}
c_flags=-I${directory_include} -I${directory_cer0_include} -I${directory_clic3_include} -I${directory_math_c_include} ${c_flags_platform}
c_flags_output=-framework CoreAudio

ifeq (${debug}, 1)
c_flags:=${c_flags} -O0 -g -v
else
c_flags:=${c_flags} -O3
endif

${name}: ${file_output}

run: ${file_output}
	cd ${directory_output} && ./${file_output}

${file_output}: ${files_objects}
	mkdir -p ${directory_output}
	${cc} ${c_flags} ${c_flags_output} ${files_objects} ${file_library_cer0} ${file_library_clic3} -o ${file_output}
	if [[ ! -h ${file_output_symbolic_link_cer0} ]]; then ln -s ${file_library_cer0} ${file_output_symbolic_link_cer0}; fi
	if [[ ! -h ${file_output_symbolic_link_clic3} ]]; then ln -s ${file_library_clic3} ${file_output_symbolic_link_clic3}; fi

${directory_objects}/%.o: ${directory_sources}/%.c
	mkdir -p ${directory_objects}
	${cc} ${c_flags} -c $< -o $@

clean: clean_objects clean_output

clean_objects:
	if [[ -d ${directory_objects_base} ]]; then rm -r ${directory_objects_base}; fi

clean_output:
	if [[ -d ${directory_output} ]]; then rm -r ${directory_output}; fi
