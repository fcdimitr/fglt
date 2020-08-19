% fglt.m Help file for fglt MEX-file.
% 
% FGLT - Fast Graphlet Transform.
%   
%  [FNET, FRAW] = FGLT( A ) computes the Fast Graphlet Transform,
%  given the adjacency matrix A of the input graph. Code currently
%  works only for undirected, unweighted graphs. The input must be
%  sparse with an empty diagonal.
% 
% INPUT
%  
%   A           Adjacency matrix                [n-by-n sparse]
% 
% OUTPUT 
%   
%   FNET        Graphlet degrees (net)          [n-by-16]
%   FRAW        Graphlet degrees (raw)          [n-by-16]
%  
%  
% REFERENCES 
%  
%  [1] D. Floros, N. Pitsianis, and X. Sun, “Fast graphlet transform
%      of sparse graphs,” IEEE High Performance Extreme Computing
%      Conference, 2020. Available: https://arxiv.org/abs/2007.11111.
%  
