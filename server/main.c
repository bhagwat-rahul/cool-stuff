/* single file http(s) server relying on a bunch of
   abstractions (kernel, driver, tcp/ip) to start with.
   rm 1 by 1 as makes sense for no deps / baremetal. */

# include <stdio.h> // Debug only
# include <sys/socket.h> // unistd usually includes this but better to explicitly include
# include <netinet/in.h>
# include <unistd.h>
# include <string.h> // We can implement this ourselves but let's use for now

#ifdef HTTP_CRLF
static const char newline[3] = "\r\n";
#else
static const char newline[2] = "\n";
#endif

int main()
{
  struct sockaddr_in addr = {0};
  addr.sin_family         = AF_INET;
  addr.sin_port           = htons(8080);
  addr.sin_addr.s_addr    = INADDR_ANY;

  struct sockaddr *addr_ptr = (struct sockaddr *)&addr;
  char *res_code, *res_cont_type, *res_cont_len, *res_cont;
  char headers[512] = "\0", res[2048] = "\0";

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
    char req_buf[1024];
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
    printf("%s", req_buf);

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
