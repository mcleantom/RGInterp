from skbuild import setup

setup(
    name="rgi_interp_python",
    version="0.0.10",
    packages=['rgi_interp_python'],
    package_dir={'': 'python'},
    cmake_install_dir='python/rgi_interp_python',
)