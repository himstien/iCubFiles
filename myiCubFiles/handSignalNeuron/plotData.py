import numpy as np
import matplotlib.pyplot as py
from copy import deepcopy
 
def plot_data(data):
  py.clf()
  py.plot(data)
  py.draw()
# py.savefig("data-%.8d.png"%counter)

py.ion()
fig = py.figure(1)
lp = fig.add_subplot(111)
if __name__ == "__main__":
	  counter = 0
	  while True:
	    try:
	      tmp = raw_input().strip().split()
	      data = deepcopy(np.array(tmp, dtype=np.double))
	    except EOFError:
	      print "Input has terminated! Exiting"
	      exit()
	    except ValueError:
	      print "Invalid input, skipping.  Input was: %s"%tmp
	      continue
 
	    print "Plotting plot number %d"%counter
	 #   py.figure(1)
	    lp.clear()	
	    l, = lp.plot(data)
	    l.set_ydata(data)		
	  #  plot_data(data)
	    fig.canvas.draw()	    
	    counter += 1

