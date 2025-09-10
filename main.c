#include<stdio.h>
#include<stdint.h>
#include<string.h>

// Functions from convert.c
void div_convert (uint32_t n , int base , char *out);
void sub_convert (uint32_t n, int base, char *out);
void print_tables (uint32_t n, char *out);


int main() {
    
    FILE * file = fopen ( "A1_tests.txt" , "r" ) ;
        if ( file == NULL ) {
        printf ( "Error : Could not open file \n" ) ;
        return 1;
    }
    //Variables
    char line [256];
    int currentTest = 1;
    int totalTests = 0;
    int testsPassed = 0;
    
    // Process each line
    while ( fgets ( line, sizeof (line), file ) != NULL ) {
        // Skip line if it's a comment or newline
        if (line[0] == '#' || line[0] == '\n'){
            continue;
        }
        
        //Test Variables
        char function[33];
        uint32_t n;
        int base;
        char expectedOutput[65];
        char output[65];
        int meetsExpected;
        
        //Process line text
        int arguments = sscanf(line, "%31s %u %d %64s", function, &n, &base, expectedOutput);
        
        //if div_convert
        if (strcmp(function, "div_convert") == 0 && arguments == 4) {
            div_convert(n, base, output);
            meetsExpected = strcmp(output, expectedOutput) == 0;
            
            //Check if expected output was met or not
            printf("Test %d: div_convert(%u , %d) -> Expected: \"%s\", Got: \"%s\" ", currentTest++, n, base, expectedOutput, output);
            //Passed test
            if (meetsExpected) {
                printf("[PASS]\n");
                testsPassed++;
            }
            //Failed test
            else {
                printf("[FAIL]\n");
            }
            
            //Increase total test count
            totalTests++;
        }
        
        //if sub_convert
        else if (strcmp(function, "sub_convert") == 0 && arguments == 4) {
            sub_convert(n, base, output);
            meetsExpected = strcmp(output, expectedOutput) == 0;
            
            //Check if expected output was met or not
            printf("Test %d: sub_convert(%u , %d) -> Expected: \"%s\", Got: \"%s\" ", currentTest++, n, base, expectedOutput, output);
            //Passed test
            if (meetsExpected) {
                printf("[PASS]\n");
                testsPassed++;
            }
            //Failed test
            else {
                printf("[FAIL]\n");
            }
            
            //Increase total test count
            totalTests++;
            
        }
        
        //if print_tables
        else if (strcmp(function, "print_tables") == 0 && arguments >= 2) {
           char printTablesOutput[512];
           print_tables(n, printTablesOutput);
           
           //Variables for format checking
           meetsExpected = 0;
           char outputCheck[512];
           strcpy(outputCheck, output);
           
           //Split text into individual lines
           char *lineText = strtok(outputCheck, "\n");
           int currentLine = 0;
           
           //Format check each line of the output
           while (lineText != NULL) {
               currentLine++;
               
               //Check if start of line matches
               if ((currentLine == 1 && strstr(lineText, "Original:") == NULL) ||
               (currentLine == 2 && strstr(lineText, "Left Shift by 3:") == NULL) ||
               (currentLine == 3 && strstr(lineText, "AND with 0xFF:") == NULL)) {
                   meetsExpected = 1;
                   break;
               }
               
               //Check if rest of output exists (Binary, Octal, etc.)
               if (strstr(lineText, "Binary =") == NULL ||
               strstr(lineText, "Octal =") == NULL ||
               strstr(lineText, "Decimal =") == NULL ||
               strstr(lineText, "Hex =") == NULL) {
                   meetsExpected = 1;
                   break;
               }
               
               //Move to next line
               lineText = strtok(NULL, "\n");
           }
           //Check if correct amount of lines in output
           if (currentLine != 3) {
               meetsExpected = 1;
           }
           
           //Check if expected output was met or not
           printf("Test %d: print_tables(%u) -> [FORMATTED OUTPUT CHECK] ", currentTest++, n);
           
           //Passed test
           if (meetsExpected) {
               printf("[PASS]\n");
               testsPassed++;
           }
           //Failed test
           else {
               printf("[FAIL]\n");
           }
           
           //Increase total test count
           totalTests++;
        }
    }
    //Close file and show test count
    fclose (file);

    printf("...\n");
    printf("Summary: %d/%d tests passed\n", testsPassed, totalTests);
    return 0;
}