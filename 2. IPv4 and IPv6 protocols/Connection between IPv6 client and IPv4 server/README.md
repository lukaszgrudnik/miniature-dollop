How to run:

    gcc server.c -o ./out/server
    gcc client.c -o ./out/client
    ./out/server 8080
    ./out/client 0000:0000:0000:0000:0000:ffff:0000:0000 8080 ::ffff:127.0.0.1
