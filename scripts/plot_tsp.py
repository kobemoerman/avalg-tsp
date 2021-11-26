import matplotlib.pyplot as plt
import numpy as np

def plotTSP(path, graph, initial_path=None):

	x = [graph[int(i)][0] for i in path]
	y = [graph[int(i)][1] for i in path]
	
	plt.plot(x, y, 'bo')
	plt.plot(x[0], y[0], 'ro')
	a_scale = float(max(x))/float(100)

	plt.arrow(x[-1], y[-1], (x[0] - x[-1]), (y[0] - y[-1]), head_width = a_scale, 
			color ='black', length_includes_head=True)

	for i in range(0,len(x)-1):
		plt.arrow(x[i], y[i], (x[i+1] - x[i]), (y[i+1] - y[i]), head_width = a_scale,
				color = 'black', length_includes_head = True)

	if initial_path is not None:
		x = [graph[int(i)][0] for i in initial_path]
		y = [graph[int(i)][1] for i in initial_path]

		plt.arrow(x[-1], y[-1], (x[0] - x[-1]), (y[0] - y[-1]), head_width = a_scale, 
				color ='grey', length_includes_head=True,linestyle='dashed')

		for i in range(0,len(x)-1):
			plt.arrow(x[i], y[i], (x[i+1] - x[i]), (y[i+1] - y[i]), head_width = a_scale,
					color = 'grey', length_includes_head = True, linestyle='dashed')

	plt.xlim(0, max(x)*1.1)
	plt.ylim(0, max(y)*1.1)

	plt.show()


if __name__ == '__main__':

	path = np.loadtxt("path.dat").flatten()
	# initial_path = np.loadtxt("initPath.dat").flatten()
	graph = np.loadtxt("data/1000.in", skiprows=1).tolist()
		
	plotTSP(path, graph, initial_path)
