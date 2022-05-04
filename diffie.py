import socket

P = int(input("P = "))
G = int(input("G = "))
a = int(input("a = "))

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(("", 5001))
print("Server started")
X = (G**a)%P

s.listen(5)
c, addr = s.accept()
print("Connection established")

c.send(str(X).encode())


Y = int(c.recv(1024).decode())
print("Y received")
Ka = (Y**a)%P
# Kb = (X**b)%P
c.close()
print("X = ", X)
print("Y = ", Y)
print("Ka = ", Ka)
# print("Kb = ", Kb)
# if(Ka == Kb):
# 	print("Keys match")
# else:
# 	print("Keys do not match")