---
title: FG$\lambda$T: Fast Graphlet Transform'
tags:
  - graph theory
  - graphlet counting
  - graph analysis
  - network analysis
  - C++
  - C
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
date: 20 August 2020
bibliography: references.bib
---

# Summary (to be removed from the paper, only for GitHub page)

We present a fast, parallel graphlet transform library, named
FG$\lambda$T, to tackle the problem of graphlet counting on large,
sparse graphs/networks. Graphlets are fundamental topology elements of
all networks or graphs, the same way as shapelets are for time series
classification or as wavelets for spectro-temporal analysis in signal
processing. The library computes vertex-wise all 16 graphlets up to
and including quad-node graphlets, see \autoref{fig:graphlets}. The
implementation reduces unnecessary operations and minimizes the number
of revisits to the same sub-matrix and the amount of working
memory. The library utilizes the `Cilk` framework for parallelization
on multi-core CPUs. The library is implement in `C++` with an optional
`MATLAB` interface. All functions are documented using `Doxygen`.

# Introduction

Graphlets have recently gained attention as coding elements to encode
graph/network topological information at multiple
granularities. Graphlets are fundamental topology elements of all
networks or graphs, the same way as shapelets are for time series
classification or as wavelets for spectro-temporal analysis in signal
processing. The concepts of graphlets, graphlet frequency, and
graphlet analysis are originally introduced in 2004 by Pržulj, Corneil
and Jurisica [??] and have been substantially extended since [??].  We
anticipate a growing of interest in the use of graphlets for
graph/network analysis. To enable such analytic tasks, we present a
parallel implementation of the graphlet transform.

First, we mention in passing the fast graphlet transform, as presented
in [@hpec]. Second, we present the FG$\lambda$T library, which
implements the fast graphlet transform for multi-core CPUs. The
dictionary used in the implementation consists of every graphlet up to
and including quad-node graphlets (see \autoref{fig:graphlets}), with
a total length of 16. We denote this dictionary as $\Sigma_16$. We
highlight specific properties and contributions in the
implementation. Third, we evaluate the library on five real-world
networks and compare the execution with ORCA, considered the
state-of-the-art for graphlet transform.

![Dictionary $\Sigma_16$ of 16 graphlets. In each graphlet, the
designated incidence node is specified by the red square marker, its
automorphic position(s) specified by red circles. The total ordering
(labeling) of the graphlets is by the following nesting
conditions. The graphlets are ordered first by non-decreasing number
of vertices. Graphlets with the same vertex set belong to the same
family. Within each family, the ordering is by non-decreasing number
of edges, and then by increasing degree at the incidence node (except
the 4-cycle). The inclusion of $\sigma_0$ is necessary to certain
vertex partition analysis [@Pearson:2017].](figs/graphlet-dictionary.png)

# Fast graphlet transform

