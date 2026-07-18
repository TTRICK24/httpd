#include <stdio.h>
#include <string.h>

struct user {
	char name[64];
	char password[64];
};



int main(int argc, char *argv[]) 
{
	if (argc != 3) {
		printf("Usage: %s <name> <password>\n", argv[0]);
		return 1;
	}

	struct user x;

	strcpy(x.name, argv[1]);
	strcpy(x.password, argv[2]);

	FILE *f = fopen("user.dat", "wb");

	if (f == NULL) {
		printf("Cannot open file.\n");
		return 1;
	}

	fwrite(&x, sizeof(x), 1, f);

	fclose(f);

	printf("User saved.\n");

	return 0;

}
