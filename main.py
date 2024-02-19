f = open('txt.txt', 'r', encoding='UTF8')
while 1:
	line = f.readline()
	if not line: break
	print(line, end='')
f.close()