from resnet import resnet39
import tensorflow as tf
import numpy as np
from config import *
import time


with tf.Session() as sess:
    model = resnet39(sess)
    for i in range(10):
        inputs = np.random.rand(500, CHANNEL, N, N)
        outputs = np.random.rand(500, N*N+1)
        start = time.time()
        model.train(inputs, outputs)
        print(time.time() - start)
