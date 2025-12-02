# cer0

c:implementation.of->{[`zer0`](https://github.com/alic3dev/zer0)};

## usage

### dependencies

- [clic3](https://github.com/alic3dev/clic3):library->{`clic3.o`}

### include

#### preprocessor_macros

- `cer0_audio_disabled` can be used to disable audio_output (useful for platforms without `CoreAudio` support) 

#### c: [`%.c`|`%.h`]

```c
#include <cer0.h>
```

#### gcc

```zsh
gcc -I${cer0_directory}include
```

### object

```zsh
gcc ${directory_cer0}/library/cer0.o ${directory_clic3}/library/clic3.o
```

### framework

required_for->{executable output}

```zsh
gcc -framework CoreAudio
```

### compilation

#### executable

```zsh
gcc -framework CoreAudio -I${directory_cer0}/include ${directory_cer0}/library/cer0.o ${directory_clic3}/library/clic3.o source.c -o output
```

#### object

```zsh
gcc -I${directory_cer0}/include -c source.c -o source.o
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
