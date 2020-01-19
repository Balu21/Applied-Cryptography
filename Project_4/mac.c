//#-pthread -m32

//Comiplation command: gcc -pthread -m32 mac.c -o output
//Run command: ./output filepath key
//Key is an integer value


/*------------------------------------------------------------
Submitted by:
Balavenkat Gottimukkala
Sreevashini Ravichandran
*/------------------------------------------------------------


#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "md5.h" 

int key; // symmetric key
int buf, n, infile, outfile;

MD5_CTX mdContext;  // needed to compute MD5

encrypt(char *name)
{ 
  struct stat st;
  int size,i,j;
  int *temp, result;   
  int rollingkey;    

  infile = open (name, O_RDONLY);
  if (infile<0) { printf("input file %s open error\n", name); exit(0); }
  
  outfile = open ("output-enc.txt", O_RDWR|O_CREAT|O_TRUNC, 0700);
  if (outfile<0) { printf("Cannot access file: output\n"); exit(0); }
  
  write(outfile,&key,4); 
  
  // do the encryption, buf contains plaintext, and rollingkey contains key
  buf = 0;
  rollingkey = key;  
  while ((n = read(infile, &buf, 4)) > 0 ) {
        // buf = buf ^ rollingkey; //XOR with key, and put ciphertext in buf
   MD5Init(&mdContext);  // compute MD5 of rollingkey
   MD5Update(&mdContext, &rollingkey, 4);
   MD5Final(&mdContext);
   temp = (int *) &mdContext.digest[12]; 
   result = *temp; // result is 32 bits of MD5 of buf
   
   rollingkey = rollingkey ^ result; // new key
   write(outfile, &buf, 4);  // write ciphertext
   buf = 0; // rinse and repeat
  };
  close(infile); close(outfile);
  return(size);
};


calculateMD5(char* filename)
{
	unsigned char c[16];
	int i, result, * temp;
	int bytes = 10;
	long filesize;

	FILE* efile = fopen(filename, "rb");
	if (efile == 0)
	{
		perror(filename);
		return 0;
	}
	fseek(efile, 0, SEEK_END);
	filesize = ftell(efile);
	rewind(efile);

	char* buf = (char*)malloc(sizeof(char) * filesize + 4);

	MD5Init(&mdContext);
	
	//Adds key at the beginning of the buffer.
	
	buf[0] = (key >> 24) & 0xFF;
	buf[1] = (key >> 16) & 0xFF;
	buf[2] = (key >> 8) & 0xFF;
	buf[3] = key & 0xFF;
	
	//Appends the encrypted file to the key.
	
	bytes = fread(buf+4, 1, filesize, efile);
	//Total bytes = 1028
	
	while (bytes != 0)
	{
		MD5Update(&mdContext, buf, bytes);
		MD5Final(&mdContext);
		temp = (int*)& mdContext.digest[12];
		result = *temp;
		printf("The hash for given input file is is %x\n", result);
		break;
	}
	fclose(efile);
}

int main(int argc, char* argv[])
{
	char *filename = argv[1];
	
	key = atoi(argv[2]);

	encrypt(filename);
	
	calculateMD5("output-enc.txt");
	return 0;
}
