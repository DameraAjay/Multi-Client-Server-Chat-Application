# Multi-Client-Server-Chat-Application
command line client-server chat application with functionalities like check for online users, send message to user, broadcast messaging, creating groups,etc..


# requirement
	GCC compiler
# compile : 
	gcc server.c -o ./server
	gcc client.c -o ./client
# execution:	
	./server PORT_NUMBER (starting server)
	./clinet PORT_NUMBER (connecting client to server)
	**BOTH PORT_NUMBERS SHOULD BE SAME (on which server is listening client requestss)
# This chat application has 11 functionalities:
	on receiving every request server validate that request.
	/active
		- this function is returns all the active clients(users).
	/send <USER_ID> <MSG>
		- on receiving this request from client the server stores all the details in message stucture (Source , Destination,message)
		- next it will check the Destination is active or not 
		- if Destination is active then server send the received message and send back to curresponding message to source(user).
		- if Destination is not active then server remove that message (free) and send back to curresponding message to source(user).
	/broadcast
		- on receiving this request from client the sever stores all the details in message structure (Source,message).
		- next server send the received message to all active clients(users) and send back to curresponding message to source(user).
	/makegroup <CLIENT_ID1> <CLIENT_ID2> <CLIENT_ID3>...
		- on receiving this request from client stores all the details and the sever server generate a unique id for the group.
		- next it check given clients are active or not.if not server will not add inactive clients to group
		- server create a group whenn atleast one clint and admin.
	/sendgroup <GROUP_ID> <message>
		- on receiving this request from client stores all the details and the server check weather group is existed or not
		- if group is existed then server send tha received message to all active clients in that group
	/activegroups
		- on receiving this request from client server start checkig which groups are having sender as a member
		- return all the groups which are having the sender as a member
	/makegroupreq <CLIENT1_ID1> <CLIENT_ID2> ...
		- on receiving this request from client server stores all the details.
		- server validate the each client(active or not).
		- server send the add request to all active clients.
		- server create a temporary group and assign a unique id.
		- next server will wait for till all the replays from clients who ever receive the add request
		- after getting all replays from clients the server make the temporary group to parminant if atleast one client accept the add request without admin.
	/joingroup <GROUP_ID>
		- on receiving this request from client server stores all the details.
		- server checks weather group exist with given group id or not.
		- if not it return the curresponding message.
		- if group exists then server checks wearther sender(client) has the add request or not
		- if sender has add request then server add the sender to temporary list and checks all replays(accept) or dacleins are received or not if yes then it make the group into perminant  or else it wait for all the replays or declains
		- if sender doesn't have the add request then server return curresponding message.
		- group will make perminant only atleast one member without admin
	/declinegroup <GROUP_ID>
		- on receiving this request from client server stores all the details.
		- server checks weather group exist with given group id or not.
		- if not it return the curresponding message.
		- if group exists then server checks wearther sender(client) has the add request or not
		- if sender has add request then server decline that request and checks all replays(accept) or declains are received or not if yes then it make the group into perminant  or else it wait for all the replays or declains.
		- group will make perminant only atleast one member without admin
	/quit 
	 	- on receiving this request from client sever checks the groups in which the sender is present
	 	- server remove the sender from all active groups which are having sender has a member
	/activeallgroups
		- on receiving this request from client server checks all the active groups and return those groups
  
