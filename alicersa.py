from email import message
import socket
import json
def encrypt(M, e, n):
	cipher = (M**e)%n
	return cipher
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

host_ip = "127.0.0.1"
port = 12345

s.connect((host_ip, port))
print("Connected to Server")

# Receive keys
json_key = s.recv(4096).decode()
key = json.loads(json_key)
print(json_key)
print("e = ", key['e'], " n = ", key['n'])

message = int(input("Message = "))

cipher = encrypt(message, key['e'], key['n'])

print("Sending cipher = ", cipher)
s.send(str(cipher).encode())