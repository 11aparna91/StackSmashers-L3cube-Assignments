DuplicateAndRemove
--------------------------------------------------------------
DuplicateAndRemove is a program in java to find the duplicate files under a directory specified. The program accepts the directory to be scanned as a command line argument and scans all its files and subdirectories to find duplicate files.

SHA-512 hashing is used to find duplicate files. The file paths are mapped to a hashmap according to their SHA-512. Two or more files mapped to the same bucket are duplicates and they are listed on screen. The user is then given the option to delete one of the duplicate files.

Usage:
C:\Users\user>javac DuplicateAndRemove.java

C:\Users\user>java DuplicateAndRemove <path_to_directory>

Output
---------------------------------------------------------------
Duplicate files found:-
------------------
D:\PRERIT\Music\New folder\New Text Document.txt
D:\PRERIT\Music\New folder (2)\New Text Document.txt
------------------
D:\PRERIT\Music\Atif Aslam\Best of Atif Aslam\AlbumArt_{D46F004D-B937-42B0-B68D-F80E9E741CC5}_Large.jpg
D:\PRERIT\Music\Atif Aslam\Best of Atif Aslam\Folder.jpg
------------------
D:\PRERIT\Music\Atif Aslam\Best of Atif Aslam\AlbumArtSmall.jpg
D:\PRERIT\Music\Atif Aslam\Best of Atif Aslam\AlbumArt_{D46F004D-B937-42B0-B68D-F80E9E741CC5}_Small.jpg
------------------
D:\PRERIT\Music\Aadat.mp3
D:\PRERIT\Music\Atif Aslam\Best of Atif Aslam\Aadat.mp3
D:\PRERIT\Music\New folder (2)\Aadat.mp3
D:\PRERIT\Music\New folder (2)\New folder\Aadat.mp3
------------------
Do you wish to delete duplicate files?
Yes
Enter the path to duplicate file: 
D:\PRERIT\Music\New folder (2)\New folder\Aadat.mp3

Your file has been deleted!
