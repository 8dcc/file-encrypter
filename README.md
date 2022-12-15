# File encrypter

**C program (and tiny lib/wrapper) for encrypting/decrypting files using aes256.**

The [`src/encrypt.c`](src/encrypt.c) file is made so you can use it in other
programs, simply copy `src/encrypt.*`, `src/misc.*`, `src/lib/` to your project.

Feel free to PR.

### Compiling
Simply run:
```console
$ git clone https://github.com/r4v10l1/file-encrypter

$ cd file-encrypter

$ make

$ ./file-encrypter
Usage:
    ./file-encrypter.out -e <filename>   - For encrypting a file
    ./file-encrypter.out -d <filename>   - For decrypting a file
```

### Credits
- Very clean and lightweight [aes256 library](https://github.com/ilvn/aes256) used in this project.
- [Md5 library](https://github.com/Zunawe/md5-c), used for hashing the user passwords.

