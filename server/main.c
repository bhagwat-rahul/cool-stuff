/* server relying on a bunch of abstractions
   (kernel, driver, tcp/ip) to start with.
   rm 1 by 1 as makes sense. */

# include <stdio.h> // Debug only
# include <sys/socket.h>
# include <netinet/in.h>
# include <unistd.h>
# include <string.h> // We can implement this ourselves but let's use for now

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
    int accepted = accept(server_fd, NULL, NULL);
    if (accepted < 0) {
      puts("failed to accept incoming conn!");
      return 1;
    }
    char buffer[1024];
    int bytes_read = read(accepted, buffer, sizeof(buffer)-1);
    if (bytes_read <= 0) {
        puts("read failed or conn closed");
        close(accepted);
        continue;
    }
    buffer[bytes_read] = '\0';
    printf("%s", buffer);

    res_code      = "HTTP/1.1 200 OK\n";
    res_cont_type = "Content-Type: text/html\n";
    res_cont_len  = "Content-Length: 16\n";
    res_cont      = "Server healthy!\n";

    strcpy(headers, res_code);
    strcat(headers, res_cont_type);
    strcat(headers, res_cont_len);
    strcat(res, headers);
    strcat(res, "\n");
    strcat(res, res_cont);

    write(accepted, res, strlen(res));
    close(accepted);
  }
  return 0;
}
