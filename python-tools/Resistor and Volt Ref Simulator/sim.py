"""
A voltage reference and resistive divider accuracy calculator for the feedback
section of a power supply. Other features may be added later.

This program works on the command line. Commands are all put on ARGV, then
the results are printed out.

Example usage:

    Simulate a 3.3V power supply using 0.8V +/-2% reference. 
    $ python sim.py Mode=FB R1="31.6k 0.5%" R2="10k 0.5%" Vref="0.8V 2%" Vnom="3.3V"

    R1: 31.442K <= 31.6K <= 31.758K
    R2: 9.95K <= 10.0K <= 10.05K
    Vref: 784.0mV <= 800.0mV <= 816.0mV
    Vout: 3.23923V <= 3.32186V <= 3.40448V
    Range: +/-2.487%
    Nom. voltage: 3.3V
    Deviation from nom.: -1.84% +3.17%

    Calculate the accuracy of a TL431B (+/-0.5%) shunt reg when using +/-0.1% 
    resistors, and calculate the deviation from a 3V nominal voltage.
	$ python sim.py Mode=FB R1="6.34k 0.1%" R2="31.6k 0.1%" Vref="2.495V 0.5%" Vnom="3V"

    R1: 6.33366K <= 6.34K <= 6.34634K
    R2: 31.5684K <= 31.6K <= 31.6316K
    Vref: 2.48253V <= 2.495V <= 2.50748V
    Vout: 2.97971V <= 2.99409V <= 3.00847V
    Range: +/-0.480%
    Nom. voltage: 3.0V
    Deviation from nom.: -0.68% +0.28%

Copyright (C) 2010 Thomas Oldbury. This is GPLv2 software.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
"""

import sys, math, re

class SimValueAndTolerance(object):
    def __init__(self, value, tolerance):
        assert 0.0 <= tolerance <= 1.0 
        self.value = value
        self.tolerance = tolerance # as a fraction
    def nomval(self):
        return self.value
    def minval(self):
        return self.value * (1 - self.tolerance)
    def maxval(self):
        return self.value * (1 + self.tolerance)
    def tol(self):
        return self.tolerance
    def step_range(self, steps):
        frac = float(self.maxval() - self.minval()) / steps
        x = self.minval()
        vals = [0] * steps
        for v in range(steps):
            vals[v] = x
            x += frac
        return vals
    def __repr__(self):
        return "<%s nomval=%f minval=%f maxval=%f tol=%f%%>" % (type(self).__name__, self.nomval(), self.minval(), self.maxval(), self.tol() * 100.0)
    def __str__(self):
        return repr(self)

class SimValue(object):
    def __init__(self, value):
        self.value = value
    def getval(self):
        return self.value
    def __repr__(self):
        return "<%s val=%f>" % (type(self).__name__, self.getval())

class SimResistance(SimValueAndTolerance):
    """Resistance."""
    pass

class SimVoltageReference(SimValueAndTolerance):
    """Voltage Reference."""
    pass

class SimVoltage(SimValue):
    """Voltage."""
    pass

def metric_suffix(value, unit='', dp=3):
    # based partially on http://php.net/manual/en/function.filesize.php
    # by nak5ive at DONT-SPAM-ME dot gmail dot com 11-Jun-2009 05:59 
    # converted into Python
    assert value >= 1e-9 and value < 1e15
    suffixes = ['p', 'n', 'm', '', 'K', 'M', 'G', 'T']
    power = math.floor((math.log(value) if value > 0 else 0) / math.log(1000.0))
    power = min(power, len(suffixes) - 1)
    value /= pow(1000.0, power)
    return str(round(value, dp)) + suffixes[int(power + suffixes.index(''))] + unit

def metric_to_float(numstr):
    matches = re.match('([0-9.]+)(p|n|m|k|M|G)?', numstr).groups()
    suffixes = {'p': -9, 'n': -6, 'm': -3, '': 0, 'k': 3, 'M': 6, 'G': 9, 'T': 12}
    if not matches[1]:
        return float(matches[0])
    else:
        assert matches[1] in suffixes
        return float(matches[0]) * math.pow(10.0, suffixes[matches[1]])

