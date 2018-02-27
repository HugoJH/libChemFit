#!/usr/bin/env python

import numpy as np
from scipy.optimize import curve_fit
def LMPARAMS(x,y, A0, B0):
    print(x)
    def func(x_, a, b):
       return a*np.exp(-b*x_)

    popt, pcov = curve_fit(func, x, y, p0=(A0,B0))
    return popt.tolist()
