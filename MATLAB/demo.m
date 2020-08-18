%% SCRIPT: DEMO
%
%   Demonstration of Fast Graphlet Transform (FGlT)
%


%% CLEAN-UP

clear
close all


%% PARAMETERS

A = sprand(5,5,2/5);
A = sparse( logical( A+A' ) );
A = A - diag(diag(A));

%% (BEGIN)

fprintf('\n *** begin %s ***\n\n',mfilename);

%% COMPUTE GRAPHLETS

ticFGlT = tic; fprintf( '...compute graphlets...\n' ); 

F = fglt( A );

fprintf( '   - DONE in %.2f sec\n', toc(ticFGlT) );


%% (END)

fprintf('\n *** end %s ***\n\n',mfilename);


%%------------------------------------------------------------
%
% AUTHORS
%
%   Dimitris Floros                         fcdimitr@auth.gr
%
% VERSION       0.1
%
% CHANGELOG 
%
%   0.1 (Aug 18, 2020) - Dimitris
%       * initial implementation
%
% TIMESTAMP     <Aug 18, 2020: 11:44:11 Dimitris>
%
% ------------------------------------------------------------

