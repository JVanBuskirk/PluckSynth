class Pluck(PyoObject):
    """
    Pluck Physical Model

    An implentation of the Karplus-Strong Algorithm
    
    :Parent: :py:class:'PyoObject'
    
    :Args:
        
        trig: PyoObject
            Trigger signal.  Generate the pluck.
        freq: float or PyoObject
            Frequency in cycles per second.
        dur: float or PyoObject
            Duration of each pluck.
        cut: float or PyoObject
            Cutoff frequency of low pass filter.


    >>> s = Server().boot()
    >>> s.start()
    >>> note = Notein(poly=10, scale=1)
    >>> osc = Pluck(trig = note['trigon'], freq=note['pitch'], dur=1, cut=5000, mul=0.8).out()

    """
    def __init__(self, trig, freq=220, dur=1, cut=7000, mul=1, add=0):
        PyoObject.__init__(self)
    
        self._trig = trig
        self._freq = freq
        self._dur = dur
        self._cut = cut
        self._mul = mul
    
        trig, freq, dur, cut, mul, add, lmax = convertArgsToLists(trig, freq, dur, cut, mul, add)
        
    
        self._table = WinTable(type = 3, size = 8192)
        self._env = TrigEnv(trig, table=self._table, dur = 0.01)
        self._noise = Noise(mul=self._env)
        self._wg = Waveguide(self._noise, freq, dur = dur)
        self._filter = Biquad(self._wg, cut, 1, 0, mul=mul, add=add)

        self._base_objs = self._filter.getBaseObjects()
        
    def setFreq(self, x):
        """
        Replace the 'freq' attribute
        
        :Args:
            x : float or PyoObject
                New 'freq' attribute.
                
        """
        self._freq = x
        self._wg.freq = x
        
    def setDur(self, x):
        """
        Replace the 'dur' attribute
        
        :Args:
            x : float or PyoObject
                New 'dur' attribute.
                
        """
        self._dur = x
        self._wg.dur = x
        
    def setCut(self, x):
        """
        Replace the 'cut' attribute
        
        :Args:
            x : float or PyoObject
                New 'cut' attribute.
                
        """
        self._cut = x
        self._filter.freq = x
        
    @property
    def freq(self):
        """ float or PyoObject. Frequency of Pluck """
        return self._freq
    @freq.setter
    def freq(self, x):
        self.setFreq(x)
        
    @property
    def dur(self):
        """ float or PyoObject. Duration of Pluck """
        return self._dur
    @dur.setter
    def dur(self, x):
        self.setDur(x)
        
    @property
    def cut(self):
        """ float or PyoObject. Cutoff Frequency of Filter """
        return self._cut
    @cut.setter
    def cut(self, x):
        self.setCut(x)
        
    
    def ctrl(self, map_list=None, title=None, wxnoserver=False):
        self._map_list = [SLMap(20., 20000., "log", "freq", self._freq),
                          SLMap(0.1, 10., "lin", "dur", self._dur),
                          SLMap(100., 15000., "log", "cut", self._cut),
                          SLMap(0., 1., "lin", "mul", self._mul)]
        PyoObject.ctrl(self, map_list, title, wxnoserver)
        
    def play(self, dur=0, delay=0):
        self._filter.play(dur, delay)
        return PyoObject.play(self, dur, delay)

    def stop(self):
        self._filter.stop()
        return PyoObject.stop(self)

    def out(self, chnl=0, inc=1, dur=0, delay=0):
        self._filter.play(dur, delay)
        return PyoObject.out(self, chnl, inc, dur, delay)

dur = SigTo(1, 0.001, 1)
cut = SigTo(7000, 0.001, 7000)
amp = SigTo(0.4, 0.001, 0.4)

note = Notein(poly=10, scale=1)
osc = Pluck(trig=note['trigon'], freq=note['pitch'], dur=dur, cut=cut, mul=amp)
mix = osc.mix(1)
pan = Pan(mix)
comp = Compress(pan, thresh=-20, ratio=6).out()
