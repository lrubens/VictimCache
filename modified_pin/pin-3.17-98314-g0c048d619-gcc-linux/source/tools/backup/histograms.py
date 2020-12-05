import matplotlib
matplotlib.use('Agg')
import numpy as np
import random
from matplotlib import pyplot as plt

data = np.random.normal(0, 20, 10) 

# fixed bin size
bins = np.arange(-100, 100, 5) # fixed bin size

#plt.xlim([min(data)-5, max(data)+5])

plt.hist(data, bins=bins, alpha=0.5)
#plt.savefig('ignore.jpg')
