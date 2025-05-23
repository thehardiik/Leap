# LZ Compression Tool

```
 _    _          _ _    _____ _                                   
| |  | |        (_) |  / ____| |                                  
| |__| | __ _ ___ _| | | (___ | |__   __ _ _ __  _ __   ___  _ __   
|  __  |/ _` |/ __| | | \___ \| '_ \ / _` | '_ \| '_ \ / _ \| '_ \  
| |  | | (_| | (__| | | ____) | | | | (_| | | | | | | | (_) | | | | 
|_|  |_|\__,_|\___|_|_| |_____/|_| |_|\__,_|_| |_|_| |_|\___/|_| |_| 
```

*"Information is the resolution of uncertainty" - Claude Shannon*

A simple Lempel-Ziv compression tool written in C.

## Build

```bash
gcc lztool.c compress.c decompress.c -o lztool
```

## Usage

```bash
# Compress a file
./lztool compress input.txt compressed.lz78

# Decompress a file
./lztool decompress compressed.lz78 output.txt
```

## Examples

```bash
# Compress
./lztool compress document.txt document.lz78

# Decompress
./lztool decompress document.lz78 restored.txt

```

That's it!
