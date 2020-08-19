function [draw, dnet] = fglt(A)
% FGLT - Compute Fast Graphlet Transform.
%   
%  D = FGLT( A ) computes the Fast Graphlet Transform, given the
%  adjacency matrix A of the input graph.
% 
% INPUT
%  
%   A           Adjacency matrix                [n-by-n sparse]
% 
% OUTPUT 
%   
%   D           Graphlet degrees                [n-by-16]
%  
% NOTES 
%  
%  Code currently works only for undirected, unweighted graphs.
%  
% REFERENCES 
%  
%  <none>
%  
% DEPENDENCIES 
%  
%  private/fgt (MEX)
%  
   
  try
    % call MEX functions (inside private)
    draw = fglt( A );
    dnet = raw2net(draw);
  catch ME
    switch ME.identifier
      case 'MATLAB:UndefinedFunction'
        error( [mfilename ':UncompiledSources'], ...
               ' Compile MEX files by issuing\n\n  fgtmake\n\n under +graph/private');
      otherwise
        rethrow(ME)
    end
  end
end
  
