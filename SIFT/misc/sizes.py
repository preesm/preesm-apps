#! /usr/bin/python3

from math import *
from sympy import divisors

img_width = 800 #3840#
img_height = 640 #2400#

nLayers = 3
imgDouble = 1

# comes from https://github.com/pts/py-intersect-sorted/blob/master/intersect_sorted.py
def intersect_sorted(a1, a2):
    """Yields the intersection of sorted lists a1 and a2, without deduplication.
  Execution time is O(min(lo + hi, lo * log(hi))), where lo == min(len(a1),
  len(a2)) and hi == max(len(a1), len(a2)). It can be faster depending on
  the data.
  """
    import bisect
    s1, s2 = len(a1), len(a2)
    i1 = i2 = 0
    if s1 and s1 + s2 > min(s1, s2) * log(max(s1, s2)) * 1.4426950408889634:
        bi = bisect.bisect_left
        while i1 < s1 and i2 < s2:
            v1, v2 = a1[i1], a2[i2]
            if v1 == v2:
                yield v1
                i1 += 1
                i2 += 1
            elif v1 < v2:
                i1 = bi(a1, v2, i1)
            else:
                i2 = bi(a2, v1, i2)
    else:  # The linear solution is faster.
        while i1 < s1 and i2 < s2:
            v1, v2 = a1[i1], a2[i2]
            if v1 == v2:
                yield v1
                i1 += 1
                i2 += 1
            elif v1 < v2:
                i1 += 1
            else:
                i2 += 1


def good_octave(nOctaves):
    for i in range(1,nOctaves):
        if img_width % 2**i != 0 or img_height % 2**i != 0:
            break
    octaveMax = i + imgDouble
    if octaveMax < imgDouble+3:
        raise Exception("The size is not enough divisible by two (nOctaves = {})".format(nOctaves))
    print("!!! The original octave ({}) was too large, so we computed a new one.".format(nOctaves))
    return octaveMax
                

def geo_sum_inv(a, r, i):
    if r <= 1:
        raise Exception("This method is intended to be called with a ratio strictly greater than 1 (that then will be inverted).")
    tot = a
    reduceda = a
    for index in range(1,i):
        reduceda //= r
        tot += reduceda
    return tot


if __name__ == '__main__':
    nGpyrLayers = nLayers + 3
    nDogLayers = nGpyrLayers - 1
    nOctaves = floor(log2(min(img_height, img_width)) - 3 + imgDouble)

    if imgDouble == 1:
        divisionH = img_height % (2**(nOctaves-2))
        divisionW = img_width % (2**(nOctaves-2))
    else:
        divisionH = img_height % (2**(nOctaves-1))
        divisionW = img_width % (2**(nOctaves-1))

    if (divisionH != 0 or divisionW != 0):
        nOctaves = good_octave(nOctaves)
        
    gRmax = 1.0
    tmpGrMax = 3.0*1.6*sqrt(2.0**((2.0*(nGpyrLayers-1))/nLayers)-2.0**((2.0*(nGpyrLayers-2))/nLayers))
    if tmpGrMax > 1.0:
        gRmax = ceil(tmpGrMax)
    gWmax = 2*gRmax+1

    if imgDouble == 1:
        totSizeWithoutLayers = geo_sum_inv(4*img_width*img_height,4,nOctaves)
    else:
        totSizeWithoutLayers = geo_sum_inv(img_width*img_height,4,nOctaves)

    totSizeDog = totSizeWithoutLayers * nDogLayers
    totSizeGrdAndDetect = totSizeWithoutLayers * nLayers

    divisorsDog = divisors(totSizeDog)
    divisorsGrdAndDetect = divisors(totSizeGrdAndDetect)
    divisorsImage = divisors(img_height)
    
    commonDivisors = list(intersect_sorted(divisorsImage, divisorsGrdAndDetect))
    commonDivisors = list(intersect_sorted(commonDivisors,divisorsDog))

    maxTotalTasks = max(commonDivisors) * ((1 + nGpyrLayers*2)*(1+imgDouble) + 4) + (1+imgDouble)*nGpyrLayers*2 + (nOctaves - 1 - imgDouble)*(1 + nGpyrLayers) + 10
    print("Size: {} x {}".format(img_width, img_height))
    print("Layers: {} (gpyr: {}, dog: {})".format(nLayers, nGpyrLayers, nDogLayers))
    print("Stencil width: {}".format(gWmax))
    print("Octaves: {}".format(nOctaves))
    print("Tot size without layers: {}".format(totSizeWithoutLayers))

    print("Tot size Dog: {}\n(divisors: {})".format(totSizeDog, divisorsDog))
    print("Tot size Grd and Detect: {}\n(divisors: {})".format(totSizeGrdAndDetect, divisorsGrdAndDetect))
    print("Common divisors: {}".format(commonDivisors))
    print("Max tot tasks (approximatively): {}".format(maxTotalTasks))
    
