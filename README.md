<!-- '''
    set xlabel "objs"\
    set ylabel "Time (us)"\
    set title "Python accesstime\
    set yrange [0:1]\
    f(x) = m*x + b\
    fit f(x) 'data.txt' using 1:2 via m,b\
    plot "data.txt" smooth csplines, "data.txt" with points\
''' -->

# A

To run my code,

```
    make
```
and then

```
    ./accesstime
```
    
I make a buffer of random bytes and an array of random indicies to read from that array. Then, I run 50 accesses, take the average acess time, and then average that access time over many iterations for each buffer size. See code for more details.

Here is an example run of the data

```
    1.024000    4.863281
    2.048000    4.833984
    4.096000    4.531250
    8.192000    4.516602
    16.384000    7.501221
    32.768000    6.900024
    65.536000    6.386108
    131.072000    10.808716
    262.144000    13.120728
    524.288000    14.538651
    1048.576000    22.864113
    2097.152000    23.456888
    4194.304000    35.102024

```
# B

See plot below. x acces is log scale

![This is an image](images/imageA.png)

# C

Just at face value, we would expect the graph to look something like a step function, and right off the bat we can see that mine does. 

Here are the stats of my machine.
```
    L1 Cache: 32 KB
    L2 Cache: 256 KB
    L3 Cache: 4 MB
```
This roughly makes sense when looking at the data and graph, as we see jumps near the 32 KB (L1 to L2) and 4 MB (L3 - main memory) marks. The jump from L2 to L3 seems to happen a bit early though. This may just be this particular run, but I also suspect that accessing the next index in our randomly generated ,although they are likely being prefetched (sequential accesses), the index array must also be occupying space in the cache. This method was the cleanest one I could find though.