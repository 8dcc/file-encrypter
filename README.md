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
...

$ ./file-encrypter -h
...
```

### Installing
For adding the program to the path and installing the manpage, run:
```console
$ sudo make install
...
```

### Usage
```
SYNOPSIS
       ./file-encrypter.out [-h] [-p password] -e|-d input output

OPTIONS
       -h     Show this help.

       -p password
              Use  password when encrypting or decrypting the file, instead of
              asking for one

       -e input output
              Encrypts data from input and writes to output.  They can be file
              names  or  in  the case of '-' it will read/write from stdin and
              stdout.  Keep in mind that if you don't use -p, it will  try  to
              read the password from stdin as well.

       -d input output
              Decrypts  data  from input and writes to output.  Just like with
              -e, they can be file names  or  in  the  case  of  '-'  it  will
              read/write from stdin and stdout.

EXAMPLES
       file-encrypter -e input.txt output.txt
              Will  encrypt  the  contents of input.txt and write them to out-
              put.txt.

       file-encrypter -p "t3st!" -d input.txt output.txt
              Will decrypt the contents of input.txt using "t3st!" as password
              and write them to output.txt.

       cat some-stuff.txt | file-encrypter -p "my-p4ss" -e - output.txt
              Will  encrypt  the  contents  of stdin (in this case what he got
              from the cat(1) pipe) using "my-p4ss" as password and write them
              to output.txt.
```

### Credits
- Very clean and lightweight [aes256 library](https://github.com/ilvn/aes256) used in this project.
- [Md5 library](https://github.com/Zunawe/md5-c), used for hashing the user passwords.

