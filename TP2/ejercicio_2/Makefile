all:
	make client server

client: character_service_client.cpp character_service_clnt.c
	g++ character_service_client.cpp character_service_clnt.c -o client.out

server: character_service_proc.cpp character_service_svc.c 
	g++ character_service_proc.cpp character_service_svc.c -o server.out

clean:
	rm -f client.out server.out
