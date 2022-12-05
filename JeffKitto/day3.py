def day3p1():
	with open("day3.txt", "r") as inputfile:
		data = [line.strip() for line in inputfile]
	total = 0
	for ruck in data:
		hw = int(len(ruck)/2)
		c1 = set(ruck[:hw])
		c2 = set(ruck[hw:])
		for item in c1:
			if item in c2:
				if item.isupper():
					total+= ord(item) - 38
				else:
					total+= ord(item) - 96
				break
	print(total)

def day3p2():
	with open("day3.txt", "r") as inputfile:
		data = [line.strip() for line in inputfile]
	total = 0
	for i in range(len(data)):
		if (i+1) % 3 == 0:
			total += calc(data[i], data[i-1], data[i-2])
	print(total)

def calc(r1,r2,r3):
	for item in set(r1):
		if item in set(r2) and item in set(r3):
			if item.isupper():
				return ord(item) - 38
			else:
				return ord(item) - 96