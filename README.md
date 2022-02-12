<h1 align=center>File encrypter</h1>

**C program for encrypting/decrypting files in a (probably) shitty way.**

Feel free to edit and improve the code. Specially the MAC part.

# Table of contents
1. [Files](https://github.com/r4v10l1/file-encrypter#Files)
2. [Todo](https://github.com/r4v10l1/file-encrypter#Todo)
<br><br>

## Files
File                 | Description
---------------------|-------------------
`encrypt.c`          | For encrypting and decrpyting files.
`Misc/encode.c`      | Apply caesar cipher with the specified OFFSET.
`Misc/get_values.c`  | Prints the values in `int` and `char` from a file (`./get_values.o < file.txt`). Useful for debugging.

## Todo
- [ ] For some reason some passwords are not read (I assume) correctly. For example 'TEST123'.
