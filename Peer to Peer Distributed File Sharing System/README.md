# AOS Assignment 3
# Lakshay Baijal 2024202006

# Peer to Peer Distributed File Sharing System

This assignment is a simple peer-to-peer (P2P) distributed file-sharing system. It involves a tracker and multiple clients that can share files with one another. The clients communicate with the tracker to register and find other peers, and they directly connect to each other to upload and download files.

- In Client Compile using
  
g++ -pthread -o client client.cpp -lcrypto

- Client Execution
  
./client IP:PORT tracker_info.txt

./client 127.0.0.1:6000 tracker_info.txt

- In Tracker Compile using
  
g++ tracker.cpp -o tracker -lpthread

- Tracker Execution
  
./tracker tracker_info.txt 1

## Menu Based Commands

### Client Terminal -
-Sign Up:
create_user
<<user_id>>
<password>

- Login:
login
<user_id>
<password>

- Create Group: 
create_group <group_id>

- Join Group: 
join_group <group_id>

- Leave Group: 
leave_group <group_id>

- Upload File: 
upload_file 
<file_path>

- Download File: 
download_file 
<file_name> 
{Destination in Client Downloads}

- Logout: 
logout

- Exit:
exit
