---
title: '${\rm FG}_{\ell}{\rm T}$: Fast Graphlet Transform'
tags:
  - graphlet transform
  - graph analysis
  - network analysis
  - C++/C
  - Python
  - Julia
  - MATLAB
authors:
  - name: Dimitris Floros
    orcid: 0000-0003-1190-4075
    affiliation: 1
  - name: Nikos Pitsianis
    orcid: 0000-0002-7353-3524
    affiliation: "1,2"
  - name: Xiaobai Sun
    affiliation: 2
affiliations:
  - name: Department of Electrical and Computer Engineering, Aristotle University of Thessaloniki, Thessaloniki 54124, Greece
    index: 1
  - name: Department of Computer Science, Duke University, Durham, NC 27708, USA
    index: 2
date: 30 August 2020
bibliography: references.bib
---

Summary
=======

We provide ${\rm FG}_{\ell}{\rm T}$, a `C/C++` multi-threading library,
for Fast Graphlet Transform of large, sparse, undirected
networks/graphs. The graphlets in dictionary $\Sigma_{16}$, shown in \autoref{fig:graphlets},
are used as encoding elements to capture topological connectivity
quantitatively and transform a graph $G=(V,E)$ into a $|V| \times 16$
array of graphlet frequencies at all vertices. The $16$-element vector
at each vertex represents the frequencies of induced subgraphs, incident
at the vertex, of the graphlet patterns. The transformed data array
serves multiple types of network analysis: statistical or/and
topological measures, comparison, classification, modeling, feature
embedding and dynamic variation, among others. The library
${\rm FG}_{\ell}{\rm T}$ is distinguished in the following key aspects.
(1) It is based on the fast, sparse and exact transform formulas
in [@floros2020b], which are of the lowest time and space complexities
among known algorithms, and, at the same time, in ready form for
globally streamlined computation in matrix-vector operations.
(2) It leverages prevalent multi-core processors, with multi-threaded
programming in `Cilk` [@blumofe1996], and uses sparse graph computation
techniques to deliver high-performance network analysis to individual
laptops or desktop computers.
(3) It has `Python`, `Julia`, and `MATLAB` interfaces for easy integration
with, and extension of, existing network analysis software.

Statement of need
=================

With continuous and rapid growth in interest, understanding, and
applications of the graphlet
transform [@przulj2006; @przulj2004; @przulj2007; @przulj2019; @yaveroglu2015; @sarajlic2016; @floros2020a; @floros2020],
an efficient software for the transform is in great need, especially for
advanced study of, and discovery in, diverse biological networks and
emerging networks in many application domains.

With ease of use, the ${\rm FG}_{\ell}{\rm T}$ user gets
high-performance graphlet transform by several advanced features of
the library. Instead of neighbor-by-neighbor search and recognition of
induced subgraphs with the graphlet patterns, we use sparse and global
formulas to theoretically and effectively reduce the redundancy among
neighborhoods and make the computation streamlined in matrix-vector
operations. We provide in \autoref{tab:graph-form} a summary of the
formulas from [@floros2020b].  We use multi-threaded programming to
leverage multi-core processors in personal computers. We use sparse
computation techniques, operation prefiltering and scheduling in order
to reduce space complexity, the amount of unnecessary computation, the
amount of data revisits, memory access latency, and imbalance among
multi-threaded computation.

