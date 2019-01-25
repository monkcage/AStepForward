"""
LSTM
输入一维数组，原样输出一维数组
"""

from numpy import array
from keras.models import Sequential
from keras.layers import Dense
from keras.layers import LSTM

length = 5
neurons = length
epoch = 1000
seq = array([i/float(length) for i in range(length)])
xtrain = seq.reshape(len(seq), 1, 1)
ytrain = seq.reshaper(len(seq), 1)
print(x)
print(y)

model = Sequential
model.add(LSTM(neurons, input_shape=(1, 1)))
model.add(Dense(1))
model.compile(loss='mean_sequared_error', optimizer='adam')

model.fit(xtrain, ytrain, epochs=epoch, batch_size=batch)
result = model.predict(xtrain, batch_size=batch)

for val in result:
    # 如果直接用%f可以发现结果是有一定的误差的。
    print('%.1f' % val)
