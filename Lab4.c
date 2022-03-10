/*
Steven Bryan
CIS 2107 Spring 2022
TUID: 915789331
 */


//Include all header files
//need time.h for srand()
//Need string.h for the string functions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <limits.h>
//this is used to get the structure for bitmap in alignement
#pragma pack(push,1)


//Struct to hold the pixels
typedef struct Pix
{
	char R;
	char  G;
	char  B;
	unsigned int BW;
}
Pix;


//struct to hold the Bitmap information
typedef struct BitMap
{   
    short int Signature;
    unsigned int Reserved1;
    unsigned int Reserved2;
    unsigned int DataOffSet;

    unsigned int Size;
    unsigned int Width;
    unsigned int Height;
    unsigned int Planes;
    short int BitsPerPixel;
    unsigned int Compression;
    unsigned int SizeImage;
    unsigned int XPixelsPreMeter;
    unsigned int YPixelsPreMeter;
    unsigned int ColorsUsed;
    unsigned int ColorsImportant;
    struct Pix  *pixels;

}BitMap;
//for alignment of the struct information
#pragma pack(pop)





//Prototypes for reading binary, writing binary, emcryption, finding length of a file, decryption, and to show a file
char * read_file(char file_name[]);
int file_write(char *input, char file_name[]);
void *encrypt_file(char file_name[], char key_name[], char encrypt_name[], int length);
unsigned char *make_rand_key(int length);
void *encrypt(char * array1,unsigned char *array,unsigned char  return_array[],int length);
int buffer_length(char file_name[]);
char * show_contents(char file_name[]);
void *decrypt(char encrypted_name[], char new_key_name[], char decrypt_name[],int length2);



