# OperatingSystemsProject2

This project focuses on creating, reading, writing, editing, and deleting large files using double indirect pointers in the inode structure, along with implementing encryption for specific files on disk.

## Double Indirect Pointers
The inode and dinode structures have been modified to support double indirect pointers for blocks. After this enhancement, a file can consist of up to 11 + 128 + 128*128 blocks. Comprehensive research on the file system is necessary to ensure full functionality in all cases. Note that modifications to the `mkfs` tool are not required for this implementation.

## Encryption and Decryption
A Caesar cipher is utilized for encryption. This cipher requires a single integer as the key for both encryption and decryption and is applicable to all characters in the ASCII table. The key is set using the `setkey` system call, which is global across the operating system. The key must always be a positive integer or zero, and any user program can invoke this call to modify the global key.

Once the key is established, files on disk can be encrypted or decrypted using the `encr` and `decr` system calls. Both calls expect that the file is already open for reading and writing.

### Automatic Encryption/Decryption
The behavior of the `read` and `write` system calls has been modified to automatically perform encryption or decryption when reading or writing. Files will store encryption status in the major attribute of the inode structure: `0` indicates the file is not encrypted, while `1` signifies it is. The operations rely on the globally set encryption/decryption key. If an incorrect key is used during file reading, the output will be nonsensical.

## System Calls
System calls must not print messages to the screen. All output, whether indicating success or failure, should be handled by user programs.

### System Call Descriptions
- **`int setecho(int do_echo);`**
  - Toggles echo functionality on the console. If the parameter is `1`, normal operation occurs. If `0`, all characters except `'\n'` are displayed as `'*'`. Returns `-1` on error, `0` otherwise.

- **`int setkey(int key);`**
  - Accepts the key for encryption and decryption. Returns `-1` on error, `0` otherwise.

- **`int encr(int fd);`**
  - Encrypts the specified file using the current global encryption key. The file descriptor must refer to an open file. Files of type `T_DEV` cannot be encrypted. Possible return values:
    - `-1`: Key not set.
    - `-2`: File type is `T_DEV`.
    - `-3`: File is already encrypted.
    - `0`: Successful encryption.

- **`int decr(int fd);`**
  - Decrypts the specified file using the current global decryption key. The file descriptor must refer to an open file. Files of type `T_DEV` cannot be decrypted. Possible return values:
    - `-1`: Key not set.
    - `-2`: File type is `T_DEV`.
    - `-3`: File is not encrypted.
    - `0`: Successful decryption.

## User Programs
If an error occurs during a system call, the user program must print a meaningful error message to inform the user.

### Available User Programs
- **`setkey`**
  - Sets the key for encryption and decryption using the `setkey` system call, which can be entered via command line parameters or standard input. Options:
    - `--help (-h)`: Displays the help menu.
    - `--secret (-s)`: Accepts the key from standard input, masking it using the `setecho` system call.

- **`blockwriter`**
  - Creates a file of arbitrary size (in blocks) with predictable text. By default, it creates a file of 150 blocks named `long.txt`, but these values can be modified using command line arguments. Options:
    - `--help (-h)`: Displays the help menu.
    - `--output-file (-o) FILENAME`: Sets the name of the newly created file.
    - `--blocks (-b) BLOCKS`: Sets the number of blocks to write.

- **`encr`**
  - Encrypts one or more files using the `encr` system call. If no file name is specified, the help menu is displayed. Options:
    - `--help (-h)`: Displays the help menu.
    - `--encrypt-all (-a)`: Encrypts all non-encrypted files in the current directory.

- **`decr`**
  - Decrypts one or more files using the `decr` system call. If no file name is specified, the help menu is displayed. Options:
    - `--help (-h)`: Displays the help menu.
    - `--decrypt-all (-a)`: Decrypts all encrypted files in the current directory.

This implementation enhances the file system's capabilities and introduces encryption to improve data security.
