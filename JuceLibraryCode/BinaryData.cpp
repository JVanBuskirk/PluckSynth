/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

namespace BinaryData
{

//================== PluckSynthJuce.py ==================
static const unsigned char temp_binary_data_0[] =
"class Pluck(PyoObject):\r\n"
"    \"\"\"\r\n"
"    Pluck Physical Model\r\n"
"\r\n"
"    An implentation of the Karplus-Strong Algorithm\r\n"
"    \r\n"
"    :Parent: :py:class:'PyoObject'\r\n"
"    \r\n"
"    :Args:\r\n"
"        \r\n"
"        trig: PyoObject\r\n"
"            Trigger signal.  Generate the pluck.\r\n"
"        freq: float or PyoObject\r\n"
"            Frequency in cycles per second.\r\n"
"        dur: float or PyoObject\r\n"
"            Duration of each pluck.\r\n"
"        cut: float or PyoObject\r\n"
"            Cutoff frequency of low pass filter.\r\n"
"\r\n"
"\r\n"
"    >>> s = Server().boot()\r\n"
"    >>> s.start()\r\n"
"    >>> note = Notein(poly=10, scale=1)\r\n"
"    >>> osc = Pluck(trig = note['trigon'], freq=note['pitch'], dur=1, cut=5000, mul=0.8).out()\r\n"
"\r\n"
"    \"\"\"\r\n"
"    def __init__(self, trig, freq=220, dur=1, cut=7000, mul=1, add=0):\r\n"
"        PyoObject.__init__(self)\r\n"
"    \r\n"
"        self._trig = trig\r\n"
"        self._freq = freq\r\n"
"        self._dur = dur\r\n"
"        self._cut = cut\r\n"
"        self._mul = mul\r\n"
"    \r\n"
"        trig, freq, dur, cut, mul, add, lmax = convertArgsToLists(trig, freq, dur, cut, mul, add)\r\n"
"        \r\n"
"    \r\n"
"        self._table = WinTable(type = 3, size = 8192)\r\n"
"        self._env = TrigEnv(trig, table=self._table, dur = 0.01)\r\n"
"        self._noise = Noise(mul=self._env)\r\n"
"        self._wg = Waveguide(self._noise, freq, dur = dur)\r\n"
"        self._filter = Biquad(self._wg, cut, 1, 0, mul=mul, add=add)\r\n"
"\r\n"
"        self._base_objs = self._filter.getBaseObjects()\r\n"
"        \r\n"
"    def setFreq(self, x):\r\n"
"        \"\"\"\r\n"
"        Replace the 'freq' attribute\r\n"
"        \r\n"
"        :Args:\r\n"
"            x : float or PyoObject\r\n"
"                New 'freq' attribute.\r\n"
"                \r\n"
"        \"\"\"\r\n"
"        self._freq = x\r\n"
"        self._wg.freq = x\r\n"
"        \r\n"
"    def setDur(self, x):\r\n"
"        \"\"\"\r\n"
"        Replace the 'dur' attribute\r\n"
"        \r\n"
"        :Args:\r\n"
"            x : float or PyoObject\r\n"
"                New 'dur' attribute.\r\n"
"                \r\n"
"        \"\"\"\r\n"
"        self._dur = x\r\n"
"        self._wg.dur = x\r\n"
"        \r\n"
"    def setCut(self, x):\r\n"
"        \"\"\"\r\n"
"        Replace the 'cut' attribute\r\n"
"        \r\n"
"        :Args:\r\n"
"            x : float or PyoObject\r\n"
"                New 'cut' attribute.\r\n"
"                \r\n"
"        \"\"\"\r\n"
"        self._cut = x\r\n"
"        self._filter.freq = x\r\n"
"        \r\n"
"    @property\r\n"
"    def freq(self):\r\n"
"        \"\"\" float or PyoObject. Frequency of Pluck \"\"\"\r\n"
"        return self._freq\r\n"
"    @freq.setter\r\n"
"    def freq(self, x):\r\n"
"        self.setFreq(x)\r\n"
"        \r\n"
"    @property\r\n"
"    def dur(self):\r\n"
"        \"\"\" float or PyoObject. Duration of Pluck \"\"\"\r\n"
"        return self._dur\r\n"
"    @dur.setter\r\n"
"    def dur(self, x):\r\n"
"        self.setDur(x)\r\n"
"        \r\n"
"    @property\r\n"
"    def cut(self):\r\n"
"        \"\"\" float or PyoObject. Cutoff Frequency of Filter \"\"\"\r\n"
"        return self._cut\r\n"
"    @cut.setter\r\n"
"    def cut(self, x):\r\n"
"        self.setCut(x)\r\n"
"        \r\n"
"    \r\n"
"    def ctrl(self, map_list=None, title=None, wxnoserver=False):\r\n"
"        self._map_list = [SLMap(20., 20000., \"log\", \"freq\", self._freq),\r\n"
"                          SLMap(0.1, 10., \"lin\", \"dur\", self._dur),\r\n"
"                          SLMap(100., 15000., \"log\", \"cut\", self._cut),\r\n"
"                          SLMap(0., 1., \"lin\", \"mul\", self._mul)]\r\n"
"        PyoObject.ctrl(self, map_list, title, wxnoserver)\r\n"
"        \r\n"
"    def play(self, dur=0, delay=0):\r\n"
"        self._filter.play(dur, delay)\r\n"
"        return PyoObject.play(self, dur, delay)\r\n"
"\r\n"
"    def stop(self):\r\n"
"        self._filter.stop()\r\n"
"        return PyoObject.stop(self)\r\n"
"\r\n"
"    def out(self, chnl=0, inc=1, dur=0, delay=0):\r\n"
"        self._filter.play(dur, delay)\r\n"
"        return PyoObject.out(self, chnl, inc, dur, delay)\r\n"
"\r\n"
"dur = SigTo(1, 0.001, 1)\r\n"
"cut = SigTo(7000, 0.001, 7000)\r\n"
"amp = SigTo(0.4, 0.001, 0.4)\r\n"
"\r\n"
"note = Notein(poly=10, scale=1)\r\n"
"osc = Pluck(trig=note['trigon'], freq=note['pitch'], dur=dur, cut=cut, mul=amp)\r\n"
"mix = osc.mix(1)\r\n"
"pan = Pan(mix)\r\n"
"comp = Compress(pan, thresh=-20, ratio=6).out()\r\n";

const char* PluckSynthJuce_py = (const char*) temp_binary_data_0;


const char* getNamedResource (const char* resourceNameUTF8, int& numBytes)
{
    unsigned int hash = 0;
    if (resourceNameUTF8 != 0)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0xca020c60:  numBytes = 3889; return PluckSynthJuce_py;
        default: break;
    }

    numBytes = 0;
    return nullptr;
}

const char* namedResourceList[] =
{
    "PluckSynthJuce_py"
};

const char* originalFilenames[] =
{
    "PluckSynthJuce.py"
};

const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8)
{
    for (unsigned int i = 0; i < (sizeof (namedResourceList) / sizeof (namedResourceList[0])); ++i)
    {
        if (namedResourceList[i] == resourceNameUTF8)
            return originalFilenames[i];
    }

    return nullptr;
}

}
