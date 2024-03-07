
#define BUFFERSIZE 1024

char ** csvopen (char * filename);

char ** csvnext (void);

char ** csvheader (void);

int csvclose (void);