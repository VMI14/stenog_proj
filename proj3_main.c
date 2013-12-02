/*
 * This program extracts a hidden file from a provided ppm file.
 *
 * Author: Tommy Bylund and Mike Mayhew
 * Date: 12/1/2013
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Define some constants for the available operations
#define READ      1
#define WRITE     2
#define INVERSE   3

#define EXIT      8

// function prototypes for the PPM I/O functions
void readPPMImage( char name[], unsigned char image[][]);
void writePPMImage( char name[], unsigned char image[][]);

// function prototypes for the image processing functions
// YOU NEED TO SUPPLY IMPLEMENTATIONS OF ALL OF THESE! See below.
int getMenuSelection(void);
void inverse( unsigned char image[][]);


// main -- print menu, get user's selection, and process it.
int main(void)
{
   unsigned char image[][];  // array to hold image data
   int choice;                      	// menu choice from user
   char filename[80];               	// filename entered by user
   
   do {
      // print menu and get user's selection
      choice = getMenuSelection();
      
      // returned value should be between READ and EXIT
      assert( choice >= READ && choice <= EXIT );
      
      // process the selection
      switch (choice) {
         case READ:     // get filename from the user
                        printf("Enter the filename to read: ");
                        scanf("%79s", filename);
                        readPPMImage( filename, image );
                        break;
                        
         case WRITE:    // get filename from the user
                        printf("Enter the filename to write: ");
                        scanf("%79s", filename);
                        writePPMImage( filename, image );
                        break;
                        
         case INVERSE:  inverse( image );
                        break;
                
         default:       // do nothing
                        break;
      }
   } while ( choice != EXIT );      // repeat until they exit
   
   return 0;
}
/*
 * readPPMImage -- 
 */
void readPPMImage( char name[], unsigned char image[][])
 {
   FILE *fp;
   int i, j;
   int width, height, depth;

   // open the file
   fp = fopen( name, "r" );
   if ( fp == NULL ) {
      fprintf(stderr, "ERROR -- Cannot open input file %s\n", name);
      exit(1);
   }

   // read PPM header stuff
   if ( fscanf(fp, "P6 %d%d%d\n", &width, &height, &depth) != 3 ) {
      fprintf(stderr, "ERROR -- Cannot read input file %s -- invalid .ppm file\n",
                 name);
      exit(1); //read the PPM header info
   }

   for (i = 0; i < height; i++) {
      for (j = 0; j < width; j++) {
         if ( feof( fp ) ) {
            fprintf(stderr, "ERROR -- Invalid input file %s.\n", name);
            exit(1);
         }
         else {
            image[i][j][0] = getc(fp); //read the pixel data /red
	    image[i][j][1] = getc(fp); //read the pixel data /green
	    image[i][j][1] = getc(fp); //read the pixel data /blue
         }
      }
   }
   // close file
   fclose( fp );
}
/*
 * writePPMImage -- 
 */
void writePPMImage( char name[], unsigned char image[][])
{
   int i, j;
   int width, height, depth;
   FILE *fp;

   // open the file
   fp = fopen( name, "w" );
   if( fp == NULL ) {
      fprintf(stderr, "ERROR -- Cannot open output file %s\n", name);
      exit(1);
   }

   // write PPM header
   fprintf(fp, "P6\nheight width\ndepth\n", height, width, depth);

   // write image data
   for ( i = 0; i < height; i++ ) {
      for ( j = 0; j < width; j++ ) {
         putc( image[i][j], fp );
      }
   }

   // close the file
   fclose( fp );
}
        
// Stub functions so that the program can be compiled. Be sure to include the real implementations of all of these functions.

/*
 * Print the menu, get the menu choice from the user, and return it.
 * Input: none
 * Returns menu selection from user (a number from 1 to 8).
 */
int getMenuSelection(void)
{
   int getMenuOption;
   
   printf("Welcome to image Stenographer\n");
   printf("Enter 1 to read the program.\n");
   printf("Choices:\n 3. Inverse\n");
   printf("Enter 2 to write the program.\n");
   printf("Enter 8 to exit.\n");
     
     scanf("%d", &getMenuOption);
 
   return getMenuOption;
}
/*
 * Take the inverse of an image.
 * Input: image = array holding the image data, i and j input variables, i represents the row of the selected pixel and j represents the column. 
 
 * Returns nothing, but modifies the image array
 */



void inverse( unsigned char image[256][256] )

{
int i, j;
	
	for(i=0; i<256; i++){
	   for (j=0; j<256; j++) {
   	      image[i][j] = 255-image[i][j];
   	   }
   	}
}

