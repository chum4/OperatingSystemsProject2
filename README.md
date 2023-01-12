# OperatingSystemsProject2
Creating, reading, writing, editing and deleting large files with the help of double indirect pointers in the inode structure. Encryption of the contents of certain files on the disk.

Double indirect node
Change the inode (both inode and dinode) structure to support double indirect pointers for blocks. After the change, one file should be able to consist of 11 + 128 + 128*128 blocks. Do a thorough research of the file system and make sure it works in all cases. Changing the mkfs tool is not required.
Encryption and decryption
A Caesar cipher is used for encryption purposes. This cipher requires setting a single int number as the key for encryption and decryption, and should work for all characters in the ASCII table. Setting this key is done using the setkey system call, and the key is global at the level of the entire operating system. The key is always a positive number or zero. Any user program can make this call to change the global key.

Once the key is set, a file already on disk can be encrypted or decrypted using the encr and decr system calls. Both system calls expect that the file is already open, both for reading and writing.

In addition to this, it is necessary to change the behavior of read / write system calls, so that they automatically perform decryption / encryption when reading / writing. Files will have encryption information recorded in the major attribute in the inode structure: 0 means the file is not encrypted, and 1 means it is. These operations use a globally set decryption/encryption key. If the wrong key is used when reading the file, it is expected to receive gibberish as a result of the read.

System calls
System calls must not print to the screen. All printing, whether the system call was successful or not, must be done by user programs.

int setecho(int do_echo);
The system call turns echo functionality on or off on the console. If the passed parameter is 1, the system works normally. If the passed parameter is 0, all characters except '\n' are printed to the console as '*'. The system call returns -1 if an error occurred while executing the system call, and 0 otherwise.

int setkey(int key);
The passed parameter is the key to be used for encryption and decryption. The system call returns -1 if an error occurred while executing the system call, and 0 otherwise.

int encr(int fd);
The system call encrypts the file using the currently set global encryption key. The passed parameter is the file descriptor of the file to be encrypted, and it is expected that the file is open for reading and writing. Files of type T_DEV cannot be encrypted. The return value can be one of:
-1: key not set.
-2: file is of type T_DEV.
-3: file is already encrypted.
0: system call completed successfully.

int decr(int fd);
The system call decrypts the file using the currently set global decryption key. The passed parameter is the file descriptor of the file to be decrypted, and it is expected that the file is open for reading and writing. Files of type T_DEV cannot be decrypted. The return value can be one of:
-1: key not set.
-2: file is of type T_DEV.
-3: file is not encrypted.
0: system call completed successfully.

User programs
If an error occurs while executing a system call, the user program must print a meaningful error message that informs the user that this has occurred.

The setkey program will allow you to set the key for encryption and decryption. The programs encr and decr will enable encryption and decryption of already existing files on the disk. Finally, the blockwriter program will allow the creation of a file that occupies an arbitrary number of blocks and contains simple and predictable text.
blockwriter
blockwriter creates a new file in the current directory of the given size in blocks with the given name. Default values ​​are 150 blocks and filename long.txt. The user of this program can modify these values ​​with line item arguments.
Options:
--help (-h) displays the help menu.
--output-file (-o) FILENAME sets the name for the newly created file FILENAME.
--blocks (-b) BLOCKS sets the number of blocks to write to BLOCKS.
setkey
setkey sets the system key to some value with the help of the setkey system call, which is entered via command line parameters or via STDIN.
Options:
--help (-h) displays the help menu.
--secret (-s) takes the key from STDIN and hides the key with the setecho system call.

encr
encr encrypts one or more files by calling the encr system call. If the name of the encryption file is omitted, print the help menu.
Options:
--help (-h) displays the help menu.
--encrypt-all (-a) encrypts all non-encrypted files in the current directory.
decr
decr decrypts one or more files by calling the decr system call. If the name of the decryption file is omitted, print the help menu.
Options:
--help (-h) displays the help menu.
--decrypt-all (-a) decrypts all encrypted files in the current directory.
