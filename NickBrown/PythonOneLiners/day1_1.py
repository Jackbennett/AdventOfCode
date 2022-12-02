# assumes there is a file collocated with this one called "day1_1.txt" containing the raw input
print(max(sum(int(calories) for calories in elf) for elf in [x.split("\n") for x in open("day1_1.txt").read().split("\n\n")]))
