</br>

[![Actions Status](https://github.com/Coldragon/PassCoder2/workflows/Build/badge.svg)](https://github.com/Coldragon/PassCoder2/actions) [![Actions Status](https://img.shields.io/github/v/release/coldragon/PassCoder2.svg)](https://github.com/Coldragon/PassCoder2/releases) [![Actions Status](https://img.shields.io/badge/license-MIT-brightgreen.svg)](./LICENSE.md)

# PassCoder2
PassCoder2 is a simple C99 crossplatform cli database-less password manager. You just have to remember a passphrase and use a tag to recover your password. The tag can be the website name, your email adress or any other string.

# How To Use 
Just run the cli and you'll be prompted to write your passphrase and tag.
There is also some parameters that can be input.
```
usage: PassCoder2.exe [-hv] [<tag>] [-p <phrase>] [--version]

  <tag>                     target tag
  -p, --phrase=<phrase>     private phrase
  -h, --help                display this help and exit
  -v, --verbose             verbose output and exit
  --version                 display version info and exit
```

# External Library
 - argon2 : https://github.com/P-H-C/phc-winner-argon2
 - argtable3 : https://github.com/argtable/argtable3
 - rlutil : https://github.com/tapio/rlutil
 
# Todo 
- [ ] Secure password input
- [ ] Build only a lib and not the cli
- [ ] GUI with auto send to clipboard
- [ ] TU on multiple platform to check consistensy
