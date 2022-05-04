from random import randint
from math import gcd
import socket
import json
def mod_inverse(e, phi):
	for i in range(1, phi + 1):
		if ((e*i)%phi == 1):
			return i

def generate_keys():
	p = int(input("p = "))
	q = int(input("q = "))
	n = p*q
	phi = (p-1)*(q-1)
	print("phi = ", phi)
	while True:
		e = randint(2, phi)
		if gcd(phi, e) == 1:
			break
	
	d = mod_inverse(e, phi)
	return [e, n], [d, n]

def decrypt(C, d, n):
	return (C**d)%n

public_key, private_key = generate_keys()
print("Public Key = ", public_key, "\nPrivate Key = ", private_key)

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
port = 12345
s.bind(("", port))
print("Socket binded to port ", port)

s.listen(5)
print("Socket is listening")
c, addr = s.accept()
print('Got connection from ', addr)
key = {
	"e": public_key[0],
	"n": public_key[1]
}
print("Sending public key to client")
c.send(str(json.dumps(key)).encode())
# c.send(str(public_key[1]).encode())
cipher = c.recv(1024).decode()
print("cipher text received = ", cipher)
c.close()
print("Decrypted Text = ", decrypt(int(cipher), private_key[0], private_key[1]))