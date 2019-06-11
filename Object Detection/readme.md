This folder contains the details and code for object recognition which is used in MARWIN.

# Installation

There are a number of methods that can be used to install TensorFlow, such as using pip to install the wheels available on PyPI. Installing TensorFlow using conda packages offers a number of benefits, including a complete package management system, wider platform support, a more streamlined GPU experience, and better CPU performance. These packages are available via the Anaconda Repository, and installing them is as easy as running ```conda install tensorflow``` or ```conda install tensorflow-gpu``` from a command line interface.

### Install [Anaconda](https://www.anaconda.com/distribution/) or [Miniconda](https://docs.conda.io/en/latest/miniconda.html) for better experience.

On Windows open the Start menu and open an Anaconda Command Prompt.

```
conda create --name tensorflow python=3.5
activate tensorflow
conda install jupyter
conda install scipy
pip install tensorflow
#or
#pip install tensorflow-gpu
```

### After installing [Anaconda](https://www.anaconda.com/distribution/) or [Miniconda](https://docs.conda.io/en/latest/miniconda.html), create a new conda environment containing TensorFlow and activate it

```
conda create -n tensorflow_env tensorflow
conda activate tensorflow_env
```

Or for the GPU version

```
conda create -n tensorflow_gpuenv tensorflow-gpu
conda activate tensorflow_gpuenv
```

TensorFlow is now installed and ready for use. 

### Install the packages one by one as per your requirement

when you rin the code and at the beginning of your code will be like this :

```
import numpy as np
import os
import six.moves.urllib as urllib
import sys
import tarfile
import tensorflow as tf
import zipfile

from collections import defaultdict
from io import StringIO
from matplotlib import pyplot as plt
from PIL import Image
```
This will show you which all packages do you need in the project working and you can install it usin ```pip``` commands.

### Incase you are having any issues in running the code it can be solved by installing the required packages or library in the folder where your code is placed.
