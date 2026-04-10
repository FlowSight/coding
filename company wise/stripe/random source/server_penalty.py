def compute_penalty(store_log, close):
	penalty = 0
	for i, log in enumerate(store_log.split(" ")):
		if (i >= close and log == '0') or (i < close and log == '1'):
			penalty += 1
	return penalty

print(compute_penalty("0 0 1 0", 2))
print(compute_penalty("0 0 1 0", 0))
print(compute_penalty("1 1 1 0", 0))

def find_best_removal_time(store_log):
	hours = len(store_log)
	best = hours
	lowest_penalty = hours
	for i in range(hours):
		penalty = compute_penalty(store_log, i)
		if penalty < lowest_penalty:
			lowest_penalty = penalty
			best = i
	return best

print(find_best_removal_time("0 0 1 1"))

def get_valid(agg_log):
	valid = []
	potential = ""
	for word in agg_log.split():
		print(word)
		if word == 'BEGIN':
			potential = 'S'
		elif word == 'END' and len(potential) > 0:
			if potential[0] == 'S':
				valid.append(" ".join(potential[1:]))
			potential = ''
		else:
			potential += word
	return valid

def get_best_closing_times(agg_log):
	return [find_best_removal_time(valid) for valid in get_valid(agg_log)]

print(get_best_closing_times("BEGIN BEGIN BEGIN 1 1 \n BEGIN 0 0 END BEGIN \n 0 0 1 1 END"))


# def get_best_closing_times__v2(file):
# 	valid = []
# 	potential = ""
# 	def get_valid_v2(agg_log):
# 		nonlocal potential
# 		for word in agg_log.split():
# 			if word == 'BEGIN':
# 				potential = 'S'
# 			elif word == 'END' and len(potential) > 0:
# 				if potential[0] == 'S':
# 					valid.append(" ".join(potential[1:]))
# 				potential = ''
# 			else:
# 				potential += word

# 	with open('myfile.txt', 'r') as file:
# 	    for line in file:
# 	        print(line.strip())
# 	        get_valid_v2(line.strip())


# 	return [find_best_closing_time(v) for v in valid]

# print(get_best_closing_times__v2("myfile.txt"))
