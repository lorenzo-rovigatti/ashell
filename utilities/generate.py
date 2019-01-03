#!/usr/bin/env python

import sys
import random
import os
import numpy as np
import subprocess as sp
import math
import itertools as it
from scipy.spatial import ConvexHull

def die(msg):
    print >> sys.stderr, msg
    sys.exit(1)

if len(sys.argv) < 2: die("Usage is %s mesh_points [add_params=False]" % sys.argv[0])

n_points = int(sys.argv[1])
if n_points < 100: die("Not enough mesh points (%d < 100)" % n_points)

add_params = False
if len(sys.argv) > 2:
    add_params = bool(sys.argv[2])

generate_sphere_path = os.path.join(os.path.dirname(sys.argv[0]), "generate_sphere")
gen = sp.Popen([generate_sphere_path, str(n_points)], stdout=sp.PIPE)
out, err = gen.communicate()

convex_points = []
min_dist_sqr = 10000.
for l in out.split("\n"):
    spl = l.split()
    if len(spl) == 3:
        new_p = np.array([float(x) for x in spl])
        new_p *= 0.5 / math.sqrt(np.dot(new_p, new_p))
        convex_points.append(new_p)
        if len(convex_points) > 1:
            diff = new_p - convex_points[0]
            dist_sqr = np.dot(diff, diff)
            if dist_sqr < min_dist_sqr:
                min_dist_sqr = dist_sqr
               
# convert to numpy arrays
points = np.array(convex_points)

# compute the convex hull of the ellipsoid. Note that since the ellipsoid is convex its convex hull will contain ALL its constituent points
cvx = ConvexHull(convex_points)
# now we can use cvx.simplices as a triangulation for the REAL points

print >> sys.stderr, "Triangulation completed"

# this lovely one-liner takes a list of triangles (identified by their three vertices) and transform it in the list of all the edges
edges = list(it.chain.from_iterable([it.combinations(t, 2) for t in cvx.simplices]))

length_factor = 0.8 / np.sqrt(min_dist_sqr)
print >> sys.stderr, "Volume and area of the convex hull:", cvx.volume * length_factor**3., cvx.area * length_factor**2.
with open("init_conf.dat", "w") as f:
    print >> f, 0
    print >> f, n_points
    print >> f, "cube 20"
    for p in points:
        p *= length_factor
        print >> f, p[0], p[1], p[2], np.random.normal(), np.random.normal(), np.random.normal()

with open("topology.dat", "w") as f:
    for e in edges:
        to_print = "%d %d %d" % (0, e[0], e[1])
        if add_params:
            diff = points[e[0]] - points[e[1]]
            dist = np.sqrt(np.dot(diff, diff))
            to_print += " %lf" % dist
        print >> f, "bond", to_print
        
    for t in cvx.simplices:
        to_print = "%d %d %d %d" % (0, t[0], t[1], t[2])
        if add_params:
            pass
        print >> f, "triangle", to_print

    for combination in it.combinations(cvx.simplices, 2):
        first = combination[0]
        second = combination[1]

        shared = []
        not_shared = list(set(list(first) + list(second)))
        for vertex in first:
            if vertex in second:
                shared.append(vertex)
                not_shared.remove(vertex)

        if len(shared) == 2:
            print >> f, "dihedral", 0, not_shared[0], shared[0], shared[1], not_shared[1]
