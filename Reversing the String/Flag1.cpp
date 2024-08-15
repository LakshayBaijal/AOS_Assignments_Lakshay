#include<bits/stdc++.h>
using namespace std;

int main(int argc , char* argv[])
{
  int startindex = atoi(argv[1]);
  int endindex = atoi(argv[2]);
  int i, filesize;
  char ch;
  
  FILE *inputfile;
  inputfile = fopen("Assignmenttextfile.txt","r");
  
  FILE *outputfile;
  outputfile = fopen("Output_File.txt","w");

  filesize = ftell(inputfile);

//First Part changed
  for( i = startindex - 1 ; i>=0;i--)
  {
    fseek(inputfile,i,SEEK_SET);
     ch = fgetc(inputfile);
     fputc(ch, outputfile);
  }
// Middle Part unchanged
  for( i = startindex; i<endindex; i++)
  {
    fseek(inputfile, i , SEEK_SET);
    ch = fgetc(inputfile);
    fputc(ch, outputfile);
  }
  
// Last Part changed
  fseek(inputfile, 0, SEEK_END);
  for( i = filesize - 1; i >= endindex; i--)
  {
    fseek(inputfile,i,SEEK_SET);
    ch = fgetc(inputfile);
    fputc(ch, outputfile);
  
  }
  fclose(inputfile);
  fclose(outputfile);
  return 0;

}
