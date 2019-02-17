import mraa

rotary = mraa.Aio(A0)
while True:
	print rotary.read()
	print rotary.readFloat()