We illustrate in \autoref{tab:experiments} the timing results with
$12$ networks of various types and sizes. 
The networks are from 
[DIMACS10](http://sparse.tamu.edu/DIMACS10):
[smallworld](http://sparse.tamu.edu/DIMACS10/smallworld), 
[598a](http://sparse.tamu.edu/DIMACS10/598a), 
[preferentialAttachment](http://sparse.tamu.edu/DIMACS10/preferentialAttachment), 
[144](http://sparse.tamu.edu/DIMACS10/144), 
[vsp_model1](http://sparse.tamu.edu/DIMACS10/vsp_model1_crew1_cr42_south31), 
[vsp-south31-slptsk](http://sparse.tamu.edu/DIMACS10/vsp_south31_slptsk), and
[coPapersDBLP](http://sparse.tamu.edu/DIMACS10/coPapersDBLP), 
and from 
[SNAP](http://snap.stanford.edu/data):
[com-Amazon](http://sparse.tamu.edu/SNAP/com-Amazon),
[loc-Gowalla](http://sparse.tamu.edu/SNAP/loc-Gowalla),
[com-LiveJournal](http://sparse.tamu.edu/SNAP/com-LiveJournal),
[com-Orkut](http://sparse.tamu.edu/SNAP/com-Orkut), and
[com-Friendster](http://sparse.tamu.edu/SNAP/com-Friendster).
All the experiments are on a
single multi-core processor. The transform of network com-LiveJournal
with 35 millions of edges takes less than 1 minute. The transform of
network com-Friendster with 1.8 billions of edges takes about 2.5
hours with $16$ threads while it takes 1.5 day with a single
thread. The sequential computation alone
substantially outpaces other available software. 



Figures
================

![Dictionary $\Sigma_{16}$ of $16$ graphlets. In each graphlet, the
designated incidence node is specified by the red square marker, its
automorphic position(s) specified by red circles. The total ordering
(labeling) of the graphlets is by the following nesting conditions. The
graphlets are ordered first by non-decreasing number of vertices.
Graphlets with the same vertex set belong to the same family. Within
each family, the ordering is by non-decreasing number of edges, and then
by increasing degree at the incidence node (except the $4$-cycle). The
inclusion of $\sigma_{0}$ is necessary to certain vertex partition
analysis [@floros2020].\label{fig:graphlets}](figs/graphlet-dictionary.png)

![Sparse and exact formulas for the Fast Graphlet Transform (FG$_\ell$T)
with dictionary $\Sigma_{16}$. There are two sets of formulas. The first
set is for computing the raw frequencies $\hat{d}_j$, $0\leq j \leq 15$,
i.e., the frequencies of subgraphs with the graphlet patterns in
dictionary $\Sigma_{16}$. The formulas are tabulated in the two tables
to the left. For two vectors $a$ and $b$, $a-b$ denotes the
sparse/rectified difference $\max\{b - a, 0\}$. The difference between
two sparse matrices is similarly denoted. The auxiliary formulas are in
the bottom table. The second set of formulas is for converting the raw
frequencies to the net frequencies $d_j$, $0\leq j\leq 15$, i.e., the
frequencies of induced subgraphs with the graphlet patterns. The matrix
for forward conversion, from the net frequencies to the raw ones, is
$U_{16} = U_5 \oplus U_{11}$. The matrix is shown to the right. The
backward conversion matrix $U_{16}^{-1}$ is explicitly formed and used,
it has the same nonzero pattern as $U_{16}$.\label{tab:graph-form}](figs/graphlet-transform.png)

![Execution time of the Fast Graphlet Transform, with software library
${\rm FG}_{\ell}{\rm T}$ in version 1.0.0, of $12$ networks on a single
Xeon processor. The networks are taken from two data sources (column 1),
they are listed row by row in the table. Some are snapshots of
real-world networks, the others are generated by models based on
real-world networks. The basic statistics of each network are shown in
columns 3 to 6: the number of nodes, number of edges, and average and
maximal node degrees, where $K$ stands for a thousand and $M$ for a
million. The execution time is wall-clock time in seconds (default),
minutes and hours. It is reported under $5$ execution options:
single-thread (sequential), $2$-threads, doubled up to $16$-threads.
Each execution time under a minute is the average over $5$ runs. Speedup
factors over the single-thread execution are placed next to the
execution time. We observe that the speedup factors are lower with
sparser networks. The experiments are carried out on an Intel Xeon
E5-2640 v4, with $10$ cores (up to $20$ concurrent threads via
hyper-threading) and 700 GB of DDR4 RAM. Cilk [@blumofe1996] is used for
multi-threaded programming.\label{tab:experiments}](figs/experiments-curated.png)

# References
