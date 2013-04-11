import re
from time import strftime, gmtime

f = open("doc/Report.tex", 'r')
data = f.read()
f.close()
array = data.split('\n')
section = {}
authorlist = {}



################################################ Extracting Title ########################################
line = ""
flag=0
firstWord = ''
while(flag==0):
	line = array[0]
	del array[0]
	firstWord = line.split('{',1)[0]
	if firstWord == '\\title':		
		title = line.split('{',1)[1]
		flag=1
		break
		
title = title[:-1]
#print("Title:",title)



########################################## Extracting Authors ###########################################

word = "author"
openb = closeb = 0
author = ""
flag=0

while(flag == 0):
	line = array[0]
	if word in line:
		while(1):
			line = array[0]
			del array[0]
			openb += line.count('{')
			closeb += line.count('}')
			if (openb - closeb != 0):
				author= author + line + '\n'
			elif(openb - closeb == 0):
				author= author + line
				flag = 1
				break
	del array[0]
					
#storing authors

authors = author.split('\n')
i=1
legthauthor = len(authors)
authorname = []
authorollNos = []



while(i!=legthauthor):
	authorname.append(re.sub('\\\\','',authors[i]))
	authoroll=re.sub("texttt{","",authors[i+1])
	authoroll=re.sub("}","",authoroll)
	authorollNos.append(re.sub("\\\\","",authoroll))
	i+=3

#print(authorname[0])
#print(authorollNos[0])


#####################################################################################

################################ extracting sections #################################
sectionNames = []
while(len(array) != 0):
	flag=0
	firstWord = ''
	sectionname = ''
	while(flag==0 and len(array)!=0):
		line = array[0]
		del array[0]
		firstWord = line.split('{',1)[0]
		if firstWord == '\\section':		
			sectionname = line.split('{',1)[1]
			flag=1
			break
	sectionname = sectionname[:-1]
	sectionNames.append(sectionname)

	sectioncontent = ""

	flag =0
	while(len(array)!=0):
		line = array[0]
		del array[0]
		openb += line.count('{')
		closeb += line.count('}')
		if (openb - closeb != 0):
			sectioncontent= sectioncontent + line + '\n'
		elif(openb - closeb == 0):
			sectioncontent= sectioncontent + line
			flag = 1
			break
	#print(sectioncontent)
	section[sectionname] = sectioncontent
	
#print(sectionNames[3])


########################################################################################################


######################### Processing section for profilling ############################################

###profiling data
section1 = section[sectionNames[3]]
arrayofsection1 = section1.split("\n")
section1 = {}
openb = closeb = 0
subsectionName = []

while(len(arrayofsection1) != 0):
	flag=0
	firstWord = ''
	sectionname = ''
	while(flag==0 and len(arrayofsection1)!=0):
		line = arrayofsection1[0]
		del arrayofsection1[0]
		firstWord = line.split('{',1)[0]
		if firstWord == '\\subsection':		
			sectionname = line.split('{',1)[1]
			flag=1
			break
	sectionname = sectionname[:-1]
	subsectionName.append(sectionname)


	sectioncontent = ""
	flag =0
	openb = closeb =0
	while(len(arrayofsection1)!=0):
		line = arrayofsection1[0]
		del arrayofsection1[0]
		openb += line.count('{')
		closeb += line.count('}')
		if (openb - closeb != 0):
			sectioncontent= sectioncontent + line + '\n'
		elif(openb - closeb == 0):
			sectioncontent= sectioncontent + line
			flag = 1
			break
	#print(sectionname)
	section1[sectionname] = sectioncontent
	

subsection1 = section1[subsectionName[0]]
subsection2 = section1[subsectionName[1]]

subsection1=re.sub("\\\\[a-z]*","",subsection1)
subsection1=re.sub("\$","",subsection1)
subsection1=re.sub("{[a-z]+}","",subsection1)
subsection1=re.sub("{","",subsection1)
subsection1=re.sub("}","",subsection1)
subsection1=re.sub("%","",subsection1)
subsection1=re.sub("\n\n","\n",subsection1)

#print(subsection1)


observationsub1 = ""
arrayofsubsection = subsection1.split('\n')
observationsub1 = arrayofsubsection[1]
del arrayofsubsection[1]
observationsub2 = arrayofsubsection[1]
del arrayofsubsection[1]
observationsub3 = arrayofsubsection[1]
del arrayofsubsection[1]
del arrayofsubsection[2]
del arrayofsubsection[2]

#print(observationsub5)
observationsub4 = ""
while (len(arrayofsubsection) != 3):
	observationsub4 = observationsub4 + arrayofsubsection[1] + '\n'
	del arrayofsubsection[1]
	
#observationsub4=re.sub("\n\n","<br>",observationsub4)	
observationsub4=re.sub("\n","<br><br>",observationsub4)


#####call graphs


subsection2=re.sub("\\\\[a-z]*","",subsection2)
subsection2=re.sub("\$","",subsection2)
subsection2=re.sub("{[a-z]+}","",subsection2)
subsection2=re.sub("{","",subsection2)
subsection2=re.sub("}","",subsection2)
#print(subsection2)

arrayofsubsection2 = subsection2.split('\n')

observationarray = []
while(len(arrayofsubsection2) != 0):
	if arrayofsubsection2[0]:
		if arrayofsubsection2[0][0].isdigit():
			observationarray.append(arrayofsubsection2[0])
	del arrayofsubsection2[0]
		
	


htmlCode = "<!DOCTYPE html><html lang='en'><head><title>" + title +"</title></head>"
htmlCode += "<body align='center'><h1>"+ title + " </h1>"
htmlCode += "<h4> <ul style= 'list-style-type:none'> <li>" + authorname[0] +" | " + authorollNos[0] + "</li>"
htmlCode += "<li>" + authorname[1] +" | " + authorollNos[1] + "</li>"
htmlCode += "<li>"+ authorname[2] +" | " + authorollNos[2] + "</li></ul></h4>"
htmlCode += "<h4>"+ strftime("%B %d, %Y", gmtime()) +"</h4><hr/>"
#Check later
htmlCode += "<ol style='list-style-type:none' align='left'>"
htmlCode += "<li><h2>" +  sectionNames[3] + "</h2>"
htmlCode += "<ol><li><h3>" + subsectionName[0] +"</h3>"
htmlCode += "<p>" + observationsub1 + "</p>"
htmlCode += "<p>" + observationsub2 +"</p>"
htmlCode += "<p>" + observationsub3 +"</p>"
htmlCode += "<p>" + observationsub4 +"</p>"
htmlCode += "<li><h3>" + subsectionName[1] +"</h3>"
htmlCode += "<p>" + observationarray[0] + "</p>"
htmlCode += "<img src='images/release.png'></img>"
htmlCode += "<img src='images/debug.png'></img>"
htmlCode += "<p>" + observationarray[1] + "</p>"
htmlCode += "<img src='images/debug_part.png'></img>"
htmlCode += "</li></ol></body></html>"

file = open('doc/Report.html', "w")
file.write(htmlCode)
file.close()

