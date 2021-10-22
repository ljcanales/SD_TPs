all:
	make client server

client: client.cpp calculator_clnt.c calculator_xdr.c
	g++ client.cpp calculator_clnt.c calculator_xdr.c -o client.out

server: calculator_proc.c calculator_svc.c calculator_xdr.c
	gcc calculator_proc.c calculator_svc.c calculator_xdr.c -o server.out

clean:
	rm -f client.out server.out