int main(){

	unsigned long int i=0;
	unsigned long int S=0;

//Declaring all chars for the file names
	char fname[100];
	char new_file [100];
	char key_name[100];
	char key_name2[100];
	char decrypt_name[100];
	char encrypted_name[100];
	char txt_file[100];
	char encode_image[100];
	char new_image[100];
	unsigned char message[500];
	unsigned char message1[500];
	char pic_file[100];

//declaring variables for variables used in the program
	int length1;
	int decrypt_length=0;
	int choice=0;
	int x=0;
	int msg_size_2=0;	

//while loop contains a menu to encrypt/ decrypt/ read/encode bitmap/decode bitmap and exit
while(1){

//Clear the screen
	system("clear");

//loop to make space
	for(int g=0;g<10;g++)
		printf("\n");
//loop to make space
	for(int f=0;f<15;f++)
		printf("* ");
//menu items below
	printf("\nWhat would you like to do?\n ");
	printf("Encrypt a file enter 1.\n ");
	printf("Decrypt a file enter 2.\n ");
	printf("Encode a bitmap enter 3.\n ");
	printf("Decode a bitmap enter 4.\n");

	printf(" Read a txt file enter 5.\n ");
	printf("Exit press 6.\n");
	for(int f=0;f<15;f++)
		printf("* ");
	printf("\nWhat is your choice: ");
	scanf("%d",&choice);


switch (choice){

//Case 1 is used for encryption 
	case 1:
		
	printf("What is the name of the file you would like to encrypt (if its a txt file, add .txt at the end): ");
		scanf("%s",fname);



//Make an integer the length of the file used in the loop to get contents
		length1= buffer_length(fname);


		printf("What would you like to call the encrypted file: ");
		scanf("%s",new_file);

		printf("What would you like to call the key file: ");
		scanf("%s", key_name);
//Calls encryption funtion
		encrypt_file(fname,key_name,new_file,length1);

		printf("\nYour encrypted file is saved as: %s", new_file);
		break;

//Case 2 is used for decryption
	case 2:
		printf("What is the name of the file you would like to decrypt:");
		scanf("%s",encrypted_name);



		printf("What is the name of the key file: ");

		scanf("%s",key_name2);
		length1= buffer_length(key_name2);

		printf("What would you like to call the decrypted file: ");
		scanf("%s", decrypt_name);
//Calls decryption function
		decrypt(encrypted_name,key_name2,decrypt_name,length1);

//calls show_contents function which prints file information to the screen
		show_contents(decrypt_name);
		printf("\n The above text is the decrypted file.\n");
		printf("\n ");	
		 for(int f=0;f<15;f++)
                printf("* ");

		printf("\nTo go back to the main menu press 1\n To exit the program press 2.");
		scanf("%d",&x);
		 for(int f=0;f<15;f++)
                printf("* ");

//if the user enters 2 then the program exists with exit(0)
		if(x==2){
			exit(0);
			}			
//if not 2 then goes back to main menu
		else{
			break;
			}		


	case 5:
		printf("What file would you like to read? ");
		scanf("%s", fname);
		show_contents(fname);
		printf("\n");
	 for(int f=0;f<15;f++)
                printf("* ");

		printf("\nTo go back to the main menu press 1\n To exit the program press 2: ");
		scanf("%d",&x);
	
	 for(int f=0;f<15;f++)
                printf("* ");

//if the user enters 2 then the program exists
	if(x==2){
		exit(0);
		}
//if not 2 then breaks back to the main menu 
	else{
		break;
		}



	case 6:
	printf("\nGood Bye!\n");	
	exit(0);
		break;


//CASES ARE OUT OF ORDER DUE TO THE COMPLEXITY OF SHIFTING CASES AROUND AND CREATING ERRORS
	
	

//Also, some of the file reading is within the case statment, due to first creating a program to encode and decode bitmaps
//and then transferring that program and integrating it into this one,  to make sure that it works, left most of the transferred
//program the same to reduce possible errors that could occur

	case 3:;

//Make instances of the needed structs
	struct BitMap source_info;
	struct Pix source_pix;
	char file_message[2000];
	//char pointer to get the file text
	char *file_message1;


//get the users information below
	printf("Enter the name of the image you wish to Encode (.bmp file): ");
	scanf("%s", encode_image);
	
	printf("Enter the name you would like the encoded image saved as (.bmp file): ");
	scanf("%s", new_image);

	printf("Enter .txt file you would like to encode: ");
 
//the scanf below allows for spaces
	scanf (" %[^\n]%*c", message);




//create space for file_message1
	file_message1=(char *)malloc(2000*sizeof(char));
	file_message1=read_file(message);
	
//get the length of the message in the file
int msg_size_2=buffer_length(message);

//make a new message that is equal to msg_size_2 because msg_size_2 will get turned into 0
	int message_length1=msg_size_2;
	 FILE *Dfp2;
         FILE*fp2;

	int msg_size_3=msg_size_2;


	//This file pointer is to get the origonal file
	fp2=fopen(encode_image,"rb");
	if (fp2==NULL)
    	{


        fputs("File error:  Could not open file.  Goodbye!\n", stderr);
        exit(1);
    	} //this file pointer is for a temporary file that saves the buffer
        Dfp2=fopen(new_image,"wb");

	fseek(fp2, 0, SEEK_END);
//get the length of the file
	int len = ftell(fp2);
//put the file pointer back at the begnning
	rewind(fp2);

        fread(&source_info, sizeof(source_info),1,fp2);
//S will be the width times height of the pixels to get the total size
        S=source_info.Width*source_info.Height;
//making space for the struct pixels within the BITmap struct
        source_info.pixels =  (struct Pix *) malloc(sizeof(struct Pix)*S);
//buffer will hold the contents of the pixels which can then be manipulated 
	unsigned char *buffer=malloc(sizeof(char)*S);

//Read the pixel info into a buffer
 	for(i=1;i<=S;i++)
    	{   
        //read pixel from the source file
        fread(&buffer[i-1],sizeof(struct Pix),1,fp2);
    }

//Write message length in first 32 chars of bmp 
    for(int bmp_cnt=0; bmp_cnt<32; bmp_cnt++){ 
      
  //Flip LSB based on a bit in message size 
        if(msg_size_2 &INT_MIN)   // msg_size_2 is message size 
            buffer[bmp_cnt] |= 1;  //Flip LSB to 1 
        else                       // m is a Bitmap struct and data file data 
            buffer[bmp_cnt] &= 254;//Flip LSB to 0 
        msg_size_2 <<= 1;           
    
}
//Start at 33 because that is the next char after the size information
	int count1=33;

// msg_size_2 has gotten updated to 0, so cant use it for the loop

	for(int start=0; start<=message_length1; start++){

	for(int end=0; end<8;end++){
//Flip LSB based on a bit in message 
        if(file_message1[start] &SCHAR_MIN)   // if file_message1 & a char equal to:1000 000 is true
            buffer[end+count1] |= 1;  //Flip LSB to 1
        else                       
            buffer[end+count1] &= 254;//Flip LSB to 0
        file_message1[start] <<= 1;//shift to the next bit in the message we are encoding


}

	count1=count1+9;//This accounts for each loop so it is the total number of chars of the buffer


}


//Write the buffer into a new file with source info above it
 	fwrite(&source_info, sizeof(BitMap),1,Dfp2);
	for(i=1;i<=S;i++)
    	{
        	fwrite(&buffer[i-1],sizeof(struct Pix),1,Dfp2);
    	}

   
        fclose(Dfp2);
	fclose(fp2);

//print all of the important information of the Bitmap
	printf("\nThe size of the file is: %d\n",len);
	printf("The width of the file is: %d\n",source_info.Width);
	printf("The height of the file is: %d\n",source_info.Height);
	printf("Encoded message legnth is: %d\n", message_length1);




	printf("\nEncoding Successful!\n");
	//free the memory used for the buffer and the file_message
	free(buffer);
	free(file_message1);
	printf("To go back to the main menu enter 1, to exit program enter 2: ");
	//create a variable that will be used exit or go to the main menu
	int choice4=0;
	scanf("%d",&choice4);
	if(choice4==1){


	break;
	}
//exit if any choice that isnt 1
	else{
	exit(0);
	}





	case 4:;
 
//create the structs needed to get the information from the bitmap
	struct BitMap source_info2;
	struct Pix source_pix2;
//create file pointers o open the bitmap file, then an array for the name of the file
	FILE *fp;
	FILE *Dfp;
	char decoded[100];

 

	printf("Enter the name of the file you wish to decode( .bmp file):" );
	scanf("%s",decoded);
//if there is no file, exit
	fp=fopen(decoded,"rb");
 	if (fp==NULL)
 	{
        fputs("File error:  exiting program\n", stderr);
        exit(1);
	}





//read in the bitmap information
	fread(&source_info2, sizeof(source_info2),1,fp);

	int S2= source_info2.Width*source_info2.Height;
	unsigned char *buffer2=malloc(sizeof(char)*S2);
	for (int p=1;p<=S2;p++)
    	{
        //read pixel from the source file
        	fread(&buffer2[p-1],sizeof(struct Pix),1,fp);
       
    	}
//this part is to read the file and get the file length from the bitmap
	unsigned int message_length;
//only goes to 32 because the value is in the first 32 bits
	for(int j=0; j<32;j++){
	

	if(1 & buffer2[j]){
//OR the value at this bit of message_length with 1
		message_length|=1;
		}
	else{
//the 4 billion number is all 1's and the last bit 0, to make that bit zero
		message_length&=4294967294;
	}
	message_length<<=1;

	}


	int count2=33;
	int count3=0;
//this loop is to get the bits of the message from the bitmap
//shift operator was off by 1.  So to account i divide the message length by 1
	for (int start2=0; start2<(message_length/2); start2++){

	for(int end2=0;end2<8;end2++){
		if(1  & buffer2[count2+end2]){
		message1[start2] |= 1;
	}

	else {
	message1[start2] &=254;

	}
//shift the bits of the message by one
	message1[start2]<<=1;


	}
	count2=count2+9;
	}
//the message length is twice the actual value, so we divide by 2
	message_length=message_length/2;
//again the shift operator was off by 1, so divide the message by 2
	printf("The  message is: ");
	for(int b=0;b<message_length;b++){
		printf("%c",message1[b]/2);
	}

	printf("\n");

	printf("To go back to the main menu enter 1, to exit program enter 2: ");
	//below will get values to continue the program or exit
	int choice3=0;
	scanf("%d",&choice3);
	if(choice3==1){


	break;
	}

	else{
		exit(0);
	}


	default:
		printf("\nThat is not a valid choice\n");
		break;
		

		}

}
}


