#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

static void list_dir (const char * dir_name);

//void printFileProperties(struct stat stats);

int main()
{ 
  list_dir(".");
    
  return 0;
}

static void
list_dir (const char * dir_name)
{
  DIR * d;
  
  /* Open the directory specified by "dir_name". */
  d = opendir (dir_name);
  
  /* Check it was opened. */
  if (! d) 
  {
    fprintf (stderr, "Cannot open directory '%s': %s\n",
    dir_name, strerror (errno));
    exit (EXIT_FAILURE);
  }
  while (1) 
  {
    struct stat mystat;
    struct dirent * entry;
    
    const char * d_name;
    /* "Readdir" gets subsequent entries from "d". */
    entry = readdir (d);

    if (! entry) 
    {
      /* There are no more entries in this directory, so break
      out of the while loop. */
      break;
    }
    stat(entry->d_name, &mystat);
    d_name = entry->d_name;
    printf( (S_ISDIR(mystat.st_mode)) ? "d" : "-");
    printf( (mystat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (mystat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (mystat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (mystat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (mystat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (mystat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (mystat.st_mode & S_IROTH) ? "r" : "-");
    printf( (mystat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (mystat.st_mode & S_IXOTH) ? "x" : "-");
    printf(" %u ",mystat.st_uid);
    printf(" %g ",mystat.st_gid);
    printf(" %d ",mystat.st_size);
    /* Print the name of the file and directory. */
    printf ("%s/%s\n", dir_name, d_name);
   // printf(" %d ", mystat.st_mtime);
    
    #if 0
	/* If you don't want to print the directories, use the
	   following line: */
     
    if (! (entry->d_type & DT_DIR))
    {
      printf( (S_ISDIR(mystat.st_mode)) ? "d" : "-");
      printf( (mystat.st_mode & S_IRUSR) ? "r" : "-");
      printf( (mystat.st_mode & S_IWUSR) ? "w" : "-");
      printf( (mystat.st_mode & S_IXUSR) ? "x" : "-");
      printf( (mystat.st_mode & S_IRGRP) ? "r" : "-");
      printf( (mystat.st_mode & S_IWGRP) ? "w" : "-");
      printf( (mystat.st_mode & S_IXGRP) ? "x" : "-");
      printf( (mystat.st_mode & S_IROTH) ? "r" : "-");
      printf( (mystat.st_mode & S_IWOTH) ? "w" : "-");
      printf( (mystat.st_mode & S_IXOTH) ? "x" : "-");
      printf(" UID: %u ",mystat.st_uid);
      printf(" GID: %g ",mystat.st_gid);
      printf(" Size: %d ",mystat.st_size);
    }

#endif /* 0 */

    
    if (entry->d_type & DT_DIR) 
    {
      /* Check that the directory is not "d" or d's parent. */
      if (strcmp (d_name, "..") != 0 && strcmp (d_name, ".") != 0) 
      {
        int path_length;
        char path[PATH_MAX];
        path_length = snprintf (path, PATH_MAX, "%s/%s", dir_name, d_name);
       // printf ("%s\n", path);
  
        if (path_length >= PATH_MAX)
        {
          fprintf (stderr, "Path length has got too long.\n");
          exit (EXIT_FAILURE);
        }
        
        /* Recursively call "list_dir" with the new path. */
        list_dir (path);
      }
    }
  }
  
  /* After going through all the entries, close the directory. */
  if (closedir (d))
  {
    fprintf (stderr, "Could not close '%s': %s\n", dir_name, strerror (errno));
    exit (EXIT_FAILURE);
  }
}


/*void printFileProperties(struct stat stats)
{
    struct tm dt;

    // File permissions
    printf("\nFile access: ");
    if (stats.st_mode & R_OK)
        printf("read ");
    if (stats.st_mode & W_OK)
        printf("write ");
    if (stats.st_mode & X_OK)
        printf("execute");

    // File size
    printf("\nFile size: %d", stats.st_size);

    // Get file creation time in seconds and 
    // convert seconds to date and time format
    dt = *(gmtime(&stats.st_ctime));
    printf("\nCreated on: %d-%d-%d %d:%d:%d", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900, 
                                              dt.tm_hour, dt.tm_min, dt.tm_sec);

    // File modification time
    dt = *(gmtime(&stats.st_mtime));
    printf("\nModified on: %d-%d-%d %d:%d:%d", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900, 
                                              dt.tm_hour, dt.tm_min, dt.tm_sec);

}*/