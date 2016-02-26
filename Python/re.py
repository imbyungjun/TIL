import re

# Only alphabet
p = re.compile('[a-z]+')
print '*************************'
print "comipled regex = ('[a-z]+')"
print '*************************'

# match
print 'match'

m = p.match("python")
print 'python =', m

m = p.match("3 python")
print '3 python =', m

print '*************************'

# search
print 'search'

s = p.search("python")
print 'python =', s

s = p.search("3 python")
print '3 python =', s

print '*************************'

# findall
print 'findall'

result = p.findall("life is too short")
print result

print '*************************'

# finditer
print 'finditer'

result = p.finditer("life is too short")
print result
for r in result :
	print r

print '*************************'

# match method
# group() - return matched string.
# start() - return start index of matched string.
# end() - return last index of matched string.
# span() - return tuple of start and last index of matched string.

print 'match method'

m = p.match("python")
print 'group() -', m.group()
print 'start() -', m.start()
print 'end() -', m.end()
print 'span() -', m.span()

print '*************************'

# raw string
p = re.compile('\\\\section')
print p.search(r'\\section')

p = re.compile(r'\\section')
print p.search('\\\\section')
