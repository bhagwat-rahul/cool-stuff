/* single file http(s) server relying on a bunch of
   abstractions (kernel, driver, tcp/ip) to start with.
   rm 1 by 1 as makes sense for no deps / baremetal. */

# include <stdio.h> // Debug only
# include <sys/socket.h> // unistd usually includes this but better to explicitly include
# include <netinet/in.h>
# include <unistd.h>
# include <string.h> // We can implement this ourselves but let's use for now
# include <dirent.h>

#define PUBLIC_DIR "./public"

// inspired by althttpd, doing my little bit in the rebellion
#ifdef HTTP_CRLF
static const char newline[3] = "\r\n";
#else
static const char newline[2] = "\n";
#endif

static const char allowedInName[] = {
      /*  x0  x1  x2  x3  x4  x5  x6  x7  x8  x9  xa  xb  xc  xd  xe  xf */
/* 0x */   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
/* 1x */   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
/* 2x */   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
/* 3x */   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,
/* 4x */   0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
/* 5x */   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  1,
/* 6x */   0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
/* 7x */   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  1,  0,
/* 8x */   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
/* 9x */   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
/* Ax */   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
/* Bx */   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
/* Cx */   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
/* Dx */   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
/* Ex */   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
/* Fx */   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
};

static const char *res_protocol       = "HTTP/1.1";
static const char *res_code_200       = "200 OK";
static const char *res_cont_type_str  = "Content-Type: ";
static const char *res_cont_len_str   = "Content-Length: ";
static const char *allowed_methods[] = { "GET" };

static int sanitizeString(char *z){
  int nChange = 0;
  while( *z ){
    if( !allowedInName[*(unsigned char*)z] ){
      char cNew = '_';
      if( *z=='%' && z[1]!=0 && z[2]!=0 ){
        int i;
        if( z[1]=='2' ){
          if( z[2]=='e' || z[2]=='E' ) cNew = '.';
          if( z[2]=='f' || z[2]=='F' ) cNew = '/';
        }
        for(i=3; (z[i-2] = z[i])!=0; i++){}
      }
      *z = cNew;
      nChange++;
    }
    z++;
  }
  return nChange;
}

typedef struct {
    char *filename;
    char *content;
    size_t size;
} FileEntry;

/* for file in files create a FileEntry for eachfile and return fcount
 * ret  -(line number) of errored line if errors anywhere
 */
int load_files(FileEntry *files)
{
  int fcount = 0;
  DIR *d = opendir(PUBLIC_DIR);
  if (!d) {
      perror("opendir");
      return fcount = -1;
  }
  struct dirent *entry;
  while ((entry = readdir(d))) {
    fcount++;
  }
  return fcount;
}

int main()
{
  struct sockaddr_in addr = {0};
  addr.sin_family         = AF_INET;
  addr.sin_port           = htons(8080);
  addr.sin_addr.s_addr    = INADDR_ANY;

  struct sockaddr *addr_ptr = (struct sockaddr *)&addr;
  char *res_code, *res_cont_type, *res_cont_len, *res_cont;
  char headers[512] = "\0", res[2048] = "\0";

  puts("loading webpage files!");
  FileEntry files[] = {};
  int lfile = load_files(files);
  if (lfile <= 0)
    {
      printf("Loading files from %s errored or it is empty\n", PUBLIC_DIR);
    }

  int server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (server_fd < 0) {
      puts("socket creation failed!");
      return 1;
  }
  int binding   = bind(server_fd, addr_ptr, sizeof(addr));
  if (binding < 0)
    {
      puts("bind failed!");
      return 1;
    }
  int listening = listen(server_fd, 10);
  if (listening < 0) {
      puts("listening failed!");
      return 1;
  }
  while (1)
  {
    char req_buf[1024], method[8], raw_path[256];
    int accepted = accept(server_fd, NULL, NULL);
    if (accepted < 0) {
      puts("failed to accept incoming conn!");
      return 1;
    }
    int bytes_read = read(accepted, req_buf, sizeof(req_buf)-1);
    if (bytes_read <= 0) {
        puts("read failed or conn closed");
        close(accepted);
        continue;
    }
    req_buf[bytes_read] = '\0';
    printf("Raw req: %s\n\n", req_buf);
    // TODO: Sanitize safely
    if (sscanf(req_buf, "%7s %255s", method, raw_path) != 2) {
        puts("Malformed request line");
        close(accepted);
        continue;
    }
    printf("Req type: %s\nReq path:- %s\n", method, raw_path);
    if (strcmp(method, "GET") != 0) // TODO: not static get use from allowed methods
      {
        puts("Invalid request method we only support GET!"); // send apropos response
        close(accepted);
        continue;
      }

    res_code      = "HTTP/1.1 200 OK";
    res_cont_type = "Content-Type: text/html";
    res_cont_len  = "Content-Length: 16";
    res_cont      = "Server healthy!";

    strcpy(headers, res_code);
    strcat(headers, newline);
    strcat(headers, res_cont_type);
    strcat(headers, newline);
    strcat(headers, res_cont_len);
    strcat(headers, newline);
    strcat(headers, newline);

    strcat(res, headers);
    strcat(res, res_cont);
    strcat(res, newline);

    write(accepted, res, strlen(res));
    close(accepted);
  }
  return 0;
}
