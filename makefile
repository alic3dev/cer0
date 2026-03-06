name=cer0

ifndef target_device
target_device=mac
endif

ifeq (${target_device},mac)
target_os=macos
endif

ifeq (${target_device},iphone)
target_os=ios
endif

ifneq (${target_os},macos)
suffix_library_target_os=_${target_os}
else
suffix_library_target_os=
endif

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

version_major=0
version_minor=0
version_patch=0
version_major_minor=${version_major}.${version_minor}
version=${version_major}.${version_minor}.${version_patch}

version_target_clic3=0
version_target_math_c=0

directory_objects_base=objects
directory_library_base=library

directory_library=${directory_library_base}/${path_target}
directory_objects=${directory_objects_base}/${path_target}

directory_clic3=../clic3
directory_clic3_library=${directory_clic3}/library/${path_target}
directory_clic3_include=${directory_clic3}/include

directory_math_c=../math_c
directory_math_c_library=${directory_math_c}/library/${path_target}
directory_math_c_include=${directory_math_c}/include

directory_install=/System/Volumes/Preboot/Cryptexes

file_library_clic3_dylib=${directory_clic3_library}/clic3${suffix_library_target}.${version_target_clic3}.dylib
file_library_clic3_dynamic=${directory_clic3_library}/clic3${suffix_library_target}.${version_target_clic3}.so

file_library_math_c_dylib=${directory_math_c_library}/math_c${suffix_library_target}.${version_target_math_c}.dylib
file_library_math_c_dynamic=${directory_math_c_library}/math_c${suffix_library_target}.${version_target_math_c}.so

directory_objects_c=${directory_objects}/c
directory_objects_obj_c=${directory_objects}/obj_c

directory_include=include
directory_sources=sources
directory_tools=tools

file_library_object=${directory_library}/${name}.o

name_library_dylib_major=${name}.${version_major}.dylib
file_library_dylib=${directory_library}/${name}.dylib
file_library_dylib_major=${directory_library}/${name_library_dylib_major}

file_install=${directory_install}/OS${name}.dylib
file_install_major=${directory_install}/OS${name_library_dylib_major}

name_library_dynamic_major=${name}.${version_major}.so
file_library_dynamic=${directory_library}/${name}.so
file_library_dynamic_major=${directory_library}/${name_library_dynamic_major}

file_library_static=${directory_library}/${name}.a

files_sources_c=${wildcard ${directory_sources}/*.c}
files_sources_obj_c=${wildcard ${directory_sources}/*.m}

files_objects_c=${patsubst ${directory_sources}/%.c,${directory_objects_c}/%.o,${files_sources_c}}
files_objects_obj_c=${patsubst ${directory_sources}/%.m,${directory_objects_obj_c}/%.o,${files_sources_obj_c}}

frameworks=-framework CoreAudio

ifndef target_device_version
target_device_version=26.1
endif

ifeq (${target_os},macos)
target_platform=arm64-apple-macos${target_device_version}

directory_sdk=${shell xcrun --sdk macosx${target_device_version} --show-sdk-path}
else
files_objects_c:=${patsubst ${directory_objects_c}/%.o,${directory_objects_c}/%_${target_os}.o,${files_objects_c}}
files_objects_obj_c:=${patsubst ${directory_objects_obj_c}/%.o,${directory_objects_obj_c}/%_${target_os}.o,${files_objects_obj_c}}

target_platform=arm64-apple-ios${target_device_version}

directory_sdk=${shell xcrun --sdk iphoneos${target_device_version} --show-sdk-path}
endif

files_objects=${files_objects_c} ${files_objects_obj_c}

cc=clang
c_flags_platform=-target ${target_platform} -isysroot ${directory_sdk}
c_flags=-I${directory_include} -I${directory_clic3_include} -I${directory_math_c_include} ${c_flags_platform}

ifneq (${target_os},ios)
c_flags:=${c_flags}
else
c_flags:=${c_flags} -Dtarget_os_ios
endif

ifeq (${debug}, 1)
c_flags:=${c_flags} -O0 -g -v
else
c_flags:=${c_flags} -O3
endif

c_flags_obj_c=${c_flags} -x objective-c -fmodules -fconstant-cfstrings

ar=ar
ar_flags=cqS

ld=ld
ld_flags=

strip=strip
strip_flags=-x

${name}: ${file_library}

ifeq (${target_os},macos)
all: ${name} tools

tools: ${file_library} .always
	cd ${directory_tools} && make all
else
all: ${name}
endif

${name}: ${file_library_dylib} ${file_library_dynamic} ${file_library_object} ${file_library_static}

${name}_objects: ${files_objects}

${name}_dylib: ${file_library_dylib}
${name}_dynamic: ${file_library_dynamic}
${name}_object: ${file_library_object}
${name}_static: ${file_library_static}

install: ${file_library_dylib}
	dd if="${file_library_dylib_major}" of="${file_install_major}"
	ln -s "${file_install_major}" "${file_install}"

${file_library_dylib}: ${files_objects}
	mkdir -p ${directory_library}
	${cc} -dynamiclib ${c_flags_platform} -install_name ${name_library_dylib_major} -current_version ${version} -compatibility_version ${version_major_minor} ${frameworks} ${file_library_clic3_dylib} ${file_library_math_c_dylib} ${files_objects} -o ${file_library_dylib_major}
ifneq (${debug}, 1)
	${strip} ${strip_flags} ${file_library_dylib_major}
endif
	if [[ ! -h ${file_library_dylib} ]]; then ln -s ${name_library_dylib_major} ${file_library_dylib}; fi

${file_library_dynamic}: ${files_objects}
	mkdir -p ${directory_library}
	${cc} -shared ${c_flags_platform} -install_name ${name_library_dynamic_major} -current_version ${version} -compatibility_version ${version_major_minor} ${frameworks} ${file_library_clic3_dynamic} ${file_library_math_c_dynamic} ${files_objects} -o ${file_library_dynamic_major}
ifneq (${debug}, 1)
	${strip} ${strip_flags} ${file_library_dynamic_major}
endif
	if [[ ! -h ${file_library_dynamic} ]]; then ln -s ${name_library_dynamic_major} ${file_library_dynamic}; fi

${file_library_object}: ${files_objects}
	mkdir -p ${directory_library}
	${ld} ${ld_flags} -r ${files_objects} -o ${file_library_object}
ifneq (${debug}, 1)
	${strip} ${strip_flags} ${file_library_object}
endif

${file_library_static}: ${files_objects}
	mkdir -p ${directory_library}
	${ar} ${ar_flags} ${file_library_static} ${files_objects}

${directory_objects_c}/%.o: ${directory_sources}/%.c
	mkdir -p ${dir $@}
	${cc} ${c_flags} -c $< -o $@

${directory_objects_obj_c}/%.o: ${directory_sources}/%.m
	mkdir -p ${dir $@}
	${cc} ${c_flags_obj_c} -c $< -o $@

${directory_objects_c}/%_${target_os}.o: ${directory_sources}/%.c
	mkdir -p ${dir $@}
	${cc} ${c_flags} -c $< -o $@

${directory_objects_obj_c}/%_${target_os}.o: ${directory_sources}/%.m
	mkdir -p ${dir $@}
	${cc} ${c_flags_obj_c} -c $< -o $@

clean_all: clean clean_tools

clean: clean_library clean_objects

clean_library:
	if [[ -d ${directory_library_base} ]]; then rm -r ${directory_library_base}; fi

clean_objects:
	if [[ -d ${directory_objects_base} ]]; then rm -r ${directory_objects_base}; fi

clean_tools:
	cd ${directory_tools} && make clean_all

.always:
