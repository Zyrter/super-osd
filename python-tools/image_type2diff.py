#!/usr/bin/python
import Image

bitflips = []

def binary(n, digits=8):
    # http://www.daniweb.com/code/snippet216539.html
    rep = bin(n)[2:]
    return ('0' * (digits - len(rep))) + rep

for b in range(256):
    bitrep = binary(b, 8)[::-1]
    bitflips.append(int(bitrep, 2))

def encode(pix):
    i = 1
    x = 0
    for n in pix:
        if n:
            x |= i
        i <<= 1
    return x

def compress_image(img1, img2):
    print "\t",
    w, h = img1.size
    binary = []
    if w != 256 or h != 192:
        raise ValueError, "image not exactly 256x192 pixels"
    assert(img1.size == img2.size)
    repcount = 0
    lastpix = 0
    data = []
    for y in range(h):
        for x in range(0, w, 16):
            pix1 = []
            pix2 = []
            for i in range(8):
                a = img1.getpixel((x + i, y))[0]
                b = img2.getpixel((x + i, y))[0]
                pix1.append(1 - int(abs(a - b) <= 127))
            for i in range(8):
                a = img1.getpixel((x + 8 + i, y))[0]
                b = img2.getpixel((x + 8 + i, y))[0]
                pix2.append(1 - int(abs(a - b) <= 127))
            data.append(encode(pix2[::-1]))
            data.append(encode(pix1[::-1]))
    for pix in data: 
        #binary.append(pix)
        if pix != lastpix or repcount >= 255:
            binary.append(repcount)
            binary.append(lastpix)
            repcount = 1
            lastpix = pix
        elif pix == lastpix:
            repcount += 1
    k = 1
    print ".byte\t",
    for bd in binary:
        if isinstance(bd, tuple) and bd[0] == -1:
        #    print "// line %d" % bd[1]
            continue
        if k % 8 != 0:
            print "0x%02x," % bd, 
        if k % 8 == 0:
            print "0x%02x" % bd, 
            print "\n\t\t\t.byte\t",
        k += 1
    print 
    print "\t\t\t// %d bytes " % len(binary) 

if __name__ == '__main__':
    for frame in range(18):
        compress_image(Image.open('splash-fr%d.png' % frame), Image.open('splash-fr%d.png' % (frame + 1)))
