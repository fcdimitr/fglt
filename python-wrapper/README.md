# Install requirements
The use of a Virtual Environment is recommended for the steps below.

In order to run the `fglt()` C++ function we will need the [ctypes](https://docs.python.org/3/library/ctypes.html) and scipy libraries:

`pip install ctypes`

`pip install scipy`

The test matrix used in `demo.py` should be in `build/docs/GD96_c` if the previous instructions were followed. If not, feel free to specify your own file in `demo.py`. Then, you can run the demo with 

`python demo.py`