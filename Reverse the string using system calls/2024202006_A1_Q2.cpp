#include<bits/stdc++.h>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h> 

using namespace std;

void reversedflag0(int outfd, int infd, off_t outsize, off_t insize)
{
    char outChar, inChar;
    int flag = 0;
    for (off_t i = 0; i < outsize; ++i) 
    {
        if (pread(outfd, &outChar, 1, i) == -1 || pread(infd, &inChar, 1, outsize - i - 1) == -1) 
        {
            perror("pread");
            cout<<("Whether file contents are reversed in newfile: No \n");
            flag = 1;
        }
        if (outChar != inChar) {
            cout<<("Whether file contents are reversed in newfile: No \n");
            flag = 1;
        }
    }

    if(flag==0)
    {
        cout<<("Whether file contents are reversed in newfile: Yes \n");
    }
}




void checkpermissions(const char* file)
{
    struct stat st;
    if (stat(file, &st) == -1) 
    {
        perror("stat");
        return;
    }  

//User Permissions

    if(st.st_mode & S_IRUSR)
    {
        cout << "User has read permissions on " << file << ": Yes \n";
    }
    else
    {
        cout << "User has read permissions on " << file << ": No \n";
    }

    if(st.st_mode & S_IWUSR)
    {
        cout << "User has write permissions on " << file << ": Yes \n";
    }
    else
    {
        cout << "User has write permissions on " << file << ": No \n";
    }

    if(st.st_mode & S_IXUSR)
    {
        cout << "User has execute permissions on " << file << ": Yes \n";
    }
    else
    {
        cout << "User has execute permissions on " << file << ": No \n";
    }



// Group Permissions

    if(st.st_mode & S_IRGRP)
    {
        cout << "Group has read permissions on " << file << ": Yes \n";
    }
    else
    {
        cout << "Group has read permissions on " << file << ": No \n";
    }
    if(st.st_mode & S_IWGRP)
    {
        cout << "Group has write permissions on " << file << ": Yes \n";
    }
    else
    {
        cout << "Group has write permissions on " << file << ": No \n";
    }
    if(st.st_mode & S_IXGRP)
    {
        cout << "Group has execute permissions on " << file << ": Yes \n";
    }
    else
    {
         cout << "Group has execute permissions on " << file << ": No \n";
    }



// Others Permission

    if(st.st_mode & S_IROTH)
    {
        cout << "Others has read permissions on " << file << ": Yes \n";
    }
    else
    {
        cout << "Others has read permissions on " << file << ": No \n";
    }
    if(st.st_mode & S_IWOTH)
    {
        cout << "Others has write permissions on " << file << ": Yes \n";
    }
    else
    {
        cout << "Others has write permissions on " << file << ": No \n";
    }
    if(st.st_mode & S_IXOTH)
    {
        cout << "Others has execute permissions on " << file << ": Yes \n";
    }
    else
    {
         cout << "Others has execute permissions on " << file << ": No \n";
    }

}   







int main (int argc , char* argv[])
{
    int infd = open(argv[1], O_RDONLY);
    int outfd = open(argv[2], O_RDONLY);

    off_t outsize = lseek(outfd,0,SEEK_END);
    off_t insize = lseek(infd,0,SEEK_END);

    DIR* dir = opendir(argv[3]);

    if(opendir(argv[3]))
    {
        cout<<"Directory is created: Yes \n";
    }
    else
    {
        cout<<"Directory is created: No \n";
    }

    reversedflag0(outfd,infd,outsize,insize);

    if(outsize == insize)
    {
        cout << "Both Files Sizes are Same : Yes \n";
    }
    else
    {
        cout << "Both Files Sizes are Same : No \n \n";
    }
    cout<<endl;

// Permission for First input File
    cout << "Permissions for " << argv[1] << ":\n";
    checkpermissions(argv[1]);

// Permission for Second Output File
    cout << "Permissions for " << argv[2] << ":\n";
    checkpermissions(argv[2]);

// Permission for Directory
    cout << "Permissions for " << argv[3] << ":\n";
    checkpermissions(argv[3]);


    close(infd);
    close(outfd);
    return 0;
}