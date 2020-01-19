#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "md5.h" 

// input : ./prog filename

char pass[5]; // 4 character password
int *pass_pointer, *temp;
int n, result, *temp;
MD5_CTX mdContext;  // needed to compute MD5




int hex2int(char ch)
{
    if (ch >= '0' && ch <= '9')
        return ch - '0';
    if (ch >= 'A' && ch <= 'F')
        return ch - 'A' + 10;
    if (ch >= 'a' && ch <= 'f')
        return ch - 'a' + 10;
    return -1;
}


check_pw(char * pass)
{
	int i = 0;
	for (i=0;i<4;i++) { 
	   if (!(((pass[i] >= 'a') && (pass [i] <= 'z'))
			 || ((pass[i] >= 'A') && (pass [i] <= 'Z'))
			 || ((pass[i] >= '0') && (pass [i] <= '9')))) {
			       printf("Password not as per specifications\n");
			       exit(0);
	   };
	};
};

void reduction(FILE *f) {
	int i = 0, j=0;
	char res[9];
	char p1[5];
	char p2[5];
	
	//printf("pass = %s\n", pwd);
	for(i=0; i<4; i++)
		p1[i] = pass[i];
		p2[i] = pass[i];
	p1[4] = '\0';
	p2[4] = '\0';
	fprintf(f, "%s",p1);
	for(i=0; i<10; i++) {
		pass_pointer = (int *)pass;
		MD5Init(&mdContext);
		MD5Update(&mdContext, pass_pointer, 4);
		MD5Final(&mdContext);
		temp = (int *) &mdContext.digest[12]; 
		//result = *temp;
		
		sprintf(res, "%x", *temp);
		int val[4];
		val[0] = hex2int(res[0]) + hex2int(res[1]) + hex2int(res[2]) + hex2int(res[3]);
		val[1] = hex2int(res[2]) + hex2int(res[3]) + hex2int(res[4]) + hex2int(res[5]);
		val[2] = hex2int(res[4]) + hex2int(res[5]) + hex2int(res[6]) + hex2int(res[7]);
		val[3] = hex2int(res[0]) + hex2int(res[1]) + hex2int(res[6]) + hex2int(res[7]);
		
		for(j=0; j<4; j++) {
			if(val[j] >=60)
				pass[j] = 0;
			else if(val[j] < 10)
				pass[j] = '0' + val[j];
			else if(val[j] >= 10 && val[j] < 36)
				pass[j] = 'a' + val[j] - 10;
			else if(val[j] >= 36 && val[j] < 60)
				pass[j] = 'A' + val[j] - 36;	
		}
		pass[4] = '\0';
		res[8] = '\0';
		fprintf(f, ",%s",pass);
	}
	//printf("%s\t%s\n", pwd, pwd);
	fprintf(f, "\n");
		
}


main(int argc, char *argv[])
{
	//pass_pointer = (int *) pass; 
	//*pass_pointer = 0; 
	
	//printf("Enter a 4 character, alphanumeric password: "); fflush(0);
	//n = read(0, pass_pointer, 4);
	
	FILE *fp = fopen("rainbow.txt", "w");
	
	char out[9] = "14928501";
	char res[9];
	 
	long int i = 0;
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;
	int output = 0;
	int j = 0;
	char c1,c2,c3;
	for(a=10;a<36;a++) {
		//printf("a = %d", a);
		if(a<10)
			pass[0]= a+48;
		else if(a>=10 && a<36)
			pass[0] = a + 55;
		else if(a>=36 && a<62)
			pass[0] = a + 61;
		c1 = pass[0];
		for(b=10; b<36; b++) {
			if(b<10)
				pass[1] = b+48;
			else if(b>=10 && b<36)
				pass[1] = b + 55;
			else if(b>=36 && b<62)
				pass[1] = b + 61;
			pass[0] = c1;
			c2 = pass[1];
			for(c=10; c<36; c++) {
				if(c<10)
					pass[2] = c+48;
				else if(c>=10 && c<36)
					pass[2] = c + 55;
				else if(c>=36 && c<62)
					pass[2] = c + 61;
				pass[0] = c1;
				pass[1] = c2;
				c3 = pass[2];
				
				for(d=10; d<36; d++) {
					if(d<10)
						pass[3] = d+48;
					else if(d>=10 && d<36)
						pass[3] = d + 55;
					else if(d>=36 && d<62)
						pass[3] = d + 61;
					pass[0] = c1;
					pass[1] = c2;
					pass[2] = c3;
					
					check_pw(pass); 
					pass_pointer = (int *) pass;
					
					
					
					//reduction(fp);
					
					
					
					
					//int i = 0, j=0;
					//char res[9];
					char p1[5];
					char p2[5];
					
					//printf("pass = %s\n", pwd);
					for(i=0; i<4; i++)
						p1[i] = pass[i];
						p2[i] = pass[i];
					p1[4] = '\0';
					p2[4] = '\0';
					fprintf(fp, "%s",p1);
					for(i=0; i<10; i++) {
						pass_pointer = (int *)pass;
						MD5Init(&mdContext);
						MD5Update(&mdContext, pass_pointer, 4);
						MD5Final(&mdContext);
						temp = (int *) &mdContext.digest[12]; 
						//result = *temp;
						
						sprintf(res, "%x", *temp);
						int val[4];
						val[0] = hex2int(res[0]) + hex2int(res[1]) + hex2int(res[2]) + hex2int(res[3]);
						val[1] = hex2int(res[2]) + hex2int(res[3]) + hex2int(res[4]) + hex2int(res[5]);
						val[2] = hex2int(res[4]) + hex2int(res[5]) + hex2int(res[6]) + hex2int(res[7]);
						val[3] = hex2int(res[0]) + hex2int(res[1]) + hex2int(res[6]) + hex2int(res[7]);
						
						for(j=0; j<4; j++) {
							if(val[j] >=60)
								pass[j] = 0;
							else if(val[j] < 10)
								pass[j] = '0' + val[j];
							else if(val[j] >= 10 && val[j] < 36)
								pass[j] = 'a' + val[j] - 10;
							else if(val[j] >= 36 && val[j] < 60)
								pass[j] = 'A' + val[j] - 36;	
						}
						pass[4] = '\0';
						res[8] = '\0';
						fprintf(fp, ",%s,%s",res,pass);
					}
					//printf("%s\t%s\n", pwd, pwd);
					fprintf(fp, "\n");
					
					
					
					
					/*
					MD5Init(&mdContext);
					MD5Update(&mdContext, pass, 4);
					MD5Final(&mdContext);
					temp = (int *) &mdContext.digest[12]; 
					//result = *temp;
					
					sprintf(res, "%x", *temp);
					if(a == 0 && b==0)
						puts(res);
					//int j = 0;
					//int output = 0;
					
					for(j=0;j<8;j++)
					{
						if(res[j] == out[j])
							output++;
					}
					
					//output = strcmp(out, res);
					if(output == 8) {
						printf("%s\n",pass);
						//exit(0);
					}
					output = 0;	
					*/
				}
				
			}
			
		}
		//printf("%s\n", pass);
		
	}

	
	
	//printf("%x\n", result); 

 	fclose(fp);
};

