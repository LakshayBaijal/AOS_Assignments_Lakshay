Advanced Operating Systems - Assignment 1
2024202006 Lakshay Baijal
IIIT Hyderabad 2024

Overview -
1) Reversing File Content.
2) File and Directory Verification

Q1) Reversing File Content
Input - Program has 3 arguments 
- The Path of the input File
- Flag input 0 or 1
- if Flag = 1 then input arguments for starting index and ending index.

If Flag is 0 the entire file will reverse and stores output in a directory named Assignment 1 with name 0_<input file.txt>
If Flag is 1 the starting and ending index range with reverse but middle part will remain same. It will Store output in a directory named Assignment 1 with 1_<input file.txt>

How to execute Q1 Reverse File Content

g++ 2024202006_A1_Q1.cpp    					-> for file compilation
./a.out <input text> 0       					-> for flag = 0
./a.out <input text> 1 <starting index> <ending index>          -> for flag = 1
eg. ./a.out input.txt 1 3 7



Q2) File and Directory Verification
Input - Program has 3 arguments
- Relative Path to the input file of Task 1
- Relative Path to the output file inside directory assignment 1 ( Output File must be executed using Flag=0
- Relative Path to Assignment 1 directory

Output 
- It will print if Directory was created
- It will print if output file = input file reversed with flag = 0
- It will print if both files are of same size
- It will print permissions of the input file output file and directory for user,group and others permissions

How to execute Q2 File and Directory Verification
g++ 2024202006_A1_Q2.cpp 					-> for file compilation
./a.out <input text> <output text> <directory text>
eg. ./a.out input.txt Assignment1/input.txt Assignment1



How to Implement
Q1) Reversing File Content

Store user input information to array argv[] and create local variables which stores the arrays informations
Add conditions of Flag == 1 or 0 and count no = 5
Create Directory Assignment 1 and store users inputfilename and outputfilename as string.

Create a Buffer which reads chunks of files as file size can be huge.
for file size offset use LSEEK and move pointer from starting to SEEK_END.
Before writing in outputfile we need to reverse the contents and create function call which swaps data of starting with ending. 

Always check if buffer size is not greater than remaining file and store the minimum and move that pointer in input file.
After storing the minimum in variable write it in output file.


for Flag = 1
Divide the file into 3 parts ( 0 to starting index, starting index to ending index, ending index to filesize)
run loops and read file according to flag 0 files.
For starting to ending index dont use function reverse call and directly write the read data.

Close both files.




Q2) File and Directory Verification

Use the stat system call to verify the assignment 1 Directory Exist,File Size and print 
Create function to check the reversing of the file.
Check permissions by using stat structure and for each file check Users, Groups and Others Permissions 

