function fglt
% FGLT - Fast Graphlet Transform.
%   
%  [FNET, FRAW] = FGLT( A ) computes the Fast Graphlet Transform,
%  given the adjacency matrix A of the input graph.
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
% NOTES 
%  
%  Code currently works only for undirected, unweighted graphs. The
%  input must be sparse.
%  
% REFERENCES 
%  
%  <none>
%  
