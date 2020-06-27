#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<dirent.h>
#include<stdlib.h>
int main(){ 

time_t t;
struct tm *tmp;
time(&t);
char buf2[64];
tmp = localtime(&t);
printf("Folder 1 created on ");
if (strftime(buf2, 64, "time and date: %r, %a %b %d, %Y", tmp) == 0)

        printf("buffer length 64 is too small\n");

	else

	        printf("%s\n", buf2);

mkdir("./folder1",0777);
mkdir("./folder2",0777);
tmp = localtime(&t);
printf("Folder 2 created on ");
if (strftime(buf2, 64, "time and date: %r, %a %b %d, %Y", tmp) == 0)

        printf("buffer length 64 is too small\n");

	        else

	         printf("%s\n", buf2);
mkdir("./folder3",0777);
tmp = localtime(&t);
printf("Folder 3 created on ");
if (strftime(buf2, 64, "time and date: %r, %a %b %d, %Y", tmp) == 0)

        printf("buffer length 64 is too small\n");

	        else

		                printf("%s\n", buf2);
chdir("./folder1");
open("file1.txt",0777);
tmp = localtime(&t);
printf("file1 created on ");
if (strftime(buf2, 64, "time and date: %r, %a %b %d, %Y", tmp) == 0)

        printf("buffer length 64 is too small\n");

	        else

		                printf("%s\n", buf2);
open("file2.txt",0777);
tmp = localtime(&t);
printf("file2 created on ");
if (strftime(buf2, 64, "time and date: %r, %a %b %d, %Y", tmp) == 0)

        printf("buffer length 64 is too small\n");

	        else

		                printf("%s\n", buf2);
chdir("../folder2");
open("file3.txt",0777);
tmp = localtime(&t);
printf("file3 created on ");
if (strftime(buf2, 64, "time and date: %r, %a %b %d, %Y", tmp) == 0)

        printf("buffer length 64 is too small\n");

	        else

		                printf("%s\n", buf2);
open("file4.txt",0777);
tmp = localtime(&t);
printf("file4 created on ");
if (strftime(buf2, 64, "time and date: %r, %a %b %d, %Y", tmp) == 0)

        printf("buffer length 64 is too small\n");

	        else

		                printf("%s\n", buf2);
chdir("../folder3");
symlink("../folder2/file4.txt","link5");

return 0;
}
