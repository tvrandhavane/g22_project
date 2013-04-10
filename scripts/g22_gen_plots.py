import numpy
import matplotlib.pyplot as plotter
import math

data = numpy.genfromtxt('data/lab09_g22_data.csv', dtype=None, delimiter=',', 
						names=['reruns', 'iterations', 'stepTime', 'colTime', 'velTime','posTime','loopTime'])



#step time averaged over all reruns (Y) for various iteration values (X)
avgStepTime = numpy.zeros(100)
stdDevs = numpy.zeros(100)
x = numpy.zeros(100)

for i in range(0,10000):
	avgStepTime[data['iterations'][i] - 1] += data['stepTime'][i]

for i in range(0,100):
	avgStepTime[i] = avgStepTime[i]/100
	x[i] = i + 1

for i in range(0, 10000):
	value = data['stepTime'][i] - avgStepTime[data['iterations'][i] - 1]
	stdDevs[data['iterations'][i] - 1] += value * value

for i in range(0, 100):
	stdDevs[i] = stdDevs[i]/100
	stdDevs[i] = math.sqrt(stdDevs[i])

#loop time averaged over all reruns (Y) for various iteration values (X)
avgLoopTime = numpy.zeros(100)
for i in range(0,10000):
	avgLoopTime[data['iterations'][i] - 1] += data['loopTime'][i]

for i in range(0,100):
	avgLoopTime[i] = avgLoopTime[i]/100

#collision time averaged over all reruns (Y) for various iteration values (X)
avgColTime = numpy.zeros(100)
for i in range(0,10000):
	avgColTime[data['iterations'][i] - 1] += data['colTime'][i]

for i in range(0,100):
	avgColTime[i] = avgColTime[i]/100

#velocity time averaged over all reruns (Y) for various iteration values (X)
avgVelTime = numpy.zeros(100)
for i in range(0,10000):
	avgVelTime[data['iterations'][i] - 1] += data['velTime'][i]

for i in range(0,100):
	avgVelTime[i] = avgVelTime[i]/100

#position time averaged over all reruns (Y) for various iteration values (X)
avgPosTime = numpy.zeros(100)
for i in range(0,10000):
	avgPosTime[data['iterations'][i] - 1] += data['posTime'][i]

for i in range(0,100):
	avgPosTime[i] = avgPosTime[i]/100

#plot1
plotter.plot(x,avgStepTime, 'r.', x, avgLoopTime, 'b.')
plotter.legend(('Step Time','Loop Time'), loc=2)
plotter.ylabel('time averaged over all reruns') 
plotter.xlabel('iteration values')
plotter.title('Loop time and Step time vs iteration values')
plotter.savefig('plots/g22_lab09_plot01.png')
plotter.clf()

#plot5
plotter.errorbar(x, avgStepTime, yerr=stdDevs, xerr=None, marker='.', linestyle='None')
plotter.legend(('Average step time','Error in step time'), loc=2)
plotter.ylabel('Step time averaged over all reruns') 
plotter.xlabel('iteration values')
plotter.title('Step time vs iteration values')
plotter.savefig('plots/g22_lab09_plot05.png')
plotter.clf()

#plot2
plotter.plot(x,avgStepTime, 'b.', x, avgColTime, 'rx', x, avgPosTime, 'g.', x, avgVelTime, 'y.')
plotter.legend(('Step Time','Collision Time', 'Position Time', 'Velocity Time'), loc=2)
plotter.ylabel('time averaged over all reruns') 
plotter.xlabel('iteration values')
plotter.title('Step time, Velocity time, Collision time and Position time vs iteration values')
plotter.savefig('plots/g22_lab09_plot02.png')
plotter.clf()

#step time averaged over all iterations (Y) for various rerun values (X)
avgStepTime = numpy.zeros(100)
for i in range(0,100):
	lower = i*100
	upper = i*100 + 99
	avgStepTime[i] = numpy.average(data['stepTime'][lower:upper])

#loop time averaged over all iterations (Y) for various rerun values (X)
avgLoopTime = numpy.zeros(100)
for i in range(0,100):
	lower = i*100
	upper = i*100 + 99
	avgLoopTime[i] = numpy.average(data['loopTime'][lower:upper])

#loop time averaged over all iterations (Y) for various rerun values (X)
avgColTime = numpy.zeros(100)
for i in range(0,100):
	lower = i*100
	upper = i*100 + 99
	avgColTime[i] = numpy.average(data['colTime'][lower:upper])

#loop time averaged over all iterations (Y) for various rerun values (X)
avgPosTime = numpy.zeros(100)
for i in range(0,100):
	lower = i*100
	upper = i*100 + 99
	avgPosTime[i] = numpy.average(data['posTime'][lower:upper])

#loop time averaged over all iterations (Y) for various rerun values (X)
avgVelTime = numpy.zeros(100)
for i in range(0,100):
	lower = i*100
	upper = i*100 + 99
	avgVelTime[i] = numpy.average(data['velTime'][lower:upper])

#plot3
plotter.plot(x,avgStepTime, 'r.', x, avgLoopTime, 'b.')
plotter.legend(('Step Time','Loop Time'), loc=0)
plotter.ylabel('time averaged over all iterations') 
plotter.xlabel('rerun values')
plotter.title('Loop time and Step time vs rerun values')
plotter.savefig('plots/g22_lab09_plot03.png')
plotter.clf()

#plot4
plotter.plot(x,avgStepTime, 'b.', x, avgColTime, 'rx', x, avgPosTime, 'g.', x, avgVelTime, 'y.')
plotter.legend(('Step Time','Collision Time', 'Position Time', 'Velocity Time'), loc=0)
plotter.ylabel('time averaged over all iterations') 
plotter.xlabel('rerun values')
plotter.title('Step time, Velocity time, Collision time and Position time vs rerun values')
plotter.savefig('plots/g22_lab09_plot04.png')
plotter.clf()

#histogram
stepTimes = numpy.zeros(100)
for i in range(0,100):
	stepTimes[i] = data['stepTime'][7*i]

n, bins, patches = plotter.hist(stepTimes, 100, facecolor='b')
n, bins, patches = plotter.hist(stepTimes, 100,histtype = 'step', cumulative=True)
plotter.ylabel('Number of reruns') 
plotter.xlabel('step time')
plotter.title('Frequency plot of reruns vs step time')
plotter.savefig('plots/g22_lab09_plot06.png')
plotter.clf()
	


