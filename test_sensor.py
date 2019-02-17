import mraa

rotary = mraa.Aio(0)
while True:
	print rotary.read()
	print rotary.readFloat()
