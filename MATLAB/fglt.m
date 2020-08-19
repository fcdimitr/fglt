% fglt.m Help file for fglt MEX-file.
% 
% FGLT - Fast Graphlet Transform.
%   
%  [Fnet, Fraw] = FGLT( A ) computes the Fast Graphlet Transform,
%  given the adjacency matrix A of the input graph that must be
%  undirected and unweighted. Matrix A must be sparse with an empty
%  diagonal.
% 
% INPUT
%  
%   A           Adjacency matrix                [n-by-n sparse]
% 
% OUTPUT 
%   
%   Fnet        Graphlet degrees (net)          [n-by-16]
%   Fraw        Graphlet degrees (raw)          [n-by-16]
%  
% The net (Fnet) and the raw (Fraw) frequencies of the following 
% graphlets are computed:
%
% sigma | Description
% ------+------------------------------
%  0    | singleton
%  1    | 1-path, at an end
%  2    | 2-path, at an end 
%  3    | bi-fork, at the root 
%  4    | 3-clique, at any node
%  5    | 3-path, at an end
%  6    | 3-path, at an interior node
%  7    | claw, at a leaf
%  8    | claw, at the root
%  9    | dipper, at the handle tip
% 10    | dipper, at a base node
% 11    | dipper, at the center
% 12    | 4-cycle, at any node
% 13    | diamond, at an off-cord node
% 14    | diamond, at an on-cord node 14
% 15    | 4-clique, at any node
%
%
% REFERENCE
%  
%  [1] D. Floros, N. Pitsianis, and X. Sun, Fast graphlet transform
%      of sparse graphs,ù IEEE High Performance Extreme Computing
%      Conference, 2020. Available: https://arxiv.org/abs/2007.11111.
%  
