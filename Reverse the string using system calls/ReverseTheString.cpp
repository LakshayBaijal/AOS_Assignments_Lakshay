#include<bits/stdc++.h>
#include <fcntl.h>
#include <iostream>
using namespace std;

#define BUFFER_SIZE 40



void reverseBuffer(char* buffer, ssize_t size) {
    for (ssize_t i = 0; i < size / 2; ++i) {
        ssize_t temp;
        temp = buffer[i];
        buffer[i]= buffer[size - i-1];
        buffer[size - i-1] = temp;
    }
}

int main(int argc, char *argv[])
{
    string inputfilename = argv[1];
    int flag = stoi(argv[2]);
    off_t startindex = 0;
    off_t endindex = 0;
    if(flag==1 && argc ==5)
    {
        startindex = stoll(argv[3]);
        endindex = stoll(argv[4]);
    }
    int inputfile = open(inputfilename.c_str(), O_RDONLY);
    
    
    const char* outputfilename = "output.txt";
    int outputfile = open(outputfilename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);


    char buffer[BUFFER_SIZE];
    
    off_t filesize = lseek(inputfile,0,SEEK_END);

    if(flag==0)
    {
    ssize_t bytestoread;
    ssize_t byteswritten;
    ssize_t bytesRead;
        while(filesize > 0)
        {
            if (filesize >= BUFFER_SIZE)
            {
                bytestoread = BUFFER_SIZE;
            }
            else
            {
                bytestoread = filesize;
            }

            filesize = filesize - bytestoread;
            lseek(inputfile,filesize,SEEK_SET);

            bytesRead = read(inputfile, buffer, bytestoread);

            reverseBuffer(buffer, bytesRead);
            byteswritten = write(outputfile, buffer, bytesRead);
            
        }
    }



    else if(flag==1)
    {
   
        // Reverse starting
        if(startindex>0)
        {
            ssize_t bytestoread;
            ssize_t byteswritten;
            ssize_t bytesRead;

            off_t remainingbytes = startindex;
            while (remainingbytes > 0)
            {
                if(remainingbytes>=BUFFER_SIZE)
                {
                    bytestoread = BUFFER_SIZE;
                }
                else 
                {
                    bytestoread = remainingbytes;
                }
                remainingbytes = remainingbytes - bytestoread;
                lseek(inputfile, remainingbytes, SEEK_SET);

                bytesRead = read(inputfile, buffer, bytestoread);

                reverseBuffer(buffer, bytesRead);

                byteswritten = write(outputfile,buffer,bytesRead);

            }

        }



        // Mid untouched
        if(startindex<endindex)
        {
            ssize_t bytestoread;
            ssize_t byteswritten;
            ssize_t bytesRead;

            lseek(inputfile,startindex,SEEK_SET);
            off_t middlepartsize = endindex - startindex;

            while(middlepartsize > 0)
            {
                if(middlepartsize >= BUFFER_SIZE)
                {
                    bytestoread = BUFFER_SIZE;
                }
                else
                {
                    bytestoread = middlepartsize;
                }

                middlepartsize = middlepartsize - bytestoread;

                bytesRead = read(inputfile,buffer,bytestoread);

                byteswritten = write(outputfile,buffer,bytesRead);

            }
        }

        //Reverse Ending

        if(endindex<filesize)
        {
            ssize_t bytestoread;
            ssize_t byteswritten;
            ssize_t bytesRead;
            off_t endpartsize = filesize - endindex;
            lseek(inputfile, endindex , SEEK_SET);

            while(endpartsize > 0)
            {
                if(endpartsize >= BUFFER_SIZE)
                {
                    bytestoread = BUFFER_SIZE;
                }
                else
                {
                    bytestoread = endpartsize;
                }
            
            endpartsize = endpartsize - bytestoread;
            bytesRead = read(inputfile, buffer, bytestoread); 
            reverseBuffer(buffer, bytesRead);
            byteswritten = write(outputfile,buffer,bytesRead);
            }
        }
    }

    cout<<"File Processed Successfully \n";

    close(inputfile);
    close(outputfile);



}

