#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#include "md5.h" 

// input : ./prog filename

char pass[5]; // 4 character password
int *pass_pointer, *temp;
int n, result, *temp;
MD5_CTX mdContext;  // needed to compute MD5

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

char* reduce( char* hashed )
{
   char sub[1000];
   int position = 1, length = 4, c = 0;

   while (c < length) {
      sub[c] = hashed[position+c-1];
      c++;
   }
   sub[c] = '\0';

   return sub;
}

char resulthash[9];
char* MD5(char* red)
{
	int resulthashsize = 10;
	MD5Init(&mdContext);
	//MD5Update(&mdContext, pass, 4);
	MD5Update(&mdContext, red, 4);
	MD5Final(&mdContext);
	temp = (int *) &mdContext.digest[12]; 
	result = *temp;
	sprintf(resulthash, "%x", result);
	return resulthash;
}


rainbowtable()
{
	//char out[9] = "14928501";
	char* res;
	char* red;
	 
	long int i = 0;
		
	FILE* fptr;
	fptr = fopen("text.txt", "w");
	if(fptr == NULL)
	{
		printf("\n Error in opening file\n");
		exit(1);
	}

					char* plains_to_hash[] = {"abcd", "love", "a1b2", "MoVe","move"};
					for(int j=0;j<5;j++)
					{
						char *plain;
						plain = plains_to_hash[j];
						fprintf(fptr, "%s,", plain);
						red = plain;
						for(int i=0;i<10;i++)
						{
							//check_pw(pass); 
							//pass_pointer = (int *) pass;
							
							res = MD5(red);
							red = reduce(res);
						}
						fprintf(fptr, "%s\n", res);
						/*
						for(int j=0;j<8;j++)
						{
							if(res[j] == out[j])
								output++;
						}
						
						//output = strcmp(out, res);
						if(output == 8) {
							printf("%s\n",pass);
							//exit(0);
						}
						output = 0;	*/	
					}
fclose(fptr);	 
}


char* getfield(char* line, int num){
    char* tok;
    for (tok = strtok(line, ",");
            tok && *tok;
            tok = strtok(NULL, ",\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

typedef struct Pass_and_Hash
{
    char* frstpss;
    char* lsthsh;
} Pass_and_Hash_t;

Pass_and_Hash_t read_final_hashes(char * check_hash)
{
    int found = 0;
    FILE * myFile = fopen("text.txt", "r");
    char line[512];
    char* placer1 =	NULL;
    char* placer2= NULL;

    char check_hash_Arr[20];
    char new_placer2_Arr[20];
    while (fgets(line, 512, myFile)){
        // NOTE strtok clobbers tmp
        char* tmp1 = _strdup(line);
        placer1 = getfield(tmp1, 1);
       // free(tmp1);
        char* tmp2 = _strdup(line);
        placer2 = getfield(tmp2, 2);
        //free(tmp2);

        strcpy(new_placer2_Arr, placer2);
        while(strlen(new_placer2_Arr)!=8){
            new_placer2_Arr[strlen(new_placer2_Arr)-1] = 0; // remove last empty char to allow equality test
        }
        //printf("%lu\n", strlen(new_placer2_Arr));

        strcpy(check_hash_Arr, check_hash);
        while(strlen(check_hash_Arr)!=8){
            check_hash_Arr[strlen(check_hash_Arr)-1] = 0; // remove last empty char to allow equality test
        }
        //printf("%lu\n", strlen(check_hash_Arr));

        int r;
        r = strcmp(new_placer2_Arr,check_hash_Arr);
        //printf("R %d\n", r);

        if (strcmp(new_placer2_Arr,check_hash_Arr) == 0){
            //printf("%s\n", new_placer2_Arr);
            found = 1;
            break;
        }

    }
    fclose(myFile);
    if(found == 1){
        //printf("%d\n", found);
        //printf("First plain is %s, Match is : %s\n", placer1, check_hash);
        Pass_and_Hash_t Pass_and_Hash;
        Pass_and_Hash.frstpss = placer1;
        Pass_and_Hash.lsthsh = check_hash;
        //printf("%s %lu\n", placer1, strlen(placer1));
        //printf("%s %lu\n", check_hash, strlen(check_hash));
        return Pass_and_Hash;
    }
    else{
        //printf("%s\n", "No Match");
        Pass_and_Hash_t Pass_and_Hash;
        Pass_and_Hash.frstpss = "No Match";
        Pass_and_Hash.lsthsh = "No Match";
        return Pass_and_Hash;
    }
}

char * online_crack( char * attack_hash )
{
    int found = 0;
    int i;
    int j;
    int k;
    char * H= NULL;
    char * R= NULL;
    char * found_first_plain= NULL;
    char * found_end_hash= NULL;
    char * new_place= NULL;
    int attempts = 50;
    H = attack_hash;
    printf("Attack hash: %s, len %lu\n", H, strlen(H));
   
    char check_red_Arr[20];
    char check_pass_Arr[20];
    char check_hash_Arr[20];

    for (i=0; i<attempts; i++)
	{
        //char * check = read_final_hashes(H);
        Pass_and_Hash_t res;
        res = read_final_hashes(H);
        char * check_pass;
        char * check_hash;
        check_pass = res.frstpss;
        check_hash = res.lsthsh;
        //printf("%s\n", check_hash);
        //printf("%s\n", check_hash);

        if (strcmp(check_hash,"No Match") != 0){
            found = 1;
            found_first_plain = check_pass;
            //printf("%s\n", "F");
            found_end_hash = check_hash;
            break;
        }
        R = reduce(H);
        //printf("red %s, len %lu\n", R, strlen(R));
        strcpy(check_red_Arr, R);
        //printf("red %s, len %lu\n", check_red_Arr, strlen(check_red_Arr));
        H = MD5(check_red_Arr);
        printf("");
    }
  
    if( found == 1)
	{
		int retu=0;
        printf("Attack Hash: %s (%lu len), First plaintext: %s (%lu len), Last hash in link: %s (%lu len)\n", attack_hash, strlen(attack_hash), found_first_plain, strlen(found_first_plain), found_end_hash, strlen(found_end_hash));
        char * next_hash;
        char * next_reduce;
        next_reduce = found_first_plain;
        found_end_hash[strlen(found_end_hash)-1] = 0;
       
		
        while(retu != 1)
		{
            next_hash = MD5(next_reduce);
            //printf("Next Redu %s, %lu\n", next_reduce, strlen(next_reduce));
            printf("Next Hash %s, %lu, Attack Hash %s, %lu\n", next_hash, strlen(next_hash), attack_hash, strlen(attack_hash));
            retu = strcmp(next_hash, attack_hash);

            if (retu ==1){
				printf("The original password/plaintext is: %s\n", found_first_plain);
                break;
            }
            next_reduce = reduce(next_hash);
        }  
    }
    else{
        printf("No match found after %d attempts\n", attempts);
    }

    return 0;
}

int main(){

    //build rainbow_table
	char* inputhash = malloc(sizeof(char) * 20);
	scanf("%20s", inputhash);
    rainbowtable();
    //crack hash
    printf("enter the hash to be decrypted: \t");
    if (strlen(inputhash)!=8)
	{
        printf("%s\n", "Hash must be of length 8!");
        exit(1);
    }
    online_crack(inputhash);


    //for (int i=1; i< argc; i++) {
    //    //printf("\nhash_to_crack_%d: %s", i, argv[i]);
    //    printf("\n");
    //    online_crack(argv[i]);
    //    }
    //printf("\n");

    return 0;
}

