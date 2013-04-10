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
		
	


'''

#########################################subsection 2#######################################




observationsub1 = re.sub("    {Observation}     ","",observationsub1)
explanationsub1 = ""
explanationsub1 = re.sub("   {Explanation} ","",arrayofsubsection[2])
explanationsub1part1 = arrayofsubsection[19]

word1="}}"
codesub1 = ""
i = 4

while(not (word1 in arrayofsubsection[i])):
	codesub1 += arrayofsubsection[i] + '\n'
	i=i+1
	
codesub1 += '  }'
codesub1 = re.sub("<","<<arbit>",codesub1)
#print(codesub1)

##subsection 2

subsection2 = section1["Errors in the step time averaged over all reruns for various iteration values. "]
subsection2=re.sub("\\\\_","_",subsection2)
subsection2=re.sub("\\\\&","&",subsection2)
subsection2=re.sub("\\\\[a-z]*","",subsection2)
subsection2=re.sub("\$","",subsection2)

observationsub2 = ""
arrayofsubsection2 = subsection2.split('\n')
observationsub2 = arrayofsubsection2[1]
observationsub2 = re.sub("   {Observation}    ","",observationsub2)
explanationsub2 = arrayofsubsection2[6]
explanationsub2 = re.sub("   {Explanation}     ","",explanationsub2)

#print(explanationsub2)

subsection3 = ""
subsection3 = section1["Values of times before and after adding load"]

subsection3=re.sub("\\\\[a-z]*","",subsection3)
subsection3=re.sub("\$","",subsection3)

arrayofsubsection3 = subsection3.split('\n')
observationsub3 = arrayofsubsection3[1]
observationsub3 = re.sub("    {Observation}    ","",observationsub3)
explanationsub3 = arrayofsubsection3[2]
explanationsub3 = re.sub("   {Explanation}    ","",explanationsub3)

#print(observationsub1)

#print(explanationsub1)


########################################################################################################
#section2.py


section2 = section["Difference between time and gettimeofday"]
section2=re.sub("\\\\_","_",section2)
section2=re.sub("\\\\&","&",section2)
section2=re.sub("\\\\[a-z]*","",section2)
section2=re.sub("{0.1cm}","",section2)
section2=re.sub("{blue}{","",section2)
section2=re.sub("\$","",section2)

data1=section2.split('\n')
#titleofsection=""
lengthofdata1 = len(data1)

#titleofsection=re.sub("{","",data1[0])
#titleofsection=re.sub("}","",titleofsection)
contentfromsection2 = ""
contentfromsection2 = data1[1] + '\n' + data1[2]+ '\n' + data1[3]
contentfromsection2 = re.sub("   ",":",contentfromsection2)
contentfromsection2 = re.sub("are:","are:<br/>",contentfromsection2)
contentfromsection2 = re.sub("ms","ms<br/>",contentfromsection2)

codefromsection2 = ""
i=5

while(i!=len(data1)-1):
	codefromsection2 = codefromsection2 + data1[i] + '\n'
	i+=1

codefromsection2 = re.sub("}}","}",codefromsection2)
codefromsection2 = re.sub("<<","<<<arbit>",codefromsection2)
'''

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
htmlCode += "<img src='release.png'></img>"
htmlCode += "<img src='debug.png'></img>"
htmlCode += "<p>" + observationarray[1] + "</p>"
htmlCode += "<img src='debug_part.png'></img>"
htmlCode += "</li></ol></body></html>"
'''
htmlCode += "<pre style='font-style:italic; color:blue;'>"
htmlCode += codesub1 + "</pre>"
htmlCode += "<img src='../plots/g22_lab09_plot01.png'></img>"
htmlCode += "<p>" + explanationsub1part1 +  "</p>"
htmlCode += "</p></p></li><li><h3>" + subsectionName[1] + "</h3><p>"
htmlCode += "<span style='font-weight:bold;'> Observation :</span>"
htmlCode += observationsub2 + "</p><p>"
htmlCode += "<span style='font-weight:bold;'> Explanation :</span>"
htmlCode += explanationsub2 + "<p>"
htmlCode += "<img src='../plots/g22_lab09_plot05.png'></img>"
htmlCode += "</p></p></li><li><h3>" + subsectionName[2] +"</h3>"
htmlCode += "<p><span style='font-weight:bold;'> Observation :</span>"
htmlCode += observationsub3
htmlCode += "</p><p><span style='font-weight:bold;'> Explanation :</span>"
htmlCode += explanationsub3
htmlCode += "<p><img align='center' src='../plots/hardcoded_plot1.png'></img>"
htmlCode += "<p align='center'> Figure 1: after load </p>"
htmlCode += "<img align='center' src='../plots/hardcoded_plot2.png'></img>"
htmlCode += "<p align='center'> Figure 2: before load </p></p></p></li></ol></li>"
htmlCode += "<li><h2> 2. "+ sectionNames[1]+"</h2>"
htmlCode += "<p>" + contentfromsection2
htmlCode += "</p><pre style='font-style:italic; color:blue;'>"
htmlCode += codefromsection2
htmlCode += "</pre></li></ol></body></html>"
'''
file = open('doc/g22_lab09_report.html', "w")
file.write(htmlCode)
file.close()