//Start of the functions


void *decrypt(char encrypted_name[], char new_key_name[], char decrypt_name[],int length2){
	printf("\n ");
	//get the variables ready
	int count=0;
	int length3=0;
	char d_array[10000];
	char *decrypted_array=d_array;
//call read_file and save results in encr_file or encrypted file
	char * encr_file=read_file(encrypted_name);

//call read file and save the key file
	char * keyed_name=read_file(new_key_name);
//printf("the length of length is %d",length2);

//this loop XOR to get the original file, but its too long, so will do another loop
	for(int p=0; p<=10000; p++){
	char temp=(encr_file[p]^keyed_name[p]);
	decrypted_array[p]= temp;
	}
	//get the length of the XOR file that now has a NULL terminator in it
	length3=buffer_length(decrypted_array);
//loop to copy the XOR file into the decrypted array pointed at
	for(int p=0; p<=length3-1; p++){
	char temp=(encr_file[p]^keyed_name[p]);
	decrypted_array[p]= temp;
	}


	printf("file has been decrypted.\n");
//Write the decrypted file into a document
	file_write(decrypted_array, decrypt_name);
//free malloc
	free(encr_file);

}



void *encrypt_file(char file_name[], char key_name[], char encrypt_name[],int length){

//get a pointer to an array that is from the file
	char * buffer=read_file(file_name);

//create an array for the encrypted information
	char encrypted_array[10000];

//create a pointer to an array that is the encrypted array
	char *return_array=encrypted_array;


	char *key=make_rand_key(length);
//Write the key to file
	file_write(key,key_name  );
//encrypt the original file with the key file
	encrypt(buffer,key,encrypted_array,length);	
//write the encrypted string to a file
	file_write(return_array, encrypt_name);
//free the buffer
	free(buffer);
	free(key);
}