def parse_arg_for_key(mode, key, value):
    if mode == "FB":
        if key in ["R1", "R2"]:
            valuestr, tolstr = value.split(' ')
            value = metric_to_float(valuestr)
            tol = float(re.match('([0-9.]+).*', tolstr).group(1))
            return SimResistance(value, tol / 100.0)
        elif key in ["Vref"]:
            valuestr, tolstr = value.split(' ')
            value = metric_to_float(valuestr)
            tol = float(re.match('([0-9.]+).*', tolstr).group(1))
            return SimVoltageReference(value, tol / 100.0)
        elif key in ["Vnom"]:
            value = metric_to_float(value)
            return SimVoltage(value)
    else:
        raise ValueError, "Invalid Mode attribute."

def parse_argv(argv_str):
    args = {}
    parsed_args = []
    mode = ""
    for arg in argv_str:
        key, value = arg.split('=', 2)
        if key == "Mode":
            mode = value
        else:
            parsed_args.append((key, value))
    if not mode:
        raise ValueError, "No Mode attribute specified."
    for k, v in parsed_args:
        args[k] = parse_arg_for_key(mode, k, v)
    args['Mode'] = mode
    return args

def reverse_divider(vout, r1, r2):
    """Calculate the Vin given R1, R2 and Vout for a resistive divider."""
    return (float(vout) / float(r1 + r2)) * r2

def forward_divider(vin, r1, r2):
    """Calculate the Vout given R1, R2 and Vin for a resistive divider."""
    return (float(r2) / float(r1 + r2)) * vin

def exec_sim(args):
    if args['Mode'] == 'FB':
        # Feedback simulation. A linear or switching power supply with feedback.
        try_r1 = args['R1'].step_range(10)
        try_r2 = args['R2'].step_range(10)
        try_vref = args['Vref'].step_range(10)
        min_vout = None
        max_vout = None
        for r1 in try_r1:
            for r2 in try_r2:
                for vref in try_vref:
                    calc_vout = vref * (vref / reverse_divider(vref, r1, r2))
                    #print(vref, r1, r2)
                    #print(calc_vout)
                    if min_vout == None or min_vout[0] > calc_vout:
                        min_vout = [calc_vout, r1, r2]
                    if max_vout == None or max_vout[0] < calc_vout:
                        max_vout = [calc_vout, r1, r2]
        return min_vout, max_vout

if __name__ == '__main__':
    print
    print "Tom's Accuracy Simulator"
    print 
    print "Copyright (C) 2010 Thomas Oldbury. This is GPLv2 software."
    print 
    print "This program is distributed in the hope that it will be useful,"
    print "but WITHOUT ANY WARRANTY; without even the implied warranty of"
    print "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the"
    print "GNU General Public License for more details."
    print
    # main application
    if sys.argv[0] == "python":
        args = parse_argv(sys.argv[2:])
    else:
        args = parse_argv(sys.argv[1:])
    res = exec_sim(args)
    if args['Mode'] == 'FB':
        min_volts = res[0][0]
        avg_volts = (res[0][0] + res[1][0]) / 2
        max_volts = res[1][0]
        perc = 100.0 * (float(max_volts - avg_volts) / avg_volts)
        print("R1: %s <= %s <= %s" % (metric_suffix(args['R1'].minval(), '', 5), \
                                      metric_suffix(args['R1'].nomval(), '', 5), \
                                      metric_suffix(args['R1'].maxval(), '', 5)))
        print("R2: %s <= %s <= %s" % (metric_suffix(args['R2'].minval(), '', 5), \
                                      metric_suffix(args['R2'].nomval(), '', 5), \
                                      metric_suffix(args['R2'].maxval(), '', 5)))
        print("Vref: %s <= %s <= %s" % (metric_suffix(args['Vref'].minval(), 'V', 5), \
                                        metric_suffix(args['Vref'].nomval(), 'V', 5), \
                                        metric_suffix(args['Vref'].maxval(), 'V', 5)))
        print("Vout: %s <= %s <= %s" % (metric_suffix(min_volts, 'V', 5), \
                                        metric_suffix(avg_volts, 'V', 5), \
                                        metric_suffix(max_volts, 'V', 5)))
        print("Range: +/-%3.3f%%" % perc)
        # If nominal voltage present then use that to calculate +x -y percentages.
        if 'Vnom' in args:
            nom = args['Vnom'].value
            _min = round(((nom - min_volts) / nom) * 100, 2)
            _max = round(((max_volts - nom) / nom) * 100, 2)
            print("Nom. voltage: %s" % metric_suffix(nom, 'V', 5))
            print("Deviation from nom.: -%s%% +%s%%" % (_min, _max))

