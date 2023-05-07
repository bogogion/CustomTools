#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

typedef unsigned char u8_t;

/* default address is 10 */
u8_t max_size = 10;

/* extra seed from urandom for better randomness*/
u8_t rand_in_range(char seed)
{
	srand(time(NULL) * seed);
	u8_t rand_num = rand() % 126;
	
	/* check if num in range */
	while(rand_num < 33 || rand_num > 126)
	{ rand_num = rand() % 126; }
}

int main(int argc, char *argv[])
{
	printf("RUN WITH SUDO/PERMISSIONS\n");

	/* argument */
	if(argc == 3)
	{
		if(!strcmp(argv[1], "-l"))
		{
			max_size = atoi(argv[2]);
		}
	}

	/* open random gibberish */
	FILE *fp;
	fp = fopen("/dev/urandom","rb");

	/* create buffer */
	char *buf;
	buf = (char *)malloc(max_size);

	/* grab random gibberish */
	fgets(buf,max_size,fp);
	fclose(fp);

	for(u8_t i = 0; i < max_size; i++)
	{
		/* keep our buf in ascii readable */
		if(buf[i] < 33){buf[i]  = rand_in_range(buf[i]); }
		if(buf[i] > 126){buf[i] = rand_in_range(buf[i]); }
	}
	
	/* open hostname file */
	fp = fopen("/etc/hostname","w");
	if(fp < 0){ printf("Try using higher permissions.\n"); }

	/* close hostname file */
	fputs(buf,fp);
	fclose(fp);

	return 0;
}
