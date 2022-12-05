def day1():
	myfile = open("day1.txt", "r")
	mylines = myfile.readlines()
	totals = []
	index = 0
	for line in mylines:
		totals.append(0)
		if line == "\n":
			index +=1
		else:
			totals[index] += int(line)
	stotals = sorted(totals, reverse=True)
	print(stotals)
	print(sum(stotals[0:3]))