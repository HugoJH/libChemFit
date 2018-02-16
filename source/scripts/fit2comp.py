#!/usr/bin/env python

import numpy as np
from scipy.optimize import curve_fit
def LM2COMP(x,y, A0, B0,C0,D0):
	
	def func(x_, a, b, c, d):
	   return a*np.exp(-b*x_) + c*np.exp(-d*x_)

	popt, pcov = curve_fit(func, x, y, p0=(A0,B0,C0,D0), sigma=y)
	return popt.tolist()