In [@hpec] we present the fast method for graphlet transform of any
large, sparse graph, with any sub-dictionary of $\Sigma_16$ as the
coding basis. The solution is deterministic, exact and directly
applicable to any range of graph size. Our solution method establishes
remarkable records at once in multiple aspects -- time complexity,
memory space complexity, program complexity and high-performance
implementation. Particularly, the time complexity of the fast graphlet
transform with any dictionary $\Sigma \subseteq \Sigma_16$ is linear
in $(|V| + |E|)|\Sigma|$ on degree-bounded graphs. 

 --------------- ------------------------------ --------------------------------------------------------------------
  $\sigma_{0}$    singleton                      $\hat{d}_{0} = e$
  $\sigma_{1}$    1-path, at an end              $\hat{d}_{1} = p_1$
  $\sigma_{2}$    2-path, at an end              $\hat{d}_{2} = p_2$
  $\sigma_{3}$    bi-fork, at the root           $\hat{d}_{3} = p_1 \odot  (p_1 - 1) / 2$
  $\sigma_{4}$    3-clique, at any node          $\hat{d}_{4} = c_3$
  $\sigma_{5}$    3-path, at an end              $\hat{d}_{5} = p_3$
  $\sigma_{6}$    3-path, at an interior node    $\hat{d}_{6} = p_2 \odot ( p_{1} - 1) - 2\, c_3$
  $\sigma_{7}$    claw, at a leaf                $\hat{d}_{7} = A \cdot  \big( (p_1 - 1) \odot (p_1 - 2) \big) / 2$
  $\sigma_{8}$    claw, at the root              $\hat{d}_{8} = p_1 \odot (p_1 - 1) \odot (p_1 - 2) / 6$
  $\sigma_{9}$    dipper, at the handle tip      $\hat{d}_{9} = A \cdot c_{3} - 2\,  c_{3}$
  $\sigma_{10}$   dipper, at a base node         $\hat{d}_{10} = C_{3}  \cdot (p_{1} - 2)$
  $\sigma_{11}$   dipper, at the center          $\hat{d}_{11} = (p_1 - 2) \odot c_3$
  $\sigma_{12}$   4-cycle, at any node           $\hat{d}_{12} = c_4$
  $\sigma_{13}$   diamond, at an off-cord node   $\hat{d}_{13}  = D_{4,c} \,  e/2$
  $\sigma_{14}$   diamond, at an on-cord node    $\hat{d}_{14} = D_{4,3} \, e / 2$
  $\sigma_{15}$   4-clique, at any node          $\hat{d}_{15}   =  T \,  e/6$
  --------------- ------------------------------ --------------------------------------------------------------------

With each graphlet $\sigma_i$ we derive first the formula for its
*raw* or independent frequency at vertex $v$, denoted by
$\hat{d}_i(v)$, see \autoref{tab:transform-formulas}. The raw frequency
vector is $\hat{f}(v) = \left[ \hat{d}_0(v), \, \hat{d}_1(v) \, \dots,
\, \hat{d}_{|\Sigma|-1}(v) \right]$. We then convert the raw
frequencies to *net* frequencies, $f(v) = \left[ d_0(v), \, d_1(v) \,
\dots, \, d_{|\Sigma|-1}(v) \right]$. The net frequencies depend on
the inter-relationships between the graphlets in a dictionary.  The
raw frequency of graphlet $\sigma$ at vertex $v$ corresponds to the
number of $\sigma$-pattern subgraphs incident at node $v$. The net
frequency corresponds to the number of $\sigma$-pattern *induced*
subgraphs, respectively.

  $\! U_{16}\!$     $d_{0}$   $d_{1}$   $d_{2}$   $d_{3}$   $d_{4}$   $d_{5}$   $d_{6}$   $d_{7}$   $d_{8}$   $d_{9}$   $d_{10}$   $d_{11}$   $d_{12}$   $d_{13}$   $d_{14}$   $d_{15}$
  ---------------- --------- --------- --------- --------- --------- --------- --------- --------- --------- --------- ---------- ---------- ---------- ---------- ---------- ----------
  $\hat{d}_{0}$        1                                                                                                                                                      
  $\hat{d}_{1}$                  1                                                                                                                                            
  $\hat{d}_{2}$                            1                   2                                                                                                              
  $\hat{d}_{3}$                                      1         1                                                                                                              
  $\hat{d}_{4}$                                                1                                                                                                              
  $\hat{d}_{5}$                                                          1                                       2         1                     2          4          2          6
  $\hat{d}_{6}$                                                                    1                                       1          2          2          2          4          6
  $\hat{d}_{7}$                                                                              1                   1         1                                2          1          3
  $\hat{d}_{8}$                                                                                        1                              1                                1          1
  $\hat{d}_{9}$                                                                                                  1                                          2                     3
  $\hat{d}_{10}$                                                                                                           1                                2          2          6
  $\hat{d}_{11}$                                                                                                                      1                                2          3
  $\hat{d}_{12}$                                                                                                                                 1          1          1          3
  $\hat{d}_{13}$                                                                                                                                            1                     3
  $\hat{d}_{14}$                                                                                                                                                       1          3
  $\hat{d}_{15}$                                                                                                                                                                  1


