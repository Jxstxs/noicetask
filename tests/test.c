
#include  <stdio.h>
#include  <stdlib.h>
#include  <time.h>
#include  <string.h>
    
int main(){
    
    // TIME STUFF
    // time_t timestamp;
    // struct tm* timeinfo;
    // time(&timestamp);
    // timeinfo = localtime(&timestamp);
    // printf("%d %d\n", timestamp, timeinfo->tm_sec);

    // // ENV STUFF
    // char *HOMEDIR = getenv("DOT");
    // if (HOMEDIR) printf("%s\n", HOMEDIR);

    // // SYSTEM STUFF
    // FILE *out;
    // char buf[1024];
    // out = popen("echo 1\n2\n3 | fzf -m --prompt 'Choose Id: ' --preview 'echo Hallo\nDave'", "r");
    // if (!out) {
    //     printf("error executing\n");
    //     return 1;
    // }
    // while (fgets(buf, 1024, out)) {
    //     printf("%s", buf);
    // }

    // STRING STUFF
    // printf("%d\n", strcmp("", ""));
    // printf("%d\n", strcmp("abc", ""));
    // printf("%d\n", strcmp("Ab", "ABC"));

    printf("%d\n", atoi("1"));
    printf("%d\n", atoi("a"));

    return 0;
}
