def split(word):
    return [char for char in word]

f = open('type.txt', 'r')
nos = split(f.read())
f.close()
f = open('hello_world_trace.txt', 'r')
trace = f.read().split('\n')
#print(trace)
print(len(nos))

length = len(trace)
print(length)
for i in range(length):
    trace[i] = nos[i] + trace[i] 

print(trace)