//function to encrypt the data
void *encrypt(char *original,unsigned  char *key,unsigned  char return_array[], int length){
	
	int count2=0;
   //Loop to XOR the contents of the two arrays
 	for(int i=0;i<length;i++){
//make a temp value for XOR of arrays and then put that result into an array that gets returned
	int temp=(int)(original[i]^key[i]);
        return_array[i]= temp;
	count2++;
				}	

}



//function to get the length of a files characters
int buffer_length(char file_name[]){
	FILE* fp;
	int count	 = 0;
  
    
  
    // To store a character read from file
	char c;
  
  	
    // Open the file
	fp = fopen(file_name, "rb");
  
    // Check if file exists
	if (fp == NULL) {
      //  printf("Could not open file %s", file_name);
        return 0;
	free(fp);
    }

 
 
    // Extract characters from file
    // and store in character c
    for (c = getc(fp); c != EOF; c = getc(fp)){
  
        // Increment count for this character
        count = count + 1;
}  
    // Close the file
	fclose(fp);

   
//this is the length of the file contents  
    return count;
}



char * read_file(char file_name[]){
 
	int p=0;
//read a file function
        FILE *ptr;
        ptr = fopen(file_name,"rb");

       //check to see if the pointer is NULL
	if(ptr){
        fseek(ptr, 0,SEEK_END); //points to the end of file
        long size = ftell(ptr);

        rewind(ptr);
        char *buffer= (char*) malloc(sizeof(char)*(size+1));
        fread(buffer, size+1,1,ptr);
       //Read the buffer
        fread(&buffer,sizeof(char),size+1,ptr);
	//close the pointer
        fclose(ptr);
        //return the buffer which is a pointer to an array
        return buffer;
	//free the memory used for the buffer
	free(buffer);
	}
	//if the FILE pointer is NULL
	else{
	printf("\nThis file does not exist!\n");
	 for(int f=0;f<15;f++)
                printf("* ");

	printf("\nWould you like to go back to the main menu or exit?\n");
	printf("\nEnter 1 for main menu\n");
	printf("\nEnter 2 to exit program: ");
	scanf("%d",&p);
	 for(int f=0;f<15;f++)
                printf("* ");

	switch (p){
	
	
	case 1:
	printf("\nreturning the main menu\n");
	break;
	case 2:

	printf("\nThank you, have a great day!\n");
	exit(0);
	break;
	
	default:
	printf("\nThats not a valid choice, goodbye!\n");
	exit(0);
	break;
}

}
free(ptr);

}
	
int file_write(char *input, char file_name[]){
//create a pointer to a FILE
	FILE *fpt;  
//open the file in read binary mode
	fpt=fopen(file_name,"wb");
	
	fseek(fpt, 0,SEEK_END); //points to the end of file
        
	long size1 = ftell(fpt);

        rewind(fpt);
       // char *buffer2= (char*) malloc(sizeof(char)*(size1+1));

	//write the data
	fwrite(input,sizeof(input),10000,fpt);
//close the pointer to the data
	fclose(fpt);
	return 0;
}




unsigned char *make_rand_key(int length){
	//create a array of chars
	char *charArray =(char*) malloc(length*sizeof(char));
	//there is no char array return NULL
	if(!charArray){
	return NULL;
			}
        //create the values for the random genorator range to use             
	int upper= 255;
	int lower=0;
	int count=0;    
//srand is used to get a random seed based on the time
	srand(time(0));
    //this loop adds the random number or "char" to the array which will be used for the key
    for (int i = 0; i < length+1; ++i) {
        
      charArray[i] = (char)((rand() % (upper - lower + 1)) + lower);
count++;
   }
   // return the array of random chars
   return charArray;
//free the memory of the char array
    free(charArray);
}


char * show_contents(char file_name[]){
 	//read a file function
        FILE *ptr;
        ptr = fopen(file_name,"rb");
       

        fseek(ptr, 0,SEEK_END); //points to the end of file
        long size = ftell(ptr);

        rewind(ptr);
       //create a buffer that will be used to get the contents of the file from 
	char *buffer1= (char*) malloc(sizeof(char)*(size+1));
        fread(buffer1, size+1,1,ptr);
        printf("%s",buffer1);  //tests, prints contents of file
       
//close the memory that was used for the pointer
        fclose(ptr);
        //return buffer, which will basically give back a pointer to the buffer
        return buffer1;
//free the memory that is being used for the buffer
	free(buffer1);
}



