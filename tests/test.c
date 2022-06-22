
#include  <stdio.h>
#include  <stdlib.h>
#include  <time.h>
    
int main(){
    
    // TIME STUFF
//  time_t timestamp;
//  struct tm* timeinfo;
//  time(&timestamp);
//  timeinfo = localtime(&timestamp);
//  printf("%d %d\n", timestamp, timeinfo->tm_sec);

    // ENV STUFF
//  char *HOMEDIR = getenv("DOT");
//  if (HOMEDIR) printf("%s\n", HOMEDIR);

    // SYSTEM STUFF
//  FILE *out;
//  char buf[1024];
//  out = popen("echo 1\n2\n3 | fzf -m --prompt 'Choose Id: ' --preview 'echo Hallo\nDave'", "r");
//  if (!out) {
//      printf("error executing\n");
//      return 1;
//  }
//  while (fgets(buf, 1024, out)) {
//      printf("%s", buf);
//  }
    return 0;
}
