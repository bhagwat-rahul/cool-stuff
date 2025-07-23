/* this is a server in c, relying on a bunch of abstractions
   (kernel , driver, tcp ip) to start with. rm 1 by 1 as makes sense. */

# include <stdio.h> // Debug only
# include <sys/socket.h>
# include <netinet/in.h>
# include <unistd.h>

int main()
{
  struct sockaddr_in addr = {0};
  addr.sin_family         = AF_INET;
  addr.sin_port           = htons(8080);
  addr.sin_addr.s_addr    = INADDR_ANY;

  struct sockaddr *addr_ptr = (struct sockaddr *)&addr;
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
  do
  {
    int accepted = accept(server_fd, NULL, NULL);
    if (accepted < 0) {
      puts("failed to accept incoming conn!");
      return 1;
    }
    char buffer[1024];
    int bytes_read = read(accepted, buffer, sizeof(buffer)-1);
    buffer[bytes_read] = '\0';
    printf("%s", buffer);
  } while (1);
  return 0;
}
