from copy import copy, deepcopy

class FontParser(object):
    def __init__(self):
        self.char_dict = {}
        self.width = 5
        self.height = 5
    
    def parse(self, filename):
        fp = open(filename, 'r')
        # Read header.
        line = fp.readline()
        x, y = line[1:].split('x')
        self.width, self.height = int(x), int(y)
        while self.read_character(fp): pass
        self.output2()
    
    def read_character(self, fp):
        # Read character header.
        line = fp.readline()
        invert = False
        key = None
        if len(line) == 0:
            return False
        if line[0] == '.':
            if len(line) > 2 and line[-1] == '!':
                invert = True
            self.char_dict[line[1]] = []
            key = line[1]
        else:
            return False
        y = 0
        while y < self.height:
            line = fp.readline().rstrip()
            parsed = []
            for c in line:
                if c == '#':
                    parsed.append(1)
                else:
                    parsed.append(0)
            if len(parsed) < self.width:
                for n in range(len(parsed), self.width):
                    parsed.append(0)
            new_parsed = []
            if invert:
                for c in parsed:
                    new_parsed.append(1 - c)
            else:
                new_parsed = parsed[:]
            self.char_dict[key].append(new_parsed)
            y += 1
        return True
    
    def output(self):
        print self.char_dict
        chars = {}
        for idx in range(0, 256):
            zeroes = "0" * (self.width * self.height)
            chars[idx] = zeroes
        for char, data in self.char_dict.items():
            bits = ""
            for line in data:
                for bit in line:
                    bits += str(bit)
            chars[ord(char)] = bits
        binary = ""
        for bits in chars.values():
            binary += bits
        lines = ""
        ctr = 0
        for idx in range(0, len(binary), 8):
            ctr += 1
            byte = binary[idx:idx+8]
            byte = "0x%02x" % int(byte, 2)
            lines += byte + ", "
            if ctr % 8 == 0:
                lines += "\n"
        print(lines)
    
    def output2(self):
        # Second output, easier to code for.
        # Either:
        #   Each line occupies 2 bytes, so characters up to 16xN are supported.
        # or:
        #   Each line occupies a byte, so characters up to 8xN are supported.
        # The mode is selected depending on the width of the character.
        # N = number of lines in font (height.)
        empty_char = [[0] * self.width] * self.height
        for ch in range(256):
            och = chr(ch)
            if och not in self.char_dict:
                self.char_dict[och] = copy(empty_char)
        print self.char_dict
        output = ""
        # Iterate over the dictionary in order.
        for char in sorted(self.char_dict.iterkeys()):
            data = self.char_dict[char]
            for line in data:
                line_rev = copy(line)
                line_rev.reverse()
                binstr = "".join(map(str, line_rev))
                num = int(binstr, 2)
                if self.width > 8:
                    output += "0x%02x, 0x00, " % (num, num >> 8)
                else:
                    output += "0x%02x, " % (num)
            output = output[:-2]            
            output += ", // 0x%02x\n" % ord(char)
        print(output)

if __name__ == '__main__':
    f = FontParser()
    f.parse('font1.txt')

