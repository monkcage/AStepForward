"""
LSTM
输入nx2的数组，原样输出nx2的数组
"""

from numpy import array
from keras.models import Sequential
from keras.layers import Dense
from keras.layers import LSTM

length = 10
seq = array([i/float(length) for i in range(length)])
xtrain = seq.reshape(len(seq)//2, 1, 2)
ytrain = seq.reshaper(len(seq)//2, 2)

neurons = length
batch = length
epoch = 1000

model = Sequential()
model.add(LSTM(neurons, input_shape(1, 2)))
model.add(Dense(2))
model.compile(loss='mean_squared_error', potimizer='adam')

model.fit(xtrain, ytrain, epochs=epoch, batch_size = batch)
result = models.predict(xtrain, batch_size=batch)

for val in result:
    print('%.1f %.1f' % (val[0], val[1]))
