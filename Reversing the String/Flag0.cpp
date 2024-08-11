#include<bits/stdc++.h>
using namespace std;

int main()
{
  int i,filesize;
  
  FILE *inputfile;
  inputfile = fopen("Assignmenttextfile.txt","r");
  
  FILE *outputfile;
  outputfile = fopen("Output_File.txt","w");

  fseek(inputfile,0,SEEK_END);
  filesize = ftell(inputfile);
  
  for(i=filesize-1;i>=0;i--)
  {
  fseek(inputfile, i, SEEK_SET);
  char ch = fgetc(inputfile);
  fputc(ch, outputfile);
  
  }
  
  fclose(inputfile);
  fclose(outputfile);
  return 0;
}
