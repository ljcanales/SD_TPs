all:
	make client server

client: my_FS_client.cpp my_FS_clnt.c
	g++ my_FS_client.cpp my_FS_clnt.c -o client.out

server: my_FS_proc.cpp my_FS_svc.c 
	g++ -pthread my_FS_proc.cpp my_FS_svc.c -o server.out

clean:
	rm -f client.out server.out
