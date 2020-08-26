function strName = graphletName(k)
% GRAPHLETNAME - Return graphlet name
%   
% DESCRIPTION
%
%   NAME = GRAPHLETNAME( K ) returns a user-readable name for the
%   graphlet at 'k'-th column
%
  
Graphlet = [
    " 0 vertex (==1)     "
    " 1 degree           "
    " 2 2-path           "
    " 3 bifork           "
    " 4 3-cycle          "
    " 5 3-path, end      "
    " 6 3-path, interior "
    " 7 claw, leaf       "
    " 8 claw, root       "
    " 9 paw, handle      "
    "10 paw, base        "
    "11 paw, center      "
    "12 4-cycle          "
    "13 diamond, off-cord"
    "14 diamond, on-cord "
    "15 4-clique         "];
  

strName = Graphlet(k);
  
end



%%------------------------------------------------------------
%
% AUTHORS
%
%   Dimitris Floros                         fcdimitr@auth
%   Nikos Pitsianis                         nikos@cs.duke.edu
%
% VERSION       0.1
%
% CHANGELOG 
%
%   0.1 (Aug 15, 2020) - Nikos
%       * initial implementation
%
% TIMESTAMP     <Aug 15, 2020: 13:10:08 Nikos>
%
% ------------------------------------------------------------