We provide in \autoref{tab:conversion} the (upper triangular) matrix
$U_{16}$ of non-negative coefficients for mapping net frequencies
$d(v)$ to raw frequencies $\hat{d}(v)$. The conversion coefficients
are determined by subgraph-isomorphisms among graphlets and
automorphisms in each graphlet. In implementation, we use the inverse
matrix $U_{16}^{-1}$ (which has the same sparsity pattern as $U_{16}$)
to convert the raw frequencies to net.

# FG$\lambda$T library

FG$\lambda$T is a C++ library that implements the fast graphlet
transform, accelerating the analysis of very large, sparse graphs. A
MATLAB wrapper around the C++ library is provided, maintaining
efficiency, with an easy-to-use interface. The library leverages the
`Cilk` framework for parallelism on multi-core CPUs.

We highlight three implementation details regarding: (i) the use of
sparse masks and filtering, (ii) operation scheduling, and (iii)
memory allocation and memory accesses. The objective is to reduce or
eliminate unnecessary operations and minimize the number of revisits
to the same sub-matrix and the amount of working memory. In the case
of Hadamard products with the sparse matrix $A$ in
\autoref{tab:transform-formulas}, the result cannot be denser than
$A$. The result is only computed at the nonzero elements of $A$,
significantly reducing execution time. Also, the conversion matrix
$U_{16}$ is used as a filtering step, in the following way: Whenever a
raw count is 0, that means that all corresponding net counts are also
zero. By appropriately removing columns we check which remaining raw
counts are needed to evaluate all net counts. For example, if the raw
count of any quad-node graphlet at given vertex is zero, then
$\sigma_15$ (a.k.a $K_4$) is also zero, therefore we omit its
evaluation. Operations using the same auxiliary matrix are grouped
together; all possible outputs are computed by visiting each matrix
element once. No auxiliary matrix is explicitly stored, all matrix
elements are evaluated on-the-fly during computation.

# Real-world network comparisons

We evaluate the performance of the FG$\lambda$T library on five
real-world networks (set \autoref{tab:experimental-results} for
details) and compare its efficiency to ORCA [@orca], which is
considered state-of-the-art regarding graphlet counting. On average,
the sequential version of FG$\lambda$T is 1.5x to 5x faster than ORCA,
while the parallel version with 16-threads reaches a speedup of 42x on
patents citation graph. We present experimental results in table
\autoref{tab:experimental-results}. We note that both methods are
exact and agree on all graphlet counts.

|Name                 |$|V|$  |$|E|$  |$\overline{d}$|ORCA (Seq.)|FG$\lambda$T (Seq.)|FG$\lambda$T (2-threads)|FG$\lambda$T (4-threads)|FG$\lambda$T (8-threads)|FG$\lambda$T (16-threads)|
|:-------------------:|:-----:|:-----:|:-------:|:---------:|:-----------------:|:----------------------:|:----------------------:|:----------------------:|:-----------------------:|
|cit-Patents_adj      |3.8 M  |16.5 M |4.4      |272.8 sec  |51.9 sec (x5.3)    |28.9 sec (x9.4)         |15.9 sec (x17.1)        | 9.0 sec (x30.2)        | 6.4 sec (x42.8)         |
|facebook_combined_adj|4.0 K  |88.2 K |21.8     | 1.4 sec   | 0.5 sec (x3.0)    | 0.2 sec (x5.6)         | 0.2 sec (x9.3)         | 0.1 sec (x13.5)        | 0.1 sec (x17.6)         |
|P1a                  |139.4 M|148.9 M|1.1      |422.7 sec  |280.8 sec (x1.5)   |149.5 sec (x2.8)        |81.6 sec (x5.2)         |45.4 sec (x9.3)         |31.0 sec (x13.6)         |
|V2a                  |55.0 M |58.6 M |1.1      |147.3 sec  |97.2 sec (x1.5)    |53.8 sec (x2.7)         |30.3 sec (x4.9)         |18.3 sec (x8.1)         |13.2 sec (x11.2)         |


# References
