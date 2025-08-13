/*
   single file http(s) server relying on a bunch of
   abstractions (kernel, driver, tcp/ip) to start with.
   rm 1 by 1 as makes sense for no deps / baremetal.
   would love to use quic over udp eventually since
   it's newer (HTTP/3) and easier for baremetal.
   To start, it will serve static files only from
   a specified dir. For now new files / updates will
   require a re-run of the server.
   Also to start, let's keep it simple and do one process
   per request, so serve a req and clean up proc, can
   change this later as we get to baremetal and see what
   queuing / parallel implementation we need.
*/

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

# define RES_PROTOCOL  "HTTP/1.1"
# define RES_CODE_200  "200 OK"
# define CONT_TYPE_STR "Content-Type: "
# define CONT_LEN_STR  "Content-Length: "
# define PORT_LISTEN   8080
static const char *allowed_methods[]  = { "GET" };

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
  addr.sin_port           = htons(PORT_LISTEN);
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

  printf("Listening on port %d\n", PORT_LISTEN);

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

    // TODO: Safely match with ram filenames
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
