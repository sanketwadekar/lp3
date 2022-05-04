import socket

P = int(input("P = "))
G = int(input("G = "))
b = int(input("b = "))

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

Y = (G**b)%P

s.connect(("127.0.0.1", 5001))
print("Connected to server")
s.send(str(Y).encode())

X = int(s.recv(1024).decode())
print("X received")
Kb = (X**b)%P

print("X = ", X)
print("Y = ", Y)
print("Kb = ", Kb)