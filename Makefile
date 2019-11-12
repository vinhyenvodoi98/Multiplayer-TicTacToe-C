home := "home.c"
file := "file.c"
linklist := "linklist.c"
UI := "UI.c"
gameClient := "gameClient.c"

run:
	@gcc -o server server.c $(home) $(file) $(linklist) && gcc -o client client.c $(UI) $(gameClient)
