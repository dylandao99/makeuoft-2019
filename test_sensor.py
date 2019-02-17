import mraa

rotary = Aio(A0)
while True:
	print rotary.read()
	print rotary.readFloat()
