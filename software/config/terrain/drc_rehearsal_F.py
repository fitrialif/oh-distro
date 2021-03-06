import numpy as np

blockName = 'cinderblock'
blockSize = np.array([15 + 5/8.0, 15 + 3/8.0, 5 + 5/8.0]) * 0.0254 # meters
blockTiltAngle = 15 # degrees


# F=sloping up forward (+x), B=sloping up backward (-x),
# R=sloping up rightward (-y), L=sloping up leftward (+y)
# last row is closest to robot (robot is on bottom looking up)
# column order is left-to-right on robot (+y to -y)
blockTypes = [
    [ 'N', 'N', 'N', 'N' ],
    [ 'F', 'R', 'B', 'L' ],
    [ 'R', 'B', 'L', 'F' ],
    [ 'N', 'N', 'N', 'N' ],
    [ 'L', 'F', 'R', 'B' ],
    [ 'F', 'R', 'B', 'L' ]
]
blockTypes.reverse()

# 0=ground level, 1=one cinderblock offset, etc
blockLevels = [
    [ -0.9, -0.9, -0.9, -0.9 ],
    [ 0, 0, 0, 0 ],
    [ 0, 0, 0, 0 ],
    [ 1, 1, 1, 1 ],
    [ 0, 0, 0, 0 ],
    [ 0, 0, 0, 0 ]
]
blockLevels.reverse()

# map between block types and (pitch,yaw) angles (degrees)
blockAngleMap = { 'F': (15,180), 'B': (15,0), 'R': (15,90), 'L': (15,270), 'N': (0,0) }

# TODO: this is just an example
# which foot, block (row,col), offset (x,y), support
# (row,col) refer to which block
# (x,y) are offsets wrt the block center, in meters
# support is an enum indicating foot support type
#   0=heel-toe, 1=midfoot-toe, 2=heel-midfoot
footstepData = [
    [ 'right', (0,1), (-0.05, 0.08),  0 ],
    [ 'left',  (0,0), (0.14, -0.11),  2 ],
    [ 'right', (1,1), (-0.02, 0.12),  0 ],
    [ 'left',  (1,0), (0.04, -0.07),  0 ],
    [ 'right', (2,1), (-0.05, 0.11),  0 ],
    [ 'left',  (2,0), (0.0, -0.08),   0 ],
    [ 'right', (2,1), (0.06, 0.11),   0 ],
    [ 'left',  (3,0), (-0.03, -0.11), 0 ],
    [ 'right', (3,1), (0.03, 0.10),   0 ],
    [ 'left',  (4,0), (-0.02, -0.10), 0 ],
    [ 'right', (4,1), (0.14, 0.07),   2 ],
    [ 'left',  (5,0), (-0.02, -0.12), 0 ],
    [ 'right', (5,1), (0.05, 0.07),   0 ],
]

numSteps = [7, -1]

# where to stand, relative to front of first block
startingPosition = np.array([-0.39, 0.4, 0])
startingYaw = 0   # degrees

# whether to lock lateral footstep offset
forceZeroLateralFootstepOffset = False

blockColor = [0.4, 0.6, 0.4]
blockColorMatched = [0.5, 0.8, 0.5]
