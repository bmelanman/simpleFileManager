# Simple File Manager
 
A simple file system manager written in C. The system is written mostly from scratch using whatever solution seemed best at the time, along with principles based off of assumption and intuition. The main forcus is to simply implement whatever features might interest me and observe how the code base natural evolves over time. 

## Current functionality:
- Creating a root directory
- Creating directories and files
- Searching for nested directories and files
- Obtaining the path of a directory or file relative to the current working directory
- Printing the file tree of a given file
- Printing directory and file debug info to screen

## Ideas for the Future:
- Symbolic Links (Soft/Hard)
- Implement a stack to replace ZVector
- Improved UI
- Implement common commands (`cd`, `ls`, `find`, etc...)

## Notes: 
- The current implementation uses a modified version of user Pzaino's ZVector library (which is incredibly useful I might add!), and it's currently only used to implement a stack for searching through directories. A custom implementation will certainly be implemented in the future if and when I ever get back to this project.
- This is meant to be more of a fun 'time-filler' during school breaks and dull weekends. Thus, I imagine this project will always have an indefinite timeline and a luandry list of todos. Beyond that though, I don't currently have any big plans for the future of this project, so we'll see where this ends up. 

## Feedback:
- If you'd like to leave feedback or point out errors, inefficiencies, etc..., please feel free to do so! I'm always looking to learn more and improve my abilities as a whole :)

## Credit:
- ZVector: 
    - It's a very impressive library, and I'd highly recommend checking it out to see if you can learn something new! 
    - The library can be found here: https://github.com/pzaino/zvector
