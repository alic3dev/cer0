# cer0

c:implementation.of->{[`zer0`](https://github.com/alic3dev/zer0)};

## usage

### dependencies

- [alic3dev](https://github.com/alic3dev)
- - [clic3](https://github.com/alic3dev/clic3)
- - [math_c](https://github.com/alic3dev/math_c)

### preprocessor_macros

- `target_os_ios`:switches_audio_output_from_core_audio_to_avf_audio

### framework

required_for->{executable output}

```zsh
clang -framework CoreAudio
```

## tools

### note_table_print

prints frequencies for notes within a specified octave range and frequency

#### usage

```
usage: note_table_print #octave_starting #octave_ending #frequency #?steps_notes
```

## development

### `make`:flags

- `debug=1`:adds->{`debugging_symbols`}:disables->{`optimizations`};
- `target_device`:sets_the_target_device_platform->{values::[`mac`|`iphone`]}
- `target_device_version`:sets_the_target_device_version.for->{`macos`|`ios`};

### build

```zsh
# library
make
# tools
make tools
# all
make all
```

### clean

```zsh
# library|objects
make clean
# tools
make clean_tools
# all
make clean all
```

## copyright|copyleft

> © [copyleft|copyright]->{alic3dev(2025|2026)}:[all_rights_reserved|all_lefts_reserved]
