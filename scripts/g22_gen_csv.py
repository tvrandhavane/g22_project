import os
import re

file = open('data/g22_data.csv', "w")

for i in range(1,11):
	for j in range(1,11):
		data = ""
		command = 'bin/cs296_base_analysis ' + str(j) + " > out" 	
		print(command)	
		data = os.system(command)	
		f = open('out', 'r')
		data = f.read()
		f.close()
		data=re.sub('[A-Z]','',data)
		data=re.sub(':','',data)
		data=re.sub('[a-z]','',data)
		data=re.sub(' *','',data)
		data=re.sub('\n+',',',data)
		data=re.sub(',\n','',data)
		data = data[0:-1]
		data = data + '\n'
		data = str(i) + ',' + data
		file.write(data)
		os.system("rm out")
file.close()