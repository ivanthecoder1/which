#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

int main(int argc, char** argv) {
    bool a_flag = false;
    char *filename;
    
    // Read in path variable
    char* path = getenv("PATH"); 

    // Split the PATH variable into a list of directories using : as the delimiter 
    char* dir = strtok(path, ":"); 

    // Read and parse command line inputs
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-a") == 0) { // a flag passed in
          a_flag = true;
        } 
        else if (argv[i][0] == '-') { // Unknown flag passed in
          printf("Unknown flag %s\n", argv[i]);
          return 2;
        }
        else { // Extract filename
          filename = argv[i];
        }
    }

    // no arguments inputted or argument has a flag but no filename
    if (argc == 1 || a_flag == true && argc == 2) {
      return 1;
    }
    
    // Iterate through the PATH directories
    while (dir != NULL) {
      // Iterate through the file names
      // Concatenate the file name to the path directory
      char *filepath = malloc(strlen(dir) + strlen(filename) + 2); // add 2 to account for slashes
      sprintf(filepath, "%s/%s", dir, filename);

      // Determine whether or not this is a valid executable file
      if (file_exists(filepath)) {
          printf("%s\n", filepath);
          // Move on to the next filename if the -a flag is not passed into the program.
          if (!a_flag) {
              break;
          } 
       }
      free(filepath); // Deallocate the memory block used to create filepath array

      // Continue looping through the remaining directories in the PATH to find duplicate files
      dir = strtok(NULL, ":");
    }
  return 0;
}

//  Takes as input a path to a file, and determines if the file exists and is executable 
int file_exists(char* path) {
    if (access(path, X_OK) == 0) { 
        return 0; 
    } else {
        return 1;
    }
}