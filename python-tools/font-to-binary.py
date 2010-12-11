#!/usr/bin/python
# Convert a font to a C data structure.
# Structure supports up to 254 distinct characters.
# Only works up to a maximum width of 8 pixels at the moment.
import pygame, os

def sort_dict(_dict):
    # http://corykrug.com/2007/08/13/sorting-dictionaries-in-python/
    new_dict = {}
    sorted_keys = _dict.keys()
    sorted_keys.sort()
    for key in sorted_keys:
        new_dict[key] = _dict[key]
    return new_dict

class FontToBin(object):
    def __init__(self, font_name, simple_name):
        self.font_name = font_name
        self.simple_name = simple_name
        self.chars = {}
        self.font_size = self.get_font_size()
    
    def get_font_size(self):
        # Find the space character (should always be present) and get the dimensions of the font.
        spacechar = self.find_char(32)
        size = pygame.image.load(spacechar).get_size()
        return size
    
    def find_char(self, char):
        num_path = self.font_name + "/char_x" + str(int(char)) + ".png"
        if char >= 32 and char != 127:
            char_path = self.font_name + "/char_" + chr(char) + ".png"
        else:
            char_path = num_path
        if os.path.isfile(char_path):
            return char_path
        elif os.path.isfile(num_path):
            return num_path
        else:
            return None
    
    def read_char(self, fpath):
        data = [0x00] * (self.font_size[1] * 2)
        # Read the image surface.
        surf = pygame.image.load(fpath)
        idx = 0
        # Add mask bits first.
        for y in range(self.font_size[1]):
            byte = 0x00
            for x in range(self.font_size[0]):
                xr = self.font_size[0] - x - 1
                pix = surf.get_at((xr, y))
                if pix[0] >= 100 and pix[0] <= 200:
                    bit = 0
                else:
                    bit = 1
                byte |= bit << x
            data[idx] = byte
            idx += 1
        # Then add level bits.
        for y in range(self.font_size[1]):
            byte = 0x00
            for x in range(self.font_size[0]):
                xr = self.font_size[0] - x - 1
                pix = surf.get_at((xr, y))
                if pix[0] >= 150:
                    bit = 1
                else:
                    bit = 0
                byte |= bit << x
            data[idx] = byte
            idx += 1
        return data
    
    def create_font_struct(self):
        n = 0
        char_count = 0
        for i in range(0, 256):
            char = self.find_char(i)
            if char:
                self.chars[i] = (n, char)
                char_count += 1
            n += 1
        # Create entry lookup table.
        n = 0
        print "const char font_lookup_%s[256] = {\n\t" % self.simple_name,
        for i in range(0, 256):
            if i == 255: comma = ""
            else: comma = ","
            if i in self.chars:
                print "0x%02x%s" % (n, comma),
                n += 1
            else:
                print "0xff%s" % comma, # 0xff is reserved 
            if i != 255 and (i + 1) % 8 == 0: 
                print "\n\t",
        print "\n};"
        print
        # Create font data table.
        print "const char font_data_%s[] = {\n" % self.simple_name,
        for ch in sorted(self.chars.iterkeys()):
            data = self.chars[ch]
            print "\t",
            seq, fname = data
            # Open the character and extract the binary data.
            lines = self.read_char(fname)
            for idx, byte in enumerate(lines):
                print "0x%02x," % byte,
                if idx == self.font_size[1] - 1:
                    print "\n\t",
            print "// 0x%02x" % ch
        print "\n};"

if __name__ == '__main__':
    fb = FontToBin('NewFont - Outlined2 (8x8)', 'outlined8x8')
    fb.create_font_struct()

