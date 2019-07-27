from resnet import resnet39
import tensorflow as tf
import numpy as np
from config import *


with tf.Session() as sess:
    model = resnet39(sess)
    inputs = np.random.rand(4, N, N, 17)
    outputs = np.random.rand(4, N*N+1)
    model.train(inputs, outputs)
    print(tf.convert_to_tensor(model.predict(inputs)).get_shape())
