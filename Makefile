serverService := "serverService.c"
file := "file.c"
linklist := "linklist.c"
UI := "UI.c"
gameClient := "gameClient.c"
clientP2P := "clientP2P.c"

run:
	@gcc -o server server.c $(serverService) $(file) $(linklist) && gcc -o client client.c $(UI) $(gameClient) $(clientP2P)
