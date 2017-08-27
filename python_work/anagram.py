

def is_anagram(s1,s2):
	letters = {}

	if len(s1) is not len(s2):
		return False

	for c in s1:
		if c in letters:
			letters[c] += 1
		else:
			letters[c] = 1

	for c in s2:
		if c in letters:
			letters[c] -= 1

			if letters[c] < 0:
				return False
		else:
			return False
	

	print letters

	return True


s1 = "ccca"
s2 = "ccca"

print is_anagram(s1,s2)
