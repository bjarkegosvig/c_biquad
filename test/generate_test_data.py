import numpy as np
from scipy import signal
import matplotlib.pyplot as plt


fs = 48000
T = 0.001 # time in seconds
t = np.arange(0, int(T*fs)) / fs
x = signal.chirp(t, f0=200, f1=2000, t1=T, method='quadratic')

plt.plot(x)
sos = signal.iirfilter(1, Wn=200, btype='lowpass', analog=False, ftype='butter', fs=fs,
                       output='sos')

y = signal.sosfilt(sos,x)
plt.plot(y)
w, h = signal.sosfreqz(sos, 2000, fs=fs)
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
ax.semilogx(w, 20 * np.log10(np.maximum(abs(h), 1e-5)))
ax.set_title('Frequency response')
ax.set_xlabel('Frequency [Hz]')
ax.set_ylabel('Amplitude [dB]')
# ax.axis((10, 1000, -100, 10))
ax.grid(which='both', axis='both')
plt.show()


np.savetxt('sos.txt', sos, delimiter=', ', fmt='%.20f')
np.savetxt('input.txt', x, newline=', ', fmt='%.20f')
np.savetxt('ref.txt', y, newline=', ', fmt='%.20f')


