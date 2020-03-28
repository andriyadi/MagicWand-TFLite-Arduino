# Magic Wand with Machine Learning

Magic Wand using Arduino Nano 33 BLE Sense, powered by TensorFlow Lite for Microcontrollers and PlatformIO.

## Demo Video

Click the image to view video.

[![Demo video thumbnail](http://i3.ytimg.com/vi/Lfv3WJnYhX0/hqdefault.jpg)](https://www.youtube.com/watch?v=Lfv3WJnYhX0)

## Prerequisites

* [PlatformIO](http://platformio.org/)
* [platform-nordicnrf52](https://github.com/platformio/platform-nordicnrf52). Should be installed automatically, as it's specified in platformio.ini. Please note that I'm using `develop` version/branch.

## Train
You can train the Machine Learning model to recognize your own gesture, or even other gestures than Magic Wand. The model and  training code is [here](https://github.com/tensorflow/tensorflow/tree/master/tensorflow/lite/micro/examples/magic_wand/train).

I'm thinking to create some guideline to do that training in [Azure Machine Learning](https://azure.microsoft.com/en-us/services/machine-learning/), let me find the time.

## Credit

* [Magic Wand original sample code](https://github.com/tensorflow/tensorflow/tree/master/tensorflow/lite/micro/examples/magic_wand)
