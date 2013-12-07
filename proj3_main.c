/*
* This program extracts a hidden file from a provided ppm file.
*
* Author: Tommy Bylund and Mike Mayhew
* Date: 12/1/2013
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// main -- print menu, get user's selection, and process it.
int main(int argc, char *argv[])
{
   char filename[80];         // filename entered by user
  
   FILE *fp_read;
   FILE *fp_write;
   int i, j;
   int width, height, depth;
   int b, size, data;
     
   //open the file STEP 1
   if( (argc < 3)){
     fprintf(stderr, "ERROR -- argc must be 3%s --invalid .ppm file\n", argv[1]);
     exit(1); //make sure that the user enters enough into the command line
   } 
   
   fp_read = fopen( argv[1], "r" );
   if ( fp_read == NULL ) {
      fprintf(stderr, "ERROR -- Cannot open input file %s\n", argv[1]);
      exit(1);
   }

   // open the file
   fp_write = fopen( argv[2], "w" ); //argv[1]
   if( fp_write == NULL ) {
      fprintf(stderr, "ERROR -- Cannot open output file %s\n", argv[2]);
      exit(1);
   }

   // read PPM header stuff STEP 2
   if ( fscanf(fp_read, "P6 %d%d%d\n", &width, &height, &depth) != 3 ) {
      fprintf(stderr, "ERROR -- Cannot read input file %s -- invalid .ppm file\n", argv[1]);
      exit(1); //read the PPM header info
   }

   //Check to see if file is valid. width & height > 0 and depth == 255
   if ( (width < 0) || (height < 0) || (depth != 255) ) {
      fprintf(stderr, "ERROR -- Cannot read input file %s -- unsupported .ppm file\n",
		argv[1]);
      exit(1);
   }
   
   //write the output file STEP 3 and 4
   
   // write image data
   
   //use get()C to read a byte from file ... b = c&1; extracts LSB... size = size(size<<1)
      
   for (i=0; i < 32; i++) 
   {      
     b = getc(fp_read)&1; //lsb
     size = (size<<1)|b; //add bit to size
   }
   
   
   printf("size of file %d \n", size); 
   for (i=0; i <size; i++)
   {

   data = 0;
   
     for( j= 0; j<8; j++)
     {
     b = getc(fp_read)&1; //lsb
     data = (data<<1)|b; 
     }

   putc(data, fp_write);

   }
       
   // close file
   fclose( fp_read );
   fclose( fp_write );
   
   return 0;
}
