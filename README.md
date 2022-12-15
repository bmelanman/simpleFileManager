# Simple File Manager
 
A simple file system manager written in C. The system is written mostly from scratch, 
using whatever solution seemed best at the time and principles based off of assumption 
and intuition.

Current functionality includes:
- Create a root directory
- Create directories and files
- Get nested directories and files
- Get the path of a directory or file from a given directory
- Print directory and file debug info to screen
- Print the file tree of a given file

I don't currently have any big plans for the future of this project, so we'll see 
where this ends up. 

Note: The current implementation uses a modified version of user Pzaino's ZVector library, 
which is incredibly useful I might add. It's currently only used as a stack when searching 
through directories, though there are future plans to replace this with a custom implementation. 

The ZVector library can be found here: https://github.com/pzaino/zvector
