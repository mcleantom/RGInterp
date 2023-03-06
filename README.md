# RGInterp

A multi-threaded regular grid interpolation library.

The usage is similar to scipy's regular grid interpolator:

Scipy:
```python
import numpy as np
from scipy.interpolate import RegularGridInterpolator

def f(x, y, z):
    return 2 * x**3 + 3 * y**2 - z

x = np.linspace(1, 4, 11)
y = np.linspace(4, 7, 22)
z = np.linspace(7, 9, 33)
xg, yg, zg = np.meshgrid(x, y, z, indexing='ij', sparse=True)
data = f(xg, yg, zg)

scipy_rgi = RegularGridInterpolator([x, y, z], data, method="linear")
```

RGInterp:
```python
import numpy as np
from rgi_interp_python import LinearInterpolator3D, CoordinateAxis, Grid3D

def f(x, y, z):
    return 2 * x**3 + 3 * y**2 - z

x = np.linspace(1, 4, 11)
y = np.linspace(4, 7, 22)
z = np.linspace(7, 9, 33)
xg, yg, zg = np.meshgrid(x, y, z, indexing='ij', sparse=True)
data = f(xg, yg, zg)

rgi_interp = LinearInterpolator3D(
    CoordinateAxis(1, 4, 11),
    CoordinateAxis(4, 7, 22),
    CoordinateAxis(7, 9, 33),
    Grid3D(data, float("inf"), "Data")
)
```

However, the performance is improved:
```python
N = int(1e7)
x_test = np.linspace(1, 4, N)
y_test = np.linspace(4, 7, N)
z_test = np.linspace(7, 9, N)
test_points = np.vstack((x_test, y_test, z_test)).T

n_starts = 10
Timer(lambda: scipy_rgi(test_points)).timeit(number=n_starts)
Timer(lambda: rgi_interp.interpolate(x_test, y_test, z_test)).timeit(number=n_starts)
```

In this example, on my setup, scipy interpolated 10 million points, 10 times in 10.58 seconds. RGInterp performed the 
same calculation in 0.17 seconds, a 62x speedup.