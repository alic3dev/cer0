# cer0

a c reimplementation of [zer0](https://github.com/alic3dev/zer0)

## usage

### dependencies

- [clic3](https://github.com/alic3dev/clic3): library->{`clic3.o`}

### include

#### c: [.c | .h]

```c
#include <cer0.h>
```

#### gcc

```zsh
gcc -I${cer0_directory}include
```

### object

```zsh
gcc ${cer0_directory}/library/cer0.o ${clic3_directory}/library/clic3.o
```

### framework

required for final binary output file  
not required for individually compiled object files

```zsh
gcc -framework CoreAudio
```

### compilation

#### binary

```zsh
gcc -framework CoreAudio -I${cer0_directory}/include ${cer0_directory}/library/cer0.o ${clic3_directory}/library/clic3.o source.c -o output
```

#### object

```zsh
gcc -I${cer0_directory}/include -c source.c -o source.o
```

## development

### build

```zsh
make
```

#### all

```zsh
make all
```

#### tools

```zsh
make tools
```

### clean

```zsh
make clean
```

#### all

```zsh
make clean_all
```

#### tools

```zsh
make clean_tools
```

## copyright|copyleft

> © [copyleft|copyright]->{alic3dev(2025)}:[all_rights_reserved|all_lefts_reserved]
