#include <stdio.h>
#include <stdlib.h>
#include <uv.h>

void on_close(uv_handle_t *handle);
void on_connect(uv_connect_t *req, int status);
void on_write(uv_write_t *req, int status);
void alloc_cb(uv_handle_t *handle, size_t size, uv_buf_t *buf);
void startConn(char *host, int port);
static uv_loop_t *loop;

int main(int argc, char **argv)
{
    loop = uv_default_loop();
    int i;
    for (i = 0; i < 10; i++)
        startConn("0.0.0.0", 7000);

    uv_run(loop, UV_RUN_DEFAULT);
    return 0;
}

void alloc_cb(uv_handle_t *handle, size_t size, uv_buf_t *buf)
{
    *buf = uv_buf_init(malloc(size), size);
}

void on_close(uv_handle_t *handle) { printf("%p closed.\n", handle); }

void on_write(uv_write_t *req, int status)
{
    if (status) {
        perror("uv_write error ");
        return;
    }
    printf("已送出訊息\n");
    free(req);
    // uv_close((uv_handle_t*)req->handle, on_close);
}

void on_read(uv_stream_t *tcp, ssize_t nread, const uv_buf_t *buf)
{
    if (nread >= 0) {
        // printf("read: %s\n", tcp->data);
        printf("on_read. %p,內容: %s\n", tcp, buf->base);
    } else {
        // we got an EOF
        uv_close((uv_handle_t *)tcp, on_close);
    }

    // cargo-culted
    free(buf->base);
}

void writeToServer(uv_stream_t *stream, char *data, int length)
{
    uv_buf_t buffer[] = {{.base = data, .len = length}};
    uv_write_t *req = malloc(sizeof(uv_write_t));
    uv_write(req, stream, buffer, 1, on_write);
}

void on_connect(uv_connect_t *connection, int status)
{
    if (status < 0) {
        printf("failed to connect\n");
        return;
    }
    printf("已連線... %p %d\n", connection, status);

    uv_stream_t *stream = connection->handle;
    free(connection);
    writeToServer(stream, "Hello world! I am Client", 128);
    uv_read_start(stream, alloc_cb, on_read);
}

void startConn(char *host, int port)
{
    uv_tcp_t *pSock = malloc(sizeof(uv_tcp_t));
    uv_tcp_init(loop, pSock);
    uv_tcp_keepalive(pSock, 1, 10);

    struct sockaddr_in dest;
    uv_ip4_addr(host, port, &dest);

    uv_connect_t *pConn = malloc(sizeof(uv_connect_t));
    printf("分配連線中... %p\n", pConn);
    uv_tcp_connect(pConn, pSock, (const struct sockaddr *)&dest, on_connect);
}