/* single file http(s) server relying on a bunch of
   abstractions (kernel, driver, tcp/ip) to start with.
   rm 1 by 1 as makes sense for no deps / baremetal.
   would love to use quic over udp eventually since
   it's newer (HTTP/3) and easier for baremetal. */

# include <stdio.h> // Debug only
# include <sys/socket.h> // unistd usually includes this but better to explicitly include
# include <netinet/in.h>
# include <unistd.h>
# include <string.h> // We can implement this ourselves but let's use for now
# include <dirent.h>

# define PUBLIC_DIR "./public"

// inspired by althttpd, doing my little bit in the rebellion
# ifdef SEND_CR
# define CRLF "\r\n"
# else
# define CRLF "\n"
# endif

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

# define RES_PROTOCOL  "HTTP/1.1"
# define RES_CODE_200  "200 OK"
# define CONT_TYPE_STR "Content-Type: "
# define CONT_LEN_STR  "Content-Length: "
static const char *allowed_methods[]  = { "GET" };

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

/* create FileEntry for each file in dir and return file count / -1 if error */
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
  closedir(d);
  return fcount;
}

int handle_req(int accepted)
{
  int handled = 0;
  char *res_code, *res_cont_type, *res_cont_len, *res_cont;
  res_code      = "HTTP/1.1 200 OK";
  res_cont_type = "Content-Type: text/html";
  res_cont_len  = "Content-Length: 16";
  res_cont      = "Server healthy!";

  write(accepted, res_code, strlen(res_code));
  write(accepted, CRLF, strlen(CRLF));
  write(accepted, res_cont_type, strlen(res_cont_type));
  write(accepted, CRLF, strlen(CRLF));
  write(accepted, res_cont_len, strlen(res_cont_len));
  write(accepted, CRLF, strlen(CRLF));
  write(accepted, CRLF, strlen(CRLF));
  write(accepted, res_cont, strlen(res_cont));
  write(accepted, CRLF, strlen(CRLF));
  close(accepted);

  return handled;
}

int handle_method (char *req_buf)
{
  return 0;
}

int main()
{
  struct sockaddr_in addr = {0};
  addr.sin_family         = AF_INET;
  addr.sin_port           = htons(8080);
  addr.sin_addr.s_addr    = INADDR_ANY;

  struct sockaddr *addr_ptr = (struct sockaddr *)&addr;

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

    int handled = handle_req(accepted);
  }
  return 0;
}
