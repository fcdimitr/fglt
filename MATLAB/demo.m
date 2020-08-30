%% SCRIPT: DEMO
%
%   Demonstration of Fast Graphlet Transform (FGlT)
%


%% CLEAN-UP

clear
close all

%% PARAMETERS

listDataFile = dir('data/*.mat');

%% (BEGIN)

fprintf('\n *** begin %s ***\n\n',mfilename);

%% COMPUTE GRAPHLETS

ticFGlT = tic; fprintf( '...compute graphlets...\n' ); 

for iData = 1:length( listDataFile )

  structData = load( ['data' filesep listDataFile(iData).name] );
  Fnet = fglt( structData.A );
  
  figure(1)
  plot(graph(structData.A))
  title( listDataFile(iData).name )
  
  fprintf([repmat('%2d ',1,size(Fnet,2)) '\n'],Fnet');
  
  pause
  
end


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
%   1.0 (Aug 30, 2020) - Dimitris
%       * added multiple datasets, looping through each
% 
%   0.1 (Aug 18, 2020) - Dimitris
%       * initial implementation
%
% TIMESTAMP     <Aug 30, 2020: 22:26:28 Dimitris>
%
% ------------------------------------------------------------

